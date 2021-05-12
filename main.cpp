#include <iostream>
#include <fstream>
#include "program.h"

using namespace std;
using namespace type_plants;

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        cout << "Incorrect command line!\n"
             << "Waited: command infile outfile" << endl;
        exit(1);
    }
    cout << argv[1] << endl;
    cout << argv[2] << endl;

    ifstream ifst(argv[1]);

    // Проверка на количество строк в входном файле
    if (ifst.is_open())
    {
        int count_string = 0;
        while (ifst.ignore(numeric_limits<streamsize>::max(), '\n'))
        {
            if (!ifst.eof()) // если в конце последней строки '\n', иначе не нужно
                count_string++;
        }
        count_string = count_string + 1;
        cout << "Count = " << count_string << endl;
        if (count_string % 4 != 0 && count_string != 1)
        {
            cout << "Error, Insufficient input data!" << endl;
            exit(1);
        }
        ifst.close();
    }

    ifst.open(argv[1]);
    // Проверка - отсутствие входного файла
    if (!ifst.is_open())
    {
        cout << "Input file is not open!" << endl;
        exit(1);
    }
    ofstream ofst(argv[2]);

    cout << "Start" << endl;
    container c;
    c.container_Fill(ifst);
    cout << "Filled container" << endl;

    c.container_Output(ofst);
    cout << "Output container" << endl;

    c.MultiMethod(ofst);
    cout << "Multimethod" << endl;

    c.Sort();
    ofst << "\nSorted" << endl;
    cout << "Sorted container" << endl;

    c.container_Output(ofst);
    cout << "Output container" << endl;

    c.Output_only_tree(ofst);
    cout << "Output of trees only" << endl;
    c.container_Clear();
    cout << "Empty container" << endl;
    c.container_Output(ofst);
    cout << "Stop" << endl;

    system("pause");
    return 0;
}