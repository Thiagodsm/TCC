//#pragma once
#ifndef _READ_H
#define _READ_H

#include "Data.h"

#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
// para o TCC
#include <fstream>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <sstream>


void ReadData(char nameTable[], char constraints[], std::vector <std::vector <double> >& dist, std::vector <std::vector <int> >& constraints_matrix, std::vector <TConstraint>& CL, std::vector <TConstraint>& ML);

void FreeMemoryProblem(std::vector <TNode> node, std::vector <std::vector <double> > dist);

#endif