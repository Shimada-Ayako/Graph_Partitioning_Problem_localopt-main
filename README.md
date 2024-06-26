# Graph_Partitioning_Problem_localopt
Serach for a local optimum solution to the graph 
partitioning problem.

<!-- Badges -->
<table>
    <tr>
        <td>License</td>
        <td>Lang</td>
        <td>Editor</td>
    </tr>
    <tr>
        <td>
            <img src="http://img.shields.io/badge/license-MIT-blue.svg?style=flat">
        </td>
        <td>
            <img src="https://img.shields.io/badge/-C++-00599C.svg?logo=cplusplus">
            <img src="https://img.shields.io/badge/-Boost-F7901E.svg?logo=boost">
        </td>
        <td>
            <img src="https://img.shields.io/badge/-VSCode-007ACC.svg?logo=visualstudiocode">
        </td>
    </tr>
</table>

# Overview
The graph partitioning problem is formulated as follows:
 
- Input:  
    - An undirected graph $G$ with an even number of variable.  
- Feasible Solution:
    - A partition of the variable set of $G$ int $\textbf{X}$ and $\textbf{Y}$.
- Objective Function:
    - Minimize the number of edges between $\textbf{X}$ and $\textbf{Y}$

To address this problem, the following operations are repeatedly performed to update the feasible solution:

Let \{ $\textbf{X}$, $\textbf{Y}$ \} be the currently best feasible solution:
1. Randomly select variable $x$ $\in$ $\textbf{X}$ and $y$ $\in$ $\textbf{Y}$
2. Update as follows: $\textbf{X}$ := $\textbf{X}$ $\cup$ \{ $y$ \} $\backslash$ \{ $x$ \}, $\textbf{Y}$ := $\textbf{Y}$ $\cup$ \{ $x$ \} $\backslash$ \{ $y$ \} 

By repeating these steps, we search for a local optimum solution.

# Install 
This project requires [Boost](http://www.boost.org/). Please see the documentation for more details.

# Usage
This package entails following steps:
## 1. build
```
mkdir build  
cmake -S . -B build
cd build
make
```
## 2. make simulation data
```
cd ..
cd test
./make_data <variable size> <output file name(csv format)>
```

## 3. solve the problem
```
cd ..
cd build/bin/
./main <adjacency matrix(csv format) path> -i <iteration number> -t <maximum running time>
```
The ```-help```command line option will show more information about main program. For example:
```
./main --help
```
# Example
```
% ./main ../../test/test_matrix20.csv -i 10                                                              
initial solution: 53
new_solution: 52
new_solution: 51
new_solution: 48
new_solution: 47
new_solution: 44
solution: 44
1 2 5 7 8 9 15 19 18 11
10 12 13 14 16 0 6 3 17 4
 0.000000s wall, 0.000000s user + 0.000000s system = 0.000000s CPU (n/a%)
```

```
% ./main ../../test/test_matrix20.csv -i 1000000 -t 10                                                       
Maximum running time: 10
initial solution: 53
new_solution: 52
new_solution: 47
new_solution: 45
new_solution: 43
new_solution: 42
new_solution: 41
out of time
solution: 41
0 1 5 8 9 15 18 11 7 19
10 12 14 16 17 6 2 3 13 4
 10.000000s wall, 5.840000s user + 4.140000s system = 9.980000s CPU (99.8%)
```

# License
The source code is licensed MIT.


