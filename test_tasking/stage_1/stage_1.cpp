#include <iostream>
#include <vector>
#include <unordered_map>


int findContainer(const std::vector<std::vector<std::string>>& containers, const std::string& target) {
    std::unordered_map<std::string, int> containerMap;  // Хранит соответствие строка - контейнер

    // Заполняем хэш-таблицу для к контейнеру по строке
    for (int i = 0; i < containers.size(); i++) {
        const std::vector<std::string>& container = containers[i];
        for (const std::string& str : container) {
            containerMap[str] = i;
        }
    }

    if (containerMap.find(target) != containerMap.end()) {
        return containerMap[target];
    } else {
        return -1;
    }
}

int main() {
    std::vector<std::vector<std::string>> containers = {
            {"строка1", "строка2", "строка3"},
            {"строка4", "строка5"},
            {"строка6", "строка7", "строка8"},
            {"строка9"}
    };

    std::cout << "Начальное наполнение контейнеров:\n";
    for (int i = 0; i < containers.size(); i++) {
        std::cout << "Контейнер " << i << ": ";
        for (const std::string& str : containers[i]) {
            std::cout << str << ' ';
        }
        std::cout << '\n';
    }

    std::string searchString;
    std::cout << "\nВведите строку для поиска: ";
    std::getline(std::cin, searchString);

    int containerIndex = findContainer(containers, searchString);

    if (containerIndex != -1) {
        std::cout << "Строка найдена в контейнере " << containerIndex << '\n';
    } else {
        std::cout << "Строка не найдена в контейнерах" << '\n';
    }

    return 0;
}
