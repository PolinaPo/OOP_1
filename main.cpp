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
    if (!ifst.is_open())
    {
        cout << "File is not open!" << endl;
        exit(1);
    }
    ofstream ofst(argv[2]);
    cout << "Start" << endl;
    container c;
    c.container_Fill(ifst);
    cout << "Filled container" << endl;
    c.container_Output(ofst);
    c.sort();
    cout << "Sorted container" << endl;
    c.container_Output(ofst);
    c.Output_only_tree(ofst);
    cout << "Output of trees only" << endl;
    c.container_Clear();
    cout << "Empty container" << endl;
    c.container_Output(ofst);
    cout << "Stop" << endl;

    system("pause");
    return 0;
}