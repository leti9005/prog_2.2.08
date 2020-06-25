#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

struct Node
{
    string text;
    Node* next;
};

// this'is'a'text
// =>
// [
//    "this", // firstNode*
//    "is",
//    "a",
//    "text",
// ]

Node createListFromTextFile(ifstream* stream)
{
    char marker = '\'';

    Node firstNode;
    auto currentNode = &firstNode;

    while (!(*stream).eof())
    {
        char c = stream->get();
        // *stream >> c;

        if (c == '\n')
            break;

        if (c != marker)
        {
            currentNode->text += c;
        }
        else
        {
            // Инпут не должен заканчиваться апострофом,
            // иначе в конце будет лишняя нода.
            currentNode->next = new Node;
            currentNode = currentNode->next;
        }
    }

    return firstNode;
}

int main(int argc, char *argv[])
{
    ifstream s("input.txt");

    Node a = createListFromTextFile(&s);
    s.close();

    auto n = &a;
    do
    {
        cout << n->text << endl;
    } while (n = n->next);
}
