#include "result.h"

#include <algorithm>
#include <string>
#include <vector>

Result::Result(Result::ResultCode code) :
    _code(code), _data()
{
}

Result::Result(Result::ResultCode code, std::vector<std::string> data) :
    _code(code), _data(data)
{
}

/**
 * @brief - Возвращает строку с результатом выполнения
 * @return - Строка с результатом выполнения
 */
std::string Result::toString() const
{
    std::string resultString = _err_header;
    switch (_code)
    {
        case (ResultCode::OK):
        {
            resultString = "";
            if (not _data.empty())
            {
                std::for_each(_data.begin(),
                              _data.end(),
                              [&resultString](std::string line) {
                                  resultString += line;
                                  resultString += "\n";
                              });
            }
            resultString += "OK";
            break;
        }
        case (ResultCode::WRONG_ARGUMENT):
        {
            resultString += "Wrong arguments";
            break;
        }
        case (ResultCode::TABLE_ALREADY_EXISTS):
        {
            resultString += "Table already exists";
            break;
        }
        case (ResultCode::UNKNOWN_TABLE):
        {
            resultString += "Unknown table";
            break;
        }
        case (ResultCode::DUPLICATE_KEY):
        {
            resultString += "Duplicate key";
            break;
        }
        default:
            resultString += "Unknown Error ";
    }
    return resultString;
}
