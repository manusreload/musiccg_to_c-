/* 
 * File:   ArrayRankDouble.h
 * Author: antwalls
 *
 * Created on 17 de marzo de 2015, 18:38
 */

#ifndef ARRAYRANKDOUBLE_H
#define	ARRAYRANKDOUBLE_H

#include <vector>
#include "auxiliar.h"
using namespace std;

class ArrayRankDouble 
{
public:
    ArrayRankDouble();
    
        
/**
 * Get the index position of maximum value the given array 
 * @param array
 * @return	index of the max value in array
 */
int getMaxValueIndex(vector<double>  array);

/**
 * Get the index position of minimum value in the given array 
 * @param array
 * @return	index of the min value in array
 */
int getMinValueIndex(vector<double>  array) ;

/**
 * Get the n-th value in the array after sorted
 * @param array
 * @param n
 * @param ascending	is ascending order or not
 * @return
 */
double getNthOrderedValue(vector<double>  array, int n, bool ascending) ;

double getOrderedValue(vector<double>  array, int index); 

// sort the partitions by quick sort, and locate the target index
void locate(vector<double>  array, int left, int right, int index) ;

 void swap(vector<double>  array, int i, int j) ;
    
    ArrayRankDouble(const ArrayRankDouble& orig);
    virtual ~ArrayRankDouble();


};

#endif	/* ARRAYRANKDOUBLE_H */

