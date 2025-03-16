#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (abs(int(str1.size()) - int(str2.size())) > d) return false;
    int edits = 0;
    for (size_t i = 0; i < min(str1.size(), str2.size()); ++i) {
        if (str1[i] != str2[i]) {
            if (++edits > d) return false;
        }
    }
    return edits <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladders;
    ladders.push({begin_word});
    set<string> visited = {begin_word};
    while (!ladders.empty()) {
        auto ladder = ladders.front();
        ladders.pop();
        string last_word = ladder.back();
        if (last_word == end_word) return ladder;
        for (const auto& word : word_list) {
            if (visited.find(word) == visited.end() && is_adjacent(last_word, word)) {
                auto new_ladder = ladder;
                new_ladder.push_back(word);
                ladders.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Cannot open file: " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    for (const auto& word : ladder) {
        cout << word << (word == ladder.back() ? "\n" : " -> ");
    }
}

void verify_word_ladder() {
    // Implement verification logic if needed
}