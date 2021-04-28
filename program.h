#ifndef PROGRAM_H
#define PROGRAM_H
#include <fstream>
#include <string>
using namespace std;

namespace type_plants
{

	// ����� ����� ����
	class plants
	{
	public:
		// �������� ���� ������������� ��������
		enum place
		{
			TUNDRA,
			DESERT,
			STEPPE,
			TAIGA,
			MIXED_FOREST,
			MOUNTAINS
		};
		place place_growth; //����� �������������

		string name;
		virtual ~plants(){};
		static plants *plants_Input(ifstream &ifst);
		void plants_Output(ofstream &ofst);
		virtual void Input(ifstream &ifst) = 0;
		virtual void Output(ofstream &ofst) = 0;
		// ���������� ��������� ���� � �������� �������� (����� �����)
		int number_consonants();
		// C�������� ������ ���� ����������� ��������
		bool compare(struct plants *other);

		// ����� ������ ��������
		virtual void Output_only_tree(ofstream &ofst);
	};

	class tree : public plants
	{
	public:
		long age;
		void Input(ifstream &ifst);
		void Output(ofstream &ofst);
		// ����� ������ ��������
		void Output_only_tree(ofstream &ofst);
		~tree();
	};

	class node
	{
	public:
		plants *info;
		node *next;
		bool node_Add(ifstream &ifst);
		bool node_Output(ofstream &ofst);
		static node *node_Next(node *cur_node, node *value, int flag);
		// ����� ������ ��������
		bool Output_only_node_tree(ofstream &ofst);
		~node();
	};

	class container
	{
	public:
		int size;
		node *head;
		node *tmp_node = new node;
		void container_Clear();
		void container_Fill(ifstream &ifst);
		void container_Output(ofstream &ofst);
		// ���������� ����������� ����������
		void sort();

		// ����� ������ ��������
		void Output_only_tree(ofstream &ofst);
		container();
		~container();
	};

	class bash : public plants
	{
	public:
		// �������� ������ �������� �����������
		enum month
		{
			JAN,
			FEB,
			MAR,
			APR,
			MAY,
			JUNE,
			JULY,
			AUG,
			SEPT,
			OCT,
			NOV,
			DEC
		};
		month m;
		void Input(ifstream &ifst);
		void Output(ofstream &ofst);
		~bash();
	};

	// �����
	class flower : public plants
	{
	public:
		// �������� ����� ������
		enum view
		{
			DOMESTIC,
			GARDEN,
			WILD
		};
		view flower_view;
		void Input(ifstream &ifst);
		void Output(ofstream &ofst);
		~flower();
	};
} // end type_plants namespace

#endif // !PROGRAM_H
