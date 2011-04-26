/***************************************************************************
                          textureview.h  -  description
                             -------------------
    begin                : Thy Jul 11 19:39:03 EET 2002
    copyright            : (C) 2002 by Henrik Enqvist IB
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

#ifndef TEXTVIEW_H
#define TEXTVIEW_H

// qt includes
#include <qwidget.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <QPaintEvent>
// application includes
#include "pineditdoc.h"
// emilia includes
#include "EMath.h"

class PinEditDoc;
class Group;
class QLineEdit;
class Q3ListViewItem;
class Q3ListView;
class Behavior;
class Polygon3D;
class QPainter;
class QImage;
class TextureView;
class QComboBox;
class Shape3D;
class TexCoordDialog;

class TextureImageWidget : public QWidget {
	Q_OBJECT
 public:
	TextureImageWidget(PinEditDoc * doc, QWidget * parent, const char * name, Qt::WFlags f);
	~TextureImageWidget();
	void mouseMoveEvent(QMouseEvent * e);
	void paintEvent(QPaintEvent * e);
	void mousePressEvent(QMouseEvent * e);
	void setCurrent(int i);
	void setInit(QImage * image, TextureView * view);
 private:
	void drawPolygon(Polygon3D * poly);

	TextureView * p_TextureView;
	TexCoord * p_texCurrent;
	int m_iCurrent;
	PinEditDoc * p_Doc;
	QImage * p_Image;
	QPainter * p_Painter;
};

class TextureView: public QWidget, public Updateable, public Rebuildable  {
	Q_OBJECT        // must include this if you use Qt signals/slots
 public:
	TextureView(PinEditDoc * doc, QWidget * parent, const char * name, Qt::WFlags f) ;
	~TextureView();
	void doRebuild();
	void doUpdate();
	//void edit(Shape3D * shape, Polygon * poly, QImage * image);
	void setCurrent(int i);
	void rebuild();
 protected slots:
	void slotChanged();
 //void slotApply();
	void slotSnap();
 	void slotChoose();
 	void slotName();
 	void slotAutoTexCoord();
 private:
	QLineEdit * p_EditTexture;
	TexCoordDialog * p_TexCoordDialog;
	TextureImageWidget * p_TextureImageWidget;
	PinEditDoc * p_Doc;
	//Polygon * p_Poly;
	//Shape3D * p_Shape;
	Q3ListView * p_ListView;
	QLineEdit * p_EditU;
	QLineEdit * p_EditV;
	QComboBox * p_ComboSnap;
};

#endif 

