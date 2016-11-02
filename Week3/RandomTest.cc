//
//  RandomTest.cpp
//  PartIB Computing Practicals
//
//  Created by Brian Lo on 31/10/2016.
//  Copyright © 2016 University of Cambridge. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#define ranf(min,max) \
(min + (max-min)*((double)random()/(1.0+(double)RAND_MAX)) ) // Uniform from interval [min,max) */

int main(int argc, char* argv[])
{
    double testxmax = 0, testxmin = 100000000;
    double testymax = 0, testymin = 100000000;
    double val = 2;
    double setxmax = exp(1);
    double setxmin = val;
    double x,y;
    
    for (int i=1; i<= 10000; i++) {
        x = ranf(setxmin,setxmax);
        y = ranf(0,1/val);
        printf("%.5f, %.5f\n",x,y);
        testxmax = (x > testxmax) ? x : testxmax;
        testxmin = (x < testxmin) ? x : testxmin;
        testymax = (y > testymax) ? y : testymax;
        testymin = (y < testymin) ? y : testymin;
    }
    printf("xMax: %.10f\n",testxmax);
    printf("xMin: %.10f\n",testxmin);
    printf("yMax: %.10f\n",testymax);
    printf("yMin: %.10f\n",testymin);
}
