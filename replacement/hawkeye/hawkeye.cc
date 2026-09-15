#include<bits/stdc++.h>
#include "hawkeye.h"
using namespace std;
hawkeye::hawkeye(CACHE* cache) : hawkeye(cache, cache->NUM_SET, cache->NUM_WAY) {}
hawkeye::hawkeye(CACHE* cache, long sets, long ways) : replacement(cache), NUM_WAYS(ways), NUM_SET(sets), multiplicity(8), OFFSET_BITS(cache->OFFSET_BITS), optgen(sets, ways), RRPV(sets){
  //std::cout <<"Hawkeye Implementation"<< "\n";
  for(int i = 0; i < sets; i++) RRPV[i].resize(ways,7);
}
long hawkeye::find_victim(uint32_t triggering_cpu, uint64_t instr_id, long set, const champsim::cache_block* current_set, champsim::address ip,
                      champsim::address full_addr, access_type type)
{
  for(int way = 0; way < this->NUM_WAYS; way++){
    if(!current_set[way].valid) return way;
  }
  return rrip::find_victim(RRPV[set]);
}

void hawkeye::replacement_cache_fill(uint32_t triggering_cpu, long set, long way, champsim::address full_addr, champsim::address ip, champsim::address victim_addr,
                                 access_type type)
{
}

void hawkeye::update_replacement_state(uint32_t triggering_cpu, long set, long way, champsim::address full_addr, champsim::address ip,
                                   champsim::address victim_addr, access_type type, uint8_t hit)
{
   if(!hit && RRPV[set][way] < 7){   
    uint64_t victimBlockAddr = victim_addr.to<uint64_t>() >> champsim::to_underlying(OFFSET_BITS);
    auto victimEntry = sampledCache.find(victimBlockAddr);
    if(victimEntry != sampledCache.end()){
      predictor.train(victimEntry->second.to<uint64_t>(), false);
    }
    /*for(auto& entry : sampledCache){
      if(entry.first == victimBlockAddr){
        predictor.train(entry.second.to<uint64_t>(), false); 
        break;
      }
    }*/
  }
  Classification cls = predictor.predict(ip.to<uint64_t>()) ? Classification::CACHE_FRIENDLY : Classification::CACHE_AVERSE;
  rrip::update_rrpv(RRPV[set], way, cls, hit);
  if (access_type{type} == access_type::WRITE) return;
  //bool isFound = false;
  uint64_t blockAddr = full_addr.to<uint64_t>() >> champsim::to_underlying(OFFSET_BITS);
  auto entry = sampledCache.find(blockAddr);
  if(entry != sampledCache.end()){
    predictor.train(entry->second.to<uint64_t>(), optgen.access(set, blockAddr));
    entry->second = ip;
  } else {
    optgen.access(set, blockAddr);
    sampledCache.emplace(blockAddr, ip);
  }
  /*for(std::size_t i = 0; i < sampledCache.size(); i++){
    if(sampledCache[i].first == blockAddr){
      isFound = true;
      predictor.train(sampledCache[i].second.to<uint64_t>(), optgen.access(set, blockAddr));
      sampledCache[i].second = ip;
      break;
    }
  }
  if(!isFound){
    optgen.access(set, blockAddr);
    sampledCache.push_back({blockAddr, ip});
  }*/
  // Mark the way as being used on the current cycle
 // if (hit && access_type{type} != access_type::WRITE) // Skip this for writeback hits
}