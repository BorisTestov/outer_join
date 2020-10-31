#pragma once

#include "result.h"
#include "table.h"

#include <memory>
#include <string>
#include <unordered_map>

class Controller
{
    using tablePtr = std::shared_ptr<Table>;
    using resultType = std::vector<Table::dataType>;

public:
    Controller() = default;
    ~Controller() = default;

    /**
     * @brief Создать новую таблицу
     * @param name - имя таблицы
     * @return код результата выполнения
     */
    Result createTable(std::string name);

    /**
     * @brief Получить ссылку на таблицу по ее имени
     * @param name - имя таблицы
     * @return ссылка на таблицу
     */
    tablePtr getTable(std::string name);

protected:
    /**
     * @brief Вставить значение в таблицу
     * @param name - имя таблицы, в которую будет производиться вставка
     * @param id - id элемента
     * @param value - значение
     * @return код результата выполнения
     */
    Result insert(std::string name, int id, std::string value);

    /**
     * @brief Усечь таблицу
     * @param name - имя таблицы
     * @return код результата выполнения
     */
    Result truncate(std::string name);

private:
    std::unordered_map<std::string, tablePtr> _tables;
};