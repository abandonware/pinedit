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

#ifndef TESTPINEDITDOC_H
#define TESTPINEDITDOC_H

#if EM_UNIT_TEST

#include <fstream>
#include <sstream>
#include <string>

#include <cppunit/TestFixture.h>
#include <cppunit/Test.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/extensions/HelperMacros.h>

#include "pineditdoc.h"

class TestPinEditDoc : public CppUnit::TestFixture {
 public:
  void setUp() {
  };

  void tearDown() {
  };

	void testSelect() {
	};

	void testAddSelect() {
	};

	void testUnSelect() {
	};

  void testTrue() {
		CPPUNIT_ASSERT(true);
  };

	CPPUNIT_TEST_SUITE(TestPinEditDoc);

	CPPUNIT_TEST(testTrue);
	CPPUNIT_TEST(testSelect);
	CPPUNIT_TEST(testAddSelect);
	CPPUNIT_TEST(testUnSelect);
	
	CPPUNIT_TEST_SUITE_END();
};

#endif // EM_UNIT_TEST

#endif // COMMANDTEST_H

