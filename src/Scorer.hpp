#include <iostream>
#include <string>
#include <unordered_map>
#include <random>

#include "random_utils.hpp"
#include "LazyAliasTable.hpp"
#include "Edge.hpp"

#ifndef SCORER_HPP
#define SCORER_HPP

using namespace std;

class Scorer {
public:
    Scorer(double eps, int num_walks);
    void add(Edge *edge);
    void remove(Edge *edge);
    double score(Edge *edge);
    void display();

private:
    double eps;
    int num_walks;
    unordered_map<string, int> src_count;
    unordered_map<string, int> dst_count;
    unordered_map<string, LazyAliasTable> adjacency_list;

    default_random_engine generator;
    geometric_distribution<int> distribution;

    double get_visit_fraction(string src, string dst, Edge *i_edge=NULL);

    inline string sample_neighbor(string src, Edge* i_edge) {
        if(i_edge == NULL or src.compare(i_edge->src) != 0)
            return adjacency_list[src].random_key();
        double total_wt = adjacency_list[src].get_total() + i_edge->wt;
        if(random_fraction() <= i_edge->wt / total_wt)
           return i_edge->dst;
        else
            return adjacency_list[src].random_key();
    }
};

#endif /* SCORER_HPP */
