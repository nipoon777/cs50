from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
from datetime import datetime

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():

    portfolioSymbols= db.execute("SELECT shares,symbol FROM portfolio WHERE id = :id",id = session["user_id"])

    total_cash = 0
    for portfolioSymbol in portfolioSymbols:
        symbol = portfolioSymbol["symbol"]
        shares = portfolioSymbol["shares"]
        stock = lookup(symbol)
        total = shares * stock["price"]

        total_cash += total

        db.execute("UPDATE portfolio SET price =:price,total =:total WHERE id =:id AND symbol =:symbol",\
                    price = usd(stock["price"]),total= usd(total), id = session["user_id"],symbol = symbol)

    updated_cash = db.execute("SELECT cash FROM  users WHERE id= :id", id= session["user_id"])

    total_cash +=updated_cash[0]["cash"]

    updated_portfolio =db.execute("SELECT * FROM portfolio WHERE id = :id",id = session["user_id"])

    return render_template("index.html",stocks = updated_portfolio,\
    cash = usd(updated_cash[0]["cash"]),total= usd(total_cash))






@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "GET":
            return render_template("buy.html")
    else:
        # ensure proper symbol
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Invalid Symbol")

        # ensure proper number of shares
        try:
            shares = int(request.form.get("shares"))
            if shares < 0:
                return apology("Shares must be positive integer")
        except:
            return apology("Shares must be positive integer")

        # select user's cash
        cash = db.execute("SELECT cash FROM users WHERE id = :id", \
                            id=session["user_id"])

        # check if enough money to buy
        if not cash or float(cash[0]["cash"]) < stock["price"] * shares:
            return apology("Not enough money")

        # update history
        db.execute("INSERT INTO histories (symbol, shares, price, id,transacted) \
                    VALUES(:symbol, :shares, :price, :id,:transacted)", \
                    symbol=stock["symbol"], shares=shares, \
                    price=usd(stock["price"]), id=session["user_id"],transacted= str(datetime.now()))

        # update user cash
        db.execute("UPDATE users SET cash = cash - :purchase WHERE id = :id", \
                    id=session["user_id"], \
                    purchase=stock["price"] * float(shares))

        # Select user shares of that symbol
        user_shares = db.execute("SELECT shares FROM portfolio \
                           WHERE id = :id AND symbol=:symbol", \
                           id=session["user_id"], symbol=stock["symbol"])

        # if user doesn't has shares of that symbol, create new stock object
        if not user_shares:
            db.execute("INSERT INTO portfolio (name, shares, price, total, symbol, id) \
                        VALUES(:name, :shares, :price, :total, :symbol, :id)", \
                        name=stock["name"], shares=shares, price=usd(stock["price"]), \
                        total=usd(shares * stock["price"]), \
                        symbol=stock["symbol"], id=session["user_id"])

        # Else increment the shares count
        else:
            shares_total = user_shares[0]["shares"] + shares
            db.execute("UPDATE portfolio SET shares=:shares \
                        WHERE id=:id AND symbol=:symbol", \
                        shares=shares_total, id=session["user_id"], \
                        symbol=stock["symbol"])

        # return to index
        return redirect(url_for("index"))


@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    histories=db.execute("SELECT * FROM histories WHERE id =:id", id = session["user_id"])

    return render_template("history.html",histories= histories)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == "POST":
        rows = lookup(request.form.get("symbol"))

        if not rows:
            return apology("Invalid Symbol")

        return render_template("quoted.html", stocks=rows)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():


    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
        # check the correction of the passwords
        elif request.form.get("password") != request.form.get("confirmation"):

            return apology("un matched password")

        result = db.execute("INSERT INTO users(username,hash)\
        VALUES(:username,:hash)",\
        username =request.form.get("username"),\
        hash =pwd_context.hash(request.form.get("password")))
        if not result:
            return apology("user exists")



        # remember which user has logged in
        session["user_id"] = result

        return redirect(url_for("login"))

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "GET":
        return render_template("sell.html")
    else:
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("INVALID SYMBOL")
        try:

            shares = int(request.form.get("shares"))

            if shares <0:
                return render_template("Shares must be positive integer")
        except:
            return render_template("shares must be a positive integer")

        userShares = db.execute("SELECT shares FROM portfolio WHERE id =:id AND symbol =:symbol",id = session["user_id"],symbol = stock["symbol"])

        if not userShares or int(userShares[0]["shares"])<shares:
            return apology("NOT Enough Shares")
        db.execute("INSERT INTO histories(symbol,shares,price,id,transacted)\
        values(:symbol,:shares,:price,:id,:transacted)",symbol = stock["symbol"],shares= -shares,price= usd(stock["price"]), id = session["user_id"],\
        transacted = str(datetime.now()))

        db.execute("UPDATE users SET cash = cash +:sold WHERE id = :id " ,id = session["user_id"], sold = stock["price"]*float(shares))

        sharesTotal = userShares[0]["shares"] - shares

        if sharesTotal == 0:
            db.execute("DELETE FROM portfolio WHERE id = :id AND symbol = :symbol", id = session["user_id"],symbol = stock["symbol"])

        else:
            db.execute("UPDATE portfolio SET shares =:shares WHERE id = :id AND symbol = :symbol", shares = sharesTotal, id = session["user_id"],symbol = stock["symbol"])
        return redirect(url_for("index"))
@app.route("/changepassord", methods=["GET", "POST"])
@login_required
def changepassword():
    if request.method == "GET":
        return render_template("changepassword.html")
    else:
        if not request.form.get("password"):
            return apology("must provide old password")
        else:

            passOld = db.execute("SELECT hash FROM users WHERE id =:id", id = session["user_id"])
            if len(passOld)==1 and pwd_context.verify(request.form.get("password"), passOld[0]["hash"]):
                if request.form.get("newpassword") == request.form.get("conpassword"):

                    rows = db.execute("UPDATE users SET hash =:hash WHERE id =:id", hash = pwd_context.hash(request.form.get("conpassword")), id = session["user_id"])
                    flash("password changed successfully")
                    return redirect(url_for("index"))
                else:
                    return apology("password not matched")
            else:
                return apology("invalid password")


