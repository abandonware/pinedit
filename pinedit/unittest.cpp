/***************************************************************************
 Unit test runner
 ***************************************************************************/

#include "editconfig.h"

#if EM_UNIT_TEST
#include <cppunit/ui/text/TestRunner.h>
#include "testcommand.h"
#include "testpineditdoc.h"
#endif

/** Main */
int main(int argc, char *argv[]) {
#if EM_UNIT_TEST
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(TestPinEditDoc::suite());
  runner.addTest(TestCommand::suite());
  runner.run();
#endif
	return 0;
}
