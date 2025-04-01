#include <random>
#include <cassert>
#include <chrono>

using namespace std;

int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);

int randrange(int r) {
    assert(r > 0);
    return mt() % r;
}

int randrange(int l, int r) {
    return l + randrange(r - l);
}

int randint(int a, int b) {
    return randrange(a, b + 1);
}