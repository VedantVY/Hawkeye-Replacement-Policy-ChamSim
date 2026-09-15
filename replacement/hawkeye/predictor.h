#ifndef PREDICTOR_H
#define PREDICTOR_H
#include<bits/stdc++.h>
using namespace std;
class HawkeyePredictor {
    private:
        vector<int> predictions;
        int numEntries, counterBits;
    public:
    // num_entries:  size of the PC-indexed table (paper: 8K entries)
    // counter_bits: width of the saturating counter (paper: 3 bits, range [0, 2^counter_bits - 1])
    HawkeyePredictor(std::size_t num_entries = 8192, int counter_bits = 3);
    // Trains the counter indexed by a hash of `pc` per Section 3.3's update rule.
    void train(uint64_t pc, bool opt_hit);
    // Returns the predicted classification for `pc`.
    bool predict(uint64_t pc) const;
    int get_counter(uint64_t pc) const;
};
#endif