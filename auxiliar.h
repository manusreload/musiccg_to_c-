/* 
 * File:   auxiliar.h
 * Author: antwalls
 *
 * Created on 17 de marzo de 2015, 11:57
 */

#ifndef AUXILIAR_H
#define	AUXILIAR_H

#define PI 3.14159265358979323846;
typedef unsigned char byte;
#include <string>
using namespace std;

double DOUBLE_MIN_VALUE         = numeric_limits<double>::min();
double DOUBLE_MAX_VALUE         = numeric_limits<double>::max();
double INT_MIN_VALUE            = numeric_limits<int>::min();
double INT_MAX_VALUE            = numeric_limits<int>::max();
string toUpperCase(const string& _cadena);


#endif	/* AUXILIAR_H */

