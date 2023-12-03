//
// Created by Danilo Ardagna on 01/11/23.
//

#ifndef NEURALNETWORKS_RE_LU_H
#define NEURALNETWORKS_RE_LU_H
#include "activation_function.h"



// Your code goes here
class re_lu : public activation_function{
    public:
        // override the pure virtual method
        double eval(const double x) const override;
};

#endif //NEURALNETWORKS_RE_LU_H
