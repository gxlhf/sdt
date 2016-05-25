#include<iostream>
#include<string>
#include<vector>
#include"symbol_table.h"
using namespace std;

struct tokenOnValue
{
	int type;
	float value;
};

double convertToFloat(string str)
{
	return atof(str.c_str());
}

symbolTable symTab;
/*
vector<token> laxAnal(string input)
{
	while (input[p] != 0)
	{
		temp.name.clear();

		//过滤空格
		while (input[p] == ' ')
			p++;

		//识别元素
		if (input[p] <= '9' && input[p] >= '0')
		{
			temp.type = 1;
			while (input[p] <= '9' && input[p] >= '0')
				temp.name += input[p++];
			if (input[p] == '.')
			{
				temp.name += input[p++];
				while (input[p] <= '9' && input[p] >= '0')
					temp.name += input[p++];
			}	
			p--;
			symTab.insert(temp.name, 1);
		}
		else if (symTab.find(input[p]) != -1) temp.type = symTab.find(input[p]);
		else
		{
			cout << "You have inputed an incorrect expression!" << endl;
			output.clear();
			return output;
		}

		output.push_back(temp);
		p++;
	}
	return output;
}*/

vector<tokenOnValue> laxAnal(string input)
{
	int p = 0, state = 0;
	vector<tokenOnValue> output;
	token temp;
	tokenOnValue tempOnValue;
	char c;

	while (1)
	{
		switch (state)
		{
		case 0:{
				   c = input[p++];
				   temp.name.clear();
				   if (c <= '9' && c >= '0') 
				   {
					   state = 1; 
					   temp.name += c;					   
				   }
				   else
				   {
					   switch (c)
					   {
					   case '+': state = 6; break;
					   case '-': state = 7; break;
					   case '*': state = 8; break;
					   case '/': state = 9; break;
					   case '(': state = 10; break;
					   case ')': state = 11; break;
					   case ' ': state = 12; break;
					   case 0: goto done;
					   default: goto outLoop;
					   }
				   }
				   break;
			}
		case 1:{
				   c = input[p++];
				   if (c <= '9' && c >= '0')
				   {
					   state = 1; 
					   temp.name += c;
				   }
				   else if (c == '.')
				   {
					   state = 2;
					   temp.name += c;
				   }
				   else state = 4;
				   break;
			}
		case 2:{
				   c = input[p++];
				   if (c <= '9' && c >= '0')
				   {
					   state = 3; temp.name += c;
				   }
				   else goto outLoop;
				   break;
			}
		case 3:{
				   c = input[p++];
				   if (c <= '9' && c >= '0')
				   {
					   state = 1; temp.name += c;
				   }
				   else state = 5;
				   break;
			}
		case 4:{
				   temp.type = 1;
				   symTab.insert(temp);
				   tempOnValue.type = temp.type;
				   tempOnValue.value = atof(temp.name.c_str());
				   output.push_back(tempOnValue);
				   if (c == 0)
					   goto done;
				   else
				   {
					   state = 0;
					   p--;
				   }
				   break;
			}
		case 5:{
				   temp.type = 2;
				   symTab.insert(temp);
				   tempOnValue.type = temp.type;
				   tempOnValue.value = atof(temp.name.c_str());
				   output.push_back(tempOnValue);
				   if (c == 0)
					   goto done;
				   else
				   {
					   state = 0;
					   p--;
				   }
				   break;
			}
		case 6:{
				   temp.type = 3;
				   tempOnValue.type = temp.type;
				   tempOnValue.value = 0;
				   output.push_back(tempOnValue);
				   if (c == 0)
					   goto done;
				   else
					   state = 0;
				   break;
			}
		case 7:{
				   temp.type = 4;
				   tempOnValue.type = temp.type;
				   tempOnValue.value = 0;
				   output.push_back(tempOnValue);
				   if (c == 0)
					   goto done;
				   else
					   state = 0;
				   break;
			}
		case 8:{
				   temp.type = 5;
				   tempOnValue.type = temp.type;
				   tempOnValue.value = 0;
				   output.push_back(tempOnValue);
				   if (c == 0)
					   goto done;
				   else
					   state = 0;
				   break;
			}
		case 9:{
				   temp.type = 6;
				   tempOnValue.type = temp.type;
				   tempOnValue.value = 0;
				   output.push_back(tempOnValue);
				   if (c == 0)
					   goto done;
				   else
					   state = 0;
				   break;
			}
		case 10:{
					temp.type = 7;
					tempOnValue.type = temp.type;
					tempOnValue.value = 0;
					output.push_back(tempOnValue);
					if (c == 0)
						goto done;
					else
						state = 0;
					break;
			}
		case 11:{
					temp.type = 8;
					tempOnValue.type = temp.type;
					tempOnValue.value = 0;
					output.push_back(tempOnValue);
					if (c == 0)
						goto done;
					else
						state = 0;
					break;
			}
		case 12:{
					c = input[p++];
					if (c == ' ')
						state = 12;
					else
						state = 13;
					break;
			}
		case 13:{
					if (c == 0)
						goto done;
					else
					{
						state = 0;
						p--;
					}
						
					break;
			}
		}
	} 
done: 
	tempOnValue.type = 9;
	tempOnValue.value = 0;
	output.push_back(tempOnValue);
	return output;

	outLoop: //cout << "Error Expression! ";
	output.clear();
	return output;
}