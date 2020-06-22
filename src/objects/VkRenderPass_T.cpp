#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkRenderPass_T.hpp"

namespace dxv {

    VkResult VkRenderPass_T::Create(const dxv::VkDevice_T* device, HPTR(VkRenderPassCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
        this->createInfo = createInfo;
        this->device = VkDevice(device);
        return VK_SUCCESS;
    };

};
