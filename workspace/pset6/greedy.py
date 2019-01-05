import cs50

print("O hai! ")

while True:
    print("How much change is owed?")
    n= cs50.get_float()
    if n > 0:
        break

cents = round(100*n)
count=0

if cents%25 < cents:
    q = (cents-(cents%25))//25
    count+=q
    cents=(cents%25)
if cents%10 < cents:
    q = (cents-(cents%10))//10
    count+=q
    cents=(cents%10)
if cents%5 < cents:
    q = (cents-(cents%5))//5
    count+=q
    cents=(cents%5)
if cents%1 < cents:
    q = (cents-(cents%1))//1
    count+=q
    cents=(cents%1)

print(count)

