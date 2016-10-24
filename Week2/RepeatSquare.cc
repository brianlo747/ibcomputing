#include<cstdlib>
#include<iostream>
#include<cmath>

using namespace std;

int main(int argc, char* argv[])
{
    double result = sqrt(1);
    for(int i = 1; i <= 20; i++) {
        printf("%.10lf\n", result);
        result = sqrt(1+result);
    }

    return 0;
}
