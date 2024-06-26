/**
 * @file check_solution.cpp
 * @brief check the current solution
 * @author Koya KATO (Ayako SHIMADA)
 * @date 2024-06-26 10:24:30
 */

#include<vector>
#include<string>
#include <fstream>
#include <sstream>
#include"check_solution.hpp"

/**
 * @fn int check_solution (std::vector<std::vector<int> > matrix, std::vector<int> A, std::vector<int> B)
 * @brief check the current solution using variable set A and B.
 * @return current solution
*/
int  check_solution (std::vector<std::vector<int> > matrix, std::vector<int> A, std::vector<int> B){
    int current_solution = 0;

    for(int i = 0; i < A.size(); ++i){
        for(int j = 0; j < B.size(); ++j){
            if(matrix[A[i]][B[j]] == 1){
                current_solution++;
            }
        }
    }

    return current_solution;
}