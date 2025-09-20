#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <cassert>
#include <string>

// ==================================================
// ECS Core Types
// ==================================================
using Entity = std::uint32_t;                       // Unsigned integer 0 to 4,294,967,295
constexpr size_t MAX_ENTITIES   = 5000;             // size_t is also an unsign integer.
constexpr size_t MAX_COMPONENTS = 32;

// Each entity’s "signature" (bitset) describes which components it has.
using Signature = std::bitset<MAX_COMPONENTS>;      // bitset is a packed together set of bits
                                                    // its like a set of holding data to say this is used or not used.
                                                    // [010110]

// ==================================================
// Entity Manager
// ==================================================
class EntityManager {
    std::vector<Entity> freeIds{};                  // tracks destroyed IDs for reuse.
    std::vector<Signature> signatures{};            // 
    Entity nextId{0};

public:
    EntityManager() {
        signatures.resize(MAX_ENTITIES);
    }

    Entity create() {
        Entity id;
        if (!freeIds.empty()) {
            id = freeIds.back();
            freeIds.pop_back();
        } else {
            assert(nextId < MAX_ENTITIES && "Too many entities!");  // assert = ensure we don't go over our max entity number.
            id = nextId++;
        }
        signatures[id].reset();
        return id;
    }

    void destroy(Entity e) {
        signatures[e].reset();
        freeIds.push_back(e);
    }

    void setSignature(Entity e, Signature sig) {
        signatures[e] = sig;
    }

    const Signature& getSignature(Entity e) const {
        return signatures[e];
    }
};

// ==================================================
// Component Manager (type-erased storage)
// ==================================================
class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(Entity e) = 0;
};

// Templated storage for each component type
template<typename T>
class ComponentArray : public IComponentArray {
    std::vector<T> data;
    std::unordered_map<Entity, size_t> entityToIndex;
    std::unordered_map<size_t, Entity> indexToEntity;
    size_t size{0};

public:
    void insert(Entity e, T component) {
        assert(entityToIndex.find(e) == entityToIndex.end() && "Component added twice!");
        size_t idx = size;
        entityToIndex[e] = idx;
        indexToEntity[idx] = e;
        if (data.size() <= idx) data.resize(idx + 1);
        data[idx] = component;
        ++size;
    }

    void remove(Entity e) {
        assert(entityToIndex.find(e) != entityToIndex.end() && "No component to remove!");
        size_t idx = entityToIndex[e];
        size_t lastIdx = size - 1;
        data[idx] = data[lastIdx];
        Entity lastEntity = indexToEntity[lastIdx];
        entityToIndex[lastEntity] = idx;
        indexToEntity[idx] = lastEntity;

        entityToIndex.erase(e);
        indexToEntity.erase(lastIdx);
        --size;
    }

    T& get(Entity e) {
        assert(entityToIndex.find(e) != entityToIndex.end() && "No component found!");
        return data[entityToIndex[e]];
    }

    void entityDestroyed(Entity e) override {
        if (entityToIndex.find(e) != entityToIndex.end()) {
            remove(e);
        }
    }
};

// ==================================================
// Component Manager Registry
// ==================================================
class ComponentManager {
    std::unordered_map<const char*, size_t> componentTypes{};
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};
    size_t nextComponentType{0};

public:
    template<typename T>
    void registerComponent() {
        const char* typeName = typeid(T).name();
        assert(componentTypes.find(typeName) == componentTypes.end() && "Already registered!");
        componentTypes[typeName] = nextComponentType++;
        componentArrays[typeName] = std::make_shared<ComponentArray<T>>();
    }

    template<typename T>
    size_t getComponentType() {
        const char* typeName = typeid(T).name();
        return componentTypes[typeName];
    }

    template<typename T>
    void addComponent(Entity e, T component) {
        getArray<T>()->insert(e, component);
    }

    template<typename T>
    void removeComponent(Entity e) {
        getArray<T>()->remove(e);
    }

    template<typename T>
    T& getComponent(Entity e) {
        return getArray<T>()->get(e);
    }

    void entityDestroyed(Entity e) {
        for (auto const& [name, arr] : componentArrays) {
            arr->entityDestroyed(e);
        }
    }

private:
    template<typename T>
    std::shared_ptr<ComponentArray<T>> getArray() {
        const char* typeName = typeid(T).name();
        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }
};

// ==================================================
// System Base
// ==================================================
class System {
public:
    std::vector<Entity> entities;
};

// Example System: Combat
class CombatSystem : public System {
public:
    void update(ComponentManager& cm) {
        for (auto e : entities) {
            auto& s = cm.getComponent<struct Stats>(e);
            std::cout << "Entity " << e << " has HP=" << s.health << "\n";
        }
    }
};

// ==================================================
// ECS Coordinator (ties everything together)
// ==================================================
class Coordinator {
    EntityManager em;
    ComponentManager cm;

public:
    Entity createEntity() {
        return em.create();
    }

    void destroyEntity(Entity e) {
        em.destroy(e);
        cm.entityDestroyed(e);
    }

    template<typename T>
    void registerComponent() {
        cm.registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity e, T component) {
        cm.addComponent<T>(e, component);
        Signature sig = em.getSignature(e);
        sig.set(cm.getComponentType<T>(), true);
        em.setSignature(e, sig);
    }

    template<typename T>
    T& getComponent(Entity e) {
        return cm.getComponent<T>(e);
    }
};

// ==================================================
// Components for the Game
// ==================================================
struct Stats {
    int health;
    int mana;
    int stamina;
    int agility;
};

struct Hero {
    std::string role;
};

struct Enemy {
    std::string species;
};

// ==================================================
// Main
// ==================================================
int main() {
    Coordinator ecs;

    // Register components
    ecs.registerComponent<Stats>();
    ecs.registerComponent<Hero>();
    ecs.registerComponent<Enemy>();

    // Create a mage hero
    Entity mage = ecs.createEntity();
    ecs.addComponent(mage, Stats{80, 100, 40, 15});
    ecs.addComponent(mage, Hero{"Mage"});

    // Create an ogre enemy
    Entity ogre = ecs.createEntity();
    ecs.addComponent(ogre, Stats{120, 0, 60, 5});
    ecs.addComponent(ogre, Enemy{"Ogre"});

    // Access components
    auto& mStats = ecs.getComponent<Stats>(mage);
    auto& oStats = ecs.getComponent<Stats>(ogre);

    std::cout << "Mage HP=" << mStats.health << ", Ogre HP=" << oStats.health << "\n";

    // Example simple battle
    oStats.health -= 20;
    std::cout << "Mage casts Fireball! Ogre HP now " << oStats.health << "\n";

    return 0;
}

