
#include <vector>


extern "C" {
    int GetSize(int base) {
    
        auto add = [=] (auto a, auto b) {
            return base + a+b;
        };

        return add(111,222);
    }
}


template<class T>
struct Collection {
    T inner;
};

extern "C" {
    int GetCollection(Collection<int>& collection) {
        return collection.inner + 100;
    }
}


struct Position {
    int x;
    int y;
};

static int counter = 0;

extern "C" {
    void AddPosition(std::vector<Position>& positions) {
        Position pos;
        pos.x = 1;
        pos.y = 2 + counter++;
        positions.emplace_back(pos);
    }
}
