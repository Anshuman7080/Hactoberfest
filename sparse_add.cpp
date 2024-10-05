#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to sort the sparse matrix based on row and column
void sortSparseMatrix(vector<vector<int>>& sparse) {
    sort(sparse.begin() + 1, sparse.end(), [](const vector<int>& a, const vector<int>& b) {
        if (a[0] == b[0])
            return a[1] < b[1]; // Sort by column if rows are equal
        return a[0] < b[0]; // Sort by row
    });
}

int main() {
    int rows, cols, n1, n2;

    cout << "Enter number of rows for both matrices: ";
    cin >> rows;
    cout << "Enter number of cols for both matrices: ";
    cin >> cols;
    cout << "Enter number of non-zero values in matrix 1: ";
    cin >> n1;
    cout << "Enter number of non-zero values in matrix 2: ";
    cin >> n2;

    vector<vector<int>> sparse1(n1 + 1, vector<int>(3));
    vector<vector<int>> sparse2(n2 + 1, vector<int>(3));
    
    sparse1[0] = {rows, cols, n1};
    sparse2[0] = {rows, cols, n2};

    string arr[3] = {"row", "col", "value"};

    // Input for matrix 1
    cout << "\nFor matrix 1:" << endl;
    for (int i = 1; i <= n1; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Enter " << arr[j] << ": ";
            cin >> sparse1[i][j];
        }
    }

    // Input for matrix 2
    cout << "\nFor matrix 2:" << endl;
    for (int i = 1; i <= n2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Enter " << arr[j] << ": ";
            cin >> sparse2[i][j];
        }
    }

    // Sort both sparse matrices
    sortSparseMatrix(sparse1);
    sortSparseMatrix(sparse2);

    // Add the sparse matrices
    vector<vector<int>> add(n1 + n2 + 1, vector<int>(3));
    add[0] = {rows, cols, 0};

    int i = 1, j = 1, k = 1;

    while (i <= n1 && j <= n2) {
        if (sparse1[i][0] < sparse2[j][0] || (sparse1[i][0] == sparse2[j][0] && sparse1[i][1] < sparse2[j][1])) {
            add[k++] = sparse1[i++];
        } else if (sparse1[i][0] > sparse2[j][0] || (sparse1[i][0] == sparse2[j][0] && sparse1[i][1] > sparse2[j][1])) {
            add[k++] = sparse2[j++];
        } else { // They are equal in row and column
            add[k] = {sparse1[i][0], sparse1[i][1], sparse1[i][2] + sparse2[j][2]};
            k++;
            i++;
            j++;
        }
    }

    // Copy remaining elements from sparse1
    while (i <= n1) {
        add[k++] = sparse1[i++];
    }

    // Copy remaining elements from sparse2
    while (j <= n2) {
        add[k++] = sparse2[j++];
    }

    // Update the count of non-zero values
    add[0][2] = k - 1;

    // Display the result
    cout << "\nResultant Sparse Matrix:" << endl;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            bool found = false;
            for (int m = 1; m < k; m++) {
                if (add[m][0] == r && add[m][1] == c) {
                    cout << add[m][2] << '\t';
                    found = true;
                    break;
                }
            }
            if (!found) cout << 0 << '\t';
        }
        cout << endl;
    }

    return 0;
}
