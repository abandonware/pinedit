/***************************************************************************
                          polygonview.h  -  description
                             -------------------
    begin                : Wed Apr 10 2002
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

#ifndef POLYGONVIEW_H
#define POLYGONVIEW_H

// general includes
#include <map>
// qt includes
#include <qwidget.h>
// application includes
#include "pineditdoc.h"
#include "listitem.h"
// emilia includes
#include "EMath.h"

class PinEditDoc;
class QListView;
class QListViewItem;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QButtonGroup;
class QCheckBox;
class Polygon;
class Shape3D;
class TextureDialog;
class TexCoordDialog;

#define TRANS_BOX 0x1
#define COLOR     0x2

/** @author Henrik Enqvist IB  */
class PolygonView : public QWidget, public Updateable, public Rebuildable  {
	Q_OBJECT        // must include this if you use Qt signals/slots
 public:
	PolygonView(PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) ;
	~PolygonView();
	void doRebuild();
	void doUpdate();
 public slots:
	void slotVertexChanged();
	void slotChanged();
  void slotApplyVertex();
	void slotApplyColor();
	void slotApplyProp();
	void slotTexCoord();
	void slotChoose();
	void slotNone();
	void slotAutoTexCoord();
	void slotVertexUp();
	void slotVertexDown();
 private:
	void disableButtons();
	void updateSelected();
	void findSelected();
	void setShape(Shape3D * shape);

	bool m_bSelectionChanged;
	PinEditDoc * p_Doc;
	Shape3D * p_Shape;

	TextureDialog * p_TextureDialog;
	TexCoordDialog * p_TexCoordDialog;

	QListView * p_PolygonListView;
	QListView * p_VertexListView;
	QPushButton * p_ButtonUp;
	QPushButton * p_ButtonDown;
	QLineEdit * p_EditX;
	QLineEdit * p_EditY;
	QLineEdit * p_EditZ;
	QLineEdit * p_EditR;
	QLineEdit * p_EditG;
	QLineEdit * p_EditB;
	QLineEdit * p_EditA;
	QCheckBox * p_TransBox;
	QLineEdit * p_EditTexture;
	QPushButton * p_ChooseButton;
	QPushButton * p_NoneButton;
	QPushButton * p_TexButton;
	QPushButton * p_AutoButton;
	QPushButton * p_AutoTexCoord;
	QPushButton * p_ApplyVertexButton;
	QPushButton * p_ApplyColorButton;
	QPushButton * p_ApplyPropButton;

	map<Polygon*, ListItem*> m_hPolyListItem;
};

#endif
