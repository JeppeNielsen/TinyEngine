//
//  ArchetypeCollection.hpp
//  ECS
//
//  Created by Jeppe Nielsen on 30/09/2022.
//

#pragma once
#include "TupleHelper.hpp"

namespace Tiny {

template<typename ...T>
struct ArchetypeCollection {
    using Archetypes = std::tuple<T...>;
    Archetypes achetypes;
    
    static constexpr int Size = std::tuple_size_v<Archetypes>;
    
    template<typename SystemType>
    static constexpr auto GetArcheTypesMatches() {
        return std::tuple_cat(std::conditional_t<(TupleHelper::all_parameters_in_tuple<typename T::Components>(&SystemType::Step)),
                              std::tuple<T*>,
                              std::tuple<>>{}...);
    }
    
    template<typename SystemType>
    static constexpr auto GetArcheTypesMatchesTuple() {
        return decltype(GetArcheTypesMatches<SystemType>()) { GetArcheTypesMatches<SystemType>() };
    }
    
};

}
