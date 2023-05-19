
#include <iostream>
#include <string>
#include <sstream>
#include <list>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::list;

#include <math.h>
#include <stdlib.h>

class nz {	    // one instance for every non-zero entry in matrix
};

typedef list<nz> sparseRow;	// a single row

double epsilon = 0.0;

int main(int argc, char *argv[])
{
  if (argc > 1 &&
      string(argv[1]) == "-e")
  {
    epsilon = fabs(strtod(argv[2], 0));
  }

  string line;
  int nzct = 0;

  while (getline(cin, line))	// get next full line of text; NB: text
  {
    std::istringstream lstream(line) ;
    sparseRow row;
    int ind = 0;		// index of element of row
    double val;
    while (lstream>> val)	// peel off values in this line, one at a time
    {
      ind++;
      if (fabs(val) <= epsilon)
	continue;

      // ok this is a keeper; so keep it
    }


  }

  // now iterate through the list of lists, writing out as we go
  list<sparseRow>::const_iterator rit; // we only want to /read/ list
  for (rit = rows.begin(); rit != rows.end(); rit++)
  {
    sparseRow row = *rit;

    // iterate over this row, writing out

  }
}

// STL:  http://www.csci.csusb.edu/dick/samples/stl.html
