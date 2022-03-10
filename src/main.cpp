#include "logic.h"
#include "terminalUI.h"
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    vector<string> instructions;
    char l = askLanguage();
    string path;
    if (l == 's')
        path = "../instructions/instructionsFinnish.txt";
    if (l == 'e')
        path = "../instructions/instructionsEnglish.txt";
    ifstream f(path);
    string line;
    while (getline(f, line))
    {
        instructions.push_back(line);
    }
    f.close();
}