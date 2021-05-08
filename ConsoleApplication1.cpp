#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <math.h>
#include <iterator>


using namespace std;  // структура котороя помещается в список , вроде работает

struct Node               // так как в список уже входят указатели на следующий и предудущий
{
	Node *L = nullptr;  // левый потомок      // в структуре они по сути не нужны
	Node *R = nullptr; // правый потомок
	char s; // символ
	int f = 0; // частота
};

struct Tree
{
	Tree* root;
	Node* left;
	Node* right;
};
/////////////// создание частности, сортировка и создание списка символов ///////////////




void Shaker(Node* Arr, int size) // Шейкерная сортировка
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
			if (Arr[i].f > Arr[i + 1].f)
			{
				tmp = Arr[i];
				Arr[i] = Arr[i + 1];
				Arr[i + 1] = tmp;
				R1 = i;
			}
			i++;
		}
		R = R1;
		i = R; // проход справа налево
		L1 = R;
		while (i > L)
		{
			if (Arr[i - 1].f > Arr[i].f)
			{
				tmp = Arr[i];
				Arr[i] = Arr[i - 1];
				Arr[i - 1] = tmp;
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

void AddFrequency(Node *Arr, char *Str, int sizeStr) // Вычисляет частотность символов
{
	int j = 0;
	for (int i = 0; i < 255; i++)
	{
		while (j != sizeStr)
		{
			if (Arr[i].s == Str[j])
				Arr[i].f++;
			j++;	
		}
		j = 0;
		//cout << Arr[i].s << " = " << Arr[i].f << endl;
	}
}

list <Node> Sort(Node* Arr) // выделяем символы с частотами и сортируем по возрастанию и добавляем в список
{
	int size = 0; // подсчитываем, сколько символов имеют частотность
	for (int i = 0; i < 255; i++)
		if (Arr[i].f > 0) size++;

	Node *Result = new Node[size]; // создаем то количество узлов, сколько разновидностей символов присутствует в тексте
	int j = 0;

	for (int i = 0; i < 255; i++)
		if (Arr[i].f > 0)
		{
			Result[j] = Arr[i];
			j++;
		}

	Shaker(Result, size);
	
	list <Node> Spisok;
	for (int i = 0; i < size; i++)
		Spisok.push_back(Result[i]);
	

	//for (int i = 0; i < size; i++)
		//cout << Result[i].s << " = " << Result[i].f << endl;

	return Spisok;
}

void PrintList(list <Node> A) // проверка списка на правильность
{
	Node temp;
	for (auto i = A.begin(); i != A.end(); i++)
	{
		temp = *i;
		cout << temp.s << " = " << temp.f << endl;
	}
}

////////////// построение дерева /////////////
void SortList(list <Node> A)
{




}

Node PoolOfNodes(Node A, Node B)
{
	Node Result;
	Result.f = A.f + B.f;
	Result.L = &A;
	Result.R = &B;

	return Result;
}

Tree CreateTree (list <Node> S)
{
	int size = S.size();
	
	Node temp;
	while (size != 1);
	{
		


		size--;
	}
	

	





}

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE *fi = fopen("Input.txt", "rt");
	if (fi == NULL) { cout << "File problem!!!"; return 1; }
	char x;
	int size = 0;
	while (!feof(fi))  // узнаем размер текста в файле "Input.txt"
	{
		fscanf(fi, "%c", &x);
		size++;
	}
	size -= 1;
	fclose(fi);

	fopen("Input.txt", "rt");
	char *string = new char[size]; // пишем в массив char все из "Input.txt"
	int i = 0;
	while (!feof(fi))  
	{
		fscanf(fi, "%c", &x);
		string[i] = x;
		++i;
	}
	//for (int j = 0; j < size; j++)
	//	cout << string[j] << ' ';
	fclose(fi);
		
	Node s_Array[255];
	for (int i = 0; i < 255; i++)
		s_Array[i].s = (int)i;

	AddFrequency(s_Array, string, size); // вычисляем частоту символов

	list<Node> Spisok = Sort(s_Array); // сортируем и избавляемся от лишних узлов и добавляем их в список
	
	





	
	
	
	


	return 0;

}