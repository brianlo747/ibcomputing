// SortReference.cc
// Program to sort two numbers using call by reference.
// Smallest number is output first.
#include <iostream>
using namespace std;
// Function prototype for call by reference
void swap(float &x, float &y);
int main()
{
    float a, b;
    cout << "Enter 2 numbers: " << endl;
    cin >> a >> b;
    if(a>b)
        swap(a,b);
    // Variable a contains value of smallest number
    cout << "Sorted numbers: ";
    cout << a << " " << b << endl;
    return 0;
}
// A function definition for call by reference
// The variables x and y will have their values changed.
void swap(float &x, float &y)
// Swaps x and y data of calling function
{
    float temp;
    temp = x;
    x = y;
    y = temp;
}
