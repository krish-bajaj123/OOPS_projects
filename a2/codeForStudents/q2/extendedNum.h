#include <iostream>
#include <string>

struct ExtendedNum {
    int value;
    int type; // 0 for NUMBER, 1 for +infinity, 2 for -infinty, 3 for undefined

    ExtendedNum(int val = 0, int t = 0);

    ExtendedNum operator+(const ExtendedNum &rhs) const;
    ExtendedNum operator-(const ExtendedNum &rhs) const;
    ExtendedNum operator*(const ExtendedNum &rhs) const;
    ExtendedNum operator/(const ExtendedNum &rhs) const;
    ExtendedNum operator-() const;
};

std::ostream &operator<<(std::ostream &out, const ExtendedNum &num);
std::istream &operator>>(std::istream &in, ExtendedNum &num);
