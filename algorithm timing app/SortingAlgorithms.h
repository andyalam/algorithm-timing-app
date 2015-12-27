/*

Currently contains:
    - merge sort
    - quick sort
    - insertion sort
    - shell sort

*/
#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


template <typename Comparable>
void insertionSort(vector<Comparable> &a)
{
    int k, pos, arraySize;
    Comparable tmp;

    arraySize = a.size();
    for (pos = 1; pos < arraySize; pos++)
    {
        tmp = a[pos];
        for (k = pos; k > 0 && tmp < a[k - 1]; k--)
            a[k] = a[k - 1];
        a[k] = tmp;
    }
}


//used for quicksort
template <typename Comparable>
void insertionSort(vector<Comparable> & a, int left, int right)
{
    int k, pos;
    Comparable tmp;

    for (pos = left + 1; pos <= right; pos++)
    {
        tmp = a[pos];
        for (k = pos; k > left && tmp < a[k - 1]; k--)
            a[k] = a[k - 1];
        a[k] = tmp;
    }
}


template <typename Comparable>
void shellSort(vector<Comparable> & a)
{
    int k, pos, arraySize, gap;
    Comparable tmp;

    arraySize = a.size();
    for (gap = arraySize / 2; gap > 0; gap /= 2)  // outer gap loop
        for (pos = gap; pos < arraySize; pos++)   // middle loop (outer of "insertion-sort")
        {
            tmp = a[pos];
            for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap)   // inner loop
                a[k] = a[k - gap];
            a[k] = tmp;
        }
}


//NOTE: Messy codegolf(ranked via semicolons) implementation of mergesort, 
//      I do not code like this, this was a bet...
//      Managed 3 semicolons total.
template <typename Comparable>
void merge(vector<Comparable> &vec,
    vector<Comparable> &left, vector<Comparable> &right,
    int leftIndex = 0, int rightIndex = 0)
{
    while (leftIndex < left.size() || rightIndex < right.size())
        (leftIndex < left.size() && rightIndex < right.size()) ?
        (left.at(leftIndex) <= right.at(rightIndex)) ?
        vec.push_back(left.at(leftIndex++)) : vec.push_back(right.at(rightIndex++))
        : (rightIndex < right.size()) ?
        vec.push_back(right.at(rightIndex++)) : vec.push_back(left.at(leftIndex++));
}

template <typename Comparable>
void mergesort(vector<Comparable> &vec) {
    if (vec.size() > 1)
    {
        vector<Comparable> left(vec.begin(), vec.begin() + vec.size() / 2),
            right(vec.begin() + vec.size() / 2, vec.end());
        mergesort(left), mergesort(right), merge(vec = vector<Comparable>(0), left, right);
    }
}



// quickSort helper
// median3 sorts a[left], a[center] and a[right].
// it leaves the smallest in a[left], the largest in a[right]
// and median (the pivot) is moved "out-of-the-way" in a[right-1].
// (a[center] has what used to be in a[right-1])
template <typename Comparable>
const Comparable & median3(vector<Comparable> & a, int left, int right)
{
    int center;

    center = (left + right) / 2;
    if (a[center] < a[left])
        swap(a[left], a[center]);
    if (a[right] < a[left])
        swap(a[left], a[right]);
    if (a[right] < a[center])
        swap(a[center], a[right]);

    swap(a[center], a[right - 1]);
    return a[right - 1];
}

#define QS_RECURSION_LIMIT 15

// quickSort internal
template <typename Comparable>
void quickSort(vector<Comparable> & a, int left, int right)
{
    Comparable pivot;
    int i, j;

    if (left + QS_RECURSION_LIMIT <= right)
    {
        pivot = median3(a, left, right);
        for (i = left, j = right - 1; ; )
        {
            while (a[++i] < pivot)
                ;
            while (pivot < a[--j])
                ;
            if (i < j)
                swap(a[i], a[j]);
            else
                break;
        }

        swap(a[i], a[right - 1]);  // restore pivot

                                       // recursive calls on smaller sub-groups
        quickSort(a, left, i - 1);
        quickSort(a, i + 1, right);
    }
    else
        // non-recursive escape valve - insertionSort
        insertionSort(a, left, right);
}

// quickSort public driver
template <typename Comparable>
void quickSort(vector<Comparable> & a)
{
    quickSort(a, 0, a.size() - 1);
}
