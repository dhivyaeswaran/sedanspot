#include "Sampler.hpp"

Sampler::Sampler(int sample_size) {
    this->sample_size = sample_size;
    entries_seen = 0;
}

pair<bool,bool> Sampler::sample(Edge* edge, double weight) {
    entries_seen += 1;
    double score = log10(random_fraction()) / weight;
    if(entries_seen <= sample_size) {
        PriorityQueueElement element(edge, score);
        min_priority_heap.push(element);
        added_edge = edge;
        return make_pair(false, true);
    } else {
        PriorityQueueElement least_priority_element = min_priority_heap.top();
        if(least_priority_element.priority < score) {
            added_edge = edge;
            removed_edge = least_priority_element.edge;
            min_priority_heap.pop();
            PriorityQueueElement element(edge, score);
            min_priority_heap.push(element);
            return make_pair(true, true);
        } else {
            return make_pair(false, false);
        }
    }
}
