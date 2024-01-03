#include "matrix_diff.hpp"

la::dense_matrix la::vertical_diff(const dense_matrix &A){

    // output matrix has one less row
    la::dense_matrix A_ver(A.rows()-1, A.columns());

    // take the difference between rows
    for (size_t i=0; i<A_ver.rows(); ++i)
        for (size_t j=0; j<A_ver.columns(); ++j)
            A_ver(i,j) = A(i+1,j) - A(i,j);

    return A_ver;
}
