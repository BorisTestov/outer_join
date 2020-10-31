#pragma once

#include "controller.h"
#include "result.h"

#include <sstream>
#include <string>
class Command
{
public:
    Command() = delete;
    Command(std::string name);
    Command(const Command& other);
    Command(Command&& other);
    virtual ~Command() = default;

    Result exec(std::shared_ptr<Controller> controller, std::stringstream& args);
    std::string usage();
    std::string getName();

protected:
    virtual Result execute(std::shared_ptr<Controller> controller, std::stringstream& args) = 0;
    virtual std::string getUsage() = 0;

private:
    std::string _name;
};