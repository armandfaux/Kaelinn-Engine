#include "Utils.hpp"

namespace ge {
    uint32_t getAvailableId(std::unordered_set<uint32_t> &set, uint32_t maxValue) {
        uint32_t id = 1;

        while (set.find(id) != set.end()) {
            if (++id > maxValue) {
                // No available id was found
                return 0;
            }
        }
        return id;
    }

    uint32_t getAvailableId(std::unordered_set<uint32_t> &set, uint32_t minValue, uint32_t maxValue) {
        uint32_t id = std::max(static_cast<uint32_t>(1), minValue);

        while (set.find(id) != set.end()) {
            if (++id > maxValue) {
                // No available id was found
                return 0;
            }
        }
        return id;
    }
} // namespace ge