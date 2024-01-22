#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip> // For beautiful display
#include <cmath>

using Matrix = std::vector<std::vector<double>>;


namespace algebra {
    /**
     * 1. zeros implement this function so that it will create a n x m matrix with all elements equal to zero.
    */
    Matrix zeros(size_t n, size_t m);

    /**
     * 2. ones implement this function so that it will create a n x m matrix with all elements equal to one.
    */
    Matrix ones(size_t n, size_t m);


    /**
     * 3. random implement this function so that it will create a n x m matrix with all elements a random number between min and max.
    */
    Matrix random(size_t n, size_t m, double min, double max);


    /**
     * 4. show implement this function so that it will display the matrix in a beautiful way.
    */
    void show(const Matrix& matrix);


    /**
     * 5. implement this function so that it multiplies the matrix into the constant scalar c.
    */
    Matrix multiply(const Matrix& matrix, double c);

    /**
     * 6. implement this function so that it multiplies the matrix1 into matrix2. (this is not an element-wise multiplication)
    */
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);

    /**
     * 7. implement this function so that it adds the constant number c to every element of matrix.
    */
    Matrix sum(const Matrix& matrix, double c);

    /**
     * 8. implement this function so that it adds 2 matrices to each other.
    */
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2);


    /**
     * 9. implement this function so that it will generate the transpose matrix of the input matrix.
    */
    Matrix transpose(const Matrix& matrix);

    /**
     * 10. implement this function so that it will create the minor of the input matrix with respect to nth row and mth column.
    */
    Matrix minor(const Matrix& matrix, size_t n, size_t m);

    /**
     * 11. implement this function so that it calculates the determinant of the input matrix.
    */
    double determinant(const Matrix& matrix);

    /**
     * 12. implement this function so that it generates the matrix's inverse.
    */
    Matrix inverse(const Matrix& matrix);
    
    /**
     * 13. concatenate implement this function so that it will concatenate matrix1 and matrix2 along the specified axis. (axis=0: on top of each other | axis=1: alongside each other).
     */
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis=0);


    /**
     * 14. swaps r1-th row with r2-th row.
     */
    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);


    /**
     * 15. multiplies every element in r-th row with constant number c.
    */
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c);

    /**
     * 15. adds r1-th row * c into r2-th row.
    */
    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2);

    /**
     * 16. 
    */
    Matrix upper_triangular(const Matrix& matrix);



    /**
     * Helper functions
    */

    std::pair<int, int> shape(const Matrix& matrix);
    
    int rowSize(const Matrix& matrix);

    int columnSize(const Matrix& matrix);

    bool isEmpty(const Matrix& matrix);

    bool isSquare(const Matrix& matrix);

}



#endif //AP_HW1_H
