#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <math.h>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::list;
using std::vector;
using std::istringstream;
using std::ostream;

using namespace std;


class nz {	    // one instance for every non-zero entry in matrix
public:
    nz() { ind = 0; val = 0.0; }
    nz(int i, double v) {	// constructor when given the two items of data
        ind = i;
        val = v;
    }

    int getInd() const { return ind; } // access to ind class member
    double getVal() const { return val; } // access to val class member

    friend istringstream& operator>>(istringstream& is, nz& base){
        is >> base.ind;
        is >> base.val;
        return is;
    }
    friend ostream& operator<<(ostream &os, const nz& base){
        os << base.ind << " ";
        os << base.val << " ";
        return os;
    }

private:
    int ind;
    double val;
};

typedef list<nz> sparseRow;
typedef vector<sparseRow> sparseMat;

void readMat(sparseMat&, int&);	// read from stdin
void transpMat(const sparseMat, int&,  sparseMat&); // first arg is mat to transpose;
//  second is passed by reference
//  so this will be the transpose
double epsilon = 0.0;

int main(int argc, char *argv[])
{
    int colct;
    sparseMat rows;
    readMat(rows, colct);
    vector<sparseRow> transp;
    transpMat(rows, colct, transp);

    // now write out
    //    :
    for (int i = 0; i < transp.capacity(); ++i) {
        for (const nz &nz: transp.at(i)) {
            cout << nz;
        }
        cout << endl;
    }
    return 0;
}
// *
void readMat(sparseMat& rows, int& colct)
{
    colct = 0;
    string line;
    while (getline(cin, line))	// get next full line of text; NB: text
    {
        istringstream lstream(line) ;
        sparseRow row;

        // :
        nz next;
        while(lstream>>next){
            row.push_back(next);
            if(next.getInd() > colct) colct = next.getInd();
        }
        rows.push_back(row);
    }
}

// *
void transpMat(const sparseMat rows, int &colct, sparseMat& transp)
{
    for (unsigned int c = 0; c < colct; c++) // might not be square matrix
    {
        sparseRow row;
        transp.push_back(row);	// initialise every row of transpose;
        //   there are colct of them
    }

    //:
    for(int row = 0 ; row < rows.size() ; row++)
    {
        for (const nz &nz: rows.at(row)) {
            // Row number is row + 1
            // Column number is column + 1
            // so now M(r,c) becomes M(c, r);
            int column = nz.getInd() - 1;
            class nz nzt(row + 1 ,nz.getVal());
            transp.at(column).push_back(nzt);
        }

    }
}

//*/

