#include "cache.h"

Entry::Entry() : valid(false), tag(0), last_used(0) {}
Entry::~Entry() {}

void Entry::set_tag(unsigned _tag) { tag = _tag; }
unsigned Entry::get_tag() const { return tag; }

void Entry::set_valid(bool _valid) { valid = _valid; }
bool Entry::get_valid() const { return valid; }

void Entry::set_last_used(unsigned long time) { last_used = time; }
unsigned long Entry::get_last_used() const { return last_used; }

Cache::Cache(int _num_entries, int _assoc) {
    assoc = _assoc;
    num_entries = _num_entries;
    num_sets = num_entries / assoc;
    global_time = 0;

    entries = new Entry*[num_sets];
    for (int i = 0; i < num_sets; i++) {
        entries[i] = new Entry[assoc];
    }
}

Cache::~Cache() {
    for (int i = 0; i < num_sets; i++)
        delete[] entries[i];
    delete[] entries;
}

bool Cache::access(ofstream& outfile, unsigned long addr) {
    int index = get_index(addr);
    unsigned tag = get_tag(addr);
    global_time++;

    // Check for hit
    for (int i = 0; i < assoc; i++) {
        if (entries[index][i].get_valid() && entries[index][i].get_tag() == tag) {
            entries[index][i].set_last_used(global_time); // update LRU
            return true;  // HIT
        }
    }

    // MISS — try to fill invalid
    for (int i = 0; i < assoc; i++) {
        if (!entries[index][i].get_valid()) {
            entries[index][i].set_tag(tag);
            entries[index][i].set_valid(true);
            entries[index][i].set_last_used(global_time);
            return false;
        }
    }

    // MISS — replace LRU
    int lru_index = 0;
    unsigned long min_time = entries[index][0].get_last_used();
    for (int i = 1; i < assoc; i++) {
        if (entries[index][i].get_last_used() < min_time) {
            min_time = entries[index][i].get_last_used();
            lru_index = i;
        }
    }
    entries[index][lru_index].set_tag(tag);
    entries[index][lru_index].set_last_used(global_time);

    return false;
}

int Cache::get_index(unsigned long addr) {
    return addr & (num_sets - 1);
}

int Cache::get_tag(unsigned long addr) {
    return addr >> int(log2(num_sets));
}




