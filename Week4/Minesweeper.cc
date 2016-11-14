#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<ctime>

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
void reveal(int** mArray);
bool isoption(char mOptionChar);

int Xdim, Ydim, totmines, mines_left, x, y;
int** mine_array;
int** open_array;
int** flag_array;
int** mark_array;
int** neighbour_array;
bool quit, dead;
char action;
char digits[] = {'0','1','2','3','4','5','6','7','8','9'};
char optionchars[] = {'o','f','q','m'};

int main(int argc, char* argv[])
{
    
    srand(time(NULL));
    
    gamemenu();
    options();
    generate_mine_array();
    generate_open_array();
    generate_flag_array();
    generate_mark_array();
    // Use if you would like to cheat or test the game!
    // printarray(mine_array);
    // printf("\n");
    generate_neighbour_array();
    play();
    return 0;
}

void gamemenu() {
    
    // Runs the introductory game menu
    
    int readcheck = rand() % 10;
    int human;
    
    printf("Welcome to Minesweeper!\n");
    printf("Please enlarge your screen for the best gaming experience.\n\n");
    printf("Rules:\n");
    printf("Opening a square without a mine will show you a number, indicating the number of mines in the 8 adjacent squares. To win the game, you will have to flag all correct squares that genuinely contain a mine, without opening the square itself! The mark function is there to help you with your guesses only, it does not contribute to winning or losing. If you happen to open a square with a mine on it, you will immediately lose the game...\n\n");
    
    printf("Instructions: When asked for your next move\n");
    printf("Type o x y to open square at column x, row y.\n");
    printf("Type f x y to flag square at column x, row y.\n");
    printf("Type m x y to mark square at column x, row y.\n");
    printf("Replace x and y with integers.\n");
    printf("In the unfortunate case where you find Minesweeper too stressful, type q when asked for your next move.\n\n");
    
    printf("If you have read and agreed to all the above, enter the digit %d, then press enter : ", readcheck);
    cin >> human;
    while (readcheck != human) {
        readcheck = rand() % 10;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printf("You did not read and agree to the instructions! Read, agree and type in the digit %d, before pressing enter : ", readcheck);
        cin >> human;
    }
    printf("\nGood luck!\n\n");
}

void options() {
    
    // Interface that prompts the user to set up their board
    
    int suggest_mines;
    
    printf("How would you like your board?\n");
    printf("Number of columns between 1 and 99: ");
    cin >> Xdim;
    while (Xdim < 1 || Xdim > 99) {
        cin.ignore();
        cin.clear();
        printf("Try again! Number of columns between 1 and 99: ");
        cin >> Xdim;
    }
    printf("Number of rows between 1 and 99: ");
    cin >> Ydim;
    while ((Ydim < 1 || Ydim > 99)) {
        cin.ignore();
        cin.clear();
        printf("Try again! Number of rows between 1 and 99: ");
        cin >> Ydim;
    }
    suggest_mines = 0.15625 * (Xdim * Ydim); //Minesweeper boards have around 15% of mines out of all squares
    printf("Number of mines on the board: (I suggest placing approximately %d mines)\n",suggest_mines);
    cin >> totmines;
    while (totmines < 1 || totmines > Xdim*Ydim) {
        cin.ignore();
        cin.clear();
        printf("Try again! Number of mines on the board: (I suggest placing approximately %d mines)\n",suggest_mines);
        cin >> totmines;
    }
    
    mines_left = totmines;
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
    
    // Generates 2D array of mines
    
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
            mx = rand() % Xdim; // random x coord
            my = rand() % Ydim; // random y coord
        } while (mine_array[mx][my] !=0 ); // do again if a mine is located there already
        mine_array[mx][my] = 1; // place a mine at location
        mines_placed++; // increase mines_placed count
    } while (mines_placed < totmines); // Keep doing this until target number of mines placed
    
}

void printarray(int** mArray) {
    
    // Only used for beta-testing. See printboard() for the equivalent function in-game
    // Takes in a pointer to a 2D array and prints out its elements left to right first then top to bottom
    
    for (int j = 0; j < Ydim; ++j) {
        for (int i = 0; i < Xdim; ++i) {
            printf("%d ", mArray[i][j]);
        }
        printf("\n");
    }
}

void generate_open_array() {
    
    // Generates 2D array of whether a square is open
    
    open_array = new int*[Xdim];
    for(int i = 0; i < Xdim; ++i) {
        open_array[i] = new int[Ydim];
    }
    
    //Zeros out 2D array
    zeroarray(open_array);
}

void generate_flag_array() {
    
    // Generates 2D array of whether a square is flagged
    
    flag_array = new int*[Xdim];
    for(int i = 0; i < Xdim; ++i) {
        flag_array[i] = new int[Ydim];
    }
    
    //Zeros out 2D array
    zeroarray(flag_array);
}

void generate_mark_array() {
    
    // Generates 2D array of whether a square is marked
    
    //Generates 2D array
    mark_array = new int*[Xdim];
    for(int i = 0; i < Xdim; ++i) {
        mark_array[i] = new int[Ydim];
    }
    
    //Zeros out 2D array
    zeroarray(mark_array);
}

void generate_neighbour_array() {
    
    // Generates 2D array for calculating number of adjacent mines
    
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
    
    // Prints a nice looking board for the game
    
    //     0  1  2  3  4  5  6  7  8  9  10 11 12
    //
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
    //
    //     0  1  2  3  4  5  6  7  8  9  10 11 12
    //
    // Flags Left :
    
    //Top line
    printf("\n");
    printf("     ");
    for(int i = 0; i<min(Xdim,10); ++i) {
        printf("%d  ",i);
    }
    for(int i = 10; i<Xdim; ++i) {
        printf("%d ",i);
    }
    printf("\n\n");
    
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
    printf("\n     ");
    for(int i = 0; i<min(Xdim,10); ++i) {
        printf("%d  ",i);
    }
    for(int i = 10; i<Xdim; ++i) {
        printf("%d ",i);
    }
    printf("\n\n");
    
    //Mines Left line
    printf("   Flags Left : %d\n", mines_left);
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

    printf("\nYour next move: ");
    cin >> action;
    while (!isoption(action)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printf("Try again!\nYour next move: ");
        cin >> action;
    }
    if (action == 'q') {
        quit = true;
        return;
    }
    scanf(" %d %d", &x, &y);
    while (!(x >= 0 && x < Xdim && y >= 0 && y < Ydim)) {
        fflush(stdin);
        printf("Try again! ");
        promptplayer();
    }
    
}

void move() {
    
    // Executes the move
    
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
    }
}

void open(int i, int j) {
    
    // Opens the specified square and cascades if there are no neighbours
    
    int di[] = {0,1,0,-1};
    int dj[] = {1,0,-1,0};
    
    if (mine_array[i][j] == 1) {
        dead = true;
    } else {
        if (flag_array[i][j] == 1) {
            printf("Unflag before opening!\n");
            return;
        }
        if (mark_array[i][j] == 1) {
            printf("Unmark before opening!\n");
            return;
        }
        open_array[i][j] = 1;
        if (neighbour_array[i][j] == 0) {
            for (int e = 0; e <= 3; ++e) {
                if (i+di[e]>=0 && i+di[e]<Xdim && j+dj[e]>=0 && j+dj[e]<Ydim && neighbour_array[i][j] == 0 && open_array[i+di[e]][j+dj[e]] == 0) {
                    open(i+di[e],j+dj[e]);
                }
            }
        }
    }
}

void flag(int i, int j) {
    
    // Flags a specified square
    
    if (mines_left <= 0) {
        printf("You have run out of flags! Please remove a flag before placing this one...\n");
        return;
    }
    if (flag_array[i][j] == 1) {
        flag_array[i][j] = 0;
        ++mines_left;
    } else {
        mark_array[i][j] = 0;
        flag_array[i][j] = 1;
        --mines_left;
    }
}

void mark(int i, int j) {
    
    // Marks a specified square
    
    mark_array[i][j] = abs(mark_array[i][j] - 1);
    if (flag_array[i][j] == 1) {
        flag_array[i][j] = 0;
        ++mines_left;
    }
}

int checkneighbours(int i, int j) {
    
    // Calculates the number of adjacent mines for a specified square and returns it
    
    int neighbours = 0;
    int di[] = {-1,0,1,1,1,0,-1,-1};
    int dj[] = {1,1,1,0,-1,-1,-1,0};
    
    for (int e = 0; e <= 7; ++e) {
        if (i+di[e]>=0 && i+di[e]<=(Xdim-1) && j+dj[e]>=0 && j+dj[e]<=(Ydim-1) && mine_array[i+di[e]][j+dj[e]] == 1) {
            neighbours++;
        }
    }
    return neighbours;
}

void reveal(int** mArray) {
    
    // Takes in a pointer to a 2D array and prints out X if the array element is 1
    
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
            if (mine_array[i][j]==1) {
                printf("X  ");
            } else {
                printf("-  ");
            }
        }
        printf("|%d\n",j);
    }
    for(int j = 10; j<Ydim; ++j) {
        printf("%d|  ",j);
        for(int i = 0; i<Xdim; ++i) {
            if (mine_array[i][j]==1) {
                printf("X  ");
            } else {
                printf("-  ");
            }
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

bool isoption(char mOptionChar) {
    
    // Checks whether user input mOptionChar is a valid option and returns true if it is, else false
    
    for (int i = 0; i < sizeof(optionchars); ++i) {
        if (mOptionChar == optionchars[i]) {
            return true;
        }
    }
    return false;
}

bool checkwin() {
    
    // Checks the winning condition
    
    bool result = true;
    
    for(int i = 0; i < Xdim; i++) {
        for(int j = 0; j < Ydim; j++) {
            if (result) {
                result = (mine_array[i][j] == flag_array[i][j]);
            } else {
                return false;
            }
        }
    }
    return result;
}

void play() {
    
    // Gameloop, while running checks on winning and losing conditions. Breaks out of the game loop if either occurs
    
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
    } while (true);
    if (checkwin()) {
        printf("\nYOU DID IT!\n");
    } else {
        printf("\nBOOOM! GAME OVER!\n");
    }
    reveal(mine_array);
}

