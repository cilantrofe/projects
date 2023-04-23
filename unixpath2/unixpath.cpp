#include "unixpath.h"

UnixPath::UnixPath(std::string_view initial_dir) {
    current_dir_for_relative_ = initial_dir;
    current_dir_for_absolute_ = initial_dir;
}

void UnixPath::ChangeDirectory(std::string_view path) {
    absolute_path_ = NormalizePath(current_dir_for_absolute_, path);
    relative_path_ = RelativizePath(current_dir_for_relative_, path);
    current_dir_for_absolute_ = std::string_view{absolute_path_};
}

std::string UnixPath::GetAbsolutePath() const {
    return absolute_path_;
}

std::string UnixPath::GetRelativePath() const {
    return relative_path_;
}

std::string UnixPath::Join(const std::vector<std::string>& elems, char delimiter) {
    std::string s;
    for (int i = 0; i < static_cast<int>(elems.size()); ++i) {
        if (i > 0) {
            s += delimiter;
        }
        s += elems[i];
    }
    s = '/' + s;
    return s;
}

void UnixPath::MakeStack(std::vector<std::string>& pas_as_stack, std::string_view path) {
    std::string current_dir;
    for (char c : path) {
        if (c == '/') {
            if (!current_dir.empty() && current_dir == "..") {
                if (!pas_as_stack.empty()) {
                    pas_as_stack.pop_back();
                }
            } else if (!current_dir.empty() && current_dir != ".") {
                pas_as_stack.push_back(current_dir);
            }
            current_dir = "";
        } else {
            current_dir += c;
        }
    }
    if (current_dir == "..") {
        if (!pas_as_stack.empty()) {
            pas_as_stack.pop_back();
        }
    } else if (current_dir != "." && !current_dir.empty()) {
        pas_as_stack.push_back(current_dir);
    }
}

std::string UnixPath::NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::vector<std::string> current_as_stack;
    if (path[0] == '/') {
        MakeStack(current_as_stack, path);
        return Join(current_as_stack, '/');
    }
    MakeStack(current_as_stack, current_working_dir);
    MakeStack(current_as_stack, path);
    return Join(current_as_stack, '/');
}

std::string UnixPath::RelativizePath(std::string_view current_working_dir, std::string_view path) {
    size_t i = 0;
    std::vector<std::string> current_as_stack;
    MakeStack(current_as_stack, current_working_dir);
    std::vector<std::string> path_as_stack;
    if (path[0] == '/') {
        MakeStack(path_as_stack, path);
    } else {
        MakeStack(path_as_stack, current_working_dir);
        MakeStack(path_as_stack, path);
    }
    int index = -1;
    while (i < current_as_stack.size() && i < path_as_stack.size()) {
        if (current_as_stack[i] != path_as_stack[i]) {
            index = static_cast<int>(i);
            break;
        }
        ++i;
    }
    if (path_as_stack == current_as_stack) {
        return ".";
    } else if (path_as_stack.size() > current_as_stack.size()) {
        std::string s;
        for (size_t j = 0; j < path_as_stack.size() - current_as_stack.size(); ++j) {
            s += "./";
        }
        return s + path_as_stack.back();
    } else if (index != -1) {
        std::string s;
        for (size_t j = 0; j < current_as_stack.size() - index; ++j) {
            s += "../";
        }
        for (size_t j = index; j < path_as_stack.size(); ++j) {
            s += path_as_stack[j] + "/";
        }
        return s.substr(0, s.size() - 1);
    }
    return ".";
}