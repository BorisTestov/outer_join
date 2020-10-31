#pragma once

#include "result.h"

#include <algorithm>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

class Table
{
public:
    struct dataType
    {
        dataType(int newId, std::string newName) :
            id(newId), name(newName) {};
        int id;
        std::string name;
    };

    Table() = default;
    virtual ~Table() = default;

    /**
     * @brief Добавить запись в таблицу
     * @return Результат выполнения операции
     */
    Result addValue(int id, std::string name);

    /**
     * @brief Очистить таблицу
     * @return Результат выполнения операции
     */
    Result truncate();

    /**
     * @brief Выполнить операцию пересечения таблиц
     * @return Результат выполнения операции
     */
    Result intersection(std::shared_ptr<Table> other);

    /**
     * @brief Выполнить симметрическую разность между таблицами
     * @return Результат выполнения операции
     */
    Result symmetricDifference(std::shared_ptr<Table> other);

protected:
    /**
     * @brief Вернуть индекс записи с заданным id
     * @param id - id записи
     * @return - индекс
     */
    int getIndex(int id);

private:
    std::vector<dataType> _rows;
    std::map<int, int> _indexMap;
    std::mutex _mutexTransaction;
};