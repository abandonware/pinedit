/***************************************************************************
                          commandsnap.h  -  description
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

#ifndef COMMANDSNAP_H
#define COMMANDSNAP_H

using namespace std;

#include <vector>

#include "command.h"

#include "EMath.h"

/** @author Henrik Enqvist */
class CommandSnap : public Command  {
 public:
	CommandSnap(PinEditDoc * doc);
	~CommandSnap();
	Command * build();
	void undo();
	void clearObjects();
	void execute(const CommandContext & context);
    void setFactor(float factor) { m_fFactor = factor; }
    void preview(const CommandContext &, View2D *, QPainter&) {}
    void setX(bool x) { m_bX = x; }
    void setY(bool y) { m_bY = y; }
    void setZ(bool z) { m_bZ = z; }
    const char * type() { return "CommandSnap"; }
 private:
	vector<Vertex3D> m_vVertex;
	vector<int> m_vIndex;
	float m_fFactor;
	bool m_bX;
	bool m_bY;
	bool m_bZ;
};

#endif
