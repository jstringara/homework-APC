/*
 * Check sudoku matrix
 */

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const size_t SIZE = 9;

// search key function
int search_key (const unsigned v[], unsigned n_elements, unsigned key);

// basic search and row, col and region checking functions
int basic_search(const unsigned v[], unsigned n_elements);
int check_rows(const unsigned sudoku[][SIZE]);
int check_cols(const unsigned sudoku[][SIZE]);
int check_regions(const unsigned sudoku[][SIZE]);

// Return:
//         1 if sudoku matrix complies to all Sudoku rules
//        -1 if a row violates the game rules
//        -2 if a column violates the game rules
//        -3 if a region violates the game rules
int check_sudoku(const unsigned sudoku[][SIZE]);

// Create a Sudoku matrix by Lewis' Algorithm
// (https://en.wikipedia.org/wiki/Sudoku_solving_algorithms)
void generate_sudoku(unsigned sudoku[][SIZE]);

int main()
{
    // initialize a sudoku matrix
    unsigned sudoku[SIZE][SIZE] = {
            {1,2,3,4,5,6,7,8,9},
            {2,3,4,5,6,7,8,9,1},
            {3,4,5,6,7,8,9,1,2},
            {4,5,6,7,8,9,1,2,3},
            {5,6,7,8,9,1,2,3,4},
            {6,7,8,9,1,2,3,4,5},
            {7,8,9,1,2,3,4,5,6},
            {8,9,1,2,3,4,5,6,7},
            {9,1,2,3,4,5,6,7,8}
    }; // this has invalid regions (should return -3)

    // check
    int res = check_sudoku(sudoku);
    cout << "check_sudoku returns: " <<  res << endl;

    // initialize another sudoku matrix
    unsigned sudoku2[SIZE][SIZE];
    generate_sudoku(sudoku2);
    // this should be valid and return 1

    // check
    res = check_sudoku(sudoku2);
    cout << "check_sudoku returns: " <<  res << endl;

    return 0;
}

// given search_key function
int search_key (const unsigned v[], unsigned n_elements, unsigned key)
{
    unsigned key_found = 0;

    for (size_t i=0; i<n_elements; ++i)
        if (v[i] == key)
            key_found = 1;

    return key_found;
}

int basic_search(const unsigned v[], unsigned n_elements){
    // loop over numbers from 1 to 9
    for (size_t i=1; i<SIZE+1; ++i)
        // if not found return 0
        if (!search_key(v, n_elements, i))
            return 0;
    return 1;
}

// row checking function definition
int check_rows(const unsigned sudoku[][SIZE]){
    // loop over the rows and for each check if every number is found
    // check if all numbers are present in the row, otherwise return 0
    for (size_t i=0; i<SIZE; ++i)
        if (!basic_search(sudoku[i], SIZE))
            return 0;
    // all numbers and rows have been checked, rows are valid
    return 1;
}

int check_cols(const unsigned sudoku[][SIZE]){
    // loop over the columns
    for (size_t i=0; i<SIZE; ++i){
        // create the column as a one-dimensional array
        unsigned col[SIZE];
        for (size_t j=0; j<SIZE; ++j)
            col[j] = sudoku[j][i];
        // check if all numbers are present in the col, otherwise return 0
        if (!basic_search(col, SIZE))
            return 0;
    }
    // all numbers and columns have been checked
    return 1;
}

int check_regions(const unsigned sudoku[][SIZE]){
    // loop over the regions
    for (size_t i=0; i<SIZE; ++i){
        // create the region as a one dimensional array
        unsigned region[SIZE];
        // indexes of square, submatrix start row, submatrix start col
        size_t j = 0, start_row = 3*(i/3), start_col = 3*(i%3);
        for (size_t k=start_row; k<start_row+3; ++k) // loop over submatrix
            for (size_t l=start_col; l<start_col+3; ++l){
                // insert and increase index
                region[j] = sudoku[k][l];
                ++j;
            }
        // check if all numbers are present in the region, otherwise return 0
        if (!basic_search(region, SIZE))
            return 0;
    }
    // all numbers and columns have been checked
    return 1;
}

int check_sudoku(const unsigned sudoku[][SIZE])
{

    // It's a bit unclear what and if the function should return if multiple conditions are met
    // eg. if both rows and cols are not valid, should we return -1 or -2? Here we return -1, since the rows
    // are checked first, cols second and regions third

    if (!check_rows(sudoku)) return -1; // check rows
    if (!check_cols(sudoku)) return -2; // check cols
    if (!check_regions(sudoku)) return -3; // check regions

    return 1; // all conditions met, return 1
}

void generate_sudoku(unsigned sudoku[][SIZE])
{
    int x = 0;
    for (size_t i=1; i<=3; ++i)
    {
        for (size_t j=1; j<=3; ++j)
        {
            for (size_t k=1; k<=SIZE; ++k)
            {
                sudoku[3*(i-1)+j-1][k-1] = (x % SIZE) + 1;
                x++;
            }
            x += 3;
        }
        x++;
    }
}
