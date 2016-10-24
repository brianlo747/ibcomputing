#include<cstdlib>
#include<iostream>
#include<cmath>

using namespace std;

int main(int argc, char* argv[])
{
    double n;
    double result = 0;
    printf("Your value of n: ");
    cin >> n;
    for (int i = 1; i <= 100; i++) {
        printf("%.10lf\n", result);
        result = n + 1/result ;
    }
}
