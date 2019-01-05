#include<cs50.h>
#include<stdio.h>
#include<ctype.h> //toupper() is present in this header file
#include<string.h>


int main( void )
{
    string s = get_string();
    char c[5];
    if(s!=NULL)//to check whether the correct string value is inputed
    {
    c[0]=s[0];
    for(int i=0,j=0,n=strlen(s);i<n;i++)// loop over entire string length
    {

    if(s[i]==' ')//checks for space
    {
        i++;
        j++;
        c[j]=s[i];
    }
    }
    for(int i =0,n=strlen(c); i<n;i++)
        printf("%c",toupper(c[i]));
        printf("\n");
    }
}
