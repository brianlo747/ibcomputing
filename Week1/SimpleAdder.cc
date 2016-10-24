// Program to add two integers typed by user at keyboard
#include <iostream>
using namespace std;

int main()
{
	float years, seconds;

	cout << "Enter years:" << endl;
	cin >> years;
    seconds = years * 31557600;
	cout << "In seconds, that is: " << seconds << endl;

	return 0;
}
