// FunctionFactorial.cc
// Program to calculate factorial of a number with function call
#include <iostream>
using namespace std;
// Function declaration (prototype)
int Factorial(int M);
int main()
{
    int number=0, result;
    // User input must be an integer number between 1 and 10
    while(number<1 || number>10)
    {
        cout << "Integer number = ";
        cin >> number;
    }
    // Function call and assignment of return value to result
    result = Factorial(number);
    //Output result
    cout << "Factorial = " << result << endl;
    return 0;
}
// Function definition (header and body)
// An integer, M, is passed from caller function.
int Factorial(int M)
{
    int factorial=1;
    // Calculate the factorial with a FOR loop
    for(int i=1; i<=M; i++)
    {
        factorial = factorial*i;
    }
    return factorial; // This value is returned to caller
}
