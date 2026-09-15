#include<bits/stdc++.h>
#include "./predictor.h"
using namespace std;
HawkeyePredictor:: HawkeyePredictor(std::size_t num_entries, int counter_bits){
    this->predictions.resize(num_entries, 1 << (counter_bits-1));
    this->numEntries = num_entries;
    this->counterBits = counter_bits;
}
void HawkeyePredictor :: train(uint64_t pc, bool opt_hit){
    size_t index = (pc ^ (pc >> 12)) & (this->numEntries - 1); 
    if(opt_hit && this->predictions[index] < (pow(2,this->counterBits) - 1)) this->predictions[index]++;
    else if(!opt_hit && this->predictions[index] > 0) this->predictions[index]--;
}
bool HawkeyePredictor :: predict(uint64_t pc) const{
    return (this->predictions[(pc ^ (pc >> 12)) & (this->numEntries - 1)] >> (this->counterBits - 1));
}
int HawkeyePredictor :: get_counter(uint64_t pc) const{
    return (this->predictions[(pc ^ (pc >> 12)) & (this->numEntries - 1)]);
}
/*class HawkeyePredictor {
    private:
        vector<int> predictions;
        int numEntries, counterBits;
    public:
    // num_entries:  size of the PC-indexed table (paper: 8K entries)
    // counter_bits: width of the saturating counter (paper: 3 bits, range [0, 2^counter_bits - 1])
    HawkeyePredictor(std::size_t num_entries = 8192, int counter_bits = 3){
        this->predictions.resize(num_entries, 1 << (counter_bits-1));
        this->numEntries = num_entries;
        this->counterBits = counter_bits;
    }
    // Trains the counter indexed by a hash of `pc` per Section 3.3's update rule.
    void train(uint64_t pc, bool opt_hit){
        size_t index = (pc ^ (pc >> 12)) & (this->numEntries - 1); 
        if(opt_hit && this->predictions[index] < (pow(2,this->counterBits) - 1)) this->predictions[index]++;
        else if(!opt_hit && this->predictions[index] > 0) this->predictions[index]--;
    }
    // Returns the predicted classification for `pc`.
    bool predict(uint64_t pc) const{
        return (predictions[(pc ^ (pc >> 12)) & (this->numEntries - 1)] >> (this->counterBits - 1));
    }
    // Debug-only accessor: raw counter value in [0, 2^counter_bits - 1].
    int get_counter(uint64_t pc) const{
        return (predictions[(pc ^ (pc >> 12)) & (this->numEntries - 1)]);
    }
};
int main() {
    HawkeyePredictor pred;
    // TEST_VECTOR_START
    // train_events: ordered (pc, opt_hit) pairs applied via pred.train(pc, opt_hit)
    //std::vector<std::pair<uint64_t, bool>> train_events = {{}};
    // query_pcs: pcs to print counter/prediction for, after all training is applied
    //std::vector<uint64_t> query_pcs = {};

std::vector<std::pair<uint64_t, bool>> train_events = {
    {0x1000, false},
    {0x1000, false},
    {0x1000, false},
    {0x1000, false},
    {0x1000, false},
    {0x1000, false},
    {0x1000, false},
    {0x1000, false},
    {0x1000, false},
    {0x1000, false}
};

std::vector<uint64_t> query_pcs = {
    0x1000
};


    // TEST_VECTOR_END
    for (auto& [pc, opt_hit] : train_events) {
        pred.train(pc, opt_hit);
    }
    for (uint64_t pc : query_pcs) {
        std::cout << std::hex << pc << std::dec
        << ": counter=" << pred.get_counter(pc)
        << " predict=" << pred.predict(pc) << "\n";
    }
}*/