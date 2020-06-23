#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dxv {

    class VkCommandBuffer_T {
    protected:
        ComPtr<ID3D12GraphicsCommandList> commandList = {};
        VkImageViewCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;
        
    public:
        VkCommandBuffer_T() {}
        VkCommandBuffer_T(const dxv::VkDevice_T* device, ComPtr<ID3D12GraphicsCommandList> commandList = {});

        // 
        ID3D12GraphicsCommandList* Get() const { return commandList.Get(); };
    };

};