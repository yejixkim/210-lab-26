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

int main() {
    const int NUM_SIMULATIONS = 15;
    const int NUM_OPERATIONS = 4;
    const int NUM_STRUCTURES = 3;

    // 3D array:
    // first dimension: 15 simulation runs (0-14) + 1 totals slice (15)
    // second dimension: operations (0 = read, 1 = sort, 2 = insert, 3 = delete)
    // third dimension: data structures (0 = vector, 1 = list, 2 = set)
    long long times[16][NUM_OPERATIONS][NUM_STRUCTURES] = {};

    
    // run the experiment 15 times
    for (int run = 0; run < NUM_SIMULATIONS; run++) {
        // new containers for this run
        vector<string> codesVector;
        list<string> codesList;
        set<string> codesSet;
        string code;

        // read names into the vector
        ifstream vectorFile("names.txt");
        if (!vectorFile) {
            cerr << "Error opening names.txt" << endl;
            return 1;
        }

        auto start = high_resolution_clock::now();

        while (vectorFile >> code) {
            codesVector.push_back(code);
        }

        auto end = high_resolution_clock::now();
        times[run][0][0] =
            duration_cast<nanoseconds>(end - start).count();
        vectorFile.close();

        // read names into the list
        ifstream listFile("names.txt");
        if (!listFile) {
            cerr << "Error opening names.txt" << endl;
            return 1;
        }

        start = high_resolution_clock::now();

        while (listFile >> code) {
            codesList.push_back(code);
        }

        end = high_resolution_clock::now();
        times[run][0][1] =
            duration_cast<nanoseconds>(end - start).count();
        listFile.close();

        // read names into the set
        ifstream setFile("names.txt");
        if (!setFile) {
            cerr << "Error opening names.txt" << endl;
            return 1;
        }

        start = high_resolution_clock::now();

        while (setFile >> code) {
            codesSet.insert(code);
        }

        end = high_resolution_clock::now();
        times[run][0][2] =
            duration_cast<nanoseconds>(end - start).count();
        setFile.close();

        // sort the vector
        start = high_resolution_clock::now();
        sort(codesVector.begin(), codesVector.end());
        end = high_resolution_clock::now();

        times[run][1][0] =
            duration_cast<nanoseconds>(end - start).count();

        // sort the list
        start = high_resolution_clock::now();
        codesList.sort();
        end = high_resolution_clock::now();

        times[run][1][1] =
            duration_cast<nanoseconds>(end - start).count();

        // set is already sorted
        times[run][1][2] = 0;

        // insert into the middle of the vector
        start = high_resolution_clock::now();

        codesVector.insert(
            codesVector.begin() + codesVector.size() / 2,
            "TESTCODE"
        );

        end = high_resolution_clock::now();
        times[run][2][0] =
            duration_cast<nanoseconds>(end - start).count();

        // insert into the middle of the list
        start = high_resolution_clock::now();

        auto listMiddle = codesList.begin();
        advance(listMiddle, codesList.size() / 2);
        codesList.insert(listMiddle, "TESTCODE");

        end = high_resolution_clock::now();
        times[run][2][1] =
            duration_cast<nanoseconds>(end - start).count();

        // insert into the set
        start = high_resolution_clock::now();

        codesSet.insert("TESTCODE");

        end = high_resolution_clock::now();
        times[run][2][2] =
            duration_cast<nanoseconds>(end - start).count();

        // delete from the middle of the vector
        start = high_resolution_clock::now();

        codesVector.erase(
            codesVector.begin() + codesVector.size() / 2
        );

        end = high_resolution_clock::now();
        times[run][3][0] =
            duration_cast<nanoseconds>(end - start).count();

        // delete from the middle of the list
        start = high_resolution_clock::now();

        auto listDelete = codesList.begin();
        advance(listDelete, codesList.size() / 2);
        codesList.erase(listDelete);

        end = high_resolution_clock::now();
        times[run][3][1] =
            duration_cast<nanoseconds>(end - start).count();

        // delete the middle element of the set
        start = high_resolution_clock::now();

        auto setDelete = codesSet.begin();
        advance(setDelete, codesSet.size() / 2);
        codesSet.erase(setDelete);

        end = high_resolution_clock::now();
        times[run][3][2] =
            duration_cast<nanoseconds>(end - start).count();

        // add this run's results to the accumulator slice (index 15)
        for (int operation = 0;
             operation < NUM_OPERATIONS; operation++) {
            for (int structure = 0;
                 structure < NUM_STRUCTURES; structure++) {
                times[15][operation][structure] +=
                    times[run][operation][structure];
            }
        }
    }

    // display avg runtimes
    cout << "Number of simulations: " << NUM_SIMULATIONS << "\n\n";

    cout << right << setw(12) << "Operation" 
        << setw(12) << "Vector"
        << setw(12) << "List"
        << setw(12) << "Set" << '\n';

    cout << string(48, '-') << '\n';

    string operations[] = {"Read", "Sort", "Insert", "Delete"};

    for (int operation = 0; 
        operation < NUM_OPERATIONS; operation++) {
            cout << right << setw(12) << operations[operation];

            for (int structure = 0; 
                structure < NUM_STRUCTURES; structure++) {
                    // calc avg runtime in nanoseconds
                    long long average = times[15][operation][structure] / NUM_SIMULATIONS;
                
                    cout << setw(12) << average;
            }
        cout << '\n';
    }
    
    return 0;
}