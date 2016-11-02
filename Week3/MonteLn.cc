//  Here begins file MonteLn.cc
//
//  MonteLn.cc
//   usage:
//     MonteLn [<val> [<N> [<seed>]]]
//   example:
//     MonteLn          (Run with default values that calculates ln2, 100 iterations and seed value of 873469242)
//     MonteLn 10       (Runs and calculates ln10, with default values 100 iterations and seed value of 873469242)
//     MonteLn 30 8967  (Runs and calculates ln10, with 8967 iterations and default seed value of 873469242)
//     MonteLn 6.89 10000 86  (Runs and calculates ln6.89, with 10000 iterations and seed value of 86)

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#define ranf(min,max) \
(min + (max-min)*((double)random()/(1.0+(double)RAND_MAX)) ) // Uniform from interval [min,max) */

int main(int argc, char* argv[])
{
    int outcome;
    int N = 100;
    int count_in = 0;
    int seed=873469242;
    double val = 2.0;
    double fraction_in, error, fresult;
    bool isleft;
    
    if(argc>1)   {
        sscanf( argv[1], "%lf", &val ) ; // put the 1st command-line argument in x
        if(val <= 0) {
            printf("Do not attempt to break this simulation please...\n");
            return 0; // exits program if you attempt to ln(0) or ln(-ve)
        }
    }
    if(argc>2) {
        sscanf( argv[2], "%d", &N ) ; // put the 2nd command-line argument in N
    }
    if(argc>3) {
        sscanf( argv[3], "%d", &seed ) ; // put the 3nd argument in for seed value
    }
    // Write out a summary of parameters
    cout << "# " << argv[0] << " You are running the simulation for ln(" << val << ") N=" << N << " seed=" << seed << endl ;
    
    // Initialise random number generator
    srandom(seed);
    
    // Tests whether inputted val is less than e
    isleft = (val < exp(1.0));
    
    // Sets x bounds for random number generation
    double xmax = (isleft)  ? exp(1) : val;
    double xmin = (!isleft) ? exp(1) : val;
    
    // Sets y bounds for random number generation
    double ymax = 0;
    double ymin = 1/xmin;
    
    // Perform N experiments.
    for(int n=1; n<=N; n++) {
        // Randomly picks a point
        double x = ranf(xmin,xmax);
        double y = ranf(ymin,ymax);
        // Tests if point is under or outside 1/x curve
        outcome = ( y < 1.0/x ) ? 1 : 0 ;
        // Adds 1 to count_in if random point under 1/x curve, else adds 0
        count_in += outcome ;
        // Calculates fraction of points under curve
        fraction_in = static_cast<double>(count_in)/n;
        // Calculates esitmation of lnx after each iteration
        double result = isleft ? 1 - fraction_in/val * (exp(1.0)-val) : 1 + fraction_in/exp(1.0)*(val-exp(1.0));
        fresult = result;
        cout << "Location" << outcome << "\t" << x << "\t" << y << "\t"
        << count_in << "\t" << n << "\t" << result << endl;
    }
    error = abs(fresult - log(val)) * 100;
    printf("\nYour estimate of ln(%lf) is %lf.\n", val, fresult);
    printf("After %d iterations, your estimate is %.2f%% from its true value.\n", N, error);
    return 0;
}
