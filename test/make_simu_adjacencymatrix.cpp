/**
 * @file make_simu_adjacencymatrix.cpp
 * @brief make simulation adjacency matrix
 * @author Koya KATO (Ayako SHIMADA)
 * @date 2024-06-26 13:03:01    
*/


#include<iostream>
#include<random>
#include<fstream>

// print adjacency matrix
void printAdjacencyMatrix(const std::vector<std::vector<int> > &matrix, std::ostream& out){
    for(int i = 0; i < matrix.size(); ++i){
        for(int j = 0; j < matrix[0].size() - 1; ++j){
            out << matrix[i][j] << ",";
        }
        out << matrix[i][matrix[0].size()] << std::endl;
    }
}


int main(int argc, char *argv[]){
    // help
    if(argc != 3){
        std::cerr << "Usage: " << argv[0] << " <graph_size>  <output_file>" << std::endl;
        std::exit(1);
    }

    // graph size
    int graph_size = std::stoi(argv[1]);
    if(graph_size <= 0){
        std::cerr << "Graph size must be a positive integer. " << std::endl;
    }

    // output file
    std::string outputfile = argv[2];

    // initialize 
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    // uniform distribution [0, 1.0)
    std::uniform_int_distribution<> dist(0, 1);

    // initialize adjacency matrix
    std::vector<std::vector<int> > matrix(graph_size, std::vector<int>(graph_size, 0));

    // make adjacency matrix
    for(int i = 0; i < graph_size; ++i){
        for(int j = i + 1; j < graph_size; ++j){
            int random_value = dist(engine);
            matrix[i][j] = random_value;
            matrix[j][i] = random_value;
        }
    }

    // output the adjacency matrix
    std::ofstream outFile(outputfile);
    if(!outFile){
        std::cerr << "Error: Cound not open file " << outputfile << std::endl;
        std::exit(1);
    }
    std::cout << "Write adjacecy matrix to file " << outputfile << std::endl;
    printAdjacencyMatrix(matrix, outFile);

    return 0;
}