#include "../headers/terminalUI.h"
#include "../headers/team.h"
#include "../headers/logic.h"
#include <vector>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

// Globals
vector<team> teams;
vector<string> words;

void createRandomTeams()
{
    printlString("How many participants in total?");
    int count = seeInt();
    vector<string> participants;
    for (int i = 0; i < count; i++)
    {
        printlString("Give a participant's name: ");
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

        printlString("How many team members in a team called " + teams[i].name + "?");
        int count = seeInt();
        for (int j = 0; j < count; j++)
        {
            printlString("Give " + teams[i].name + "'s member's name:");
            string name = seeString();
            teams[i].addTeamMember(name);
        }
    }
}

void initializeTeams()
{
    printlString("How many teams play?");
    int teamsCount = seeInt();
    for (int i = 0; i < teamsCount; i++)
    {
        printlString("Give a name for one of the teams:");
        string name = seeString();
        team t(name);
        teams.push_back(t);
    }
    string s;
    do
    {
        printlString("If you want to decide the members of each team, please press 'd'. If you want random teams, please press 'r':");
        s = seeString();
    } while (s != "r" && s != "d");
    if (s == "r")
        createRandomTeams();
    if (s == "d")
        createSpecificTeams();
}

void initializeWords()
{
    string s;
    do
    {
        printlString("If you want to use custom words, please type 'c'. If you want to use default dictionary, please type 'd':");
        s = seeString();
    } while (s != "c" && s != "d");
    string path;
    if (s == "c")
        path = "../words/custom.txt";
    if (s == "d")
    {
        string l;
        do
        {
            printlString("There is a possibility to use Finnish or English dictionaries. To choose Finnish type 'fin' and to choose English type 'eng': ");
            l = seeString();
        } while (l != "eng" && l != "fin");
        if (l == "eng")
            path = "../words/dictionaries/EnglishDictionary.txt";
        else if (l == "fin")
            path = "../words/dictionaries/FinnishDictionary.txt";
    }
    ifstream f(path);
    string line;
    while (getline(f, line))
    {
        words.push_back(line);
    }
    f.close();
}

string getRandomWord()
{
    mt19937 g(random_device{}());
    int size = words.size();
    uniform_int_distribution<int> d(0, size - 1);
    int r = d(g);
    string word = words[r];
    return word;
}

int turn(int duration)
{
    int points = 0;
    string s;
    do
    {
        printlString("When you are ready, press 'r'. Then one team member explains while other team members try to guess.");
        s = seeString();
    } while (s != "r");
    auto start = chrono::system_clock::now();
    auto end = chrono::system_clock::now();
    chrono::duration<double> time = end - start;
    string word = getRandomWord();

    while (time <= chrono::seconds{duration})
    {
        end = chrono::system_clock::now();
        auto oldTime = time;
        time = end - start;
        if ((int)time.count() - (int)oldTime.count() > 10)
        {
            int timeLeft = duration - ((int)time.count());
            printlString("Time left: " + to_string(timeLeft) + " s");
            printlString("Explain: " + word);
            printlString("Correct: type 'c' (+1p). Skip: press 's' (-1p).");
        }
    }

    return points;
}

void play(int rounds, int duration)
{

    int r = 1;
    while (r <= rounds)
    {
        for (unsigned int i = 0; i < teams.size(); i++)
        {
            printlString("Next it is " + teams[i].name + "'s turn!");
            teams[i].points += turn(duration);
        }

        printlString("Points after round " + to_string(r) + ": ");
        for (team t : teams)
        {
            printlString(t.name + ": " + to_string(t.points));
        }
        r++;
    }
}

int main()
{
    initializeTeams();
    printlString("The teams:");
    for (team t : teams)
    {
        printlString(t.name + ": " + t.printMembers());
    }
    printlString("How many rounds? Give a number 1-100:");
    int rounds = seeInt();
    printlString("How many seconds for each turn?");
    int duration = seeInt();
    initializeWords();
    play(rounds, duration);
}