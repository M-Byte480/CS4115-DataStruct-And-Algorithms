#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;

#include <math.h>
#include <stdlib.h>

void readArr(int, int, double **);
void multArrs(int, double **, int, double **, int, double **);

int main(int argc, char *argv[]){

    if(argc != 5){
        cerr << "Incorrect Format" << endl;
        cout << "You had: " << argc << " arguments" << endl;
        exit(-1);
    }

  int ar = atoi(argv[1]);
  int ac = atoi(argv[2]);
  int br = atoi(argv[3]);
  int bc = atoi(argv[4]);

  if (ac != br){
    cerr<< "Matrix dimensions mismatch; exiting.\n";
    exit(-1);
  }

  // reserve space for the three arrays
  double **A = new double*[ar];	// each el. of this points to a row of A
  for (int i = 0; i < ar; i++) A[i] = new double[ac];	// a row of 'ac' floats

  double **B = new double*[br];
  for (int i = 0; i < br; i++) B[i] = new double[bc];	// a row of 'bc' floats

  double **C = new double*[ar];	// each el. of this points to a row of C
  // fill in code here to allocate C
  // C has 'ar' rows and 'bc' columns
  // second line to fill in
  // a row of 'bc' floats

    for (int i = 0; i < ar; ++i) {
        C[i] = new double[bc];
    }

  // now that sufficient storage is allocated, start reading from kbd

  readArr(ar, ac, A);
  readArr(br, bc, B);

  /*
    cout << "Matrix 1:" << endl;
    for (int i = 0; i < ar; ++i) {
        for (int j = 0; j < bc; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;


    cout << "Matrix 2: " << endl;
    for (int i = 0; i < ar; ++i) {
        for (int j = 0; j < bc; ++j) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
  */

  multArrs(ar, A, bc, B, ac, C);

  // now print out answer, nice and plainly
  for (int i = 0; i < ar; ++i) {
        for (int j = 0; j < bc; ++j) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }


    // Memory management
  
  /*
    delete[] C;
    delete[] A;
    delete[] B;
  */
  
    // Successful exit
    exit(0);
}

// read from kbd into this array, row by row
//  for a total of r x c entries;
//  WARNING: space for array must have been reserved beforehand
void readArr(int r, int c, double **arr){
  // code for reading in r rows of c elements each goes here
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            std::cin >> arr[i][j];
        }
    }

}

void multArrs(int ar, double **A, int bc, double **B, int br, double **C){
    // multiplication here
  
    // AR = first ROW
    // BR is the OVERLAP
    // BC = second COLUMN

    for (int rr = 0; rr < ar; ++rr) {
        for (int rc = 0; rc < bc; ++rc) {
            for (int i = 0; i < br; ++i) {
                C[rr][rc] += A[rr][i] * B[i][rc];
            }
        }
    }

}
