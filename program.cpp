#include <iostream>
#include <fstream>
#include "program.h"

using namespace std;

namespace type_plants
{

	void tree::Input(ifstream &ifst)
	{
		ifst >> age;
	}

	void tree::Output(ofstream &ofst)
	{
		ofst << "Tree age: " << age << "," << endl;
	}

	tree::~tree() {}

	void container::container_Fill(ifstream &ifst)
	{
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
		ofst << "The number of consonants in the name: " << info->number_consonants() << "." << endl;
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
		m = month(mnth);
	}

	void bash::Output(ofstream &ofst)
	{
		ofst << "Mounth: " << m + 1 << "," << endl;
	}

	bash::~bash() {}

	void flower::Input(ifstream &ifst)
	{
		int f_view = 0;
		ifst >> f_view;
		flower_view = view(f_view);
	}

	void flower::Output(ofstream &ofst)
	{
		ofst << "View: " << flower_view + 1 << "," << endl;
	}

	flower::~flower() {}

	// Количество согласных букв в названии растения (целое число)
	int plants::number_consonants()
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
	bool plants::compare(plants *other)
	{
		return number_consonants() > other->number_consonants();
	}

	// Сортировка содержимого контейнера
	void container::sort()
	{
		node* left = head;
		node* right = head->next;

		node* temp = new node;
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (left->info->compare(right->info))
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

		ofst << "Only trees." << endl;
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
		ofst << "The number of consonants in the name: " << number_consonants() << "." << endl;
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