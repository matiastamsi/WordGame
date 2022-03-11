#include "../headers/terminalUI.h"
#include "../headers/team.h"
#include "../headers/logic.h"
#include <vector>
#include <fstream>

using namespace std;

// Globals
vector<string> instructions;
vector<team> teams;

void initializeInstructions()
{
    string s;
    do
    {
        printlString("If you want to play in English,"
                     " please type 'eng'.");
        printlString("Jos haluat pelata suomeksi, kirjoita 'fin':");
        s = seeString();
    } while (s != "eng" && s != "fin");
    string path;
    if (s == "fin")
        path = "../instructions/Finnish.txt";
    if (s == "eng")
        path = "../instructions/English.txt";
    ifstream f(path);
    string line;
    while (getline(f, line))
    {
        instructions.push_back(line);
    }
    f.close();
}

void createRandomTeams()
{
}

void createSpecificTeams()
{
}

void initializeTeams()
{
    printlString(instructions[0]);
    int teamsCount = seeInt();
    for (int i = 0; i < teamsCount; i++)
    {
        printlString(instructions[1]);
        string name = seeString();
        team t(name);
        teams.push_back(t);
    }
    string s;
    do
    {
        printlString(instructions[2]);
        s = seeString();
    } while (s != "r" && s != "d");
    if (s == "r")
        createRandomTeams();
    if (s == "d")
        createSpecificTeams();
}

int main()
{
    initializeInstructions();
    initializeTeams();
    printlString(instructions[4]);
    int rounds = seeInt();
}