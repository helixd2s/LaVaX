#include <dvx/DXVulkan.hpp>

#include "pch/pch.h"
#include "objects/VkDevice_T.hpp"
#include "objects/VkPhysicalDevice_T.hpp"

#ifndef BUILD_EXPORTS
#define BUILD_EXPORTS
#endif

namespace dvx {

    // 
    BUILD_API VkResult vkCreateDevice(
        VkPhysicalDevice physicalDevice,
        const VkDeviceCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDevice* pDevice
    )
    {   // TODO: use pAllocator for allocate that class...
        auto allocation = new VkDevice_T(reinterpret_cast<VkPhysicalDevice_T*>(physicalDevice), pCreateInfo, *pAllocator);
        *pDevice = VkDevice(allocation);
        return VK_SUCCESS; // TODO: Result Info
    };

};
