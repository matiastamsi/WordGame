#include "../headers/terminalUI.h"
#include "../headers/team.h"
#include "../headers/logic.h"
#include <vector>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

// Globals
vector<team> teams;
vector<string> words;
condition_variable cv;
char answer;

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

void handleWhenEveryTeamCanGuess()
{
    string s;
    do
    {
        printlString("Now every team can guess! If some team got it right, type 'r'. If nobody knew, type 's'.");
        s = seeString();
    } while (s != "r" && s != "s");
    if (s == "r")
    {
        printlString("If some team got extra points, type team's name.");
        printlString("The teams are: ");
        for (team t : teams)
        {
            printlString(t.name);
        }
        string t = seeString();
        for (unsigned int i = 0; i < teams.size(); i++)
        {
            if (teams[i].name == t)
                teams[i].points++;
        }
    }
}

void handleAnswer()
{
    answer = seeChar();
    cv.notify_one();
}

int turn(int d)
{
    int points = 0;
    string s;
    do
    {
        printlString("When you are ready, press 'r'. Then one team member explains while other team members try to guess.");
        s = seeString();
    } while (s != "r");
    chrono::duration<int> duration = chrono::seconds{d};
    string word = getRandomWord();
    while (duration.count() > 0)
    {
        thread th(handleAnswer);
        mutex mtx;
        unique_lock<mutex> lck(mtx);
        while (cv.wait_for(lck, chrono::seconds(1)) == cv_status::timeout)
        {
            duration = duration - chrono::seconds{1};
            if (duration.count() < 0)
            {
                th.detach();
                handleWhenEveryTeamCanGuess();
                return points;
            }
            printlString("Time left: " + to_string(duration.count()));
            printlString("Explain word: " + word);
            printlString("Correct answer (+1p): press 'c'. Skip word (-1p): press 's'.");
        }
        if (answer == 'c')
            points += 1;
        if (answer == 's')
            points -= 1;
        word = getRandomWord();
        th.join();
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