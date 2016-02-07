/***************************************************************************
                          shapeview.h  -  description
                             -------------------
    begin                : Wed Apr 10 2002
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

#ifndef SHAPEVIEW_H
#define SHAPEVIEW_H

// general includes
#include <map>
// qt includes
#include <q3vbox.h>
// application includes
#include "pineditdoc.h"
#include "listitem.h"

class QLineEdit;
class QComboBox;
class QCheckBox;
class Q3MainWindow;
class PinEditDoc;
class Q3ListView;
class Q3ListViewItem;
class Group;
class Shape3D;
class StateDialog;
class LightDialog;
class BumperDialog;
class ArmDialog;
class ModuleDialog;
class Behavior;
class Q3WidgetStack;
class ListItem;

/** @author Henrik Enqvist IB  */
class ShapeView : public Q3VBox, public Updateable, public Rebuildable {
	Q_OBJECT        // must include this if you use Qt signals/slots
 public:
	ShapeView(PinEditDoc * doc, QWidget * parent, const char * name, Qt::WFlags f) ;
	~ShapeView();
	void doRebuild();
	void doUpdate();
	void addGroup(Group * group, ListItem * parent);
	void updateProperties();
 public slots:
	void slotChanged();
	void slotApplyProp();
	void slotAdd();
	void slotEdit();
	void slotLight();
 protected:
	void disableProperties();
	void enableProperties(int type);
 private:
	PinEditDoc * p_Doc;
	QWidget * p_WidgetGroup;
	QWidget * p_WidgetShape;
	QWidget * p_WidgetBehavior;
	Q3WidgetStack * p_WidgetStack;
	StateDialog * p_StateDialog;
	BumperDialog * p_BumperDialog;
	ArmDialog * p_ArmDialog;
	LightDialog * p_LightDialog;
	ModuleDialog * p_ModuleDialog;
	Q3ListView * p_ListView;
	QLineEdit * p_LineEditName;
	QCheckBox * p_BoxHidden;
	QCheckBox * p_BoxCollision;
	QCheckBox * p_BoxTransformOnce;
	QCheckBox * p_BoxWall;
	QCheckBox * p_BoxOneWay;
	QCheckBox * p_BoxBehind;
	QCheckBox * p_BoxBehind2;
	QCheckBox * p_BoxAllwaysLit;
	QComboBox * p_ChoiceBehavior;
/* 	map<QListViewItem *, Shape3D *> m_hShape; */
/* 	map<QListViewItem *, Group *> m_hGroup; */
/* 	map<QListViewItem *, Behavior *> m_hBehavior; */
};

#endif
