/***************************************************************************
                          commandhideselected.h  -  description
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

#ifndef COMMANDHIDESELECTED_H
#define COMMANDHIDESELECTED_H

#include <command.h>

/** @author Henrik Enqvist IB */
class CommandHideSelected : public Command  {
 public:
	CommandHideSelected(PinEditDoc * doc);
	~CommandHideSelected();
	Command * build();
	void undo();
	void execute(const CommandContext & context);
	void preview(const CommandContext & context, View2D * view2d);
	const char * type() { return "CommandHideSelected"; };
};

#endif
