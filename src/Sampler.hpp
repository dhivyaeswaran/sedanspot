#include <math.h>
#include <string>
#include <queue>

#include "Edge.hpp"
#include "random_utils.hpp"

#ifndef SAMPLER_HPP
#define SAMPLER_HPP

using namespace std;

class PriorityQueueElement {
public:
    Edge *edge;
    double priority;
    PriorityQueueElement(Edge *edge, double priority) {
        this->edge = edge;
        this->priority = priority;
    }
};

struct ComparePriority {
    bool operator()(PriorityQueueElement const & p1, PriorityQueueElement const & p2) {
        if(p1.priority == p2.priority) {
            return random_fraction() <= 0.5;
        }
        return p1.priority > p2.priority;
    }
};

class Sampler {
public:
    Edge *removed_edge;
    Edge *added_edge;
    Sampler(int sample_size);
    pair<bool,bool> sample(Edge* edge, double weight);
    inline bool full() {
        return entries_seen >= sample_size;
    }

private:
    int sample_size;
    int entries_seen;
    priority_queue<PriorityQueueElement, vector<PriorityQueueElement>, ComparePriority> min_priority_heap;
};

#endif /* SAMPLER_HPP */
