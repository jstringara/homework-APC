#include "matrix_assemble.hpp"
#include <mpi.h>

la::dense_matrix la::assemble_cols(const la::dense_matrix& local_A){

    // get the size
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // get size of local matrix
    int local_m=local_A.rows(), local_n=local_A.columns();

    // transposed matric to hold gathered data
    la::dense_matrix A_t(local_n * size, local_m);

    MPI_Allgather(
        local_A.transposed().data(), local_m * local_n, MPI_DOUBLE,
        A_t.data(), local_m * local_n, MPI_DOUBLE,
        MPI_COMM_WORLD
    );

    return A_t.transposed();
}
