#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include"lax_anal.h"
using namespace std;

struct actItem
{
	char act;//a = acc, e = error
	int val;
};

actItem actionTab[16][8] =
{
	/*   +   0  ||   -   1   ||   *   2  ||    /   3  ||   (   4  ||    )   5  ||  id   6   ||   $   7    */
	{ { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 's', 4 }, { 'e', 0 }, { 's', 5 }, { 'e', 0 } },
	{ { 's', 6 }, { 's', 7 }, { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 'a', 0 } },
	{ { 'r', 3 }, { 'r', 3 }, { 's', 8 }, { 's', 9 }, { 'e', 0 }, { 'r', 3 }, { 'e', 0 }, { 'r', 3 } },
	{ { 'r', 6 }, { 'r', 6 }, { 'r', 6 }, { 'r', 6 }, { 'e', 0 }, { 'r', 6 }, { 'e', 0 }, { 'r', 6 } },
	{ { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 's', 4 }, { 'e', 0 }, { 's', 5 }, { 'e', 0 } },
	{ { 'r', 8 }, { 'r', 8 }, { 'r', 8 }, { 'r', 8 }, { 'e', 0 }, { 'r', 8 }, { 'e', 0 }, { 'r', 8 } },
	{ { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 's', 4 }, { 'e', 0 }, { 's', 5 }, { 'e', 0 } },
	{ { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 's', 4 }, { 'e', 0 }, { 's', 5 }, { 'e', 0 } },
	{ { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 's', 4 }, { 'e', 0 }, { 's', 5 }, { 'e', 0 } },
	{ { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 's', 4 }, { 'e', 0 }, { 's', 5 }, { 'e', 0 } },
	{ { 's', 6 }, { 's', 7 }, { 'e', 0 }, { 'e', 0 }, { 'e', 0 }, { 's', 15 }, { 'e', 0 }, { 'e', 0 } },
	{ { 'r', 1 }, { 'r', 1 }, { 's', 8 }, { 's', 9 }, { 'e', 0 }, { 'r', 1 }, { 'e', 0 }, { 'r', 1 } },
	{ { 'r', 2 }, { 'r', 2 }, { 's', 8 }, { 's', 9 }, { 'e', 0 }, { 'r', 2 }, { 'e', 0 }, { 'r', 2 } },
	{ { 'r', 4 }, { 'r', 4 }, { 'r', 4 }, { 'r', 4 }, { 'e', 0 }, { 'r', 4 }, { 'e', 0 }, { 'r', 4 } },
	{ { 'r', 5 }, { 'r', 5 }, { 'r', 5 }, { 'r', 5 }, { 'e', 0 }, { 'r', 5 }, { 'e', 0 }, { 'r', 5 } },
	{ { 'r', 7 }, { 'r', 7 }, { 'r', 7 }, { 'r', 7 }, { 'e', 0 }, { 'r', 7 }, { 'e', 0 }, { 'r', 7 } }
};

int gotoTab[16][3] =
{
	/*  0    1   2   */
	/*  E    F   T   */
	{ 1, 3, 2 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ 10, 3, 2 },
	{ -1, -1, -1 },
	{ -1, 3, 11 },
	{ -1, 3, 12 },
	{ -1, 13, -1 },
	{ -1, 14, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 }
};

int expTab[9][3] =
{
	    /*pop goto*/
	/*0*/{ -1, -1 },
	/*1*/{ 3, 0 },//E -> E + T
	/*2*/{ 3, 0 },//E -> E - T
	/*3*/{ 1, 0 },//E -> T
	/*4*/{ 3, 2 },//T -> T * F
	/*5*/{ 3, 2 },//T -> T / F
	/*6*/{ 1, 2 },//T -> F
	/*7*/{ 3, 1 },//F -> (E)
	/*8*/{ 1, 1 } //F -> id
};



actItem getAction(int s, int a)
{
	if (s == -1)
		return{ 'e', 0 };

	if (a == 1 || a == 2)
		a = 6;
	else if (a == 9)
		a = 7;
	else
		a = a - 3;
	return actionTab[s][a];
}


class valueStack
{
public:
	valueStack(){}
	void push(float value)
	{
		elem.push_back(value);
		size++;
		if (size!=elem.size())
		{
			cout << "size!=elem.size()";
		}
	}
	float& operator[](int posFromTop)
	{
		return elem[size - posFromTop - 1];
	}
	void pop(int count)
	{
		elem.erase(elem.end() - count, elem.end());
		size -= count;
		if (size != elem.size())
		{
			cout << "size!=elem.size()";
		}
	}

private:
	vector<float> elem;
	int size = 0;
};

valueStack values;

void modifyStackOnR(int exp)
{
	switch (exp)
	{
	case 1:values[2] = values[2] + values[0]; values.pop(2); break;
	case 2:values[2] = values[2] - values[0]; values.pop(2); break;
	case 3:break;
	case 4:values[2] = values[2] * values[0]; values.pop(2); break;
	case 5:values[2] = values[2] / values[0]; values.pop(2); break;
	case 6:break;
	case 7:values[2] = values[1]; values.pop(2); break;
	case 8:break;
	default:cout << "error occured in modifyStackOnR"; exit(1);
		break;
	}
}

void sdt(string input)
{
	vector<tokenOnValue> tokenArray = laxAnal(input);
	int tokenP = 0, state = 0;
	stack<int> sta;
	actItem actNow;

	if (!tokenArray.size())
	{
		cout << "Unacceptable words!";
		return;
	}

	sta.push(0);

	while (1)
	{
		state = sta.top();
		actNow = getAction(state, tokenArray[tokenP].type);
		//cout << '(' << state << ", " << tokenArray[tokenP].type << ") = " << actNow.act << actNow.val << endl;
		if (actNow.act == 's')
		{
			sta.push(actNow.val);
			values.push(tokenArray[tokenP].value);
			tokenP++;
		}
		else if (actNow.act == 'r')
		{
			for (int i = 0; i < expTab[actNow.val][0]; i++)
				sta.pop();
			modifyStackOnR(actNow.val);
			sta.push(gotoTab[sta.top()][expTab[actNow.val][1]]);
		}
		else if (actNow.act == 'a')
		{
			/*cout final result here*/
			cout << values[0];
			return;
		}
		else
		{
			cout << "Error expersion!";
			return;
		}
	}
}
