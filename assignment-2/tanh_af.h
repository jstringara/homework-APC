//
// Created by Danilo Ardagna on 01/11/23.
//

#ifndef NEURALNETWORKS_TANH_AF_H
#define NEURALNETWORKS_TANH_AF_H
#include "activation_function.h"


// Your code goes here
class tanh_af: public activation_function {
public:
  double eval(const double x) const;
};


#endif //NEURALNETWORKS_TANH_AF_H
