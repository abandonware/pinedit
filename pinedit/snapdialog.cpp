/***************************************************************************
                          snapdialog.cpp  -  description
                             -------------------
    begin                : Thu Jul 11 19:39:03 EET 2002
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
#include <iostream>
// qt includes
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <qmsgbox.h>
// application includes
#include "pineditdoc.h"
#include "snapdialog.h"
#include "commandsnap.h"

SnapDialog::SnapDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) 
: QDialog(parent, name, f) {
	assert(doc != NULL);
	p_Doc = doc;
	p_CommandSnap = new CommandSnap(p_Doc);
	p_CommandSnap->setFactor(1);

	p_BoxX = new QCheckBox("x", this);
	p_BoxY = new QCheckBox("y", this);
	p_BoxZ = new QCheckBox("z", this);
	p_ComboSnap = new QComboBox(this);
	p_ComboSnap->insertItem("1");
	p_ComboSnap->insertItem("0.5");
	p_ComboSnap->insertItem("0.25");
	p_ComboSnap->insertItem("0.125");
	p_ComboSnap->insertItem("0.0625");
	QPushButton * snapbutton = new QPushButton("snap", this);
	connect(snapbutton, SIGNAL(clicked()), this, SLOT(slotSnap()));
	QPushButton * cancelbutton = new QPushButton("cancel", this);
	connect(cancelbutton, SIGNAL(clicked()), this, SLOT(slotCancel()));

	QBoxLayout * layout = new QVBoxLayout(this);
	QBoxLayout * hlayout = new QHBoxLayout(layout);
	hlayout->addWidget(p_BoxX);
	hlayout->addWidget(p_BoxY);
	hlayout->addWidget(p_BoxZ);
	layout->addWidget(p_ComboSnap);
	layout->addWidget(snapbutton);
	layout->addWidget(cancelbutton);
}

SnapDialog::~SnapDialog() {
}

void SnapDialog::slotSnap() {
	CommandContext context;
	context.clear();
	context.shape = p_Doc->getCurrentShape();
	if (context.shape == NULL) {
		QMessageBox::information( this, "Snap", "No Shape selected.");
		this->done(0);
		return;
	}
	switch (p_ComboSnap->currentItem()) {
	case 0: p_CommandSnap->setFactor(1); break;
	case 1: p_CommandSnap->setFactor(0.5f); break;
	case 2: p_CommandSnap->setFactor(0.25f); break;
	case 3: p_CommandSnap->setFactor(0.125f); break;
	case 4: p_CommandSnap->setFactor(0.0625f); break;
	default: p_CommandSnap->setFactor(1);
	}
	p_CommandSnap->setX(p_BoxX->isChecked());
	p_CommandSnap->setY(p_BoxY->isChecked());
	p_CommandSnap->setZ(p_BoxZ->isChecked());
	p_CommandSnap->build()->execute(context);
	this->done(0);
	cerr << "SnapDialog::slotSnap" << endl;
};

void SnapDialog::slotCancel() {
	this->done(0);
	cerr << "SnapDialog::slotCancel" << endl;
};
