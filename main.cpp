#include "cache.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: ./cache_sim <num_entries> <associativity> <input_file>\n";
        return 1;
    }

    int numEntries = stoi(argv[1]);
    int assoc = stoi(argv[2]);
    string inputFile = argv[3];

    // --- NEW: print cache info to terminal ---
    cout << "Number of entries: " << numEntries << endl;
    cout << "Associativity: " << assoc << endl;
    cout << "Input file: " << inputFile << endl;
    cout << "Starting cache simulation..." << endl;
    // -----------------------------------------

    ifstream infile(inputFile);
    ofstream outfile("cache_sim_output");

    if (!infile.is_open()) {
        cerr << "Error: could not open input file.\n";
        return 1;
    }

    Cache cache(numEntries, assoc);
    unsigned long addr;

    while (infile >> addr) {
        bool hit = cache.access(outfile, addr);
        outfile << addr << " : " << (hit ? "HIT" : "MISS") << "\n";
    }

    infile.close();
    outfile.close();

    cout << "Simulation complete. Output written to cache_sim_output.\n";

    return 0;
}








