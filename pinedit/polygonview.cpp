/***************************************************************************
                          polygonview.cpp  -  description
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
#include <iostream>
#include <cstdio>
#include <cassert>
// qt includes
#include <qlayout.h>
#include <qlistview.h>
#include <qlineedit.h>
#include <qtabwidget.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qstring.h>
#include <qfiledialog.h>
#include <qmsgbox.h>
// application includes
#include "polygonview.h"
#include "pineditdoc.h"
#include "listitem.h"
// emilia includes
#include "Private.h"
#include "Engine.h"
#include "Group.h"
#include "Shape3D.h"
#include "Polygon.h"
#include "EMath.h"
#include "TextureUtil.h"

#define INT2OBJ(a) ((void*)((a)+1))
#define OBJ2INT(a) (((int)(a))-1)

PolygonView::PolygonView(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) 
: QWidget(parent, name, f) {
  assert(doc != NULL);
  p_Doc = doc;
  p_Shape = NULL;
  p_Polygon = NULL;
  m_bSelectionChanged = true;
  p_Doc->registerUpdateable(this, "polygon");
  p_Doc->registerRebuildable(this, "polygon");
  // the polygon list view
  p_PolygonListView = new QListView(this);
  connect(p_PolygonListView, SIGNAL(selectionChanged()), this, SLOT(slotChanged()));
  p_PolygonListView->setSelectionMode(QListView::Extended);
  p_PolygonListView->addColumn(QString("polygons"));
  p_PolygonListView->setMinimumSize(200, 240);
  // the vertex list view
  p_VertexListView = new QListView(this);
  connect(p_VertexListView, SIGNAL(selectionChanged()), this, SLOT(slotVertexChanged()));
  p_VertexListView->setSelectionMode(QListView::Single);
  p_VertexListView->addColumn(QString("vertices for polygon"));
  p_VertexListView->setMinimumSize(200, 80);
  // tabs and widgets
  QTabWidget * tabWidget = new QTabWidget(this);
  //tabWidget->setFixedSize(200, 80);
  tabWidget->setMinimumSize(200, 80);
  // main layout
  QBoxLayout * vlayout = new QVBoxLayout(this);
  vlayout->addWidget(p_PolygonListView);
  vlayout->addWidget(p_VertexListView);
  vlayout->addWidget(tabWidget);
  vlayout->setStretchFactor(p_PolygonListView, 3);
  vlayout->setStretchFactor(p_PolygonListView, 2);
  vlayout->setStretchFactor(tabWidget, 0);
  // the vertex order widget
  {
    QWidget * widget = new QWidget(this);
    tabWidget->addTab(widget, "order");
		
    p_ButtonUp = new QPushButton("up", widget);
    connect(p_ButtonUp, SIGNAL(clicked()), this, SLOT(slotVertexUp()));
    p_ButtonDown = new QPushButton("down", widget);
    connect(p_ButtonDown, SIGNAL(clicked()), this, SLOT(slotVertexDown()));
		
    QBoxLayout * layout = new QHBoxLayout(widget);
    layout->addWidget(p_ButtonUp);
    layout->addWidget(p_ButtonDown);
  }
  // the position widget
  {
    QWidget * widget = new QWidget(this);
    tabWidget->addTab(widget, "position");
		
    p_EditX = new QLineEdit(widget);
    p_EditY = new QLineEdit(widget);
    p_EditZ = new QLineEdit(widget);
    connect(p_EditX, SIGNAL(returnPressed()), this, SLOT(slotApplyVertex()));
    connect(p_EditY, SIGNAL(returnPressed()), this, SLOT(slotApplyVertex()));
    connect(p_EditZ, SIGNAL(returnPressed()), this, SLOT(slotApplyVertex()));
		
    p_ApplyVertexButton = new QPushButton("apply", widget);
    connect(p_ApplyVertexButton, SIGNAL(clicked()), this, SLOT(slotApplyVertex()));

    QBoxLayout * vlayoutc = new QVBoxLayout(widget);
    QBoxLayout * hlayout = new QHBoxLayout(vlayoutc);
    hlayout->addWidget(p_EditX);
    hlayout->addWidget(p_EditY);
    hlayout->addWidget(p_EditZ);
    vlayoutc->addWidget(p_ApplyVertexButton);
  }
  // the color widget
  {
    QWidget * widget = new QWidget(this);
    tabWidget->addTab(widget, "color");

    p_EditR = new QLineEdit(widget);
    p_EditG = new QLineEdit(widget);
    p_EditB = new QLineEdit(widget);
    p_EditA = new QLineEdit(widget);
		
    connect(p_EditR, SIGNAL(returnPressed()), this, SLOT(slotApplyColor()));
    connect(p_EditG, SIGNAL(returnPressed()), this, SLOT(slotApplyColor()));
    connect(p_EditB, SIGNAL(returnPressed()), this, SLOT(slotApplyColor()));
    connect(p_EditA, SIGNAL(returnPressed()), this, SLOT(slotApplyColor()));

    p_ApplyColorButton = new QPushButton("apply", widget);
    connect(p_ApplyColorButton, SIGNAL(clicked()), this, SLOT(slotApplyColor()));

    QBoxLayout * vlayoutc = new QVBoxLayout(widget);
    QBoxLayout * hlayoutb = new QHBoxLayout(vlayoutc);
    hlayoutb->addWidget(p_EditR);
    hlayoutb->addWidget(p_EditG);
    hlayoutb->addWidget(p_EditB);
    hlayoutb->addWidget(p_EditA);
    vlayoutc->addWidget(p_ApplyColorButton);
  }
  // properties widget
  {
    QWidget * widget = new QWidget(this);
    tabWidget->addTab(widget, "prop");

    p_TransBox = new QCheckBox("transparent", widget);

    p_ApplyPropButton = new QPushButton("apply", widget);
    connect(p_ApplyPropButton, SIGNAL(clicked()), this, SLOT(slotApplyProp()));

    QBoxLayout * vlayout = new QVBoxLayout(widget);
    vlayout->addWidget(p_TransBox);
    vlayout->addWidget(p_ApplyPropButton);
  }

  this->doRebuild();
  //this->doUpdate();
}

PolygonView::~PolygonView(){
}

void PolygonView::doRebuild() {
  EM_CERR("PolygonView::doRebuild hashed ");
  p_PolygonListView->clear();
  p_VertexListView->clear();
  m_hPolyListItem.clear();
  // insert all children
  Shape3D * shape = p_Doc->getCurrentShape();
  p_Polygon = NULL;
  this->setShape(shape);

  p_PolygonListView->show();
}

void PolygonView::doUpdate() {
  EM_CERR("PolygonView::doUpdate");
  if (p_Shape == NULL) return;
  this->updateSelected();
}

void PolygonView::disableButtons() {
  EM_CERR("PolygonView::disbleButtons");
  p_ButtonUp->setEnabled(false);
  p_ButtonDown->setEnabled(false);
  p_ApplyVertexButton->setEnabled(false);
  p_ApplyColorButton->setEnabled(false);
  p_ApplyPropButton->setEnabled(false);
}

/* Adds all groups and shapes to the tree as items. */
void PolygonView::setShape(Shape3D * shape) {
  EM_CERR("PolygonView::setShape");
  this->disableButtons();
  p_Shape = shape;
  if (shape == NULL)  return;

  ListItem * shapeitem = new ListItem(p_PolygonListView, "shape");
  shapeitem->setOpen(TRUE);

  int polyindex = 0;
  Polygon * poly = shape->getPolygon(polyindex);
  // all polys
  while (poly != NULL) {
    QString str;
    if (polyindex < 100 && polyindex >= 10) {
      str = "0" + QString().setNum(polyindex);
    } else if (polyindex < 10) {
      str = "00" + QString().setNum(polyindex);
    } else {
      str = QString().setNum(polyindex);
    }

    ListItem * polyitem = new ListItem(shapeitem, str + " polygon");
    polyitem->setObject(poly, LISTITEM_POLYGON);
    // hash it
    m_hPolyListItem.insert(pair<Polygon*, ListItem*>(poly, polyitem));
		
    polyindex++;
    poly = shape->getPolygon(polyindex);
  }
}

void PolygonView::setPolygon(Shape3D * shape, Polygon * poly) {
  EM_CERR("PolygonView::setPolygon");
  p_VertexListView->clear();
  assert(shape != NULL);
  assert(poly != NULL);
  p_Polygon = poly;

  int index = 0;
  int vtxindex = poly->getIndex(index);
  Vertex3D * vtx = shape->getVertex3D(vtxindex);
  Color * color = poly->getColor(index);
  TexCoord * texcoord = poly->getTexCoord(index);
  while (vtx != NULL) {
    assert(color != NULL);
    assert(texcoord != NULL);
    QString str = QString().setNum(index) +
      " vtx " + 
      QString().setNum(vtx->x, 'g', 2) + " " +
      QString().setNum(vtx->y, 'g', 2) + " " +
      QString().setNum(vtx->z, 'g', 2) + " " +
      " color " +
      QString().setNum(color->r, 'g', 2) + " " +
      QString().setNum(color->g, 'g', 2) + " " +
      QString().setNum(color->b, 'g', 2) + " " +
      QString().setNum(color->a, 'g', 2) + " " +
      " tex " + 
      QString().setNum(texcoord->u, 'g', 2) + " " +
      QString().setNum(texcoord->v, 'g', 2);
    ListItem * vtxitem = new ListItem(p_VertexListView, str);
    vtxitem->setObject(INT2OBJ(vtxindex), LISTITEM_VERTEX);
	
    index++;
    vtxindex = poly->getIndex(index);
    vtx = shape->getVertex3D(vtxindex);
    color = poly->getColor(index);
    texcoord = poly->getTexCoord(index);
  }
  p_VertexListView->show();
}

void PolygonView::updateSelected() {
  EM_CERR("PolygonView::updateSelected");
  assert(p_Shape != NULL);
  assert(p_PolygonListView != NULL);
  m_bSelectionChanged = false;
  p_PolygonListView->selectAll(false);
  m_bSelectionChanged = true;
  this->disableButtons();
  // Create an iterator and give the listview as argument
  int index = 0;
  Polygon * poly = p_Doc->getSelectedPolygon(index);
  while (poly != NULL) {
    map<Polygon*, ListItem*>::iterator poly_item = m_hPolyListItem.find(poly);
    assert(poly_item != m_hPolyListItem.end());
    p_ApplyColorButton->setEnabled(true);
    p_ApplyPropButton->setEnabled(true);
    m_bSelectionChanged = false;
    (*poly_item).second->setSelected(true);
    m_bSelectionChanged = true;
    ++index;
    poly = p_Doc->getSelectedPolygon(index);
  }
}

void PolygonView::findSelected() {
  EM_CERR("PolygonView::findSelected");
  assert(p_Shape != NULL);
  this->disableButtons();
  int selected = 0;
  // Create an iterator and give the listview as argument
  QListViewItemIterator iter(p_PolygonListView);
  // iterate through all items of the listview
  for (; iter.current(); ++iter) {
    if (iter.current()->isSelected()) {
      selected++;
      // is it a polygon
      if (((ListItem*)iter.current())->getObjectType() == LISTITEM_POLYGON) {
	p_ApplyColorButton->setEnabled(true);
	p_ApplyPropButton->setEnabled(true);
	// TODO do it as an command so it can be undon
	Polygon * poly = (Polygon*)((ListItem*)iter.current())->getObject();
	assert(poly != NULL);
	int vtxindex = 0;
	int i = poly->getIndex(vtxindex);
	while (i >= 0) {
	  p_Doc->selectVertex(i);
	  vtxindex++;
	  i = poly->getIndex(vtxindex);
	}
				
	if (selected == 1) {
	  if (poly->getProperties() & EM_POLY_TRANS) {
	    p_TransBox->setChecked(TRUE);
	  } else {
	    p_TransBox->setChecked(FALSE);
	  } 
	} else {
	  if (poly->getProperties() & EM_POLY_TRANS && !p_TransBox->isChecked()) {
	    p_TransBox->setTristate(true);
	  }
	  if (!(poly->getProperties() & EM_POLY_TRANS) && p_TransBox->isChecked()) {
	    p_TransBox->setTristate(true);
	  }
	}
				
	p_Doc->selectPolygon(poly);
	this->setPolygon(p_Shape, poly);
	EM_CERR("PolygonView::findSelected selected a polygon");
      }
    }
  }
}

void PolygonView::slotVertexUp() {
  EM_CERR("PolygonView::slotVertexUp");
  assert(p_Shape != NULL);
  assert(p_Polygon != NULL);
  QListViewItemIterator iter(p_VertexListView);
  // iterate through all items of the listview
  for (; iter.current(); ++iter) {
    if (iter.current()->isSelected()) {
      if (((ListItem*)iter.current())->getObjectType() == LISTITEM_VERTEX) {
	int vtxindex = OBJ2INT(((ListItem*)iter.current())->getObject());
	p_Polygon->moveUp(p_Polygon->includes(vtxindex));
	this->setPolygon(p_Shape, p_Polygon);
      }
    }
  }
  p_Doc->updateAll("polygon");
}

void PolygonView::slotVertexDown() {
  EM_CERR("PolygonView::slotVertexDown");
  assert(p_Shape != NULL);
  assert(p_Polygon != NULL);
  QListViewItemIterator iter(p_VertexListView);
  // iterate through all items of the listview
  for (; iter.current(); ++iter) {
    if (iter.current()->isSelected()) {
      if (((ListItem*)iter.current())->getObjectType() == LISTITEM_VERTEX) {
	int vtxindex = OBJ2INT(((ListItem*)iter.current())->getObject());
	p_Polygon->moveDown(p_Polygon->includes(vtxindex));
	this->setPolygon(p_Shape, p_Polygon);
      }
    }
  }
  p_Doc->updateAll("polygon");
}

void PolygonView::slotVertexChanged() {
  EM_CERR("PolygonView::slotVertexChanged");
  assert(p_VertexListView != NULL);
  if (!m_bSelectionChanged) return;
  this->disableButtons();
	
  //p_Doc->clearSelectedVertex();
  //p_Doc->clearSelectedPolygon();
  //this->findSelected();
  p_ButtonUp->setEnabled(true);
  p_ButtonDown->setEnabled(true);
  p_ApplyVertexButton->setEnabled(true);
  // DO NOT update the view itself
  //p_Doc->updateAllExclude("polygon", this);
}

void PolygonView::slotChanged() {
  EM_CERR("PolygonView::slotChanged");
  assert(p_PolygonListView != NULL);
  if (!m_bSelectionChanged) return;
  p_Doc->clearSelectedVertex();
  p_Doc->clearSelectedPolygon();
  this->findSelected();
  // DO NOT update the view itself
  p_Doc->updateAllExclude("polygon", this);
}

void PolygonView::slotApplyVertex() {
  EM_CERR("polygonview::slotvertexchanged");
  assert(p_Shape != NULL);
  // Create an iterator and give the listview as argument
  QListViewItemIterator iter(p_VertexListView);
  // iterate through all items of the listview
  for (; iter.current(); ++iter) {
    if (iter.current()->isSelected()) {
      // if it was a vertex, set x y z
      if (((ListItem*)iter.current())->getObjectType() == LISTITEM_VERTEX) {
	//				Vertex3D * vtx = p_Shape->getVertex3D((*item_vtx).second);
	Vertex3D * vtx = p_Shape->getVertex3D(OBJ2INT(((ListItem*)iter.current())->getObject()));
	bool ok;
	float val;
	val = p_EditX->text().toFloat(&ok);
	if (ok) vtx->x = val;
	val = p_EditY->text().toFloat(&ok);
	if (ok) vtx->y = val;
	val = p_EditZ->text().toFloat(&ok);
	if (ok) vtx->z = val;
	EM_CERR("PolygonView::slotApplyVertex vertex");
      }
    }
  }
  p_Doc->updateAll("polygon");
}


void PolygonView::slotApplyColor() {
  EM_CERR("Polygonview::slotApplyColor");
  bool bVertex = false;
	
  // change selected vertex
  QListViewItemIterator viter(p_VertexListView);
  for (; viter.current(); ++viter) {
    if (viter.current()->isSelected()) {
      bVertex = true;
      if (((ListItem*)viter.current())->getObjectType() == LISTITEM_VERTEX) {
	// 				Color * color = poly->getColor((*coloritem).second);
	// 				assert(color != NULL);
	// 				color->r = p_EditR->text().toFloat();
	// 				color->g = p_EditG->text().toFloat();
	// 				color->b = p_EditB->text().toFloat();
	// 				color->a = p_EditA->text().toFloat();
	EM_CERR("PolygonView::slotApplyColor vertex");
      }
    }
  }

  // change selected polygon only if no vertex was selected
  QListViewItemIterator piter(p_PolygonListView);
  for (; piter.current() && !bVertex; ++piter) {
    if (piter.current()->isSelected()) {
      if (((ListItem*)piter.current())->getObjectType() == LISTITEM_POLYGON) {
	Polygon * poly = (Polygon*)((ListItem*)piter.current())->getObject();
	assert(poly != NULL);
	poly->setColor(p_EditR->text().toFloat(), 
		       p_EditG->text().toFloat(),
		       p_EditB->text().toFloat(), 
		       p_EditA->text().toFloat());
	EM_CERR("PolygonView::slotApplyColor polygon");
      }
    }
  }

  p_Doc->updateAll("polygon");
}

void PolygonView::slotApplyProp() {
  EM_CERR("polygonview::slotapply");
  assert (p_Shape != NULL);
  int index = 0;
  Polygon * poly = p_Doc->getSelectedPolygon(index);
  while (poly != NULL) {
    if (p_TransBox->isChecked()) {
      poly->setProperty(EM_POLY_TRANS);
      EM_CERR("polygon::slotapply - set polygon to transparent");
    } else {
      poly->unsetProperty(EM_POLY_TRANS);
      EM_CERR("polygon::slotapply - unset polygon transparent");
    }
    index++; 
    poly = p_Doc->getSelectedPolygon(index);
  }
  p_Shape->setProperty(EM_SHAPE3D_USE_TRANS);
  p_Doc->updateAll("polygon");
}
