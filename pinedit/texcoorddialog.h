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

#ifndef TEXCOORDDIALOG_H
#define TEXCOORDDIALOG_H

// qt includes
#include <qdialog.h>

class QRadioButton;
class PinEditDoc;
class CommandTexCoord;

/** Yet another dialog */
class TexCoordDialog : public QDialog {
	Q_OBJECT
 public:
	TexCoordDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f);
	~TexCoordDialog();
 public slots:
	void slotTexCoord();
	void slotCancel();
 private:
	CommandTexCoord * p_CommandTexCoord;
	QRadioButton * p_RadioButtonXY;
	QRadioButton * p_RadioButtonXZ;
	QRadioButton * p_RadioButtonZY;
	PinEditDoc * p_Doc;
};

#endif 

