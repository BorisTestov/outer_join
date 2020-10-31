#pragma once

#include "command.h"

class CommandTruncate : public Command
{
public:
    CommandTruncate();
    CommandTruncate(const CommandTruncate& other);
    CommandTruncate(CommandTruncate&& other);
    ~CommandTruncate() = default;

protected:
    virtual Result execute(std::shared_ptr<Controller> controller, std::stringstream& args) override;
    virtual std::string getUsage() override;
};