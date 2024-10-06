#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>
using namespace std;


struct toDoList
{
    // String pointer
    string* list;

    // Number of elements in list (<= max size)
    int length;

    // Constructor
    toDoList(int max_size)
    {
        list = new string[max_size];
        length = 0;
    }

};

#endif