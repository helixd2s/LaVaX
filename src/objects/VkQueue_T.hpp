#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dxv {

    class VkQueue_T {
    protected:
        ComPtr<ID3D12CommandQueue> commandQueue = {};
        VkImageViewCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;

    public:
        VkQueue_T() {}
        VkQueue_T(const dxv::VkDevice_T* device, ComPtr<ID3D12CommandQueue> commandQueue);

        // 
        ID3D12CommandQueue* Get() const { return commandQueue.Get(); };
    };

};
