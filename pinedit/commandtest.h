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

#ifndef COMMANDTEST_H
#define COMMANDTEST_H

#if EM_UNIT_TEST

#include <fstream>
#include <sstream>
#include <string>

#include "commandnewvertex.h"

#include <cppunit/TestFixture.h>
#include <cppunit/Test.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/extensions/HelperMacros.h>

class NewVertexTest : public CppUnit::TestFixture {
 public:
  void setUp() {
  }

  void tearDown() {
  }

  void testNewVertex() {
		CPPUNIT_ASSERT(true);
  }

	CPPUNIT_TEST_SUITE(NewVertexTest);

	CPPUNIT_TEST(testNewVertex);
	
	CPPUNIT_TEST_SUITE_END();
};

#endif // EM_UNIT_TEST

#endif // COMMANDTEST_H

