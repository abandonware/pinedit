/***************************************************************************
                          texturedialog.h  -  description
                             -------------------
    begin                : Mon Jul 22 2002
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

#ifndef TEXTUREDIALOG_H
#define TEXTUREDIALOG_H

// general includes
#include <vector>
#include <map>
// qt includes
#include <qdialog.h>
// emilia includes
#include <EMath.h>

class PinEditDoc;
class Group;
class QLineEdit;
class QListViewItem;
class QListView;
class Behavior;
class Polygon;
class QPainter;
class QImage;
class TextureDialog;
class QComboBox;
class Shape3D;

class TextureImageWidget : public QWidget {
	Q_OBJECT
 public:
	TextureImageWidget(QWidget * parent, const char * name, WFlags f);
	~TextureImageWidget();
	void mouseMoveEvent(QMouseEvent * e);
	void paintEvent(QPaintEvent * e);
	void mousePressEvent(QMouseEvent * e);
	void setInit(QImage * image, Shape3D * shape, Polygon * poly, TextureDialog * dialog);
 private:
	void drawPolygon(Polygon * poly);

	TextureDialog * p_TextureDialog;
	TexCoord * m_texCurrent;
	int m_iCurrent;
	Polygon * p_Poly;
	Shape3D * p_Shape;
	QImage * p_Image;
	QPainter * p_Painter;
};

/** @author Henrik Enqvist */
class TextureDialog : public QDialog {
	Q_OBJECT        // must include this if you use Qt signals/slots
 public:
	TextureDialog(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) ;
	~TextureDialog();
	void edit(Shape3D * shape, Polygon * poly, QImage * image);
	void setCurrent(int i);
	void reload(Shape3D * shape, Polygon * poly, QImage * image);
	void rebuild();
 protected slots:
	void slotDone();
	void slotCancel();
	void slotChanged();
	void slotApply();
	void slotSnap();
 private:
	TextureImageWidget * p_TextureImageWidget;
	PinEditDoc * p_Doc;
	QImage * p_QImage;
	Polygon * p_Poly;
	Shape3D * p_Shape;
	QListView * p_ListView;
	QLineEdit * p_EditU;
	QLineEdit * p_EditV;
	QComboBox * p_ComboSnap;
	vector<QListViewItem *> m_vListViewItem;
	map<QListViewItem *, TexCoord *> m_hTexCoord;
};

#endif
