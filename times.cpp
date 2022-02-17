#include "classi/BST.h"
#include "classi/AVL.h"
#include "classi/RBT.h"
#include <iostream>
#include <chrono>
#include <valarray>
#include <climits>
#include <random>
using namespace std;
using namespace std::chrono;

double getResolution() {
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);
    typedef duration<double, seconds::period> secs;
    return duration_cast<secs>(end - start).count();
}

template<class typeTree>
double calcTime(int iterations, typeTree tree, int keys[]) {
    double r = getResolution();
    double Emax = 0.01;
    double minTime = (r * ((1 / Emax) + 1));
    typedef duration<double, seconds::period> secs;
    int counter = 0;
    steady_clock::time_point start = steady_clock::now(), end;

    do {
        tree = nullptr;
        for (int i = 0; i < iterations; i++) {
            if (tree->find(tree, keys[i]) == nullptr) {
                tree = tree->insert(tree, keys[i], "");
            }
        }
        end = steady_clock::now();
        counter++;
    } while (duration_cast<secs>(end - start).count() < minTime);
    tree->destroy(tree);
    return (duration_cast<secs>(end - start).count() / counter) / iterations;
}

void genKeys(int keys[], int n) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, INT_MAX);
    for (int i = 0; i < n; i++) {
        keys[i] = distribution(generator);
    }
}

int main() {
    int nMax = 1000000;
    int a = 5000;
    double b = exp((log(nMax) - log(a)) / 99);
    int n;
    int exec = 100;

    BST *bstTree;
    AVL *avlTree;
    RBT *rbtTree;

    double bstTime;
    double avlTime;
    double rbtTime;

    double bstMean = 0, bstDevStd = 0;
    double avlMean = 0, avlDevStd = 0;
    double rbtMean = 0, rbtDevStd = 0;


    for (int i = 0; i < exec; i++) {
        n = a * pow(b, i);
        int keys[n];
        genKeys(keys, n);
        bstTime = calcTime(n, bstTree, keys);
        avlTime = calcTime(n, avlTree, keys);
        rbtTime = calcTime(n, rbtTree, keys);

        bstMean += bstTime;
        bstDevStd += pow(bstTime, 2);

        avlMean += avlTime;
        avlDevStd += pow(avlTime, 2);

        rbtMean += rbtTime;
        rbtDevStd += pow(rbtTime, 2);

    }
    cout << exec << " ";

    cout << bstMean << " ";
    cout << bstDevStd << " ";

    cout << avlMean << " ";
    cout << avlDevStd << " ";

    cout << rbtMean << " ";
    cout << rbtDevStd << " ";

    return 0;
}