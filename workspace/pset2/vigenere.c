#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>


bool checkAlpha(string k);



int main (int argc , string argv[])
{
    if(argc==2)//to commandline args
    {
        bool c = checkAlpha(argv[1]);
        if(c)
        {
            string k = argv[1];
            printf("plaintext: ");
            string s = get_string();
            if(s!=NULL)
            {

                for(int i=0,j=0,n=strlen(s),kl=strlen(k);i<n;i++)//looping over clear entire length
                {
                    if(isalpha(s[i]))//check for alphabet
                {
                    if(isupper(s[i]))//check for uppercase
                    {


                    int num,b,kind;

                    b= j%kl;
                    j++;//grouping in different groups
                    char offset;
                    num =s[i]%65;
                    kind=(toupper(k[b]))%65;// to covert into alphabet index
                    offset = (char)((num+kind)%26);//equivalent shifts
                    s[i]=offset+65;//shifted text

                    }
                else
                    {
                    int num,b,kind;

                    b= j%kl;
                    j++;
                    char offset;
                    num =s[i]%97;
                    kind =(tolower(k[b]))%97;
                    offset = (char)((num+kind)%26);//equivalent shifts
                    s[i]=offset+97;//shifted text
                    }



                }
                }printf("ciphertext: %s\n",s);//encrypted text


            }


        }
        else
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }



    }




    else
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }

}

bool checkAlpha(string s)
{
    string k =s;
    for(int i=0,n=strlen(k);i<n;i++)
    {
    if(!(isalpha(k[i])))
    {

        return false;
    }
    }

        return true;

}




