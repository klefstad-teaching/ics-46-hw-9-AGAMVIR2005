#include "ladder.h"




void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();
    if (abs(len1 - len2) > d) return false;

    int i = 0, j = 0, edits = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            edits++;
            if (edits> d) return false;


            if (len1 > len2) {
                ++i;
            } else if (len2 > len1) {
                ++j;
            } else {

                ++i;
                ++j;
            }
        } else {

            ++i;
            ++j;
        }
    }

    if(i<len1 || j<len2){
        edits++;
    }

    return edits <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladders;
    vector<string> word;
    if (begin_word == end_word) {
        return word;
    }
    word.push_back(begin_word);
    ladders.push(word);
    set<string> visited;
    visited.insert(begin_word);
    while (!ladders.empty()) {
        vector<string> lastladder = ladders.front();
        ladders.pop();
        string last_word = lastladder.back();
        for (string word: word_list) {
            if (is_adjacent(word, last_word) && !visited.count(word)) {
                visited.insert(word);
                vector<string> newladder = lastladder;
                newladder.push_back(word);
                ladders.push(newladder);
                if (word == end_word) {
                    return newladder;
                }
            }
        }
    }
    return {};

}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (!ladder.empty()){
        cout << "Word ladder found: ";
        for (const auto& word : ladder) {
            cout << word << " ";
        }
    }
    else
        cout << "No word ladder found.";
    cout<<endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}