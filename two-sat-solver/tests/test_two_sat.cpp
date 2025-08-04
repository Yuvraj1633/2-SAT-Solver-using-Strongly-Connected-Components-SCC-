
// File: tests/test_two_sat.cpp
#include <iostream>
#include <vector>
#include "two_sat_solver.h"

int main() {
    int tests_passed = 0;
    int tests_total = 0;

    // Test 1: Simple satisfiable formula (x1 ∨ x2) ∧ (¬x1 ∨ ¬x2)
    {
        tests_total++;
        TwoSatSolver solver(2);
        solver.addClause(1, 2);    // (x1 ∨ x2)
        solver.addClause(-1, -2);  // (¬x1 ∨ ¬x2)
        bool res = solver.solve();
        bool expected = true;
        if(res != expected) {
            std::cout << "Test1 FAILED: expected " 
                      << (expected ? "SAT" : "UNSAT") << ", got " 
                      << (res ? "SAT" : "UNSAT") << "\n";
        } else {
            // Verify that the assignment satisfies all clauses
            bool ok = true;
            if(res) {
                std::vector<std::pair<int,int>> clauses = {{1,2}, {-1,-2}};
                const std::vector<bool>& assign = solver.getAssignment();
                for(auto clause : clauses) {
                    int a = clause.first;
                    int b = clause.second;
                    bool valA = (a > 0 ? assign[abs(a)-1] : !assign[abs(a)-1]);
                    bool valB = (b > 0 ? assign[abs(b)-1] : !assign[abs(b)-1]);
                    if(!(valA || valB)) {
                        ok = false;
                        break;
                    }
                }
            }
            if(!ok) {
                std::cout << "Test1 FAILED: assignment does not satisfy all clauses.\n";
            } else {
                std::cout << "Test1 PASSED.\n";
                tests_passed++;
            }
        }
    }

    // Test 2: Unsatisfiable formula (x1 ∨ x2) ∧ (¬x1 ∨ x2) ∧ (x1 ∨ ¬x2) ∧ (¬x1 ∨ ¬x2)
    {
        tests_total++;
        TwoSatSolver solver(2);
        solver.addClause(1, 2);
        solver.addClause(-1, 2);
        solver.addClause(1, -2);
        solver.addClause(-1, -2);
        bool res = solver.solve();
        bool expected = false;
        if(res != expected) {
            std::cout << "Test2 FAILED: expected " 
                      << (expected ? "SAT" : "UNSAT") << ", got " 
                      << (res ? "SAT" : "UNSAT") << "\n";
        } else {
            std::cout << "Test2 PASSED.\n";
            tests_passed++;
        }
    }

    // Test 3: Formula with 3 variables (example from documentation)
    // (x1 ∨ ¬x2) ∧ (¬x1 ∨ x2) ∧ (¬x1 ∨ ¬x2) ∧ (x1 ∨ ¬x3)
    {
        tests_total++;
        TwoSatSolver solver(3);
        solver.addClause(1, -2);
        solver.addClause(-1, 2);
        solver.addClause(-1, -2);
        solver.addClause(1, -3);
        bool res = solver.solve();
        bool expected = true;
        if(res != expected) {
            std::cout << "Test3 FAILED: expected " 
                      << (expected ? "SAT" : "UNSAT") << ", got " 
                      << (res ? "SAT" : "UNSAT") << "\n";
        } else {
            bool ok = true;
            std::vector<std::pair<int,int>> clauses = {{1,-2}, {-1,2}, {-1,-2}, {1,-3}};
            const std::vector<bool>& assign = solver.getAssignment();
            for(auto clause : clauses) {
                int a = clause.first;
                int b = clause.second;
                bool valA = (a > 0 ? assign[abs(a)-1] : !assign[abs(a)-1]);
                bool valB = (b > 0 ? assign[abs(b)-1] : !assign[abs(b)-1]);
                if(!(valA || valB)) {
                    ok = false;
                    break;
                }
            }
            if(!ok) {
                std::cout << "Test3 FAILED: assignment does not satisfy all clauses.\n";
            } else {
                std::cout << "Test3 PASSED.\n";
                tests_passed++;
            }
        }
    }

    // Summary of test results
    std::cout << tests_passed << " / " << tests_total << " tests passed.\n";
    return 0;
}
