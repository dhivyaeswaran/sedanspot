#include "LazyAliasTable.hpp"

LazyAliasTable::LazyAliasTable() {
    use_cached = false;
    total = 0.0;
    last_index = -1;
}

void LazyAliasTable::increment(string key, double val) {
    if(val > 0) {
        if(key_to_pos.count(key) == 0) {
            last_index += 1;
            keys.push_back(key);
            values.push_back(val);
            key_to_pos[key] = last_index;
        } else {
            values[key_to_pos[key]] += val;
        }
        total += val;
        use_cached = false;
    } else if(val < 0) {
        cout << "error increment by negative value" << endl;
        exit(1);
    }
}

void LazyAliasTable::decrement(string key, double val) {
    if(val > 0) {
        if(key_to_pos.count(key) == 0) {
            cout << "error: trying to decrement non-existing key" << endl;
            exit(1);
        } else {
            int i = key_to_pos[key];
            values[i] -= val;
            if(values[i] < 0) {
                 cout << "error: value non-negative on decrementing" << endl;
                 exit(1);
            } else if(values[i] == 0) {
                string move_key = keys.back(); keys.pop_back();
                double move_value = values.back(); values.pop_back();
                if(i != last_index) {
                    keys[i] = move_key;
                    values[i] = move_value;
                    key_to_pos[move_key] = i;
                }
                last_index -= 1;
                key_to_pos.erase(key);
            }
            total -= val;
            use_cached = false;
        }
    } else if(val < 0) {
        cout << "error decrement by negative value" << endl;
        exit(1);
    }
}

void LazyAliasTable::initialize_alias_table() {
    int k = last_index + 1;
    /* reset alias table */
    prob.clear();
    alias.clear();
    for(int i=0; i<k; i++) {
        prob.push_back(0.0);
        alias.push_back("-");
    }
    /* determine scaled probabilities and small, large lists */
    double scaled_prob[k];
    vector<int> small, large;
    for(int i=0; i<k; i++) {
        scaled_prob[i] = values[i] * k / total;
        if(scaled_prob[i] < 1.0)
            small.push_back(i);
        else
            large.push_back(i);
    }
    /* move masses */
    while(!small.empty() and !large.empty()) {
        int s = small.back(); small.pop_back();
        int l = large.back(); large.pop_back();
        prob[s] = scaled_prob[s];
        alias[s] = keys[l];
        scaled_prob[l] = (scaled_prob[l] + scaled_prob[s]) - 1.0;
        if(scaled_prob[l] < 1.0)
            small.push_back(l);
        else
            large.push_back(l);
    }
    /* set remaining probabilities to 1.0 */
        while(!large.empty()) {
            prob[large.back()] = 1.0; large.pop_back();
        }
        while(!small.empty()) {
            prob[small.back()] = 1.0; small.pop_back();
        }
    use_cached = true;
}
