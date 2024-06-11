#include <iostream>
#include <stack>
#include <queue>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <numeric>

template <typename T, typename Container = std::vector<T>>
class Pila {
    Container cnt;
public:
    Pila() = default;
    explicit Pila(Container cnt): cnt(std::move(cnt)) {}

    template<class Iterator>
    Pila(Iterator start, Iterator stop) {
        std::copy(start, stop, std::back_inserter(cnt));
    }

    bool empty() { return cnt.size() == 0; }
    size_t size() { return cnt.size(); }
    void push(T value) { cnt.push_back(value); }
    void pop() { cnt.pop_back(); }
    T& top() { return cnt.back(); }
    template <typename ...Params>
    void emplace(Params ...params) {
        cnt.emplace_back(params...);
    }
    void swap(Pila other) { std::swap(this->cnt, other.cnt); }
};

template <typename T, typename Container = std::deque<T>>
requires (!std::same_as<Container, std::vector<T>>)
class Cola {
    Container cnt;
public:
    Cola() = default;
    explicit Cola(Container cnt): cnt(std::move(cnt)) {}

    template<class Iterator>
    Cola(Iterator start, Iterator stop) {
        std::copy(start, stop, std::back_inserter(cnt));
    }

    bool empty() { return cnt.size() == 0; }
    size_t size() { return cnt.size(); }
    void push(T value) { cnt.push_back(value); }
    void pop() { cnt.pop_front(); }
    T& front() { return cnt.front(); }
    T& back() { return cnt.back(); }
    template <typename ...Params>
    void emplace(Params ...params) {
        cnt.emplace_back(params...);
    }
    void swap(Cola other) { std::swap(this->cnt, other.cnt); }
};

template <typename T, typename ... Params, template <typename ...> class AdapterType>
void print(AdapterType<T, Params...> a) {
    if constexpr (std::is_same_v<AdapterType<T>, std::stack<T>> || std::is_same_v<AdapterType<T>, Pila<T>>)  {
        while (!a.empty()) {
            std::cout << a.top() << " ";
            a.pop();
        }
        std::cout << std::endl;
    }
    if constexpr (std::is_same_v<AdapterType<T>, std::queue<T>> || std::is_same_v<AdapterType<T>, Cola<T>>) {
        while (!a.empty()) {
            std::cout << a.front() << " ";
            a.pop();
        }
        std::cout << std::endl;
    }
}

void ejemplo_stack_1() {
    std::stack<int> s1;
    s1.push(1);
    s1.push(3);
    s1.push(4);
    s1.emplace(6);
    print(s1);

    std::vector<int> v1 = {10, 20, 30, 40};
    std::stack<int, std::vector<int>> s2(v1);
    print(s2);
//    std::stack<int> s3(v1.begin(), v1.end());
}

void ejemplo_stack_2() {
    Pila<int> s1;
    s1.push(1);
    s1.push(3);
    s1.push(4);
    s1.emplace(6);
    print(s1);

    std::vector<int> v1 = {10, 20, 30, 40};
    Pila<int, std::vector<int>> s2(v1);
    print(s2);
    Pila<int> s3(v1.begin(), v1.end());
    print(s3);
}

void ejemplo_queue_1() {
    std::vector<int> v1 = {10, 20, 30, 40};
    std::queue<int> q1;
    for (const auto& item: v1)
        q1.push(item);
    print(q1);
    std::deque<int> d1 = {100, 200, 300, 400};
    std::queue<int> q2(d1);
    print(q2);
    std::queue<int, std::vector<int>> q3 (v1);
//    q3.pop();
//    print(q3);
}


void ejemplo_queue_2() {
    std::vector<int> v1 = {10, 20, 30, 40};
    Cola<int> q1;
    for (const auto& item: v1)
        q1.push(item);
    print(q1);
    std::deque<int> d1 = {100, 200, 300, 400};
    Cola<int> q2(d1);
    print(q2);
//    Cola<int, std::vector<int>> q3 (v1);
//    q3.pop();
//    print(q3);
}

int main() {
//    ejemplo_stack_1();
//    ejemplo_stack_2();
//    ejemplo_queue_1();
    ejemplo_queue_2();
    return 0;
}
