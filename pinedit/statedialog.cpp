/***************************************************************************
                          statedialog.cpp  -  description
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
#include <qtabwidget.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qtabwidget.h>
#include <qfiledialog.h>
#include <qmsgbox.h>
// application includes
#include "listitem.h"
#include "statedialog.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "SoundUtil.h"
#include "Group.h"
#include "StateBehavior.h"
#include "Pinball.h"
#include "Loader.h"
#include "Shape3D.h"

StateDialog::StateDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) 
  : QDialog(parent, name, f) {
  assert(doc != NULL);
  p_Doc = doc;
  p_StateBehavior = NULL;

  p_ListView = new QListView(this);
  connect(p_ListView, SIGNAL(selectionChanged()), this, SLOT(slotChanged()));
  p_ListView->setSelectionMode(QListView::Single);
  p_ListView->addColumn(QString("stateitem"));
  p_ListView->addColumn(QString("asig"));
  p_ListView->addColumn(QString("csig"));
  p_ListView->addColumn(QString("coll"));
  p_ListView->addColumn(QString("d state"));
  p_ListView->addColumn(QString("delay"));
  p_ListView->addColumn(QString("light"));
  p_ListView->addColumn(QString("type"));
  p_ListView->addColumn(QString("prop"));
  p_ListView->addColumn(QString("sound"));
  p_ListView->addColumn(QString("music"));
  p_ListView->setMinimumSize(500, 200);
	
  QPushButton * addbutton = new QPushButton("new", this);
  connect(addbutton, SIGNAL(clicked()), this, SLOT(slotAdd()));
  QPushButton * delbutton = new QPushButton("del", this);
  connect(delbutton, SIGNAL(clicked()), this, SLOT(slotDel()));

  QTabWidget * tabwidget = new QTabWidget(this);
  //tabwidget->setFixedSize(200,200);
  // the layout of the objects
  QBoxLayout * vlayout = new QVBoxLayout(this);
  //QBoxLayout * vlayoutA = new QVBoxLayout(hlayout);
  //QBoxLayout * vlayoutB = new QVBoxLayout(hlayout);
  vlayout->addWidget(p_ListView);
	
  QBoxLayout * hlayoutA = new QHBoxLayout(vlayout);
  hlayoutA->addWidget(addbutton);
  hlayoutA->addWidget(delbutton);

  vlayout->addWidget(tabwidget);
  // signals
  {
    QWidget * widget = new QWidget(this);
    tabwidget->addTab(widget, "signals");

    QLabel * labelActSig = new QLabel("activation signal", widget);
    p_ComboActSig = new QComboBox(widget);
		
    QLabel * labelCollSig = new QLabel("collision signal", widget);
    p_ComboCollSig = new QComboBox(widget);

    QPushButton * newButton = new QPushButton("new signal name", widget);
    connect(newButton, SIGNAL(clicked()), this, SLOT(slotNewSignal()));

    p_EditSignal = new QLineEdit(widget);

    QBoxLayout * vlayout1 = new QVBoxLayout(widget);
    QBoxLayout * hlayout1 = new QHBoxLayout(vlayout1);
    hlayout1->addWidget(labelActSig);
    hlayout1->addWidget(p_ComboActSig);
    hlayout1->addWidget(labelCollSig);
    hlayout1->addWidget(p_ComboCollSig);
    QBoxLayout * hlayout2 = new QHBoxLayout(vlayout1);
    hlayout2->addWidget(newButton);
    hlayout2->addWidget(p_EditSignal);
  }
  // states
  {
    QWidget * widget = new QWidget(this);
    tabwidget->addTab(widget, "states");

    QLabel * labelCollState = new QLabel("collision state", widget);
    p_SpinCollState = new QSpinBox(-1, 16, 1, widget);
    QLabel * labelDelayState = new QLabel("delay state", widget);
    p_SpinDelayState = new QSpinBox(-1, 16, 1, widget);
    QLabel * labelDelay = new QLabel("delay", widget);
    p_SpinDelay = new QSpinBox(-1, 1000, 1, widget);

    QBoxLayout * vlayout1 = new QVBoxLayout(widget);
    QBoxLayout * hlayout1 = new QHBoxLayout(vlayout1);
    QBoxLayout * hlayout2 = new QHBoxLayout(vlayout1);
    QBoxLayout * hlayout3 = new QHBoxLayout(vlayout1);
    hlayout1->addWidget(labelCollState);
    hlayout1->addWidget(p_SpinCollState);
    hlayout2->addWidget(labelDelayState);
    hlayout2->addWidget(p_SpinDelayState);
    hlayout3->addWidget(labelDelay);
    hlayout3->addWidget(p_SpinDelay);
  }
  // light
  {
    QWidget * widget = new QWidget(this);
    tabwidget->addTab(widget, "light");

    p_BoxLight = new QCheckBox("light on", widget);

    QBoxLayout * vlayout1 = new QVBoxLayout(widget);
    vlayout1->addWidget(p_BoxLight);
  }		
  // animation
  {
    QWidget * widget = new QWidget(this);
    tabwidget->addTab(widget, "animation");

    QLabel * labelTX = new QLabel("x", widget);
    QLabel * labelTY = new QLabel("y", widget);
    QLabel * labelTZ = new QLabel("z", widget);
    QLabel * labelStep = new QLabel("steps", widget);
    QLabel * labelRX = new QLabel("x", widget);
    QLabel * labelRY = new QLabel("y", widget);
    QLabel * labelRZ = new QLabel("z", widget);
		
    p_EditTX = new QLineEdit(widget);
    p_EditTY = new QLineEdit(widget);
    p_EditTZ = new QLineEdit(widget);
    p_EditRX = new QLineEdit(widget);
    p_EditRY = new QLineEdit(widget);
    p_EditRZ = new QLineEdit(widget);
    p_EditStep = new QLineEdit(widget);

    QBoxLayout * vlayout1 = new QVBoxLayout(widget);

    QBoxLayout * hlayout1 = new QHBoxLayout(vlayout1);
    hlayout1->addWidget(labelStep);
    hlayout1->addWidget(p_EditStep);

    QBoxLayout * hlayout2 = new QHBoxLayout(vlayout1);
    hlayout2->addWidget(labelTX);
    hlayout2->addWidget(p_EditTX);
    hlayout2->addWidget(labelTY);
    hlayout2->addWidget(p_EditTY);
    hlayout2->addWidget(labelTZ);
    hlayout2->addWidget(p_EditTZ);
		
    QBoxLayout * hlayout3 = new QHBoxLayout(vlayout1);
    hlayout3->addWidget(labelRX);
    hlayout3->addWidget(p_EditRX);
    hlayout3->addWidget(labelRY);
    hlayout3->addWidget(p_EditRY);
    hlayout3->addWidget(labelRZ);
    hlayout3->addWidget(p_EditRZ);
  }
  // type - user and shape properties
  {
    QWidget * widget = new QWidget(this);
    tabwidget->addTab(widget, "type");

    p_ComboProperty = new QComboBox(widget);
    p_ComboProperty->insertItem("null");
    p_ComboProperty->insertItem("lock");
    p_ComboProperty->insertItem("trap");
    p_ComboProperty->insertItem("trap bounce");

    p_BoxAlwaysLit = new QCheckBox("always lit", widget);

    QBoxLayout * vlayout1 = new QVBoxLayout(widget);
    vlayout1->addWidget(p_ComboProperty);
    vlayout1->addWidget(p_BoxAlwaysLit);
  }
  // sound
  {
    QWidget * widget = new QWidget(this);
    tabwidget->addTab(widget, "audio");

    p_EditSound = new QLineEdit(widget);
    QPushButton * choosesound = new QPushButton("choose", widget);
    connect(choosesound, SIGNAL(clicked()), this, SLOT(slotChooseSound()));

    p_EditMusic = new QLineEdit(widget);
    QPushButton * choosemusic = new QPushButton("choose", widget);
    connect(choosemusic, SIGNAL(clicked()), this, SLOT(slotChooseMusic()));

    QBoxLayout * vlayout1 = new QVBoxLayout(widget);
    QBoxLayout * hlayout1 = new QHBoxLayout(vlayout1);
    QBoxLayout * hlayout2 = new QHBoxLayout(vlayout1);
    hlayout1->addWidget(p_EditSound);
    hlayout1->addWidget(choosesound);
    hlayout2->addWidget(p_EditMusic);
    hlayout2->addWidget(choosemusic);
  }		
  // shape
  {
    QWidget * widget = new QWidget(this);
    tabwidget->addTab(widget, "shape");

    p_BoxShape[0] = new QCheckBox("shape 0", widget);
    p_BoxShape[1] = new QCheckBox("shape 1", widget);
    p_BoxShape[2] = new QCheckBox("shape 2", widget);
    p_BoxShape[3] = new QCheckBox("shape 3", widget);
    p_BoxShape[4] = new QCheckBox("shape 4", widget);
    p_BoxShape[5] = new QCheckBox("shape 5", widget);
    p_BoxShape[6] = new QCheckBox("shape 6", widget);
    p_BoxShape[7] = new QCheckBox("shape 7", widget);

    QBoxLayout * hlayout1 = new QHBoxLayout(widget);
    QBoxLayout * vlayout1 = new QVBoxLayout(hlayout1);
    QBoxLayout * vlayout2 = new QVBoxLayout(hlayout1);
    vlayout1->addWidget(p_BoxShape[0]);
    vlayout1->addWidget(p_BoxShape[1]);
    vlayout1->addWidget(p_BoxShape[2]);
    vlayout1->addWidget(p_BoxShape[3]);
    vlayout2->addWidget(p_BoxShape[4]);
    vlayout2->addWidget(p_BoxShape[5]);
    vlayout2->addWidget(p_BoxShape[6]);
    vlayout2->addWidget(p_BoxShape[7]);
  }

  p_BoxMove = new QCheckBox("move", this);
  p_BoxUseShape = new QCheckBox("shape", this);

  QBoxLayout * hlayoutC = new QHBoxLayout(vlayout);
  hlayoutC->addWidget(p_BoxMove);
  hlayoutC->addWidget(p_BoxUseShape);

  QPushButton * editbutton = new QPushButton("apply", this);
  connect(editbutton, SIGNAL(clicked()), this, SLOT(slotApply()));
  QPushButton * donebutton = new QPushButton("exit", this);
  connect(donebutton, SIGNAL(clicked()), this, SLOT(slotDone()));

  vlayout->addWidget(editbutton);
  vlayout->addWidget(donebutton);
  EM_CERR("statedialog::statedialog");
}

StateDialog::~StateDialog() {
}

void StateDialog::reload() {
  assert(p_StateBehavior != NULL);
  p_ListView->clear();
  //m_hStateItem.clear();
  //QListViewItem * firstitem = new QListViewItem(p_ListView, "bottom");
  int index = 0;
  StateItem * stateitem = p_StateBehavior->getStateItem(index);
  while (stateitem != NULL) {
    // 		QListViewItem * listitem = 	new QListViewItem(p_ListView, QString().setNum(index) + " state");
    ListItem * listitem = new ListItem(p_ListView, QString().setNum(index) + " state");
    listitem->setText(1, (stateitem->getActSig() >= 0 ? 
			  QString(Loader::getInstance()->getSignal(stateitem->getActSig())) :
			  QString("")));
    listitem->setText(2, (stateitem->getCollSig() >= 0 ? 
			  QString(Loader::getInstance()->getSignal(stateitem->getCollSig())) :
			  QString("")));
    listitem->setText(3, (stateitem->getCollState() >= 0 ? QString().setNum(stateitem->getCollState()) :
			  QString("")));
    listitem->setText(4, (stateitem->getDelayState() >= 0 ? QString().setNum(stateitem->getDelayState()) :
			  QString("")));
    listitem->setText(5, (stateitem->getDelay() >= 0 ? QString().setNum(stateitem->getDelay()) :
			  QString("")));
    listitem->setText(6, (stateitem->getLight() ? QString("on") :	QString("off")));
    listitem->setText(7, QString().setNum(stateitem->getUserProperty()));
    listitem->setText(8, QString().setNum(stateitem->getShapeProperty()));
    listitem->setText(9, (stateitem->getSound() != -1 ? QString().setNum(stateitem->getSound()) :
			  QString("")));
    listitem->setText(10, (stateitem->getMusic() != -1 ? QString().setNum(stateitem->getMusic()) :
			  QString("")));
    listitem->setOpen(TRUE);
    listitem->setObject(stateitem, LISTITEM_STATEITEM);
    // 		m_hStateItem.insert(pair<QListViewItem *, StateItem *>(listitem, stateitem));
    ++index;
    stateitem = p_StateBehavior->getStateItem(index);
  }	
  // check boxes
  p_BoxMove->setChecked(p_StateBehavior->usesMove());
  p_BoxUseShape->setChecked(p_StateBehavior->usesShape());
  // signal comboboxes
  // TODO fix a work around for a strange qt-bug
  p_ComboActSig->clear();
  p_ComboCollSig->clear();
  m_hIndex.clear();
  // default signals
  int count = 0;
  p_ComboActSig->insertItem("null");
  p_ComboCollSig->insertItem("null");
  m_hIndex.insert(pair<QString, int>("null", count)); 
  ++count;
  p_ComboActSig->insertItem("reset");
  p_ComboCollSig->insertItem("reset");
  m_hIndex.insert(pair<QString, int>("reset", count)); 
  ++count;
  p_ComboActSig->insertItem("tilt");
  p_ComboCollSig->insertItem("tilt");
  m_hIndex.insert(pair<QString, int>("tilt", count));
  ++count;
  // 	p_ComboActSig->insertItem("extraball");
  // 	p_ComboCollSig->insertItem("extraball");
  // 	m_hIndex.insert(pair<QString, int>("extraball", count));
  // 	++count;
  // 	p_ComboActSig->insertItem("multiball_off");
  // 	p_ComboCollSig->insertItem("multiball_off");
  // 	m_hIndex.insert(pair<QString, int>("multiball_off", count));
  // 	++count;
  // 	p_ComboActSig->insertItem("allballs_off");
  // 	p_ComboCollSig->insertItem("allballs_off");
  // 	m_hIndex.insert(pair<QString, int>("allballs_off", count));
  // 	++count;
  p_ComboActSig->insertItem("lock1");
  p_ComboCollSig->insertItem("lock1");
  m_hIndex.insert(pair<QString, int>("lock1", count));
  ++count;
  p_ComboActSig->insertItem("lock2");
  p_ComboCollSig->insertItem("lock2");
  m_hIndex.insert(pair<QString, int>("lock2", count));
  ++count;
  p_ComboActSig->insertItem("lock3");
  p_ComboCollSig->insertItem("lock3");
  m_hIndex.insert(pair<QString, int>("lock3", count));
  ++count;
  p_ComboActSig->insertItem("lock4");
  p_ComboCollSig->insertItem("lock4");
  m_hIndex.insert(pair<QString, int>("lock4", count));
  ++count;

  index = LOADER_FIRSTSIGNAL;
  for (const char * str = NULL; (str = Loader::getInstance()->getSignal(index)) != NULL; ++index, ++count) {
    p_ComboActSig->insertItem(str);
    p_ComboCollSig->insertItem(str);
    m_hIndex.insert(pair<QString, int>(str, count));
  } 

  p_ListView->sort();
  p_ListView->show();
  EM_CERR("statedialog::reload");
}

void StateDialog::edit(StateBehavior * beh) {
  assert(beh != NULL);
  p_StateBehavior = beh;
  // TODO load behavior
  this->reload();
  this->show();
  EM_CERR("statedialog::edit");
}

void StateDialog::applyChanges(StateItem * stateitem) {
  EM_CERR("StateDialog::applyChanges");
  assert(p_StateBehavior != NULL);
  assert(stateitem != NULL);

  stateitem->setActSig(Loader::getInstance()->getSignal(p_ComboActSig->currentText().latin1()));
  stateitem->setCollSig(Loader::getInstance()->getSignal(p_ComboCollSig->currentText().latin1()));
  stateitem->setCollState(p_SpinCollState->value());
  stateitem->setDelayState(p_SpinDelayState->value(), p_SpinDelay->value());

  if (p_BoxLight->isChecked()) {
    stateitem->setLight(true);
  } else {
    stateitem->setLight(false);
  }

  switch (p_ComboProperty->currentItem()) {
  case 0: stateitem->setUserProperty(PBL_NULL); break;
  case 1: stateitem->setUserProperty(PBL_LOCK); break;
  case 2: stateitem->setUserProperty(PBL_TRAP); break;
  case 3: stateitem->setUserProperty(PBL_TRAP_BOUNCE); break;
  }

  if (p_BoxAlwaysLit->isChecked()) {
    stateitem->setShapeProperty(EM_SHAPE3D_ALWAYSLIT);
  } else {
    stateitem->setShapeProperty(0);
  }

  stateitem->setMoveSteps(p_EditStep->text().toInt());
  stateitem->m_vtxTr.x = p_EditTX->text().toFloat();
  stateitem->m_vtxTr.y = p_EditTY->text().toFloat();
  stateitem->m_vtxTr.z = p_EditTZ->text().toFloat();
  stateitem->m_vtxRot.x = p_EditRX->text().toFloat();
  stateitem->m_vtxRot.y = p_EditRY->text().toFloat();
  stateitem->m_vtxRot.z = p_EditRZ->text().toFloat();
  // sound
  if (!(p_EditSound->text().isEmpty())) {
    int sound = SoundUtil::getInstance()->loadSample(p_EditSound->text());
    if (sound != -1) {
      stateitem->setSound(sound);
      EM_CERR("StateDialog::applyChanges added sound");
    } else {
      cerr << "StateDialog::applyChanges sound not loaded" << endl;
    }
  } else {
    stateitem->setSound(-1);
    EM_CERR("StateDialog::applyChanges lineedit empty");
  }
  // music
  if (!(p_EditMusic->text().isEmpty())) {
    int music = SoundUtil::getInstance()->loadMusic(p_EditMusic->text());
    if (music != -1) {
      stateitem->setMusic(music);
      EM_CERR("StateDialog::applyChanges added music");
    } else {
      cerr << "StateDialog::applyChanges music not loaded" << endl;
    }
  } else {
    stateitem->setMusic(-1);
    EM_CERR("StateDialog::applyChanges lineedit empty");
  }

  for (int a=0; a<8; ++a) {
    stateitem->addShapeEnable(a, p_BoxShape[a]->isChecked());
  }
}

void StateDialog::slotAdd() {
  EM_CERR("StateDialog::slotAdd");
  assert(p_StateBehavior != NULL);

  StateItem * stateitem = new StateItem();
  this->applyChanges(stateitem);
  p_StateBehavior->addStateItem(stateitem);

  this->reload();
}

void StateDialog::slotApply() {
  EM_CERR("StateDialog::slotApply");
  assert(p_StateBehavior != NULL);
  // 	QListViewItem * selecteditem = p_ListView->selectedItem();
  ListItem * selecteditem = (ListItem*)p_ListView->selectedItem();
  if (selecteditem == NULL || selecteditem->getObjectType() != LISTITEM_STATEITEM) return;

  StateItem * stateitem = (StateItem*) selecteditem->getObject();
  this->applyChanges(stateitem);

  if (p_BoxMove->isChecked()) {
    p_StateBehavior->useMove(true);
  } else {
    p_StateBehavior->useMove(false);
  }
  if (p_BoxUseShape->isChecked()) {
    p_StateBehavior->useShape(true);
  } else {
    p_StateBehavior->useShape(false);
  }

  this->reload();
}

// TODO do this as a command to allow undo
void StateDialog::slotDel() {
  EM_CERR("StateDialog::slotDel");
  assert(p_StateBehavior != NULL);
  // 	QListViewItem * selecteditem = p_ListView->selectedItem();
  ListItem * selecteditem = (ListItem*)p_ListView->selectedItem();
  if (selecteditem == NULL || selecteditem->getObjectType() != LISTITEM_STATEITEM) return;
  StateItem * stateitem = (StateItem*) selecteditem->getObject();
  p_StateBehavior->removeStateItem(stateitem);
  delete(stateitem);
  this->reload();
}

void StateDialog::slotChanged() {
  EM_CERR("StateDialog::slotChanged");
  // 	QListViewItem * selecteditem = p_ListView->selectedItem();
  ListItem * selecteditem = (ListItem*)p_ListView->selectedItem();
  if (selecteditem == NULL || selecteditem->getObjectType() != LISTITEM_STATEITEM) return;
  StateItem * stateitem = (StateItem*) selecteditem->getObject();
  // the signals and delay TODO
  map<QString, int>::iterator item = 
    m_hIndex.find(Loader::getInstance()->getSignal(stateitem->getActSig()));
  if (item != m_hIndex.end() && (*item).second >= 0) {
    p_ComboActSig->setCurrentItem((*item).second);
  } else {
    p_ComboActSig->setCurrentItem(0);
  }
  item = m_hIndex.find(Loader::getInstance()->getSignal(stateitem->getCollSig()));
  if (item != m_hIndex.end() && (*item).second >= 0) {
    p_ComboCollSig->setCurrentItem((*item).second);
  } else {
    p_ComboCollSig->setCurrentItem(0);
  }
	
  p_SpinCollState->setValue(stateitem->getCollState());
  p_SpinDelayState->setValue(stateitem->getDelayState());
  p_SpinDelay->setValue(stateitem->getDelay());
  p_BoxLight->setChecked(stateitem->m_bLight);
  // the property
  switch(stateitem->getUserProperty()) {
  case PBL_NULL: p_ComboProperty->setCurrentItem(0); break;
  case PBL_LOCK: p_ComboProperty->setCurrentItem(1); break;
  case PBL_TRAP: p_ComboProperty->setCurrentItem(2); break;
  case PBL_TRAP_BOUNCE: p_ComboProperty->setCurrentItem(3); break;
  }
  p_BoxAlwaysLit->setChecked(stateitem->getShapeProperty() & EM_SHAPE3D_ALWAYSLIT);
  p_EditStep->setText(QString().setNum(stateitem->m_iMoveSteps));
  p_EditTX->setText(QString().setNum(stateitem->m_vtxTr.x));
  p_EditTY->setText(QString().setNum(stateitem->m_vtxTr.y));
  p_EditTZ->setText(QString().setNum(stateitem->m_vtxTr.z));
  p_EditRX->setText(QString().setNum(stateitem->m_vtxRot.x));
  p_EditRY->setText(QString().setNum(stateitem->m_vtxRot.y));
  p_EditRZ->setText(QString().setNum(stateitem->m_vtxRot.z));
  // sound
  if (stateitem->getSound() != -1 && 
      SoundUtil::getInstance()->getSoundName(stateitem->getSound()) != NULL) {
    p_EditSound->setText(QString(SoundUtil::getInstance()->getSoundName(stateitem->getSound())));
  } else {
    p_EditSound->setText(QString(""));
  }
  // music
  if (stateitem->getMusic() != -1 && 
      SoundUtil::getInstance()->getMusicName(stateitem->getMusic()) != NULL) {
    p_EditMusic->setText(QString(SoundUtil::getInstance()->getMusicName(stateitem->getMusic())));
  } else {
    p_EditMusic->setText(QString(""));
  }
	
  vector<bool>::iterator iter = stateitem->m_vShapeEnable.begin();
  vector<bool>::iterator end = stateitem->m_vShapeEnable.end();
  int a=0;
  for (; iter != end && a<8; ++iter, ++a) {
    p_BoxShape[a]->setChecked(*iter);
  }
}

void StateDialog::slotDone() {	
  EM_CERR("StateDialog::slotDone");
  this->done(0);
}

void StateDialog::slotNewSignal() {
  EM_CERR("StateDialog::slotNewSignal");
  assert(p_StateBehavior != NULL);
  assert(p_StateBehavior->getParent() != NULL);
  int index = 0;
  QString name = p_EditSignal->text();
  if (name.isEmpty()) {
    name = QString(p_StateBehavior->getParent()->getName()) + QString().setNum(index);
  }
  // find an unused name
  while (m_hIndex.find(name) != m_hIndex.end()) {
    ++index;
    name = QString(p_StateBehavior->getParent()->getName()) + QString().setNum(index);
  }
  m_hIndex.insert(pair<QString, int>(name, m_hIndex.size()));
  // register it at the loader
  Loader::getInstance()->getSignal(name.latin1());
  p_ComboActSig->insertItem(name);
  p_ComboCollSig->insertItem(name);
}

void StateDialog::slotChooseSound() {
  EM_CERR("StateDialog::slotChooseSound");
  QString filename = QFileDialog::getOpenFileName(0, 0, this);
  if (!filename.isEmpty()) {
    p_EditSound->setText(filename);
  }
}

void StateDialog::slotChooseMusic() {
  EM_CERR("StateDialog::slotChooseMusic");
  QString filename = QFileDialog::getOpenFileName(0, 0, this);
  if (!filename.isEmpty()) {
    p_EditMusic->setText(filename);
  }
}
