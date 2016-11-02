//
//  Test.cpp
//  PartIB Computing Practicals
//
//  Created by Brian Lo on 31/10/2016.
//  Copyright © 2016 University of Cambridge. All rights reserved.
//

#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    double x,y;
    int outcome;
    x = ((double)random()/(1.0+(double)RAND_MAX));
    y = rand();
    outcome = ( x*x + y*y < 1.0 ) ? 1 : 0;
    printf("%.f",x);
    
    if (x*x + y*y < 1.0) {
        outcome = 1;
    } else {
        outcome = 0;
    }
    printf("%d\n",outcome);
}
