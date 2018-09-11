#include <iostream>
#include <string>
#include <vector>

#ifndef EDGE_HPP
#define EDGE_HPP

using namespace std;

class Edge {
public:
    int time;
    string src;
    string dst;
    double wt;
    bool label;
    Edge(string line, string delimiter);
    Edge(int time, const string& src, const string& dst, double wt, bool label);
    Edge* reverse();
};

#endif /* EDGE_HPP */
