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
void swap(int values[], int n)
{
    int m = n + 1;
    
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
    // set values for upper and lower
    int low = 0;
    int high = n - 1;
    
    //loop through
    while (low <= high)
    {
        int middle = (low + high) / 2;
        
        if (values[middle] == value)
            return true;
        else if (values[middle] < value)
            low = middle + 1;
        else if (values[middle] > value)
            high = middle - 1;
    }
    return false;
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // bubble sort
    
    //return if sorted
    if (n == 1)
        return;
    //swap highest value all the way right
    for (int i = 0; i < (n - 1); i++)
    {
        if (values[i] > values[i + 1])
            swap(values, i);
    }
    // change size to account for what is sorted
    int newSize = n - 1;
    // make recursive
    sort(values, newSize);
}
