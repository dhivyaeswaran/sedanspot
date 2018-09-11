#include "Edge.hpp"

Edge::Edge(string line, string delimiter) {
    size_t pos = 0;
    vector<string> tokens;
    while ((pos = line.find(delimiter)) != string::npos) {
        tokens.push_back(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());
    }
    tokens.push_back(line);
    this->time = stoi(tokens[0]);
    this->src = tokens[1];
    this->dst = tokens[2];
    this->wt = stod(tokens[3]);
    this->label = (tokens[4].compare("-") != 0);
}

Edge::Edge(int time, const string& src, const string& dst, double wt, bool label) {
    this->time = time;
    this->src = src;
    this->dst = dst;
    this->wt = wt;
    this->label = label;
}

Edge* Edge::reverse() {
    return new Edge(time, dst, src, wt, label);
}
