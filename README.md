# SEDANSPOT
SOAR, short for Streaming EDge ANomaly SPOTter, is a principled randomized algorithm to detect anomalies in a stream of edges in near real-time using bounded memory (sublinear in graph size). This implementation is based on the following paper - [SedanSpot: Detecting Anomalies in Edge Stream](http://www.cs.cmu.edu/~deswaran/papers/icdm18-sedanspot.pdf). *Dhivya Eswaran, Christos Faloutsos*. ICDM 2018.


##Input format
Each line is an edge
<time (int), source (str), destination (str), weight (float), label (str)>
The edges should be sorted in non-decreasing order of their time stamps.

## Parameters
./bin/SedanSpot --help
Allowed options:
  --help                                produce help message
  --input arg                           input file name
  --delimiter arg (=,)                  column separator in input file
  --directed arg (=1)                   is the graph directed?
  --sample-size arg (=10000)            number of edges in sample
  --num-walks arg (=50)                 number of local random walks
  --restart-prob arg (=0.14999999999999999)
                                        random walk's restart probability
  --seed arg (=1)                       control the randomness

## Getting started
(1) Install Boost C++ library on your machine.
(2) Change line 16 of Makefile to link to your Boost installation.
(3) Run "make" to compile code and create the binary.
(4) Run "make test" to do (3) and run code on the example dataset.
(5) Run "make clean" to clean binaries and outputs.

The Makefile has currently only been tested on MacOS and may require some changes for the other OS.
