//
// Created by Danilo Ardagna on 01/11/23.
//

#include "nn_model.h"

la::dense_matrix nn_model::predict(const la::dense_matrix &input_vector) const {

    // Your code goes here
    // initialize the output_vector to be the input_vector
    la::dense_matrix output_vect(input_vector);
    for (const auto& layer: layers){
        // evaluate the layer
        output_vect = layer.eval(output_vect);
    }
    return output_vect;
}

void nn_model::add_layer(const layer & l) {

    // Your code goes here
    // layers is not empty and the dimensions are mismatched
    if (!layers.empty() &&
        layers.back().get_output_size()!=l.get_input_size()
    ){
        std::cerr <<
            "New layer input dimensions don't match model output dimensions"
            << std::endl;
        return;
    }

    layers.push_back(l);
}
