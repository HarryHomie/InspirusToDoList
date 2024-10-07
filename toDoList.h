#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>
using namespace std;


struct Task
{
    string task;
    bool isComplete;
    
    Task(string t, bool c)
    {
        task = t;
        isComplete = c;
    }
}

class toDoList
{
    // String pointer
    string* list;
    bool* isDone;

    int max_size = 100;

    // Number of elements in list (<= max size)
    int index = -1;
    
    
    // Attributes for faux-pop
    int fauxIndex = -1;

    public:
        // Constructor
        toDoList()
        {
            list = new string[max_size];
            isDone = new bool[max_size];
        }

        void push(string task)
        {
            if (index+1 < max_size)
            {
                list[++index] = task;
                isDone[index] = false;
            }
            else
            {
                string* temp = list;
                bool* isDoneTemp = isDone;

                max_size = max_size * 2;

                list = new string[max_size];
                isDone = new bool[max_size];

                int max = index + 1;
                for (int i = 0; i < max; i++)
                {
                    list[i] = temp[i];
                    isDone[i] = isDoneTemp[i];
                }

                delete[] temp;
                delete[] isDoneTemp;

                push(task);
            }

        }
        
        void getCount() const
        {
          return index+1;
        }
        
        
        void setupFauxPop()
        {
            fauxIndex = index;
          
        }
        
        
        string fauxPop() const
        {
            if (fauxIndex == -1)
            {
                cerr << "Stack underflow. Use setupFauxPop() before calling fauxPop() or Tasks are empty" << endl;
                return "";     
            }
            
          return list[fauxIndex--];
        }
    
    bool isCompleted()
    {
        return isDone[fauxIndex];
    }
    
    
        

};

#endif