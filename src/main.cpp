#include "logic.h"
#include "terminalUI.h"
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    vector<string> instructions;
    string language = askLanguage();
    string path;
    if (language == "fin")
        path = "../instructions/Finnish.txt";
    if (language == "eng")
        path = "../instructions/English.txt";
    ifstream f(path);
    string line;
    while (getline(f, line))
    {
        instructions.push_back(line);
    }
    f.close();
    int teamsCount = askInt(instructions[1]);
    string teams[teamsCount];
    for (int i = 0; i < teamsCount; i++)
    {
        teams[i] = askString(instructions[2]);
    }
    int rounds = askInt(instructions[0]);
}