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
#include "texturedialog.h"
#include "texcoorddialog.h"
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
	m_bSelectionChanged = true;
	p_Doc->registerUpdateable(this, "polygon");
	p_Doc->registerRebuildable(this, "polygon");
	p_TextureDialog = new TextureDialog(doc, this, 0, 0);
	p_TexCoordDialog = new TexCoordDialog(doc, this, 0, 0);
	// the polygon list view
	p_PolygonListView = new QListView(this);
	connect(p_PolygonListView, SIGNAL(selectionChanged()), this, SLOT(slotChanged()));
	p_PolygonListView->setSelectionMode(QListView::Extended);
	p_PolygonListView->addColumn(QString("polygons"));
	//p_PolygonListView->setFixedSize(200, 250);
	p_PolygonListView->setMinimumSize(200, 250);
	// the polygon list view
 	p_VertexListView = new QListView(this);
 	connect(p_VertexListView, SIGNAL(selectionChanged()), this, SLOT(slotVertexChanged()));
 	p_VertexListView->setSelectionMode(QListView::Single);
 	p_VertexListView->addColumn(QString("vertices"));
 	//p_VertexListView->setFixedSize(200, 80);
 	p_VertexListView->setMinimumSize(200, 80);
	// tabs and widgets
	QTabWidget * tabWidget = new QTabWidget(this);
	//tabWidget->setFixedSize(200, 70);
	tabWidget->setMinimumSize(200, 70);
	// main layout
  QBoxLayout * vlayout = new QVBoxLayout(this);
	vlayout->addWidget(p_PolygonListView);
	vlayout->addWidget(p_VertexListView);
	vlayout->addWidget(tabWidget);
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
	// texture widget
	{
		QWidget * widget = new QWidget(this);
		tabWidget->addTab(widget, "texture");
		
		p_EditTexture = new QLineEdit(widget);

		p_ChooseButton = new QPushButton("choose", widget);
		connect(p_ChooseButton, SIGNAL(clicked()), this, SLOT(slotChoose()));
		p_NoneButton = new QPushButton("none", widget);
		connect(p_NoneButton, SIGNAL(clicked()), this, SLOT(slotNone()));
		p_TexButton = new QPushButton("edit texcoords", widget);
		connect(p_TexButton, SIGNAL(clicked()), this, SLOT(slotTexCoord()));
		p_AutoButton = new QPushButton("auto texcoords", widget);
		connect(p_AutoButton, SIGNAL(clicked()), this, SLOT(slotAutoTexCoord()));

		QBoxLayout * vlayout = new QVBoxLayout(widget);
		QBoxLayout * hlayout = new QHBoxLayout(vlayout);
		hlayout->addWidget(p_EditTexture);
		hlayout->addWidget(p_ChooseButton);
		hlayout->addWidget(p_NoneButton);
		vlayout->addWidget(p_TexButton);
		vlayout->addWidget(p_AutoButton);
	}

	this->doRebuild();
	//this->doUpdate();
}

PolygonView::~PolygonView(){
}

void PolygonView::doRebuild() {
	cerr << "PolygonView::doRebuild hashed " << endl;
	p_PolygonListView->clear();
	m_hPolyListItem.clear();
	// insert all children
	Shape3D * shape = p_Doc->getCurrentShape();
	this->setShape(shape);
	if (shape != NULL && shape->getTexture() != NULL) {
		p_EditTexture->setText(TextureUtil::getInstance()->getTextureName(shape->getTexture()));
	} else {
		p_EditTexture->setText(QString());
	}

	p_PolygonListView->show();
}

void PolygonView::doUpdate() {
	cerr << "PolygonView::doUpdate" << endl;
	if (p_Shape == NULL) return;
	this->updateSelected();
}

void PolygonView::disableButtons() {
	cerr << "PolygonView::disbleButtons" << endl;
 	p_ButtonUp->setEnabled(false);
 	p_ButtonDown->setEnabled(false);
 	p_ChooseButton->setEnabled(false);
 	p_NoneButton->setEnabled(false);
 	p_TexButton->setEnabled(false);
 	p_AutoButton->setEnabled(false);
 	p_ApplyVertexButton->setEnabled(false);
 	p_ApplyColorButton->setEnabled(false);
 	p_ApplyPropButton->setEnabled(false);
}

/** Adds all groups and shapes to the tree as items. */
void PolygonView::setShape(Shape3D * shape) {
	cerr << "PolygonView::setShape" << endl;
	this->disableButtons();
	p_Shape = shape;
 	if (shape == NULL)  return;
 	p_ChooseButton->setEnabled(true);
 	p_NoneButton->setEnabled(true);

	ListItem * shapeitem = new ListItem(p_PolygonListView, "shape");
	shapeitem->setOpen(TRUE);

 	int polyindex = 0;
	Polygon * poly = shape->getPolygon(polyindex);
	//Polygon * poly = p_Doc->getSelectedPolygon(polyindex);
 	// all polys
 	while (poly != NULL) {
		ListItem * polyitem = new ListItem(shapeitem, QString().setNum(polyindex) + " polygon");
		polyitem->setObject(poly, LISTITEM_POLYGON);
		// hash it
		m_hPolyListItem.insert(pair<Polygon*, ListItem*>(poly, polyitem));
		
		int index = 0;
		int vtxindex = poly->getIndex(index);
		Vertex3D * vtx = shape->getVertex3D(vtxindex);
		Color * color = poly->getColor(index);
		TexCoord * texcoord = poly->getTexCoord(index);
		while (vtx != NULL && false) {
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
			ListItem * vtxitem = new ListItem(polyitem, str);
			vtxitem->setObject(INT2OBJ(vtxindex), LISTITEM_VERTEX);

			index++;
			vtxindex = poly->getIndex(index);
			vtx = shape->getVertex3D(vtxindex);
			color = poly->getColor(index);
			texcoord = poly->getTexCoord(index);
		}
		polyitem->setOpen(FALSE);

 		polyindex++;
 		poly = shape->getPolygon(polyindex);
		//poly = p_Doc->getSelectedPolygon(polyindex);
 	}
}

void PolygonView::updateSelected() {
	cerr << "PolygonView::updateSelected" << endl;
	assert(p_Shape != NULL);
	assert(p_PolygonListView != NULL);
	m_bSelectionChanged = false;
	p_PolygonListView->selectAll(false);
	m_bSelectionChanged = true;
	this->disableButtons();
 	p_ChooseButton->setEnabled(true);
 	p_NoneButton->setEnabled(true);
  // Create an iterator and give the listview as argument
	int index = 0;
	Polygon * poly = p_Doc->getSelectedPolygon(index);
	while (poly != NULL) {
		map<Polygon*, ListItem*>::iterator poly_item = m_hPolyListItem.find(poly);
		assert(poly_item != m_hPolyListItem.end());
		p_ApplyColorButton->setEnabled(true);
		p_ApplyPropButton->setEnabled(true);
		if (p_Shape->getTexture() != NULL) {
			p_TexButton->setEnabled(true);
			p_AutoButton->setEnabled(true);
		}
		m_bSelectionChanged = false;
		(*poly_item).second->setSelected(true);
		m_bSelectionChanged = true;
		++index;
		poly = p_Doc->getSelectedPolygon(index);
	}
	cerr << "PolygonView::updateSelected done" << endl;
}

void PolygonView::findSelected() {
	cerr << "PolygonView::findSelected" << endl;
	assert(p_Shape != NULL);
	this->disableButtons();
 	p_ChooseButton->setEnabled(true);
	p_NoneButton->setEnabled(true);
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
				if (p_Shape->getTexture() != NULL) {
					p_TexButton->setEnabled(true);
					p_AutoButton->setEnabled(true);
				}
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
				cerr << "PolygonView::findSelected selected a polygon" << endl;
			}
			// if it was a vertex, set x,y,z and enable some buttons
			if (((ListItem*)iter.current())->getObjectType() == LISTITEM_VERTEX) {
				p_ButtonUp->setEnabled(true);
				p_ButtonDown->setEnabled(true);
				p_ApplyVertexButton->setEnabled(true);
				Vertex3D * vtx = p_Shape->getVertex3D(OBJ2INT(((ListItem*)iter.current())->getObject()));
				p_Doc->selectVertex(OBJ2INT(((ListItem*)iter.current())->getObject()));
				p_EditX->setText(QString().setNum(vtx->x));
				p_EditY->setText(QString().setNum(vtx->y));
				p_EditZ->setText(QString().setNum(vtx->z));
				cerr << "PolygonView::findSelected selected a vertex" << endl;
			}
		}
	}
}

void PolygonView::slotVertexUp() {
	cerr << "PolygonView::slotVertexUp" << endl;
	assert(p_Shape != NULL);
	QListViewItemIterator iter(p_PolygonListView);
	// iterate through all items of the listview
	for (; iter.current(); ++iter) {
		if (iter.current()->isSelected()) {
			if (((ListItem*)iter.current())->getObjectType() == LISTITEM_VERTEX) {
				int vtxindex = OBJ2INT(((ListItem*)iter.current())->getObject());
				// the polygon is the parent to the vertex
				ListItem * polyitem = (ListItem*)iter.current()->parent();
				assert(polyitem != NULL);
				assert(polyitem->getObjectType() == LISTITEM_POLYGON);
				Polygon * poly = (Polygon*)polyitem->getObject();
				assert(poly != NULL);
				poly->moveUp(poly->includes(vtxindex));
			}
		}
	}
	p_Doc->updateAll("polygon");
}

void PolygonView::slotVertexDown() {
	cerr << "PolygonView::slotVertexDown" << endl;
	assert(p_Shape != NULL);
	QListViewItemIterator iter(p_PolygonListView);
	// iterate through all items of the listview
	for (; iter.current(); ++iter) {
		if (iter.current()->isSelected()) {
			if (((ListItem*)iter.current())->getObjectType() == LISTITEM_VERTEX) {
				int vtxindex = OBJ2INT(((ListItem*)iter.current())->getObject());
				// the polygon is the parent to the vertex
				ListItem * polyitem = (ListItem*)iter.current()->parent();
				assert(polyitem != NULL);
				assert(polyitem->getObjectType() == LISTITEM_POLYGON);
				Polygon * poly = (Polygon*)polyitem->getObject();
				assert(poly != NULL);
				poly->moveDown(poly->includes(vtxindex));
			}
		}
	}
	p_Doc->updateAll("polygon");
}

void PolygonView::slotVertexChanged() {
 	cerr << "PolygonView::slotVertexChanged" << endl;
	assert(p_PolygonListView != NULL);
	if (!m_bSelectionChanged) return;
	p_Doc->clearSelectedVertex();
	p_Doc->clearSelectedPolygon();
	this->findSelected();
	// texture
	assert(p_Shape != NULL);
	if (p_Shape->getTexture() != NULL) {
		p_EditTexture->setText(TextureUtil::getInstance()->getTextureName(p_Shape->getTexture()));
		if (p_PolygonListView->currentItem() != NULL &&
				((ListItem*)p_PolygonListView->currentItem())->getObjectType() == LISTITEM_POLYGON) {
			QImage * qimage = p_Doc->loadQImage(p_EditTexture->text());
			p_TextureDialog->reload(p_Shape, 
															(Polygon*)((ListItem*)p_PolygonListView->currentItem())->getObject(), qimage);
		}
	} else {
		p_EditTexture->setText(QString());
	}
 	// DO NOT update the view itself
	p_Doc->updateAllExclude("polygon", this);
}

void PolygonView::slotChanged() {
 	cerr << "PolygonView::slotChanged" << endl;
	assert(p_PolygonListView != NULL);
	if (!m_bSelectionChanged) return;
	p_Doc->clearSelectedVertex();
	p_Doc->clearSelectedPolygon();
	this->findSelected();
	// texture
	assert(p_Shape != NULL);
	if (p_Shape->getTexture() != NULL) {
		p_EditTexture->setText(TextureUtil::getInstance()->getTextureName(p_Shape->getTexture()));
		if (p_PolygonListView->currentItem() != NULL &&
				((ListItem*)p_PolygonListView->currentItem())->getObjectType() == LISTITEM_POLYGON) {
			QImage * qimage = p_Doc->loadQImage(p_EditTexture->text());
			p_TextureDialog->reload(p_Shape, 
															(Polygon*)((ListItem*)p_PolygonListView->currentItem())->getObject(), qimage);
		}
	} else {
		p_EditTexture->setText(QString());
	}
 	// DO NOT update the view itself
	p_Doc->updateAllExclude("polygon", this);
}

void PolygonView::slotApplyVertex() {
	cerr << "polygonview::slotvertexchanged" << endl;
	assert(p_Shape != NULL);
  // Create an iterator and give the listview as argument
	QListViewItemIterator iter(p_PolygonListView);
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
				cerr << "PolygonView::slotApplyVertex vertex" << endl;
			}
		}
	}
	p_Doc->updateAll("polygon");
}

void PolygonView::slotChoose() {
	assert(p_Shape != NULL);
  QString filename = QFileDialog::getOpenFileName(0, 0, this);
  if (!filename.isEmpty()) {
    EmTexture * tex = TextureUtil::getInstance()->loadTexture(filename);
		if (tex != NULL) {
			p_Shape->setTexture(tex);
			p_EditTexture->setText(filename);
		}
	}
}

void PolygonView::slotNone() {
	assert(p_Shape != NULL);
	p_Shape->setTexture(NULL);
	p_EditTexture->setText("");
}

void PolygonView::slotTexCoord() {
	cerr << "PolygonView::slotTexCoord" << endl;
	assert(p_Shape != NULL);
	EmTexture * tex = TextureUtil::getInstance()->loadTexture(p_EditTexture->text());
	if (tex != NULL) {
		p_Shape->setTexture(tex);
		// get first selected vertex
		ListItem * current = (ListItem*)p_PolygonListView->currentItem();
		if (current != NULL && current->getObjectType() == LISTITEM_POLYGON) {
			QImage * qimage = p_Doc->loadQImage(p_EditTexture->text());
			p_TextureDialog->edit(p_Shape, (Polygon*)current->getObject(), qimage);
		}
	} else {
		cerr << "PolygonView::slotTexCoord texture NULL" << endl;
	}
}

void PolygonView::slotAutoTexCoord() {
	cerr << "PolygonView::slotAutoTexCoord" << endl;
	assert(p_Shape != NULL);
	EmTexture * tex = TextureUtil::getInstance()->loadTexture(p_EditTexture->text());
	if (tex != NULL) {
		p_Shape->setTexture(tex);
		if (p_Doc->getSelectedPolygon(0) == NULL) {
			QMessageBox::information( this, "Auto TexCoord", "No polygons selected.");
		} else {
			p_TexCoordDialog->show();
		}
	}	
}

void PolygonView::slotApplyColor() {
	cerr << "Polygonview::slotApplyColor" << endl;
  // Create an iterator and give the listview as argument
	QListViewItemIterator iter(p_PolygonListView);
	// iterate through all items of the listview
	for (; iter.current(); ++iter) {
		if (iter.current()->isSelected()) {
			// is it a polygon
			if (((ListItem*)iter.current())->getObjectType() == LISTITEM_POLYGON) {
				//				Polygon * poly = (*polyitem).second;
				Polygon * poly = (Polygon*)((ListItem*)iter.current())->getObject();
				assert(poly != NULL);
				poly->setColor(p_EditR->text().toFloat(), 
											 p_EditG->text().toFloat(),
											 p_EditB->text().toFloat(), 
											 p_EditA->text().toFloat());
				cerr << "PolygonView::slotApplyColor polygon" << endl;
			}
			// if it was a vertex, set rgb
			if (((ListItem*)iter.current())->getObjectType() == LISTITEM_VERTEX) {
// 				Color * color = poly->getColor((*coloritem).second);
// 				assert(color != NULL);
// 				color->r = p_EditR->text().toFloat();
// 				color->g = p_EditG->text().toFloat();
// 				color->b = p_EditB->text().toFloat();
// 				color->a = p_EditA->text().toFloat();
				cerr << "PolygonView::slotApplyColor vertex" << endl;
			}
		}
	}
	p_Doc->updateAll("polygon");
}

void PolygonView::slotApplyProp() {
	cerr << "polygonview::slotapply" << endl;
	assert (p_Shape != NULL);
	int index = 0;
	Polygon * poly = p_Doc->getSelectedPolygon(index);
	while (poly != NULL) {
		if (p_TransBox->isChecked()) {
			poly->setProperty(EM_POLY_TRANS);
			cerr << "polygon::slotapply - set polygon to transparent" << endl;
		} else {
			poly->unsetProperty(EM_POLY_TRANS);
			cerr << "polygon::slotapply - unset polygon transparent" << endl;
		}
		index++; 
		poly = p_Doc->getSelectedPolygon(index);
	}
	p_Shape->setProperty(EM_SHAPE3D_USE_TRANS);
	p_Doc->updateAll("polygon");
}
