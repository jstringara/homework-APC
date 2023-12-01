//
// Created by Danilo Ardagna on 01/11/23.
//

#include "sigmoid.h"

// Your code goes here
double sigmoid::eval(const double x) const{
  return 1/(1+std::exp(-x));
}
