/**
 * @file change_variable.cpp
 * @brief change the one variable
 * @author Koya KATO (Ayako SHIMADA)
 * @date 2024-06-26 11:01:42
 */

#include<vector>
#include<string>
#include<iostream>
#include<random>
#include<algorithm>
#include"change_variable.hpp"

// generate random value
int choose_variable(int num){
    // initialize 
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    // uniform distribution
    std::uniform_int_distribution<> dist(0, num);
    return dist(engine);
}

/**
 * @fn void  change_variable(std::vector<int> A, std::vector<int> B)
 * @brief 1. choose a \in A and b \in B, 
 *        2. A <- A \cup {b} / {a}, B <- B \cup {a} / {b}
 * @return void
*/
void change_variable(std::vector<int> &A, std::vector<int> &B){
    int variable_size = A.size();

    // 1. choose a \in A and b \in B 
    int a_num = choose_variable(variable_size - 1);
    int b_num = choose_variable(variable_size - 1);

    // 2. A <- A \cup {b} / {a}, B <- B \cup {a} / {b}
    int a = A[a_num];
    int b = B[b_num];
    auto it_a = std::find(A.begin(), A.end(), a);
    A.erase(it_a);
    A.push_back(b);
    auto it_b = std::find(B.begin(), B.end(), b);
    B.erase(it_b);
    B.push_back(a);

    return;
}