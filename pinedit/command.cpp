/***************************************************************************
                          command.cpp  -  description
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

// general includes
#include <cassert>
// application includes
#include "pineditdoc.h"
#include "command.h"

Command::Command(PinEditDoc * doc){
	assert(doc != NULL);
	p_Doc = doc;
	p_Context = new CommandContext();
	p_Context->clear();

}

Command::~Command(){
	delete p_Context;
}
