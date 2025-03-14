#include "ladder.h"
#include <iostream>
#include <fstream>


void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        error("", "", "Unable to open file " + file_name);
    }

    string word;
    while (file >> word) {
        word_list.insert(word);
    }

    file.close();
}


bool is_adjacent(const string& word1, const string& word2){
    int len1 = word1.length();
    int len2 = word2.length();

    if (abs(len1 - len2) > 1){
        return false;
    }

    int differences = 0;
    int i = 0, j = 0;

    while (i < len1 && j < len2){
        if (word1[i] != word2[j]){
            differences++;
            if (differences > 1) {
                return false;
            }
            
            if (len1 > len2) i++;
            
            else if (len1 < len2) j++;
            
            else {i++; j++;}
        } else {
            i++;
            j++;
        }
    }

    if (i < len1 || j < len2){
        differences++;
    }

    return differences == 1;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    string begin_word, end_word;
    cout << "Enter the start word: ";
    cin >> begin_word;
    cout << "Enter the end word: ";
    cin >> end_word;

    if (begin_word == end_word) {
        error(begin_word, end_word, "Start and end words cannot be the same!");
        return;
    }

    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    
    if (ladder.empty()) {
        error(begin_word, end_word, "No word ladder found");
        return;
    }

    print_word_ladder(ladder);
}

