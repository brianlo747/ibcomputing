// Here begins file Multiples.cc
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
	int low;
	int high;
	int mul;
	
	cout << "Enter the minimum integer: ";
	cin >> low;
	
	cout << "Enter the maximum integer: ";
	cin >> high;
	
	cout << "Enter the integer you would like to output multiples of: ";
	cin >> mul;
	
	
	if (low % mul == 0) {
		cout << low << endl;
	}
	for (int i = low + (mul - (low % mul)); i <= high; i = i + mul) {
		cout << i << endl;
	}
	return 0;
}