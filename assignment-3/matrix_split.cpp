#include "matrix_split.hpp"
#include <string>

la::dense_matrix la::split_cols(const la::dense_matrix& A){

    // how many processors
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // original matrix is only on processor 0
    // these are 0 for all other processors
    int m = A.rows(), n = A.columns()/size;

    // broadcast m and n to all processors
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // create local matrix to hold scattered values
    la::dense_matrix local_A_t(n, m);

    // prepare the data to be sent
    la::dense_matrix A_t;
    if (rank==0)
        A_t = A.transposed();

    // scatter the transposed matrix (nothing for rank!=0)
    MPI_Scatter(
        A_t.data(), n*m, MPI_DOUBLE,
        local_A_t.data(), n*m, MPI_DOUBLE,
        0, MPI_COMM_WORLD
    );

    return local_A_t.transposed();
}
