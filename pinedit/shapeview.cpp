/***************************************************************************
                          shapeview.cpp  -  description
                             -------------------
    begin                : Wed Apr 10 2002
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
// qt includes
#include <qtabwidget.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qwidgetstack.h>
// application includes
#include "statedialog.h"
#include "bumperdialog.h"
#include "lightdialog.h"
#include "armdialog.h"
#include "moduledialog.h"
#include "shapeview.h"
#include "pineditdoc.h"
#include "listitem.h"
#include "commandnewbehavior.h"
#include "pinedit.h"
#include "pineditview.h"
// emilia includes
#include "Private.h"
#include "Engine.h"
#include "Group.h"
#include "Shape3D.h"
#include "Polygon.h"
#include "EMath.h"
#include "CollisionBounds.h"
#include "BumperBehavior.h"
#include "ArmBehavior.h"
#include "StateBehavior.h"
#include "FakeModuleBehavior.h"
#include "Pinball.h"

ShapeView::ShapeView(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) 
  : QVBox(parent, name, f) {
  EM_CERR("shapeview::shapeview");
  assert(doc != NULL);
  p_Doc = doc;
  p_Doc->registerUpdateable(this, "group");
  p_Doc->registerRebuildable(this, "group");

  p_StateDialog = new StateDialog(doc, this, 0, 0);
  p_LightDialog = new LightDialog(doc, this, 0, 0);
  p_BumperDialog = new BumperDialog(doc, this, 0, 0);
  p_ArmDialog = new ArmDialog(doc, this, 0, 0);
  p_ModuleDialog = new ModuleDialog(doc, this, 0, 0);

  p_ListView = new QListView(this);
  connect(p_ListView, SIGNAL(selectionChanged()), this, SLOT(slotChanged()));
  p_ListView->setSelectionMode(QListView::Single);
  p_ListView->addColumn(QString("elements"));

  p_ListView->setMinimumSize(200, 250);
		
  // widget stack
  p_WidgetStack = new QWidgetStack(this);

  // group widget
  {
    p_WidgetGroup = new QWidget(p_WidgetStack);
    p_WidgetStack->addWidget(p_WidgetGroup, 0);
    p_LineEditName = new QLineEdit(p_WidgetGroup);
    p_BoxCollision = new QCheckBox("collision (1st shape)", p_WidgetGroup);
    p_BoxTransformOnce = new QCheckBox("transform once", p_WidgetGroup);
    p_BoxWall = new QCheckBox("wall", p_WidgetGroup);
    p_BoxOneWay = new QCheckBox("one way", p_WidgetGroup);
    QPushButton * applybutton = new QPushButton("apply", p_WidgetGroup);
    connect(applybutton, SIGNAL(clicked()), this, SLOT(slotApplyProp()));
    // behavior choice
    p_ChoiceBehavior = new QComboBox(p_WidgetGroup);
    p_ChoiceBehavior->insertItem("none");
    p_ChoiceBehavior->insertItem("bumper beh");
    p_ChoiceBehavior->insertItem("left arm beh");
    p_ChoiceBehavior->insertItem("right arm beh");
    p_ChoiceBehavior->insertItem("module");
    p_ChoiceBehavior->insertItem("statemachine");
    QPushButton * addbutton = new QPushButton("new behavior", p_WidgetGroup);
    connect(addbutton, SIGNAL(clicked()), this, SLOT(slotAdd()));
    // layout
    QBoxLayout * vlayout1 = new QVBoxLayout(p_WidgetGroup);
    vlayout1->addWidget(p_LineEditName);
    vlayout1->addWidget(p_BoxCollision);
    vlayout1->addWidget(p_BoxTransformOnce);
    vlayout1->addWidget(p_BoxWall);
    vlayout1->addWidget(p_BoxOneWay);
    vlayout1->addWidget(applybutton);
    QBoxLayout * hlayout1 = new QHBoxLayout(vlayout1);
    hlayout1->addWidget(p_ChoiceBehavior);
    hlayout1->addWidget(addbutton);
    p_WidgetGroup->adjustSize();
  }
  // shape widget
  {
    p_WidgetShape = new QWidget(p_WidgetStack);
    p_WidgetStack->addWidget(p_WidgetShape, 1);
    //p_LineEditName = new QLineEdit(p_WidgetShape);
    p_BoxHidden = new QCheckBox("hidden", p_WidgetShape);
    p_BoxBehind = new QCheckBox("behind", p_WidgetShape);
    p_BoxBehind2 = new QCheckBox("behind2", p_WidgetShape);
    p_BoxAllwaysLit = new QCheckBox("allways lit", p_WidgetShape);
    QPushButton * button = new QPushButton("apply", p_WidgetShape);
    connect(button, SIGNAL(clicked()), this, SLOT(slotApplyProp()));
    // layout
    QBoxLayout * vlayout1 = new QVBoxLayout(p_WidgetShape);
    vlayout1->addWidget(p_BoxHidden);
    vlayout1->addWidget(p_BoxBehind);
    vlayout1->addWidget(p_BoxBehind2);
    vlayout1->addWidget(p_BoxAllwaysLit);
    vlayout1->addWidget(button);
    p_WidgetShape->adjustSize();
  }
  // behavior widget
  {
    p_WidgetBehavior = new QWidget(p_WidgetStack);
    p_WidgetStack->addWidget(p_WidgetBehavior, 2);
    QPushButton * editbutton = new QPushButton("edit behavior", p_WidgetBehavior);
    connect(editbutton, SIGNAL(clicked()), this, SLOT(slotEdit()));
    QPushButton * lightbutton = new QPushButton("edit light", p_WidgetBehavior);
    connect(lightbutton, SIGNAL(clicked()), this, SLOT(slotLight()));
    // layout
    QBoxLayout * vlayout1 = new QVBoxLayout(p_WidgetBehavior);
    vlayout1->addWidget(editbutton);
    vlayout1->addWidget(lightbutton);
    p_WidgetBehavior->adjustSize();
  }
  p_WidgetStack->raiseWidget(p_WidgetGroup);
  this->adjustSize();

  this->doRebuild();
  this->doUpdate();
}

ShapeView::~ShapeView(){
}

void ShapeView::doRebuild() {
  EM_CERR("ShapeView::doRebuild");
  assert(p_Doc->getEngine() != NULL);
  p_ListView->clear();
  ListItem * firstitem = new ListItem(p_ListView, "bottom");
  // insert all children
  //this->addGroup(p_Doc->getEngine(), firstitem);
  int index = 0;
  Group * child = p_Doc->getEngine()->getGroup(index);
  while (child != NULL) {
    this->addGroup(child, firstitem);
    index++;
    child = p_Doc->getEngine()->getGroup(index);
    // open up groups with children
    //groupitem->setOpen(TRUE);
  }

  firstitem->setOpen(TRUE);
  p_ListView->show();
}

void ShapeView::doUpdate() {
  // TODO select selectd group, shape or behavior.
  EM_CERR("ShapeView::doUpdate");
}

/* Adds all groups, shapes and behaviors to the tree as items. */
void ShapeView::addGroup(Group * group, ListItem * parent) {
  if (group == NULL) return;
  EM_CERR("ShapeView::addGroup added a group");

  if (QString(group->getName()).find('#', 0, true) == 0) return;

  ListItem * groupitem = new ListItem(parent, QString("object ") + QString(group->getName()));
  groupitem->setObject(group, LISTITEM_GROUP);
  if (p_Doc->getEngine() == group) {
    groupitem->setOpen(TRUE);
  }
  if (group == p_Doc->getCurrentGroup()) {
    p_ListView->setCurrentItem(groupitem);
  }

  int index = 0;
  Group * child = group->getGroup(index);
  // do not add  children
  // 	while (child != NULL) {
  // 		this->addGroup(child, groupitem);
  // 		index++;
  // 		child = group->getGroup(index);
  // 		// open up groups with children
  // 		//groupitem->setOpen(TRUE);
  // 	}

  // add shapes
  int shindex = 0;
  Shape3D * shape = group->getShape3D(shindex);
  while (shape != NULL) {
    ListItem * shapeitem = new ListItem(groupitem, QString("shape ") + 
					QString().setNum(shindex));
    shapeitem->setObject(shape, LISTITEM_SHAPE);
    if (shape == p_Doc->getCurrentShape()) {
      p_ListView->setCurrentItem(shapeitem);
      groupitem->setOpen(TRUE);
    }
    shindex++;
    shape = group->getShape3D(shindex);
  }
  // add behaviors
  Behavior * beh = group->getBehavior();
  if (beh != NULL) {
    QString str;
    switch (beh->getType()) {
    case PBL_TYPE_BUMPERBEH: str = QString("bumper behavior"); break;
    case PBL_TYPE_ARMBEH: str = QString("arm behavior"); break;
    case PBL_TYPE_STATEBEH: str = QString("state behavior"); break;
    default: str = QString("behavior");
    }
    if (beh->getLight() != NULL) {
      str += QString(" (has light)");
    }
    ListItem * behitem = new ListItem(groupitem, str);
    behitem->setObject(beh, LISTITEM_BEHAVIOR);
  }
}

void ShapeView::slotChanged() {
  EM_CERR("ShapeView::slotChanged");
  QListViewItem * currentitem = p_ListView->currentItem();
  if (currentitem != NULL) {
    switch (((ListItem*)currentitem)->getObjectType()) {
    case LISTITEM_GROUP: {
      p_Doc->clearSelectedVertex();
      p_Doc->clearSelectedPolygon();
      p_Doc->setCurrentGroup((Group*)((ListItem*)currentitem)->getObject());
      p_WidgetStack->raiseWidget(p_WidgetGroup);
      PinEditApp::p_CurrentApp->setMode(EM_GROUP_MODE);
      EM_CERR("ShapeView::slotChanged selected a group");
    } break;
    case LISTITEM_SHAPE: {
      p_Doc->clearSelectedVertex();
      p_Doc->clearSelectedPolygon();
      p_Doc->setCurrentShape((Shape3D*)((ListItem*)currentitem)->getObject());
      p_WidgetStack->raiseWidget(p_WidgetShape);
      PinEditApp::p_CurrentApp->setMode(EM_SHAPE_MODE);
      EM_CERR("ShapeView::slotChanged selected a shape");
    } break;
    case LISTITEM_BEHAVIOR: {
      p_WidgetStack->raiseWidget(p_WidgetBehavior);
      EM_CERR("ShapeView::slotChanged seledted a shape");
    } break;
    }
  }
  this->updateProperties();
  p_Doc->rebuildAll("polygon");
}

void ShapeView::disableProperties() {
  EM_CERR("ShapeView::disableProperties");
  p_LineEditName->setDisabled(true);
  p_BoxHidden->setDisabled(true);
  p_BoxCollision->setDisabled(true);
  p_BoxTransformOnce->setDisabled(true);
  p_BoxWall->setDisabled(true);
  p_BoxOneWay->setDisabled(true);
  p_BoxBehind->setDisabled(true);
  p_BoxBehind2->setDisabled(true);
  p_BoxAllwaysLit->setDisabled(true);
}

void ShapeView::enableProperties(int type) {
  EM_CERR("ShapeView::enableProperties");
  switch (type) {
  case 0: {
    p_LineEditName->setEnabled(true);
    p_BoxCollision->setEnabled(true);
    p_BoxTransformOnce->setEnabled(true);
    p_BoxWall->setEnabled(true);
    p_BoxOneWay->setEnabled(true);
  } break;
  case 1: {
    p_BoxHidden->setEnabled(true);
    p_BoxBehind->setEnabled(true);
    p_BoxBehind2->setEnabled(true);
    p_BoxAllwaysLit->setEnabled(true);
  } break;
  }
}

void ShapeView::updateProperties() {
  EM_CERR("ShapeView::updateProperties");
  QListViewItem * currentitem = p_ListView->currentItem();
  if (currentitem == NULL) return;
  this->disableProperties();
  // group
  if (((ListItem*)currentitem)->getObjectType() == LISTITEM_GROUP) {
    this->enableProperties(0);
    Group * group = (Group*)((ListItem*)currentitem)->getObject();
    // name
    p_LineEditName->setText(group->getName());
    // collision
    if (group->getCollisionBounds() != NULL) {
      p_BoxCollision->setChecked(TRUE);
    } else {
      p_BoxCollision->setChecked(FALSE);
    }
    // transform once
    if (group->getProperties() & (EM_GROUP_TRANSFORM_ONCE | EM_GROUP_NO_TRANSFORM)) {
      p_BoxTransformOnce->setChecked(TRUE);
      group->unsetProperty(EM_GROUP_NO_TRANSFORM);
      group->setProperty(EM_GROUP_TRANSFORM_ONCE);
    } else {
      p_BoxTransformOnce->setChecked(FALSE);
    }
    // wall
    if (group->getUserProperties() & PBL_WALLS) {
      p_BoxWall->setChecked(TRUE);
    } else {
      p_BoxWall->setChecked(FALSE);
    }
    // one way
    if (group->getUserProperties() & PBL_WALLS_ONE) {
      p_BoxOneWay->setChecked(TRUE);
    } else {
      p_BoxOneWay->setChecked(FALSE);
    }
    EM_CERR("ShapeView::updateProperties group");
  }
  // shape
  // 	if (m_hShape.find(currentitem) != m_hShape.end()) {
  if (((ListItem*)currentitem)->getObjectType() == LISTITEM_SHAPE) {
    this->enableProperties(1);
    // 		Shape3D * shape = (*(m_hShape.find(currentitem))).second;
    Shape3D * shape = (Shape3D*)((ListItem*)currentitem)->getObject();
    // hidden
    if (shape->getProperties() & EM_SHAPE3D_HIDDEN) {
      p_BoxHidden->setChecked(TRUE);
    } else {
      p_BoxHidden->setChecked(FALSE);
    }
    // behind
    if (shape->getProperties() & EM_SHAPE3D_BEHIND) {
      p_BoxBehind->setChecked(TRUE);
    } else {
      p_BoxBehind->setChecked(FALSE);
    }
    // behind2
    if (shape->getProperties() & EM_SHAPE3D_BEHIND2) {
      p_BoxBehind2->setChecked(TRUE);
    } else {
      p_BoxBehind2->setChecked(FALSE);
    }
    // allways lit
    if (shape->getProperties() & EM_SHAPE3D_ALLWAYSLIT) {
      p_BoxAllwaysLit->setChecked(TRUE);
    } else {
      p_BoxAllwaysLit->setChecked(FALSE);
    }
    EM_CERR("ShapeView::updateProperties shape");
  }
}

void ShapeView::slotApplyProp() {
  EM_CERR("ShapeView::slotApplyProp");
  QListViewItem * currentitem = p_ListView->currentItem();
  if (currentitem == NULL) return;
  // 	if (m_hGroup.find(currentitem) != m_hGroup.end()) {
  if (((ListItem*)currentitem)->getObjectType() == LISTITEM_GROUP) {
    // 		Group * group = (*(m_hGroup.find(currentitem))).second;
    Group * group = (Group*)((ListItem*)currentitem)->getObject();
    // name
    group->setName(p_LineEditName->text().data());
    // collision
    if (p_BoxCollision->isChecked()) {
      if (group->getCollisionBounds() == NULL) {
	CollisionBounds * cb = new CollisionBounds(0.0f);
	group->setCollisionBounds(cb);
      }
    } else {
      if (group->getCollisionBounds() != NULL) {
	delete(group->getCollisionBounds());
	group->setCollisionBounds(NULL);
      }
    }
    // transform once
    // TODO: fix transform_once -> no_transform problem
    if (p_BoxTransformOnce->isChecked()) {
      group->setProperty(EM_GROUP_TRANSFORM_ONCE);
    } else {
      group->unsetProperty(EM_GROUP_TRANSFORM_ONCE);
      group->unsetProperty(EM_GROUP_NO_TRANSFORM);
    }
    // wall
    if (p_BoxWall->isChecked()) {
      group->setUserProperty(PBL_WALLS);
    } else {
      group->unsetUserProperty(PBL_WALLS);
    }
    if (p_BoxOneWay->isChecked()) {
      group->setUserProperty(PBL_WALLS_ONE);
    } else {
      group->unsetUserProperty(PBL_WALLS_ONE);
    }
  }
  // shape
  // 	if (m_hShape.find(currentitem) != m_hShape.end()) {
  if (((ListItem*)currentitem)->getObjectType() == LISTITEM_SHAPE) {
    this->enableProperties(1);
    // 		Shape3D * shape = (*(m_hShape.find(currentitem))).second;
    Shape3D * shape = (Shape3D*)((ListItem*)currentitem)->getObject();
    // hidden
    if (p_BoxHidden->isChecked()) {
      shape->setProperty(EM_SHAPE3D_HIDDEN); 
    } else {
      shape->unsetProperty(EM_SHAPE3D_HIDDEN);
    }
    // behind
    if (p_BoxBehind2->isChecked()) {
      shape->setProperty(EM_SHAPE3D_BEHIND2); 
      shape->unsetProperty(EM_SHAPE3D_BEHIND);
    } else {
      shape->unsetProperty(EM_SHAPE3D_BEHIND2);
      if (p_BoxBehind->isChecked()) {
	shape->setProperty(EM_SHAPE3D_BEHIND); 
      } else {
	shape->unsetProperty(EM_SHAPE3D_BEHIND);
      }
    }
    // allways lit
    if (p_BoxAllwaysLit->isChecked()) {
      shape->setProperty(EM_SHAPE3D_ALLWAYSLIT);
    } else {
      shape->unsetProperty(EM_SHAPE3D_ALLWAYSLIT);
    }
  }
  p_Doc->rebuildAll("group");
}

void ShapeView::slotEdit() {
  EM_CERR("ShapeView::slotEdit");	
  QListViewItem * currentitem = p_ListView->currentItem();
  if (currentitem == NULL) return;
  // 	if (m_hBehavior.find(currentitem) != m_hBehavior.end()) {
  if (((ListItem*)currentitem)->getObjectType() == LISTITEM_BEHAVIOR) {
    // 		Behavior * beh = (*(m_hBehavior.find(currentitem))).second;
    Behavior * beh = (Behavior*)((ListItem*)currentitem)->getObject();
    switch (beh->getType()) {
    case PBL_TYPE_STATEBEH: {
      p_StateDialog->edit((StateBehavior*)beh);
    } break;
    case PBL_TYPE_BUMPERBEH: {
      p_BumperDialog->edit((BumperBehavior*)beh);
    } break;
    case PBL_TYPE_ARMBEH: {
      p_ArmDialog->edit((ArmBehavior*)beh);
    } break;
    case PBL_TYPE_FAKEMODULEBEH: {
      p_ModuleDialog->edit((FakeModuleBehavior*)beh);
    } break;
    default: EM_CERR("ShapeView::slotEdit no editor for behavior");
    }
  }
}

void ShapeView::slotLight() {
  EM_CERR("ShapeView::slotLight");	
  QListViewItem * currentitem = p_ListView->currentItem();
  if (currentitem == NULL) return;
  // 	if (m_hBehavior.find(currentitem) != m_hBehavior.end()) {
  if (((ListItem*)currentitem)->getObjectType() == LISTITEM_BEHAVIOR) {
    // 		Behavior * beh = (*(m_hBehavior.find(currentitem))).second;
    Behavior * beh = (Behavior*)((ListItem*)currentitem)->getObject();
    p_LightDialog->edit(beh);
  }
}

void ShapeView::slotAdd() {
  EM_CERR("ShapeView::slotAdd");
  if (p_Doc->getCurrentGroup() == NULL) {
    EM_CERR("shapeview::slotapplyadd no group selected");
    return;
  }
  switch (p_ChoiceBehavior->currentItem()) {
    // none
  case 0:	
    break;
    // bumper
  case 1: {
    CommandNewBehavior * command = new CommandNewBehavior(p_Doc);
    command->setBehaviorType(PBL_TYPE_BUMPERBEH);
    CommandContext context;
    context.clear();
    context.group = p_Doc->getCurrentGroup();
    command->execute(context);
  } break;
  case 2: {
    CommandNewBehavior * command = new CommandNewBehavior(p_Doc);
    command->setBehaviorType(PBL_TYPE_ARMBEH);
    CommandContext context;
    context.clear();
    context.group = p_Doc->getCurrentGroup();
    command->execute(context);
    ((ArmBehavior*)command->getBehavior())->setIsRight(false);
  } break;
  case 3: {
    CommandNewBehavior * command = new CommandNewBehavior(p_Doc);
    command->setBehaviorType(PBL_TYPE_ARMBEH);
    CommandContext context;
    context.clear();
    context.group = p_Doc->getCurrentGroup();
    command->execute(context);
    ((ArmBehavior*)command->getBehavior())->setIsRight(true);
  } break;
  case 4: {
    CommandNewBehavior * command = new CommandNewBehavior(p_Doc);
    command->setBehaviorType(PBL_TYPE_FAKEMODULEBEH);
    CommandContext context;
    context.clear();
    context.group = p_Doc->getCurrentGroup();
    command->execute(context);
    p_ModuleDialog->edit((FakeModuleBehavior*)command->getBehavior());
  } break;
  case 5: {
    CommandNewBehavior * command = new CommandNewBehavior(p_Doc);
    command->setBehaviorType(PBL_TYPE_STATEBEH);
    CommandContext context;
    context.clear();
    context.group = p_Doc->getCurrentGroup();
    command->execute(context);
    p_StateDialog->edit((StateBehavior*)command->getBehavior());
  } break;
  }
}
