// File: src/two_sat_solver.h
#ifndef TWO_SAT_SOLVER_H
#define TWO_SAT_SOLVER_H

#include <vector>

class TwoSatSolver {
private:
    int n_vars;
    int n_nodes;
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> adj_rev;
    std::vector<int> comp;
    std::vector<int> order;
    std::vector<bool> visited;
    std::vector<bool> assignment;

    void dfs1(int v);
    void dfs2(int v, int comp_idx);
    int litIndex(int literal) const {
        int var_index = abs(literal) - 1;
        return 2 * var_index + (literal < 0);
    }

public:
    TwoSatSolver(int variables);
    void addClause(int lit_a, int lit_b);
    bool solve();
    const std::vector<bool>& getAssignment() const;
};

#endif
