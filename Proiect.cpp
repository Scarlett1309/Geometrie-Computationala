#include <iostream> 
#include <stack> 
#include <stdlib.h> 
using namespace std;

struct Point
{
    int x, y;
};

Point p0;

//functie care sa gaseasca urmatorul element din stiva 
Point nextToTop(stack<Point>& S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

void swap(Point& p1, Point& p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
        (p1.y - p2.y) * (p1.y - p2.y);
}

// Pentru a gasi orientarea tripletului ordonat, functia returneaza :  
// 0 --> p, q si r sunt coliniare 
// 1 --> in sensul acelor de ceas 
// 2 --> in sensul opus 
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// functie pt sortarea vectorului de puncte 
int compare(const void* vp1, const void* vp2)
{
    Point* p1 = (Point*)vp1;
    Point* p2 = (Point*)vp2;

    // Find orientation 
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

//afiseaza acoperirea convexa a poligonului dat
void convexHull(Point points[], int n)
{
    // gasim cel mai de jos punct
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;

        //alegem cel mai de jos punct
        //sau cel mai din stanga in caz ca sunt mai multe puncte situate in jos
        if ((y < ymin) || (ymin == y &&
            points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Plasam punctul pe prima pozitie 
    swap(points[0], points[min]);

    // Sortam cele n-1 puncte in comparatie cu primul punct

    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    //daca unul sau mai multe puncte fac acelasi unghi cu p0, stergem punctele, mai putin cel mai departat punct fata de p0
    // Remember that, in above sorting, our criteria was 
    // to keep the farthest point at the end when more than 
    // one points have same angle. 
    int m = 1; // marimea noului vector de puncte 
    for (int i = 1; i < n; i++)
    {
        //stergem punctul i cat timp unghiul lui i si i+1 este acelasi in comparatie cu p0

        while (i < n - 1 && orientation(p0, points[i],
            points[i + 1]) == 0)
            i++;


        points[m] = points[i];
        m++;  // updatam marimea vectorului
    }

    // daca vectorul modificat are mai putin de 3 puncte, acoperirea convexa nu este posibila
    if (m < 3) return;

    // adaugam primele 3 puncte in stiva
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // ultimele m-3 puncte ramase
    for (int i = 3; i < m; i++)
    {
        //continuam sa stergem elemente din top-ul stivei,  
        // cat timp unghiul format intre punctele nextToTop, top si points[i](punctul anterior, curent si urmator)
        //  nu vireaza la dreapta
        while (orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    // acum stiva are punctele finale ale acoperirii convexe si putem sa le afisam
    cout << "Acoperirea convexa a poligonului dat, este: " << endl;
    while (!S.empty())
    {
        Point p = S.top();
        cout << "(" << p.x << ", " << p.y << ")" << endl;
        S.pop();
    }
}

int main()
{
    Point points[] = { {0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3} };
    int n = sizeof(points) / sizeof(points[0]);
    convexHull(points, n);
    return 0;
}