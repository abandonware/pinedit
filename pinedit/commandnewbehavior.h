/***************************************************************************
                          commandnewbehavior.h  -  description
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

#ifndef COMMANDNEWBEHAVIOR_H
#define COMMANDNEWBEHAVIOR_H

#include <command.h>

class Group;
class Behavior;

/** @author Henrik Enqvist */
class CommandNewBehavior : public Command  {
 public:
	CommandNewBehavior(PinEditDoc * doc);
	~CommandNewBehavior();
	Command * build();
	void clearObjects();
	inline void setBehaviorType(int t) { m_iBehaviorType = t; };
	/** Gets the behavior, the command must be executed before a behavior will exist. */
	inline Behavior * getBehavior() { return p_Behavior; };
	void undo();
	void execute(const CommandContext & context);
	void preview (const CommandContext &, View2D *) {};
	const char * type() { return "CommandNewBehavior"; };
 private:
	Group * p_Group;
	Behavior * p_Behavior;
	int m_iBehaviorType;
};

#endif
