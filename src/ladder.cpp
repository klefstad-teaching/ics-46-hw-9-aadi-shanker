#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

void error(string word1, string word2, string msg){
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

void load_words(set<string>& word_list, const string& file_name){
    ifstream file(file_name);
    if (!file){
        error("", "", "Unable to open file " + file_name);
        return;
    }
    string word;
    while (file >> word){
        // Convert to lowercase
        for (char &c : word){
            c = static_cast<char>(tolower(c));
        }
        word_list.insert(word);
    }
    file.close();
}

bool is_adjacent(const string& word1, const string& word2){
    if (word1 == word2) return true;

    int len1 = word1.length();
    int len2 = word2.length();

    if (abs(len1 - len2) > 1)
        return false;

    int differences = 0;
    int i = 0, j = 0;
    while (i < len1 && j < len2){
        if (word1[i] != word2[j]){
            differences++;
            if (differences > 1)
                return false;
            if (len1 > len2)
                i++;
            else if (len1 < len2)
                j++;
            else{
                i++;
                j++;
            }
        } else{
            i++;
            j++;
        }
    }
    if (i < len1 || j < len2)
        differences++;
    return differences == 1;
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    
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
    if (ladder.empty()){
        error(begin_word, end_word, "No word ladder found");
        return;
    }
    print_word_ladder(ladder);
    // my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    // my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    // my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    // my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    // my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    // my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

bool edit_distance_within(const string& str1, const string& str2, int d){
    int n = str1.size(), m = str2.size();
    if (abs(n - m) > d) return false;
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            int cost = (str1[i-1] == str2[j-1]) ? 0 : 1;
            dp[i][j] = min({dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + cost});
        }
        int min_val = *min_element(dp[i].begin(), dp[i].end());
        if (min_val > d) return false;
    }

    return dp[n][m] <= d;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word){
        error(begin_word, end_word, "Start and end words cannot be the same!");
        return{};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()){
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        const string& last_word = current_ladder.back();
        if (last_word == end_word){
            return current_ladder;
        }
        for (const auto& dict_word : word_list){
            if (visited.find(dict_word) == visited.end() && is_adjacent(last_word, dict_word)){
                visited.insert(dict_word);
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(dict_word);
                if (dict_word == end_word){
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    return{};
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()){
        cout << "No word ladder found.\n";
        return;
    }
    
    cout << "Word ladder found: ";

    for (size_t i = 0; i < ladder.size(); i++){
        cout << ladder[i] << " ";
    }
    cout << "\n";
}