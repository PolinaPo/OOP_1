#ifndef PROGRAM_H
#define PROGRAM_H
#include <fstream>
#include <string>
using namespace std;

namespace type_plants
{
	// общий класс растений
	class plants
	{
	public:
		// Значения мест произрастания растений
		enum place { TUNDRA, DESERT, STEPPE, TAIGA, MIXED_FOREST, MOUNTAINS };
		place place_growth;//место произрастания

		string name;
		virtual ~plants(){};
		static plants *plants_Input(ifstream &ifst);
		void plants_Output(ofstream &ofst);
		virtual void Input(ifstream &ifst) = 0;
		virtual void Output(ofstream &ofst) = 0;
		// Количество согласных букв в названии растения (целое число)
		int number_consonants();
		// Cравнение ключей двух программных объектов
		bool compare(struct plants *other);
		// Вывод только деревьев
		virtual void Output_only_tree(ofstream &ofst);
	};

	class tree : public plants
	{
	public:
		long age;
		void Input(ifstream &ifst);
		void Output(ofstream &ofst);
		// Вывод только деревьев
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
		// Вывод только деревьев
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
		// Сортировка содержимого контейнера
		void sort();

		// Вывод только деревьев
		void Output_only_tree(ofstream &ofst);
		container();
		~container();
	};

	class bash : public plants
	{
	public:
		// Значение месяца цветения кустарников
		enum month { JAN, FEB, MAR, APR, MAY, JUNE, JULY, AUG, SEPT, OCT, NOV, DEC };
		month m;
		void Input(ifstream &ifst);
		void Output(ofstream &ofst);
		~bash();
	};

	class flower : public plants
	{
	public:
		// Значения видов цветов
		enum view { DOMESTIC, GARDEN, WILD };
		view flower_view;
		void Input(ifstream &ifst);
		void Output(ofstream &ofst);
		~flower();
	};
} // end type_plants namespace
#endif // !PROGRAM_H
