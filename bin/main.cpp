/**
 * @file main.c
 * @brief solve the graph partitioning problem using local optimization
 * @author Koya KATO (Ayako SHIMADA)
 * @date 2024-06-24 10:55:07
 */

#include<iostream>
#include<exception>
#include<stdexcept>
#include<boost/program_options.hpp>
#include<boost/program_options/positional_options.hpp>
#include<boost/program_options/option.hpp>
#include<boost/program_options/options_description.hpp>
#include<boost/timer/timer.hpp>
#include<boost/asio.hpp>
#include<boost/thread.hpp>
#include"load.hpp"
#include"check_solution.hpp"
#include"change_variable.hpp"

namespace po = boost::program_options;

bool outOfTime; // A variable to check if the user-specified time limit has expired.
std::string matrix_path;
int iteration_num; // A variable indicates the iteration number;



/**
 * Handler when out of time
*/
void timeout(const boost::system::error_code& /*e*/){
    printf("out of time\n");
    outOfTime = true;
}

/**
 * @fn void solve(std::string matrix_path)
 * @brief solve the graph partitioning problem using local optimization
*/
void solve(){
    //  load the adjacency matrix
    std::vector<std::vector<int> > matrix = load(matrix_path);
    int variable_num = matrix.size();
    int sol = variable_num;
    

    // divide matrix into A and B
    // if variable_num = 4 then A = {0, 1}, B = {2, 3}
    std::vector<int> A, B;
    try{
        if(variable_num % 2 != 0){
            throw std::runtime_error("ERROR: matrix size is not even.");
        }
        for(int a = 0; a < variable_num / 2; ++a){
            A.push_back(a);
        }
        for(int b = variable_num / 2; b < variable_num; ++b){
            B.push_back(b);
        }
    }catch(std::runtime_error& e){
        std::cout << e.what() << std::endl;
        std::exit(1);
    }



    // set initial solution
    sol = check_solution(matrix, A, B); 
    std::cout << "initial solution: " << sol << std::endl;

    // improve the solution
    std::vector<int> C(A.size());
    std::vector<int> D(B.size());
    int count = 0;
    bool flag = false;
    while(flag || count < iteration_num){
        if(outOfTime){  // time out
            break;
        }
        flag = true;
        for(int i = 0; i < A.size(); ++i){
            C[i] = A[i];
        }
        for(int i = 0; i < B.size(); ++i){
            D[i] = B[i];
        }

        change_variable(C, D);

        int new_sol = check_solution(matrix, C, D);

        if(new_sol >= sol){
            flag = false;
            count++;
        }else{
            for(int i = 0; i < C.size(); ++i){
                A[i] = C[i];
            }
            for(int i = 0; i < D.size(); ++i){
                B[i] = D[i];
            }
            
            std::cout << "new_solution: " << new_sol << std::endl;
            sol = new_sol;
            count = 0;
        }
    }

    // check the solution
    std::cout << "solution: " << sol << std::endl;
    // check the variable
    for(int i = 0; i < A.size() - 1; ++i){
        std::cout << A[i] << " ";
    }
    std::cout << A[A.size() - 1] << std::endl;
    for(int i = 0; i < B.size() - 1; ++i){
        std::cout << B[i] << " ";
    }
    std::cout << B[B.size() - 1] << std::endl;

    return;
}

/**
 * @fn int main (void)
 * @brief Main function to solve the graph partitioning problem using local optimization
 * @return 0 if the program completes successfully.
*/
int main(int argc, char** argv){
    boost::timer::auto_cpu_timer timer;
    int runningTime; // maximum running time
    boost::asio::io_service io; // A timer to keep track of how long the algorithm has been running.

    // description
    std::string description = std::string("Solve the  graph partitioning problem using local optimization.");
    po::options_description desc(description);

    // add options
    desc.add_options()
        ("matrix_path", po::value<std::string > (&matrix_path)->required(), "The file containing the adjacency matrix in csv format. First positional argument.")
        ("runningTime,t", po::value<int> (&runningTime)->default_value(0), "The maximum running time for the algorithm. 0 means no running time limit.")
        ("iteration_num,i", po::value<int> (&iteration_num)->default_value(100), "The maximum iteration  for the algorithm. ")
        ("help,h", "Show this help message.")
    ;

    // set options
    po::positional_options_description positionalOptions;
    positionalOptions.add("matrix_path", 1);
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc)
        .positional(positionalOptions).run(), vm);
    // show help message
    if(vm.count("help") || argc == 1){
        std::cout << desc;
        return 0;
    }
    if(iteration_num < 0){
        std::cerr << "iteration num is positive integer." << std::endl;
        std::exit(1);
    }
    po::notify(vm);
    outOfTime = false;
    boost::asio::deadline_timer t(io);
    if(runningTime > 0){
        printf("Maximum running time: %d\n", runningTime);
        t.expires_from_now(boost::posix_time::seconds(runningTime));
        t.async_wait(timeout);
        boost::thread workerThread(solve);
        io.run();
        workerThread.join();
    }else{
        solve();
    }

    return 0;
}