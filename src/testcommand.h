/***************************************************************************
                            SrcTest.h -  description
                             -------------------
    begin                : Sun Aug 25 2002
    copyright            : (C) 2002 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

/****************************************************************************
 * Unit testing
 ***************************************************************************/

#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#if EM_UNIT_TEST

#include <fstream>
#include <sstream>
#include <string>

#include <cppunit/TestFixture.h>
#include <cppunit/Test.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/extensions/HelperMacros.h>

#include "commandnewvertex.h"
#include "commandnewgroup.h"
#include "pinedit.h"

class TestCommand : public CppUnit::TestFixture {
 public:
  void setUp() {
		//		pineditapp = new PinEditApp();
		//		commandnewgroup = new CommandNewGroup(pineditapp->getDoc());
		//		commandnewvertex = new CommandNewVertex(pineditapp->getDoc());
  };

  void tearDown() {
  };

	void testNewGroup() {
	};

	void testNewVertex() {
	};

  void testTrue() {
		CPPUNIT_ASSERT(true);
  };

	CPPUNIT_TEST_SUITE(TestCommand);

	CPPUNIT_TEST(testTrue);
	CPPUNIT_TEST(testNewGroup);
	CPPUNIT_TEST(testNewVertex);
	
	CPPUNIT_TEST_SUITE_END();
 private:
	PinEditApp * pineditapp;
	CommandNewVertex * commandnewvertex;
	CommandNewGroup * commandnewgroup;
};

#endif // EM_UNIT_TEST

#endif // COMMANDTEST_H

