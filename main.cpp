#include <NativeFunc.hpp>
#include <NativesMain.hpp>
#include <Server/Components/Pawn/pawn.hpp>
#include <sdk.hpp>

struct HelloComponent;
HelloComponent* helloComponent = nullptr;
extern void* pAMXFunctions;

struct HelloComponent final : IComponent, PawnEventHandler {
    PROVIDE_UID(/* UID GOES HERE */);

    StringView componentName() const override
    {
        return "HelloWorld";
    }

    SemanticVersion componentVersion() const override
    {
        return SemanticVersion(0, 0, 1, 0);
    }

    void onLoad(ICore* c) override
    {
        core = c;
    }

    void onInit(IComponentList* components) override
    {
        pawnComponent = components->queryComponent<IPawnComponent>();

        if (pawnComponent == nullptr) {
            StringView name = componentName();
            core->logLn(
                LogLevel::Error,
                "Error loading component %.*s: Pawn component not loaded",
                name.length(),
                name.data());
            return;
        }

        pAMXFunctions = (void*)&pawnComponent->getAmxFunctions();
        pawnComponent->getEventDispatcher().addEventHandler(this);
    }

    void onReady() override { }

    void onAmxLoad(void* amx) override
    {
        pawn_natives::AmxLoad(static_cast<AMX*>(amx));
    }

    void onAmxUnload(void* amx) override { }

    void onFree(IComponent* component) override
    {
        if (component == pawnComponent) {
            pawnComponent = nullptr;
            pAMXFunctions = nullptr;
        }
    }

    void free() override
    {
        if (pawnComponent != nullptr)
            pawnComponent->getEventDispatcher().removeEventHandler(this);

        delete this;
    }

    void reset() override
    {
        // Nothing to reset for now.
    }

    ICore* core = nullptr;
    IPawnComponent* pawnComponent;
};

COMPONENT_ENTRY_POINT()
{
    helloComponent = new HelloComponent();
    return helloComponent;
}

PAWN_NATIVE(Hello, HelloWorld, void())
{
    helloComponent->core->printLn("Hello, world!");
}
