#include "matrix_assemble.hpp"

la::dense_matrix la::assemble_cols(const dense_matrix &local_A){

    // get the size
    int size(0);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // get local matrix dimensions
    int local_m(local_A.rows()), local_n(local_A.columns());

    // transposed matrix to hold the gathered data
    la::dense_matrix A_t(local_n*size, local_m);

    // transpose local_A to use in gather
    la::dense_matrix local_A_t = local_A.transposed();

    MPI_Allgather(
        local_A_t.data(), local_m*local_n, MPI_DOUBLE,
        A_t.data(), local_m*local_n, MPI_DOUBLE,
        MPI_COMM_WORLD
    );

    // transpose the gathered matrix and return
    return A_t.transposed();
}
