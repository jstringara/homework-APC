#include <string>
#include <mpi.h>

#include "dense_matrix.hpp"

namespace la {

dense_matrix assemble_cols(const dense_matrix& local_A);

};
