#pragma once

#include <string_view>
#include <vector>
#include <unordered_map>

class SearchEngine {

public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;

private:
    mutable std::unordered_map<std::string_view, std::unordered_map<std::string_view, double>> str_count_by_str_;
    mutable std::unordered_map<std::string_view, double> request_count_by_text_;
    mutable std::unordered_map<std::string_view, double> count_word_of_str_;
    std::vector<std::string_view> lines_;
    double size_of_text_ = 0;
    bool IsEqual(std::string_view a, std::string_view b);
    static bool SortByValues(const std::pair<std::string_view, double>& a,
                             const std::pair<std::string_view, double>& b);
    std::vector<std::string_view> MakeListForQuery(std::string_view text) const;
    std::vector<std::string_view> MakeLineList(std::string_view text);
    std::vector<std::string_view> MakeList(std::string_view text) const;
};