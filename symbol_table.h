#include<hash_map>
#include<string>
using namespace std;

struct token
{
	int type;
	string name;
};

class symbolTable
{
public:
	symbolTable();
	void insert(string name, int type);
	void insert(token& input);
	void remove(string name);
	int find(string name);
	int find(char name);
	void show();
private:
	hash_map<string, int> tab;
};

symbolTable::symbolTable()
{
	this->insert("+", 3);
	this->insert("-", 4);
	this->insert("*", 5);
	this->insert("/", 6);
	this->insert("(", 7);
	this->insert(")", 8);
}

void symbolTable::insert(string name, int type)
{
	tab[name] = type;
}

void symbolTable::insert(token& input)
{
	tab[input.name] = input.type;
}

void symbolTable::remove(string name)
{
	tab.erase(name);
}

int symbolTable::find(string name)
{
	if (tab.find(name) != tab.end())
		return (*tab.find(name)).second;
	else
		return -1;
}

int symbolTable::find(char name)
{
	string temp;
	temp = name;
	return this -> find(temp);
}

void symbolTable::show()
{
	hash_map<string, int>::iterator it;

	cout << "Content of symbol table:" << endl;
	cout << "====================" << endl;
	cout << "name\ttype\t" << endl;
	cout << "====================" << endl;
	for (it = tab.begin(); it != tab.end(); it++)
		cout << (*it).first << '\t' << (*it).second << endl;
	cout << "====================" << endl;
}