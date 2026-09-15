#ifndef OPTGEN_H
#define OPTGEN_H
#include<bits/stdc++.h>
using namespace std; 
class OPTgen {
    private:
        vector<vector<pair<uint64_t, int>>> occupancyVector;
        vector<vector<pair<pair<uint64_t, uint64_t>, uint64_t>>> historyTable;
        int sets, associativity, history;
    public:
        // num_sets: number of cache sets tracked independently
        // associativity: W, the cache associativity (occupancy vector cap)
        // history_multiplier: length of tracked history, in units of the set's
        //                       capacity (paper uses 8x; see Figure 2). Default 8.
        OPTgen(std::size_t num_sets, std::size_t associativity,
        std::size_t history_multiplier = 8);
        // Processes one access to `address`, mapped to set `set_idx`, per Section 3.1.
        bool access(std::size_t set_idx, uint64_t address);
};
#endif