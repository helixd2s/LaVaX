#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {

    class VkBufferView_T {
    protected:
        ComPtr<ID3D12DescriptorHeap> heap = {};
        ComPtr<ID3D12Resource> resource = {};
        VkBufferViewCreateInfo createInfo = {};
        VkDevice device = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;

    public:
        VkBufferView_T() {}
        VkBufferView_T(const lvx::VkDevice_T* device, HPTR(VkBufferViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(device, createInfo, callbacks);
        };

        // 
        VkResult Create(const lvx::VkDevice_T* device, HPTR(VkBufferViewCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);

        // 
        ComPtr<ID3D12DescriptorHeap>& Heap() { return this->heap; };
        const ComPtr<ID3D12DescriptorHeap>& Heap() const { return this->heap; };

        //
        D3D12_CPU_DESCRIPTOR_HANDLE Handle() const { return this->heap->GetCPUDescriptorHandleForHeapStart(); };

        // 
        ID3D12DescriptorHeap* Get() const { return heap.Get(); };
        ID3D12Resource* GetResource() const { return resource.Get(); };
    };

};
