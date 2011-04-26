/***************************************************************************
                          snapdialog.h  -  description
                             -------------------
    begin                : Thy Jul 11 19:39:03 EET 2002
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

#ifndef SNAPDIALOG_H
#define SNAPDIALOG_H

// qt includes
#include <qdialog.h>

class QComboBox;
class QCheckBox;
class PinEditDoc;
class CommandSnap;

/** Yet another dialog */
class SnapDialog : public QDialog {
	Q_OBJECT
 public:
	SnapDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f);
	~SnapDialog();
 public slots:
	void slotSnap();
	void slotCancel();
 private:
	CommandSnap * p_CommandSnap;
	QCheckBox * p_BoxX;
	QCheckBox * p_BoxY;
	QCheckBox * p_BoxZ;
	QComboBox * p_ComboSnap;
	PinEditDoc * p_Doc;
};

#endif 

