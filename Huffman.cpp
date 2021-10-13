#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>


using namespace std;  // структура котороя помещается в список , вроде работает

struct Freq // таблица частотности + таблица кодов
{
	char s;
	int n;
	vector <bool> code;
};

class Node // узел для построения дерева
{
public:
	int n;
	
	char s;
	Node* left;
	Node* right;

	Node()
	{
		left = nullptr;
		right = nullptr;
	}

	Node(Node* ll, Node* rr)
	{
		left = ll;
		right = rr;
		n = ll->n + rr->n;
	}

};

string FileToString(ifstream& file) // читаем текст с файла
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

Freq* CreateTableOfFrequency(string text) // заполняем таблицу частотности
{
	char symbols[255];  // заносим все символы ASCII в массив
	for (int i = 0; i < 255; i++)
		symbols[i] = i;

	Freq* temp = new Freq[255]; // создаем таблицу частотности через (структуру и массив)
	int k = 0;

	for (int i = 0; i < 255; i++) // бежим по входному тексту и считываем частотности каждого символа, записывая в (временную) таблицу частотности
	{
		for (int j = 0; j < text.size(); j++)
			if (symbols[i] == text[j])
				k++;
		temp[i].s = symbols[i];
		temp[i].n = k;
		k = 0;
	}

	
	for (int i = 0; i < 255; i++) // смотрим какие символы БЫЛИ в исходном тексте
		if (temp[i].n != 0)
			k++;

	int size = k;
	Freq* table = new Freq[256]; // создаем финальную таблицу частотности
	k = 0;

	for (int i = 0; i < 255; i++) // заносим в финальную таблицу данные
		if (temp[i].n != 0)
		{
			table[k].n = temp[i].n;
			table[k].s = temp[i].s;
			k++;
		}
	table[k].n = 0;
	

	int tmp;
	char tmps;
	int j;
	for (int i = 1; i < size; i++) // сортируем финальную таблицу по возрастанию (прямая вставка)
	{
		tmp = table[i].n;
		tmps = table[i].s;
		for (j = i - 1; j >= 0 && table[j].n > tmp; j--)
		{
			table[j + 1].n = table[j].n;
			table[j + 1].s = table[j].s;
		}
		table[j + 1].n = tmp;
		table[j + 1].s = tmps;
	}

	delete[]temp;
	return table;
}

list <Node*> TableToList(Freq* table) // заносим отсортированную таблицу частотности в список
{
	int i = 0;
	list <Node*> List;

	while (table[i].n != 0)
	{
		Node* Symbol = new Node;
		Symbol->n = table[i].n;
		Symbol->s = table[i].s;
		List.push_back(Symbol);
		i++;
	}

	return List;
}

struct LISTcompare // структура для сравнения элементов списка
{
	bool operator()(const Node* l, const Node* r)
		const
	{
		return l->n < r->n;
	}
};
Node* CreateTree(list <Node*> list) // создание дерева из списка с возвращением корня дерева
{
	while (list.size() != 1)
	{
		list.sort(LISTcompare());
		Node* L = list.front();
		list.pop_front();
		Node* R = list.front();
		list.pop_front();

		Node* LR = new Node(L, R);
		list.push_back(LR);
	}

	return list.front();
}

vector <bool> tmp;
void CreateTableOfCode(Node* root, Freq* table) // создание кодов по дереву и занесение их в таблицу чатотности
{
	if (root->left != nullptr)
	{
		tmp.push_back(0);
		CreateTableOfCode(root->left, table);
	}

	if (root->right != nullptr)
	{
		tmp.push_back(1);
		CreateTableOfCode(root->right, table);
	}

	int i = 0;
	while (table[i].n != 0)
	{
		if ((root->s) == table[i].s)
		{
			table[i].code = tmp;
			break;
		}
		i++;
		
	}
	if (tmp.size() != 0) tmp.pop_back();
}

void PrintInformaton(Freq* table) // вывод таблицы на экран (символ, кол-во символов, код символа)
{
	cout << "********* ТАБЛИЦА ЧАСТОТНОСТИ С КОДАМИ *********" << endl << endl;
	cout << "CHAR   FREQ         CODE" << endl << endl;
	int i = 0;
	while (table[i].n != 0)
	{
		cout << table[i].s << "   =   " << table[i].n << "   =   ";
		for (int j = 0; j < table[i].code.size(); j++)
			cout << table[i].code[j];
		cout << endl;
		i++;
	}
	cout << "************************************************" << endl;
}

 string CodeToString(string text, Freq* table) // записываем в string сжатую информацию (но пока еще не сжатую)
{
	 string out;
	 int i; // iterator table

	 for (int j = 0; j < size(text); j++)
	 {
		 i = 0;
		 while (table[i].n != 0)
		 {
			 if (text[j] == table[i].s)
			 {
				 for (auto k = 0; k < table[i].code.size(); k++)
				 {
					 if (table[i].code[k] == true)
						 out += '1';
					 else
						 out += '0';
				}
				 break;
			 }
			 i++;
		 }
	 }

	 return out;
} 
 string TextCodeToFinalCode(string text, string input) // побитово записываем (сжимаем)
 {
	 string out;
	 unsigned char v = 0;
	 unsigned char mask = 128;

	 for (int i = 0; i < size(text); i++)
	 {
		 if (text[i] == '1')
			 v |= mask;
		 
		 mask >>= 1;

		 if (mask == 0)
		 {
			 out += v;
			 v = 0;
			 mask = 128;
		 }
	 }

	 out += "size=";
	 
	 int n = size(input);
	 int k = 1;

	 while ((n / 10) != 0)
	 {
		 n /= 10;
		 k++;
	 }

	 char *SIZE = new char[k];
	 n = size(input);

	 for (int i = (k - 1); i >= 0; i--)
	 {
		 SIZE[i] = (n % 10) + 48;
		 n = n / 10;
	 }

	 for (int i = 0; i < k; i++)
		 out += SIZE[i];

	 return out;
 }

 void Output(ofstream& file, string text) // запись текста в файл
 {
	 file << text;
 }
 void OutputCodeTableToFile (ofstream& file, Freq* table) // занесение в файл (символ-код)
 {
	 int i = 0;
	 while (table[i].n != 0)
	 {
		 file << table[i].s;
		 for (int j = 0; j < table[i].code.size(); j++)
		 {
			 if (table[i].code[j] == true)
				 file << '1';
			 else
				 file << '0';
		 }
		 i++;
	 }



 }

 void Encode(ifstream& file, ofstream& outfile, ofstream& outfilecode) // функция сжатия (начальный файл, сжатая информация, таблица кодов)
 {
	 cout << "############### ENCODE PROCESS ##############" << endl;
	 string text = FileToString(file);
	 Freq* table = CreateTableOfFrequency(text);
	 list <Node*> List = TableToList(table);
	 Node* root = CreateTree(List);
	 CreateTableOfCode(root, table);
	 PrintInformaton(table);
	 cout <<"TEXT: " <<text << endl;
	 string textcode = CodeToString(text, table);
	 cout <<"BYTE: " << textcode << endl;
	 string finally = TextCodeToFinalCode(textcode, text);
	 cout <<"ENCRYPT: " << finally << endl;
	 Output(outfile, finally);
	 OutputCodeTableToFile(outfilecode, table);
 }
 /////////////////////////////////////////////////////////////////////

 int ReturnSizeOfDecodingText(ifstream& file) // ицем в сжатом файле пометку "size=" чтобы извлечь из файла количество символов в итоговом файле
 {
	 string text = FileToString(file);
	 
	 int i = 0;
	 int k;
	 for (i = text.find("size=", i++); i != string::npos; i = text.find("size=", i + 1))
		 k = i;

	 i = k + 5;
	 int tmp = i;
	 k = 0;

	 for (; i < size(text); i++)
		 k++;

	 char* SIZE = new char[k];
	 i = 0;

	 for (; tmp < size(text); tmp++,i++)
		 SIZE[i] = text[tmp];

	 int result = 0;
	 int x = k;
	 for (int j = 0; j < k; j++)
	 {
		 result += pow(10, x - 1) * (SIZE[j] - 48);
		 x--;
	 }
	 return result;
 }
 Freq* TableFromFile(ifstream& file)
 {
	 string table = FileToString(file);
	 cout << "FREQ: " << table << endl;

	 int n_of_s = 0;

	 for (int i = 0; i < size(table); i++) // находим количество закодированных символов
		 if (table[i] != '1' && table[i] != '0')
			 n_of_s++;

	 Freq* TableCode = new Freq[n_of_s + 1];
	 int i = 0;// текст

	 for (int j = 0; j < n_of_s; j++)
	 {
		 TableCode[j].s = table[i];
		 i++;
		 while (table[i] == '1' || table[i] == '0')
		 {
			 if (table[i] == '1') TableCode[j].code.push_back(1);
			 if (table[i] == '0') TableCode[j].code.push_back(0);
			 i++;
		 }
	 }
	 TableCode[n_of_s].code.clear();
	 return TableCode;
 }
 string ByteToText(ifstream& file) 
 {
	 string text = FileToString(file);
	 cout << "ENCRYPT: " << text << endl;

	 int i = 0;
	 int k;
	 for (i = text.find("size=", i++); i != string::npos; i = text.find("size=", i + 1))
		 k = i;

	 string out;
	 unsigned char mask;

	 for (int j = 0; j < k; j++)
	 {
		 mask = 128;
		 while (mask != 0)
		 {
			 if ((text[j] & mask) == mask) out += '1';
			 else out += '0';
			 mask >>= 1;
		 }
	 }
	 return out;
 }
 Node* Tree(Freq* table)
 {
	 Node* root = new Node;
	 Node* tmp;
	 int i = 0;

	 while (table[i].code.size() != 0)
	 {
		 tmp = root;
		 for (int k = 0; k < table[i].code.size(); k++)
		 {
			 if (table[i].code[k] == true)
			 {
				 if (tmp->right == nullptr)
				 {
					 tmp->right = new Node; tmp = tmp->right;
				 }
				 else
					 tmp = tmp->right;
			 }
			 else
			 {
				 if (tmp->left == nullptr)
				 {
					 tmp->left = new Node; tmp = tmp->left;
				 }
				 else
					 tmp = tmp->left;
			 }	 
		}
		 tmp->s = table[i].s;
		 i++;
	 }
	 return root;
 }
 string Out(Node* root, string byte)
 {
	string out;
	Node* tmp;
	int i = 0;

	while (i < size(byte))
	{
		tmp = root;
		while (tmp->left != nullptr && tmp->right != nullptr)
		{
			if (byte[i] == '1')
				tmp = tmp->right;
			else tmp = tmp->left;
			i++;
		}
		out += tmp->s;
	}
	 return out;
 }

 void Decode(ifstream& file, ifstream& filecode, ofstream& outfile)
 {
	 cout << endl << "############## DECODING PROCESS #############" << endl;
	 string byte = ByteToText(file);
	 Freq* table = TableFromFile(filecode);
	 Node* root = Tree(table);
	 cout << "BYTE: " << byte << endl;
	 string out = Out(root, byte);
	 cout << "TEXT: " << out << endl;
	 Output(outfile, out);
 }


int main()
{
	setlocale(LC_ALL, "Russian");
	////////// ENCODE //////////////
	ifstream infile("InputENCODE.txt");
	ofstream outfile("OutputENCODE.txt");
	ofstream outfilecode("OutputTableENCODE.txt");
	Encode(infile, outfile, outfilecode);
	////////////////////////////////
	/////////DECODE////////////////
	ifstream infileDECODE("InputDECODE.txt");
	ifstream TableDECODE("InputTableDECODE.txt");
	ofstream OutFileDECODE("OutputDECODE.txt");
	Decode(infileDECODE, TableDECODE, OutFileDECODE);
	


	outfile.close();
	infile.close();
	outfilecode.close();
	infileDECODE.close();
	TableDECODE.close();
	OutFileDECODE.close();
	return 0;

}