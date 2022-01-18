#include <sdk.hpp>

struct HelloComponent final : IComponent {
	PROVIDE_UUID(0x1126fdb4780f11ec);

	StringView componentName() const override {
		return "Says hello";
	}

	SemanticVersion componentVersion() const override {
		return SemanticVersion(0, 0, 0, 0);
	}

	void onLoad(ICore* c) override {
		core = c;
		c->printLn("Hello, world!");
	}

	void onInit(IComponentList* components) override {}

	void onReady() override {}

	void free() override {
		delete this;
	}

	ICore* core = nullptr;
};

COMPONENT_ENTRY_POINT() {
	return new HelloComponent();
}
