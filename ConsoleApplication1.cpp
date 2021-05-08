#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;  // структура котороя помещается в список , вроде работает

class Node
{
private:
	int f;
	char s;
	Node* L;
	Node* R;

public:


	Node()
	{
		f = 0;
		s = 0;
		L = nullptr;
		R = nullptr;
	}

	Node(Node* A, Node* B)
	{
		f = A->f + B->f;
		s = 0;
		L = A;
		R = B;
	}

	friend list <Node> CreateListOfFrequency(string text);
	friend void PrintList(list <Node> S);
	friend void SortList(list <Node> S);
};

string FileToString(ifstream &file)
{
	string text;
	if (file.is_open())
	{
		stringstream ss;
		ss << file.rdbuf();
		text = ss.str();
		file.close();
	}
	else
		cout << "Your file are failed!" << endl;

	return text;
}

list <Node> CreateListOfFrequency(string text)
{
	Node* ArrayAllSymbols = new Node[255];
	for (int i = 0; i < 255; i++)
		ArrayAllSymbols[i].s = (int)i;

	int j = 0;
	for (int i = 0; i < 255; i++)
	{
		while (j != text.size())
		{
			if (ArrayAllSymbols[i].s == text[j])
				ArrayAllSymbols[i].f++;
			j++;
		}
		j = 0;
	}

	list <Node> Spisok;
	for (int i = 0; i < 255; i++)
		if (ArrayAllSymbols[i].f > 0) Spisok.push_back(ArrayAllSymbols[i]);

	return Spisok;
}

void PrintList(list <Node> S)
{
	for (auto i = S.begin(); i != S.end(); i++)
	{
		Node temp = *i;
		cout << temp.s << " = " << temp.f << endl;
	}


}

void SortList(list <Node> S)
{
	
		
	
}


int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream file("Input.txt");
	string text = FileToString(file);
	list <Node> Spisok = CreateListOfFrequency(text);
	SortList(Spisok);
	//PrintList(Spisok);
	
	
		
	
	





	
	
	
	


	return 0;

}