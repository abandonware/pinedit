//Added by qt3to4:
#include <Q3TextStream>
/***************************************************************************
                          fileutil.h  -  description
                             -------------------
    begin                : Tue May 15 19:39:03 EET 2002
    copyright            : (C) 2001 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef FILEUTIL_H
#define FILEUTIL_H

class Engine;
class Group;
class Shape3D;
class Behavior;
class PinEditDoc;
class QString;
class Q3TextStream;

/** A utility that saves the groups, shapes and behaviors in an engine 
 ** to a pinball file. */
class FileUtil {
 public:
  FileUtil(PinEditDoc * doc);
  ~FileUtil() {};
  int saveFile(const QString & fn, Group * group);
 private:
  int writeGroup(Q3TextStream & file, Group * Group);
  int writeShape(Q3TextStream & file, Shape3D * shape);
  int writeBehavior(Q3TextStream & file, Behavior * beh);
  inline void incIndent() {
    ++m_iIndent;
  };
  inline void decIndent() {
    --m_iIndent;
    if (m_iIndent < 0) m_iIndent = 0;
  };
  inline void resetIndent() {
    m_iIndent = 0;
  };
  PinEditDoc * p_Doc;
  int m_iIndent;
};

#endif
