#include "matrix_split.hpp"

la::dense_matrix la::split_cols(const la::dense_matrix& A){

    // get the rank and size
    int rank(0), size(0);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // broadcast dimensions of matrix from root
    int m(A.rows()), n(A.columns()/size);
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // create a local transposed matrix to hold scatter data
    la::dense_matrix local_A_t(n,m);

    // create a valid transposed matrix to scatter the data from
    la::dense_matrix A_t(n*size,m);
    if (rank==0)
        A_t = A.transposed();

    // scatter the data from the root
    MPI_Scatter(
        A_t.data(), n*m, MPI_DOUBLE,
        local_A_t.data(), n*m, MPI_DOUBLE,
        0, MPI_COMM_WORLD
    );

    // return transposed local matrix
    return local_A_t.transposed();
}
