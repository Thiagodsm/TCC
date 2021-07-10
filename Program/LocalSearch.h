//#pragma once
#ifndef _LOCALSEARCH_H
#define _LOCALSEARCH_H

#include "Data.h"

/************************************************************************************
 Method: LocalSearch
 Description: RVND
*************************************************************************************/
TSol LocalSearch(TSol s, int n, int m, std::vector < std::vector <double> > dist, std::vector <std::vector <int> > constraints_matrix, std::vector <TConstraint> CL);

/************************************************************************************
 Method: LS1
 Description: 2-Opt
*************************************************************************************/
TSol LS1(TSol s, int n, int m, std::vector < std::vector <double> > dist, std::vector <std::vector <int> > constraints_matrix, std::vector <TConstraint> CL);


double rand(double min, double max);
int irand(int min, int max);

#endif