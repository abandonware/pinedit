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
#include <q3filedialog.h>
#include <qlayout.h>
//Added by qt3to4:
#include <Q3BoxLayout>
#include <Q3HBoxLayout>
// application includes
#include "moduledialog.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "FakeModuleBehavior.h"

ModuleDialog::ModuleDialog(PinEditDoc * doc, QWidget * parent, const char * name, Qt::WFlags f) 
: QDialog(parent, name, f) {
	EM_CERR("ModuleDialog::ModuleDialog");
	assert(doc != NULL);
	p_Doc = doc;
	p_FakeModuleBehavior = NULL;

	p_EditModule = new QLineEdit(this);
	QPushButton * choosebutton = new QPushButton("choose", this);
	connect(choosebutton, SIGNAL(clicked()), this, SLOT(slotChooseModule()));

	QPushButton * donebutton = new QPushButton("done", this);
	connect(donebutton, SIGNAL(clicked()), this, SLOT(slotDone()));

	Q3BoxLayout * hlayout = new Q3HBoxLayout(this);
	hlayout->addWidget(p_EditModule);
	hlayout->addWidget(choosebutton);
	hlayout->addWidget(donebutton);
}

ModuleDialog::~ModuleDialog() {
}

void ModuleDialog::reload() {
	EM_CERR("ModuleDialog::reload");
	assert(p_FakeModuleBehavior != NULL);
	p_EditModule->setText(QString(p_FakeModuleBehavior->getName()));
}

void ModuleDialog::edit(FakeModuleBehavior * beh) {
	EM_CERR("ModuleDialog::edit");
	assert(beh != NULL);
	p_FakeModuleBehavior = beh;
	// TODO load behavior
	this->reload();
	this->show();
}

void ModuleDialog::applyChanges() {
	EM_CERR("ModuleDialog::applyChanges");
	assert(p_FakeModuleBehavior != NULL);
	p_FakeModuleBehavior->setName(p_EditModule->text().latin1());
}

void ModuleDialog::slotDone() {	
	EM_CERR("ModuleDialog::slotDone");
	this->applyChanges();
	this->done(0);
}

void ModuleDialog::slotChooseModule() {
  QString filename = Q3FileDialog::getOpenFileName(0, 0, this);
  if (!filename.isEmpty()) {
		p_EditModule->setText(filename);
	}
}
