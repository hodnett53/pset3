/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <math.h>  //added! check if needed to alter Makefile
#include "helpers.h"

/**
 * Swaps any two items in an array
 */
void swap(int values[], int n, int m)
{
    // check for same input values
    if (n == m || values[n] == values[m])
    {
       return;
    }
    
    // set the placeholder
    int placeholder = values[n];
    
    // swap the array items
    values[n] = values[m];
    values[m] = placeholder;
    
    return;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // (needle, haystack, size)
    
    while (n > 0)
    {
        // get midpoint
        int half = round(n / 2);
        int midpoint = values[half];
    
        if (midpoint == value)
        {
            return true;
        }
        
        else if (midpoint < value)
        {
            int newSize = n - half;
            int newValues[newSize];
            
            for (int i = 0; i < newSize; i++)
                {
                    newValues[i] = values[half + i];
                }
                
            search(value, newValues, newSize);
        }
        
        else if(midpoint > value)
        {
            int newSize = n - half - 1;
            int newValues[newSize];
            
            for (int i = 0; i < newSize; i++)
            {
                newValues[i] = values[i];
            }
            
            search(value, newValues, newSize);
        }
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    if (n == 1)
    {
        return;
    }
    
    for (int i = 0; i < (n - 1); i++)
    {
        if (values[i] > values[i + 1])
        {
            swap(values, i, i + 1);
        }
    }
    
    int newSize = n - 1;
    
    sort(values, newSize);
}
