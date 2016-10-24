#include<cmath>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include <chrono>

using namespace std;

int main(int argc, char* argv[])
{
    int choice;
    int fchoice = 0;
    int lower, upper, a, b, q, attempts, score;
    double percent, elapsed_secs;
    char again = 'y';
    
    srand(time(0));
    while(again == 'y') {
        score = 0;
        attempts = 0;
        printf("\nWelcome to the program that would (supposedly) improve your arithmetic!\n");
        printf("What would you like to do today?\n\n");
        printf("   1. Addition\n");
        printf("   2. Subtraction\n");
        printf("   3. Multiplication\n");
        printf("   4. Division\n");
        printf("   5. Mixed Challenge\n");
        printf("   6. Take a break\n\n");
        printf("Your option: ");
        
        cin >> choice;
        while(choice > 6 or choice < 1) {
            cin.clear();
            choice = 0;
            printf("I am asking for an integer from 1 to 5 inclusive...\n\n");
            printf("Your option: ");
            cin >> choice;
        }
        printf("\n");
        
        if (choice == 6) {
            printf("You are lazy... Bye!\n");
            return 0;
        }
        if (choice >= 1 && choice <= 4) {fchoice = choice;}
        
        printf("Specify a range of POSITIVE integers you would like to practice with.\n\n");
        printf("Lower range: ");
        while(!(cin >> lower)){
            cout << "Bad value!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printf("Lower range: ");
        }
        printf("Upper range: ");
        while(!(cin >> upper)){
            cout << "Bad value!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printf("Upper range: ");
        }
        while(lower >= upper) {
            cin.clear();
            upper = -1;
            printf("Can't you even see that your upper limit should be higher than your lower limit?\n");
            printf("Upper range: ");
            cin >> upper;
        }
        printf("\nHow many problems would you like?\n\n");
        printf("Number of problems: ");
        while(!(cin >> q)){
            cout << "Bad value!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printf("Number of problems: ");
        }
        printf("\nHit any key when you are ready to start the timer!");
        getchar();
        getchar();
        
        auto t_start = chrono::high_resolution_clock::now();
        
        for (int i = 1; i <= q; i++) {
            if (choice == 5) {
                fchoice = 1 + rand() % 4;
            }
            printf("\n");
            printf("\n\nProblem Number %d:\n\n" , i);
            switch(fchoice) {
                case 1:
                {
                    int response;
                    int answer;
                    a = lower + rand() % (upper - lower + 1);
                    b = lower + rand() % (upper - lower + 1);
                    while (a + b > upper) {
                        a = lower + rand() % (upper - lower + 1);
                        b = lower + rand() % (upper - lower + 1);
                    }
                    answer = a + b;
                    printf("What is %d + %d?\n" , a, b);
                    cin >> response;
                    if (response == answer) {
                        score++;
                        printf("Correct!");
                    } else {
                        printf("Incorrect!");
                    }
                    attempts++;
                    percent = (double) score / attempts * 100;
                    printf(" Score: %d out of %d, %.1f%%",score,attempts,percent);
                    break;
                }
                case 2:
                {
                    int response;
                    int answer;
                    a = lower + rand() % (upper - lower + 1);
                    b = lower + rand() % (upper - lower + 1);
                    while (a < b or a - b < lower) {
                        a = lower + rand() % (upper - lower + 1);
                        b = lower + rand() % (upper - lower + 1);
                    }
                    answer = a - b;
                    printf("What is %d - %d?\n" , a, b);
                    cin >> response;
                    if (response == answer) {
                        score++;
                        printf("Correct!");
                    } else {
                        printf("Incorrect!");
                    }
                    attempts++;
                    percent = (double) score / attempts * 100;
                    printf(" Score: %d out of %d, %.1f%%",score,attempts,percent);
                    break;
                }
                case 3:
                {
                    int response;
                    int answer;
                    a = lower + rand() % (upper - lower + 1);
                    b = lower + rand() % (upper - lower + 1);
                    while (a * b > upper) {
                        a = lower + rand() % (upper - lower + 1);
                        b = lower + rand() % (upper - lower + 1);
                    }
                    answer = a * b;
                    printf("What is %d \u00D7 %d?\n" , a, b);
                    cin >> response;
                    if (response == answer) {
                        score++;
                        printf("Correct!");
                    } else {
                        printf("Incorrect!");
                    }
                    attempts++;
                    percent = (double) score / attempts * 100;
                    printf(" Score: %d out of %d, %.1f%%",score,attempts,percent);
                    break;
                }
                case 4:
                {
                    double response;
                    double answer;
                    a = lower + rand() % (upper - lower + 1);
                    b = lower + rand() % (upper - lower + 1);
                    while (a / b < lower or b == 0) {
                        a = lower + rand() % (upper - lower + 1);
                        b = lower + rand() % (upper - lower + 1);
                    }
                    answer = (double) a / b;
                    printf("What is %d \u00F7 %d?\nPlease round your answer to 1 decimal place.\n" , a, b);
                    cin >> response;
                    if (abs(response - answer) <= 0.1) {
                        score++;
                        printf("Correct!");
                    } else {
                        printf("Incorrect!");
                    }
                    attempts++;
                    percent = (double) score / attempts * 100;
                    printf(" Score: %d out of %d, %.1f%%",score,attempts,percent);
                    break;
                }
            }
        }
        
        auto t_end = chrono::high_resolution_clock::now();
        elapsed_secs = chrono::duration<double>(t_end-t_start).count();
        printf("\n\nWell Done! You have completed %d questions and got %d of them correct in just under %.2f seconds!\n\n",q,score,elapsed_secs);
        printf("Would you like to return to the main menu? (y/n)");
        while(!(cin >> again)){
            cout << "You did not enter a character!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printf("Would you like to return to the main menu? (y/n)");
        }
        while(again != 'y' and again != 'n') {
            cin.clear();
            again = 'y';
            printf("Answer my question!\n");
            printf("Would you like to return to the main menu? (y/n)");
            cin >> again;
        }
    }
    printf("Bye!\n");
    return 0;
}
