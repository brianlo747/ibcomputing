//
//  Random.cpp
//  PartIB Computing Practicals
//
//  Created by Brian Lo on 24/10/2016.
//  Copyright © 2016 University of Cambridge. All rights reserved.
//

#include<cmath>
#include<cstdlib>
#include<iostream>

using namespace std;

int main()
{
    srand(time(0));
    int a,b,c;
    b = -10;
    c = -1;
    
    clock_t begin = clock();
    
    for (int i = 1; i <= 20; i++) {
    a = 1 + rand() % 4;
    cout << a << endl;
    }
    
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << elapsed_secs << endl;
}
