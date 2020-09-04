#include <iostream>
#include <cmath>

using namespace std;

const double eps = 1e-6;
const int N = 4;

struct Puncte {
    double x, y;
};
Puncte p[N + 1];

double get_dist(Puncte p1, Puncte p2) {
    return (p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x);
}

double get_cos(Puncte o, Puncte p1, Puncte p2) {
    double dop1 = get_dist(o, p1);
    double dop2 = get_dist(o, p2);
    double dp1p2 = get_dist(p1, p2);

    return (dop1 + dop2 - dp1p2) / (2.0 * sqrt(dop1 * dop2));
}

int main() {
    for (int i = 1; i <= N; ++i)
    {
        cout << "Introduceti datele pentru punctul " << i << " :\n";
        cout << "X: ";
        cin >> p[i].x;
        cout << "Y: ";
        cin >> p[i].y;
    }

    double cos2 = get_cos(p[2], p[1], p[3]);
    double cos4 = get_cos(p[4], p[1], p[3]);

    if (abs(cos2 + cos4) < eps) {
        cout << "Punctul A4(" << p[4].x << ", " << p[4].y << ") este pe cerc!\n";
    }
    else if (cos2 + cos4 < -eps) {
        cout << "Punctul A4(" << p[4].x << ", " << p[4].y << ") este in interiorul cercului!\n";
    }
    else {
        cout << "Punctul A4(" << p[4].x << ", " << p[4].y << ") este in exteriorul cercului!\n";
    }

    double d1 = get_dist(p[1], p[2]) + get_dist(p[3], p[4]);
    double d2 = get_dist(p[1], p[4]) + get_dist(p[2], p[3]);

    if (abs(d1 - d2) < eps) {
        cout << "Patrulaterul este circumscriptibil!\n";
    }
    else {
        cout << "Patrulaterul nu este circumscriptibil!\n";
    }

    return 0;
}