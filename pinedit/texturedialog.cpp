/***************************************************************************
                          texturedialog.cpp  -  description
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
// qt includes
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qlistview.h>
#include <qimage.h>
#include <qcombobox.h>
#include <qpainter.h>
// application includes
#include "texturedialog.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "Polygon.h"
#include "Shape3D.h"

TextureImageWidget::TextureImageWidget(QWidget * parent, const char * name, WFlags f) 
: QWidget(parent, name, f) {
	m_iCurrent = 0;
	m_texCurrent = NULL;
	p_Image = NULL;
	p_Poly = NULL;
	p_Shape = NULL;
	this->setFixedSize(256, 256);
	p_Painter = new QPainter(this);
	this->setBackgroundMode(PaletteBase);
}

TextureImageWidget::~TextureImageWidget() {
}

void TextureImageWidget::mouseMoveEvent(QMouseEvent * e) {
	cerr << "TextureImageWidget::mouseMoveEvent" << endl;
}

/* Left mouse button applies, right mouse button sets current texcoord to next. */
void TextureImageWidget::mousePressEvent(QMouseEvent * e) {
	assert(p_Poly != NULL);
	if (e->button() ==  QMouseEvent::LeftButton) {
		m_texCurrent->u = (float)(e->x())/255.0f;
		m_texCurrent->v = (float)(e->y())/255.0f;
		p_TextureDialog->rebuild();
		p_TextureDialog->setCurrent(m_iCurrent);
		cerr << "left mouse pressed in view2d " << m_texCurrent->u <<" "<< m_texCurrent->v << endl;
	} else if (e->button() == QMouseEvent::RightButton) {
		++m_iCurrent;
		m_texCurrent = p_Poly->getTexCoord(m_iCurrent);
		if (m_texCurrent == NULL) {
			m_iCurrent = 0;
			m_texCurrent = p_Poly->getTexCoord(0);
		}
		assert(m_texCurrent != NULL);
		p_TextureDialog->setCurrent(m_iCurrent);
		cerr << "right mouse pressed in view2d" << endl;
	} else if (e->button() == QMouseEvent::MidButton) {
	}
	this->repaint();
}

/* We assume that the polygon has one or more texcoords. */
void TextureImageWidget::setInit(QImage * image, Shape3D * shape, 
																 Polygon * poly, TextureDialog * dialog) { 
	p_TextureDialog = dialog;
	p_Image = image; 
	p_Poly = poly;
	p_Shape = shape;
	m_iCurrent = 0;
	m_texCurrent = poly->getTexCoord(0);
	assert(m_texCurrent != NULL);
}

void TextureImageWidget::drawPolygon(Polygon * poly) {
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

void TextureImageWidget::paintEvent(QPaintEvent * e) {
	assert(p_Image != NULL);
	assert(p_Poly != NULL);
	assert(p_Shape != NULL);
	p_Painter->drawImage(0, 0, *p_Image);
	// draw all polygons in green
	p_Painter->setPen(Qt::green);
	int polyindex = 0;
	Polygon * poly = p_Shape->getPolygon(polyindex);
	while (poly != NULL) {
		this->drawPolygon(poly);
		++polyindex;
		poly = p_Shape->getPolygon(polyindex);
	}
	p_Painter->setPen(Qt::red);
	assert(m_texCurrent != NULL);
	// draw extra rectangle around current texcoord
	p_Painter->drawRect((int)(m_texCurrent->u*255.0f)-2, (int)(m_texCurrent->v*255.0f)-2, 5, 5);
	// draw selected polygon in red
	this->drawPolygon(p_Poly);
	cerr << "TextureDialog::paintEvent drawing " << p_Image->width() <<" "<< p_Image->height() << endl;
}

/* TextureDialog */

TextureDialog::TextureDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) 
: QDialog(parent, name, f) {
	assert(doc != NULL);
	p_Doc = doc;
	p_Poly = NULL;
	p_QImage = NULL;
	p_Shape = NULL;
	// the image
	p_TextureImageWidget = new TextureImageWidget(this, 0, 0);
	// the list view
	p_ListView = new QListView(this);
	connect(p_ListView, SIGNAL(selectionChanged()), this, SLOT(slotChanged()));
	p_ListView->setSelectionMode(QListView::Single);
	p_ListView->addColumn(QString("texcoords"));
	p_ListView->setFixedSize(200, 300);

	p_EditU = new QLineEdit(this);
	connect(p_EditU, SIGNAL(returnPressed()), this, SLOT(slotApply()));
	p_EditV = new QLineEdit(this);
	connect(p_EditV, SIGNAL(returnPressed()), this, SLOT(slotApply()));

	p_ComboSnap = new QComboBox(this);
	p_ComboSnap->insertItem("0.5");
	p_ComboSnap->insertItem("0.25");
	p_ComboSnap->insertItem("0.125");
	p_ComboSnap->insertItem("0.0625");
	p_ComboSnap->insertItem("0.03125");
	p_ComboSnap->insertItem("0.015625");

	QPushButton * snapbutton = new QPushButton("snap", this);
	connect(snapbutton, SIGNAL(clicked()), this, SLOT(slotSnap()));

	QPushButton * applybutton = new QPushButton("apply", this);
	connect(applybutton, SIGNAL(clicked()), this, SLOT(slotApply()));
	QPushButton * donebutton = new QPushButton("done", this);
	connect(donebutton, SIGNAL(clicked()), this, SLOT(slotDone()));

	QBoxLayout * hlayout = new QHBoxLayout(this);
	QBoxLayout * vlayout2 = new QVBoxLayout(hlayout);
	//vlayout2->addWidget(p_Label);
	vlayout2->addWidget(p_TextureImageWidget);
	QBoxLayout * vlayout1 = new QVBoxLayout(hlayout);
	vlayout1->addWidget(p_ListView);
	QBoxLayout * hlayout1 = new QHBoxLayout(vlayout1);
	hlayout1->addWidget(p_EditU);
	hlayout1->addWidget(p_EditV);
	QBoxLayout * hlayout2 = new QHBoxLayout(vlayout1);
	hlayout2->addWidget(p_ComboSnap);
	hlayout2->addWidget(snapbutton);
	vlayout1->addWidget(applybutton);
	vlayout1->addWidget(donebutton);

	cerr << "texturedialog::texturedialog" << endl;
}

TextureDialog::~TextureDialog() {
}

void TextureDialog::setCurrent(int i) {
	assert(p_Poly != NULL);
	if (i < 0 || i >= (signed)m_hTexCoord.size()) return;
	p_ListView->setCurrentItem(m_vListViewItem[i]);
	map<QListViewItem *, TexCoord *>::iterator texitem = m_hTexCoord.find(m_vListViewItem[i]);
	if (texitem != m_hTexCoord.end()) {
		TexCoord * texcoord = (*texitem).second;
		p_EditU->setText(QString().setNum(texcoord->u));
		p_EditV->setText(QString().setNum(texcoord->v));
	}
	p_Doc->selectVertexExtra(p_Poly->getIndex(i));
	cerr << "TextureDialog::slotChanged" << endl;
}

void TextureDialog::rebuild() {
	p_ListView->clear();
	m_hTexCoord.clear();
	m_vListViewItem.clear();
	int texindex = 0;
	TexCoord * texcoord = p_Poly->getTexCoord(texindex);
	while (texcoord != NULL) {
		QString str = QString().setNum(texindex) + " texcoord " +
			QString().setNum(texcoord->u) + " " + QString().setNum(texcoord->v);
		QListViewItem * texitem = new QListViewItem(p_ListView, str);
		//hash it
		m_hTexCoord.insert(pair<QListViewItem *, TexCoord *>(texitem, texcoord));
		m_vListViewItem.push_back(texitem);
		++texindex;
		texcoord = p_Poly->getTexCoord(texindex);
	}
	p_ListView->show();
}

void TextureDialog::reload(Shape3D * shape, Polygon * poly, QImage * image) {
	assert(p_ListView != NULL);
	assert(poly != NULL);
	assert(image != NULL);
	assert(shape != NULL);
	p_TextureImageWidget->setInit(image, shape, poly, this);
	p_QImage = image;
	p_Poly = poly;
	p_Shape = shape;
	this->rebuild();
	p_TextureImageWidget->repaint();
	cerr << "texturedialog::reload hashed " << m_hTexCoord.size() << " texcoords" << endl;
}

void TextureDialog::edit(Shape3D * shape, Polygon * poly, QImage * image) {
	this->reload(shape, poly, image);
	this->setCurrent(0);
	this->show();
}

void TextureDialog::slotChanged() {
	QListViewItem * selected = p_ListView->currentItem();
	map<QListViewItem *, TexCoord *>::iterator texitem = m_hTexCoord.find(selected);
	if (texitem != m_hTexCoord.end()) {
		TexCoord * texcoord = (*texitem).second;
		p_EditU->setText(QString().setNum(texcoord->u));
		p_EditV->setText(QString().setNum(texcoord->v));
	}
	cerr << "TextureDialog::slotChanged" << endl;
}

void TextureDialog::slotSnap() {
	assert(p_Poly != NULL);
	float factor;
	switch (p_ComboSnap->currentItem()) {
	case 0: factor = 0.5f; break;
	case 1: factor = 0.25f; break;
	case 2: factor = 0.125f; break;
	case 3: factor = 0.0625f; break;
	case 4: factor = 0.03125f; break;
	case 5: factor = 0.015625f; break;
	default: factor = 0.5f;
	}

	int texindex = 0;
	TexCoord * texcoord = p_Poly->getTexCoord(texindex);
	while (texcoord != NULL) {
		texcoord->u = (int)(texcoord->u/factor + (texcoord->u > 0 ? 0.5f : -0.5f))*factor;
		texcoord->v = (int)(texcoord->v/factor + (texcoord->v > 0 ? 0.5f : -0.5f))*factor;
		++texindex;
		texcoord = p_Poly->getTexCoord(texindex);
	}
	cerr << "TextureDialog::slotSnap" << endl;
}

void TextureDialog::slotApply() {
	QListViewItem * selected = p_ListView->currentItem();
	map<QListViewItem *, TexCoord *>::iterator texitem = m_hTexCoord.find(selected);
	if (texitem != m_hTexCoord.end()) {
		TexCoord * texcoord = (*texitem).second;
		texcoord->u = p_EditU->text().toFloat();
		texcoord->v = p_EditV->text().toFloat();
	}
	this->rebuild();
	cerr << "TexureDialog::slotApply" << endl;
}

void TextureDialog::slotDone() {
	this->done(0);
	cerr << "TextureDialog::slotDone" << endl;
}

void TextureDialog::slotCancel() {
	this->done(0);
	cerr << "TextureDialog::slotCancel" << endl;
}
