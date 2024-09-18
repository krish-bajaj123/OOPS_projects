#include "extendedNum.h"
#include <sstream>

// Constructor
ExtendedNum::ExtendedNum(int val, int t) : value(val), type(t) {}

// Overloaded operators
ExtendedNum ExtendedNum::operator+(const ExtendedNum &rhs) const {
    if (type == 3 || rhs.type == 3) { // If either is undefined, return undefined
        return ExtendedNum(0, 3);
    } else if (type == 1 && rhs.type == 2) { // If one is +inf and the other is -inf, return undefined
        return ExtendedNum(0, 3);
    } else if (type == 2 && rhs.type == 1) { // If one is -inf and the other is +inf, return undefined
        return ExtendedNum(0, 3);
    } else if (type == 1 || rhs.type == 1) { // If either is +inf, return +inf
        return ExtendedNum(0, 1);
    } else if (type == 2 || rhs.type == 2) { // If either is -inf, return -inf
        return ExtendedNum(0, 2);
    } else { // Otherwise, both are numbers, return their sum
        return ExtendedNum(value + rhs.value, 0);
    }
}


ExtendedNum ExtendedNum::operator-(const ExtendedNum &rhs) const {
    if (type == 3 || rhs.type == 3) { // If either is undefined, return undefined
        return ExtendedNum(0, 3);
    } else if (type == 1 && rhs.type == 1) { // If both are +inf, return undefined
        return ExtendedNum(0, 3);
    } else if (type == 2 && rhs.type == 2) { // If both are -inf, return undefined
        return ExtendedNum(0, 3);
    } else if (type == 1) { // If lhs is +inf and rhs is anything else, return +inf
        return ExtendedNum(0, 1);
    } else if (type == 2) { // If lhs is -inf and rhs is anything else, return -inf
        return ExtendedNum(0, 2);
    } else if (rhs.type == 1) { // If rhs is +inf and lhs is anything else, return -inf
        return ExtendedNum(0, 2);
    } else if (rhs.type == 2) { // If rhs is -inf and lhs is anything else, return +inf
        return ExtendedNum(0, 1);
    } else { // Otherwise, both are numbers, return their difference
        return ExtendedNum(value - rhs.value, 0);
    }
}

ExtendedNum ExtendedNum::operator*(const ExtendedNum &rhs) const {
    if (type == 3 || rhs.type == 3) { // If either is undefined, return undefined
        return ExtendedNum(0, 3);
    } else if (type == 0 || rhs.type == 0) { // If either is a number, return a number
        return ExtendedNum(value * rhs.value, 0);
    } else if ((type == 1 && rhs.value == 0) || (rhs.type == 1 && value == 0)) { // If one is positive infinity and the other is zero
        return ExtendedNum(0, 3); // Result is undefined
    } else if ((type == 2 && rhs.value == 0) || (rhs.type == 2 && value == 0)) { // If one is negative infinity and the other is zero
        return ExtendedNum(0, 3); // Result is undefined
    } else if ((type == 1 && rhs.value > 0) || (rhs.type == 1 && value > 0)) { // If one is positive infinity and the other is positive
        return ExtendedNum(0, 1); // Result is positive infinity
    } else if ((type == 1 && rhs.value < 0) || (rhs.type == 1 && value < 0)) { // If one is positive infinity and the other is negative
        return ExtendedNum(0, 2); // Result is negative infinity
    } else if ((type == 2 && rhs.value < 0) || (rhs.type == 2 && value < 0)) { // If one is negative infinity and the other is negative
        return ExtendedNum(0, 1); // Result is positive infinity
    } else if ((type == 2 && rhs.value > 0) || (rhs.type == 2 && value > 0)) { // If one is negative infinity and the other is positive
        return ExtendedNum(0, 2); // Result is negative infinity
    } else {
        return ExtendedNum(0, 3); // Undefined
    }
}


ExtendedNum ExtendedNum::operator/(const ExtendedNum &rhs) const {
    // If either operand is undefined, the result is undefined
    if (type == 3 || rhs.type == 3) {
        return ExtendedNum(0, 3);
    }
    // Division by zero is undefined, unless the numerator is zero or the numerator is positive infinity and the denominator is negative or vice versa
    if (rhs.value == 0) {
        if ((type == 1 && value > 0) || (type == 2 && value < 0) || value == 0) {
            return ExtendedNum(0, 3);
        }
    }
    // If both operands are numbers, perform division
    if (type == 0 || rhs.type == 0) {
        return ExtendedNum(value / rhs.value, 0);
    }
    // Division of infinities is undefined
    if ((type == 1 && rhs.type == 1) || (type == 2 && rhs.type == 2)) {
        return ExtendedNum(0, 3);
    }
    // If one operand is infinity and the other is a number or infinity, determine the sign of the result based on the sign of the operands
    if (type == 1 || type == 2) {
        if (rhs.value > 0) {
            if (type == 1) {
                return ExtendedNum(0, 1); // Positive infinity / positive number = positive infinity
            } else {
                return ExtendedNum(0, 2); // Negative infinity / positive number = negative infinity
            }
        } else {
            if (type == 1) {
                return ExtendedNum(0, 2); // Positive infinity / negative number = negative infinity
            } else {
                return ExtendedNum(0, 1); // Negative infinity / negative number = positive infinity
            }
        }
    } else {
        return ExtendedNum(0, 3); // Default case: undefined
    }
}



ExtendedNum ExtendedNum::operator-() const {
    if (type == 0) { // If it's a number, negate it
        return ExtendedNum(-value, 0);
    } else if (type == 1) { // If it's positive infinity, return negative infinity
        return ExtendedNum(0, 2);
    } else if (type == 2) { // If it's negative infinity, return positive infinity
        return ExtendedNum(0, 1);
    } else { // Undefined
        return ExtendedNum(0, 3);
    }
}

// Overloaded input/output operators
std::ostream &operator<<(std::ostream &out, const ExtendedNum &num) {
    // Print the value or corresponding infinity or undefined
    if (num.type == 0) {
        out << num.value;
    } else if (num.type == 1) {
        out << "+infinity";
    } else if (num.type == 2) {
        out << "-infinity";
    } else {
        out << "undefined";
    }
    return out;
}

std::istream &operator>>(std::istream &in, ExtendedNum &num) {
    std::string input;
    in >> input; // Read input from stream
    // Check if input represents positive infinity
    if (input == "+infinity") {
        num.value = 0; // Value is irrelevant for infinity
        num.type = 1; // Set type to positive infinity
    } 
    // Check if input represents negative infinity
    else if (input == "-infinity") {
        num.value = 0; // Value is irrelevant for infinity
        num.type = 2; // Set type to negative infinity
    } 
    // Check if input represents undefined
    else if (input == "undefined") {
        num.value = 0; // Value is irrelevant for undefined
        num.type = 3; // Set type to undefined
    } 
    // Otherwise, input may represent a numeric value
    else {
        std::istringstream iss(input);
        // Try to extract a numeric value from the input
        if (iss >> num.value)
            num.type = 0; // Set type to number
        else
            num.type = 3; // If input cannot be converted to a number, mark it as undefined
    }
    return in;
}



