/***************************************************************************
                          moduledialog.cpp  -  description
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
// application includes
#include "moduledialog.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "FakeModuleBehavior.h"

ModuleDialog::ModuleDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) 
: QDialog(parent, name, f) {
	cerr << "ModuleDialog::ModuleDialog" << endl;
	assert(doc != NULL);
	p_Doc = doc;
	p_FakeModuleBehavior = NULL;

	p_EditModule = new QLineEdit(this);
	QPushButton * choosebutton = new QPushButton("choose", this);
	connect(choosebutton, SIGNAL(clicked()), this, SLOT(slotChooseModule()));

	QPushButton * donebutton = new QPushButton("done", this);
	connect(donebutton, SIGNAL(clicked()), this, SLOT(slotDone()));

	QBoxLayout * hlayout = new QHBoxLayout(this);
	hlayout->addWidget(p_EditModule);
	hlayout->addWidget(choosebutton);
	hlayout->addWidget(donebutton);
}

ModuleDialog::~ModuleDialog() {
}

void ModuleDialog::reload() {
	cerr << "ModuleDialog::reload" << endl;
	assert(p_FakeModuleBehavior != NULL);
	p_EditModule->setText(QString(p_FakeModuleBehavior->getName()));
}

void ModuleDialog::edit(FakeModuleBehavior * beh) {
	cerr << "ModuleDialog::edit" << endl;
	assert(beh != NULL);
	p_FakeModuleBehavior = beh;
	// TODO load behavior
	this->reload();
	this->show();
}

void ModuleDialog::applyChanges() {
	cerr << "ModuleDialog::applyChanges" << endl;
	assert(p_FakeModuleBehavior != NULL);
	p_FakeModuleBehavior->setName(p_EditModule->text().latin1());
}

void ModuleDialog::slotDone() {	
	cerr << "ModuleDialog::slotDone" << endl;
	this->applyChanges();
	this->done(0);
}

void ModuleDialog::slotChooseModule() {
  QString filename = QFileDialog::getOpenFileName(0, 0, this);
  if (!filename.isEmpty()) {
		p_EditModule->setText(filename);
	}
}
