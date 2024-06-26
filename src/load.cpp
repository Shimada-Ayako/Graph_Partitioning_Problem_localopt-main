/**
 * @file load.cpp
 * @brief load the matrix to solve
 * @author Koya KATO (Ayako SHIMADA)
 * @date 2024-06-25 10:33:41
 */

#include<vector>
#include<string>
#include <fstream>
#include <sstream>
#include"load.hpp"


// delimiter 
std::vector<std::string> split(std::string &input, char delimiter) {
  std::istringstream stream(input);
  std::string field;
  std::vector<std::string> result;
  while (getline(stream, field, delimiter)) result.push_back(field);
  return result;
}

/**
 * @fn std::vector<std::vector<int> > load(std::string filename)
 * @brief load the adjacency matrix (csv format)
 * @return adjacency matrix (vector)
*/
std::vector<std::vector<int> > load(std::string filename){
    std::ifstream ifs(filename); // file stream
    std::vector<std::vector<int> > load_matrix; // adjacency matrix
    if (ifs) {
        std::string line;
        
        while (getline(ifs, line)) {
            std::vector<int> datvec;
            std::vector<std::string> strvec = split(line, ',');
            for (auto &&s : strvec) datvec.push_back(std::stoi(s)); // convert string -> int
            load_matrix.push_back(datvec);
        }
    }
    return load_matrix;
}
