#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

int main(int argc, char* argv[])
{
    int N;
    int sum = 0;
    int sumcheck = 0;

    cout << "N: ";
    cin >> N;

    for (int i = 1; i <= N; i++) {
        sum = sum + (2*i - 1);
    }

    cout << "The loop has calculated: " << sum << endl;

    sumcheck = pow(N,2);

    cout << "The formula has calculated: " << sumcheck << endl;

    if (sumcheck == sum) {
        cout << "You have passed the test!" << endl;
    }
    else {
        cout << "You have failed badly..." << endl;
    }

    return 0;
}
