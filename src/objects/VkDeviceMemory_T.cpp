#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkDeviceMemory_T.hpp"

namespace dxv {

    VkDeviceMemory_T::VkDeviceMemory_T(const dxv::VkDevice_T* device, ComPtr<ID3D12Heap> memoryHeap = {}) : device(VkDevice(device)), memoryHeap(memoryHeap) {
        
    };

};
