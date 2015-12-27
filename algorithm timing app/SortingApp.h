#pragma once

#include <iostream>
#include <string>
#include <algorithm>

#include <vector>
#include "SortingAlgorithms.h"
using namespace std;

class SortingApp
{
private:
    vector<unsigned int> vec;
    int vecSize;
    int numRange;
    time_t start, stop;

private:
    double elapsedTime();
    void menuSA();
    void menu();

    void allocateVec(int size, int range);
    void sortVec(int userInput);

    bool isSorted();

public:    
    void init();
};

bool SortingApp::isSorted()
{
    for (int i = 0; i < vec.size() - 1; i++)
        if (vec[i] > vec[i + 1])
            return false;
    return true;
}

double SortingApp::elapsedTime()
{
    return (double)(stop - start) / (double)CLOCKS_PER_SEC;
}


void SortingApp::menuSA()
{
    cout << "************************************\n"
        << "* Select a search algorithm to test:\n"
        << "* 1. STL Sort                       \n"
        << "* 2. Merge Sort                     \n"
        << "* 3. Shell Sort                     \n"
        << "* 4. Insertion Sort                 \n"
        << "* 5. Quick Sort                     \n"
        << "************************************\n\n\n";
}

void SortingApp::menu()
{
    cout << "************************************\n"
        << "* 1. Set vector size                \n"
        << "* 2. Select sort algorithm          \n"
        << "* 3. Quit                           \n"
        << "************************************\n\n\n";
}


void SortingApp::allocateVec(int size, int range)
{
    srand(time(NULL));
    vec.clear();
    for (int i = 0; i < size; i++)
        vec.push_back(rand() % range);
}

void SortingApp::sortVec(int userInput)
{
    switch (userInput) {

            //STL
        case 1:
            start = clock();
            sort(vec.begin(), vec.end());
            stop = clock();
            cout << "Elapsed time: "
                << elapsedTime() << " seconds."
                << endl << endl;
            break;

            //Merge
        case 2:
            start = clock();
            mergesort(vec);
            stop = clock();
            cout << "Elapsed time: "
                << elapsedTime() << " seconds."
                << endl << endl;
            break;

            //Shell
        case 3:
            start = clock();
            shellSort(vec);
            stop = clock();
            cout << "Elapsed time: "
                << elapsedTime() << " seconds."
                << endl << endl;
            break;

            //Insertion
        case 4:
            start = clock();
            insertionSort(vec);
            stop = clock();
            cout << "Elapsed time: "
                << elapsedTime() << " seconds."
                << endl << endl;
            break;

            //Quick
        case 5:
            start = clock();
            quickSort(vec);
            stop = clock();
            cout << "Elapsed time: "
                << elapsedTime() << " seconds."
                << endl << endl;
            break;

        default:
            break;
    }
    if (!isSorted())
        cout << "DID NOT SORT DID NOT SORT DID NOT SORT" << endl;
}


void SortingApp::init()
{
    while (cin) 
    {
        this->menu();
        string choice = "";
        cout << "Enter your choice: ";
        getline(cin, choice);

        if (choice == "1") 
        {
            cout << "Enter size: ";
            getline(cin, choice);
            
            string choice1 = "";
            cout << "Enter range of random integers: ";
            getline(cin, choice1);
            cout << endl;

            //save vector user input for later
            vecSize = stoi(choice);
            numRange = stoi(choice1);

            this->allocateVec(vecSize, numRange);

            cout << "Vector has been filled with " << choice
                << " random integers ranging from 0 to " << choice1
                << endl << endl;
            continue;
        }
        else if (choice == "2")
        {
            if (vec.empty())
            {
                cout << "Vector is empty, please allocate it (main menu option 1) then try sorting." << endl << endl;
                continue;
            }

            this->menuSA();
            cout << "Enter your choice: ";
            getline(cin, choice);

            cout << "Sorting...\n\n";

            this->sortVec(stoi(choice));
            
            cout << "Randomizing vector again...";
            this->allocateVec(vecSize, numRange);
            cout << "The vector has been randomized.\n\n";
        }
        else
            break;
    }
}