/***************************************************************************
                          pineditview.cpp  -  description
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

// general includes
#include "assert.h"
// qt includes
#include <qtabwidget.h>
#include <qlayout.h>
#include <qgl.h>
#include <qlistbox.h>
#include <qbutton.h>
#include <qsplitter.h>
#include <qcanvas.h>
// application includes
#include "pineditview.h"
#include "glengine.h"
#include "view2d.h"
#include "command.h"
#include "shapeview.h"
#include "polygonview.h"

PinEditView::PinEditView(QWidget * parent, PinEditDoc * doc) : QWidget(parent) {
	assert(doc != NULL);
  // connect doc with the view
  connect(doc, SIGNAL(documentChanged()), this, SLOT(slotDocumentChanged()));
	
//  QHBox * vbox = new QVBox(this);
//	QSplitter *split = new QSplitter(this);
 	
	QGLFormat format;
	format.setDepth(true);
	format.setDoubleBuffer(true);
	p_GLEngine = new GLEngine(format, this, "glengine", doc);
	p_GLEngine->setFixedSize(300, 240); // must set to a fixed size otherwise it disappears

	p_XYView = new View2D(XY, doc, this, 0, 0);
	p_XYView->setFixedSize(300, 240);
	p_XZView = new View2D(XZ, doc, this, 0, 0);
	p_XZView->setFixedSize(300, 240);
	p_ZYView = new View2D(ZY, doc, this, 0, 0);
	p_ZYView->setFixedSize(300, 240);
	
	p_TabWidget = new QTabWidget(this);

	p_ShapeView = new ShapeView(doc, this, 0, 0);
	p_PolygonView = new PolygonView(doc, this, 0, 0);
	p_TabWidget->addTab(p_ShapeView, "shapes");
	p_TabWidget->addTab(p_PolygonView, "polygons");

  QBoxLayout * hlayout = new QHBoxLayout(this);

  QBoxLayout * vlayoutl = new QVBoxLayout(hlayout);
  QBoxLayout * vlayoutm = new QVBoxLayout(hlayout);
  QBoxLayout * vlayoutr = new QVBoxLayout(hlayout);

	vlayoutl->addWidget(p_XYView);		
	vlayoutl->addWidget(p_ZYView);		

	vlayoutm->addWidget(p_XZView);		
	vlayoutm->addWidget(p_GLEngine);

	vlayoutr->addWidget(p_TabWidget);
}

PinEditView::~PinEditView() {
}

void PinEditView::setViewMode(int mode) {
	p_XYView->setMode(mode);
	p_XZView->setMode(mode);
	p_ZYView->setMode(mode);
}

void PinEditView::setZoom(int zoom) {
	p_XYView->setZoom(zoom);
	p_XZView->setZoom(zoom);
	p_ZYView->setZoom(zoom);
}

void PinEditView::slotDocumentChanged() {
	p_ShapeView->doUpdate();
  //TODO update the view
	cerr << "pineditview::slotdocumentchanged" << endl;
}

