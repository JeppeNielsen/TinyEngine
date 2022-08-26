//
//  ArchetypeContainer.hpp
//  ECS
//
//  Created by Jeppe Nielsen on 26/08/2022.
//

#pragma
#include <vector>
#include <tuple>
#include "GameObject.hpp"

namespace Tiny {

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
    void Invoke(MethodPtr<Ret, Type, Args...> ptr, Type* instance)
    {
        for (int i=0; i<components.size(); ++i) {
            std::invoke(ptr, instance, (std::get<std::remove_const_t<std::remove_reference_t<Args>>>(components[i]))...);
        }
    }
    
};

}
