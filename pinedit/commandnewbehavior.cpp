/***************************************************************************
                          commandnewbehavior.cpp  -  description
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

// application includes
#include "pineditdoc.h"
#include "commandnewbehavior.h"
// emilia includes
#include "Private.h"
#include "Group.h"
#include "Engine.h"
#include "BumperBehavior.h"
#include "StateBehavior.h"
#include "ArmBehavior.h"
#include "FakeModuleBehavior.h"
#include "Pinball.h"

CommandNewBehavior::CommandNewBehavior(PinEditDoc * doc) : Command(doc) {
  p_Behavior = NULL;
  p_OldBehavior = NULL;
  p_OldLightGroup = NULL;
  m_iBehaviorType = 0;
}

CommandNewBehavior::~CommandNewBehavior() {
}

void CommandNewBehavior::clearObjects() {
  EM_CERR("CommandNewBehavior::clearObjects TODO");
  // should delete undo behavior
}

void CommandNewBehavior::execute(const CommandContext & context) {
  EM_CERR("CommandNewBehavior::execute");
  assert(context.group != NULL);

  switch (m_iBehaviorType) {
  case PBL_TYPE_BUMPERBEH:
    p_Behavior = new BumperBehavior();
    break;
  case PBL_TYPE_ARMBEH:
    p_Behavior = new ArmBehavior(true);
    break;
  case PBL_TYPE_STATEBEH:
    p_Behavior = new StateBehavior();
    break;
  case PBL_TYPE_FAKEMODULEBEH:
    p_Behavior = new FakeModuleBehavior("");
    break;
  default:
    p_Behavior = NULL;
  }

  // save old 
  p_OldBehavior = context.group->getBehavior();
  if (p_OldBehavior != NULL) {
    Light * light = p_OldBehavior->getLight();
    if (light != NULL) {
      p_OldLightGroup = light->getParent();
      assert(p_OldLightGroup != NULL);
      Group * parent = p_OldLightGroup->getParent();
      assert(parent != NULL);
      assert(parent == context.group);
      parent->removeGroup(p_OldLightGroup);
    }
  }

  context.group->setBehavior(p_Behavior);

  p_Doc->setModified(true);
  p_Doc->rebuildAll("group");
  //p_Doc->updateAll();
  p_Doc->pushUndo(this);
  //p_Context = new CommandContext(context);
  EM_CERR("CommandNewBehavior::execute done");
}

void CommandNewBehavior::undo() {
  EM_CERR("CommandNewBehavior::undo TODO");
}

Command * CommandNewBehavior::build() {
  return new CommandNewBehavior(p_Doc);
}

