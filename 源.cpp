#include"sdt.cpp"
using namespace std;

int main()
{
	//string input;
	string input[14] = {
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
		"1*(2+3)"
	};
	/*while (1){
	getline(cin, input);

	if (parser(input))
	cout << "Accept";
	else
	cout << "Error";

	cout << endl;
	}*/

	for (int i = 0; i < 14; i++)
	{
		cout << input[i] << endl;
		sdt(input[i]);
		cout << endl << "===========" << endl;
	}

	system("pause");
}