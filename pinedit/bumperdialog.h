/***************************************************************************
                          bumperdialog.h  -  description
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

#ifndef BUMPERDIALOG_H
#define BUMPERDIALOG_H

// qt includes
#include <qdialog.h>
// application includes
#include "pineditdoc.h"

class QLineEdit;
class BumperBehavior;

/** @author Henrik Enqvist IB  */
class BumperDialog : public QDialog  {
	Q_OBJECT        // must include this if you use Qt signals/slots
 public:
	BumperDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) ;
	~BumperDialog();
	/** Pops up a dialog to edit the BumperBehavior. */
	void edit(BumperBehavior * beh);
 protected:
	void reload();
	void applyChanges();
 protected slots:
	void slotDone();
	void slotChooseSound();
 private:
	PinEditDoc * p_Doc;

	QLineEdit * p_EditSound;
	BumperBehavior * p_BumperBehavior;
};

#endif
