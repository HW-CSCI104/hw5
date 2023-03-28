#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function

void recurse(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict, std::set<std::string>& answers) {
        string f = floating;
        bool completed = true;
        size_t pos = in.size();
        size_t empty = 0;
        for (size_t i = 0; i < in.size(); i++) {
            if (in[i] == '-') {
                if (pos == in.size()) {
                    completed = false;
                    pos = i;
                }
                empty++;
            }
        }

        if (empty < f.size()) {
            return;
        }

        if (completed && dict.find(in) != dict.end() && f.size() == 0) {
            answers.insert(in);
            return;
        } else if (completed) {
            return;
        }

        string word = in;

            for (char c = 'a'; c <= 'z'; c++) {
                bool bl = false;
                word[pos] = c;
                string temp = f;
                for (size_t k = 0; k < temp.size(); k++) {
                    if (temp[k] == word[pos]) {
                        temp.erase(k,1);
                        bl = true;
                        break;
                    }
                }

 
                if (empty-1 < temp.size() && !bl) {
                    continue;
                }

                recurse(word, temp, dict, answers);

            }

    }

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict) {
            set<string> answers;
            recurse(in, floating, dict, answers);
            return answers;

    }

// Define any helper functions here
