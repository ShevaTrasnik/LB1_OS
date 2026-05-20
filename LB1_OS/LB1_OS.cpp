#include <iostream>
#include <tchar.h>
#include <locale.h>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
int compareUnicodeStrings(const void* a, const void* b)
{
    const wchar_t* str1 = *(const wchar_t**)a;
    const wchar_t* str2 = *(const wchar_t**)b;
    return wcscmp(str1, str2);
}
int main()
{
    _tsetlocale(LC_ALL, _T("Ukrainian"));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    _tprintf(_T("Rozmir typu TCHAR: %d bait\n"), sizeof(TCHAR));
#ifdef UNICODE
    _tprintf(_T("Rezhym koduvannia: UNICODE\n"));
#else
    _tprintf(_T("Rezhym koduvannia: ASCII / MultiByte\n"));
#endif
    const char* asciiNames[] =
    {
        "Shevchun Olena",
        "Shevchun Vova",
        "Shevchun Maksym"
    };
    const int count = 3;
    
    cout << "\nASCII riadky:" << endl;
    for (int i = 0; i < count; i++)
    {
        cout << asciiNames[i] << endl;
    }

    wchar_t unicodeNames[count][100];
    for (int i = 0; i < count; i++)
    {
        MultiByteToWideChar(
            CP_ACP,
            0,
            asciiNames[i],
            -1,
            unicodeNames[i],
            100
        );
    }

    _tprintf(_T("\nUnicode riadky za dopomohoiu _tprintf:\n"));
    for (int i = 0; i < count; i++)
    {
        _tprintf(_T("%ls\n"), unicodeNames[i]);
    }
    wcout << L"\nUnicode riadky za dopomohoiu wcout:" << endl;
    for (int i = 0; i < count; i++)
    {
        wcout << unicodeNames[i] << endl;
    }
    MessageBoxW(
        0,
        unicodeNames[0],
        L"Unicode MessageBox",
        MB_OK
    );
    wchar_t* qsortArray[count];
    for (int i = 0; i < count; i++)
    {
        qsortArray[i] = unicodeNames[i];
    }
    qsort(
        qsortArray,
        count,
        sizeof(wchar_t*),
        compareUnicodeStrings
    );
    wcout << L"\nVidsortovanyi masyv Unicode za dopomohoiu qsort:" << endl;
    for (int i = 0; i < count; i++)
    {
        wcout << qsortArray[i] << endl;
    }
    vector<wstring> sortVector;
    for (int i = 0; i < count; i++)
    {
        sortVector.push_back(unicodeNames[i]);
    }
    sort(sortVector.begin(), sortVector.end());
    wcout << L"\nVidsortovanyi masyv Unicode za dopomohoiu sort:" << endl;
    for (int i = 0; i < count; i++)
    {
        wcout << sortVector[i] << endl;
    }
    char convertedAscii[count][100];
    for (int i = 0; i < count; i++)
    {
        WideCharToMultiByte(
            CP_ACP,
            0,
            unicodeNames[i],
            -1,
            convertedAscii[i],
            100,
            NULL,
            NULL
        );
    }
    cout << "\nUnicode -> ASCII:" << endl;
    for (int i = 0; i < count; i++)
    {
        cout << convertedAscii[i] << endl;
    }
    return 0;
}