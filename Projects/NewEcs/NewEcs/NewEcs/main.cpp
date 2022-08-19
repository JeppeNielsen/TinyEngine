//
//  main.cpp
//  NewEcs
//
//  Created by Jeppe Nielsen on 22/07/2022.
//

#include <iostream>
#include <tuple>
#include <vector>
#include "GameObject.hpp"
#include "TupleHelper.hpp"
#include "MemberHelper.hpp"
#include "ClassNameHelper.hpp"
#include <array>
#include <string>

struct Position {
    float x = 0;
    float y = 0;
};

struct Velocity {
    float vx = 1;
    float vy = 1;
};

struct VelocitySystem {
    
    void Step(Position& position, const Velocity& velocity) {
        position.x += velocity.vx;
        position.y += velocity.vy;
        std::cout << "VelocitySystem::Step: position.x = " << position.x << ", position.y = " << position.y<< " position.addr:" << &position << " position.addr:" << &velocity <<std::endl;
    }
    
};


struct PositionSystem {
    
    void Step(Position& position) {
        std::cout << "PositionSystem::Step" << " addr:" << &position << std::endl;
    }
    
};

struct BrakeSystem {
    
    void Step(const Velocity& velocity) {
        std::cout << "BrakeSystem::Step" << " addr:" << &velocity << std::endl;
    }
    
};



struct ArchetypeContainerBase {
    virtual ~ArchetypeContainerBase() {}
    virtual GameObject Create(int typeIndex) = 0;
    virtual void Remove(const GameObject gameObject) = 0;
};

template<typename ...T>
struct ArchetypeContainer : ArchetypeContainerBase {
    using Components = std::tuple<T...>;
    std::vector<Components> components;
    std::vector<int> indicies;
    
    GameObject Create(int typeIndex) override {
        uint32_t index = (uint32_t)components.size();
        components.push_back({});
        return GameObject(index, 0, typeIndex);
    }
    
    void Remove(const GameObject gameObject) override {
        std::cout << "Deleting " << gameObject.Type() << std::endl;
    }
    
    template<typename Ret, typename Type, typename... Args>
    using MethodPtr = Ret(Type::*)(Args...);
    
    template <typename Ret, typename Type, typename... Args>
    void Invoke(MethodPtr<Ret, Type, Args...> ptr, Type* instance, int index)
    {
        for (int i=0; i<components.size(); ++i) {
            std::invoke(ptr, instance, (std::get<std::remove_const_t<std::remove_reference_t<Args>>>(components[i]))...);
        }
    }
    
};


template<typename ...T>
using Archetype = ArchetypeContainer<T...>;

template<typename ...T>
struct ArchetypeList {
    using Archetypes = std::tuple<T...>;
    Archetypes achetypes;
    
    static constexpr int Size = std::tuple_size_v<Archetypes>;
    
    template<typename SystemType>
    static constexpr auto GetArcheTypesMatches() {
        return std::tuple_cat(std::conditional_t<(all_parameters_in_tuple<typename T::Components>(&SystemType::Step)),
                              std::tuple<T*>,
                              std::tuple<>>{}...);
    }
    
    template<typename SystemType>
    static constexpr auto GetArcheTypesMatchesTuple() {
        return std::tuple<decltype(GetArcheTypesMatches<SystemType>())> { GetArcheTypesMatches<SystemType>() };
    }
    
};

template<typename Archetypes, typename ...T>
struct SystemsList {
    
    static constexpr auto GetSystemTuples() {
        return std::tuple_cat(Archetypes::template GetArcheTypesMatchesTuple<T>()...);
    }
    
    using Systems = std::tuple<T...>;
    Systems systems;
    decltype(GetSystemTuples()) archetypes;
    
    void HookUpPointers(const Archetypes& achetypesList) {
        TupleHelper::Iterate(archetypes, [&] (auto& a) {
            TupleHelper::Iterate(a, [&] (auto& aa) {
                using ContainerType = std::remove_pointer_t< std::remove_reference_t<decltype(aa)> >;
                auto& container = std::get<ContainerType>(achetypesList.achetypes);
                aa = (std::remove_reference_t<decltype(aa)>)&container;
            });
        });
    }
    
};


template<typename Archetypes>
struct Registry {
    Archetypes archetypes;
    std::array<ArchetypeContainerBase*, Archetypes::Size> archetypesArray;
    
    Registry() {
      archetypesArray = std::apply([](auto&... archetype){return std::array<ArchetypeContainerBase*, sizeof...(archetype)>{&archetype...};}, archetypes. achetypes);
    }

    GameObject CreateGameObject(const int archetype) {
        return archetypesArray[archetype]->Create(archetype);
    }
    
    void RemoveGameObject(const GameObject gameObject) {
        archetypesArray[gameObject.Type()]->Remove(gameObject);
    }

};

template<typename TRegistry, typename TSystems>
struct World {
    TRegistry& registry;
    TSystems systems;
    
    World(TRegistry& registry) : registry(registry){
        systems.HookUpPointers(registry.archetypes);
    }
    
    void Step() {
        TupleHelper::Iterate(systems.systems, [&](auto& system) {
            using SystemType = std::remove_reference_t<decltype(system)>;
            constexpr auto taskIndex = TupleHelper::Index<SystemType, decltype(systems.systems)>::value;
            const auto components = std::get<taskIndex>(systems.archetypes);
            
            TupleHelper::Iterate(components, [&](auto archetypeContainer) {
                archetypeContainer->Invoke(&SystemType::Step, &system, 0);
            });
        });
    }
    
};


struct Transform {
    int pos;
};

struct Sprite {
    int image;
};


using Types = ArchetypeList<
    Archetype<Position>,
    Archetype<Position, Velocity>,
    Archetype<Velocity>,
    Archetype<Velocity, Transform>
>;

using Systems = SystemsList<Types, VelocitySystem, PositionSystem, BrakeSystem>;
//using Systems = SystemsList<Types, PositionSystem>;

struct RenderSystem {
    void Render(const Transform& t, Sprite& s) {
        std::cout << "RenderSystem : Transform.pos = " << t.pos << "  Sprite.image = " << s.image << "\n";
    }
    
};


int main() {
    
    constexpr auto tuple = std::tuple<Transform, Sprite, int>();
    
    constexpr auto result = std::apply([](auto...ts) {
        return std::tuple_cat(std::conditional_t<(!std::is_same<decltype(ts), Transform>()),
                              std::tuple<decltype(ts)*>,
                              std::tuple<>>{}...);
    }, tuple);
    
    
    RenderSystem r;
    
    Transform tr { 123 };
    Sprite sp { 2222};
    
    auto invokeTuple = std::tuple_cat(std::make_tuple(&r), std::make_tuple(tr), std::make_tuple(sp));
    
    std::apply(&RenderSystem::Render, invokeTuple);
    
    std::invoke(&RenderSystem::Render, &r, tr, sp);
    
    using Components = std::tuple<Transform, Sprite>;
    
    static_assert(all_parameters_in_tuple<Components>(&RenderSystem::Render), "UH OH");
    
    
    Registry<Types> registry;
    
    World<Registry<Types>, Systems> world(registry);
    
    
    
    
    auto go1 = registry.CreateGameObject(0);
    auto go2 = registry.CreateGameObject(1);
    auto go22 = registry.CreateGameObject(1);
    auto go3 = registry.CreateGameObject(2);
    
    std::get<0>(std::get<2>(registry.archetypes.achetypes).components[1]).vx = 3;
    
    world.Step();
    
    registry.RemoveGameObject(go2);
    
    
    std::cout << "go1.Type = " << go1.Type() << "\n";
    std::cout << "go2.Type = " << go2.Type() << "\n";
    std::cout << "go3.Type = " << go3.Type() << "\n";

    
    
    return 0;
}
