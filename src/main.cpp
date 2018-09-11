#include<iostream>
#include <iterator>
#include <exception>
#include <boost/program_options.hpp>

#include "AnomalyDetector.hpp"
#include "Sampler.hpp"
#include "Scorer.hpp"

using namespace std;
namespace po = boost::program_options;

int main(int argc, char *argv[]) {

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("input", po::value<string>(), "input file name")
        ("delimiter", po::value<string>()->default_value(","), "column separator in input file")
        ("directed", po::value<bool>()->default_value(true), "is the graph directed?")
        ("sample-size", po::value<int>()->default_value(10000), "number of edges in sample")
        ("num-walks", po::value<int>()->default_value(50), "number of local random walks")
        ("restart-prob", po::value<double>()->default_value(0.15), "random walk's restart probability")
        ("seed", po::value<int>()->default_value(1), "control the randomness");

    po::variables_map var;
    po::store(po::parse_command_line(argc, argv, desc), var);
    po::notify(var);

    if(var.count("help")) {
        cout << desc << "\n";
        return 0;
    }

    if(!var.count("input")) {
        cout << "Missing argument --input.\n";
        return 1;
    }

    random_seed(var["seed"].as<int>());

    Sampler *sampler = new Sampler(
        var["sample-size"].as<int>()
    );
    Scorer *scorer = new Scorer(
        var["restart-prob"].as<double>(), var["num-walks"].as<int>()
    );

    AnomalyDetector detector(
        var["input"].as<string>(), var["delimiter"].as<string>(),
        sampler, scorer, var["directed"].as<bool>()
    );
    detector.run();
    return 0;
}
