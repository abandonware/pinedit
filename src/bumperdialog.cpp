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
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <q3filedialog.h>
#include <qlayout.h>
#include <qspinbox.h>
#include <qmessagebox.h>
//Added by qt3to4:
#include <Q3BoxLayout>
#include <Q3HBoxLayout>
// application includes
#include "bumperdialog.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "SoundUtil.h"
#include "BumperBehavior.h"

BumperDialog::BumperDialog(PinEditDoc * doc, QWidget * parent, const char * name, Qt::WFlags f) 
  : QDialog(parent, name, f) {
  EM_CERR("BumperDialog::BumperDialog");
  assert(doc != NULL);
  p_Doc = doc;
  p_BumperBehavior = NULL;

  QLabel * label = new QLabel("sound", this);

  p_SpinPower = new QSpinBox(0, 100, 1, this);
  p_EditSound = new QLineEdit(this);
  QPushButton * choosebutton = new QPushButton("choose", this);
  connect(choosebutton, SIGNAL(clicked()), this, SLOT(slotChooseSound()));

  QPushButton * donebutton = new QPushButton("done", this);
  connect(donebutton, SIGNAL(clicked()), this, SLOT(slotDone()));

  Q3BoxLayout * hlayout = new Q3HBoxLayout(this);
  hlayout->addWidget(p_SpinPower);
  hlayout->addWidget(label);
  hlayout->addWidget(p_EditSound);
  hlayout->addWidget(choosebutton);
  hlayout->addWidget(donebutton);
}

BumperDialog::~BumperDialog() {
}

void BumperDialog::reload() {
  EM_CERR("BumperDialog::reload");
  assert(p_BumperBehavior != NULL);
  p_SpinPower->setValue((int)((float)p_BumperBehavior->getPower() * 100.0f));
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
  EM_CERR("statedialog::edit");
}

void BumperDialog::applyChanges() {
  assert(p_BumperBehavior != NULL);
  EM_CERR("BumperDialog::applyChanges");
  p_BumperBehavior->setPower((float)p_SpinPower->value()/100.0f);
  if (!(p_EditSound->text().isEmpty())) {
    int sound = SoundUtil::getInstance()->loadSample(p_EditSound->text());
    if (sound != -1) {
      p_BumperBehavior->setSound(sound);
      EM_CERR("BumperDialog::applyChanges added sound");
    } else {
      EM_CERR("BumperDialog::applyChagnes sound not loaded");
    }
  } else {
    p_BumperBehavior->setSound(-1);
    EM_CERR("BumperDialog::applyChanges lineedit empty");
  }
}

void BumperDialog::slotDone() {	
  EM_CERR("BumperDialog::slotDone");
  this->applyChanges();
  this->done(0);
}

void BumperDialog::slotChooseSound() {
  QString filename = Q3FileDialog::getOpenFileName(0, 0, this);
  if (!filename.isEmpty()) {
    p_EditSound->setText(filename);
  }
}
