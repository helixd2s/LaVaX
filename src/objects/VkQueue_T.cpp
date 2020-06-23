#include "pch/pch.h"
#include "VkDevice_T.hpp"
#include "VkQueue_T.hpp"

namespace dxv {

    VkQueue_T::VkQueue_T(const dxv::VkDevice_T* device, ComPtr<ID3D12CommandQueue> commandQueue ={}) : device(VkDevice(device)), commandQueue(commandQueue) {
        
        // 
        D3D12_COMMAND_QUEUE_DESC queueDesc = {};
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        ThrowIfFailed(device->GetDevice()->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue)));
        
    };

};
