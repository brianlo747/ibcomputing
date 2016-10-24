#include<cstdlib>
#include<iostream>
#include<cmath>

using namespace std;

int main(int argc, char* argv[])
{
    bool composite;

    for(int i = 2; i <= 1000 ; i++) {
        composite = false;
        int j = 2;
        while(j < i/2 + 1) {
            if((i % j) == 0) {
                composite = true;
            }
            j++;
        }
        if (!composite) {
            printf("%d\n", i);
        }
    }
}
