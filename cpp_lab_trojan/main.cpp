#include <iostream>
#include <string.h>

using namespace std;


struct ProgramState {
    char marker = '\'';
    char text[1000];
};


int main(int argc, char* argv[])
{
    ProgramState prog;

    cout << "Input text: " << endl;
    cin.getline(prog.text, sizeof(prog.text));

    int maxSpacesSequenceIndex = -1;
    int maxSpaces = 0;

    int currentSpacesSequenceIndex = -1;
    int currentSequenceSpaces = 0;

    for (int i = 0; prog.text[i] != prog.marker; i++)
    {
        if (prog.text[i] != ' ')
        {
            if (currentSequenceSpaces > maxSpaces)
            {
                // Обновить информацию о последовательности пробелов с максимальной длиной.
                maxSpaces = currentSequenceSpaces;
                maxSpacesSequenceIndex = currentSpacesSequenceIndex;
            }

            // Обнулить сведения о текущей последовательности пробелов.
            currentSpacesSequenceIndex = -1;
            currentSequenceSpaces = 0;
        }
        else
        {
            if (currentSpacesSequenceIndex == -1)
            {
                currentSpacesSequenceIndex = i;
                currentSequenceSpaces = 1;
            }
            else
            {
                currentSequenceSpaces++;
            }
        }
    }

    cout << maxSpacesSequenceIndex;
}
