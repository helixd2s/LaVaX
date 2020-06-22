#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dxv {
    class VkDevice_T {
    protected:
        ComPtr<ID3D12Device> device = {};
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        std::vector<const char*> enabledExtensions = {};
        std::vector<const char*> enabledLayers = {};

    public:
        VkDevice_T() {}
        VkDevice_T(const dxv::VkPhysicalDevice_T* physicalDevice, HPTR(VkDeviceCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        ComPtr<ID3D12Device> getDevice() const { return this->device; }
    };
};
