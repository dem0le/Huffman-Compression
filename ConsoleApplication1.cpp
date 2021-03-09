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

Node *CreateArrayOfSymbols() // создает массив из 255 символов ASCII (убрать лишние символы)
{
	Node s_Array[255];
	s_Array[0].s = 'a';
	for (int i = 1; i < 255; i++)
		s_Array[i].s = s_Array[i - 1].s + 1;
	//for (int i = 0; i < 255; i++)
		//cout << s_Array[i].s << ' ';
	return s_Array;
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
		cout << Arr[i].s << " = " << Arr[i].f << endl;
	}
}



int main()
{
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
	for (int j = 0; j < size; j++)
		cout << string[j] << ' ';
	fclose(fi);
	
	Node *Symbols = new Node[255];
	Symbols = CreateArrayOfSymbols();
	AddFrequency(Symbols, string, size);
	
	
	
	


	return 0;

}