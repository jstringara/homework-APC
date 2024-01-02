#include "matrix_diff.hpp"

la::dense_matrix la::vertical_diff(const la::dense_matrix& A){

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // empty matrix
    la::dense_matrix A_ver(A.rows()-1, A.columns());

    for (size_t i=0; i<A_ver.rows(); ++i)
         for (size_t j=0; j<A.columns(); ++j)
            A_ver(i,j) = A(i+1,j) - A(i,j);
        
    return A_ver;
}
