#pragma once

// 
#include "pch/objects.hpp"

// 
namespace lvx {
    class VkDevice_T {
    protected:
        ComPtr<ID3D12Device> device = {};
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkResult result = VK_SUCCESS;
        std::vector<const char*> enabledExtensions = {};
        std::vector<const char*> enabledLayers = {};

        // Critically Required
        const std::vector<const char*> DX12ForceCriticalRequiredExtensions = {
            "VK_EXT_scalar_block_layout", // DX12 Always using scalar layouts for shaders, defaultly!
            "VK_EXT_conservative_rasterization", // DX12 Defaultly support conservative rasterization, even when features are false
            "VK_EXT_extended_dynamic_state", // For IASetVertexBuffers, that very simila, but SoA, needs convert into AoS internally
            "VK_EXT_descriptor_indexing",
            "VK_EXT_buffer_device_address",
            "VK_KHR_shader_float16_int8", // HLSL regulary using 16-bit data
            "VK_KHR_16bit_storage", // Same reason...
            "VK_KHR_maintenance1", // F&ck, damn'it your Y axis...
            "VK_KHR_timeline_semaphore" // For DX12 Based It Required!
        };

        // Int8 Recommended
        const std::vector<const char*> DX12ForceWarningRequiredExtensions = {
            "VK_EXT_index_type_uint8",
            "VK_KHR_shader_subgroup_extended_types",
            "VK_KHR_8bit_storage",
            "VK_KHR_swapchain",
            "VK_KHR_surface",
            "VK_KHR_win32_surface",
            "VK_KHR_win32_keyed_mutex",
        };

        // When You Want Export DirectX Handles - don't do it without that extensions!
        const std::vector<const char*> DX12SharingCriticalRequired = {
            "VK_KHR_external_fence_capabilities",
            "VK_KHR_external_fence_win32",
            "VK_KHR_external_fence",
            "VK_KHR_external_memory_capabilities",
            "VK_KHR_external_memory_win32",
            "VK_KHR_external_memory",
            "VK_KHR_external_semaphore_capabilities",
            "VK_KHR_external_semaphore_win32",
            "VK_KHR_external_semaphore"
        };

        // Ray Tracing Extension Enable DXR1.1, also needs HW checks
        const std::vector<const char*> DXRForceCriticalRequiredExtensions = {
            "VK_EXT_buffer_device_address",
            "VK_KHR_ray_tracing"
        };

    public:
        VkDevice_T() {}
        VkDevice_T(const lvx::VkPhysicalDevice_T* physicalDevice, HPTR(VkDeviceCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks) {
            this->result = this->Create(physicalDevice, createInfo, callbacks);
        };
        
        // 
        ComPtr<ID3D12Device> GetDevice() const { return this->device; }
        VkResult Create(const lvx::VkPhysicalDevice_T* physicalDevice, HPTR(VkDeviceCreateInfo) createInfo, UPTR(VkAllocationCallbacks) callbacks);

        // 
        ID3D12Device* Get() const { return device.Get(); };
    };
};
