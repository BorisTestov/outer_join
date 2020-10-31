#include "table.h"

#include "result.h"

Result Table::addValue(int id, std::string name)
{
    std::lock_guard<std::mutex> lock(_mutexTransaction);

    if (_indexMap.count(id) != 0)
    {
        Result result = Result(Result::ResultCode::DUPLICATE_KEY, { std::to_string(id) });
        return result;
    }
    _rows.push_back(dataType(id, name));
    _indexMap[id] = _rows.size() - 1;
    return Result::ResultCode::OK;
}

Result Table::truncate()
{
    _rows.clear();
    _indexMap.clear();
    return Result::ResultCode::OK;
}

Result Table::intersection(std::shared_ptr<Table> other)
{
    std::lock_guard<std::mutex> lock(_mutexTransaction);
    std::lock_guard<std::mutex> lockOther(other->_mutexTransaction);

    std::vector<std::string> resultData;
    for (auto index : _indexMap)
    {
        int id = (index.first);

        int otherIndex = (other->getIndex(id));
        if (otherIndex != -1)
        {
            resultData.push_back(std::to_string(id) + "," + _rows.at(index.second).name + "," + other->_rows.at(otherIndex).name);
        }
    }
    return Result(Result::ResultCode::OK, resultData);
}

Result Table::symmetricDifference(std::shared_ptr<Table> other)
{
    std::lock_guard<std::mutex> lock(_mutexTransaction);
    std::lock_guard<std::mutex> lockOther(other->_mutexTransaction);

    std::vector<std::string> resultData;

    auto iterLeft(_indexMap.cbegin());
    auto leftEnd(_indexMap.cend());
    auto iterRight(other->_indexMap.cbegin());
    auto rightEnd(other->_indexMap.cend());

    while ((iterLeft != leftEnd) && (iterRight != rightEnd))
    {
        if (iterLeft->first == iterRight->first)
        {
            ++iterLeft;
            ++iterRight;
        }
        else if (iterLeft->first < iterRight->first)
        {
            resultData.push_back(std::to_string(iterLeft->first) + "," + _rows.at(iterLeft->second).name + ",");
            ++iterLeft;
        }
        else
        {
            resultData.push_back(std::to_string(iterRight->first) + ",," + other->_rows.at(iterRight->second).name);
            ++iterRight;
        }
    }

    if (iterLeft != leftEnd)
    {
        std::for_each(iterLeft, leftEnd, [&resultData, this](auto index) {
            resultData.push_back(std::to_string(index.first) + "," + _rows.at(index.second).name + ",");
        });
    }
    else
    {
        std::for_each(iterRight, rightEnd, [&resultData, other](auto index) {
            resultData.push_back(std::to_string(index.first) + ",," + other->_rows.at(index.second).name);
        });
    }
    return Result(Result::ResultCode::OK, resultData);
}

int Table::getIndex(int id)
{
    if (_indexMap.count(id) == 0)
    {
        return -1;
    }
    return (_indexMap.at(id));
}
