//
// Created by Danilo Ardagna on 01/11/23.
//

#ifndef NEURALNETWORKS_NN_MODEL_H
#define NEURALNETWORKS_NN_MODEL_H

#include "layer.h"
#include "activation_function.h"
#include "utils.h"
#include "dense_matrix.hpp"

class nn_model {

private:
    // Your code goes here
public:
    la::dense_matrix predict(const la::dense_matrix & input_vector) const;
    void add_layer(const layer & l);

};


#endif //NEURALNETWORKS_NN_MODEL_H
