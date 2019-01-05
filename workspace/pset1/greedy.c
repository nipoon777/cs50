#include<cs50.h>
#include<stdio.h>
#include<math.h>

int main(void)
{
    float n,cents;
    int c=0;
    do
    {
        printf("O hai! How much change is owed?\n");
        n = get_float();
    }
    while(n<0);
    cents =roundf(100*n);

    while(cents>=25)
    {
        c++;
        cents = cents-25;

    }
    while(cents>=10)
    {
        c++;
        cents = cents-10;
    }
    while(cents>=5)
    {
        c++;
        cents = cents-5;

    }
    while(cents>=1)
    {
        c++;
        cents = cents -1;
    }
    printf("%i\n",c);


}