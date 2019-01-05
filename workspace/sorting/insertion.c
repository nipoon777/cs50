#include<stdio.h>
#include<cs50.h>
void insort(int a[],int n);

int main(void)
{
    int n;
    do
    {

        printf("Enter the size of the array\n");
        scanf("%d",&n);

    }
    while(n<0);

    printf("Input the array\n");


    int a[n], i, j;


    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);

    }
    printf("The inputted array is \n [");
    for(i=0 ;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("]\n");

    insort(a,n);
}


void insort(int a[] , int n)
{
    int key, i ,j;
    for(j =1 ;j <n ;j++)
    {
        key = a[j];

        i = j-1;
        while(a[i]>key && i>=0)
        {
            a[i+1]=a[i];
            i--;
        }
        a[i+1]=key;

    }

    printf("the sorted list is \n[ ");
    for(i =0 ;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("]\n");
}
