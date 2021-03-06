#pragma once
#include "../../../Core/Application.h"

#include "LitColumnsRenderItem.h"
#include "LitColumnsFrameResource.h"

class LitColumns : public Application
{
public:
    LitColumns(HINSTANCE hInstance);
    LitColumns(const LitColumns& rhs) = delete;
    LitColumns& operator=(const LitColumns& rhs) = delete;
    bool Init() override;
    ~LitColumns() override;
    LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;
    int Run() override;
protected:
    void OnResize() override;
    void Update(const GameTimer& timer) override;
    void Draw(const GameTimer& timer) override;

    void OnMouseDown(WPARAM btnState, int x, int y) override;
    void OnMouseUp(WPARAM btnState, int x, int y) override;
    void OnMouseMove(WPARAM btnState, int x, int y) override;

    void OnKeyboardInput(const GameTimer& timer);
    void UpdateCamera(const GameTimer& timer);
    void AnimateMaterials(const GameTimer& timer);
    void UpdateObjectCBs(const GameTimer& timer);
    void UpdateMaterialsCBs(const GameTimer& timer);
    void UpdateMainPassCB(const GameTimer& timer);

    void BuildRootSignature();
    void BuildShaderAndInputLayout();
    void BuildShapeGeometry();
    void BuildSkullGeometry();
    void BuildPSOs();
    void BuildFrameResources();
    void BuildMaterials();
    void BuildRenderItems();
    void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<LitColumnsRenderItem*>& renderItems);    
private:
    std::vector<std::unique_ptr<LitColumnsFrameResource>> _frameResources;
    LitColumnsFrameResource* _currFrameResource = nullptr;
    int _currentFrameResourceIndex = 0;
    
    Microsoft::WRL::ComPtr<ID3D12RootSignature> _rootSignature = nullptr;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _srvHeap = nullptr;

    std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> _geometries;
    std::unordered_map<std::string, std::unique_ptr<Material>> _materials;
    std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>> _shaders;

    std::vector<D3D12_INPUT_ELEMENT_DESC> _inputLayout;

    Microsoft::WRL::ComPtr<ID3D12PipelineState> _opaquePSO = nullptr;

    std::vector<std::unique_ptr<LitColumnsRenderItem>> _allRenderItems;
    std::vector<LitColumnsRenderItem*> _opaqueRenderItems;

    LitColumnsFrameResource::PassConstants _mainPassCB;

    DirectX::XMFLOAT3 _eyePos = { 0.0f, 0.0f, 0.0f };
    DirectX::XMFLOAT4X4 _view = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 _proj = MathHelper::Identity4x4();

    float _theta = 1.5f * DirectX::XM_PI;
    float _phi = 0.2f * DirectX::XM_PI;
    float _radius = 15.0f;

    POINT _lastMousePos;
};

