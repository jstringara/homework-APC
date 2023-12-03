//
// Created by Danilo Ardagna on 01/11/23.
//

#include "nn_model.h"

la::dense_matrix nn_model::predict(const la::dense_matrix &input_vector) const {

    // Your code goes here
    // no need to check dimensions, layer.eval() will return nan
    // copy the input into the future output (synthesized copy constructor)
    la::dense_matrix output_vector = input_vector;
    // iterate over the layers and update the output
    for (const auto& layer : layers)
        output_vector = layer.eval(output_vector);
    return output_vector;
}

void nn_model::add_layer(const layer & l) {

    // Your code goes here
    // if layers is not empty and dimensions don't match
    if (!(layers.empty()) && (layers.back().get_output_size() != l.get_input_size())){
        std::cerr << "New layer dimensions don't match model output dimensions" << std::endl;
        return;
    }
    // either layer is empty or the dimensions match, add new layers to the back
    layers.push_back(l);
}
