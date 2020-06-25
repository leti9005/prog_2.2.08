#include <iostream>
#include <string.h>

using namespace std;

struct State {
    char marker = '@';
    char nonRepeatedCharacter;
    char text[1000];
};


unsigned strlen(char text[])
{
    unsigned size = 0;
    while (text[size]) { size++; };
    return size;
}


void duplicateWithShifting(char text[], int index)
{
    auto len = strlen(text);

    auto shiftedLength = len - index;

    char* src = text + index;
    char* dest = src + 1;

    memmove(dest, src, shiftedLength + 1);

    text[index + 1] = text[index];
}


int main(int argc, char* argv[])
{
    State state;

    cout << "Enter text: " << endl;
    cin.getline(state.text, sizeof(state.text));

    cout << "Enter the symbol that won't be repeated: " << endl;
    cin >> state.nonRepeatedCharacter;

    for (unsigned i = 0; state.text[i] != state.marker; i++)
    {
        if (state.text[i] != state.nonRepeatedCharacter)
        {
            duplicateWithShifting(state.text, i);
            i++;
        }
    }

    for (unsigned i = 0; state.text[i] != state.marker; i++)
    {
        cout << state.text[i];
    }

    cout << endl;
}
