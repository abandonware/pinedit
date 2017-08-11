/***************************************************************************
                          command.h  -  description
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

#ifndef COMMAND_H
#define COMMAND_H

#define XY       0x1
#define XZ       0x2
#define ZY       0x3

#define PE_ROTATION_FACTOR 100
#define PE_RESIZE_FACTOR 50

#include <cstdlib>

class View2D;
class PinEditDoc;
class Group;
class Shape3D;
class QPainter;

/** @author Henrik Enqvist */
class CommandContext {
 public:
	CommandContext() {};
	~CommandContext() {};
	void clear() { 
		x1 = x2 = y1 = y2 = z1 = z2 = 0; 
		sx1 = sy1 = sx2 = sy2 = 0;
		type = 0; 
		group = NULL; 
		shape = NULL;
	};
	void copy(const CommandContext & cc) {
		x1 = cc.x1;
		x2 = cc.x2;
		y1 = cc.y1;
		y2 = cc.y2;
		z1 = cc.z1;
		z2 = cc.y2;
		type = cc.type;
		group = cc.group;
		shape = cc.shape;
	};
	float x1, x2;
	float y1, y2;
	float z1, z2;
	int sx1, sy1;
	int sx2, sy2;
	int type;
	Group * group;
	Shape3D * shape;
};

/** Commands are the operation that we can perform on the object(s) that 
 * we are editing. E.g. adding vertices, moving group, deleting behaviors etc. */
class Command {
 public:
	/** Constucts a command that can be executed and undon. */
	Command(PinEditDoc * doc);
	virtual ~Command();
	/** Some classes manages an 'current command' object. This class is used
	 * when we want to construct a command of the same (unknown) type. 
	 * Subclasses should implement this function by only only creating a
	 * new object and returning it. */
	virtual Command * build() = 0;
	/** Reverses the action of the command. The command must first be executed. */
	virtual void undo() = 0;
	/** Performs the action implemented by this action on a given context. 
	 * The context can be used to pass 'arguments' to the command. */
	virtual void execute(const CommandContext & context) = 0;
	/** Some commands wishes to  generate a preview of the action onto a View2D. E.g.
	 * movement of objects. */
    virtual void preview(const CommandContext & context, View2D * view2d, QPainter& painter) = 0;
	/** Returns the name of the command subclass. Subclasses should implement
	 * this function by returning a name that exaclty matches the name of 
	 * the class. */
	virtual const char * type() = 0;
	/** Clears any temporary objects needed by the undo operation. This function
	 * is called when the command is pushed out from the undo stack. This function
	 * is NOT called if command is undon. */
	virtual void clearObjects() = 0;
 protected:
	PinEditDoc * p_Doc;
	CommandContext * p_Context;
};
#endif
