#include<stdio.h>
#include<cs50.h>
#include<math.h>

void mergesort(int a[],int p , int r);
void merge(int a[],int p,int q,int r);

int main(void)
{
    int n ;
    do{
        printf("Enter the size of array");
        scanf("%d",&n);

    }while(n<0);


    int a[n];
    printf("Input the array");

    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);

    }
    int p =0;
    int r =n;

    mergesort(a,p,r);
    for(int i=0;i<n;i++)
    {
        printf("%d",a[i]);

    }

}


void merge(int a[],int p , int q ,int r)
{
    int i,j;
    int n1 = (q-p)+1;
    int n2 = r-q;

    int L[n1] ,R[n2];

    for(i=0;i<n1;i++)
    {
        L[i]= a[p+i];
    }
    L[n1-1]=78786;

    for( j=0;j<n2;j++)
    {
        R[j]= a[j+q+1];
    }
    R[n2-1]=121465;

    i=0,j=0;
    int k=p ;
    while(i<n1 && j< n2)
    {
        if(L[i]<=R[j])
        {
            a[k]=L[i];
            i++;
        }
        else
        {
            a[k]=R[j];
            j++;

        }
        k++;

    }
    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }

}



void  mergesort(int a[],int p,int r)
{
    if (p<r)
    {
        int q = (p+r-1)/2;
        mergesort(a,p,q);
        mergesort(a,q+1,r);
        merge(a,p,q,r);
    }

}

