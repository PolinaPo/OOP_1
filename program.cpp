#include <iostream>
#include <fstream>
#include "program.h"

using namespace std;

namespace type_plants
{
	void tree::Input(ifstream &ifst)
	{
		long tmp_age = 0;
		ifst >> tmp_age;
		// Проверка на то, что возраст - число больше нуля
		if (tmp_age < 0)
		{
			cout << "Error, Age cannot be negative!" << endl;
			exit(1);
		}
		age = tmp_age;
	}

	void tree::Output(ofstream &ofst)
	{
		ofst << "Tree age: " << age << "," << endl;
	}

	tree::~tree() {}

	void container::container_Fill(ifstream &ifst)
	{
		// Проверка файла на пустоту
		if (ifst.peek() == EOF) 
		{
			cout << "Error, Fail empty!" << endl;
			exit(1);
		}
		
		while (!ifst.eof())
		{
			node *tmpNode = new node;
			if (tmpNode->node_Add(ifst))
			{
				size++;

				if (head != NULL)
				{
					tmpNode->next = head;
					head = tmpNode;
				}
				else
				{
					tmpNode->next = NULL;
					head = tmpNode;
				}
			}
			else
				break;
		}
	}

	void container::container_Output(ofstream &ofst)
	{
		if (size == 0)
		{
			cout << "|List is empty!|" << endl;
			return;
		}
		ofst << "Container contains " << size << " element" << endl;
		cout << "|Container contains " << size << " elements.|" << endl;
		tmp_node = head;
		for (int i = 0; i < size; i++)
		{
			tmp_node->node_Output(ofst);
			tmp_node = node::node_Next(tmp_node, NULL, 2);
		}
	}

	void container::container_Clear()
	{
		node *curNode;
		curNode = head;

		while (curNode != NULL)
		{
			node *temp = curNode->next;
			delete curNode;
			curNode = temp;
		}

		head = NULL;
		size = 0;
	}

	container::container()
	{
		size = 0;
		head = NULL;
	}

	container::~container()
	{
		container_Clear();
	}

	bool node::node_Add(ifstream &ifst)
	{
		info = plants::plants_Input(ifst);
		if (info == NULL)
		{
			return false;
		}	
		else
		{
			return true;
		}
	}

	bool node::node_Output(ofstream &ofst)
	{
		info->plants_Output(ofst);
		info->Output(ofst);
		ofst << "The number of consonants in the name: " << info->number_Consonants() << "." << endl;
		return true;
	}

	node *node::node_Next(node *cur_node, node *value, int flag)
	{
		switch (flag)
		{
		case 1: // добавить ссылку на следующий элемент
			cur_node->next = value;
			return cur_node;
		case 2: // получить следующий элемент
			cur_node = cur_node->next;
			return cur_node;
		default:
			break;
		}
	}

	node::~node() {}

	plants *plants::plants_Input(ifstream &ifst)
	{
		plants *new_plants;
		int k;
		ifst >> k;
		if (ifst.eof())
		{
			return 0;
		}
		// Проверка на то, что ключ - число от 1 до 3
		if (k < 1 || k > 3)
		{
			cout << "Error, the key must be a value between 1 and 3!" << endl;
			exit(1);
		}
		switch (k)
		{
		case 1:
			new_plants = new tree;
			break;
		case 2:
			new_plants = new bash;
			break;
		case 3:
			new_plants = new flower;
			break;
		default:
			return 0;
		}
		new_plants->Input(ifst);
		int place_plant = 0;
		ifst >> place_plant;
		// Проверка на то, что место произрастания - число от 0 до 5
		if (place_plant < 0 || place_plant > 5)
		{
			cout << "Error, The place of growth should take a value from 0 to 5!" << endl;
			exit(1);
		}
		new_plants->place_growth = place(place_plant);
		ifst >> new_plants->name;
		return new_plants;
	}

	void plants::plants_Output(ofstream &ofst)
	{
		ofst << "\nName: " << name << "," << "\n"
			 << "Place of growth: " << place_growth + 1 << "," << endl;
	}

	void bash::Input(ifstream &ifst)
	{
		int mnth = 0;
		ifst >> mnth;
		// Проверка на то, что месяц - число от 0 до 11
		if (mnth < 0 || mnth > 11)
		{
			cout << "Error, month must be between 0 and 11!" << endl;
			exit(1);
		}
		m = month(mnth);
	}

	void bash::Output(ofstream &ofst)
	{
		ofst << "Mounth: " << m << "," << endl;
	}

	bash::~bash() {}

	void flower::Input(ifstream &ifst)
	{
		int f_view = 0;
		ifst >> f_view;
		// Проверка на то, что вид - число от 0 до 2
		if (f_view < 0 || f_view > 2)
		{
			cout << "Error, view must be between 0 and 2!" << endl;
			exit(1);
		}
		flower_view = view(f_view);
	}

	void flower::Output(ofstream &ofst)
	{
		ofst << "View: " << flower_view << "," << endl;
	}

	flower::~flower() {}

	// Количество согласных букв в названии растения (целое число)
	int plants::number_Consonants()
	{
		string consonants = "BbCcDdFfGgHhJjKkLlMmNnPpQqRrSsTtVvWwXxYyZz";
		int sum = 0;
		for (unsigned i = 0; i < name.length(); i++)
		{
			for (unsigned j = 0; j < consonants.length(); j++)
			{
				if (name[i] == consonants[j])
				{
					sum++;
				}
			}
		}
		return sum;
	}

	// Cравнение ключей двух программных объектов
	bool plants::Compare(plants *other)
	{
		return number_Consonants() > other->number_Consonants();
	}

	// Сортировка содержимого контейнера
	void container::Sort()
	{
		node* left = head;
		node* right = head->next;

		node* temp = new node;
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (left->info->Compare(right->info))
				{
					temp->info = left->info;
					left->info = right->info;
					right->info = temp->info;
				}
				right = right->next;
			}
			left = left->next;
			right = left->next;
		}
	}

	// Вывод только деревьев
	void container::Output_only_tree(ofstream & ofst)
	{
		node *currentNode;
		if (size == 0)
		{
			cout << "LIST IS EMPTY!" << endl;
			return;
		}

		ofst << "\nOnly trees." << endl;
		for (int i = 0; i < size; i++)
		{
			currentNode = head;
			for (int j = 0; j < i; j++)
			{
				currentNode = currentNode->next;
			}
			currentNode->Output_only_node_tree(ofst);
		}
	}

	void tree::Output_only_tree(ofstream & ofst)
	{
		plants_Output(ofst);
		Output(ofst);
		ofst << "The number of consonants in the name: " << number_Consonants() << "." << endl;
	}

	void plants::Output_only_tree(ofstream & ofst)
	{
		ofst << "";
	}

	bool node::Output_only_node_tree(ofstream & ofst)
	{
		info->Output_only_tree(ofst);
		return true;
	}
}