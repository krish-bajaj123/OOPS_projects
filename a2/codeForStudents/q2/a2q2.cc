#include <iostream>
#include "extendedNum.h"
using namespace std;

int main() {
    const unsigned int MAX_ARR_SIZE = 4;
    ExtendedNum a[MAX_ARR_SIZE];
    string command;

    while (cin >> command) {
        char which, which2;

        if (command == "quit") break;

        if (command == "create") {
            cin >> which; // reads a b c or d
            cin >> a[which-'a'];
        } else if (command == "print") {
            cin >> which; // reads a b c or d
            cout << a[which-'a'] << endl;
        } else if (command == "-") { // 
            cin >> which >> which2; // reads a b c or d twice
            cout << a[which-'a'] - a[which2-'a'] << endl;
        } else if (command == "u-") { //unary minus
            cin >> which; // reads a b c or d
            cout << -a[which-'a']  << endl;
        } else if (command == "+") {
            cin >> which >> which2; // reads a b c or d twice
            cout << a[which-'a'] + a[which2-'a'] << endl;
        } else if (command == "*") {
            cin >> which >> which2; // reads a b c or d twice
            cout << a[which-'a'] * a[which2-'a'] << endl;
        } else if (command == "/"){
            cin >> which >> which2; // reads a b c or d twice
            cout << a[which-'a'] / a[which2-'a'] << endl;
        } // if
    } // while
} // main
