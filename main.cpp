#include <iostream>
#include <list.h>
#include <list>
#include <string>

int main()
{
    List<int> list;
    std::cout << list;

    list.push_back(3);
    list.push_back(123);
    list.push_back(8);

    list.remove(123);
    std::cout << list;

    list.push_back(1234);
    std::cout << list;

    list.push_front(16);
    std::cout << list;

    list.insert(++list.begin(), 1);
    std::cout << list;

    list.insert(list.find(16), 99);
    std::cout << list;

    list.remove_first();
    std::cout << list;

    list.remove_last();
    std::cout << list;

    list.reversed();
    std::cout << list;

    for (auto i : list)
        std::cout << i * 2 << ' ';

    return 0;
}
