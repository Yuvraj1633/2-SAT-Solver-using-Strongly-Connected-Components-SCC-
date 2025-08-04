// File: src/main.cpp
#include <iostream>
#include <string>
#include "two_sat_solver.h"

int main() {
    std::cout << "2-SAT Solver (using SCC algorithm)\n";
    int n_vars, n_clauses;
    std::cout << "Enter number of variables: ";
    if(!(std::cin >> n_vars)) {
        std::cerr << "Invalid input.\n";
        return 1;
    }
    TwoSatSolver solver(n_vars);
    std::cout << "Enter number of clauses: ";
    if(!(std::cin >> n_clauses)) {
        std::cerr << "Invalid input.\n";
        return 1;
    }
    std::cout << "Enter clauses (each clause as two integers (lit1 lit2), use negative for negation):\n";
    for(int i = 1; i <= n_clauses; ++i) {
        int lit1, lit2;
        std::cout << "Clause " << i << ": ";
        if(!(std::cin >> lit1 >> lit2)) {
            std::cerr << "Invalid clause input.\n";
            return 1;
        }
        solver.addClause(lit1, lit2);
    }
    bool satisfiable = solver.solve();
    if(!satisfiable) {
        std::cout << "The formula is UNSATISFIABLE.\n";
    } else {
        std::cout << "The formula is SATISFIABLE.\n";
        const std::vector<bool>& assignment = solver.getAssignment();
        std::cout << "One possible assignment:\n";
        for(int i = 0; i < n_vars; ++i) {
            std::cout << "  x" << (i+1) << " = " 
                      << (assignment[i] ? "TRUE" : "FALSE") << "\n";
        }
    }
    return 0;
}
