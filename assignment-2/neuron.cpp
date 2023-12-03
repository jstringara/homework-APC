//
// Created by Danilo Ardagna on 01/11/23.
//

#include "neuron.h"

neuron::neuron(size_t input_size, const ptr_act_function & p_a_f) {
    p_act_func = p_a_f;
    bias = 0;
    weights = la::dense_matrix(input_size,1, 1.0);
}

double neuron::eval(const la::dense_matrix & input_vect) const{

    // Your code goes here
    // weights vector is a col vector by definition of constructor

    if (input_vect.columns()==1 && input_vect.rows() == weights.rows()) // input is a col -> transpose
        // we can access directly the data since it is only one number, equivalent to doing sum(0,0)
        return p_act_func->eval(
            *(input_vect.transposed() * weights).data() + bias
        );
    // all else has failed, wrong dimensions, error and return NaN
    std::cerr <<  "Wrong Input dimensions" << std::endl;
    return std::nan("");
}
