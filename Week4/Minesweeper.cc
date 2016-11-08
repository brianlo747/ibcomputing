#include<cstdlib>
#include<iostream>

#define ranf() \
((double)random()/(1.0+(double)RAND_MAX))

using namespace std;

void gamemenu();
void options();
void zeroarray(int** mArray);
void generate_mine_array();
void generate_open_array();
void generate_flag_array();
void generate_mark_array();
void generate_neighbour_array();
void printboard();
char tilechar(int i, int j);
void promptplayer();
void move();
void open(int i, int j);
void flag(int i, int j);
void mark(int i, int j);
int checkneighbours(int i, int j);
bool checkwin();
void play();
void printarray(int** mArray);

int Xdim, Ydim, totmines, mines_left, x, y;
int** mine_array;
int** open_array;
int** flag_array;
int** mark_array;
int** neighbour_array;
bool quit, dead;
char action;
char digits[] = {'0','1','2','3','4','5','6','7','8','9'};

int main(int argc, char* argv[])
{
    
    srand(time(NULL));
    
    gamemenu();
    options();
    generate_mine_array();
    
    generate_open_array();
    
    generate_flag_array();
    
    generate_mark_array();
    printarray(mine_array);
    printf("\n");
    printarray(open_array);
    printf("\n");
    printarray(flag_array);
    printf("\n");
    printarray(mark_array);
    printf("\n");
    generate_neighbour_array();
    play();
    return 0;
}

void gamemenu() {
    printf("Welcome to Minesweeper!\n");
}

void options() {
    
    int suggest_mines;
    
    printf("How would you like your board?\n");
    printf("Number of columns: ");
    scanf("%d",&Xdim);
    printf("Number of rows: ");
    scanf("%d",&Ydim);
    suggest_mines = 0.15625 * (Xdim * Ydim); //Minesweeper boards have around 15% of mines out of all squares
    printf("Number of mines on the board: (I suggest placing approximately %d mines)\n",suggest_mines);
    scanf("%d",&totmines);
    
}

void zeroarray(int** mArray) {
    
    // Takes in a pointer to a 2D array and zeros out all its elements
    
    for(int i = 0; i < Xdim; ++i) {
        for(int j = 0; j < Ydim; ++j) {
            mArray[i][j] = 0;
        }
    }
}

void generate_mine_array() {
    
    int mx;
    int my;
    int mines_placed = 0;
    
    //Generates 2D array
    mine_array = new int*[Xdim];
    for(int i = 0; i < Xdim; ++i) {
        mine_array[i] = new int[Ydim];
    }
    
    //Zeros out 2D array
    zeroarray(mine_array);
    
    do
    {
        do
        {
            mx = random() % Xdim; // random x coord
            my = random() % Ydim; // random y coord
        } while (mine_array[mx][my] !=0 ); // do again if a mine is located there already
        mine_array[mx][my] = 1; // place a mine at location
        mines_placed++; // increase mines_placed count
    } while (mines_placed < totmines); // Keep doing this until target number of mines placed
    
}


void printarray(int** mArray) {
    
    // Takes in a pointer to a 2D array and prints out its elements left to right first then top to bottom
    
    for (int j = 0; j < Ydim; ++j) {
        for (int i = 0; i < Xdim; ++i) {
            printf("%d ", mArray[i][j]);
        }
        printf("\n");
    }
}


void generate_open_array() {
    
    //Generates 2D array
    open_array = new int*[Xdim];
    for(int i = 0; i < Xdim; ++i) {
        open_array[i] = new int[Ydim];
    }
    
    //Zeros out 2D array
    zeroarray(open_array);
}

void generate_flag_array() {
    
    //Generates 2D array
    flag_array = new int*[Xdim];
    for(int i = 0; i < Xdim; ++i) {
        flag_array[i] = new int[Ydim];
    }
    
    //Zeros out 2D array
    zeroarray(flag_array);
}

void generate_mark_array() {
    
    //Generates 2D array
    mark_array = new int*[Xdim];
    for(int i = 0; i < Xdim; ++i) {
        mark_array[i] = new int[Ydim];
    }
    
    //Zeros out 2D array
    zeroarray(mark_array);
}

void generate_neighbour_array() {
    
    //Generates 2D array
    neighbour_array = new int*[Xdim];
    for(int i = 0; i < Xdim; ++i) {
        neighbour_array[i] = new int[Ydim];
    }
    
    //Zeros out 2D array
    zeroarray(neighbour_array);
    
    //Fills the array with neighbour information
    for(int i = 0; i < Xdim; ++i) {
        for(int j = 0; j < Ydim; ++j) {
            neighbour_array[i][j] = checkneighbours(i,j);
        }
    }
    
}

void printboard() {
    //     0  1  2  3  4  5  6  7  8  9  10 11 12
    // 0|  -  -  -  -  -  -  -  -  -  -  -  -  -  |0
    // 1|  -  -  -  -  -  -  -  -  -  -  -  -  -  |1
    // 2|  -  -  -  -  -  -  -  -  -  -  -  -  -  |2
    // 3|  -  -  -  -  -  -  -  -  -  -  -  -  -  |3
    // 4|  -  -  -  -  -  -  -  -  -  -  -  -  -  |4
    // 5|  -  -  -  -  -  -  -  -  -  -  -  -  -  |5
    // 6|  -  -  -  -  -  -  -  -  -  -  -  -  -  |6
    // 7|  -  -  -  -  -  -  -  -  -  -  -  -  -  |7
    // 8|  -  -  -  -  -  -  -  -  -  -  -  -  -  |8
    // 9|  -  -  -  -  -  -  -  -  -  -  -  -  -  |9
    //10|  -  -  -  -  -  -  -  -  -  -  -  -  -  |10
    //11|  -  -  -  -  -  -  -  -  -  -  -  -  -  |11
    //     0  1  2  3  4  5  6  7  8  9  10 11 12
    
    //Top line
    printf("\n");
    printf("     ");
    for(int i = 0; i<min(Xdim,10); ++i) {
        printf("%d  ",i);
    }
    for(int i = 10; i<Xdim; ++i) {
        printf("%d ",i);
    }
    printf("\n");
    
    //nth line
    for(int j = 0; j<min(Ydim,10); ++j) {
        printf(" %d|  ",j);
        for(int i = 0; i<Xdim; ++i) {
            char tile = tilechar(i,j);
            printf("%1c  ",tile);
        }
        printf("|%d\n",j);
    }
    for(int j = 10; j<Ydim; ++j) {
        printf("%d|  ",j);
        for(int i = 0; i<Xdim; ++i) {
            char tile = tilechar(i,j);
            printf("%1c  ",tile);
        }
        printf("|%d\n",j);
    }
    
    //Bottom line
    printf("     ");
    for(int i = 0; i<min(Xdim,10); ++i) {
        printf("%d  ",i);
    }
    for(int i = 10; i<Xdim; ++i) {
        printf("%d ",i);
    }
    printf("\n");
}

char tilechar(int i, int j) {
    
    //Checks status of tile (i,j) and returns char of tile
    
    if (open_array[i][j] == 0) {
        if (flag_array[i][j] == 1) {
            return 'F';
        }
        else if (mark_array[i][j] == 1) {
            return '?';
        } else {
            return '-';
        }
    } else {
        return digits[checkneighbours(i,j)];
    }

}

void promptplayer() {
    
    //Prompts the player for their next move
    
    printf("Your next move: ");
    cin >> action;
    if (action == 'q') {
        quit = true;
        return;
    }
    scanf(" %d %d", &x, &y);
}

void move() {
    if (action == 'o') {
        action = ' ';
        open(x,y);
    }
    else if (action == 'f') {
        action = ' ';
        flag(x,y);
    }
    else if (action == 'm') {
        action = ' ';
        mark(x,y);
    } else {
        action = ' ';
        promptplayer();
    }
}

void open(int i, int j) {
    
    int di[] = {-1,0,1,1,1,0,-1,-1};
    int dj[] = {1,1,1,0,-1,-1,-1,0};
    
    if (mine_array[i][j] == 1) {
        dead = true;
    } else {
        open_array[i][j] = 1;
    }
}

void flag(int i, int j) {
    
    flag_array[i][j] = abs(flag_array[i][j] - 1);
    mark_array[i][j] = 0;
    
}

void mark(int i, int j) {
    
    mark_array[i][j] = abs(mark_array[i][j] - 1);
    flag_array[i][j] = 0;
    
}

int checkneighbours(int i, int j) {
    
    int neighbours = 0;
    int di[] = {-1,0,1,1,1,0,-1,-1};
    int dj[] = {1,1,1,0,-1,-1,-1,0};
    
    for (int e = 0; e <= 7; ++e) {
        if (i+di[e]>=0 && i+di[e]<(Xdim-1) && j+dj[e]>=0 && j+dj[e]<(Ydim-1) && mine_array[i+di[e]][j+dj[e]] == 1) {
            neighbours++;
        }
    }
    return neighbours;
}

bool checkwin() {
    
    bool result = true;
    
    for(int i = 0; i < Xdim; ++i) {
        for(int j = 0; j < Ydim; ++j) {
            if (result) {
                result = (flag_array[i][j] == mine_array[i][j]);
            } else {
                return false;
            }
        }
    }
    return true;
}

void play() {
    
    do {
        printboard();
        if (checkwin()) {
            break;
        }
        promptplayer();
        if (quit == true) {
            break;
        }
        move();
        if (dead == true) {
            break;
        }
    } while (
        dead == false || !checkwin()
    );
    
    if (checkwin()) {
        printf("YOU DID IT!\n");
    } else {
        printf("BOOOM! GAME OVER!\n");
    }
}

