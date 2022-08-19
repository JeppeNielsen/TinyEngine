//
//  TestCallable.cpp
//  NewEcs
//
//  Created by Jeppe Nielsen on 06/08/2022.
//
#include <string>
#include <type_traits>
#include "TupleHelper.hpp"
#include <iostream>



template <typename> struct FnArgs;

template <typename R, typename ...Args>
struct FnArgs<R(Args...)>
{
    using type = std::tuple<Args...>;
};




template<typename ...T>
constexpr bool Test2(T... t) {
    const std::tuple<T...> tuple;
    
    TupleHelper::Iterate(tuple, [](auto& c) {
        std::cout << " value = " << c << std::endl;
    });
    
    return false;
}


template<typename T, typename TypeToTest>
constexpr bool Test() {
    using FT = typename FnArgs<T>::type;
    
    constexpr FT tuple;
    bool isTrue = false;
    
    TupleHelper::Iterate(tuple, [&isTrue](auto c) {
        if constexpr (typename std::is_same<decltype(c), TypeToTest>()) {
            isTrue = true;
        }
    });
    
    return isTrue;
}

struct can_call_test
{
    template<typename F, typename... A>
    static decltype(std::declval<F>()(std::declval<A>()...), std::true_type())
    f(int) {
        const std::tuple<A...> tuple;
        
        TupleHelper::Iterate(tuple, [](auto& c) {
            std::cout << " value = " << c << std::endl;
        });
    }

    template<typename F, typename... A>
    static std::false_type
    f(...) {
        
        const std::tuple<A...> tuple;
        
        TupleHelper::Iterate(tuple, [](auto& c) {
            std::cout << " value = " << c << std::endl;
        });
        
    }
};

template<typename F, typename... A>
struct can_call : decltype(can_call_test::f<F, A...>(0)) {
    
};

template<typename F, typename... A>
struct can_call <F(A...)> : can_call <F, A...> { };

template<typename... A, typename F>
constexpr can_call<F, A...>
is_callable_with(F&&) { return can_call<F(A...)>{}; }

void f1(int) { }
void f2(const std::string&) { }
void f3(bool hej1, int hej2) {
    
    std::cout <<"f3 called " << std::endl;
}

struct Vel {
    float x;
    float y;
};

struct VelocitySystem {
    
    void Step(int normal, int start, float speed) {
        std::cout << "VelocitySystem::Step called" << std::endl;
    }
    
};

struct MovementSystem {
    
    bool Step(Vel& vel) {
        std::cout << "VelocitySystem::Step called" << std::endl;
        return true;
    }
    
};

template <typename R, typename... T>
 std::tuple<T...> function_args(R (*)(T...))
 {
     return std::tuple<T...>();
 }

template <typename R, typename... T>
 std::tuple<T...> member_args(void(R::*VelPtr)(T...))
 {
     return std::tuple<T...>();
 }


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

template <typename TypeToTest, typename Ret, typename Type, typename... Args>
constexpr bool has_member_type2(Ret(Type::*VelPtr)(Args...))
{
    bool isTrue = false;
    [](...){ }(isTrue = typename std::is_same<Args, TypeToTest>()...);
    return isTrue;
}

template <class ... Ts>
void Foo (Ts && ... inputs)
{
    int i = 0;

    ([&]
    {
        // Do things in your "loop" lambda

        ++i;
        std::cout << "input " << i << " = " << inputs << std::endl;

    } (), ...);
}


int main_callable()
{
    typedef void (VelocitySystem::*VelPtr)(int, int, float);
    
    VelocitySystem velocitySystem;
    
    VelPtr velPtr = &VelocitySystem::Step;
    
    bool is_true = is_callable_with<bool>(f3);
    
    //static_assert(Test<decltype(VelocitySystem::Step), float>(), "OFF");
    //(velocitySystem.*(velPtr(3,1,2.0f)));
    
    VelocitySystem& pp = velocitySystem;
    
    (pp.*velPtr)(3,1,2.0f);
    
    using FT = FnArgs<decltype(f3)>::type;

    FT tf;
    
    std::cout << ""<< std::get<0>(tf) << std::endl;
    
    auto args = member_args(&VelocitySystem::Step);
    
    
    //auto args = member_args<VelocitySystem>(velPtr);
    
    // get the tuple type
     
    //auto args = function_args<VelPtr>(&velocitySystem);
    
    
    //static_assert(is_callable_with<int>(f1), "Oops");
    //static_assert(!is_callable_with<int>(f2), "Oops");
    
    if constexpr (has_member_type<int>(&VelocitySystem::Step)) {
        std::cout << "Yes "<<std::endl;
    }
    
    static_assert(has_member_type<int>(&VelocitySystem::Step), "NONO");
    static_assert(has_member_type<float>(&VelocitySystem::Step), "NONO");
    static_assert(!has_member_type<bool>(&VelocitySystem::Step), "NONO");
    static_assert(has_member_type2<Vel&>(&MovementSystem::Step), "NONO");

    int hej = 2;
    
    int& ref = hej;
    
    return 0;
}
