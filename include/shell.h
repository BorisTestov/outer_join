#pragma once

#include "command.h"
#include "command_create.h"
#include "command_difference.h"
#include "command_insert.h"
#include "command_intersection.h"
#include "command_truncate.h"
#include "controller.h"

#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>

class Shell
{
public:
    Shell() = delete;
    Shell(std::shared_ptr<Controller> controller);
    ~Shell();

    std::string execute(std::string strCommand);

protected:
private:
    std::mutex _mutexTransaction;
    std::shared_ptr<Controller> _controller;
    std::unordered_map<std::string, std::shared_ptr<Command>> _commands;
};

using shellPtr = std::shared_ptr<Shell>;