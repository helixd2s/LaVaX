#pragma once

// 
#include "pch/objects.hpp"

// 
namespace dxv {

    class VkImageView_T {
    protected:
        ComPtr<ID3D12DescriptorHeap> heap = {};
        VkImageViewCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;
        vkt::uni_arg<VkAllocationCallbacks> callbacks = {};

    public:
        VkImageView_T() {}
        VkImageView_T(const dxv::VkDevice_T* device, HPTR(VkImageViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const dxv::VkDevice_T* device, const D3D12_CPU_DESCRIPTOR_HANDLE& Handle);
        VkResult Create(const dxv::VkDevice_T* device, HPTR(VkImageViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks, const D3D12_CPU_DESCRIPTOR_HANDLE& Handle);
        VkResult Create(const dxv::VkDevice_T* device, HPTR(VkImageViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);

        // 
        ComPtr<ID3D12DescriptorHeap>& Heap() { return this->heap; };
        const ComPtr<ID3D12DescriptorHeap>& Heap() const { return this->heap; };

        // 
        D3D12_CPU_DESCRIPTOR_HANDLE Handle() const { return this->heap->GetCPUDescriptorHandleForHeapStart(); };

        // 
        ID3D12DescriptorHeap* Get() const { return heap.Get(); };
    };

};
