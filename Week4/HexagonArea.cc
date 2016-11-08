// HexagonValue.cc
// Program to calculate the area of a regular hexagon inscribed in a
// circle as sum of areas of 6 triangles by calling AreaTriangle()
#include <iostream>
using namespace std;
// AreaTriangle function prototype
float AreaTriangle(float base, float height);
int main()
{
    float side, segmentHeight, hexagonArea;
    float cosTheta = 0.866025;
    cout << "Program to calculate the area of a hexagon" << endl;
    cout << "Enter side of hexagon: ";
    cin >> side;
    // Base of triangle is equal to side, height is side*cos(30)
    segmentHeight = side*cosTheta;
    // Function returns area of segment. 6 segments for total area.
    hexagonArea = 6.0f * AreaTriangle(side,segmentHeight);
    cout << "Area of hexagon = " << hexagonArea << endl;
    return 0;
}
// AreaTriangle function definition
float AreaTriangle(float base, float height)
{
    float area;
    area = (base*height)/2.0f;
    return area;
}
