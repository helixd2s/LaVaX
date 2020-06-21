# DXV

Vulkan API wrapper of DirectX 12 Ultimate (but uses DXIL instead of SPIR-V)


### Limitations

- Shader modules accept only DXIL intermediate code, so you can use only HLSL
- Every binding ID of all descriptor sets should to be unique per every pipeline (but can to be array)
- This wrapper are similar D3D12 for Windows 7 (i.e. only for developers)
- Support only for Windows 10 Build 2004 or beyond, and WSL-2 with WDDM v2.9
- Support only as Visual Studio 2019 Project, there is NO CMAKE... it made for precise control, for single DLL library
- It DOES NOT replace the regular Vulkan API in full, but is as similar as possible, which provides portability
- Required Windows 10 SDK (10.0.19041.0 or higher) for compile that project
