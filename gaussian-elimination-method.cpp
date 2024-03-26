#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

void rowAddition(vector<vector<double>>& matrix, int row_to_change, int row_to_add, double multiplier) {
    int cols = matrix[0].size();
    for (int i = 0; i < cols; ++i) {
        matrix[row_to_change][i] += multiplier * matrix[row_to_add][i];
    }
}

void rowMultiplication(vector<vector<double>>& matrix, int row_index, double multiplier) {
    int cols = matrix[0].size();
    for (int i = 0; i < cols; ++i) {
        matrix[row_index][i] *= multiplier;
    }
}

void rowSwap(vector<vector<double>>& matrix, int row1, int row2) {
    matrix[row1].swap(matrix[row2]);
}

void gaussianElimination(vector<vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    int lead = 0;
    for (int r = 0; r < rows; ++r) {
        if (lead >= cols)
            break;

        int i = r;
        while (matrix[i][lead] == 0) {
            ++i;
            if (i == rows) {
                i = r;
                ++lead;
                if (lead == cols)
                    return;
            }
        }

        rowSwap(matrix, i, r);
        rowMultiplication(matrix, r, 1.0 / matrix[r][lead]);
        for (int i = 0; i < rows; ++i) {
            if (i != r)
                rowAddition(matrix, i, r, -matrix[i][lead]);
        }

        ++lead;
    }
}

void fillRandomMatrix(vector<vector<double>>& matrix) {
    srand(time(NULL));

    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = -10 + rand() % 21;
        }
    }
}

void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double element : row) {
            if (fabs(element) == 0) {
                cout << 0 << "\t";
            } else {
                cout << element << "\t";
            }
        }
        cout << endl;
    }
}

int main() {
    vector<vector<double>> matrix(3, vector<double>(4));

    fillRandomMatrix(matrix);

    cout << "Original Matrix:" << endl;
    printMatrix(matrix);

    gaussianElimination(matrix);

    cout << "\nMatrix in Row Echelon Form:" << endl;
    printMatrix(matrix);

    cin.ignore();
    return 0;
}

