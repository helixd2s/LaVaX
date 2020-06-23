#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkBuffer_T.hpp"

namespace dxv {

    VkResult VkBuffer_T::Create(const dxv::VkDevice_T* device, HPTR(VkBufferCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);

        
        
        return VK_SUCCESS;
    };

};
