#include "ReadFile.h"

void main()
{
	string fileName = "", str = "";
	ifstream input, input2;

	cout << "Enter name of file to read: ";
	cin >> fileName;

	try
	{
		input.open(fileName);
		if (!input)
			throw fileException();
	}
	catch (fileException)
	{
	}

	input2.open(fileName);
	input2 >> str;
	while (input2)
	{
		cout << str << " ";
		if (input.eof())
			break;
		input2 >> str;
	}

	cout << endl << endl;

	ReadFile file(fileName);

	system("pause");
}