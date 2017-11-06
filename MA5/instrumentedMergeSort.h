/***************************************************************************
 *
 *  Sorting algorithms and counting work - Merge sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented mergesort
 *
 */

#ifndef __INSTRUMENTEDMS_H
#define __INSTRUMENTEDMS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

void instrumentedMergeSort( vector<int> & a, SortStats & stats )
{
    clock_t time_begin = clock();       // Grab presort time

	mergeSort(a, stats, 0, a.size() - 1)
	
	// MA TODO: Implement Merge Sort plus logging compares and moves/swaps


    clock_t time_end = clock();         // Grab time when sort complete
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

void mergeSort( vector<int> & a, SortStats & stats, int lowest, int highest )
{
	if(lowest < highest)
	{
		int i = lowest + (highest - 1)/2;
		mergeSort(a, stats, lowest, i);
		mergeSort(a, stats,  i + 1, highest);
//
		merge(a, stats, lowest, i, highest); 
	}
}

void merge( vector<int> & a, SortStats & stats, int min, int mid,  int max )
{
	int num = mid - min + 1;
	int num2 = max - mid;

	int subArray[num];
	int subArray2[num2];

	for(int i = 0; i < num; i++)
	{
		subArray[i] = a[min + 1];
	}
	for(int k = 0; k < num2; k++)
        {
                subArray[k] = a[mid + 1 + k];
        }
	
	int index = 0;
	int index2 = 0;
	int index3 = min;

	while( index < num && index2 < num2 )
	{
		if ( subArray[index] <= subArray2[index2] )
		{
			a[index3] = subArray[index];
			index++;
		}
		else
		{
			a[index3] = subArray2[index2];
			index2++;
		}
		index3++;
	}
	
	while( index < num )
	{
		a[index3] = subArray[index];
		index++;
		index3++;
	}

	
        while( index2 < num2 )
        {
                a[index3] = subArray2[index2];
                index2++;
                index3++;
        }

}	


#endif
