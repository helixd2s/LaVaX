#pragma once 

#include <vulkan/vulkan.h>

#ifdef BUILD_EXPORTS
#define BUILD_API __declspec(dllexport)
#else
#define BUILD_API __declspec(dllimport)
#endif

namespace dxv {
    BUILD_API VkResult vkCreateDevice(
        VkPhysicalDevice physicalDevice,
        const VkDeviceCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDevice* pDevice
    );
};
