#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>// to use strlen
#include<stdlib.h>

int main(int argc, string argv[])
{
    int m = argc;
    if(m==2)
    {
        int k = atoi(argv[1]);//convert the string into a integer
            printf("plaintext: ");
            string s= get_string();// get the user input
        if(s!= NULL)
        {


// in order to go around the
        for(int i=0,n=strlen(s);i<n;i++)//looping over entire length
        {
            if(isalpha(s[i]))//check for alphabet
            {
                if(isupper(s[i]))
                {
                    int num;
                    char offset;
                    num =s[i]%65;// to covert into alphabet index
                    offset = (char)((num+k)%26);//equivalent shifts
                    s[i]=offset+65;//shifted text
                }
                else
                {
                    int num;
                    char offset;
                    num =s[i]%97;
                    offset = (char)((num+k)%26);//equivalent shifts
                    s[i]=offset+97;//shifted text
                }


            }
        }
        printf("ciphertext: %s\n",s);//encrypted text


    }


    }

    else
    {
        eprintf ("usage : ./caesar + key \n");// in case of wrong command line argument

        return 1;
    }



}