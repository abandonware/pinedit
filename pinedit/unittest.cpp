/***************************************************************************
 Unit test runner
 ***************************************************************************/

#if EM_UNIT_TEST
#include <cppunit/ui/text/TestRunner.h>
#include "Private.h"
#include "SrcTest.h"
#include "BaseTest.h"
#endif

/** Main */
int main(int argc, char *argv[]) {
#if EM_UNIT_TEST
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(CommandTest::suite());
  runner.run();
#endif
	return 0;
}
