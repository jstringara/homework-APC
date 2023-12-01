//
// Created by Danilo Ardagna on 01/11/23.
//

#include "neuron.h"
#include <cmath>

neuron::neuron(size_t input_size, const ptr_act_function & p_a_f) {
    p_act_func = p_a_f;
    bias = 0;
    weights = la::dense_matrix(input_size,1, 1.0);
}

double neuron::eval(const la::dense_matrix & input_vect) const{

    // Your code goes here
    // check that input size and weights size match
    // due to the constructor w is alway a column vector
    if (input_vect.columns()==1 && input_vect.rows() == weights.rows()) // input is a col
        // sum is input^T * w
        return p_act_func->eval(
            *(input_vect.transposed() * weights).data() + bias
        );
    if (input_vect.rows()==1 && input_vect.columns() == weights.rows()) // input is a row
        // sum is input * w
        return p_act_func->eval(
            *(input_vect.transposed() *weights).data() + bias
        );

    // all else has failed, print error and return NaN
    std::cerr << "Wrong input dimensions" << std::endl;
    return nan("");
}
