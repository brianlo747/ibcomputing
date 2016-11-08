#include<cstdlib>
#include<iostream>

using namespace std;

double squarefunc(double x, double y);

int main(int argc, char* argv[]) {
    double upper = 100;
    double lower = 1;
    double tol = 0.0001;
    double input, error, mid;
    double upper_y, mid_y, lower_y;
    
    error = upper - lower;
    
    printf("Enter the number you would like to find the square root of: ");
    cin >> input;
    while (error > tol) {
        mid = 0.5 * (upper + lower);
        upper_y = squarefunc(upper, input);
        mid_y = squarefunc(mid, input);
        lower_y = squarefunc(lower, input);
        lower = ( (upper_y * mid_y) < 0) ? mid : lower;
        upper = ( (lower_y * mid_y) < 0) ? mid : upper;
        error = upper - lower;
        printf("%.10f\n",mid);
    }
}

double squarefunc(double x, double y) {
    return x*x - y;
}
