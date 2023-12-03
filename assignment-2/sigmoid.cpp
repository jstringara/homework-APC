//
// Created by Danilo Ardagna on 01/11/23.
//

#include "sigmoid.h"

// Your code goes here
double sigmoid::eval(const double x) const {
    // sigmoid function e^x/(1+e^x) = 1/(1+e^-x)
    return 1 / (1 + std::exp(-x));
}