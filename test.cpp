#include "Map.hpp"
#include <cassert>

int main(){
        cs540::Map<int, int> m{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
        printf("value at key = 1: %d\n", m.at(1));
        printf("value at key = 2: %d\n", m.at(2));
        printf("value at key = 3: %d\n", m.at(3));
        printf("value at key = 4: %d\n", m.at(4));
        printf("value at key = 5: %d\n", m.at(5));

        printf("\niterating over the map using iterator\n");
        for(auto iter = m.begin(); iter != m.end(); iter++){
                printf("key: %d, value: %d\n", (*iter).first, (*iter).second);
        }

        printf("\niterating over the map using ConstIterator\n");
        for(cs540::Map<int, int>::ConstIterator citer = m.begin(); citer != m.end(); citer++){
                printf("key: %d, value: %d\n", (*citer).first, (*citer).second);
        }

        printf("\niterating over the map using ReverseIterator\n");
        for(cs540::Map<int, int>::ReverseIterator riter = m.rbegin(); riter != m.rend(); riter++){
                printf("key: %d, value: %d\n", (*riter).first, (*riter).second);
        }

        printf("\nobtaining iterator pointing to key:value pair 2:2 and then iterating from then on till the end\n");
        auto iter2 = m.find(2);
        while(iter2 != m.end()){
                printf("key: %d, value: %d\n", (*iter2).first, (*iter2).second);
                iter2++;
        }

        printf("erasing the first entry from the map and then iterating\n");
        m.erase(m.begin());
        for(auto iter3 = m.begin(); iter3 != m.end(); iter3++){
                printf("key: %d, value: %d\n", (*iter3).first, (*iter3).second);
        }
}
