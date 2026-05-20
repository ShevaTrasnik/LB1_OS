#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream inputFile("input.txt", ios::binary);
    if (!inputFile.is_open())
    {
        cout << "Ne вдалося відкрити файл input.txt" << endl;
        return 1;
    }
    string text(
        (istreambuf_iterator<char>(inputFile)),
        istreambuf_iterator<char>()
    );
    inputFile.close();
    reverse(text.begin(), text.end());
    ofstream outputFile("output.txt", ios::binary);
    if (!outputFile.is_open())
    {
        cout << "Ne вдалося створити файл output.txt" << endl;
        return 1;
    }
    outputFile << text;
    outputFile.close();
    cout << "Pochatkovyi tekst:" << endl;
    cout << endl;
    cout << string(text.rbegin(), text.rend()) << endl;
    cout << endl;
    cout << "Tekst u zvorotnomu poriadku:" << endl;
    cout << endl;
    cout << text << endl;
    cout << endl;
    cout << "Rezultat zapisano u output.txt" << endl;
    return 0;
}