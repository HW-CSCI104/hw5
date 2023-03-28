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
/*
void recurse(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict, std::set<std::string>& answers) {
        bool completed = true;
        size_t pos = 0;
        
        for (size_t i = 0; i < in.size(); i++) {
            if (in[i] == '-') {
                completed = false;
                pos = i;
                break;
            }
        }

        string word = in;

        if (completed && dict.find(in) != dict.end()) {
            for (size_t k = 0; k < floating.size(); k++) {
                bool yellow = false;

                for (size_t l = 0; l < word.size(); l++) {
                    if (floating[k] == word[l]) {
                        yellow = true;
                        word.erase(l,1);
                        break;
                    }
                }

                if (!yellow) {
                    return;
                }
            }
            answers.insert(in);
            return;
        } else if (completed) {
            return;
        }




        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        for (char c : alphabet) {
            word[pos] = c;
            recurse(word, floating, dict, answers);
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

*/
    

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> answers;

    bool completed = true;
        
    for (size_t i = 0; i < in.size(); i++) {
        if (in[i] == '-') {
            completed = false;
            break;
        }
    }

    if (completed && dict.find(in) != dict.end()) {
        answers.insert(in);
        return answers;
    }

    for (set<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
        string word = *it;
        if (word.size() != in.size()) {
            continue;
        }

        bool yellow = true;
        string tmp = word;
        for (size_t j = 0; j < floating.size(); j++) {
            bool temp = true;
            for (size_t k = 0; k < tmp.size(); k++) {
                if (tmp[k] == floating[j]) {
                    tmp.erase(k,1);
                    temp = false;
                    break;
                }
            }

            if (temp) {
                yellow = false;
                break;
            }
        }

        if (!yellow) {
            continue;
        }

        bool green = true;

        for (size_t i = 0; i < in.size(); i++) {
            if ((in[i] != '-' && in[i] != word[i]) || (word[i] < 'a')) {
                green = false;
                break;
            }
        }

        if (!green) {
            continue;
        }

        answers.insert(word);
    }

    return answers;
}

// Define any helper functions here
