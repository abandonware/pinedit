/***************************************************************************
                          pinedit.cpp  -  description
                             -------------------
    begin                : Tue Nov 27 19:39:03 EET 2001
    copyright            : (C) 2001 by Henrik Enqvist
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

// qt includes
#include <qaccel.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qpixmap.h>
#include <qstring.h>
#include <qstatusbar.h>
#include <qwhatsthis.h>
#include <qmsgbox.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
// application includes
#include "pineditview.h"
#include "pineditdoc.h"
#include "pinedit.h"
#include "snapdialog.h"
#include "textdialog.h"
// pixmaps
#include "filesave.xpm"
#include "fileopen.xpm"
#include "filenew.xpm"
#include "filesavegroup.xpm"
// #include "filesaveshape.xpm"
// #include "workloadshape.xpm"
#include "editicon.xpm"
#include "manual.xpm"
#include "tutorial.xpm"
#include "workloadgroup.xpm"
#include "worknewvertex.xpm"
#include "workselect.xpm"
#include "workaddselect.xpm"
#include "workunselect.xpm"
#include "worknewpolygon.xpm"
#include "worknewshape.xpm"
#include "worknewgroup.xpm"
#include "workmove.xpm"
#include "workflip.xpm"
#include "workmovegroup.xpm"
#include "workrotategroup.xpm"
#include "workrotate.xpm"
#include "workrotatelocal.xpm"
#include "workdeletegroup.xpm"
#include "workdeleteshape.xpm"
#include "workdeletepolygon.xpm"
#include "workdeletevertex.xpm"
#include "worksnap.xpm"
#include "workresize.xpm"
#include "workresizelocal.xpm"
#include "workextrude.xpm"
#include "workhideselected.xpm"
#include "workundo.xpm"
#include "workcopy.xpm"
#include "workpaste.xpm"
#include "workmirrorx.xpm"
#include "workmirrory.xpm"
#include "workmirrorz.xpm"
#include "workmirrorlocalx.xpm"
#include "workmirrorlocaly.xpm"
#include "workmirrorlocalz.xpm"
// commands
#include "command.h"
#include "commandhideselected.h"
#include "commandnewvertex.h"
#include "commandselect.h"
#include "commandaddselect.h"
#include "commandcopy.h"
#include "commandpaste.h"
#include "commandnewpolygon.h"
#include "commandunselect.h"
#include "commandnewgroup.h"
#include "commandnewshape.h"
#include "commandmove.h"
#include "commandrotate.h"
#include "commandflip.h"
#include "commandmovegroup.h"
#include "commandrotategroup.h"
#include "commandrotatelocal.h"
#include "commanddeletegroup.h"
#include "commanddeleteshape.h"
#include "commanddeletepolygon.h"
#include "commanddeletevertex.h"
#include "commandsnap.h"
#include "commandresize.h"
#include "commandresizelocal.h"
#include "commandextrude.h"
#include "commandmirror.h"
#include "commandmirrorlocal.h"
// emilia includes
#include "Private.h"
#include "Group.h"
#include "Engine.h"

// must include editconfig.h after Private.h cause Private.h changes the
// package name and version
#ifdef HAVE_CONFIG_H
#include "editconfig.h"
#endif

PinEditApp * PinEditApp::p_CurrentApp = NULL;

PinEditApp::PinEditApp() : QMainWindow() {
  setCaption(tr("PinEdit " VERSION));
	p_CurrentApp = this;

  ///////////////////////////////////////////////////////////////////
  // call inits to invoke all other construction parts
 	initActions();
  initMenuBar();
  initToolBar();
  initWorkBar();
  initStatusBar();

  initDoc();
	initView();
	this->setMode(EM_GROUP_MODE);
	// initdoc must be called before initcommands
	initCommands();

  viewToolBar->setOn(true);
  viewStatusBar->setOn(true);
}

PinEditApp::~PinEditApp() {
}

/** initializes all QActions of the application */
void PinEditApp::initActions() {
  EM_CERR("PinEditApp::initActions");
  
  QPixmap pineditIcon = QPixmap(editicon);
  QPixmap tutorialIcon = QPixmap(tutorial);
  QPixmap manualIcon = QPixmap(manual);
  QPixmap newIcon = QPixmap(filenew);
  QPixmap openIcon = QPixmap(fileopen);
  QPixmap saveIcon = QPixmap(filesave);
  QPixmap saveGroupIcon = QPixmap(filesavegroup);
  // 	QPixmap saveShapeIcon = QPixmap(filesaveshape);
  
  //QPixmap lockIcon = QPixmap(worklock);
//   QPixmap loadShapeIcon = QPixmap(workloadshape);
  QPixmap loadGroupIcon = QPixmap(workloadgroup);
	//QPixmap caveIcon = QPixmap(workcave);
	QPixmap undoIcon = QPixmap(workundo);
	QPixmap newVertexIcon = QPixmap(worknewvertex);
	QPixmap selectIcon = QPixmap(workselect);
	QPixmap addSelectIcon = QPixmap(workaddselect);
	QPixmap copyIcon = QPixmap(workcopy);
	QPixmap pasteIcon = QPixmap(workpaste);
	QPixmap newPolygonIcon = QPixmap(worknewpolygon);
	QPixmap hideSelectedIcon = QPixmap(workhideselected);
	QPixmap unSelectIcon = QPixmap(workunselect);
	QPixmap newShapeIcon = QPixmap(worknewshape);
	QPixmap newGroupIcon = QPixmap(worknewgroup);
	QPixmap moveIcon = QPixmap(workmove);
	QPixmap flipIcon = QPixmap(workflip);
	QPixmap moveGroupIcon = QPixmap(workmovegroup);
	QPixmap rotateGroupIcon = QPixmap(workrotategroup);
	QPixmap rotateIcon = QPixmap(workrotate);
	QPixmap rotateLocalIcon = QPixmap(workrotatelocal);
	QPixmap deleteGroupIcon = QPixmap(workdeletegroup);
	QPixmap deleteShapeIcon = QPixmap(workdeleteshape);
	QPixmap deletePolygonIcon = QPixmap(workdeletepolygon);
	QPixmap deleteVertexIcon = QPixmap(workdeletevertex);
	QPixmap snapIcon = QPixmap(worksnap);
	QPixmap resizeIcon = QPixmap(workresize);
	QPixmap resizeLocalIcon = QPixmap(workresizelocal);
	QPixmap extrudeIcon = QPixmap(workextrude);
	QPixmap mirrorXIcon = QPixmap(workmirrorx);
	QPixmap mirrorYIcon = QPixmap(workmirrory);
	QPixmap mirrorZIcon = QPixmap(workmirrorz);
	QPixmap mirrorLocalXIcon = QPixmap(workmirrorlocalx);
	QPixmap mirrorLocalYIcon = QPixmap(workmirrorlocaly);
	QPixmap mirrorLocalZIcon = QPixmap(workmirrorlocalz);

  fileNew = new QAction(tr("New File"), newIcon, tr("&New"), QAccel::stringToKey(tr("Ctrl+N")), this);
  fileNew->setStatusTip(tr("Creates a new document"));
  fileNew->setWhatsThis(tr("New File\n\nCreates a new document"));
  connect(fileNew, SIGNAL(activated()), this, SLOT(slotFileNew()));

  fileOpen = new QAction(tr("Open File"), openIcon, tr("&Open..."), 0, this);
  fileOpen->setStatusTip(tr("Opens an existing document"));
  fileOpen->setWhatsThis(tr("Open File\n\nOpens an existing document"));
  connect(fileOpen, SIGNAL(activated()), this, SLOT(slotFileOpen()));

  fileSave = new QAction(tr("Save File"), saveIcon, tr("&Save"), 
												 QAccel::stringToKey(tr("Ctrl+S")), this);
  fileSave->setStatusTip(tr("Saves the actual document"));
  fileSave->setWhatsThis(tr("Save File.\n\nSaves the actual document"));
  connect(fileSave, SIGNAL(activated()), this, SLOT(slotFileSave()));

  fileSaveAs = new QAction(tr("Save File As"), tr("Save &as..."), 0, this);
  fileSaveAs->setStatusTip(tr("Saves the actual document under a new filename"));
  fileSaveAs->setWhatsThis(tr("Save As\n\nSaves the actual document under a new filename"));
  connect(fileSaveAs, SIGNAL(activated()), this, SLOT(slotFileSaveAs()));
 
  fileSaveGroup = new QAction(tr("Save Object"), saveGroupIcon, tr("Save Object..."), 0, this);
  fileSaveGroup->setStatusTip(tr("Saves the selected object to a file"));
  fileSaveGroup->setWhatsThis(tr("Save Object\n\nSaves the selected object to a file"));
  connect(fileSaveGroup, SIGNAL(activated()), this, SLOT(slotFileSaveGroup()));

//   fileSaveShape = new QAction(tr("Save Shape"), saveShapeIcon, tr("Save shape..."), 0, this);
//   fileSaveShape->setStatusTip(tr("Saves the selected shape to a file"));
//   fileSaveShape->setWhatsThis(tr("Save Shape\n\nSaves the selected shape to a file"));
//   connect(fileSaveShape, SIGNAL(activated()), this, SLOT(slotFileSaveShape()));

  fileClose = new QAction(tr("Close File"), tr("&Close"), QAccel::stringToKey(tr("Ctrl+W")), this);
  fileClose->setStatusTip(tr("Closes the actual document"));
  fileClose->setWhatsThis(tr("Close File\n\nCloses the actual document"));
  connect(fileClose, SIGNAL(activated()), this, SLOT(slotFileClose()));

  filePrint = new QAction(tr("Print File"), tr("&Print"), QAccel::stringToKey(tr("Ctrl+P")), this);
  filePrint->setStatusTip(tr("Prints out the actual document"));
  filePrint->setWhatsThis(tr("Print File\n\nPrints out the actual document"));
  connect(filePrint, SIGNAL(activated()), this, SLOT(slotFilePrint()));

  fileQuit = new QAction(tr("Exit"), tr("E&xit"), QAccel::stringToKey(tr("Ctrl+Q")), this);
  fileQuit->setStatusTip(tr("Quits the application"));
  fileQuit->setWhatsThis(tr("Exit\n\nQuits the application"));
  connect(fileQuit, SIGNAL(activated()), this, SLOT(slotFileQuit()));

  viewToolBar = new QAction(tr("Toolbar"), tr("Tool&bar"), 0, this, 0, true);
  viewToolBar->setStatusTip(tr("Enables/disables the toolbar"));
  viewToolBar->setWhatsThis(tr("Toolbar\n\nEnables/disables the toolbar"));
  connect(viewToolBar, SIGNAL(toggled(bool)), this, SLOT(slotViewToolBar(bool)));

  viewStatusBar = new QAction(tr("Statusbar"), tr("&Statusbar"), 0, this, 0, true);
  viewStatusBar->setStatusTip(tr("Enables/disables the statusbar"));
  viewStatusBar->setWhatsThis(tr("Statusbar\n\nEnables/disables the statusbar"));
  connect(viewStatusBar, SIGNAL(toggled(bool)), this, SLOT(slotViewStatusBar(bool)));

  helpAboutApp = new QAction(tr("About"), pineditIcon, tr("&About..."), 0, this);
  helpAboutApp->setStatusTip(tr("About the application"));
  helpAboutApp->setWhatsThis(tr("About\n\nAbout the application"));
  connect(helpAboutApp, SIGNAL(activated()), this, SLOT(slotHelpAbout()));

  helpTutorial = new QAction(tr("Tutorial"), tutorialIcon, tr("Tutorial..."), 0, this);
  helpTutorial->setStatusTip(tr("Tutorial for the editor"));
  helpTutorial->setWhatsThis(tr("Tutorial\n\nTutorial for the editor"));
  connect(helpTutorial, SIGNAL(activated()), this, SLOT(slotTutorial()));

  helpManual = new QAction(tr("Manual"), manualIcon, tr("Manual..."), 0, this);
  helpManual->setStatusTip(tr("Manual for the editor"));
  helpManual->setWhatsThis(tr("Manual\n\nManual for the editor"));
  connect(helpManual, SIGNAL(activated()), this, SLOT(slotManual()));

	workLoadGroup = new QAction(tr("Load Object"), loadGroupIcon, tr("Load Object"), 0, this);
  workLoadGroup->setStatusTip(tr("Loads an object to the table"));
  workLoadGroup->setWhatsThis(tr("Load Object\n\nLoads an object to the table"));
  connect(workLoadGroup, SIGNAL(activated()), this, SLOT(slotLoadGroup()));

  // work actions
	workGroup = new QActionGroup(this);

// 	workLoadShape = new QAction(tr("Load Shape"), loadShapeIcon, tr("Load Shape"), 0, this);
//   workLoadShape->setStatusTip(tr("Load a shape to the table"));
//   workLoadShape->setWhatsThis(tr("Load Shape\n\nUse this to load 3d shapes such as walls"));
//   connect(workLoadShape, SIGNAL(activated()), this, SLOT(slotLoadShape()));

//  	workLock = new QAction(tr("New Lock"), lockIcon, tr("New Lock"), 0, this);
//   workLock->setStatusTip(tr("Add a lock the game"));
//   workLock->setWhatsThis(tr("New Lock\n\nUse this to create locks for multiballs"));
//   connect(workLock, SIGNAL(activated()), this, SLOT(slotNewLock()));

//  	workCave = new QAction(tr("New Cave"), caveIcon, tr("New Cave"), 0, this);
//   workCave->setStatusTip(tr("Add a cave the game"));
//   workCave->setWhatsThis(tr("New Cave\n\nUse this to create a cave that captures the balls for a while and then shoots it out"));
//   connect(workCave, SIGNAL(activated()), this, SLOT(slotNewCave()));

 	workUndo = new QAction(tr("Undo"), undoIcon, tr("Undo"), 0, this);
  workUndo->setStatusTip(tr("Undo recent action"));
  workUndo->setWhatsThis(tr("Undo\n\nUndo recent action."));
  connect(workUndo, SIGNAL(activated()), this, SLOT(slotUndo()));

 	workNewVertex = new QAction(tr("New Vertex"), newVertexIcon, tr("New Vertex"), 0, this);
 	workNewVertex->setToggleAction(true);
  workNewVertex->setStatusTip(tr("Add a vertex to the current shape"));
  workNewVertex->setWhatsThis(tr("New Vertex\n\nCreates a vertex."));
  connect(workNewVertex, SIGNAL(activated()), this, SLOT(slotNewVertex()));

  workSelect = new QAction(tr("Select"), selectIcon, tr("Select"), 0, this);
  workSelect->setToggleAction(true);
  workSelect->setStatusTip(tr("Selects vertices in the current shape"));
  workSelect->setWhatsThis(tr("Select Vertices\n\nSelect vertices."));
  connect(workSelect, SIGNAL(activated()), this, SLOT(slotSelect()));

  workAddSelect = new QAction(tr("AddSelect"), addSelectIcon, tr("AddSelect"), 0, this);
  workAddSelect->setToggleAction(true);
  workAddSelect->setStatusTip(tr("Selects vertices in the current shape"));
  workAddSelect->setWhatsThis(tr("Select Vertices\n\nMerges the old selection with the newly selected vertices."));
  connect(workAddSelect, SIGNAL(activated()), this, SLOT(slotAddSelect()));

  workUnSelect = new QAction(tr("UnSelect"), unSelectIcon, tr("UnSelect"), 0, this);
  workUnSelect->setToggleAction(true);
  workUnSelect->setStatusTip(tr("Unselects selected vertices"));
  workUnSelect->setWhatsThis(tr("Unselect vertices\n\nUnselect vertices."));
  connect(workUnSelect, SIGNAL(activated()), this, SLOT(slotUnSelect()));

//   workCut = new QAction(tr("Cut"), cutIcon, tr("Cu&t"), QAccel::stringToKey(tr("Ctrl+X")), this);
//   workCut->setStatusTip(tr("Cuts the selected section and puts it to the clipboard"));
//   workCut->setWhatsThis(tr("Cut\n\nCuts the selected section and puts it to the clipboard"));
//   connect(workCut, SIGNAL(activated()), this, SLOT(slotCut()));

  workCopy = new QAction(tr("Copy"), copyIcon, tr("&Copy"), 
												 QAccel::stringToKey(tr("Ctrl+C")), this);
  workCopy->setStatusTip(tr("Copies the selected section to the clipboard"));
  workCopy->setWhatsThis(tr("Copy\n\nCopies the selected section to the clipboard"));
  connect(workCopy, SIGNAL(activated()), this, SLOT(slotCopy()));

  workPaste = new QAction(tr("Paste"), pasteIcon, tr("&Paste"), 
													QAccel::stringToKey(tr("Ctrl+V")), this);
  workPaste->setStatusTip(tr("Pastes the clipboard contents to actual position"));
  workPaste->setWhatsThis(tr("Paste\n\nPastes the clipboard contents to actual position"));
  connect(workPaste, SIGNAL(activated()), this, SLOT(slotPaste()));

  workMove = new QAction(tr("Move"), moveIcon, tr("Move"), 0, this);
  workMove->setToggleAction(true);
  workMove->setStatusTip(tr("Move selected vertices"));
  workMove->setWhatsThis(tr("Move vertices\n\nMove vertices."));
  connect(workMove, SIGNAL(activated()), this, SLOT(slotMove()));

  workRotate = new QAction(tr("Rotate"), rotateIcon, tr("Rotate"), 0, this);
  workRotate->setToggleAction(true);
  workRotate->setStatusTip(tr("Rotate selected vertices"));
  workRotate->setWhatsThis(tr("Rotate vertices\n\nRotates vertices around the main origo."));
  connect(workRotate, SIGNAL(activated()), this, SLOT(slotRotate()));

  workRotateLocal = new QAction(tr("RotateLocal"), rotateLocalIcon, tr("RotateLocal"), 0, this);
  workRotateLocal->setToggleAction(true);
  workRotateLocal->setStatusTip(tr("RotateLocal selected vertices"));
  workRotateLocal->setWhatsThis(tr("RotateLocal vertices\n\nRotates vertices around the local origo."));
  connect(workRotateLocal, SIGNAL(activated()), this, SLOT(slotRotateLocal()));

  workResize = new QAction(tr("Resize"), resizeIcon, tr("Resize"), 0, this);
  workResize->setToggleAction(true);
  workResize->setStatusTip(tr("Resize selected vertices"));
  workResize->setWhatsThis(tr("Resize vertices\n\nScales vertices around origo."));
  connect(workResize, SIGNAL(activated()), this, SLOT(slotResize()));

  workResizeLocal = new QAction(tr("ResizeLocal"), resizeLocalIcon, tr("ResizeLocal"), 0, this);
  workResizeLocal->setToggleAction(true);
  workResizeLocal->setStatusTip(tr("ResizeLocal selected vertices"));
  workResizeLocal->setWhatsThis(tr("Resize vertices\n\nScales vertices around the local origo."));
  connect(workResizeLocal, SIGNAL(activated()), this, SLOT(slotResizeLocal()));

  workMoveGroup = new QAction(tr("Move Object"), moveGroupIcon, tr("Move Object"), 0, this);
  workMoveGroup->setToggleAction(true);
  workMoveGroup->setStatusTip(tr("Move current object"));
  workMoveGroup->setWhatsThis(tr("Move Object\n\n"));
  connect(workMoveGroup, SIGNAL(activated()), this, SLOT(slotMoveGroup()));

  workRotateGroup = new QAction(tr("Rotate Object"), rotateGroupIcon, tr("Rotate Object"), 0, this);
  workRotateGroup->setToggleAction(true);
  workRotateGroup->setStatusTip(tr("Rotate current object"));
  workRotateGroup->setWhatsThis(tr("Rotate Object\n\n"));
  connect(workRotateGroup, SIGNAL(activated()), this, SLOT(slotRotateGroup()));

  workHideSelected = new QAction(tr("Hide Selected Vertices"), hideSelectedIcon, tr("Hide Selected Vertices"), 0, this);
  workHideSelected->setStatusTip(tr("Hides selected vertices"));
  workHideSelected->setWhatsThis(tr("Hide Selected Vertcies\n\nHides selected vertices and ..."));
  connect(workHideSelected, SIGNAL(activated()), this, SLOT(slotHideSelected()));

  workNewPolygon = new QAction(tr("New Polygon"), newPolygonIcon, tr("New Polygon"), 0, this);
  workNewPolygon->setStatusTip(tr("Creates a new polygon from the selected vertices"));
  workNewPolygon->setWhatsThis(tr("New Polygon\n\nFirst select vertices then connect them to polygons to create shapes."));
  connect(workNewPolygon, SIGNAL(activated()), this, SLOT(slotNewPolygon()));

  workFlip = new QAction(tr("Flip Polygons"), flipIcon, tr("Flip Polygons"), 0, this);
  workFlip->setStatusTip(tr("Flip polygons to make the other side visible"));
  workFlip->setWhatsThis(tr("Flip Polygons\n\n"));
  connect(workFlip, SIGNAL(activated()), this, SLOT(slotFlip()));

  workExtrude = new QAction(tr("Extrude"), extrudeIcon, tr("Extrude"), 0, this);
  workExtrude->setStatusTip(tr("Extrude selected vertices"));
  workExtrude->setWhatsThis(tr("Extrude vertices\n\nExtrude vertices."));
  connect(workExtrude, SIGNAL(activated()), this, SLOT(slotExtrude()));

  workMirrorX = new QAction(tr("Mirror"), mirrorXIcon, tr("Mirror"), 0, this);
  workMirrorX->setStatusTip(tr("Mirror selected vertices"));
  workMirrorX->setWhatsThis(tr("Mirror vertices\n\nMirror vertices."));
  connect(workMirrorX, SIGNAL(activated()), this, SLOT(slotMirrorX()));

  workMirrorY = new QAction(tr("Mirror"), mirrorYIcon, tr("Mirror"), 0, this);
  workMirrorY->setStatusTip(tr("Mirror selected vertices"));
  workMirrorY->setWhatsThis(tr("Mirror vertices\n\nMirror vertices."));
  connect(workMirrorY, SIGNAL(activated()), this, SLOT(slotMirrorY()));

  workMirrorZ = new QAction(tr("Mirror"), mirrorZIcon, tr("Mirror"), 0, this);
  workMirrorZ->setStatusTip(tr("Mirror selected vertices"));
  workMirrorZ->setWhatsThis(tr("Mirror vertices\n\nMirror vertices."));
  connect(workMirrorZ, SIGNAL(activated()), this, SLOT(slotMirrorZ()));

  workMirrorLocalX = new QAction(tr("MirrorLocal"), mirrorLocalXIcon, tr("MirrorLocal"), 0, this);
  workMirrorLocalX->setStatusTip(tr("MirrorLocal selected vertices"));
  workMirrorLocalX->setWhatsThis(tr("MirrorLocal vertices\n\nMirrorLocal vertices."));
  connect(workMirrorLocalX, SIGNAL(activated()), this, SLOT(slotMirrorLocalX()));

  workMirrorLocalY = new QAction(tr("MirrorLocal"), mirrorLocalYIcon, tr("MirrorLocal"), 0, this);
  workMirrorLocalY->setStatusTip(tr("MirrorLocal selected vertices"));
  workMirrorLocalY->setWhatsThis(tr("MirrorLocal vertices\n\nMirrorLocal vertices."));
  connect(workMirrorLocalY, SIGNAL(activated()), this, SLOT(slotMirrorLocalY()));

  workMirrorLocalZ = new QAction(tr("MirrorLocal"), mirrorLocalZIcon, tr("MirrorLocal"), 0, this);
  workMirrorLocalZ->setStatusTip(tr("MirrorLocal selected vertices"));
  workMirrorLocalZ->setWhatsThis(tr("MirrorLocal vertices\n\nMirrorLocal vertices."));
  connect(workMirrorLocalZ, SIGNAL(activated()), this, SLOT(slotMirrorLocalZ()));

	workNewShape = new QAction(tr("New Shape"), newShapeIcon, tr("New Shape"), 0, this);
	workNewShape->setStatusTip(tr("Creates a new shape in the current object"));
	workNewShape->setWhatsThis(tr("New Shape\n\nCreates a new shape in the current object"));
	connect(workNewShape, SIGNAL(activated()), this, SLOT(slotNewShape()));

	workNewGroup = new QAction(tr("New Object"), newGroupIcon, tr("New Object"), 0, this);
	workNewGroup->setStatusTip(tr("Creates a new object"));
	workNewGroup->setWhatsThis(tr("New Group\n\nCreates a new object"));
	connect(workNewGroup, SIGNAL(activated()), this, SLOT(slotNewGroup()));

	workDeleteGroup = new QAction(tr("Delete Object"), deleteGroupIcon,tr("Delete Object"), 0, this);
	workDeleteGroup->setStatusTip(tr("Deletes the current object"));
	workDeleteGroup->setWhatsThis(tr("Delete Object\n\nDeletes the current object"));
	connect(workDeleteGroup, SIGNAL(activated()), this, SLOT(slotDeleteGroup()));

	workDeleteShape = new QAction(tr("Delete Shape"), deleteShapeIcon,	tr("Delete Shape"), 0, this);
	workDeleteShape->setStatusTip(tr("Deletes the current shape"));
	workDeleteShape->setWhatsThis(tr("Delete Shape\n\nFirst select the shape in the group tree."));
	connect(workDeleteShape, SIGNAL(activated()), this, SLOT(slotDeleteShape()));

	workDeletePolygon = new QAction(tr("Delete Polygons"), deletePolygonIcon, 
																	tr("Delete Polygons"), 0, this);
	workDeletePolygon->setStatusTip(tr("Deletes the selected polygons"));
	workDeletePolygon->setWhatsThis(tr("Delete Polygons\n\nDelete the selected polygons."));
	connect(workDeletePolygon, SIGNAL(activated()), this, SLOT(slotDeletePolygon()));

	workDeleteVertex = new QAction(tr("Delete Vertexs"), deleteVertexIcon, 
																	tr("Delete Vertexs"), 0, this);
	workDeleteVertex->setStatusTip(tr("Deletes the selected vertices"));
	workDeleteVertex->setWhatsThis(tr("Delete Vertexs\n\nDelete the selected vertices that are not included in any polygon."));
	connect(workDeleteVertex, SIGNAL(activated()), this, SLOT(slotDeleteVertex()));

	workSnap = new QAction(tr("Snap Vertices"), snapIcon, tr("Snap Vertices"), 0, this);
	workSnap->setStatusTip(tr("Snap vertices"));
	workSnap->setWhatsThis(tr("Snap vertices\n\nSnap vertices."));
	connect(workSnap, SIGNAL(activated()), this, SLOT(slotSnap()));
}

void PinEditApp::initMenuBar() {
  EM_CERR("PinEditApp::initMenuBar");
  // menuBar entry fileMenu
  fileMenu=new QPopupMenu();
  fileNew->addTo(fileMenu);
  fileOpen->addTo(fileMenu);
  fileClose->addTo(fileMenu);
  fileMenu->insertSeparator();
  fileSave->addTo(fileMenu);
  fileSaveAs->addTo(fileMenu);
  fileSaveGroup->addTo(fileMenu);
  // 	fileSaveShape->addTo(fileMenu);
  fileMenu->insertSeparator();
  filePrint->addTo(fileMenu);
  fileMenu->insertSeparator();
  fileQuit->addTo(fileMenu);

  // menuBar entry editMenu
  //editMenu=new QPopupMenu();

  // menuBar entry viewMenu
  viewMenu=new QPopupMenu();
  viewMenu->setCheckable(true);
  viewToolBar->addTo(viewMenu);
  viewStatusBar->addTo(viewMenu);

  // menuBar entry workMenu
  workMenu = new QPopupMenu();
  //   workLoadShape->addTo(workMenu);
  workUndo->addTo(workMenu);
  workNewVertex->addTo(workMenu);
  workSelect->addTo(workMenu);
  workAddSelect->addTo(workMenu);
  workUnSelect->addTo(workMenu);
  workCopy->addTo(workMenu);
  workPaste->addTo(workMenu);
  workMove->addTo(workMenu);
  workRotate->addTo(workMenu);
  workRotateLocal->addTo(workMenu);
  workResize->addTo(workMenu);
  workResizeLocal->addTo(workMenu);
  workCopy->addTo(workMenu);
  workPaste->addTo(workMenu);
  workFlip->addTo(workMenu);
  workHideSelected->addTo(workMenu);
  workNewPolygon->addTo(workMenu);
  workDeletePolygon->addTo(workMenu);
  workDeleteVertex->addTo(workMenu);
  workSnap->addTo(workMenu);
  workMoveGroup->addTo(workMenu);
  workRotateGroup->addTo(workMenu);
  workNewGroup->addTo(workMenu);
  workNewShape->addTo(workMenu);
  workDeleteGroup->addTo(workMenu);
  workDeleteShape->addTo(workMenu);
  workExtrude->addTo(workMenu);
  workMirrorX->addTo(workMenu);
  workMirrorY->addTo(workMenu);
  workMirrorZ->addTo(workMenu);
  workMirrorLocalX->addTo(workMenu);
  workMirrorLocalY->addTo(workMenu);
  workMirrorLocalZ->addTo(workMenu);

  // menuBar entry helpMenu
  helpMenu = new QPopupMenu();
  helpAboutApp->addTo(helpMenu);
  helpTutorial->addTo(helpMenu);
  helpManual->addTo(helpMenu);

  // MENUBAR CONFIGURATION
  menuBar()->insertItem(tr("&File"), fileMenu);
  //menuBar()->insertItem(tr("&Edit"), editMenu);
  menuBar()->insertItem(tr("&View"), viewMenu);
  menuBar()->insertItem(tr("&Work"), workMenu);
  menuBar()->insertSeparator();
  menuBar()->insertItem(tr("&Help"), helpMenu);
}

void PinEditApp::initToolBar() {
  EM_CERR("PinEditApp::initToolBar");
  // TOOLBAR
  fileToolbar = new QToolBar(this, "file operations");
  fileNew->addTo(fileToolbar);
  fileOpen->addTo(fileToolbar);
  fileSave->addTo(fileToolbar);
  fileSaveGroup->addTo(fileToolbar);
  workLoadGroup->addTo(fileToolbar);
  // 	fileSaveShape->addTo(fileToolbar);
  fileToolbar->addSeparator();
  QWhatsThis::whatsThisButton(fileToolbar);
}

void PinEditApp::initWorkBar() {
  EM_CERR("PinEditApp::initWorkBar");
  // WORKBAR
  workToolbar = new QToolBar(this, "work operations");
  // 	workLoadShape->addTo(workToolbar);
  workUndo->addTo(workToolbar);
  workNewVertex->addTo(workToolbar);
  workSelect->addTo(workToolbar);
  workAddSelect->addTo(workToolbar);
  workUnSelect->addTo(workToolbar);
  workMove->addTo(workToolbar);
  workRotate->addTo(workToolbar);
  workRotateLocal->addTo(workToolbar);
  workResize->addTo(workToolbar);
  workResizeLocal->addTo(workToolbar);
  workToolbar->addSeparator();

  workCopy->addTo(workToolbar);
  workPaste->addTo(workToolbar);
  workHideSelected->addTo(workToolbar);
  workFlip->addTo(workToolbar);
  workNewPolygon->addTo(workToolbar);
  workDeletePolygon->addTo(workToolbar);
  workDeleteVertex->addTo(workToolbar);
  workSnap->addTo(workToolbar);
  workExtrude->addTo(workToolbar);
  workMirrorX->addTo(workToolbar);
  workMirrorY->addTo(workToolbar);
  workMirrorZ->addTo(workToolbar);
  workMirrorLocalX->addTo(workToolbar);
  workMirrorLocalY->addTo(workToolbar);
  workMirrorLocalZ->addTo(workToolbar);
  workDeleteShape->addTo(workToolbar);
  workToolbar->addSeparator();

  workMoveGroup->addTo(workToolbar);
  workRotateGroup->addTo(workToolbar);
  workToolbar->addSeparator();

  workNewGroup->addTo(workToolbar);
  workNewShape->addTo(workToolbar);
  workDeleteGroup->addTo(workToolbar);
  workToolbar->addSeparator();

  // 	workMode = new QComboBox(workToolbar);
  // 	workMode->insertItem("shapes");
  // 	workMode->insertItem("groups");
  // 	connect(workMode, SIGNAL(activated(int)), this, SLOT(slotMode(int)));

  workZoom = new QSpinBox(5, 50, 1, workToolbar);
  workZoom->setValue(10);
  connect(workZoom, SIGNAL(valueChanged(int)), this, SLOT(slotZoom(int)));

  workGroup->insert(workNewVertex);
  workGroup->insert(workSelect);
  workGroup->insert(workAddSelect);
  workGroup->insert(workUnSelect);
  workGroup->insert(workMove);
  workGroup->insert(workRotate);
  workGroup->insert(workRotateLocal);
  workGroup->insert(workResize);
  workGroup->insert(workResizeLocal);
  workGroup->insert(workMoveGroup);
  workGroup->insert(workRotateGroup);
}

void PinEditApp::initStatusBar() {
  EM_CERR("PinEditApp::initStatusBar");
  ///////////////////////////////////////////////////////////////////
    //STATUSBAR
    statusBar()->message(tr("Ready."), 2000);
}

void PinEditApp::initDoc() {
  EM_CERR("PinEditApp::initDoc");
  p_Doc = new PinEditDoc();
}

void PinEditApp::initView() {
  EM_CERR("PinEditApp::initView");
  // set the main widget here
  p_View = new PinEditView(this, p_Doc);
  setCentralWidget(p_View);
}

void PinEditApp::initCommands() {
  EM_CERR("PinEditApp::initCommands");
  // create one object for each command here
  // make sure initDoc is called before this
  p_CommandContext = new CommandContext();
  p_CommandNewVertex = new CommandNewVertex(p_Doc);
  p_CommandSelect = new CommandSelect(p_Doc);
  p_CommandAddSelect = new CommandAddSelect(p_Doc);
  p_CommandUnSelect = new CommandUnSelect(p_Doc);
  p_CommandMove = new CommandMove(p_Doc);
  p_CommandRotate = new CommandRotate(p_Doc);
  p_CommandMoveGroup = new CommandMoveGroup(p_Doc);
  p_CommandRotateGroup = new CommandRotateGroup(p_Doc);
  p_CommandRotateLocal = new CommandRotateLocal(p_Doc);
  p_CommandResize = new CommandResize(p_Doc);
  p_CommandResizeLocal = new CommandResizeLocal(p_Doc);

  p_SnapDialog = new SnapDialog(p_Doc, this, 0, 0);
  p_TextDialog = new TextDialog(this, 0, 0);
}

bool PinEditApp::queryExit() {
  EM_CERR("PinEditApp::queryExit");
  int exit = QMessageBox::information(this, tr("Quit..."),
				      tr("Do your really want to quit?"),
              	                      QMessageBox::Ok, QMessageBox::Cancel);
  return (exit == 1);
}

bool PinEditApp::queryModified() {
  EM_CERR("PinEditApp::queryModified");
  int discard = QMessageBox::information(this, tr("Edited..."),
					 tr("Document modified but not saved. Discard edits?"),
					 QMessageBox::Ok, QMessageBox::Cancel);
  return (discard == 1);
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////

void PinEditApp::slotFileNew() {
  EM_CERR("PinEditApp::slotFilwNew");
  if (p_Doc->isModified()) {
    if (!this->queryModified()) return;
  }
  statusBar()->message(tr("Creating new file..."));
  p_Doc->newDoc();
  statusBar()->message(tr("Ready."));
}

void PinEditApp::slotFileOpen() {
  EM_CERR("PinEditApp::slotFileOpen");
  if (p_Doc->isModified()) {
    if (!this->queryModified()) return;
  }
  statusBar()->message(tr("Opening file..."));
  QString fileName = QFileDialog::getOpenFileName(0,0,this);
  if (!fileName.isEmpty()) {
    p_Doc->load(fileName);
    this->setCaption(fileName);
    QString message=tr("Loaded document: ")+fileName;
    statusBar()->message(message, 2000);
  } else {
    statusBar()->message(tr("Opening aborted"), 2000);
  }
}

void PinEditApp::slotFileSave() {
  EM_CERR("PinEditApp::slotFileSave");
  statusBar()->message(tr("Saving file..."));
  if (p_Doc->getFileName().isEmpty()) {
    this->slotFileSaveAs();
  } else {
    p_Doc->save();
  }
  statusBar()->message(tr("Ready."));
}

void PinEditApp::slotFileSaveAs() {
  EM_CERR("PinEditApp::slotFileSaveAs");
  statusBar()->message(tr("Saving file under new filename..."));
  QString fn = QFileDialog::getSaveFileName(0, 0, this);
  if (!fn.isEmpty()) {
    p_Doc->saveAs(fn);
    this->setCaption(fn);
  } else {
    statusBar()->message(tr("Saving aborted"), 2000);
  }
  statusBar()->message(tr("Ready."));
}

void PinEditApp::slotFileSaveGroup() {
  EM_CERR("PinEditApp::slotFileSaveGroup");
  statusBar()->message(tr("Saving group in file..."));
  Group * group = p_Doc->getCurrentGroup();
  if (group == NULL) {
    QMessageBox::information( this, "Save Object", "No object selected.");
  } else {
    QString fn = QFileDialog::getSaveFileName(0, 0, this);
    if (!fn.isEmpty()) {
      p_Doc->saveGroup(fn, group);
    } else {
      statusBar()->message(tr("Saving aborted"), 2000);
    }
  }
  statusBar()->message(tr("Ready."));
}

// void PinEditApp::slotFileSaveShape() {
//   statusBar()->message(tr("Saving shape in file..."));

// 	Shape3D * shape = p_Doc->getCurrentShape();
// 	if (shape == NULL) {
// 		QMessageBox::information( this, "Save Shape", "No Shape selected.");
// 	} else {
// 		QString fn = QFileDialog::getSaveFileName(0, 0, this);
// 		if (!fn.isEmpty()) {
// 			p_Doc->saveShape(fn, shape);
// 		} else {
// 			statusBar()->message(tr("Saving aborted"), 2000);
// 		}
// 	}
//   statusBar()->message(tr("Ready."));
// }

void PinEditApp::slotFileClose() {
  statusBar()->message(tr("Closing file..."));
  statusBar()->message(tr("Ready."));
}

void PinEditApp::slotFilePrint() {
  statusBar()->message(tr("Printing..."));
  QPrinter printer;
  if (printer.setup(this)) {
    QPainter painter;
    painter.begin(&printer);
    ///////////////////////////////////////////////////////////////////
      // TODO: Define printing by using the QPainter methods here
      painter.end();
  };
  statusBar()->message(tr("Ready."));
}

void PinEditApp::slotFileQuit() {
  statusBar()->message(tr("Exiting application..."));
  ///////////////////////////////////////////////////////////////////
    // exits the Application
    if(p_Doc->isModified()) {
      if(queryExit()) {
	qApp->quit();
      } else {
      };
    } else {
      qApp->quit();
    };
    statusBar()->message(tr("Ready."));
}



void PinEditApp::slotViewToolBar(bool toggle) {
  statusBar()->message(tr("Toggle toolbar..."));
  ///////////////////////////////////////////////////////////////////
    // turn Toolbar on or off
    if (toggle== false) {
      fileToolbar->hide();
    } else {
      fileToolbar->show();
    };
    statusBar()->message(tr("Ready."));
}

void PinEditApp::slotViewStatusBar(bool toggle) {
  statusBar()->message(tr("Toggle statusbar..."));
  ///////////////////////////////////////////////////////////////////
    //turn Statusbar on or off
    if (toggle == false) {
      statusBar()->hide();
    } else {
      statusBar()->show();
    }
    statusBar()->message(tr("Ready."));
}

void PinEditApp::slotHelpAbout() {
  QMessageBox::about(this, tr("About..."), 
		     tr("PinEdit\nVersion " VERSION "\n(c) 2001 by Henrik Enqvist") );
}

void PinEditApp::slotTutorial() {
  EM_CERR("PinEditApp::slotTutorial");
  // TODO fix path
  p_TextDialog->setSource(QString(PIN_DATADIR) + "/doc/tutorial.html");
  p_TextDialog->show();
}

void PinEditApp::slotManual() {
  EM_CERR("PinEditApp::slotManual");
  p_TextDialog->setSource(QString(PIN_DATADIR) + "/doc/manual.html");
  p_TextDialog->show();
}

// void PinEditApp::slotLoadShape() {
//   statusBar()->message(tr("Opening file..."));
//   QString fileName = QFileDialog::getOpenFileName(0, 0, this);
//   if (!fileName.isEmpty()) {
//     p_Doc->loadShape(fileName);
//     QString message = tr("Loaded shape: ") + fileName;
//     statusBar()->message(message, 2000);
//   } else {
//     statusBar()->message(tr("Opening aborted"), 2000);
//   }	
// }

void PinEditApp::slotLoadGroup() {
  statusBar()->message(tr("Opening file..."));
  QString fileName = QFileDialog::getOpenFileName(0, 0, this);
  if (!fileName.isEmpty()) {
    p_Doc->loadGroup(fileName);
    QString message = tr("Loaded group: ") + fileName;
    statusBar()->message(message, 2000);
  } else {
    statusBar()->message(tr("Opening aborted"), 2000);
  }	
}

void PinEditApp::slotUndo() {
  EM_CERR("PinEditApp::slotUndo");
  p_Doc->undo();
}

void PinEditApp::slotNewVertex() {
  EM_CERR("PinEditApp::slotNewVertex");
  p_Doc->setCommand(p_CommandNewVertex);
}

void PinEditApp::slotSelect() {
  EM_CERR("PinEditApp::slotSelect");
  p_Doc->setCommand(p_CommandSelect);
}

void PinEditApp::slotAddSelect() {
  EM_CERR("PinEditApp::slotAddSelect");
  p_Doc->setCommand(p_CommandAddSelect);
}

void PinEditApp::slotUnSelect() {
  EM_CERR("PinEditApp::slotUnselect");
  p_Doc->setCommand(p_CommandUnSelect);
}

void PinEditApp::slotMove() {
  EM_CERR("PinEditApp::slotMove");
  p_Doc->setCommand(p_CommandMove);
}

void PinEditApp::slotRotate() {
  EM_CERR("PinEditApp::slotRotate");
  p_Doc->setCommand(p_CommandRotate);
}

void PinEditApp::slotRotateLocal() {
  EM_CERR("PinEditApp::slotRotateLocal");
  p_Doc->setCommand(p_CommandRotateLocal);
}

void PinEditApp::slotResize() {
  EM_CERR("PinEditApp::slotResize");
  p_Doc->setCommand(p_CommandResize);
}

void PinEditApp::slotResizeLocal() {
  EM_CERR("PinEditApp::slotResizeLocal");
  p_Doc->setCommand(p_CommandResizeLocal);
}


void PinEditApp::slotCut() {
  statusBar()->message(tr("Cutting selection..."));
  statusBar()->message(tr("Ready."));
}

void PinEditApp::slotCopy() {
  EM_CERR("PinEditApp::slotCopy");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape != NULL) {
    Command * command = new CommandCopy(p_Doc);
    command->execute(context);
  }
}

void PinEditApp::slotPaste() {
  EM_CERR("PinEditApp::slotPaste");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape != NULL) {
    Command * command = new CommandPaste(p_Doc);
    command->execute(context);
  }
}

void PinEditApp::slotNewPolygon() {
  EM_CERR("PinEditApp::slotNewPolygon");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape != NULL) {
    Command * command = new CommandNewPolygon(p_Doc);
    command->execute(context);
  } else {
    QMessageBox::information( this, "New Polygon", "No Shape selected.");
  }
}

void PinEditApp::slotHideSelected() {
  EM_CERR("PinEditApp::slotHideSelected");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape != NULL) {
    Command * command = new CommandHideSelected(p_Doc);
    command->execute(context);
  } else {
    QMessageBox::information( this, "Hide Selected", "No Shape selected.");
  }
}

void PinEditApp::slotFlip() {
  EM_CERR("pineditapp::slotflip");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape != NULL) {
    Command * command = new CommandFlip(p_Doc);
    command->execute(context);
  } else {
    QMessageBox::information( this, "Flip Polygon", "No Shape selected.");
  }
}

void PinEditApp::slotMirrorX() {
  EM_CERR("PinEditApp::slotMirrorX");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape != NULL) {
    CommandMirror * command = new CommandMirror(p_Doc);
    command->setXYZ(0);
    command->execute(context);
  } else {
    QMessageBox::information( this, "Mirror Polygon", "No Shape selected.");
  }
}

void PinEditApp::slotMirrorY() {
  EM_CERR("PinEditApp::slotMirrorY");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape != NULL) {
    CommandMirror * command = new CommandMirror(p_Doc);
    command->setXYZ(1);
    command->execute(context);
  } else {
    QMessageBox::information( this, "Mirror Polygon", "No Shape selected.");
  }
}

void PinEditApp::slotMirrorZ() {
  EM_CERR("PinEditApp::slotMirrorZ");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape != NULL) {
    CommandMirror * command = new CommandMirror(p_Doc);
    command->setXYZ(2);
    command->execute(context);
  } else {
    QMessageBox::information( this, "Mirror Polygon", "No Shape selected.");
  }
}

void PinEditApp::slotMirrorLocalX() {
  EM_CERR("PinEditApp::slotMirrorLocalX");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape != NULL) {
    CommandMirrorLocal * command = new CommandMirrorLocal(p_Doc);
    command->setXYZ(0);
    command->execute(context);
  } else {
    QMessageBox::information( this, "MirrorLocal Polygon", "No Shape selected.");
  }
}

void PinEditApp::slotMirrorLocalY() {
  EM_CERR("PinEditApp::slotMirrorLocalY");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape != NULL) {
    CommandMirrorLocal * command = new CommandMirrorLocal(p_Doc);
    command->setXYZ(1);
    command->execute(context);
  } else {
    QMessageBox::information( this, "MirrorLocal Polygon", "No Shape selected.");
  }
}

void PinEditApp::slotMirrorLocalZ() {
  EM_CERR("PinEditApp::slotMirrorLocalZ");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape != NULL) {
    CommandMirrorLocal * command = new CommandMirrorLocal(p_Doc);
    command->setXYZ(2);
    command->execute(context);
  } else {
    QMessageBox::information( this, "MirrorLocal Polygon", "No Shape selected.");
  }
}

void PinEditApp::slotMoveGroup() {
  EM_CERR("pinedit::slotmovegroup");
  p_Doc->setCommand(p_CommandMoveGroup);
}

void PinEditApp::slotRotateGroup() {
  EM_CERR("pinedit::slotrotategroup");
  p_Doc->setCommand(p_CommandRotateGroup);
}

void PinEditApp::slotNewGroup() {
  EM_CERR("pineditapp::slotnewgroup");
  CommandContext context;
  context.clear();
  // only add groups to engine
  context.group = p_Doc->getEngine();
  assert(context.group != NULL);
  Command * command = new CommandNewGroup(p_Doc);
  command->execute(context);
}

void PinEditApp::slotDeletePolygon() {
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape == NULL) {
    QMessageBox::information( this, "Delete Polygon", "No Shape selected.");
  } else {
    Command * command = new CommandDeletePolygon(p_Doc);
    command->execute(context);
  }
  EM_CERR("PinEditApp::slotDeletePolygon");
}
 
void PinEditApp::slotDeleteVertex() {
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape == NULL) {
    QMessageBox::information(this, "Delete Vertex", "No Shape selected.");
  } else {
    Command * command = new CommandDeleteVertex(p_Doc);
    command->execute(context);
  }
  EM_CERR("PinEditApp::slotDeleteVertex");
}

void PinEditApp::slotDeleteGroup() {
  CommandContext context;
  context.clear();
  context.group = p_Doc->getCurrentGroup();
  if (context.group == NULL) {
    QMessageBox::information( this, "Delete Object", "No object selected.");
  } else {
    Command * command = new CommandDeleteGroup(p_Doc);
    command->execute(context);
  }
  EM_CERR("PinEditApp::slotDeleteGroup");
}

void PinEditApp::slotNewShape() {
  EM_CERR("PinEditApp::slotNewShape");
  CommandContext context;
  context.clear();
  context.group = p_Doc->getCurrentGroup();
  if (context.group != NULL) {
    Command * command = new CommandNewShape(p_Doc);
    command->execute(context);
  } else {
    QMessageBox::information( this, "New Polygon", "No shape selected.");
  }
}

void PinEditApp::slotDeleteShape() {
  EM_CERR("PinEditApp::slotDeleteShape");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  context.group = p_Doc->getCurrentGroup();
  if (context.group == NULL) {
    QMessageBox::information( this, "Delete Shape", "No object selected.");
  } else if (context.shape == NULL) {
    QMessageBox::information( this, "Delete Shape", "No shape selected.");
  } else {
    Command * command = new CommandDeleteShape(p_Doc);
    command->execute(context);
  }
}

// void PinEditApp::slotMode(int index) {
// 	EM_CERR("pineditapp::slotmode " << index);
// 	if (index == 0) {
// 		this->setMode(EM_SHAPE_MODE);
// 	} else if (index == 1) {
// 		this->setMode(EM_GROUP_MODE);
// 	}
// }

void PinEditApp::slotZoom(int zoom) {
  EM_CERR("pineditapp::slotzoom " << zoom);
  p_View->setZoom(zoom);
  p_Doc->updateAll("polygon");
}

void PinEditApp::setMode(int mode) {
  switch (mode) {
  case EM_SHAPE_MODE:
    p_View->setViewMode(EM_SHAPE_MODE);
    workNewVertex->setEnabled(true);
    workSelect->setEnabled(true);
    workAddSelect->setEnabled(true);
    workUnSelect->setEnabled(true);
    workCopy->setEnabled(true);
    workPaste->setEnabled(true);
    workMove->setEnabled(true);
    workRotate->setEnabled(true);
    workRotateLocal->setEnabled(true);
    workResize->setEnabled(true);
    workResizeLocal->setEnabled(true);
    workHideSelected->setEnabled(true);
    workNewPolygon->setEnabled(true);
    workFlip->setEnabled(true);
    workMirrorX->setEnabled(true);
    workMirrorY->setEnabled(true);
    workMirrorZ->setEnabled(true);
    workMirrorLocalX->setEnabled(true);
    workMirrorLocalY->setEnabled(true);
    workMirrorLocalZ->setEnabled(true);
    workDeletePolygon->setEnabled(true);
    workDeleteVertex->setEnabled(true);
    workSnap->setEnabled(true);
    workExtrude->setEnabled(true);
    workDeleteShape->setEnabled(true);

    workDeleteGroup->setEnabled(false);
    workMoveGroup->setEnabled(false);
    workRotateGroup->setEnabled(false);
    //		workMode->setCurrentItem(0);
    break;
  case EM_GROUP_MODE:
    p_View->setViewMode(EM_GROUP_MODE);
    workNewVertex->setEnabled(false);
    workSelect->setEnabled(false);
    workAddSelect->setEnabled(false);
    workUnSelect->setEnabled(false);
    workCopy->setEnabled(false);
    workPaste->setEnabled(false);
    workMove->setEnabled(false);
    workRotate->setEnabled(false);
    workRotateLocal->setEnabled(false);
    workResize->setEnabled(false);
    workResizeLocal->setEnabled(false);
    workHideSelected->setEnabled(false);
    workNewPolygon->setEnabled(false);
    workFlip->setEnabled(false);
    workMirrorX->setEnabled(false);
    workMirrorY->setEnabled(false);
    workMirrorZ->setEnabled(false);
    workMirrorLocalX->setEnabled(false);
    workMirrorLocalY->setEnabled(false);
    workMirrorLocalZ->setEnabled(false);
    workDeletePolygon->setEnabled(false);
    workDeleteVertex->setEnabled(false);
    workSnap->setEnabled(false);
    workExtrude->setEnabled(false);
    workDeleteShape->setEnabled(false);

    workDeleteGroup->setEnabled(true);
    workMoveGroup->setEnabled(true);
    workRotateGroup->setEnabled(true);
    //		workMode->setCurrentItem(1);
    break;
  }
  p_Doc->updateAll("polygon");
}

void PinEditApp::slotSnap() {
  EM_CERR("PinEditApp::slotSnap");
  p_SnapDialog->show();
}

void PinEditApp::slotExtrude() {
  EM_CERR("PinEditApp::slotExtrude");
  CommandContext context;
  context.clear();
  context.shape = p_Doc->getCurrentShape();
  if (context.shape == NULL) {
    QMessageBox::information( this, "Delete Shape", "No Shape selected.");
  } else {
    Command * command = new CommandExtrude(p_Doc);
    command->execute(context);
  }
}

