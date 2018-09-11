#include "AnomalyDetector.hpp"

AnomalyDetector::AnomalyDetector(string file_name, string delimiter, Sampler *sampler, Scorer *scorer, bool directed) {
    this->file_name = file_name;
    this->delimiter = delimiter;
    this->sampler = sampler;
    this->scorer = scorer;
    this->directed = directed;
}

void AnomalyDetector::run() {
    ifstream file(file_name);
    string line;
    queue<Edge*> edge_queue;
    int prev_time = -1;
    int cur_time = 0;
    double sampling_weight;

    double sampling_time = 0.0;
    double scoring_time = 0.0;
    double updating_time = 0.0;

    while(getline(file, line)) {
        Edge* edge = new Edge(line, delimiter);
        if(edge->time !=  cur_time) {
            if(edge_queue.size() > 0) {
                sampling_weight = (cur_time - prev_time) / (double) edge_queue.size();
                process_edges(&edge_queue, sampling_weight, &scoring_time, &sampling_time, &updating_time);
            }
            prev_time = cur_time;
            cur_time = edge->time;
        }
        edge_queue.push(edge);
    }
    sampling_weight = (cur_time - prev_time) / (double) edge_queue.size();
    process_edges(&edge_queue, sampling_weight, &scoring_time, &sampling_time, &updating_time);


    cerr << "scoring time: " << scoring_time << endl;
    cerr << "sampling time: " << sampling_time << endl;
    cerr << "updating time: " << updating_time << endl;
    cerr << "total time without IO: " << scoring_time + sampling_time + updating_time << endl;
}

void AnomalyDetector::process_edges(
        queue<Edge*> *edge_queue, double sampling_weight,
        double *scoring_time,  double *sampling_time, double *updating_time
) {
    Edge *edge;
    double score;
    pair<bool, bool> sampling_result;
    std::chrono::steady_clock::time_point begin, end;

    while(!edge_queue->empty()) {
        edge = edge_queue->front();

        /* scoring */
        begin = std::chrono::steady_clock::now();
        if(sampler->full())
            if(directed == true)
                score = scorer->score(edge);
            else
                score = (scorer->score(edge) + scorer->score(edge->reverse())) / 2.0;
        else
            score = 0.0;
        end = std::chrono::steady_clock::now();
        (*scoring_time) += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;

        /* sampling */
        begin = std::chrono::steady_clock::now();
        sampling_result = sampler->sample(edge, sampling_weight);
        end = std::chrono::steady_clock::now();
        (*sampling_time) += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;

        /* updating */
        begin = std::chrono::steady_clock::now();
        if(sampling_result.first == true) {
            scorer->remove(sampler->removed_edge);
            if(directed == false)
                scorer->remove(sampler->removed_edge->reverse());
        }
        if(sampling_result.second == true) {
            scorer->add(sampler->added_edge);
            if(directed == false)
                scorer->add(sampler->added_edge->reverse());
        }
        end = std::chrono::steady_clock::now();
        (*updating_time) += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;

        cout << score << endl;
        edge_queue->pop();
    }
}
