#include<bits/stdc++.h>
#include "./optgen.h"
using namespace std;
OPTgen :: OPTgen(std::size_t num_sets, std::size_t associativity, std::size_t history_multiplier){
    this->occupancyVector.resize(num_sets);
        //for(int i = 0; i < num_sets; i++) this->occupancyVector[i].resize(associativity*history_multiplier);
    this->sets = num_sets;
    this->associativity = associativity;
    this->history = history_multiplier;
}
bool OPTgen :: access(std::size_t set_idx, uint64_t address){
    if(!occupancyVector[set_idx].size()){
        occupancyVector[set_idx].resize(1, pair<uint64_t, int>(address,0));
        return false;
    }
    bool overlap = false;
    int foundAtIndex = -1;
    for(int i = static_cast<int>(occupancyVector[set_idx].size()) - 1; i >= 0; i--){
        overlap = (overlap) || (occupancyVector[set_idx][i].second == this->associativity);
        if(overlap) break;
        if(occupancyVector[set_idx][i].first != address) continue;
        foundAtIndex = i;
        break;
    }
    if(foundAtIndex != -1 && !overlap) for(int i = foundAtIndex; i < occupancyVector[set_idx].size(); i++) occupancyVector[set_idx][i].second++;
    if(occupancyVector[set_idx].size() >= this->associativity*this->history) occupancyVector[set_idx].erase(occupancyVector[set_idx].begin());
    occupancyVector[set_idx].push_back(pair<uint64_t,int>(address, 0));
    return foundAtIndex != -1 && !overlap;
}
/*class OPTgen {
    private:
        vector<vector<pair<uint64_t, int>>> occupancyVector;
        int sets, associativity, history;
    public:
        // num_sets: number of cache sets tracked independently
        // associativity: W, the cache associativity (occupancy vector cap)
        // history_multiplier: length of tracked history, in units of the set's
        //                       capacity (paper uses 8x; see Figure 2). 
        OPTgen(std::size_t num_sets, std::size_t associativity,
        std::size_t history_multiplier = 8){
            this->occupancyVector.resize(num_sets);
            //for(int i = 0; i < num_sets; i++) this->occupancyVector[i].resize(associativity*history_multiplier);
            this->sets = num_sets;
            this->associativity = associativity;
            this->history = history_multiplier;
        }
        // Processes one access to `address`, mapped to set `set_idx`, per 
        bool access(std::size_t set_idx, uint64_t address){
            if(!occupancyVector[set_idx].size()){
                occupancyVector[set_idx].resize(1, pair<uint64_t, int>(address,0));
                return false;
            }
            bool overlap = false;
            int foundAtIndex = -1;
            for(int i = static_cast<int>(occupancyVector[set_idx].size()) - 1; i >= 0; i--){
                overlap = (overlap) || (occupancyVector[set_idx][i].second == this->associativity);
                if(overlap) break;
                if(occupancyVector[set_idx][i].first != address) continue;
                foundAtIndex = i;
                break;
            }
            if(foundAtIndex != -1 && !overlap) for(int i = foundAtIndex; i < occupancyVector[set_idx].size(); i++) occupancyVector[set_idx][i].second++;
            if(occupancyVector[set_idx].size() >= this->associativity*this->history) occupancyVector[set_idx].erase(occupancyVector[set_idx].begin());
            occupancyVector[set_idx].push_back(pair<uint64_t,int>(address, 0));
            return foundAtIndex != -1 && !overlap;
        }
};
int main(){
    OPTgen opt = OPTgen(1,2);
    std::vector<std::pair<std::size_t, uint64_t>> accesses = {{0,0}, {0,1}, {0,1}, {0,2}, {0,3}, {0,4}, {0,0}, {0,5}, {0,3}, {0,4}, {0,5}, {0,2}};
    int hits = 0;
    for (auto& [set_idx, addr] : accesses) {
    bool hit = opt.access(set_idx, addr);
    std::cout << std::hex << addr << std::dec << ": " << (hit ? "HIT" : 
    "MISS") << "\n";
    if (hit) hits++;
    }
    std::cout << "TOTAL HITS: " << hits << "\n";
}*/