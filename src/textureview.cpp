/***************************************************************************
                          textureview.cpp  -  description
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

#define UNUSED __attribute__((__unused__))

// general includes
#include <cassert>
// qt includes
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>
#include <q3listview.h>
#include <qimage.h>
#include <qcombobox.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <q3filedialog.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3BoxLayout>
#include <QPaintEvent>
#include <QMouseEvent>
#include <Q3VBoxLayout>
// application includes
#include "textureview.h"
#include "pineditdoc.h"
#include "listitem.h"
#include "texcoorddialog.h"
// emilia includes
#include "Private.h"
#include "Polygon.h"
#include "Shape3D.h"

TextureImageWidget::TextureImageWidget(PinEditDoc * doc, QWidget * parent, 
				       const char * name, Qt::WFlags f) : QWidget(parent, name, f) {
  assert(doc != NULL);
  m_iCurrent = 0;
  p_texCurrent = NULL;
  p_Image = NULL;
  p_Doc = doc;
  this->setFixedSize(256, 256);
  p_Painter = new QPainter(this);
  this->setBackgroundMode(Qt::PaletteBase);
}

TextureImageWidget::~TextureImageWidget() {
}

void TextureImageWidget::mouseMoveEvent(QMouseEvent *) {
  EM_CERR("TextureImageWidget::mouseMoveEvent");
}

/* Left mouse button applies, right mouse button sets current texcoord to next. */
void TextureImageWidget::mousePressEvent(QMouseEvent * e) {
  Shape3D * shape = p_Doc->getCurrentShape();
  if (shape == NULL) return;
  if (p_Image == NULL) return;
  if (p_texCurrent == NULL) return;
  if (e->button() ==  Qt::LeftButton) {
    p_texCurrent->u = (float)(e->x())/255.0f;
    p_texCurrent->v = (float)(e->y())/255.0f;
    p_TextureView->rebuild();
    p_TextureView->setCurrent(m_iCurrent);
    EM_CERR("left mouse pressed in view2d " << p_texCurrent->u <<" "<< p_texCurrent->v);
  } else if (e->button() == Qt::RightButton) {
    ++m_iCurrent;
    p_texCurrent = shape->getTexCoord(m_iCurrent);
    if (p_texCurrent == NULL) {
      m_iCurrent = 0;
      p_texCurrent = shape->getTexCoord(0);
    }
    assert(p_texCurrent != NULL);
    p_TextureView->setCurrent(m_iCurrent);
    EM_CERR("right mouse pressed in view2d");
  } else if (e->button() == Qt::MidButton) {
  }
  this->repaint();
}

void TextureImageWidget::setCurrent(int i) {
  Shape3D * shape = p_Doc->getCurrentShape();
  if (shape == NULL) return;
  m_iCurrent = i;
  p_texCurrent = shape->getTexCoord(m_iCurrent);
  if (p_texCurrent == NULL) {
    m_iCurrent = 0;
    p_texCurrent = shape->getTexCoord(0);
  }
  this->repaint();
}

/* We assume that the polygon has one or more texcoords. */
void TextureImageWidget::setInit(QImage * image, TextureView * view) { 
  p_TextureView = view;
  p_Image = image; 
  m_iCurrent = 0;
  p_texCurrent = NULL;
  if (p_Doc->getCurrentShape() != NULL) {
    p_texCurrent = p_Doc->getCurrentShape()->getTexCoord(0);
  }
}

void TextureImageWidget::drawPolygon(Polygon3D * poly) {
  assert(poly != NULL);
  // draw lines between texcoords
  int texindex = 1;
  TexCoord * texcoordbak = poly->getTexCoord(0);
  TexCoord * texcoord = poly->getTexCoord(texindex);
  while (texcoord != NULL) {
    p_Painter->drawLine((int)(texcoordbak->u*255.0f), (int)(texcoordbak->v*255.0f),
			(int)(texcoord->u*255.0f), (int)(texcoord->v*255.0f));
    texcoordbak = texcoord;
    ++texindex;
    texcoord = poly->getTexCoord(texindex);
  }
  // last line
  texcoord = poly->getTexCoord(0);
  assert(texcoordbak != NULL);
  assert(texcoord != NULL);
  p_Painter->drawLine((int)(texcoordbak->u*255.0f), (int)(texcoordbak->v*255.0f), 
		      (int)(texcoord->u*255.0f), (int)(texcoord->v*255.0f));
}

void TextureImageWidget::paintEvent(QPaintEvent *) {
  assert(p_Doc != NULL);
  Shape3D * shape = p_Doc->getCurrentShape();
  if (shape == NULL) return;
  if (p_Image == NULL) return;
  if (p_texCurrent == NULL) return;
  p_Painter->drawImage(0, 0, *p_Image);
  // draw all polygons in green
  p_Painter->setPen(Qt::green);
  int polyindex = 0;
  Polygon3D * poly = shape->getPolygon(polyindex);
  while (poly != NULL) {
    this->drawPolygon(poly);
    ++polyindex;
    poly = shape->getPolygon(polyindex);
  }
  // draw selected polygons in red
  p_Painter->setPen(Qt::red);
  polyindex = 0;
  poly = p_Doc->getSelectedPolygon(polyindex);
  while (poly != NULL) {
    this->drawPolygon(poly);
    ++polyindex;
    poly = p_Doc->getSelectedPolygon(polyindex);
  }
  // draw extra rectangle around current texcoord
  p_Painter->drawRect((int)(p_texCurrent->u*255.0f)-2, (int)(p_texCurrent->v*255.0f)-2, 5, 5);
  EM_CERR("TextureView::paintEvent");
}

/************************************************************/
/* TextureView **********************************************/
/************************************************************/

TextureView::TextureView(PinEditDoc * doc, QWidget * parent, const char * name, Qt::WFlags f) 
  : QWidget(parent, name, f) {
  assert(doc != NULL);
  p_Doc = doc;
  p_Doc->registerUpdateable(this, "polygon");
  p_Doc->registerRebuildable(this, "polygon");
  // dialog
  p_TexCoordDialog = new TexCoordDialog(doc, this, 0, 0);
  // the image
  p_TextureImageWidget = new TextureImageWidget(doc, this, 0, 0);
  // the list view
  p_ListView = new Q3ListView(this);
  connect(p_ListView, SIGNAL(selectionChanged()), this, SLOT(slotChanged()));
  p_ListView->setSelectionMode(Q3ListView::Single);
  p_ListView->addColumn(QString("texcoords"));
  p_ListView->setMinimumSize(240, 60);

  // 	p_EditU = new QLineEdit(this);
  // 	connect(p_EditU, SIGNAL(returnPressed()), this, SLOT(slotApply()));
  // 	p_EditV = new QLineEdit(this);
  // 	connect(p_EditV, SIGNAL(returnPressed()), this, SLOT(slotApply()));

  p_ComboSnap = new QComboBox(this);
  p_ComboSnap->insertItem("0.5");
  p_ComboSnap->insertItem("0.25");
  p_ComboSnap->insertItem("0.125");
  p_ComboSnap->insertItem("0.0625");
  p_ComboSnap->insertItem("0.03125");
  p_ComboSnap->insertItem("0.015625");

  p_EditTexture = new QLineEdit(this);
  connect(p_EditTexture, SIGNAL(returnPressed()), this, SLOT(slotName()));

	QPushButton * choosebutton = new QPushButton("choose", this);
	connect(choosebutton, SIGNAL(clicked()), this, SLOT(slotChoose()));

  // 	QPushButton * applybutton = new QPushButton("apply", this);
  // 	connect(applybutton, SIGNAL(clicked()), this, SLOT(slotApply()));

  QPushButton * snapbutton = new QPushButton("snap", this);
  connect(snapbutton, SIGNAL(clicked()), this, SLOT(slotSnap()));

  QPushButton * autobutton = new QPushButton("auto texcoord", this);
  connect(autobutton, SIGNAL(clicked()), this, SLOT(slotAutoTexCoord()));

  Q3BoxLayout * vlayout = new Q3VBoxLayout(this);
  vlayout->addWidget(p_TextureImageWidget);
  //vlayout1->addWidget(p_ListView);
  vlayout->addWidget(p_ListView);
	Q3BoxLayout * hlayout1 = new Q3HBoxLayout(vlayout);
  hlayout1->addWidget(p_EditTexture);
	hlayout1->addWidget(choosebutton);
  // 	QBoxLayout * hlayout1 = new QHBoxLayout(vlayout);
  // 	hlayout1->addWidget(p_EditU);
  // 	hlayout1->addWidget(p_EditV);
  // 	vlayout->addWidget(applybutton);
  Q3BoxLayout * hlayout2 = new Q3HBoxLayout(vlayout);
  hlayout2->addWidget(p_ComboSnap);
  hlayout2->addWidget(snapbutton);
  vlayout->addWidget(autobutton);

  EM_CERR("textureview::textureview");
}

TextureView::~TextureView() {
}

void TextureView::doRebuild() {
  assert(p_Doc != NULL);
  Shape3D * shape = p_Doc->getCurrentShape();
  QImage * qimage = NULL;
  if (shape != NULL && shape->getTexture() != NULL) {
    p_EditTexture->setText(TextureUtil::getInstance()->getTextureName(shape->getTexture()));
    qimage = p_Doc->loadQImage(p_EditTexture->text());
  } else {
    p_EditTexture->setText(QString());
  }

  p_TextureImageWidget->setInit(qimage, this);
  this->rebuild();
  p_TextureImageWidget->repaint();
}

void TextureView::doUpdate() {
}

void TextureView::setCurrent(int i) {
  EM_CERR("TextureView::setCurrect");
  //assert(p_Poly != NULL);
  //if (i < 0 || i >= (signed)m_hTexCoord.size()) return;
  //p_ListView->setCurrentItem(m_vListViewItem[i]);
  //map<QListViewItem *, TexCoord *>::iterator texitem = m_hTexCoord.find(m_vListViewItem[i]);
  //if (texitem != m_hTexCoord.end()) {
  //	TexCoord * texcoord = (*texitem).second;
  //	p_EditU->setText(QString().setNum(texcoord->u));
  //	p_EditV->setText(QString().setNum(texcoord->v));
  //}
  p_Doc->selectVertexExtra(i);
}

void TextureView::rebuild() {
  EM_CERR("TextureDailog::rebuild");
  assert(p_Doc != NULL);
  p_ListView->clear();
  Shape3D * shape = p_Doc->getCurrentShape();
  if (shape == NULL) {
    p_ListView->show();
    return;
  }

  int vtxindex = 0;
  TexCoord * texcoord = shape->getTexCoord(vtxindex);
  while (texcoord != NULL) {
    QString stri;
    if (vtxindex < 100 && vtxindex >= 10) {
      stri = "0" + QString().setNum(vtxindex);
    } else if (vtxindex < 10) {
      stri = "00" + QString().setNum(vtxindex);
    } else {
      stri = QString().setNum(vtxindex);
    }

    QString str = stri + " texcoord " +	QString().setNum(texcoord->u) + " " + 
      QString().setNum(texcoord->v);
    ListItem * texitem = new ListItem(p_ListView, str);
    // a bit unsafe cause texcoord pointers might change
    texitem->setObject(texcoord, LISTITEM_TEXCOORD);
    //hash it
    // 		m_hTexCoord.insert(pair<QListViewItem *, TexCoord *>(texitem, texcoord));
    // 		m_vListViewItem.push_back(texitem);
    ++vtxindex;
    texcoord = shape->getTexCoord(vtxindex);
  }
  p_ListView->show();
}

void TextureView::slotChanged() {
  EM_CERR("TextureView::slotChanged");
  ListItem * selected = (ListItem*) p_ListView->currentItem();
  if (selected != NULL) {
    assert(selected->getObjectType() == LISTITEM_TEXCOORD);
    assert(selected->getObject() != NULL);
    TexCoord * texcoord = (TexCoord*)selected->getObject();
    assert(texcoord != NULL);
    assert(p_Doc != NULL);
    assert(p_Doc->getCurrentShape() != NULL);
    p_TextureImageWidget->setCurrent(p_Doc->getCurrentShape()->getVertex3DIndex(texcoord));
    // 		p_EditU->setText(QString().setNum(texcoord->u));
    // 		p_EditV->setText(QString().setNum(texcoord->v));
  }
}

void TextureView::slotSnap() {
  assert(p_Doc != NULL);
  Shape3D * shape = p_Doc->getCurrentShape();
  if (shape == NULL) return;
  float factor;
  switch (p_ComboSnap->currentItem()) {
  case 0: factor = 0.5f; break;
  case 1: factor = 0.25f; break;
  case 2: factor = 0.125f; break;
  case 3: factor = 0.0625f; break;
  case 4: factor = 0.03125f; break;
  case 5: factor = 0.015625f; break;
  default: factor = 0.015625f;
  }

  TexCoord * texcoord = shape->getTexCoord(p_Doc->getSelectedVertexExtra());
  if (texcoord != NULL) {
    texcoord->u = (int)(texcoord->u/factor + (texcoord->u > 0 ? 0.5f : -0.5f))*factor;
    texcoord->v = (int)(texcoord->v/factor + (texcoord->v > 0 ? 0.5f : -0.5f))*factor;
  }

  int texindex = 0;
  texcoord = shape->getTexCoord(p_Doc->getSelectedVertex(texindex));
  while (texcoord != NULL) {
    texcoord->u = (int)(texcoord->u/factor + (texcoord->u > 0 ? 0.5f : -0.5f))*factor;
    texcoord->v = (int)(texcoord->v/factor + (texcoord->v > 0 ? 0.5f : -0.5f))*factor;
    ++texindex;
    texcoord = shape->getTexCoord(p_Doc->getSelectedVertex(texindex));
  }
  EM_CERR("TextureView::slotSnap");
}

// void TextureView::slotApply() {
// 	EM_CERR("TexureView::slotApply");
// 	ListItem * selected = (ListItem*) p_ListView->currentItem();
// 	if (selected != NULL) {
// 		assert(selected->getObjectType() == LISTITEM_TEXCOORD);
// 		assert(selected->getObject() != NULL);
// 		TexCoord * texcoord = (TexCoord*) selected->getObject();
// 		texcoord->u = p_EditU->text().toFloat();
// 		texcoord->v = p_EditV->text().toFloat();
// 	}
// 	this->rebuild();
// }

void TextureView::slotChoose() {
  assert(p_Doc != NULL);
  if (p_Doc->getCurrentShape() == NULL) {
    QMessageBox::information( this, "Choose Texture", "No Shape selected.");
    return;
  }
  QString filename = Q3FileDialog::getOpenFileName(0, 0, this);
  if (!filename.isEmpty()) {
    EmTexture * tex = TextureUtil::getInstance()->loadTexture(filename);
    if (tex != NULL) {
      p_Doc->getCurrentShape()->setTexture(tex);
      p_EditTexture->setText(filename);
    }
  }
}

void TextureView::slotName() {
  Shape3D * shape = p_Doc->getCurrentShape();
  if (shape == NULL) {
    QMessageBox::information( this, "Choose Texture", "No Shape selected.");
    return;
  }
  EmTexture * tex = TextureUtil::getInstance()->loadTexture(p_EditTexture->text());
  if (tex != NULL) {
    p_Doc->getCurrentShape()->setTexture(tex);
  } else {
    shape->setTexture(NULL);
  }
}

void TextureView::slotAutoTexCoord() {
  EM_CERR("TextureView::slotAutoTexCoord");
  Shape3D * shape = p_Doc->getCurrentShape();
  if (shape == NULL) {
    return;
  }
  EmTexture * tex = TextureUtil::getInstance()->loadTexture(p_EditTexture->text());
  if (tex != NULL) {
    shape->setTexture(tex);
    if (p_Doc->getSelectedPolygon(0) == NULL) {
      QMessageBox::information( this, "Auto TexCoord", "No polygons selected.");
    } else {
      p_TexCoordDialog->show();
    }
  }	
}
