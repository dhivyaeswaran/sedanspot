# SedanSpot
SedanSpot, short for Streaming EDge ANomaly SPOTter, is a principled randomized algorithm to detect anomalies from an edge stream in near real-time using bounded memory (sublinear in graph size). Here, anomalies are edges connecting sparsely-connected parts of the graph (bridge edges) and possible occuring during intense bursts of activity. 

This implementation is based on the following paper - [SedanSpot: Detecting Anomalies in Edge Streams](http://www.cs.cmu.edu/~deswaran/papers/icdm18-sedanspot.pdf). *Dhivya Eswaran, Christos Faloutsos*. ICDM 2018.

## Getting started
1. Install Boost C++ library on your machine.
2. Change line 16 of Makefile to link to your Boost installation.
3. Run `make` to compile code and create the binary.
4. Run `make test` to do the above step and run code on the example dataset.
5. Run `make clean` to clean binaries and outputs.

Note: The Makefile has currently only been tested on MacOS and may require some changes for the other operating systems.

## Command line options
  * `--help`: produce help message
  * `--input`: input file name
  * `--delimiter`: column separator in input file (default: ,)
  * `--directed` : is the graph directed (=1) or undirected (=0)? If 0, edges are internally symmetrized. (default: 1)
  * `--sample-size`: number of edges in sample (default: 10000)
  * `--num-walks`: number of local random walks (default: 50)
  * `--restart-prob`: random walk's restart probability (default: 0.15)
  * `--seed`: control the randomness (default: 1)

## Input file format
SedanSpot expects the input (un)directed (un)weighted edge stream to be stored in a single file containing the following five columns in order:
1. `time (int)`: time stamp of the edge
2. `source (str)`: source ID of the edge
3. `destination (str)`: destination ID of the edge
4. `weight (float)`: weight of the edge (if weight is 0, the edge will be ignored)
5. `label (str)`: label of the edge (useful during evaluation, by default it should be left as -)

Thus, each line represents an edge. Edges should be sorted in non-decreasing order of their time stamps and the column delimiter can be passed an argument.
