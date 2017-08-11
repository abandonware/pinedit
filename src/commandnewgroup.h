/***************************************************************************
                          commandnewgroup.h  -  description
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

#ifndef COMMANDNEWGROUP_H
#define COMMANDNEWGROUP_H

#include <command.h>

class Group;

/** @author Henrik Enqvist */
class CommandNewGroup : public Command  {
 public:
	CommandNewGroup(PinEditDoc * doc);
	~CommandNewGroup();
	Command * build();
	void undo();
	void clearObjects();
	void execute(const CommandContext & context);
    const char * type() { return "CommandNewGroup"; }
    void preview (const CommandContext &, View2D *, QPainter&) {}
 private:
	Group * p_Group;
};

#endif
