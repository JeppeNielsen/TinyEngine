
#include <vector>
//#include "ECS.hpp"

template<typename ...T>
struct System {
    
};

struct Position {
    float x;
    float y;
};


struct Velocity {
    std::vector<int> indices;
};


struct PositionSystem : System<Position, const Velocity> {
  
    
};
