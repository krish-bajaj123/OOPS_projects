module binarynum;
import  <iostream>;
import <string>;
import <sstream>;

using namespace std;

// Function to read binary number from input
BinaryNum readBinaryNum() {
    string input;
    cin >> input;

    // Initialize BinaryNum 
    BinaryNum binNum;
    binNum.size = 0;
    binNum.capacity = 4;
    binNum.contents = new bool[binNum.capacity];

    // Parse the input string characterwise
    istringstream iss(input);
    char c;
    while (iss >> c) {
        // To Check if character will be a  valid binary digit
        if (c == '0' || c == '1') {
            // Resize contents array 
            if (binNum.size == binNum.capacity) {
                int newCapacity = binNum.capacity * 2;
                bool *newContents = new bool[newCapacity];
                for (int i = 0; i < binNum.size; ++i) {
                    newContents[i] = binNum.contents[i];
                }
                delete[] binNum.contents;
                binNum.contents = newContents;
                binNum.capacity = newCapacity;
            }
            // Storing binary digit
            binNum.contents[binNum.size++] = (c == '1');
        } else {
            // Stop if non binary digit character is seen
            break;
        }
    }

    return binNum;
}

// concatenate function to join additional binary digits to  existing BinaryNum
void binaryConcat(BinaryNum &binNum) {
    string input;
    cin >> input;

    // Parse input string characterwise
    istringstream iss(input);
    char c;
    while (iss >> c) {
        // Check if character will be valid binary digit
        if (c == '0' || c == '1') {
            // Resize contents array
            if (binNum.size == binNum.capacity) {
                int newCapacity = binNum.capacity * 2;
                bool *newContents = new bool[newCapacity];
                for (int i = 0; i < binNum.size; ++i) {
                    newContents[i] = binNum.contents[i];
                }
                delete[] binNum.contents;
                binNum.contents = newContents;
                binNum.capacity = newCapacity;
            }
            // Store binary digit
            binNum.contents[binNum.size++] = (c == '1');
        } else {
            // stop if Non-binary digit character is seen
            break;
        }
    }
}

// Function to convert a binary number to decimal
int binaryToDecimal(const BinaryNum &binNum) {
    int decimal = 0;
    int power = 1;
    for (int i = binNum.size - 1; i >= 0; --i) {
        //decimal value 
        if (binNum.contents[i]) {
            decimal += power;
        }
        power *= 2;
    }
    return decimal;
}

// Function to print the binary number digits to output stream  with separator (if not the last digit)
void printBinaryNum(std::ostream &out, const BinaryNum &binNum, char sep) {
    for (int i = 0; i < binNum.size; ++i) {
        out << (binNum.contents[i] ? '1' : '0');
        // Print separator
        if (i != binNum.size - 1) {
            out << sep;
        }
    }
    // Print newline at end
    out << endl;
}
