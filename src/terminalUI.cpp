#include <iostream>

using namespace std;

string seeString()
{
    string x;
    cin >> x;
    cin.clear();
    return x;
}

char seeChar()
{
    char c;
    cin >> c;
    cin.clear();
    return c;
}

int seeInt()
{
    int x;
    cin >> x;
    cin.clear();
    return x;
}

void printlInt(int i)
{
    cout << i << endl;
}

void printlString(string str)
{
    cout << str << endl;
}