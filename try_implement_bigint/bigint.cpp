#include "bigint.hpp"

bigint::bigint() : val("0") {}

bigint::bigint(unsigned int n) {
    std::stringstream ss;
    ss << n;
    val = ss.str();
}

bigint::bigint(const bigint& b) : val(b.val) {}

bigint::bigint(const str& s) : val(s) {
    // Remove leading zeros
    size_t pos = val.find_first_not_of('0');
    if (pos == str::npos)
        val = "0";
    else
        val = val.substr(pos);
}

bigint::~bigint() {}

str bigint::getVal() const {
    return val;
}

bigint bigint::operator+(const bigint& b) const {
    str s1 = this->val;
    str s2 = b.val;
    
    if (s1.size() < s2.size())
        std::swap(s1, s2);
    
    str result = "";
    int carry = 0;
    int i = s1.size() - 1;
    int j = s2.size() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? s1[i] - '0' : 0;
        int digit2 = (j >= 0) ? s2[j] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result = char('0' + (sum % 10)) + result;
        i--;
        j--;
    }
    
    // Remove leading zeros from result
    size_t pos = result.find_first_not_of('0');
    if (pos == str::npos)
        result = "0";
    else
        result = result.substr(pos);
    
    return bigint(result);
}

bigint& bigint::operator+=(const bigint& b) {
    *this = *this + b;
    return *this;
}

bigint bigint::operator++(int) {
    bigint temp(*this);
    *this += bigint(1);
    return temp;
}

bigint& bigint::operator++() {
    *this += bigint(1);
    return *this;
}

bigint bigint::operator<<(unsigned int shift) const {
    if (this->val == "0")
        return *this;
    bigint copy(*this);
    copy.val.append(shift, '0');
    return copy;
}

bigint& bigint::operator<<=(unsigned int shift) {
    if (this->val == "0")
        return *this;
    this->val.append(shift, '0');
    return *this;
}

bigint& bigint::operator>>=(const bigint& b) {
    if (this->val == "0")
        return *this;
    
    std::stringstream ss;
    ss << b.val;
    unsigned int shift = 0;
    ss >> shift;
    
    if (shift >= this->val.size()) {
        this->val = "0";
        return *this;
    }
    
    this->val = this->val.substr(0, this->val.size() - shift);
    return *this;
}

bool bigint::operator<(const bigint& b) const {
    if (this->val.size() < b.val.size())
        return true;
    if (this->val.size() > b.val.size())
        return false;
    return this->val < b.val;
}

bool bigint::operator>(const bigint& b) const {
    return b < *this;
}

bool bigint::operator==(const bigint& b) const {
    return this->val == b.val;
}

bool bigint::operator!=(const bigint& b) const {
    return !(*this == b);
}

bool bigint::operator<=(const bigint& b) const {
    return !(*this > b);
}

bool bigint::operator>=(const bigint& b) const {
    return !(*this < b);
}

bigint bigint::operator-(const bigint& b) const {
    // Dummy implementation as per subject note
    (void)b;
    return bigint(0);
}

std::ostream& operator<<(std::ostream& os, const bigint& b) {
    os << b.getVal();
    return os;
}
