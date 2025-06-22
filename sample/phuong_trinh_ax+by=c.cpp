#include <iostream>

using namespace std;

// Hàm tìm ước chung lớn nhất (GCD) và hệ số x, y trong phương trình ax + by = gcd(a, b)
int extended_gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a; // GCD của (a, b) là a
    }
    int x1, y1;
    int gcd = extended_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

// Hàm tìm nghiệm của phương trình Diophantine ax + by = c
bool solve_diophantine(int a, int b, int c, int &x, int &y, int &gcd)
{
    gcd = extended_gcd(a, b, x, y);

    // Kiểm tra nếu c không chia hết cho gcd(a, b) thì phương trình vô nghiệm
    if (c % gcd != 0)
        return false;

    // Nhân hệ số lên để có nghiệm cho phương trình ax + by = c
    x *= c / gcd;
    y *= c / gcd;
    return true;
}

int main()
{
    //39x + 15b = 12
    int a = 39, b = 15, c = 12;
    int x, y, gcd;

    if (solve_diophantine(a, b, c, x, y, gcd))
    {
        cout << "Mot nghiem cu the: x = " << x << ", y = " << y << endl;
        cout << "Nghiem tong quat: x = " << x << " + k*" << (b / gcd) << ", y = " << y << " - k*" << (a / gcd) << " voi k la so nguyen" << endl;
    }
    else
    {
        cout << "Phuong trinh vo nghiem!" << endl;
    }

    return 0;
}
