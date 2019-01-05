#include<cs50.h>
#include<stdio.h>

int main(void)
{
    int height;
    do
    {
    printf("Height: ");
    height = get_int();
    }
    while(height<0||height>=24);

    for(int i=0 ;i<height;i++)
        {
            for(int j =1;j<height-i;j++)
            {
                printf(" ");
            }
            for(int k= 0; k<=i+1;k++)

                printf("#");

                printf("\n");
        }
}