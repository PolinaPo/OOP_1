#include <iostream>
#include <fstream>
#include "program.h"

using namespace std;

namespace type_plants {

	void tree::Input(ifstream& ifst) {
		ifst >> age;
	}

	void tree::Output(ofstream& ofst) {
		ofst << "Tree age: " << age << "." << endl;
	}

	tree::~tree() {}

	void container::container_Fill(ifstream& ifst) {
		while (!ifst.eof())
		{
			node* tmpNode = new node;
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

	void container::container_Output(ofstream& ofst) {
		if (size == 0) {
			cout << "|List is empty!|" << endl;
			return;
		}
		ofst << "Container contains " << size << " element" << endl;
		cout << "|Container contains " << size << " elements.|" << endl;
		tmp_node = head;
		for (int i = 0; i < size; i++) {
			tmp_node->node_Output(ofst);
			tmp_node = node::node_Next(tmp_node, NULL, 2);
		}
	}

	void container::container_Clear() {
		node* curNode;
		curNode = head;

		while (curNode != NULL)
		{
			node* temp = curNode->next;
			delete curNode;
			curNode = temp;
		}

		head = NULL;
		size = 0;
	}

	container::container() {
		size = 0;
		head = NULL;
	}

	container::~container() {
		container_Clear();
	}

	bool node::node_Add(ifstream& ifst) {
		info = plants::plants_Input(ifst);
		if (info == NULL) return false;
		else return true;
	}

	bool node::node_Output(ofstream& ofst) {
		info->plants_Output(ofst);
		info->Output(ofst);
		ofst << "The number of consonants in the name: " << info->number_consonants() << "." << endl;
		return true;
	}

	node* node::node_Next(node* cur_node, node* value, int flag) {
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

	plants* plants::plants_Input(ifstream& ifst) {
		plants* new_plants;
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
		default:
			return 0;
		}
		new_plants->Input(ifst);
		ifst >> new_plants -> name;
		return new_plants;
	}

	void plants::plants_Output(ofstream& ofst) {
		ofst << "\nName: " << name << "," << endl;
	}

	void bash::Input(ifstream& ifst) {
		int mnth = 0;
		ifst >> mnth;
		m = month(mnth);
	}

	void bash::Output(ofstream& ofst) {
		ofst << "Mounth: " << m << "." << endl;
	}

	bash::~bash() {}

	//  оличество согласных букв в названии растени€ (целое число)
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
}