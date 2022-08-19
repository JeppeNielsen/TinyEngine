//
//  MemberHelper.hpp
//  NewEcs
//
//  Created by Jeppe Nielsen on 07/08/2022.
//
#pragma once
#include "TupleHelper.hpp"

/*
template <typename TypeToTest, typename Ret, typename Type, typename... Args>
constexpr bool has_member_type(Ret(Type::*VelPtr)(Args...))
{
    constexpr std::tuple<Args*...> tuple;
    bool isTrue = false;
    
    TupleHelper::Iterate(tuple, [&isTrue](auto arg) {
        if constexpr (typename std::is_same<std::remove_pointer_t<decltype(arg)>, TypeToTest>()) {
            isTrue = true;
        }
    });
    
    return isTrue;
}
*/

template <typename TypeToTest, typename Ret, typename Type, typename... Args>
constexpr bool has_member_type(Ret(Type::*VelPtr)(Args...))
{
    bool isTrue = false;
    [](...){ }(isTrue |= typename std::is_same<Args, TypeToTest>()...);
    return isTrue;
}

template <typename Tuple, typename Ret, typename Type, typename... Args>
constexpr bool all_parameters_in_tuple(Ret(Type::*VelPtr)(Args...))
{
    bool oneIsMissing = false;
    [](...){ }(oneIsMissing |= !typename TupleHelper::HasType<std::remove_pointer_t<std::remove_const_t<std::remove_reference_t<Args>>>, Tuple>()...);
    return !oneIsMissing;
}
