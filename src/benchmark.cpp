#include <iostream>
#include <chrono>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>
#include <random>
#include <iomanip>
#include "BinaryTree.hpp"

/**
 * Benchmark to compare custom BinaryTree against std::multiset.
 * Measures insertion and sequential minimum removal performance.
 */
int main() {
    const int N = 100000;
    std::vector<int> data(N);
    
    // 1. Prepare Random Data
    std::iota(data.begin(), data.end(), 1);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "================================================" << std::endl;
    std::cout << "  BENCHMARK of tree algorithms                  " << std::endl;
    std::cout << "  N = " << N << " elements (Randomized)" << std::endl;
    std::cout << "================================================" << std::endl;

    // BinaryTree
    BinaryTree<int> bst;
    
    auto bst_start_in = std::chrono::high_resolution_clock::now();
    for (int x : data) bst.insert(x);
    auto bst_end_in = std::chrono::high_resolution_clock::now();
    
    auto bst_start_out = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) bst.removeMin();
    auto bst_end_out = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> bst_in_time = bst_end_in - bst_start_in;
    std::chrono::duration<double> bst_out_time = bst_end_out - bst_start_out;

    // std::multiset
    std::multiset<int> ms;
    
    auto ms_start_in = std::chrono::high_resolution_clock::now();
    for (int x : data) ms.insert(x);
    auto ms_end_in = std::chrono::high_resolution_clock::now();
    
    auto ms_start_out = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        auto it = ms.begin();
        if (it != ms.end()) ms.erase(it);
    }
    auto ms_end_out = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> ms_in_time = ms_end_in - ms_start_in;
    std::chrono::duration<double> ms_out_time = ms_end_out - ms_start_out;

    // Print Results
    std::cout << std::left << std::setw(15) << "Structure" 
              << std::setw(15) << "Insert (s)" 
              << std::setw(15) << "RemoveMin (s)" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << std::setw(15) << "BinaryTree" 
              << std::setw(15) << bst_in_time.count() 
              << std::setw(15) << bst_out_time.count() << std::endl;
    std::cout << std::setw(15) << "std::multiset" 
              << std::setw(15) << ms_in_time.count() 
              << std::setw(15) << ms_out_time.count() << std::endl;
    std::cout << "================================================" << std::endl;

    return 0;
}