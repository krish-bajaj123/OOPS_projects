#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "textprocess.h"
#include "echo.h"
#include "dropfirst.h"   // Include for DropFirst decorator
#include "doublewords.h" // Include for DoubleWords decorator
#include "allcaps.h"     // Include for AllCaps decorator
#include "count.h"       // Include for Count decorator

int main () {
  // Turn on exceptions for when cin.fail() or cin.eof() are true.
  cin.exceptions(ios::failbit|ios::eofbit);
  string s;

  try {
    while(true) {
      getline(cin,s);
      istringstream iss{s};
      iss.exceptions(ios::failbit);
      string fname;
      iss >> fname;
      istream *in = (fname == "stdin") ? &cin : new ifstream(fname.c_str());
      in->exceptions(ios::failbit|ios::eofbit);
  
      TextProcessor *tp = new Echo;
      string dec;
      try {
        while (true) {
          iss >> dec;
          if (dec == "dropfirst") {
            int n;
            iss >> n;
            tp = new DropFirst(tp, n); // extend with DropFirst decorator
          } else if (dec == "doublewords") {
            tp = new DoubleWords(tp); // extend with DoubleWords decorator
          } else if (dec == "allcaps") {
            tp = new AllCaps(tp); // extend with AllCapa decorator
          } else if (dec == "count") {
            char c;
            iss >> c;
            tp = new Count(tp, c); // extend with Count decorator
          } // if
       } // while
      } catch (ios::failure&) {}

      tp->setSource(in);

      try {
        string word;
        int lineNumber = 1;
        while (true) {
          word = tp->getWord();
          cout << lineNumber++ << ":\t" << word << endl;
        } // while
      } catch (ios::failure&) {}
  
      if (in != &cin) delete in;
      delete tp;
    } // while
  } catch (ios::failure&) {}
} // main
