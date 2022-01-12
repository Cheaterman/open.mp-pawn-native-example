#include <sdk.hpp>
#include <Server/Components/Vehicles/vehicles.hpp>

struct CountVehiclesInRulesComponent : IComponent, PoolEventHandler<IVehicle> {
	PROVIDE_UUID(0x88f9172cc6eb78a3);

	StringView componentName() const override {
		return "Count vehicles in rules";
	}

	SemanticVersion componentVersion() const override {
		return SemanticVersion(0, 0, 0, 0);
	}

	void onLoad(ICore* c) override {
		// Cache core, player pool here
		core = c;
		c->printLn("on load");
	}

	void onInit(IComponentList* components) override {
		// Cache components, add event handlers here
		vehicles = components->queryComponent<IVehiclesComponent>();
		if (vehicles) {
			vehicles->getPoolEventDispatcher().addEventHandler(this);
		}
	}

	void onReady() override {
		// Fire events here at earliest
	}

	~CountVehiclesInRulesComponent() {
		// Clean up what you did above
		if (vehicles) {
			vehicles->getPoolEventDispatcher().removeEventHandler(this);
		}
	}

	void onPoolEntryCreated(IVehicle& entry) override {
		for (INetwork* network : core->getNetworks()) {
			INetworkQueryExtension* query = queryExtension<INetworkQueryExtension>(network);
			if (query) {
				query->addRule("vehicles", std::to_string(vehicles->count()));
			}
		}
	}

	void onPoolEntryDestroyed(IVehicle& entry) override {
		for (INetwork* network : core->getNetworks()) {
			INetworkQueryExtension* query = queryExtension<INetworkQueryExtension>(network);
			if (query) {
				query->addRule("vehicles", std::to_string(vehicles->count()));
			}
		}
	}

	ICore* core = nullptr;
	IVehiclesComponent* vehicles = nullptr;
} component;

COMPONENT_ENTRY_POINT() {
	return &component;
}
