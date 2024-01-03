#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <mpi.h>

#include "matrix_split.hpp"
#include "matrix_diff.hpp"
#include "matrix_assemble.hpp"


using dense_matrix = la::dense_matrix;


int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // read the name of the matrix file and the difference direction
  std::string filename = argv[1];
  std::string direction = argv[2];

  // initialize matrix
  dense_matrix A;
  if (rank == 0)
  {
    std::ifstream ifs(filename);
    A.read(ifs);
  }

  // compute diff
  dense_matrix matrix_diff;
  if (direction == "vertical")
  {
    // split matrix
    dense_matrix local_A = la::split_cols(A);
    // compute local diff
    dense_matrix local_diff = la::vertical_diff(local_A);
    // assemble matrix columns
    matrix_diff = la::assemble_cols(local_diff);
  }
  else
  {
    std::cerr << "ERROR: no implementation provided" << std::endl;
  }

  // print
  std::string diff_filename = "diff_f_" + std::to_string(rank) + ".csv";
  std::ofstream ofs1(diff_filename);
  matrix_diff.to_csv(ofs1);

  MPI_Finalize();

  return 0;
}
