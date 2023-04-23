#include "search.h"
#include <algorithm>
#include <cmath>
#include <tuple>
#include <cctype>

std::vector<std::string_view> SearchEngine::MakeList(std::string_view text) const {
    std::vector<std::string_view> res;
    size_t beg = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        if (!std::isalpha(text[i])) {
            std::string_view word = text.substr(beg, i - beg);
            if (!word.empty()) {
                res.push_back(word);
            }
            beg = i + 1;
        }
    }
    std::string_view word = text.substr(beg, beg - text.size());
    if (!word.empty()) {
        res.push_back(word);
    }
    return res;
}

std::vector<std::string_view> SearchEngine::MakeListForQuery(std::string_view text) const {
    std::vector<std::string_view> res;
    size_t beg = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        if (!std::isalpha(text[i])) {
            std::string_view word = text.substr(beg, i - beg);
            if (!word.empty() && std::find(res.begin(), res.end(), word) == res.end()) {
                res.push_back(word);
            }
            beg = i + 1;
        }
    }
    std::string_view word = text.substr(beg, beg - text.size());
    if (!word.empty()) {
        res.push_back(word);
    }
    return res;
}

std::vector<std::string_view> SearchEngine::MakeLineList(std::string_view text) {
    std::vector<std::string_view> res;
    bool was_word = true;
    size_t beg = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        if (std::isalpha(text[i])) {
            was_word = true;
        } else if (text[i] == '\n') {
            std::string_view line = text.substr(beg, i - beg);
            if (!line.empty() && was_word) {
                res.push_back(line);
            }
            beg = i + 1;
            was_word = false;
        }
    }
    std::string_view line = text.substr(beg, text.size() - beg);
    if (!text.empty() && was_word) {
        res.push_back(line);
    }
    return res;
}

bool SearchEngine::SortByValues(const std::pair<std::string_view, double>& a,
                                const std::pair<std::string_view, double>& b) {
    return a.second > b.second;
}

bool SearchEngine::IsEqual(std::string_view a, std::string_view b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (std::tolower(a[i]) != std::tolower(b[i])) {
            return false;
        }
    }
    return true;
}

void SearchEngine::BuildIndex(std::string_view text) {
    str_count_by_str_.clear();
    request_count_by_text_.clear();
    count_word_of_str_.clear();
    lines_.clear();
    size_of_text_ = 0;
    for (std::string_view str : MakeLineList(text)) {
        lines_.push_back(str);
        ++size_of_text_;
        for (std::string_view request : MakeListForQuery(str)) {
            ++count_word_of_str_[str];
            double count_by_str = 0;
            for (std::string_view word : MakeList(str)) {
                if (IsEqual(request, word)) {
                    ++count_by_str;
                }
            }
            str_count_by_str_[str][request] = count_by_str;
            if (count_by_str != 0) {
                request_count_by_text_[request] = request_count_by_text_[request] + 1;
            }
        }
    }
}

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    double x = 1;
    std::vector<std::pair<std::string_view, double>> ans = {};
    for (std::string_view str : lines_) {
        double count = 0;
        for (std::string_view request : MakeListForQuery(query)) {
            if (count_word_of_str_[str] == 0 || request_count_by_text_[request] == 0 || size_of_text_ == 0) {
                continue;
            }
            count += ((str_count_by_str_[str][request]) / (count_word_of_str_[str])) *
                     log(x / (request_count_by_text_[request] / size_of_text_));
        }
        if (count != 0) {
            ans.push_back(make_pair(str, count));
        }
    }
    std::stable_sort(ans.begin(), ans.end(), &SearchEngine::SortByValues);
    std::vector<std::string_view> res;
    size_t i = 0;
    for (auto& item : ans) {
        if (item.second <= 0 || i >= results_count) {
            break;
        }
        res.push_back(item.first);
        ++i;
    }
    return res;
}