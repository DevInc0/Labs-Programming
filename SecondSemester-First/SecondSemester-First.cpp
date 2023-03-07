#include <iostream>

using namespace std;

int main()
{
	char* str = new char[256];
	char* str2 = new char[256];

	cout << "\nEnter:" << endl;

	cin.ignore();

	cin.getline(str, 256);

	cout << "\nEnter 2:" << endl;

	cin.getline(str2, 256);

	cout << str << " " << str2 << endl;

	// aboba
}