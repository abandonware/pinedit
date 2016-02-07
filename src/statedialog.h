/***************************************************************************
                          statedialog.h  -  description
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

#ifndef STATEDIALOG_H
#define STATEDIALOG_H

// general includes
#include <map>
// qt includes
#include <qdialog.h>
// application includes
#include "pineditdoc.h"

class Q3ListView;
class QLineEdit;
class QComboBox;
class QCheckBox;
class StateBehavior;
class StateItem;
class QString;
class QSpinBox;

/** @author Henrik Enqvist IB  */
class StateDialog : public QDialog  {
	Q_OBJECT        // must include this if you use Qt signals/slots
 public:
	StateDialog(PinEditDoc * doc, QWidget * parent, const char * name, Qt::WFlags f) ;
	~StateDialog();
	/** Pops up a dialog to edit the StateBehavior. */
	void edit(StateBehavior * beh);
 protected:
	void reload();
	void applyChanges(StateItem * stateitem);
 protected slots:
	void slotChanged();
	void slotDone();
	void slotAdd();
	void slotDel();
	void slotApply();
	void slotNewSignal();
	void slotChooseSound();
	void slotChooseMusic();
 private:
	PinEditDoc * p_Doc;
	StateBehavior * p_StateBehavior;
	Q3ListView * p_ListView;

	QSpinBox * p_SpinCollState;
	QSpinBox * p_SpinDelayState;
	QSpinBox * p_SpinDelay;
	QLineEdit * p_EditSignal;
 	QLineEdit * p_EditTX;
 	QLineEdit * p_EditTY;
 	QLineEdit * p_EditTZ;
 	QLineEdit * p_EditStep;
 	QLineEdit * p_EditRX;
 	QLineEdit * p_EditRY;
 	QLineEdit * p_EditRZ;
	QLineEdit * p_EditSound;
	QLineEdit * p_EditMusic;
	QComboBox * p_ComboProperty;
	QComboBox * p_ComboActSig;
	QComboBox * p_ComboCollSig;
	QCheckBox * p_BoxAlwaysLit;
	QCheckBox * p_BoxLight;
	QCheckBox * p_BoxMove;
	QCheckBox * p_BoxUseShape;
	QCheckBox * p_BoxShape[8];
/* 	map<QListViewItem *, StateItem *> m_hStateItem; */
	map<QString, int> m_hIndex;
};

#endif
