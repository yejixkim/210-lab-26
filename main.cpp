// COMSC 210 | Lab 26 | Yeji Kim

#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <iterator>
#include <iomanip>
using namespace std;
using namespace chrono;

struct RaceResult {
    string operation;
    long long vectorTime;
    long long listTime;
    long long setTime;
};

int main() {
    // make a vector, list, and set to store the codes
    vector<string> codesVector;
    list<string> codesList;
    set<string> codesSet;

    // open codes file
    ifstream inputFile("names.txt");

    // check file
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string code;

    // measure how long it takes to read the codes into the vector
    auto start = high_resolution_clock::now();

    while(inputFile >> code) {
        codesVector.push_back(code);
    }

    auto end = high_resolution_clock::now();
    auto vectorReadTime = duration_cast<nanoseconds>(end - start).count();

    // reset the file so it can be read again
    inputFile.clear();
    inputFile.seekg(0);

    // measure how long it takes to read the codes into the list
    start = high_resolution_clock::now();

    while (inputFile >> code) {
        codesList.push_back(code);
    }

    end = high_resolution_clock::now();
    auto listReadTime = duration_cast<nanoseconds>(end - start).count();

    // reset the file before reading the codes into the set
    inputFile.clear();
    inputFile.seekg(0);

    // measure how long it takes to read the codes into the set
    start = high_resolution_clock::now();

    while(inputFile >> code) {
        codesSet.insert(code);
    }

    end = high_resolution_clock::now();
    auto setReadTime = duration_cast<nanoseconds>(end - start).count();

    // store the times for sorting, insertion, and deletion
    long long vectorSortTime;
    long long listSortTime;
    long long setSortTime = -1; // set keeps its elements sorted automatically

    long long vectorInsertTime;
    long long listInsertTime;
    long long setInsertTime;

    long long vectorDeleteTime;
    long long listDeleteTime;
    long long setDeleteTime;

    // measure how long it takes to sort the vector
    start = high_resolution_clock::now();

    sort(codesVector.begin(), codesVector.end());

    end = high_resolution_clock::now();
    vectorSortTime = duration_cast<nanoseconds>(end - start).count();

    // measure how long it takes to sort the list
    start = high_resolution_clock::now();

    codesList.sort();

    end = high_resolution_clock::now();
    listSortTime = duration_cast<nanoseconds>(end - start).count();

    // insert a new code into the middle of the vector
    start = high_resolution_clock::now();

    codesVector.insert(codesVector.begin() + codesVector.size() / 2, "TESTCODE");

    end = high_resolution_clock::now();
    vectorInsertTime = duration_cast<nanoseconds>(end - start).count();

    // find the middle of the list and insert the new code
    start = high_resolution_clock::now();

    auto listMiddle = codesList.begin();
    advance(listMiddle, codesList.size() / 2);
    codesList.insert(listMiddle, "TESTCODE");

    end = high_resolution_clock::now();
    listInsertTime = duration_cast<nanoseconds>(end - start).count();

    // measure how long it takes to insert the new code into the set
    start = high_resolution_clock::now();

    codesSet.insert("TESTCODE");

    end = high_resolution_clock::now();
    setInsertTime = duration_cast<nanoseconds>(end - start).count();

    // remove an element from the middle of the vector
    start = high_resolution_clock::now();

    codesVector.erase(codesVector.begin() + codesVector.size() / 2);

    end = high_resolution_clock::now();
    vectorDeleteTime = duration_cast<nanoseconds>(end - start).count();

    // find the middle of the list and remove that element
    start = high_resolution_clock::now();

    auto listDelete = codesList.begin();
    advance(listDelete, codesList.size() / 2);
    codesList.erase(listDelete);

    end = high_resolution_clock::now();
    listDeleteTime = duration_cast<nanoseconds>(end - start).count();

    // find the middle element of the set and remove it
    start = high_resolution_clock::now();

    auto setDelete = codesSet.begin();
    advance(setDelete, codesSet.size() / 2);
    codesSet.erase(setDelete);

    end = high_resolution_clock::now();
    setDeleteTime = duration_cast<nanoseconds>(end - start).count();

    // close the input file after all reading is complete
    inputFile.close();

    // store the results for each operation
    vector<RaceResult> results = {
        {"Reading", vectorReadTime, listReadTime, setReadTime},
        {"Sorting", vectorSortTime, listSortTime, setSortTime},
        {"Insertion", vectorInsertTime, listInsertTime, setInsertTime},
        {"Deletion", vectorDeleteTime, listDeleteTime, setDeleteTime}
    };

    // print the comparison table
    cout << "\nPerformance Comparison (nanoseconds)\n\n";

    cout << left << setw(18) << "Operation"
         << right << setw(16) << "Vector"
         << setw(16) << "List"
         << setw(16) << "Set" << '\n';

    cout << string(66, '-') << '\n';

    // display each race from the results vector
    for (const RaceResult& result : results) {
        cout << left << setw(18) << result.operation
             << right << setw(16) << result.vectorTime
             << setw(16) << result.listTime
             << setw(16) << result.setTime << '\n';
    }

    return 0;
}