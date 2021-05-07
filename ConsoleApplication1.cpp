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

Node *Sort(Node* Arr) // выделяем символы с частотами и сортируем по возрастанию
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
	

	for (int i = 0; i < size; i++)
		cout << Result[i].s << " = " << Result[i].f << endl;

	return Result;
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

	Node* SortSymbol = Sort(s_Array); // сортируем и избавляемся от лишних узлов
	
	
	
	
	
	


	return 0;

}