/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if(n>=0)
    {
        int first = 0,last = n-1,mid;
        mid= (first+last)/2;
        while(first<=last)
        {
            if(values[mid]==value)
            {
                return true;
                break;
            }
            else if(values[mid]>value)
            last = mid-1;
            else
            first = mid+1;
            
            mid = (first +last)/2;
        }
        return false;
        
    }
 
    else
    return false;
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int sc=-1, temp;
    while(sc!=0)
    {
        sc= 0;
        for(int i =0 ;i<n-1;i++)
        {
            if(values[i]>values[i+1])
            {
                temp = values[i];
                values[i]=values[i+1];
                values[i+1]=temp;
                sc++;
                
            }
        }
    }
     return ;
}
