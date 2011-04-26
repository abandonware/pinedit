/***************************************************************************
                          pineditview.h  -  description
                             -------------------
    begin                : Tue Nov 27 19:39:03 EET 2001
    copyright            : (C) 2001 by Henrik Enqvist IB
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

#ifndef PINEDITVIEW_H
#define PINEDITVIEW_H

#include <qwidget.h>

#include "pineditdoc.h"

class QMainWindow;
class QListBox;
class QTabWidget;

class GLEngine;
class View2D;
class ShapeView;
class PolygonView;
class TextureView;

#define EM_SHAPE_MODE 1
#define EM_GROUP_MODE 2

/** @author Henrik Enqvist IB */
class PinEditView : public QWidget {
  Q_OBJECT
 public:
	PinEditView(QWidget * parent, PinEditDoc * doc);
	~PinEditView();
	void setViewMode(int mode);
	void setZoom(int zoom);
	ShapeView * getShapeView() { return p_ShapeView; };
	PolygonView * getPolygonView() { return p_PolygonView; };

	static PinEditView * p_CurrentView;
  
 protected slots:
	void slotDocumentChanged();
	
 private:
	View2D * p_XYView;
	View2D * p_XZView;
	View2D * p_ZYView;
	QTabWidget * p_TabWidget;
	ShapeView * p_ShapeView;
	PolygonView * p_PolygonView;
	TextureView * p_TextureView;
	GLEngine * p_GLEngine;
};

#endif
