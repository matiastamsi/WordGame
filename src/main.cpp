#include "../headers/terminalUI.h"
#include "../headers/team.h"
#include "../headers/logic.h"
#include <vector>
#include <fstream>
#include <random>

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
        printlString("Jos haluat pelata suomeksi,"
                     " kirjoita 'fin':");
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
    // Ask how many participants.
    printlString(instructions[5]);
    int count = seeInt();
    vector<string> participants;
    for (int i = 0; i < count; i++)
    {
        // Tell to give a participant.
        printlString(instructions[6]);
        string name = seeString();
        participants.push_back(name);
    }
    mt19937 g(random_device{}());
    while (participants.size() > 0)
    {
        for (unsigned int i = 0; i < teams.size(); i++)
        {
            int size = participants.size();
            if (size > 0)
            {
                uniform_int_distribution<int> d(0, size - 1);
                int r = d(g);
                teams[i].addTeamMember(participants[r]);
                participants.erase(participants.begin() + r);
            }
        }
    }
}

void createSpecificTeams()
{
    for (unsigned int i = 0; i < teams.size(); i++)
    {
        // Ask how many members are in the team.
        printlString(instructions[3] + " " + teams[i].name + "?");
        int count = seeInt();
        for (int j = 0; j < count; j++)
        {
            printlString(instructions[4] + " (" + teams[i].name + ")");
            string name = seeString();
            teams[i].addTeamMember(name);
        }
    }
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
    for (team t : teams)
    {
        printlString(t.name + ": " + t.printMembers());
    }
    printlString(instructions[7]);
    int rounds = seeInt();
}