#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkDeviceMemory_T.hpp"

namespace lvx {

    VkDeviceMemory_T::VkDeviceMemory_T(const lvx::VkDevice_T* device, ComPtr<ID3D12Heap> memoryHeap) : device(VkDevice(device)), memoryHeap(memoryHeap) {
        
    };

};
