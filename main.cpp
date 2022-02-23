#include <sdk.hpp>
#include <Server/Components/Pawn/pawn.hpp>
#include <NativeFunc.hpp>
#include <NativesMain.hpp>

struct HelloComponent;
HelloComponent* helloComponent = nullptr;
extern void *pAMXFunctions;

struct HelloComponent final : IComponent, PawnEventHandler {
	PROVIDE_UID(0x1126fdb4780f11ec);

	StringView componentName() const override {
		return "HelloWorld";
	}

	SemanticVersion componentVersion() const override {
		return SemanticVersion(0, 0, 1, 0);
	}

	void onLoad(ICore* c) override {
		core = c;
	}

	void onInit(IComponentList* components) override {
		pawnComponent = components->queryComponent<IPawnComponent>();
		pAMXFunctions = (void *)&pawnComponent->getAmxFunctions();
		pawnComponent->getEventDispatcher().addEventHandler(this);
	}

	void onReady() override {}

	void onAmxLoad(void* amx) override {
		pawn_natives::AmxLoad((AMX *)amx);
	}

	void onAmxUnload(void* amx) override {}

	void free() override {
		pawnComponent->getEventDispatcher().removeEventHandler(this);
		delete this;
	}

	ICore* core = nullptr;
	IPawnComponent* pawnComponent;
};

COMPONENT_ENTRY_POINT() {
	helloComponent = new HelloComponent();
	return helloComponent;
}

PAWN_NATIVE(Hello, HelloWorld, void())
{
	helloComponent->core->printLn("Hello, world!");
}
