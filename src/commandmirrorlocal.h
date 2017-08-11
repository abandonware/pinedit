/***************************************************************************
                          commandmirrorlocal.h  -  description
                             -------------------
    begin                : Fri Apr 12 2002
    copyright            : (C) 2002 by Henrik Enqvist
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

#ifndef COMMANDMIRRORLOCAL_H
#define COMMANDMIRRORLOCAL_H

using namespace std;

#include <vector>

#include <command.h>

#include "EMath.h"

class Polygon3D;

/** @author Henrik Enqvist */
class CommandMirrorLocal : public Command  {
 public:
  CommandMirrorLocal(PinEditDoc * doc);
  ~CommandMirrorLocal();
  Command * build();
  void undo();
  void clearObjects();
  void execute(const CommandContext & context);
  void preview (const CommandContext &, View2D *, QPainter&) {}
  /** 0 = x, 1 = y, 2 = z; */
  void setXYZ(int xyz) { m_iXYZ = xyz; }
  const char * type() { return "CommandMirrorLocal"; }
 private:
  int m_iXYZ;
  Vertex3D m_vtxCenter;
  vector<int> m_vIndex;
  vector<Polygon3D*> m_vPolygon;
};

#endif
