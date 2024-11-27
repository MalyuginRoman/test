#include <iostream>
#include "math.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include "CommandQueue.h"
#include "CommandMove.h"
#include "CommandRotate.h"
#include "CommandLoger.h"
#include "CommandRepeat.h"
#include "ExceptionHandler.h"

class test_exception : public CPPUNIT_NS::TestCase
{
CPPUNIT_TEST_SUITE(test_exception);
  CPPUNIT_TEST(test1);
CPPUNIT_TEST_SUITE_END();

public:
void setUp(void) {}
void tearDown(void){}

protected:
// Реализовать Команду, которая записывает информацию о выброшенном исключении в лог.
  void test1(void)
{
    CommandQueue cmd;
    CommandMove *cmd_move = new CommandMove;
    CommandRotate *cmd_rotate = new CommandRotate;
    CommandLoger *cmd_loger = new CommandLoger;
    std::exception ex;
    ExceptionHandler* handler = new ExceptionHandler(0, ex);

    cmd.add(cmd_move);
    cmd.add(cmd_rotate);

    while(!cmd.isEmpty())
    {
        try {
            cmd.front()->execute();
        } catch( std::exception ex) {
            cmd_loger->execute(cmd.front()->setStr());
        }
        cmd.del();
    }
    std::cout << std::endl;
  //CPPUNIT_ASSERT(0 < 1);
}
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_exception);

int main()
{
CPPUNIT_NS::TestResult controller;

CPPUNIT_NS::TestResultCollector result;
controller.addListener(&result);

CPPUNIT_NS::BriefTestProgressListener progress;
controller.addListener(&progress);

CPPUNIT_NS::TestRunner runner;
runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
runner.run(controller);

return result.wasSuccessful() ? 0 : 1;
}
