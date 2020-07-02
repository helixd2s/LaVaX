#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkCommandBuffer_T.hpp"

namespace lvx {

    VkCommandBuffer_T::VkCommandBuffer_T(const lvx::VkDevice_T* device, ComPtr<ID3D12GraphicsCommandList> commandList = {}) : device(VkDevice(device)), commandList(commandList) {
        
    };

};
