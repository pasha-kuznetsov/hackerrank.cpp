//
// Merge Sort: Counting Inversions
// https://www.hackerrank.com/challenges/ctci-merge-sort
//
// For each of the  datasets, print the number of inversions that must be swapped to sort the dataset.
// Only adjacent elements can be swapped.
//

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct MergeCount {
    long long swaps = 0;

    template<class It>
    void sort(It begin, It end) {
        int n = end - begin;
        if (n < 2) return;
        It m = begin + n / 2;
        sort(begin, m);
        sort(m, end);
        merge(begin, m, end);
    }
    
    template<class It>
    void merge(It begin, It m, It end) {
        vector<int> tmp;
        tmp.reserve(end - begin);
        for (It l = begin, r = m; l < m || r < end;) {
            while (l < m && (r == end || *l <= *r)) tmp.push_back(*l++);
            while (r < end && (l == m || *r >= *l)) tmp.push_back(*r++);
            while (r < end && (l == m || *r < *l)) tmp.push_back(*r++), swaps += m - l;
        }
        copy(tmp.begin(), tmp.end(), begin);
    }
};

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        int n; cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
           cin >> arr[i];
        MergeCount m;
        m.sort(arr.begin(), arr.end());
        cout << m.swaps << endl;
    }
    return 0;
}
