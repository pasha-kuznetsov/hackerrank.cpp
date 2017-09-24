// Bit Manipulation: Lonely Integer
// https://www.hackerrank.com/challenges/ctci-lonely-integer

#include <iostream>
#include <vector>

using namespace std;

int lonely_integer(const vector <int>& a) {
    int n = 0;
    for (int i : a)
        n ^= i;
    return n;
}

int main(){
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
       cin >> a[i];
    cout << lonely_integer(a) << endl;
    return 0;
}
