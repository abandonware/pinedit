/***************************************************************************
                          lightdialog.h  -  description
                             -------------------
    begin                : Mon Jul 22 2002
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

#ifndef LIGHTDIALOG_H
#define LIGHTDIALOG_H

// qt includes
#include <qdialog.h>

class PinEditDoc;
class Group;
class QLineEdit;
class QCheckBox;
class QSpinBox;
class Behavior;

/** @author Henrik Enqvist */
class LightDialog : public QDialog  {
	Q_OBJECT        // must include this if you use Qt signals/slots
 public:
	LightDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) ;
	~LightDialog();
	/** Pops up a dialog to edit the light. */
	void edit(Behavior * beh);
 protected slots:
	void slotDone();
	void slotCancel();
 private:
	Behavior * p_Behavior;
	PinEditDoc * p_Doc;
	QLineEdit * p_EditR;
	QLineEdit * p_EditG;
	QLineEdit * p_EditB;
	QLineEdit * p_EditX;
	QLineEdit * p_EditY;
	QLineEdit * p_EditZ;
	QCheckBox * p_BoxBlink;
	QSpinBox * p_SpinDelay;
};

#endif
