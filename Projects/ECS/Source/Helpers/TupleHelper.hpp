//
//  TupleHelper.hpp
//  NewEcs
//
//  Created by Jeppe Nielsen on 22/07/2022.
//
#pragma once
#include <tuple>
#include <type_traits>

namespace Tiny::TupleHelper {

template<class F, class...Ts, std::size_t...Is>
constexpr void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func, std::index_sequence<Is...>) {
    using expander = int[];
    (void)expander { 0, ((void)func((Ts&)std::get<Is>(tuple)), 0)... };
}

template<class F, class...Ts>
constexpr void Iterate(const std::tuple<Ts...> & tuple, F func) {
    for_each_in_tuple(tuple, func, std::make_index_sequence<sizeof...(Ts)>());
}

template <class Haystack, class Needle>
struct contains;

template <class Car, class... Cdr, class Needle>
struct contains<std::tuple<Car, Cdr...>, Needle> : contains<std::tuple<Cdr...>, Needle>
{};

template <class... Cdr, class Needle>
struct contains<std::tuple<Needle, Cdr...>, Needle> : std::true_type
{};

template <class Needle>
struct contains<std::tuple<>, Needle> : std::false_type
{};



template <class Out, class In>
struct filter;

template <class... Out, class InCar, class... InCdr>
struct filter<std::tuple<Out...>, std::tuple<InCar, InCdr...>>
{
  using type = typename std::conditional<
    contains<std::tuple<Out...>, InCar>::value
    , typename filter<std::tuple<Out...>, std::tuple<InCdr...>>::type
    , typename filter<std::tuple<Out..., InCar>, std::tuple<InCdr...>>::type
  >::type;
};

template <class Out>
struct filter<Out, std::tuple<>>
{
  using type = Out;
};

template <class T>
using UniqueTypes = typename filter<std::tuple<>, T>::type;

template <class T, class Tuple>
struct Index;

template <class T, class... Types>
struct Index<T, std::tuple<T, Types...>> {
    static const std::size_t value = 0;
};

template <class T, class U, class... Types>
struct Index<T, std::tuple<U, Types...>> {
    static const std::size_t value = 1 + Index<T, std::tuple<Types...>>::value;
};

template <typename T, typename Tuple>
struct HasType;

template <typename T, typename... Us>
struct HasType<T, std::tuple<Us...>> : std::disjunction<std::is_same<T, Us>...> {};

template <typename TypeToTest, typename Ret, typename Type, typename... Args>
constexpr bool has_member_type(Ret(Type::*VelPtr)(Args...)) {
    bool isTrue = false;
    [](...){ }(isTrue |= typename std::is_same<Args, TypeToTest>()...);
    return isTrue;
}

template <typename Tuple, typename Ret, typename Type, typename... Args>
constexpr bool all_parameters_in_tuple(Ret(Type::*Ptr)(Args...)) {
    bool oneIsMissing = false;
    [](...){ }(oneIsMissing |= !typename TupleHelper::HasType<std::remove_pointer_t<std::remove_const_t<std::remove_reference_t<Args>>>, Tuple>()...);
    return !oneIsMissing;
}





template <typename T, typename Tuple>
struct has_type;

template <typename T>
struct has_type<T, std::tuple<>> : std::false_type {};

template <typename T, typename U, typename... Ts>
struct has_type<T, std::tuple<U, Ts...>> : has_type<T, std::tuple<Ts...>> {};

template <typename T, typename... Ts>
struct has_type<T, std::tuple<T, Ts...>> : std::true_type {};

template <typename T, typename Tuple>
using tuple_contains_type = typename has_type<T, Tuple>::type;






    
}

