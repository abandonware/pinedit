/***************************************************************************
                          armdialog.cpp  -  description
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
#include <qfiledialog.h>
#include <qlayout.h>
// application includes
#include "armdialog.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "SoundUtil.h"
#include "ArmBehavior.h"

ArmDialog::ArmDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) 
  : QDialog(parent, name, f) {
  EM_CERR("ArmDialog::ArmDialog");
  assert(doc != NULL);
  p_Doc = doc;
  p_ArmBehavior = NULL;

  QLabel * label = new QLabel("sound", this);

  p_EditSound = new QLineEdit(this);
  QPushButton * choosebutton = new QPushButton("choose", this);
  connect(choosebutton, SIGNAL(clicked()), this, SLOT(slotChooseSound()));

  QPushButton * donebutton = new QPushButton("done", this);
  connect(donebutton, SIGNAL(clicked()), this, SLOT(slotDone()));

  QBoxLayout * hlayout = new QHBoxLayout(this);
  hlayout->addWidget(label);
  hlayout->addWidget(p_EditSound);
  hlayout->addWidget(choosebutton);
  hlayout->addWidget(donebutton);
}

ArmDialog::~ArmDialog() {
}

void ArmDialog::reload() {
  EM_CERR("ArmDialog::reload");
  assert(p_ArmBehavior != NULL);
  if (p_ArmBehavior->getSound() != -1 && 
      SoundUtil::getInstance()->getSoundName(p_ArmBehavior->getSound()) != NULL) {
    p_EditSound->setText(QString(SoundUtil::getInstance()->getSoundName(p_ArmBehavior->getSound())));
  } else {
    p_EditSound->setText(QString(""));
  }
}

void ArmDialog::edit(ArmBehavior * beh) {
  EM_CERR("ArmDialog::edit");
  assert(beh != NULL);
  p_ArmBehavior = beh;
  // TODO load behavior
  this->reload();
  this->show();
}

void ArmDialog::applyChanges() {
  assert(p_ArmBehavior != NULL);
  EM_CERR("ArmDialog::applyChanges");
  if (!(p_EditSound->text().isEmpty())) {
    int sound = SoundUtil::getInstance()->loadSample(p_EditSound->text());
    if (sound != -1) {
      p_ArmBehavior->setSound(sound);
      EM_CERR("ArmDialog::applyChanges added sound");
    } else {
      EM_CERR("ArmDialog::applyChagnes sound not loaded");
    }
  } else {
    p_ArmBehavior->setSound(-1);
    EM_CERR("ArmDialog::applyChanges lineedit empty");
  }
}

void ArmDialog::slotDone() {	
  EM_CERR("ArmDialog::slotDone");
  this->applyChanges();
  this->done(0);
}

void ArmDialog::slotChooseSound() {
  QString filename = QFileDialog::getOpenFileName(0, 0, this);
  if (!filename.isEmpty()) {
    p_EditSound->setText(filename);
  }
}
