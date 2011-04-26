/***************************************************************************
                          moduledialog.h  -  description
                             -------------------
    begin                : Fri Aug 23 2002
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

#ifndef MODULEDIALOG_H
#define MODULEDIALOG_H

// qt includes
#include <qdialog.h>
// application includes
#include "pineditdoc.h"

class QLineEdit;
class FakeModuleBehavior;

/** @author Henrik Enqvist IB  */
class ModuleDialog : public QDialog  {
	Q_OBJECT        // must include this if you use Qt signals/slots
 public:
	ModuleDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) ;
	~ModuleDialog();
	/** Pops up a dialog to edit the FakeModuleBehavior. */
	void edit(FakeModuleBehavior * beh);
 protected:
	void reload();
	void applyChanges();
 protected slots:
	void slotDone();
	void slotChooseModule();
 private:
	PinEditDoc * p_Doc;

	QLineEdit * p_EditModule;
	FakeModuleBehavior * p_FakeModuleBehavior;
};

#endif
