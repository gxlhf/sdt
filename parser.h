#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include"lax_anal.h"
using namespace std;

struct actItem
{
	char act ;//a = acc, e = error
	int val ;
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
	{  1,  3,  2  },
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
	{-1,-1}, 
	{3,0}, 
	{3,0},
	{1,0},
	{3,2},
	{3,2},
	{1,2},
	{3,1},
	{1,1}
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

bool parser(string input)
{
	vector<token> tokenArray = laxAnal(input);
	int tokenP = 0, state = 0;
	stack<int> sta;
	actItem actNow;

	if (!tokenArray.size())
		return 0;

	sta.push(0);

	while (1)
	{
		state = sta.top();
		actNow = getAction(state, tokenArray[tokenP].type);
		//cout << '(' << state << ", " << tokenArray[tokenP].type << ") = " << actNow.act << actNow.val << endl;
		if (actNow.act == 's')
		{
			sta.push(actNow.val);
			tokenP++;
		}
		else if (actNow.act == 'r')
		{
			for (int i = 0; i < expTab[actNow.val][0]; i++)
				sta.pop();
			sta.push(gotoTab[sta.top()][expTab[actNow.val][1]]);
		}
		else if (actNow.act == 'a')
			return 1;
		else
			return 0;
	}
}
