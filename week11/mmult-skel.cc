
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::list;
using std::vector;
using std::istringstream;
using std::ostream;

#include <math.h>
#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

class nz {	    // one instance for every non-zero entry in matrix
public:
  nz() { ind = 0; val = 0.0; }
  nz(int i, double v) {	// constructor when given the two items of data
    ind = i;
    val = v;
  }
  int getInd() const { return ind; } // access to ind class member
  double getVal() const { return val; } // access to val class member
  // other methods here, if required

private:
  int ind;
  double val;
};

typedef list<nz> sparseRow;	// this choice of DS is unquestionable
typedef list<sparseRow> sparseMat; // this choice of DS may be questioned

void readMat(sparseMat&, int&);
void transpMat(const sparseMat, int, sparseMat&);
void multMat(const sparseMat, const sparseMat, sparseMat&);
double dotProd(const sparseRow&, const sparseRow&);
void outMat(const sparseMat);

double epsilon = 0.0;

int main(int argc, char *argv[])
{
  int colct;
  sparseMat inmat;
  readMat(inmat, colct);

  sparseMat prod;
  multMat(inmat, inmat, prod);

  outMat(prod);
}

//////////////// functions below here ///////////////////

void readMat(sparseMat& in, int& colct)
{
  colct = 0;
  string line;
  while (getline(cin, line))	// get next full line of text; NB: text
  {
    istringstream lstream(line);
    sparseRow row;

    nz next;
    while (lstream>> next) { // peel off values in this line, one at a time
      row.push_back(next);
    }

    in.push_back(row);
  }
}

void transpMat(const sparseMat rows, int colct, sparseMat& transp)
{
}

void multMat(const sparseMat m1, const sparseMat m2, sparseMat& res)
{
  // remove every row of result, just in case anything there...
  res.clear();

  // now, initialise (install blank) every row of result
  for (unsigned int c = 0; c < m1.size(); c++)
  {
    sparseRow row;
    res.push_back(row);	
  }
  sparseMat transp;
  transpMat(m2, transp);	// find transpose of second matrix, m2

  // now do the multiplications, based on dotproducts of rows
  //   of /both/ matrices, m1 and transp
}

double dotProd(sparseRow r1, sparseRow r2)
{
}

void outMat(const sparseMat mat)
{
  // now write out
  for (rit = mat.begin(); rit != mat.end(); rit++)
  {
    sparseRow row = *rit;
    // iterate over this row, only /read/
    sparseRow::const_iterator nzit;
    for (nzit = row.begin(); nzit != row.end(); nzit++)
    {
      cout<< *nzit;
    }

    cout<< endl;
  }
}

// http://www.codersource.net/c/c-miscellaneous/overloading-stream-operators.aspx
