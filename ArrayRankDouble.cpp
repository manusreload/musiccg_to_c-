/* 
 * File:   ArrayRankDouble.cpp
 * Author: antwalls
 * 
 * Created on 17 de marzo de 2015, 18:38
 */

#include "ArrayRankDouble.h"

ArrayRankDouble::ArrayRankDouble() {
}
    
/**
 * Get the index position of maximum value the given array 
 * @param array
 * @return	index of the max value in array
 */
int ArrayRankDouble::getMaxValueIndex(vector<double>  array) 
{

        int index = 0;
        double max = INT_MIN_VALUE;

        for (int i = 0; i < array.size(); i++) 
        {
                if (array[i] > max) 
                {
                        max = array[i];
                        index = i;
                }
        }

        return index;
}

/**
 * Get the index position of minimum value in the given array 
 * @param array
 * @return	index of the min value in array
 */
int ArrayRankDouble::getMinValueIndex(vector<double>  array) {

        int index = 0;
        double min = INT_MAX_VALUE;

        for (int i = 0; i < array.size(); i++) 
        {
                if (array[i] < min) {
                        min = array[i];
                        index = i;
                }
        }

        return index;
}

/**
 * Get the n-th value in the array after sorted
 * @param array
 * @param n
 * @param ascending	is ascending order or not
 * @return
 */
double ArrayRankDouble::getNthOrderedValue(vector<double>  array, int n, bool ascending) {

        if (n > array.size()) 
        {
                n = array.size();
        }

        int targetindex;
        if (ascending) 
        {
                targetindex = n;
        } else 
        {
                targetindex = array.size() - n;
        }

        // this value is the value of the numKey-th element
        double passValue = getOrderedValue(array, targetindex);

        return passValue;
}

double ArrayRankDouble::getOrderedValue(vector<double>  array, int index) 
{
        locate(array, 0, array.size() - 1, index);
        return array[index];
}

// sort the partitions by quick sort, and locate the target index
void ArrayRankDouble::locate(vector<double>  array, int left, int right, int index) {

        int mid = (left + right) / 2;
        // System.out.println(left+" to "+right+" ("+mid+")");

        if (right == left) {
                // System.out.println("* "+array[targetIndex]);
                // result=array[targetIndex];
                return;
        }

        if (left < right) {
                double s = array[mid];
                int i = left - 1;
                int j = right + 1;

                while (true) {
                        while (array[++i] < s)
                                ;
                        while (array[--j] > s)
                                ;
                        if (i >= j)
                                break;
                        swap(array, i, j);
                }

                // System.out.println("2 parts: "+left+"-"+(i-1)+" and "+(j+1)+"-"+right);

                if (i > index) {
                        // the target index in the left partition
                        // System.out.println("left partition");
                        locate(array, left, i - 1, index);
                } else {
                        // the target index in the right partition
                        // System.out.println("right partition");
                        locate(array, j + 1, right, index);
                }
        }
}

 void ArrayRankDouble::swap(vector<double>  array, int i, int j) {
        double t = array[i];
        array[i] = array[j];
        array[j] = t;
}


ArrayRankDouble::ArrayRankDouble(const ArrayRankDouble& orig) {
}

ArrayRankDouble::~ArrayRankDouble() {
}

