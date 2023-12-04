//
// Created by Danilo Ardagna on 01/11/23.
//

#include "layer.h"

layer::layer(size_t input_size, size_t output_size, const ptr_act_function &p_a_f) {
    // Your code goes here
    this->input_size = input_size;
    this->output_size = output_size;
    // create #output_size neuron with input_size
    this->neurons = std::vector<neuron> (output_size, neuron(input_size, p_a_f));
}

la::dense_matrix layer::eval(const la::dense_matrix & input_vector) const{
    // Your code goes here
    // no need to check dimensions, neuron.eval() will return nan
    la::dense_matrix output_vector(output_size, 1); // empty output vector
    // iterate over the neurons in the layer and evaluate
    for (size_t i=0; i<output_size; ++i)
         output_vector(i,0) = neurons[i].eval(input_vector);

    return output_vector;

}

size_t layer::get_input_size() const {
    // Your code goes here
    return input_size;
}

size_t layer::get_output_size() const {
    // Your code goes here
    return output_size;
}
