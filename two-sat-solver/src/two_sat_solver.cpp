// File: src/two_sat_solver.cpp
#include <cstdlib>
#include "two_sat_solver.h"

TwoSatSolver::TwoSatSolver(int variables) : n_vars(variables) {
    n_nodes = 2 * n_vars;
    adj.assign(n_nodes, {});
    adj_rev.assign(n_nodes, {});
    comp.assign(n_nodes, -1);
    visited.assign(n_nodes, false);
    assignment.assign(n_vars, false);
}

void TwoSatSolver::dfs1(int v) {
    visited[v] = true;
    for(int u : adj[v]) {
        if(!visited[u])
            dfs1(u);
    }
    order.push_back(v);
}

void TwoSatSolver::dfs2(int v, int comp_idx) {
    comp[v] = comp_idx;
    for(int u : adj_rev[v]) {
        if(comp[u] == -1) {
            dfs2(u, comp_idx);
        }
    }
}

void TwoSatSolver::addClause(int lit_a, int lit_b) {
    int a_index = litIndex(lit_a);
    int b_index = litIndex(lit_b);
    int na_index = a_index ^ 1;
    int nb_index = b_index ^ 1;
    adj[na_index].push_back(b_index);
    adj[nb_index].push_back(a_index);
    adj_rev[b_index].push_back(na_index);
    adj_rev[a_index].push_back(nb_index);
}

bool TwoSatSolver::solve() {
    order.clear();
    visited.assign(n_nodes, false);
    for(int i = 0; i < n_nodes; ++i) {
        if(!visited[i]) {
            dfs1(i);
        }
    }
    comp.assign(n_nodes, -1);
    int comp_idx = 0;
    for(int i = n_nodes - 1; i >= 0; --i) {
        int v = order[i];
        if(comp[v] == -1) {
            dfs2(v, comp_idx++);
        }
    }
    assignment.assign(n_vars, false);
    for(int var = 0; var < n_vars; ++var) {
        if(comp[2*var] == comp[2*var + 1]) {
            return false;
        }
        assignment[var] = comp[2*var] > comp[2*var + 1];
    }
    return true;
}

const std::vector<bool>& TwoSatSolver::getAssignment() const {
    return assignment;
}
