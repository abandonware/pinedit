/***************************************************************************
                          commandnewvertex.h  -  description
                             -------------------
    begin                : Thu Apr 11 2002
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

#ifndef COMMANDNEWVERTEX_H
#define COMMANDNEWVERTEX_H

#include "command.h"

/** @author Henrik Enqvist */
class CommandNewVertex : public Command  {
 public:
	CommandNewVertex(PinEditDoc * doc);
	~CommandNewVertex();
	Command * build();
	void undo();
	void clearObjects();
	void execute(const CommandContext & context);
    void preview (const CommandContext &, View2D *, QPainter&) {}
    const char * type() { return "CommandNewVertex"; }
 private:
	int m_iVtxIndex;
};

#endif
