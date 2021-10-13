#include <vector>

#include "Vector2.hpp"

template<typename T>
struct List {
    T item;

};

extern "C" {
    int GetResult() {
    
        auto add = [] (auto a, auto b) {
            return a+b;
        };
    
        Vector2 vec1 {10,10};
        Vector2 vec2 {10,10};
        Vector2 vec3 {10,10};

        Vector2 result = vec1 + vec2 - vec3;

        List<int> list;
        list.item = 123;
        
        //return (int)result.Length() + add(11, 11) + list.item;
        return list.item;
        
    }
}
