/***************************************************************************
                          commandnewshape.h  -  description
                             -------------------
    begin                : Thu Apr 11 2002
    copyright            : (C) 2002 by Henrik Enqvist IB
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

#ifndef COMMANDNEWSHAPE_H
#define COMMANDNEWSHAPE_H

#include "command.h"

class Shape3D;

/** @author Henrik Enqvist IB */
class CommandNewShape : public Command  {
 public:
	CommandNewShape(PinEditDoc * doc);
	~CommandNewShape();
	Command * build();
	void undo();
	void clearObjects();
	void execute(const CommandContext & context);
	void preview (const CommandContext &, View2D *) {};
	const char * type() { return "CommandNewShape"; };
 private:
	Shape3D * p_Shape;
};

#endif
