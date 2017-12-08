/////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
/////////////////////////////////////////////////////////////////////////////////////////////


// ********************************************************************************************************
struct VS_INPUT
{
    float3 Pos      : POSITION; // Projected position
    float2 UV0      : TEXCOORD0;
};
struct PS_INPUT
{
    float4 Pos      : SV_POSITION;
    float2 UV0      : TEXCOORD0;
};

// ********************************************************************************************************
cbuffer cbPerModelValues
{
    row_major float4x4 World : WORLD;
    row_major float4x4 NormalMatrix : WORLD;
    row_major float4x4 WorldViewProjection : WORLDVIEWPROJECTION;
    row_major float4x4 InverseWorld : WORLDINVERSE;
    row_major float4x4 LightWorldViewProjection;
              float4   BoundingBoxCenterWorldSpace  < string UIWidget="None"; >;
              float4   BoundingBoxHalfWorldSpace    < string UIWidget="None"; >;
              float4   BoundingBoxCenterObjectSpace < string UIWidget="None"; >;
              float4   BoundingBoxHalfObjectSpace   < string UIWidget="None"; >;
};

// -------------------------------------
cbuffer cbPerFrameValues
{
    row_major float4x4  View;
    row_major float4x4  InverseView : ViewInverse	< string UIWidget="None"; >;
    row_major float4x4  Projection;
    row_major float4x4  ViewProjection;
              float4    AmbientColor < string UIWidget="None"; > = .20;
              float4    LightColor < string UIWidget="None"; >   = 1.0f;
              float4    LightDirection  : Direction < string UIName = "Light Direction";  string Object = "TargetLight"; string Space = "World"; int Ref_ID=0; > = {0,0,-1, 0};
              float4    EyePosition;
              float4    TotalTimeInSeconds < string UIWidget="None"; >;
			  float4    MultiSampleCount;           // .x == multisample count; .y = 1.0/x
};

SamplerState SAMPLER0 : register( s0 );
Texture2D texture_DM : register( t1 );

// ********************************************************************************************************
PS_INPUT VSMain( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( float4( input.Pos, 1.0f), WorldViewProjection );
//    output.Pos.z -= 0.0003 * output.Pos.w;  
  output.UV0 = input.UV0;

    return output;
}

// ********************************************************************************************************
void PSMain( PS_INPUT input )
{

	float4 inputTexture = texture_DM.Sample( SAMPLER0, input.UV0 );

	clip(inputTexture.a - 0.01);

 //   return float4(1,0,0,1);
}