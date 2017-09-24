//
// Time Complexity: Primality
// https://www.hackerrank.com/challenges/ctci-big-o
//
// A prime is a natural number greater than  that has no positive divisors other
// than  and itself. Given  integers, determine the primality of each integer
// and print whether it is Prime or Not prime on a new line.
//
// Note: If possible, try to come up with an O(sqrt(n)) primality algorithm,
// or see what sort of optimizations you can come up with for an
// O(n) algorithm. Be sure to check out the Editorial after submitting your code!
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

// to optimize future tests, keep track of:
// * prime numbers found so far
static std::vector<int> ordered_primes = {2, 3};
static std::unordered_set<int> primes = {2, 3};
// * max tested prime candidate
int max_tested = 3;

// can only be used to check if `n` is a prime
// if max_tested >= sqrt(n)
bool is_divisible_by_known_primes(int n) {
    if (primes.find(n) != primes.end())
        return false;
    if (n <= max_tested) return true;
    for (int prime : ordered_primes) {
        int sq = prime * prime;
        if (sq > n) break;
        if (sq == n) return true;
        if (n % prime == 0) return true;
    }
    ordered_primes.push_back(n);
    primes.insert(primes.end(), n);
    return false;
}

// test if `n` is a prime number
bool is_prime(int n) {
    // populate primes up to sqrt(n)
    for (int i = max_tested; i * i <= n + 1; i += 2) {
        is_divisible_by_known_primes(i);
        max_tested = i;
    }
    return !is_divisible_by_known_primes(n);
}

int main(){
    int p; std::cin >> p;
    for(int i = 0; i < p; i++) {
        int n; std::cin >> n;
        std::cout << (is_prime(n) ? "Prime" : "Not prime") << std::endl;
    }
    return 0;
}
