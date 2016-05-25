#include"sdt.h"
using namespace std;

int main()
{
	//string input;
	string input[15] = {
		"1+2",
		"1*2",
		"(1+2)*3",
		"1*(2+3)",
		"1/(2+3)",
		"1+(2+3)",
		"1-(2+3)",
		"1",
		"1*",
		"1*(",
		"1*(2",
		"1*(2+",
		"1*(2+3",
		"1*(2+3)",
		"1n"
	};
	/*while (1){
	getline(cin, input);

	if (parser(input))
	cout << "Accept";
	else
	cout << "Error";

	cout << endl;
	}*/

	for (int i = 0; i < 15; i++)
	{
		cout << input[i] << endl;
		sdt(input[i]);
		cout << endl << "===========" << endl;
	}
	/*
	valueStack test;
	test.push(1);
	test.push(2);
	test.push(3);
	test.push(4);
	cout << test[0];
	test.pop(3);*/


	system("pause");
}