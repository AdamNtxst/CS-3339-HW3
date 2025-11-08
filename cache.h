#ifndef CACHE_H
#define CACHE_H

#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;

class Entry {
private:
    bool valid;
    unsigned tag;
    unsigned long last_used;  

public:
    Entry();
    ~Entry();

    void set_tag(unsigned _tag);
    unsigned get_tag() const;

    void set_valid(bool _valid);
    bool get_valid() const;

    void set_last_used(unsigned long time);    
    unsigned long get_last_used() const;       
};

class Cache {
private:
    int num_entries;
    int assoc;
    int num_sets;
    Entry** entries;
    unsigned long global_time;   
public:
    Cache(int _num_entries, int _assoc);
    ~Cache();

    bool access(ofstream& outfile, unsigned long addr);

private:
    int get_index(unsigned long addr);
    int get_tag(unsigned long addr);
};

#endif

