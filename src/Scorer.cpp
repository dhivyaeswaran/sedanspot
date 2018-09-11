#include "Scorer.hpp"

Scorer::Scorer(double eps, int num_walks) {
    this->eps = eps;
    this->num_walks = num_walks;
    this->distribution = geometric_distribution<int>(eps);
}

void Scorer::add(Edge* edge) {
    /* source count and adjacency list */
    if(src_count.count(edge->src) == 0) {
        src_count[edge->src] = 0;
        adjacency_list[edge->src] = LazyAliasTable();
    }
    src_count[edge->src] += 1;
    adjacency_list[edge->src].increment(edge->dst, edge->wt);
    /* destination count */
    if(dst_count.count(edge->dst) == 0) {
        dst_count[edge->dst] = 0;
    }
    dst_count[edge->dst] += 1;
}

void Scorer::remove(Edge* edge) {
    /* source count  adjacency list */
    src_count[edge->src] -= 1;
    adjacency_list[edge->src].decrement(edge->dst, edge->wt);
    if(src_count[edge->src] == 0) {
        src_count.erase(edge->src);
        adjacency_list.erase(edge->src);
    }
    /* destination count */
    dst_count[edge->dst] -= 1;
    if(dst_count[edge->dst] == 0) {
        dst_count.erase(edge->dst);
    }
}

double Scorer::score(Edge* edge) {
    double visit_frac_before = get_visit_fraction(edge->src, edge->dst);
    double visit_frac_after = get_visit_fraction(edge->src, edge->dst, edge);
    return visit_frac_before > visit_frac_after ? 0 : visit_frac_after-visit_frac_before;
}

double Scorer::get_visit_fraction(string src, string dst, Edge *i_edge) {
    int walk_length = 0;
    int num_steps = 0;
    int num_visits = 0;
    string cur_node;
    for(int i=0; i<num_walks; i++) {
        walk_length = distribution(generator) + 1;
        cur_node = src;
        num_steps += walk_length;
        for(int step=0; step<walk_length; step++) {
            if(cur_node.compare(dst) == 0)
                num_visits += 1;
            cur_node = sample_neighbor(cur_node, i_edge);
            if(cur_node.empty())
                break;
        }
    }
    return num_visits / ((double) num_steps);
}
