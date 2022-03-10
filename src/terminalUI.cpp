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

string askLanguage()
{
    string s;
    do
    {
        /* The only hard coded part.
        There is only so few options so
        this will do for now.
        */
        cout << "If you want to play in English, please type 'eng'."
             << endl;
        cout << "Jos haluat pelata suomeksi, kirjoita 'fin'."
             << endl;
        cin >> s;
    } while (s != "eng" && s != "fin");
    return s;
}

int askInt(string s)
{
    // TODO: Check the input
    cout << s << endl;
    int n;
    cin >> n;
    return n;
}

string askString(string s)
{
    cout << s << endl;
    string x;
    cin >> x;
    return x;
}