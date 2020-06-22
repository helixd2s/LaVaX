#pragma once

#include "generals/objects.hpp"

// 
namespace dxv {
    class VkDevice_T {
    protected:
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        ComPtr<ID3D12Device> device = {};

    public:
        VkDevice_T() {}
        VkDevice_T(const dxv::VkPhysicalDevice_T* physicalDevice, HPTR(VkDeviceCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);
        ComPtr<ID3D12Device> getDevice() const { return this->device; }
    };
};
