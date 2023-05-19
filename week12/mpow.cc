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
    friend istringstream& operator>>(istringstream& is, nz& base);
    friend ostream& operator<<(ostream &os, const nz& base);

private:
    int ind;
    double val;
};
istringstream& operator>>(istringstream& is, nz& base)
{
    is>> base.ind;
    is>> base.val;
    return is;
}
ostream& operator<<(ostream &os,const nz& base)
{
    os<< base.ind<< " "<< base.val<< " ";
    return os;
}

typedef list<nz> sparseRow;
typedef list<sparseRow> sparseMat;

void readMat(sparseMat&, int&);
void transpMat(const sparseMat, sparseMat&);
void multMat(const sparseMat, const sparseMat, sparseMat&);
double dotProd(const sparseRow&, const sparseRow&);
void outMat(const sparseMat);
sparseMat matPow(const sparseMat&, int power);
sparseMat identityMat(const sparseMat& input);

double epsilon = 0.0;

int main(int argc, char *argv[])
{

    int power;
    // We will check for the right amount and type of argument
    try{
        if(argc != 2){
            throw std::invalid_argument("");
        }
        power = std::stoi(argv[1]);
        if(power < 0){
            throw std::invalid_argument("");
        }
    }catch(std::exception e){
        cout << "Use a single argument of whole positive integer" << endl;
        return -1;
    }
    // We will power the matrix
    int colct;
    sparseMat rows;
    readMat(rows, colct);

    sparseMat prod = matPow(rows, power);
    outMat(prod);
}

// Identity matrix of input number of rows
sparseMat identityMat(const sparseMat& input){
    sparseMat result;
    for (int i = 0; i < input.size(); i++) {
        sparseRow temp;
        temp.push_back(nz(i+1, 1));
        result.push_back(temp);
    }
    return result;
}

// Recursive fast exponentiation
sparseMat matPow(const sparseMat& input, int power){
    sparseMat result;

    if(power == 0){
        return identityMat(input); // Identity matrix
    }else if(power == 1){
        return input; // Matrix itself
    }else if(power == 2){
        multMat(input, input, result); // base case of power 2
        return result;
    }


    else if(power > 2){
        if(power % 2 == 0){
            result = matPow(input, power / 2); // if power even, half it
            result = matPow(result, 2);		// and then square it
        }else{
            result = matPow(input, power / 2); // otherwise half the power
            result = matPow(result, 2);		// square it
            sparseMat temp;
            multMat(input, result, temp);	// Now multiply it by once
            result = temp;
        }
    }
    return result;

}

void readMat(sparseMat &in, int &colct) {
    colct = 0;
    string line;
    while (getline(cin, line))    // get next full line of text; NB: text
    {
        istringstream lstream(line);
        sparseRow row;

        nz next;
        while (lstream >> next) { // peel off values in this line, one at a time
            row.push_back(next);
            if (colct < next.getInd()) {
                colct = next.getInd();
            }
        }

        in.push_back(row);
    }
}


void transpMat(const sparseMat rows, sparseMat &transp) {
    transp.clear();
    for (unsigned int c = 0; c < rows.size(); c++) // might not be square matrix
    {
        sparseRow row;
        transp.push_back(row);    // initialise every row of transpose;
    }

    int rowInsert = 0;
    sparseMat::iterator itr;
    for (sparseMat::const_iterator row = rows.begin(); row != rows.end(); row++) {
        rowInsert++;
        for (const nz &nonZero : *row) {
            itr = transp.begin();
            int column = nonZero.getInd() - 1;
            nz nzt(rowInsert, nonZero.getVal());
            std::advance(itr, column);
            itr->push_back(nzt);
        }
        itr++;
    }
}

void multMat(const sparseMat m1, const sparseMat m2, sparseMat& res)
{
    // remove every row of result, just in case anything there...
    res.clear();

    // now, initialise (install blank) every row of result
    for (unsigned int c = 0; c < m1.size(); c++) {
        sparseRow row;
        res.push_back(row);
    }

    sparseMat transp;
    transpMat(m2, transp);    // find transpose of second matrix, m2

    list<sparseRow>::const_iterator matrixItr = m1.begin();
    list<sparseRow>::iterator resultItr = res.begin();

    for( ; matrixItr != m1.end() ; matrixItr++){
        list<sparseRow>::const_iterator transpItr = transp.begin();
        int rowCount = 0;
        for(; transpItr != transp.end(); transpItr++){
            rowCount++;

            double value = dotProd(*matrixItr, *transpItr);

            if(value == 0){
                continue;
            }

            resultItr->push_back(nz(rowCount, value));
        }
        resultItr++;
    }
}

double dotProd(const sparseRow& r1, const sparseRow& r2)
{
    double result = 0.0f;

    sparseRow::const_iterator firstItr = r1.begin();
    sparseRow::const_iterator secondItr = r2.begin();

    while(firstItr != r1.end() && secondItr != r2.end() ){

        int index1 = firstItr->getInd(), index2 = secondItr->getInd();

        if(index1 == index2 ){
            result += firstItr->getVal() * secondItr->getVal();
            firstItr++;
        }
	// Move the index pointers
        if(index1 < index2 ){
            firstItr++;
        }else if(index2 < index1){
            secondItr++;
        }

    }

    return result;
}

void outMat(const sparseMat mat)
{
    sparseMat::const_iterator rit; // we only want to /read/ list
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

