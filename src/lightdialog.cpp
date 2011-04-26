/***************************************************************************
                          lightdialog.cpp  -  description
                             -------------------
    begin                : Wed Apr 10 2002
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
#include <iostream>
// qt includes
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>
// application includes
#include "lightdialog.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "Group.h"
#include "Light.h"
#include "Engine.h"
#include "Behavior.h"
#include "StdAnimation.h"

LightDialog::LightDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) 
  : QDialog(parent, name, f) {
  assert(doc != NULL);
  p_Doc = doc;
  p_Behavior = NULL;

  QLabel * labelR = new QLabel("r", this);
  QLabel * labelG = new QLabel("g", this);
  QLabel * labelB = new QLabel("b", this);
  QLabel * labelX = new QLabel("x", this);
  QLabel * labelY = new QLabel("y", this);
  QLabel * labelZ = new QLabel("z", this);
  p_EditR = new QLineEdit(this);
  p_EditG = new QLineEdit(this);
  p_EditB = new QLineEdit(this);
  p_EditX = new QLineEdit(this);
  p_EditY = new QLineEdit(this);
  p_EditZ = new QLineEdit(this);
  p_BoxBlink = new QCheckBox("blink", this);
  p_SpinDelay = new QSpinBox(10, 100, 10, this);

  QPushButton * donebutton = new QPushButton("ok", this);
  connect(donebutton, SIGNAL(clicked()), this, SLOT(slotDone()));
  QPushButton * removebutton = new QPushButton("remove light", this);
  connect(removebutton, SIGNAL(clicked()), this, SLOT(slotRemove()));
  QPushButton * cancelbutton = new QPushButton("cancel", this);
  connect(cancelbutton, SIGNAL(clicked()), this, SLOT(slotCancel()));

  // the layout of the objects
  QBoxLayout * vlayout = new QVBoxLayout(this);
	
  QBoxLayout * hlayout1 = new QHBoxLayout(vlayout);
  hlayout1->addWidget(labelR);
  hlayout1->addWidget(p_EditR);
  hlayout1->addWidget(labelG);
  hlayout1->addWidget(p_EditG);
  hlayout1->addWidget(labelB);
  hlayout1->addWidget(p_EditB);
  QBoxLayout * hlayout2 = new QHBoxLayout(vlayout);
  hlayout2->addWidget(labelX);
  hlayout2->addWidget(p_EditX);
  hlayout2->addWidget(labelY);
  hlayout2->addWidget(p_EditY);
  hlayout2->addWidget(labelZ);
  hlayout2->addWidget(p_EditZ);
  QBoxLayout * hlayout3 = new QHBoxLayout(vlayout);
  hlayout3->addWidget(p_BoxBlink);
  hlayout3->addWidget(p_SpinDelay);
  QBoxLayout * hlayout4 = new QHBoxLayout(vlayout);
  hlayout4->addWidget(donebutton);
  hlayout4->addWidget(removebutton);
  hlayout4->addWidget(cancelbutton);

  EM_CERR("lightdialog::lightdialog");
}

LightDialog::~LightDialog() {
}

void LightDialog::edit(Behavior * beh) {
  assert(beh->getParent() != NULL);
  p_Behavior = beh;
  Group * gl = beh->getParent()->getGroup(0);
  if (gl != NULL) {
    Light * light = gl->getLight();
    if (light != NULL) {
      float r, g, b;
      light->getColor(r, g, b);
      p_EditR->setText(QString().setNum(r));
      p_EditG->setText(QString().setNum(g));
      p_EditB->setText(QString().setNum(b));
      float x, y, z;
      gl->getTranslation(x, y, z);
      p_EditX->setText(QString().setNum(x));
      p_EditY->setText(QString().setNum(y));
      p_EditZ->setText(QString().setNum(z));
    }
    if (gl->getBehavior() != NULL) {
      if (gl->getBehavior()->getType() == EM_TYPE_STDANIMATION) {
	p_BoxBlink->setChecked(true);
	p_SpinDelay->setValue( ((StdAnimation*)gl->getBehavior())->getStep() );
      } else {
	p_BoxBlink->setChecked(false);
	cerr << "LightDialog::edit behavior in light group not of type animation" << endl;
      }
    } else {
      p_BoxBlink->setChecked(false);
    }
  }
  this->show();
}

void LightDialog::slotDone() {
  assert(p_Behavior != NULL);
  assert(p_Behavior->getParent() != NULL);
  EM_CERR("LightDialog::slotDone");
  Group * gl;
  Light * light = p_Behavior->getLight();
  if (light == NULL) {
    light = new Light(1.0f, 0.0f, 0.1f, 1, 1, 1);
    light->setOn(true);
    light->setProperty(EM_IGNORE_ANGLE_FULL);
    //light->setProperty(EM_IGNORE_DISTANCE);
    light->setProperty(EM_USE_BOUNDS);
    light->setBounds(10.0);
    gl = new Group();
    gl->setName("#light");
    gl->setLight(light);
    p_Behavior->getParent()->add(gl);
    p_Behavior->setLight(light);
    p_Doc->getEngine()->addLight(light);
  } else {
    gl = light->getParent();
  }
  assert(gl != NULL && light != NULL);

  gl->setTranslation(p_EditX->text().toFloat(), 
		     p_EditY->text().toFloat(), 
		     p_EditZ->text().toFloat());

  light->setColor(p_EditR->text().toFloat(), 
		  p_EditG->text().toFloat(), 
		  p_EditB->text().toFloat());

  if (p_BoxBlink->isChecked()) {
    // 		Behavior * beh = gl->getBehavior(0);
    Behavior * beh = gl->getBehavior();
    if (beh == NULL) {
      EM_CERR("LightDialog::slotDone added a behavior");
      beh = new StdAnimation(p_SpinDelay->value(), EM_LIGHT);
      // 			gl->addBehavior(beh);
      gl->setBehavior(beh);
    }
    assert(beh->getType() == EM_TYPE_STDANIMATION);
    EM_CERR("LightDialog::slotDone already a animation in the group");
    StdAnimation  * anim = (StdAnimation*) beh;
    anim->clear();
    anim->setStep(p_SpinDelay->value());
    anim->add(p_EditR->text().toFloat(), 
	      p_EditG->text().toFloat(), 
	      p_EditB->text().toFloat());
    anim->setEnd(0.0f, 0.0f, 0.0f);
  } else {
    Behavior * beh = gl->getBehavior();
    if (beh != NULL && beh->getType() == EM_TYPE_STDANIMATION) {
      // 			gl->removeBehavior(beh);
      gl->setBehavior(NULL);
      delete(beh);
    }
  }

  p_Doc->setModified(true);
  p_Doc->rebuildAll("group");
  this->done(0);
}

void LightDialog::slotRemove() {
  EM_CERR("LightDialog::slotRemove");
  Light * light = p_Behavior->getLight();
  if (light != NULL) {
    Group * gl = light->getParent();
    assert (gl != NULL);
    Group * parent = gl->getParent();
    assert(parent != NULL);
    Behavior * beh = parent->getBehavior();
    assert(beh != NULL);
    beh->setLight(NULL);
    parent->removeGroup(gl);
  } else {
    EM_CERR("LightDialog::slotRemove no light");
  }
  p_Doc->setModified(true);
  p_Doc->rebuildAll("group");
  this->done(0);
}

void LightDialog::slotCancel() {
  EM_CERR("LightDialog::slotCancel");
  this->done(0);
}
