#include<bits/stdc++.h>
#include "rrip.h"
using namespace std;
void rrip::update_rrpv(std::vector<int>& rrpv, std::size_t way, Classification cls, bool is_hit){
    if(cls == Classification::CACHE_AVERSE){
        rrpv[way] = 7;
        return;
    }
    rrpv[way] = 0;
    if(!is_hit){
        for(int i = 0; i < rrpv.size(); i++){
            if(i == way) continue;
            else if(rrpv[i] < 6) rrpv[i]++;
        }
    }
}
// Selects a victim way, aging the set if necessary, per Section 3.4.
std::size_t rrip::find_victim(std::vector<int>& rrpv){
    return max_element(rrpv.begin(), rrpv.end()) - rrpv.begin();
}    
/*
enum class Classification { CACHE_FRIENDLY, CACHE_AVERSE };
// Applies Table 1's update rule to each set's RRPV vector.
void update_rrpv(std::vector<int>& rrpv, std::size_t way, Classification cls, bool is_hit){
    if(cls == Classification::CACHE_AVERSE){
        rrpv[way] = 7;
        return;
    }
    rrpv[way] = 0;
    if(!is_hit){
        for(int i = 0; i < rrpv.size(); i++){
            if(i == way) continue;
            else if(rrpv[i] < 6) rrpv[i]++;
        }
    }
}
// Selects a victim way, aging the set if necessary, per Section 3.4.
std::size_t find_victim(std::vector<int>& rrpv){
    return max_element(rrpv.begin(), rrpv.end()) - rrpv.begin();
}
int main()
{
    // --- Case 1: insertion policy --
    std::vector<int> rrpv = {
    // left empty; the grading script substitutes initial per-way RRPV state
    0,0,0,0
    };
    update_rrpv(rrpv, 0, Classification::CACHE_AVERSE, /*is_hit=*//*false);
    update_rrpv(rrpv, 1, Classification::CACHE_FRIENDLY, /*is_hit=*//*false);
    for (int v : rrpv) std::cout << v << " ";
    std::cout << "\n";
    std::cout << "victim: " << find_victim(rrpv) << "\n";
    // --- Case 2: find a victim --
    std::vector<int> rrpv2 = {
    // left empty; the grading script substitutes initial per-way RRPV state
    2, 4, 5, 3
    };
    std::size_t v = find_victim(rrpv2);
    for (int x : rrpv2) std::cout << x << " ";
    std::cout << "\n";
    std::cout << "victim: " << v << "\n";
}
*/