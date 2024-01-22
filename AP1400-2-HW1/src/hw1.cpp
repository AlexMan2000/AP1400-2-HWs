#include "hw1.h"

namespace algebra {

    Matrix zeros(size_t n, size_t m) {
        int initialValue = 0;
        Matrix result(n, std::vector<double>(m, initialValue));
        return std::move(result); // For efficiency
    }

    Matrix ones(size_t n, size_t m) {
        int initialValue = 1;
        Matrix result(n, std::vector<double>(m, initialValue));
        return std::move(result); // For efficiency
    }

    Matrix random(size_t n, size_t m, double min, double max) {

        // Should throw an logic error here if min > max
        if (min > max) {
            throw std::logic_error("Range specified by [min,max] invalid, expecting min <= max");
        }

        int initialValue = 0;
        Matrix result(n, std::vector<double>(m, initialValue));
        for (auto& vector: result) {
            for (auto iter = vector.begin(); iter!=vector.end(); iter++) {
                std::random_device rd; // Seed with a real random value, if available
                std::mt19937 engine(rd()); // Standard mersenne_twister_engine seeded with rd()
                std::uniform_real_distribution<double> dist(min, max); // Distribution in range [0.0, 1.0]

                double random_double = dist(engine);
                *iter = random_double;
            }
        }
        return std::move(result);
    }


    void show(const Matrix& matrix) {
        for (auto& vector: matrix) {
            for (auto& elem: vector) {
                std::cout << std::setw(8) << std::setprecision(3) << elem;
            }
            std::cout << std::endl;
        }
    }


    Matrix multiply(const Matrix& matrix, double c) {
        if (isEmpty(matrix)) {
            return std::move(Matrix{});
        }

        auto shape_ = shape(matrix);
        int rowSize_ = shape_.first;
        int columnSize_ = shape_.second;

        Matrix result = zeros(rowSize_, columnSize_);
        
        for (int i = 0; i < rowSize_; i++) {
            for (int j = 0; j < columnSize_; j++) {
                result[i][j] = c * matrix[i][j];
            }
        }

        return std::move(result);
    }


    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
        auto shape1 = shape(matrix1);
        int rowSize1 = shape1.first;
        int columnSize1 = shape1.second;
        
        auto shape2 = shape(matrix2);
        int rowSize2 = shape2.first;
        int columnSize2 = shape2.second;

        // First check for shape compatibility
        if (columnSize1 != rowSize2) {
            // Don't ever forget the throw keyword
            throw std::logic_error("Matrix shape doesn't match");
        }

        // Next check emptiness
        if (isEmpty(matrix1) || isEmpty(matrix2)) {
            return std::move(Matrix{});
        }

        Matrix result = zeros(rowSize1, columnSize2);
        for (int i = 0; i < rowSize1; i++) {
            for (int j = 0; j < columnSize2; j++) {
                for (int k = 0; k < columnSize1; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }

        return std::move(result);
    }


    Matrix sum(const Matrix& matrix, double c) {
        if (isEmpty(matrix)) {
            return std::move(Matrix{});
        }

        auto shape_ = shape(matrix);
        int rowSize_ = shape_.first;
        int columnSize_ = shape_.second;

        Matrix result = zeros(rowSize_, columnSize_);
        
        for (int i = 0; i < rowSize_; i++) {
            for (int j = 0; j < columnSize_; j++) {
                result[i][j] = c + matrix[i][j];
            }
        }

        return std::move(result);
    }


    Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
        auto shape1 = shape(matrix1);
        int rowSize1 = shape1.first;
        int columnSize1 = shape1.second;
        
        auto shape2 = shape(matrix2);
        int rowSize2 = shape2.first;
        int columnSize2 = shape2.second;

        // First check for shape compatibility
        if (!(rowSize1 == rowSize2 && columnSize1 == columnSize2)) {
            // Don't ever forget the throw keyword
            throw std::logic_error("Matrix shape doesn't match");
        }

        // Next check emptiness
        if (isEmpty(matrix1) || isEmpty(matrix2)) {
            return std::move(Matrix{});
        }

        Matrix result = zeros(rowSize1, columnSize2);
        for (int i = 0; i < rowSize1; i++) {
            for (int j = 0; j < columnSize2; j++) {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }

        return std::move(result);
    }

    Matrix transpose(const Matrix& matrix) {
        if (isEmpty(matrix)) {
            return std::move(Matrix{});
        }

        auto shape_ = shape(matrix);
        int rowSize_ = shape_.first;
        int columnSize_ = shape_.second;

        Matrix result = zeros(columnSize_, rowSize_);
        
        for (int i = 0; i < rowSize_; i++) {
            for (int j = 0; j < columnSize_; j++) {
                result[j][i] = matrix[i][j];
            }
        }

        return std::move(result);
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m) {
        if (isEmpty(matrix)) {
            return std::move(Matrix{});
        }

        auto shape_ = shape(matrix);
        int rowSize_ = shape_.first;
        int columnSize_ = shape_.second;

        if (n >= rowSize_ || m >= columnSize_) {
            throw std::logic_error("Invalid arguments!");
        }

        if (rowSize_ - 1 == 0 || columnSize_ - 1 == 0) {
            return std::move(Matrix{});
        }

        Matrix result = zeros(rowSize_ - 1, columnSize_ - 1);

        bool rowFlag = false;
        bool columnFlag = false;
        for (int i = 0; i < rowSize_; i++) {
            if (i == n) {
                rowFlag = true;
                continue; 
            }
            for (int j = 0; j < columnSize_; j++) {
                if (j == m) {
                    columnFlag = true;
                    continue;
                }
                if (rowFlag && !columnFlag) {
                    result[i - 1][j] = matrix[i][j];
                } else if (columnFlag && !rowFlag) {
                    result[i][j - 1] = matrix[i][j];
                } else if (rowFlag && columnFlag) {
                    result[i - 1][j - 1] = matrix[i][j];
                } else {
                    result[i][j] = matrix[i][j];
                }
            }
            columnFlag = false;
        }
        return std::move(result);
    }

    double determinant(const Matrix& matrix) {
        // Using Laplacian Expansion

        // Edge cases
        // 1. If the matrix is not square, throw logic error, determinant not exist
        if (!isSquare(matrix)) {
            throw std::logic_error("Determinant doesn't exist for non-square matrices!");
        }

        // 2. If the matrix is empty, return 0, recursive termination
         if (isEmpty(matrix)) {
            return 1;
        }

        auto shape_ = shape(matrix);
        int rowSize_ = shape_.first;
        int columnSize_ = shape_.second;
        double result = 0;

        // Expand from first row
        for (int i = 0; i < columnSize_; i++) {
            Matrix minor_ = minor(matrix, 0, i);
            result += (determinant(minor_) * pow(-1, i) * matrix[0][i]);
        }

        return result;
    }

    Matrix inverse(const Matrix& matrix) {
        // Using adjoint matrix

        // Edge cases
        // 1. If the matrix is not square, throw logic error, inverse doesn't exist
        if (!isSquare(matrix)) {
            throw std::logic_error("Determinant doesn't exist for non-square matrices!");
        }

        // 2. If the matrix is not invertible(determinant is zero), then throw logic error
        if (determinant(matrix) == 0) {
            throw std::logic_error("Inverse doesn't exist, non-singular matrix");
        }

        // Computing Algorithm
        // 1. Compute the cofactor matrix
        auto shape_ = shape(matrix);
        int rowSize_ = shape_.first;
        int columnSize_ = shape_.second;
        Matrix cofactor = zeros(rowSize_, columnSize_);
        for (int i = 0; i < rowSize_; i++) {
            for (int j = 0; j < columnSize_; j++) {
                cofactor[i][j] = pow(-1, i + j) * determinant(minor(matrix, i, j));
            }
        }
        // 2. Compute adjoint matrix
        Matrix adjoint = transpose(cofactor);

        // 3. Compute determinant of original matrix
        double det = determinant(matrix);

        // 4. Compute the inverse of original matrix
        Matrix inverse = multiply(adjoint, 1 / det);

        return inverse;
    }

    /**
     * concatenate implement this function so that it will concatenate matrix1 and matrix2 along the specified axis. (axis=0: on top of each other | axis=1: alongside each other).
     * Note that in the function implementation, default parameter should not be set
     * Default parameter only appears in the header file, otherwise it won't compile.
    */
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
        
        if (isEmpty(matrix1)) {
            return std::move(matrix2);
        } 

        if (isEmpty(matrix2)) {
            return std::move(matrix2);
        } 

        if (isEmpty(matrix1) && isEmpty(matrix2)) {
            return std::move(Matrix{});
        } 
        
        auto shape1 = shape(matrix1);
        int rowSize1 = shape1.first;
        int columnSize1 = shape1.second;
        
        auto shape2 = shape(matrix2);
        int rowSize2 = shape2.first;
        int columnSize2 = shape2.second;

        if (axis == 0) {
            if (columnSize1 != columnSize2) {
                throw std::logic_error("Column size mismatches, columnSize1 should be the same as columnSize2, cannot stack along row direction!");
            }

            Matrix result = zeros(rowSize1 + rowSize2, columnSize1);

            for (int i = 0; i < rowSize1; i++) {
                for (int j = 0; j < columnSize1; j++) {
                    result[i][j] = matrix1[i][j];
                }
            }

            for (int i = rowSize1; i < rowSize1 + rowSize2; i++) {
                for (int j = 0; j < columnSize1; j++) {
                    result[i][j] = matrix2[i - rowSize1][j];
                }
            }

            return std::move(result);

        } else if (axis == 1) {
            if (rowSize1 != rowSize2) {
                throw std::logic_error("Row size mismatches, rowSize1 should be the same as rowSize2, cannot stack along row direction!");
            }

            Matrix result = zeros(rowSize1, columnSize1 + columnSize2);

            for (int i = 0; i < rowSize1; i++) {
                for (int j = 0; j < columnSize1; j++) {
                    result[i][j] = matrix1[i][j];
                }
            }

            for (int i = 0; i < rowSize1; i++) {
                for (int j = columnSize1; j < columnSize1 + columnSize2; j++) {
                    result[i][j] = matrix2[i][j - columnSize1];
                }
            }

            return std::move(result);

        } else {
            throw std::logic_error("Invalid axis number, expecting one of 0 or 1.");
        }
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2) {

        if (isEmpty(matrix)) {
            return std::move(Matrix{});
        }


        auto shape_ = shape(matrix);
        int rowSize_ = shape_.first;
        int columnSize_ = shape_.second;


        if (r1 >= rowSize_ || r2 >= rowSize_) {
            throw std::logic_error("Invalid arguments!");
        }

        Matrix result = matrix;
        for (int j = 0; j < columnSize_; j++) {
            result[r1][j] = matrix[r2][j];
            result[r2][j] = matrix[r1][j];
        }

        return std::move(result);
    }

    Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
        if (isEmpty(matrix)) {
            return std::move(Matrix{});
        }


        auto shape_ = shape(matrix);
        int rowSize_ = shape_.first;
        int columnSize_ = shape_.second;


        if (r >= rowSize_) {
            throw std::logic_error("Invalid arguments!");
        }

        Matrix result = matrix;
        for (int j = 0; j < columnSize_; j++) {
            result[r][j] = matrix[r][j] * c;
        }

        return std::move(result);
    }

    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
        if (isEmpty(matrix)) {
            return std::move(Matrix{});
        }

        auto shape_ = shape(matrix);
        int rowSize_ = shape_.first;
        int columnSize_ = shape_.second;


        if (r1 >= rowSize_ || r2 >= rowSize_) {
            throw std::logic_error("Invalid arguments!");
        }

        Matrix result = matrix;
        for (int j = 0; j < columnSize_; j++) {
            result[r2][j] = matrix[r2][j] + matrix[r1][j] * c;
        }

        return std::move(result);
    }

    Matrix upper_triangular(const Matrix& matrix) {
        if (isEmpty(matrix)) {
            return std::move(Matrix{});
        }

        if (!isSquare(matrix)) {
            throw std::logic_error("Matrix should be square!");
        }

        auto shape_ = shape(matrix);
        int rowSize_ = shape_.first;
        int columnSize_ = shape_.second;

        int rowIndex = 0;
        int columnIndex = 0;

        Matrix result = matrix;
        while (rowIndex < rowSize_ && columnIndex < columnSize_) {
            if (result[rowIndex][columnIndex] == 0) {
                // Look through the row below to find the non zero and swap it up
                int probe = rowIndex + 1;
                while (probe < rowSize_) {
                    if (result[probe][columnIndex] != 0) {
                        // Find one, swap it up
                        result = ero_swap(result, probe, rowIndex);
                        break;
                    }
                    probe++;
                }
            }
            // Zero out the rows below
            for (int i = rowIndex + 1; i < rowSize_; i++) {
                result = ero_sum(result, rowIndex, 
                -1 * result[i][columnIndex] / result[rowIndex][columnIndex], i);
            } 

            // Move onto the next pivotal element
            rowIndex++;
            columnIndex++;
        }
        return std::move(result);
    }

    

   /**
     * Helper functions
    */

    std::pair<int, int> shape(const Matrix& matrix) {
        int rowSize_ = matrix.size();
        
        if (isEmpty(matrix)) {
            return {0, 0};
        }

        std::vector<double> row = matrix[0];
        int columnSize_ = row.size();
        return {rowSize_, columnSize_};
    }

    
    
    int rowSize(const Matrix& matrix) {
        auto temp = shape(matrix);
        return temp.first; // auto [first, second] = shape(matrix) only supported in c++17
    }

    int columnSize(const Matrix& matrix) {
        auto temp = shape(matrix);
        return temp.second; 
    }

    bool isEmpty(const Matrix& matrix) {
        return matrix.empty();
    }

    bool isSquare(const Matrix& matrix) {
        return rowSize(matrix) == columnSize(matrix);
    }
}

