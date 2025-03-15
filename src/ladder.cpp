#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg){
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d){
    int n = str1.size(), m = str2.size();
    if (abs(n - m) > d)
        return false;
    int idx1 = 0, idx2 = 0, count = 0;
    while (idx1 < n && idx2 < m){
        if (str1[idx1] != str2[idx2]){
            count++;
            if (count > d)
                return false;
            if (n > m)
                idx1++;
            else if (n < m)
                idx2++;
            else{
                idx1++;
                idx2++;
            }
        } else{
            idx1++;
            idx2++;
        }
    }
    return (count + (n - idx1) + (m - idx2)) <= d;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

void load_words(set<string>& word_list, const string& file_name){
    ifstream infile(file_name);

    if (!infile){
        error("", "", "Unable to open file " + file_name);
        return;
    }
    
    string token;
    
    while (infile >> token){
        for (char &ch : token){
            ch = tolower(ch);
        }
        word_list.insert(token);
    }
    infile.close();
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word){
        return vector<string>{};
    }
    
    queue<vector<string>> ladderQueue;
    ladderQueue.push(vector<string>{begin_word});
    
    set<string> usedWords;
    usedWords.insert(begin_word);
    
    while (!ladderQueue.empty()){
        vector<string> currentLadder = ladderQueue.front();
        ladderQueue.pop();
        string currentWord = currentLadder.back();

        for (const string& candidate : word_list){
            if (is_adjacent(currentWord, candidate) && usedWords.find(candidate) == usedWords.end()){
                usedWords.insert(candidate);
                vector<string> newLadder = currentLadder;
                newLadder.push_back(candidate);
                if (candidate == end_word) {
                    return newLadder;
                }
                ladderQueue.push(newLadder);
            }
        }
    }
    return vector<string>();
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()){
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i){
        cout << ladder[i];
        if (i < ladder.size() - 1)
            cout << " ";
    }
    cout << " \n";
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("were", "were", word_list).size() == 0);
//     my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
//     my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
//     my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
//     my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
//     my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
//     my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}