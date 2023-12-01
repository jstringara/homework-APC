//
// Created by Danilo Ardagna on 01/11/23.
//

#ifndef NEURALNETWORKS_ACTIVATION_FUNCTION_H
#define NEURALNETWORKS_ACTIVATION_FUNCTION_H
#include <cmath>

// Your code goes here
class activation_function {
  public:
    virtual double eval(const double x) const = 0;
};

#endif //NEURALNETWORKS_ACTIVATION_FUNCTION_H
