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
		return true;
	}

	node* node::node_Next(node* cur_node, node* value, int flag) {
		switch (flag)
		{
		case 1: // �������� ������ �� ��������� �������
			cur_node->next = value;
			return cur_node;
		case 2: // �������� ��������� �������
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
		ofst << "Name: " << name << "," << endl;
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

	// ����� ������ ��������
	void container::Output_only_tree(ofstream& ofst)
	{
		node* currentNode;
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

	void tree::Output_only_tree(ofstream& ofst)
	{
		plants_Output(ofst);
		Output(ofst);
	}


	void plants::Output_only_tree(ofstream& ofst)
	{
		ofst << endl;
	}

	bool node::Output_only_node_tree(ofstream& ofst)
	{
		info->Output_only_tree(ofst);
		return true;
	}
}