#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <chrono>

#include "Edge.hpp"
#include "Sampler.hpp"
#include "Scorer.hpp"

#ifndef ANOMALYDETECTOR_HPP
#define ANOMALYDETECTOR_HPP

using namespace std;

class AnomalyDetector {
public:
    AnomalyDetector(
        string file_name, string delimiter, Sampler *sampler, Scorer *Scorer,
        bool directed
    );
    void run();
private:
    string file_name;
    string delimiter;
    Sampler *sampler;
    Scorer *scorer;
    bool print_scores;
    bool directed;

    void process_edges(
            queue<Edge*> *edge_queue, double sampling_weight,
            double *scoring_time,  double *sampling_time, double *updating_time
    );
};

#endif /* ANOMALYDETECTOR_HPP */
