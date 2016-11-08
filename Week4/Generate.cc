#include<cstdlib>
#include<iostream>

#define ranf() \
((double)random()/(1.0+(double)RAND_MAX))

using namespace std;

void generate();
void printarray(int** mArray);

int Xdim, Ydim, mines;
int** mine_array;


int main(int argc, char* argv[]) {
    
    srand(time(NULL));
    
    Xdim = 10;
    Ydim = 10;
    mines = 20;
    
    generate();
    printarray(mine_array);
}

void printarray(int** mArray) {
    for (int i = 0; i < Xdim; ++i) {
        for (int j = 0; j < Ydim; ++j) {
            printf("%d ", mArray[i][j]);
        }
        printf("|\n");
    }
}

void generate() {
    int mx;
    int my;
    int mines_placed = 0;
    
    mine_array = new int*[Xdim];
    for(int i = 0; i < Xdim; ++i) {
        mine_array[i] = new int[Ydim];
    }
    
    for(int i = 0; i < Xdim; ++i) {
        for(int j = 0; j < Ydim; ++j) {
            mine_array[i][j] = 0;
        }
    }
    
    do
    {
        do
        {
            mx = random() % Xdim; // get a random row
            my = random() % Ydim; // get a random column
        } while (mine_array[mx][my] !=0 ); // do again if a mine is located there already
        mine_array[mx][my] = 1; // place a mine at location
        mines_placed++; // increase mine count
    } while (mines_placed < mines); // Keep doing this until we have the specified number of mines
}

