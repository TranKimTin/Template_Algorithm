#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point
{
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }
    bool operator==(const Point &p) const { return x == p.x && y == p.y; }

    int cross(const Point &p) const { return x * p.y - y * p.x; }
    int dot(const Point &p) const { return x * p.x + y * p.y; }

    int cross(const Point &a, const Point &b) const { return (a - *this).cross(b - *this); }
    int dot(const Point &a, const Point &b) const { return (a - *this).dot(b - *this); }
};

using Vector = Point;

struct PointD
{
    double x, y;
    PointD(double x = 0, double y = 0) : x(x), y(y) {}
};

struct Segment
{
    Point a, b;
    Segment(Point a, Point b) : a(a), b(b) {}

    double length() const
    {
        int dx = a.x - b.x, dy = a.y - b.y;
        return sqrt(dx * dx + dy * dy);
    }

    bool contains(const Point &p) const
    {
        return a.cross(p, b) == 0 &&
               min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
               min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
    }

    bool intersects(const Segment &s) const
    {
        int d1 = a.cross(b, s.a);
        int d2 = a.cross(b, s.b);
        int d3 = s.a.cross(s.b, a);
        int d4 = s.a.cross(s.b, b);

        if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
            ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
            return true;

        // Kiểm tra giao tại điểm biên
        return contains(s.a) || contains(s.b) || s.contains(a) || s.contains(b);
    }

    // Trả về giao điểm hai **đường thẳng** (kéo dài đoạn)
    optional<PointD> intersectionPoint(const Segment &other) const
    {
        int A1 = b.y - a.y;
        int B1 = a.x - b.x;
        int C1 = A1 * a.x + B1 * a.y;

        int A2 = other.b.y - other.a.y;
        int B2 = other.a.x - other.b.x;
        int C2 = A2 * other.a.x + B2 * other.a.y;

        int det = A1 * B2 - A2 * B1;

        if (det == 0)
            return nullopt; // song song hoặc trùng nhau

        double x = (double)(B2 * C1 - B1 * C2) / det;
        double y = (double)(A1 * C2 - A2 * C1) / det;
        return PointD(x, y);
    }
};

struct Polygon
{
    vector<Point> pts;

    Polygon(const vector<Point> &pts) : pts(pts) {}

    void makeConvexHull()
    {
        if (pts.size() <= 1)
            return;

        sort(pts.begin(), pts.end(), [](const Point &a, const Point &b)
             { return tie(a.x, a.y) < tie(b.x, b.y); });

        vector<Point> lower, upper;

        for (const Point &p : pts)
        {
            while (lower.size() >= 2 && lower[lower.size() - 2].cross(lower.back(), p) <= 0)
                lower.pop_back();
            lower.push_back(p);
        }

        for (int i = (int)pts.size() - 1; i >= 0; --i)
        {
            const Point &p = pts[i];
            while (upper.size() >= 2 && upper[upper.size() - 2].cross(upper.back(), p) <= 0)
                upper.pop_back();
            upper.push_back(p);
        }

        // Gộp lại, bỏ điểm trùng nhau ở đầu và cuối
        lower.pop_back();
        upper.pop_back();
        pts = lower;
        pts.insert(pts.end(), upper.begin(), upper.end());
    }

    double perimeter() const
    {
        double res = 0;
        for (int i = 0; i < pts.size(); ++i)
            res += Segment(pts[i], pts[(i + 1) % pts.size()]).length();
        return res;
    }

    double area() const
    {
        long long s = 0;
        for (int i = 0; i < pts.size(); ++i)
        {
            Point a = pts[i], b = pts[(i + 1) % pts.size()];
            s += 1LL * a.x * b.y - 1LL * a.y * b.x;
        }
        return abs(s) / 2.0;
    }

    bool contains(const Point &p) const
    {
        int cnt = 0;
        for (int i = 0; i < pts.size(); ++i)
        {
            Point a = pts[i], b = pts[(i + 1) % pts.size()];
            if (Segment(a, b).contains(p))
                return true;
            if ((a.y > p.y) != (b.y > p.y))
            {
                double x = (double)(b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x;
                if (x > p.x)
                    cnt++;
            }
        }
        return cnt % 2 == 1;
    }

    int countLatticePoints() const
    {
        long long area2 = 0;
        long long boundaryPoints = 0;
        int n = pts.size();

        for (int i = 0; i < n; ++i)
        {
            Point a = pts[i], b = pts[(i + 1) % n];
            area2 += 1LL * (a.x * b.y - a.y * b.x);
            boundaryPoints += __gcd(abs(a.x - b.x), abs(a.y - b.y));
        }

        area2 = abs(area2);
        long long interior = (area2 - boundaryPoints) / 2 + 1;
        return (int)(interior + boundaryPoints);
    }
};

int main()
{
    system("chcp 65001");
    // Tạo điểm
    Point A(0, 0), B(4, 4), C(0, 4), D(4, 0), P(2, 2), Q(5, 5);

    // Tạo vector
    Vector v = B - A;
    cout << "Vector AB: (" << v.x << ", " << v.y << ")\n";

    // Đoạn thẳng
    Segment s1(A, B);
    Segment s2(C, D);

    cout << "Độ dài đoạn AB: " << s1.length() << "\n";

    // Giao điểm hai đường thẳng
    auto ip = s1.intersectionPoint(s2);
    if (ip)
    {
        cout << fixed << setprecision(6);
        cout << "Giao điểm hai đường thẳng AB và CD: (" << ip->x << ", " << ip->y << ")\n";
    }
    else
    {
        cout << "Hai đường thẳng AB và CD không có giao điểm (song song hoặc trùng)\n";
    }

    // Kiểm tra điểm nằm trên đoạn
    cout << "Điểm P có nằm trên đoạn AB không? " << (s1.contains(P) ? "Có" : "Không") << "\n";
    cout << "Điểm Q có nằm trên đoạn AB không? " << (s1.contains(Q) ? "Có" : "Không") << "\n";

    // Kiểm tra hai đoạn có cắt nhau không
    cout << "Hai đoạn AB và CD có cắt nhau không? " << (s1.intersects(s2) ? "Có" : "Không") << "\n";

    // Tạo đa giác lồi: hình vuông (0,0) -> (4,0) -> (4,4) -> (0,4)
    vector<Point> polygonPoints = {
        Point(0, 0), Point(4, 0), Point(4, 4), Point(0, 4)};
    Polygon poly(polygonPoints);

    poly.makeConvexHull(); // Sắp xếp lại các điểm để thành đa giác lồi nếu cần

    // Tính chu vi, diện tích
    cout << "Chu vi đa giác: " << poly.perimeter() << "\n";
    cout << "Diện tích đa giác: " << poly.area() << "\n";

    // Kiểm tra điểm nằm trong đa giác
    cout << "Điểm P có nằm trong hoặc trên đa giác không? " << (poly.contains(P) ? "Có" : "Không") << "\n";
    cout << "Điểm Q có nằm trong hoặc trên đa giác không? " << (poly.contains(Q) ? "Có" : "Không") << "\n";

    // Đếm số điểm nguyên trong và trên cạnh của đa giác
    cout << "Số điểm nguyên nằm trong hoặc trên cạnh đa giác: " << poly.countLatticePoints() << "\n";

    return 0;
}
