#pragma once

#include <functional>

#include "Core/Engine.h"
#include "Core/scene/Object3D.h"
#include "Core/material/BasicTexturedMaterial.h"
#include "Core/material/BasicColoredMaterial.h"
#include "Core/material/BasicExtrusionMaterial.h"
#include "Core/material/OutlineMaterial.h"
#include "Core/material/Shader.h"
#include "Core/scene/RayCaster.h"
#include "Core/color/Color.h"

#include "CoreScene.h"
#include "CoreSync.h"
#include "MouseAdapter.h"
#include "GestureAdapter.h"
#include "PipedEventAdapter.h"
#include "OrbitControls.h"
#include "BasicRimShadowMaterial.h"


class RenderWindow;
class MainGUI;

class ModelerApp {
public:

    using ModelerAppLifecycleEventCallback = std::function<void()>;

    ModelerApp();
    void init();
    void setRenderWindow(RenderWindow* renderWindow);
    void loadModel(const std::string& path, float scale, float smoothingThreshold, const bool zUp);
    CoreScene& getCoreScene();
    void onUpdate(ModelerAppLifecycleEventCallback callback);
    std::shared_ptr<CoreSync> getCoreSync();

private:
    void engineReady(Core::WeakPointer<Core::Engine> engine);
    void setupHighlightMaterials();
    void gesture(GestureAdapter::GestureEvent event);
    void mouseButton(MouseAdapter::MouseEventType type, Core::UInt32 button, Core::Int32 x, Core::Int32 y);
    void rayCastForObjectSelection(Core::Int32 x, Core::Int32 y, bool setSelectedObject = true);
    void setupRenderCamera();
    void setupDefaultObjects();
    void setupTransformWidget();
    void setupLights();
    void updateLights();
    void resolveOnUpdateCallbacks();
    void preRenderCallback();
    void postRenderCallback();

    void rayCastForTransformWidgetSelection(Core::Int32 x, Core::Int32 y);
    void updateTransformWidgetForObject(Core::WeakPointer<Core::Object3D> object);
    void updateTransformWidgetCamera();
    void endTransformWidgetAction(Core::Int32 x, Core::Int32 y);
    void startTransformWidgetAction(Core::Int32 x, Core::Int32 y);
    void updateTransformWidgetAction(Core::Int32 x, Core::Int32 y);
    bool getTransformWidgetTranslationTargetPosition(Core::Int32 x, Core::Int32 y, Core::Point3r origin, Core::Point3r& out);
    void resetTransformWidgetColors();

    RenderWindow* renderWindow;
    bool engineIsReady = false;
    CoreScene coreScene;
    Core::WeakPointer<Core::Camera> renderCamera;
    Core::WeakPointer<Core::Engine> engine;
    Core::RayCaster sceneRaycaster;
    std::unordered_map<Core::UInt64, Core::WeakPointer<Core::Object3D>> meshToObjectMap;
    Core::WeakPointer<Core::Object3D> ambientLightObject;
    Core::WeakPointer<Core::Object3D> directionalLightObject;
    Core::WeakPointer<Core::Object3D> pointLightObject;

    std::shared_ptr<CoreSync> coreSync;
    std::shared_ptr<GestureAdapter> gestureAdapter;
    std::shared_ptr<PipedEventAdapter<GestureAdapter::GestureEvent>> pipedGestureAdapter;
    std::shared_ptr<OrbitControls> orbitControls;

    Core::Color highlightColor;
    Core::Color outlineColor;
    Core::Color darkOutlineColor;
    Core::WeakPointer<Core::BasicColoredMaterial> highlightMaterial;
    Core::WeakPointer<Core::OutlineMaterial> outlineMaterial;

    QMutex onUpdateMutex;
    std::vector<ModelerAppLifecycleEventCallback> onUpdates;

    Core::RayCaster transformWidgetRaycaster;
    Core::WeakPointer<Core::Object3D> transformWidgetCameraObj;
    Core::WeakPointer<Core::Camera> transformWidgetCamera;
    Core::WeakPointer<Core::Object3D> transformWidgetRoot;
    Core::Color transformWidgetHighlightColor;
    Core::Color transformWidgetXColor;
    Core::Color transformWidgetYColor;
    Core::Color transformWidgetZColor;
    Core::WeakPointer<BasicRimShadowMaterial> transformWidgetXMaterial;
    Core::WeakPointer<BasicRimShadowMaterial> transformWidgetYMaterial;
    Core::WeakPointer<BasicRimShadowMaterial> transformWidgetZMaterial;
    Core::UInt32 transformWidgetXTranslateID;
    Core::UInt32 transformWidgetYTranslateID;
    Core::UInt32 transformWidgetZTranslateID;

    Core::Int32 transformWidgetActiveComponentID;
    bool transformWidgetActionInProgress;
    Core::Point3r transformWidgetActionStartPosition;
    Core::Vector3r transformWidgetActionNormal;
    Core::Vector3r transformWidgetActionOffset;
    Core::Vector4r transformWidgetPlane;

};
