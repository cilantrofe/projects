#pragma once

#include <string>
#include <string_view>
#include <vector>

class UnixPath {

public:
    explicit UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;

private:
    std::string_view current_dir_for_absolute_;
    std::string_view current_dir_for_relative_;
    std::string absolute_path_;
    std::string relative_path_;
    std::string Join(const std::vector<std::string>& elems, char delimiter);
    void MakeStack(std::vector<std::string>& pas_as_stack, std::string_view path);
    std::string NormalizePath(std::string_view current_working_dir, std::string_view path);
    std::string RelativizePath(std::string_view current_working_dir, std::string_view path);
};
