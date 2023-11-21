//
// Created by Maddox Guthrie on 6/11/23.
//

#ifndef UNO_ITERABLE_STACK_H
#define UNO_ITERABLE_STACK_H

#include <stack>

#include <deque>

template<typename T, typename Container = std::deque<T>>
class iterable_stack : public std::stack<T, Container> {
    using std::stack<T, Container>::c;

public:
    auto begin() {
        return std::begin(c);
    }

    auto end() {
        return std::end(c);
    }

    auto begin() const {
        return std::begin(c);
    }

    auto end() const {
        return std::end(c);
    }
};

#endif //UNO_ITERABLE_STACK_H