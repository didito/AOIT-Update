/////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
/////////////////////////////////////////////////////////////////////////////////////////////


#include "CPUT_DX11.h"
#include "CPUTGeometryShaderDX11.h"
#include "CPUTAssetLibraryDX11.h"

CPUTGeometryShaderDX11 *CPUTGeometryShaderDX11::CreateGeometryShader(
    const cString    &name,
    const cString    &shaderMain,
    const cString    &shaderProfile,
    CPUT_SHADER_MACRO *pShaderMacros
)
{
    ID3DBlob             *pCompiledBlob = NULL;
    ID3D11GeometryShader *pNewGeometryShader = NULL;

    CPUTAssetLibraryDX11 *pAssetLibrary = (CPUTAssetLibraryDX11*)CPUTAssetLibrary::GetAssetLibrary();
    CPUTResult result = pAssetLibrary->CompileShaderFromFile(name, shaderMain, shaderProfile, &pCompiledBlob, pShaderMacros );
    ASSERT( CPUTSUCCESS(result), _L("Error compiling Geometry shader:\n\n") );
    UNREFERENCED_PARAMETER(result);

    // Create the Geometry shader
    ID3D11Device      *pD3dDevice = CPUT_DX11::GetDevice();
    HRESULT hr = pD3dDevice->CreateGeometryShader( pCompiledBlob->GetBufferPointer(), pCompiledBlob->GetBufferSize(), NULL, &pNewGeometryShader );
    ASSERT( SUCCEEDED(hr), _L("Error creating Geometry shader:\n\n") );
    UNREFERENCED_PARAMETER(hr);
    // cString DebugName = _L("CPUTAssetLibraryDX11::GetGeometryShader ")+name;
    // CPUTSetDebugName(pNewGeometryShader, DebugName);

    CPUTGeometryShaderDX11 *pNewCPUTGeometryShader = new CPUTGeometryShaderDX11( pNewGeometryShader, pCompiledBlob );

    // add shader to library
    pAssetLibrary->AddGeometryShader(name, _L(""), shaderMain + shaderProfile, pNewCPUTGeometryShader, pShaderMacros);
    // pNewCPUTGeometryShader->Release(); // We've added it to the library, so release our reference

    // return the shader (and blob)
    return pNewCPUTGeometryShader;
}

//--------------------------------------------------------------------------------------
CPUTGeometryShaderDX11 *CPUTGeometryShaderDX11::CreateGeometryShaderFromMemory(
    const cString     &name,
    const cString     &shaderMain,
    const cString     &shaderProfile,
    const char        *pShaderSource,
    CPUT_SHADER_MACRO *pShaderMacros
)
{
    ID3DBlob             *pCompiledBlob = NULL;
    ID3D11GeometryShader *pNewGeometryShader = NULL;

    CPUTAssetLibraryDX11 *pAssetLibrary = (CPUTAssetLibraryDX11*)CPUTAssetLibrary::GetAssetLibrary();
    CPUTResult result = pAssetLibrary->CompileShaderFromMemory(pShaderSource, shaderMain, shaderProfile, &pCompiledBlob, pShaderMacros );
    ASSERT( CPUTSUCCESS(result), _L("Error creating Geometry shader:\n\n") );
    UNREFERENCED_PARAMETER(result);

    // Create the Geometry shader
    ID3D11Device      *pD3dDevice = CPUT_DX11::GetDevice();
    HRESULT hr = pD3dDevice->CreateGeometryShader( pCompiledBlob->GetBufferPointer(), pCompiledBlob->GetBufferSize(), NULL, &pNewGeometryShader );
    ASSERT( SUCCEEDED(hr), _L("Error creating Geometry shader:\n\n") );
    UNREFERENCED_PARAMETER(hr);
    // cString DebugName = _L("CPUTAssetLibraryDX11::GetGeometryShader ")+name;
    // CPUTSetDebugName(pNewGeometryShader, DebugName);

    CPUTGeometryShaderDX11 *pNewCPUTGeometryShader = new CPUTGeometryShaderDX11( pNewGeometryShader, pCompiledBlob );

    // add shader to library
    pAssetLibrary->AddGeometryShader(name, _L(""), shaderMain + shaderProfile, pNewCPUTGeometryShader, pShaderMacros);
    // pNewCPUTGeometryShader->Release(); // We've added it to the library, so release our reference

    // return the shader (and blob)
    return pNewCPUTGeometryShader;
}