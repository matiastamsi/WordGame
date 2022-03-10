#include <iostream>

using namespace std;

void printWord(string explainWordText, string word)
{
    cout << explainWordText << word << endl;
}

void printPoints(string statusText, int n, string teams[], int points[])
{
    cout << statusText << endl;
    for (int i = 0; i < n; i++)
    {
        cout << teams[i] << " " << points[i] << endl;
    }
}

char askLanguage()
{
    question:
    cout << "If you want to play in English, please press 'e'."
         << endl;
    cout << "Jos haluat pelata suomeksi, paina 's'."
         << endl;
    char a;
    cin >> a;
    if (a != 'e' && a != 's') goto question;
    return a;
}