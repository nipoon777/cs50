import cs50
import sys

#caesar implementation using python

def main():
    if(len(sys.argv)!=2):
        print("usage : ./caesar + key")
        exit(1)
    k = int(sys.argv[1])
    print("plaintext: ",end="")
    s= cs50.get_string()
    if(s==None):
        sys.exit()
    else:
        cipher =[]
        for i in s:
            if(i.isalpha()):
                if(i.isupper()):
                    #predefined array function cipher
                    cipher.append(chr(((ord(i) - 65 + k) % 26) + 65))
                else:
                    cipher.append(chr(((ord(i) - 97 + k) % 26) + 97))
            else:
                cipher.append(i)
    print("ciphertext: ",end="")
    for i in cipher:
        print(i,end="")
    #to print and endline character
    print()
#use to call the main function

if __name__ =="__main__":
    main()