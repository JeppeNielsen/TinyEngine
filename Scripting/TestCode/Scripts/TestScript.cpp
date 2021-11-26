#include <vector>
#include <cmath>

template<typename T>
struct List {
    T item;

};


int fibonaci(int start, int count) {
  if (count == 0) {
    return 0;
  }


 return start + fibonaci(start + 1, --count);

}

struct Vector2 {
  float x;
  float y;

  float Length() {
    return sqrt(x*x+y*y);
  }

};


extern "C" {
    int GetResult() {
    
       std::vector<int> bla;

       bla.push_back(2);
       bla.push_back(2);
       bla.push_back(10);

       int total = 0;
       for(auto i : bla) {
            total += i;
       }

       total++;
        
        List<int> list;

        list.item = 12;

        total += list.item;

        total = 0;

        std::vector<int> numbers {1,2,3,4,5,6};

        for(auto n : numbers) {
          total+=n*2;
        }

        Vector2 vec = {3,4};

        //return (int)result.Length() + add(11, 11) + list.item;
        return (int)vec.Length()+total;
        
    }
}
