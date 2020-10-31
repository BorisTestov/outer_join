#pragma once

#include <string>
#include <vector>

class Result
{
public:
    enum class ResultCode
    {
        OK,
        WRONG_ARGUMENT,
        UNKNOWN_TABLE,
        DUPLICATE_KEY,
        TABLE_ALREADY_EXISTS
    };

    Result() = delete;
    Result(ResultCode code);
    Result(ResultCode code, std::vector<std::string> data);

    ~Result() = default;

    std::string toString() const;

private:
    ResultCode _code;
    std::vector<std::string> _data;
    const std::string _err_header = "ERR ";
};