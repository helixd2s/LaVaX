#pragma once

// 
#include "pch/pch.h"

// 
#define HPTR(NAME) const vkt::uni_dir<vkh::NAME,::NAME>&
#define UPTR(NAME) const vkt::uni_arg<NAME>&

// 
namespace dxv {
    class VkInstance_T;
    class VkDevice_T;
    class VkQueue_T;
    class VkPhysicalDevice_T;
    class VkDescriptorSetLayout_T;
    class VkDescriptorSet_T;
    class VkDescriptorPool_T;
    class VkPipelineLayout_T;
    class VkCommandPool_T;
    class VkCommandBuffer_T;
};
