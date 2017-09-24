//
// DP: Coin Change
// https://www.hackerrank.com/challenges/ctci-coin-change
//
// 
#include <vector>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <utility>

using namespace std;

unordered_map<long long, long long> cache;

long long calc_ways_to_make_change(const vector<int>& coins, int coin, int money);

long long make_change(const vector<int>& coins, int coin, int money) {
    if (coin >= coins.size())
        return 0;
    long long key = ((long long)coin << 32) | money;
    auto cached = cache.find(key);
    return cached == cache.end()
        ? cache[key] = calc_ways_to_make_change(coins, coin, money)
        : cached->second;
}

long long calc_ways_to_make_change(const vector<int>& coins, int coin, int money) {
    long long ways = 0;
    for (int n = money / coins[coin]; n >= 0; --n) {
        int remaining = money - coins[coin] * n;
        ways += remaining ? make_change(coins, coin + 1, remaining) : 1;
    }
    return ways;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> coins(m);
    for(int i = 0; i < m; i++)
       cin >> coins[i];
    cout << make_change(coins, 0, n) << endl;
    return 0;
}
