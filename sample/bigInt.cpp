#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <string>

using namespace std;

class BigInt
{
private:
    vector<long long> blocks;
    bool isNegative;
    static const long long BASE = 1000000000; // Mỗi khối lưu trữ tới 9 chữ số

public:
    BigInt(const string &number)
    {
        if (number[0] == '-')
        {
            isNegative = true;
        }
        else
        {
            isNegative = false;
        }
        long long len = number.length();
        long long start = (isNegative ? 1 : 0);
        while (len > start)
        {
            long long end = max(len - 9, start);
            blocks.push_back(stoll(number.substr(end, len - end)));
            len -= 9;
        }
        while (blocks.size() > 1 && blocks.back() == 0)
            blocks.pop_back();
    }

    BigInt(const vector<long long> &blocks, bool isNegative)
        : blocks(blocks), isNegative(isNegative)
    {
        normalize();
    }

    void normalize()
    {
        long long carry = 0;
        for (size_t i = 0; i < blocks.size() || carry; ++i)
        {
            if (i == blocks.size())
                blocks.push_back(0);
            blocks[i] += carry;
            carry = blocks[i] / BASE;
            blocks[i] %= BASE;
        }
        while (blocks.size() > 1 && blocks.back() == 0)
            blocks.pop_back();
        if (blocks.size() == 1 && blocks[0] == 0)
            isNegative = false; 
    }

    BigInt operator+(const BigInt &other) const
    {
        if (isNegative == other.isNegative)
        {
            vector<long long> result(max(blocks.size(), other.blocks.size()), 0);
            long long carry = 0;
            for (size_t i = 0; i < result.size() || carry; ++i)
            {
                if (i < blocks.size())
                    result[i] += blocks[i];
                if (i < other.blocks.size())
                    result[i] += other.blocks[i];
                result[i] += carry;
                carry = result[i] / BASE;
                result[i] %= BASE;
            }
            if (carry)
                result.push_back(carry);
            return BigInt(result, isNegative);
        }
        else
        {
            if (abs() >= other.abs())
            {
                return *this - (-other);
            }
            else
            {
                return other - (-*this);
            }
        }
    }

    BigInt operator-(const BigInt &other) const
    {
        if (isNegative != other.isNegative)
        {
            return *this + (-other);
        }
        else
        {
            if (abs() >= other.abs())
            {
                vector<long long> result = blocks;
                long long borrow = 0;
                for (size_t i = 0; i < other.blocks.size() || borrow; ++i)
                {
                    if (i < other.blocks.size())
                        result[i] -= other.blocks[i];
                    result[i] -= borrow;
                    borrow = (result[i] < 0) ? 1 : 0;
                    if (borrow)
                        result[i] += BASE;
                }
                while (result.size() > 1 && result.back() == 0)
                    result.pop_back();
                return BigInt(result, isNegative);
            }
            else
            {
                return -(other - *this);
            }
        }
    }

    BigInt operator*(const BigInt &other) const
    {
        std::vector<long long> result(blocks.size() + other.blocks.size(), 0);
        for (size_t i = 0; i < blocks.size(); ++i)
        {
            long long carry = 0;
            for (size_t j = 0; j < other.blocks.size() || carry; ++j)
            {
                long long cur = result[i + j] +
                                blocks[i] * (j < other.blocks.size() ? other.blocks[j] : 0) +
                                carry;
                carry = cur / BASE;
                result[i + j] = cur % BASE;
            }
        }
        bool resultNegative = isNegative != other.isNegative; 
        return BigInt(result, resultNegative && !(result.size() == 1 && result[0] == 0));
    }

    BigInt operator-() const
    { 
        return BigInt(blocks, !isNegative);
    }

    bool operator<(const BigInt &other) const
    {
        if (isNegative != other.isNegative)
        {
            return isNegative;
        }
        if (blocks.size() != other.blocks.size())
        {
            return blocks.size() < other.blocks.size() != isNegative;
        }
        for (int i = static_cast<int>(blocks.size()) - 1; i >= 0; --i)
        {
            if (blocks[i] != other.blocks[i])
            {
                return blocks[i] < other.blocks[i] != isNegative;
            }
        }
        return false;
    }

    bool operator>=(const BigInt &other) const
    {
        return !(*this < other);
    }

    BigInt abs() const
    {
        return BigInt(blocks, false);
    }

    friend ostream &operator<<(ostream &out, const BigInt &num)
    {
        if (num.isNegative)
            out << '-';
        out << (num.blocks.empty() ? 0 : num.blocks.back());
        for (int i = static_cast<int>(num.blocks.size()) - 2; i >= 0; --i)
        {
            out << setw(9) << setfill('0') << num.blocks[i];
        }
        return out;
    }
};

int main()
{
    BigInt num1("-3");
    BigInt num2("5");

    BigInt sum = num1 + num2;
    BigInt diff = num1 - num2;
    BigInt mul = num1 * num2;

    cout << "Result of Addition: " << sum << endl;
    cout << "Result of Subtraction: " << diff << endl;
    cout << "Result of multi: " << mul << endl;
    return 0;
}
