/***************************************************************************
                          bumperdialog.cpp  -  description
                             -------------------
    begin                : Fri Aug 23 2002
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
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include <qlayout.h>
#include <qspinbox.h>
// application includes
#include "bumperdialog.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "SoundUtil.h"
#include "BumperBehavior.h"

BumperDialog::BumperDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) 
: QDialog(parent, name, f) {
	cerr << "BumperDialog::BumperDialog" << endl;
	assert(doc != NULL);
	p_Doc = doc;
	p_BumperBehavior = NULL;

	p_SpinScore = new QSpinBox(0, 10000, 50, this);
	p_EditSound = new QLineEdit(this);
	QPushButton * choosebutton = new QPushButton("choose", this);
	connect(choosebutton, SIGNAL(clicked()), this, SLOT(slotChooseSound()));

	QPushButton * donebutton = new QPushButton("done", this);
	connect(donebutton, SIGNAL(clicked()), this, SLOT(slotDone()));

	QBoxLayout * hlayout = new QHBoxLayout(this);
	hlayout->addWidget(p_SpinScore);
	hlayout->addWidget(p_EditSound);
	hlayout->addWidget(choosebutton);
	hlayout->addWidget(donebutton);
}

BumperDialog::~BumperDialog() {
}

void BumperDialog::reload() {
	cerr << "BumperDialog::reload" << endl;
	assert(p_BumperBehavior != NULL);
	p_SpinScore->setValue(p_BumperBehavior->getScore());
	if (p_BumperBehavior->getSound() != -1 && 
			SoundUtil::getInstance()->getSoundName(p_BumperBehavior->getSound()) != NULL) {
		p_EditSound->setText(QString(SoundUtil::getInstance()->getSoundName(p_BumperBehavior->getSound())));
	} else {
		p_EditSound->setText(QString(""));
	}
}

void BumperDialog::edit(BumperBehavior * beh) {
	assert(beh != NULL);
	p_BumperBehavior = beh;
	// TODO load behavior
	this->reload();
	this->show();
	cerr << "statedialog::edit" << endl;
}

void BumperDialog::applyChanges() {
	assert(p_BumperBehavior != NULL);
	cerr << "BumperDialog::applyChanges" << endl;
	p_BumperBehavior->setScore(p_SpinScore->value());
	if (!(p_EditSound->text().isEmpty())) {
		int sound = SoundUtil::getInstance()->loadSample(p_EditSound->text());
		if (sound != -1) {
			p_BumperBehavior->setSound(sound);
			cerr << "BumperDialog::applyChanges added sound" << endl;
		} else {
			cerr << "BumperDialog::applyChagnes sound not loaded" << endl;
		}
	} else {
		p_BumperBehavior->setSound(-1);
		cerr << "BumperDialog::applyChanges lineedit empty" << endl;
	}
}

void BumperDialog::slotDone() {	
	cerr << "BumperDialog::slotDone" << endl;
	this->applyChanges();
	this->done(0);
}

void BumperDialog::slotChooseSound() {
  QString filename = QFileDialog::getOpenFileName(0, 0, this);
  if (!filename.isEmpty()) {
		p_EditSound->setText(filename);
	}
}
