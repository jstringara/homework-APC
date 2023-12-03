//
// Created by Danilo Ardagna on 01/11/23.
//

#ifndef NEURALNETWORKS_SIGMOID_H
#define NEURALNETWORKS_SIGMOID_H
#include "activation_function.h"


// Your code goes here
class sigmoid : public activation_function{
    public:
        // override the pure virtual method
        double eval(const double x) const override;
};



#endif //NEURALNETWORKS_SIGMOID_H
