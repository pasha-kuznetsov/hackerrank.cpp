// https://www.hackerrank.com/challenges/ctci-find-the-running-median

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
#include <set>

template<class Cmp>
struct heap {
    std::vector<int> v;
    int size() const { return v.size(); }
    int top() const { return v.front(); }
    void push(int x) {
        v.push_back(x);
        // push_heap(v.begin(), v.end(), Cmp());
        if (v.size() <= 1) return;
        for (int i = v.size() - 1, p; i > 0; i = p) {
            p = (i - 1) / 2;
            if (Cmp()(v[p], v[i]))                      // v[p] < v[i]
                std::swap(v[p], v[i]);
            else
                break;
        }

    }
    int pop() {
        // pop_heap(v.begin(), v.end(), Cmp());
        int top = v.back();
        std::swap(v.front(), top);
        int n = v.size() - 1;
        for (int p = 0, max; 2 * p + 1 < n; p = max) {
            int l = 2 * p + 1;
            int r = 2 * p + 2;
            max = r < n && Cmp()(v[l], v[r]) ? r : l;   // v[l] < v[r]
            if (Cmp()(v[p], v[max]))                    // v[p] < v[max]
                std::swap(v[p], v[max]);
            else
                break;
        }
        v.pop_back();
        return top;
    }
};

typedef heap<std::less<int>> max_heap;
typedef heap<std::greater<int>> min_heap;

int main() {
    std::cout.precision(1);
    int n;
    std::cin >> n;
    max_heap left;
    min_heap right;
    double m;
    for(int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if (i == 0 || x < m) left.push(x); else right.push(x);
        while (left.size() < right.size()) left.push(right.pop());
        while (left.size() > right.size() + 1) right.push(left.pop());
        m = left.size() == right.size() ? (left.top() + right.top()) * 0.5 : left.top();
        std::cout << std::fixed << m << std::endl;
    }
    return 0;
}
