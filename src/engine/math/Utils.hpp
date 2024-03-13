#include <cstdint>
#include <unordered_set>

namespace kln {
    uint32_t getAvailableId(std::unordered_set<uint32_t> &set, uint32_t maxValue);
    uint32_t getAvailableId(std::unordered_set<uint32_t> &set, uint32_t minValue, uint32_t maxValue);
} // namespace kln