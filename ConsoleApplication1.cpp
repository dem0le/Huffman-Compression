#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;  // структура котороя помещается в список , вроде работает

class Node
{
private:
	int f;
	char s;
	Node* L;
	Node* R;
	char code;

public:


	Node()
	{
		f = 0;
		s = 0;
		L = nullptr;
		R = nullptr;
		code = 0;
	}

	Node(Node* A, Node* B)
	{
		f = A->f + B->f;
		s = 0;
		L = A;
		R = B;
		code = 0;
	}

	friend void CreateTree(list <Node> &A);
	friend list <Node> CreateListOfFrequency(string text);
	friend void PrintList(list <Node> S);
	friend void SortList(list <Node> &S);
	friend void Shaker(Node* A, int size);
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

void Shaker(Node* A, int size)
{
	int L, R, L1, R1, i;
	Node tmp;
	L = 0;
	R = size - 1;
	while (L < R)
	{
		i = L; // проход слева направо
		R1 = L;
		while (i < R)
		{
			if (A[i].f > A[i + 1].f)
			{
				tmp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = tmp;
				R1 = i;
			}
			i++;
		}
		R = R1;
		i = R; // проход справа налево
		L1 = R;
		while (i > L)
		{
			if (A[i - 1].f > A[i].f)
			{
				tmp = A[i];
				A[i] = A[i - 1];
				A[i - 1] = tmp;
				L1 = i;
			}
			i--;
		}
		L = L1;
		//cout << L << endl;
		//cout << R << endl;
		//cout << *this << endl;
	}


}

void SortList(list <Node> &S)
{
	Node* A = new Node[S.size()];
	int j = 0;

	for (auto i = S.begin(); i != S.end(); i++)
	{
		A[j] = *i;
		j++;
	}
	
	Shaker(A, S.size());
	int size = S.size();	
	S.clear();

	for (int i = 0; i < size; i++)
		S.push_back(A[i]);
}

void CreateTree(list <Node> &A)
{
	while (A.size() != 1)
	{
		SortList(A);

		Node left = (A.front());
		A.pop_front();
		Node right = (A.front());
		A.pop_front();

		Node NewUzel(&left, &right);
		A.push_back(NewUzel);
	}


}




int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream file("Input.txt");
	string text = FileToString(file);
	list <Node> Spisok = CreateListOfFrequency(text);
	CreateTree(Spisok);
	PrintList(Spisok);
	Node *Root = &Spisok.front();

	

	
	
		
		
	
	





	
	
	
	


	return 0;

}