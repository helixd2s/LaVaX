#include <dxv/DXVulkan.hpp>
#include "pch.h"
#include "framework.h"

#include "objects/VkDevice_T.hpp"
#include "objects/VkPhysicalDevice_T.hpp"

#define BUILD_EXPORTS

namespace dxv {

    // Provided by VK_VERSION_1_0
    BUILD_API VkResult vkCreateDevice(
        VkPhysicalDevice physicalDevice,
        const VkDeviceCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDevice* pDevice
    )
    {   // TODO: use pAllocator for allocate that class...
        auto allocation = new VkDevice_T(reinterpret_cast<VkPhysicalDevice_T*>(physicalDevice), *pAllocator, *pCreateInfo);
        *pDevice = VkDevice(allocation);
        return VK_SUCCESS; // TODO: Result Info
    };

};
