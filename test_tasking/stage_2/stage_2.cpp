//Вместо хранения номера контейнера в unordered_map, мы будем хранить указатель на контейнер, чтобы учесть новое ограничение

#include <iostream>
#include <vector>
#include <unordered_map>

int findContainer(const std::vector<std::vector<std::string>>& containers, const std::string& target) {
    std::unordered_map<std::string, const std::vector<std::string>*> containerMap;  // Хранит соответствие строка -> контейнер

    // Заполняем хэш-таблицу для доступа к контейнеру по строке
    for (const std::vector<std::string>& container : containers) {
        for (const std::string& str : container) {
            containerMap[str] = &container;
        }
    }

    if (containerMap.find(target) != containerMap.end()) {
        const std::vector<std::string>* container = containerMap[target];
        int containerIndex = std::distance(&containers[0], container);
        return containerIndex;
    } else {
        return -1;
    }
}

int main() {
    std::vector<std::vector<std::string>> containers = {
            {"строка3", "строка1", "строка2"},
            {"строка4", "строка5"},
            {"строка8", "строка7", "строка6"},
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

