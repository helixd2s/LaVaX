#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkBuffer_T.hpp"

namespace lvx {

    VkResult VkBuffer_T::Create(const lvx::VkDevice_T* device, HPTR(VkBufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        
        
        return VK_SUCCESS;
    };

};
