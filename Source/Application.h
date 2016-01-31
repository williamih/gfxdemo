#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "Core/FileLoader.h"

#include "GpuDevice/GpuDevice.h"
#include "GpuDevice/GpuDeferredDeletionQueue.h"

#include "Asset/AssetCache.h"

#include "Shader/ShaderAsset.h"

#include "Texture/TextureAsset.h"

#include "Model/ModelAsset.h"
#include "Model/ModelInstance.h"
#include "Model/ModelRenderQueue.h"

#include "Scene/Camera.h"

class OsWindow;
class OsEvent;

class Application {
public:
    Application();
    ~Application();
    void Frame();
private:
    Application(const Application&);
    Application& operator=(const Application&);

    static OsWindow* CreateWindow();
    static GpuDevice* CreateGpuDevice(OsWindow& window);
    static ModelInstance* CreateModelInstance(ModelRenderQueue& queue,
                                              AssetCache<ModelAsset>& cache,
                                              const char* path);

    static void OnKeyDown(const OsEvent& event, void* userdata);
    static void OnKeyUp(const OsEvent& event, void* userdata);
    static void OnMouseDragged(const OsEvent& event, void* userdata);

    void RefreshModelShader();

    std::unique_ptr<OsWindow, void (*)(OsWindow*)> m_window;
    std::unique_ptr<GpuDevice, void (*)(GpuDevice*)> m_gpuDevice;
    GpuRenderPassID m_renderPass;

#ifdef ASSET_REFRESH
    GpuDeferredDeletionQueue m_gpuDeferredDeletionQueue;
#endif

    FileLoader m_fileLoader;

    ShaderAssetFactory m_shaderAssetFactory;
    AssetCache<ShaderAsset> m_shaderCache;

    TextureAssetFactory m_textureAssetFactory;
    AssetCache<TextureAsset> m_textureCache;

    ModelAssetFactory m_modelAssetFactory;
    AssetCache<ModelAsset> m_modelCache;

    ModelRenderQueue m_modelRenderQueue;
    std::unique_ptr<ModelInstance, void (*)(ModelInstance*)> m_teapot;
    std::unique_ptr<ModelInstance, void (*)(ModelInstance*)> m_floor;
    float m_angle;
    Camera m_camera;
};

#endif // APPLICATION_H
