#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkDeviceMemory_T.hpp"

namespace dvx {

    VkDeviceMemory_T::VkDeviceMemory_T(const dvx::VkDevice_T* device, ComPtr<ID3D12Heap> memoryHeap = {}) : device(VkDevice(device)), memoryHeap(memoryHeap) {
        
    };

};
