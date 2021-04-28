#ifndef PROGRAM_H
#define PROGRAM_H
#include <fstream>
#include <string>
using namespace std;

namespace type_plants {

	// общий класс растений
	class plants {
	public:
		string name;
		virtual ~plants() {};
		static plants* plants_Input(ifstream& ifst);
		void plants_Output(ofstream& ofst);
		virtual void Input(ifstream& ifst) = 0;
		virtual void Output(ofstream& ofst) = 0;
	};

	class tree : public plants {
	public:
		long age;
		void Input(ifstream& ifst);
		void Output(ofstream& ofst);
		~tree();
	};

	class node {
	public:
		plants* info;
		node* next;
		bool node_Add(ifstream& ifst);
		bool node_Output(ofstream& ofst);
		static node* node_Next(node* cur_node, node* value, int flag);
		~node();
	};

	class container {
	public:
		int size;
		node* head;
		node* tmp_node = new node;
		void container_Clear();
		void container_Fill(ifstream& ifst);
		void container_Output(ofstream& ofst);
		container();
		~container();
	};

	class bash : public plants {
	public:
		// «начение мес€ца цветени€ кустарников
		enum month { JAN, FEB, MAR, APR, MAY, JUNE, JULY, AUG, SEPT, OCT, NOV, DEC };
		month m;
		void Input(ifstream& ifst);
		void Output(ofstream& ofst);
		~bash();
	};
} // end type_plants namespace

#endif // !PROGRAM_H
