#pragma once
#include <DirectXMath.h>
#include "../../../Core/MathHelper.h"
#include "CrateFrameResource.h"
#include "../../../Core/D3DUtil.h"

struct CrateRenderItem
{
    CrateRenderItem() = default;

    DirectX::XMFLOAT4X4 Model = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();

    int NumFramesDirty = CrateFrameResource::NumFrameResources;

    UINT ObjCBIndex = -1;
    Material* Mat = nullptr;
    MeshGeometry* Geo = nullptr;

    D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    UINT IndexCount = 0;
    UINT StartIndexLocation = 0;
    int BaseVertexLocation = 0;
};
