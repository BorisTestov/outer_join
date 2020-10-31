#include "controller.h"
#include "server.h"
#include "session.h"
#include "shell.h"
#include "version.h"

#include <boost/asio.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <vector>

TEST(commands, ok)
{
    testing::internal::CaptureStdout();

    std::shared_ptr<Controller> controller = std::make_shared<Controller>();
    shellPtr shell = std::make_shared<Shell>(controller);

    std::stringstream init;
    init << "create A" << std::endl;
    init << "create B" << std::endl;
    init << "insert A 0 lean" << std::endl;
    init << "insert A 1 sweater" << std::endl;
    init << "insert A 2 frank" << std::endl;
    init << "insert A 3 violation" << std::endl;
    init << "insert A 4 quality" << std::endl;
    init << "insert A 5 precision" << std::endl;
    init << "insert B 3 proposal" << std::endl;
    init << "insert B 4 example" << std::endl;
    init << "insert B 5 lake" << std::endl;
    init << "insert B 6 flour" << std::endl;
    init << "insert B 7 wonder" << std::endl;
    init << "insert B 8 selection" << std::endl;
    init << "intersection" << std::endl;
    init << "symmetric_difference" << std::endl;
    init << "truncate A" << std::endl;
    init << "truncate B" << std::endl;

    {
        std::string line;
        while (std::getline(init, line))
        {
            std::cout << "line:" << shell->execute(line) << std::endl;
        }
    }
    std::string output = testing::internal::GetCapturedStdout();
    std::string expectedOutput =
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:OK\n"
        "line:3,violation,proposal\n"
        "4,quality,example\n"
        "5,precision,lake\n"
        "OK\n"
        "line:0,lean,\n"
        "1,sweater,\n"
        "2,frank,\n"
        "6,,flour\n"
        "7,,wonder\n"
        "8,,selection\n"
        "OK\n"
        "line:OK\n"
        "line:OK\n";
    ASSERT_EQ(output, expectedOutput);
}