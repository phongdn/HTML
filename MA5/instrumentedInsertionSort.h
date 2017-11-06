/***************************************************************************
 *
 *  Sorting algorithms and counting work - Insertion sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented insertionsort
 *
 */

#ifndef __INSTRUMENTEDIS_H
#define __INSTRUMENTEDIS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

void instrumentedInsertionSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();           // Grab starting time before sort
	int k = 0, temp = 0;;
	for(int i = 1; i < a.size(); i++)
	{
		temp = a[i];
		k = i - 1;
		while(++stats.compares && k >= 0 && a[k] > temp)
		{
			stats.moves++;
			a[k+1] = a[k];
			k -= 1;
		}
		a[k+1] = temp;
		//if(++stats.compares && a[i-1] >  a[i])
		//{
		//	for(int k = i-1; k >= 0; k--)
		//	{
		//		if(++stats.compares && a[k] < a[i]) 
		//		{
		//			stats.moves++;
		//			temp = a[k+1];
		//			a[k+1] = a[i];
		//			a[i] = temp;
		//			//a[k+1] += a[i];
		//			//a[i] = a[k+1] - a[i];
		//			//a[k+1] -= a[i];
		//			break;
		//		}
		//	}
		//}
	}
	// MA TODO: implement insertion sort plus logging compares, moves/swaps


	clock_t time_end = clock();             // Grab ending time after sort
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}

#endif
