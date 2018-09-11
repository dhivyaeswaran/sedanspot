#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "random_utils.hpp"

#ifndef LAZYALIASTABLE_HPP
#define LAZYALIASTABLE_HPP

using namespace std;

class LazyAliasTable {
    public:
        LazyAliasTable();
        void increment(string key, double val);
        void decrement(string key, double val);

        inline string random_key() {
            if(last_index == -1)
                return string();
            if(use_cached == false)
                initialize_alias_table();
            int i = random_int(0, last_index);
            if(random_fraction() <= prob[i])
                return keys[i];
            else
                return alias[i];
        }

        inline double get_total() {
            return total;
        }

        inline vector<string> get_keys() {
            return keys;
        }

        inline vector<double> get_values() {
            return values;
        }

private:
    unordered_map<string, int> key_to_pos;
    vector<string> keys;
    vector<double> values;
    vector<string> alias;
    vector<double> prob;
    int last_index;
    bool use_cached;
    double total;
    void initialize_alias_table();

};

#endif /* LAZYALIASTABLE_HPP */
