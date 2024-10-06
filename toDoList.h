#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>
using namespace std;


class toDoList
{
    // String pointer
    string* list;

    int max_size = 100;

    // Number of elements in list (<= max size)
    int index = -1;

    public:
        // Constructor
        toDoList()
        {
            list = new string[max_size];
        }

        void push(string task)
        {
            if (index+1 < max_size)
            {
                list[++index] = task;
            }
            else
            {
                string* temp = list;

                max_size = max_size * 2;

                list = new string[max_size];

                int max = index + 1;
                for (int i = 0; i < max; i++)
                {
                    list[i] = temp[i];
                }

                delete[] temp;

                push(task);
            }

        }

};

#endif