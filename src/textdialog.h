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

#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

// qt includes
#include <qdialog.h>
#include <qstring.h>

class Q3TextBrowser;

/** Yet another dialog */
class TextDialog : public QDialog {
	Q_OBJECT
 public:
	TextDialog(QWidget * parent, const char * name, Qt::WFlags f);
	~TextDialog();
	void setSource(const QString & name);
 public slots:
	void slotBack();
	void slotCancel();
 private:
	Q3TextBrowser * p_TextBrowser;
};

#endif 

