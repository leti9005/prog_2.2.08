#include <fstream>
#include <iostream>

using namespace std;

const char marker = '\'';
const size_t max_length = 80;

struct String {
    char text[max_length + 1];
    size_t length = 0;

    String()
    {
    }

    String(const char *str, size_t len)
    {
        size_t i;
        for (i = 0; str[i] != marker && i < len && i < max_length; i++)
        {
            this->text[i] = str[i];
        }

        this->length = i;
    }

    void append(char c)
    {
        this->text[length++] = c;

        if (c == marker) length--;
    }

    bool equals(String str)
    {
        if (this->length != str.length) return false;

        for (size_t i = 0; i < this->length; i++)
        {
            if (this->text[i] != str.text[i])
            {
                return false;
            }
        }

        return true;
    }

    void copy_to(String* dest)
    {
        for (size_t i = 0; i < this->length; i++)
        {
            dest->append(this->text[i]);
        }

        dest->append(marker);
    }

    string to_string() const {
        return string(this->text, this->length);
    }
};

struct Node
{
    String* data = nullptr;
    Node *next = nullptr;

    Node()
    {
        data = new String();
    }

    ~Node() {
        delete data;
    }
};

struct LinkedList
{
    Node* _head = nullptr;

    LinkedList(Node* head)
    {
        _head = head;
    }

    Node* find(const String str, Node* node = nullptr)
    {
        if (!node)
        {
            node = _head;
        }

        if (!node->data->equals(str))
        {
            if (node->next)
            {
                return find(str, node->next);
            }
            else
            {
                return nullptr;
            }
        }

        return node;
    }

    void duplicate(Node* node)
    {
        auto newNode = new Node;
        node->data->copy_to(newNode->data);

        newNode->next = node->next;
        node->next = newNode;
    }

    void repeat(Node* repeated_node, unsigned times)
    {
        for (int i = 0; i < times; i++)
        {
            duplicate(repeated_node);
        }
    }

    void write_to_file(string file_name)
    {
        auto word = _head;
        ofstream fout(file_name);

        while (true)
        {
            fout << word->data->to_string();
            cout << word->data->to_string();

            if (word->next)
            {
                fout << ' ';
                cout << ' ';

                word = word->next;
            }
            else
            {
                fout << marker;
                break;
            }
        }
    }
};

// LinkedList create_list_from_text_file(ifstream* stream, const char marker)
// {
//     Node firstNode;
//     auto currentNode = &firstNode;

//     while (!(*stream).eof())
//     {
//         char c = stream->get();

//         if (c == '\n' || c == marker)
//             break;

//         if (c != ' ')
//         {
//             currentNode->data->append(c);
//         }
//         else
//         {
//             // Ввод не должен заканчиваться маркером,
//             // иначе в конце будет лишняя нода.
//             currentNode->next = new Node;
//             currentNode = currentNode->next;
//         }
//     }

//     LinkedList list(&firstNode);

//     return list;
// }


const char input_file_name[] = "input.txt";
const char output_file_name[] = "output.txt";

// 1 13: Вставить 13) заданное число элементов перед всеми элементами, имеющими заданное значение;

int main()
{

    Node firstNode;
    auto currentNode = &firstNode;

    ifstream fin(input_file_name);
    while (true)
    {
        char c = fin.get();

        if (c == marker)
        {
            currentNode->data->append(marker);
            break;
        }

        if (c == ' ')
        {
            currentNode->data->append(marker);
            currentNode->next = new Node;
            currentNode = currentNode->next;

            continue;
        }

        currentNode->data->append(c);
    }

    LinkedList words(&firstNode);

    // auto words = create_list_from_text_file(&fin, marker);

    int repeat_count;
    cin >> repeat_count;

    string str_repeated_element;
    cin >> str_repeated_element;

    String repeated_element(str_repeated_element.c_str(), str_repeated_element.length());

    auto repeated_node = words.find(repeated_element);

    if (!repeated_node)
    {
        cout << "Can't find the word " << str_repeated_element << " in the text." << endl;
        return 0;
    }

    auto word = words._head;
    words.repeat(repeated_node, repeat_count);

    words.write_to_file(output_file_name);
}
