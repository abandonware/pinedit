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
// emilia includes
#include "Private.h"
#include "Group.h"
#include "Engine.h"

// must include config.h after Private.h cause Private.h changes the
// packate name and version
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
	cerr << "PinEditApp::initActions" << endl;

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
 
  fileSaveGroup = new QAction(tr("Save Group"), saveGroupIcon, tr("Save group..."), 0, this);
  fileSaveGroup->setStatusTip(tr("Saves the selected group to a file"));
  fileSaveGroup->setWhatsThis(tr("Save Group\n\nSaves the selected group to a file"));
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

	workLoadGroup = new QAction(tr("Load Group"), loadGroupIcon, tr("Load Group"), 0, this);
  workLoadGroup->setStatusTip(tr("Load a group to the table"));
  workLoadGroup->setWhatsThis(tr("Load Group\n\nUse this to load the 3d groups such as walls"));
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

  workMoveGroup = new QAction(tr("Move Group"), moveGroupIcon, tr("Move Group"), 0, this);
  workMoveGroup->setToggleAction(true);
  workMoveGroup->setStatusTip(tr("Move current group"));
  workMoveGroup->setWhatsThis(tr("Move group\n\n"));
  connect(workMoveGroup, SIGNAL(activated()), this, SLOT(slotMoveGroup()));

  workRotateGroup = new QAction(tr("Rotate Group"), rotateGroupIcon, tr("Rotate Group"), 0, this);
  workRotateGroup->setToggleAction(true);
  workRotateGroup->setStatusTip(tr("Rotate current group"));
  workRotateGroup->setWhatsThis(tr("Rotate group\n\n"));
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

	workNewShape = new QAction(tr("New Shape"), newShapeIcon, tr("New Shape"), 0, this);
	workNewShape->setStatusTip(tr("Creates a new shape in the current group"));
	workNewShape->setWhatsThis(tr("New Shape\n\nFirst select a group in the group tree then create the shape."));
	connect(workNewShape, SIGNAL(activated()), this, SLOT(slotNewShape()));

	workNewGroup = new QAction(tr("New Group"), newGroupIcon, tr("New Group"), 0, this);
	workNewGroup->setStatusTip(tr("Creates a new group in the current group"));
	workNewGroup->setWhatsThis(tr("New Group\n\nFirst select a group in the group tree then create the group. Create the group with the engine as a parent to create a base level group."));
	connect(workNewGroup, SIGNAL(activated()), this, SLOT(slotNewGroup()));

	workDeleteGroup = new QAction(tr("Delete Group"), deleteGroupIcon, 	tr("Delete Group"), 0, this);
	workDeleteGroup->setStatusTip(tr("Deletes the current group"));
	workDeleteGroup->setWhatsThis(tr("Delete Group\n\nFirst select the group in the group tree."));
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
	cerr << "PinEditApp::initMenuBar" << endl;
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

  // menuBar entry helpMenu
  helpMenu = new QPopupMenu();
  helpAboutApp->addTo(helpMenu);
  helpTutorial->addTo(helpMenu);

  // MENUBAR CONFIGURATION
  menuBar()->insertItem(tr("&File"), fileMenu);
	//menuBar()->insertItem(tr("&Edit"), editMenu);
  menuBar()->insertItem(tr("&View"), viewMenu);
  menuBar()->insertItem(tr("&Work"), workMenu);
  menuBar()->insertSeparator();
  menuBar()->insertItem(tr("&Help"), helpMenu);
}

void PinEditApp::initToolBar() {
	cerr << "PinEditApp::initToolBar" << endl;
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
	cerr << "PinEditApp::initWorkBar" << endl;
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
	cerr << "PinEditApp::initStatusBar" << endl;
  ///////////////////////////////////////////////////////////////////
  //STATUSBAR
  statusBar()->message(tr("Ready."), 2000);
}

void PinEditApp::initDoc() {
	cerr << "PinEditApp::initDoc" << endl;
	p_Doc = new PinEditDoc();
}

void PinEditApp::initView() {
	cerr << "PinEditApp::initView" << endl;
  // set the main widget here
	p_View = new PinEditView(this, p_Doc);
  setCentralWidget(p_View);
}

void PinEditApp::initCommands() {
	cerr << "PinEditApp::initCommands" << endl;
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
	cerr << "PinEditApp::queryExit" << endl;
  int exit = QMessageBox::information(this, tr("Quit..."),
             	  	                    tr("Do your really want to quit?"),
              	                      QMessageBox::Ok, QMessageBox::Cancel);
  return (exit == 1);
}

bool PinEditApp::queryModified() {
	cerr << "PinEditApp::queryModified" << endl;
	int discard = QMessageBox::information(this, tr("Edited..."),
																				 tr("Document modified but not saved. Discard edits?"),
																				 QMessageBox::Ok, QMessageBox::Cancel);
	return (discard == 1);
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////

void PinEditApp::slotFileNew() {
	cerr << "PinEditApp::slotFilwNew" << endl;
	if (p_Doc->isModified()) {
		if (!this->queryModified()) return;
	}
  statusBar()->message(tr("Creating new file..."));
  p_Doc->newDoc();
  statusBar()->message(tr("Ready."));
}

void PinEditApp::slotFileOpen() {
	cerr << "PinEditApp::slotFileOpen" << endl;
	if (p_Doc->isModified()) {
		if (!this->queryModified()) return;
	}
  statusBar()->message(tr("Opening file..."));
  QString fileName = QFileDialog::getOpenFileName(0,0,this);
  if (!fileName.isEmpty()) {
    p_Doc->load(fileName);
    setCaption(fileName);
    QString message=tr("Loaded document: ")+fileName;
    statusBar()->message(message, 2000);
  } else {
    statusBar()->message(tr("Opening aborted"), 2000);
  }
}

void PinEditApp::slotFileSave() {
	cerr << "PinEditApp::slotFileSave" << endl;
  statusBar()->message(tr("Saving file..."));
	if (p_Doc->getFileName().isEmpty()) {
		this->slotFileSaveAs();
	} else {
		p_Doc->save();
	}
  statusBar()->message(tr("Ready."));
}

void PinEditApp::slotFileSaveAs() {
	cerr << "PinEditApp::slotFileSaveAs" << endl;
  statusBar()->message(tr("Saving file under new filename..."));
  QString fn = QFileDialog::getSaveFileName(0, 0, this);
  if (!fn.isEmpty()) {
    p_Doc->saveAs(fn);
  } else {
    statusBar()->message(tr("Saving aborted"), 2000);
  }
  statusBar()->message(tr("Ready."));
}

void PinEditApp::slotFileSaveGroup() {
	cerr << "PinEditApp::slotFileSaveGroup" << endl;
  statusBar()->message(tr("Saving group in file..."));
	Group * group = p_Doc->getCurrentGroup();
	if (group == NULL) {
		QMessageBox::information( this, "Save Group", "No Group selected.");
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
	cerr << "PinEditApp::slotTutorial" << endl;
	p_TextDialog->setSource("/home/henqvist/Develop/pinedit/doc/tutorial.html");
	p_TextDialog->show();
}

void PinEditApp::slotManual() {
	cerr << "PinEditApp::slotManual" << endl;
	p_TextDialog->setSource("/home/henqvist/Develop/pinedit/doc/manual.html");
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

// void PinEditApp::slotNewLock() {
// }

// void PinEditApp::slotNewCave() {
//}


void PinEditApp::slotUndo() {
	cerr << "PinEditApp::slotUndo" << endl;
	p_Doc->undo();
}

void PinEditApp::slotNewVertex() {
	cerr << "PinEditApp::slotNewVertex" << endl;
// 	this->setMode(EM_SHAPE_MODE);
	p_Doc->setCommand(p_CommandNewVertex);
}

void PinEditApp::slotSelect() {
	cerr << "PinEditApp::slotSelect" << endl;
// 	this->setMode(EM_SHAPE_MODE);
	p_Doc->setCommand(p_CommandSelect);
}

void PinEditApp::slotAddSelect() {
	cerr << "PinEditApp::slotAddSelect" << endl;
// 	this->setMode(EM_SHAPE_MODE);
	p_Doc->setCommand(p_CommandAddSelect);
}

void PinEditApp::slotUnSelect() {
	cerr << "PinEditApp::slotUnselect" << endl;
// 	this->setMode(EM_SHAPE_MODE);
	p_Doc->setCommand(p_CommandUnSelect);
}

void PinEditApp::slotMove() {
	cerr << "PinEditApp::slotMove" << endl;
// 	this->setMode(EM_SHAPE_MODE);
	p_Doc->setCommand(p_CommandMove);
}

void PinEditApp::slotRotate() {
	cerr << "PinEditApp::slotRotate" << endl;
// 	this->setMode(EM_SHAPE_MODE);
	p_Doc->setCommand(p_CommandRotate);
}

void PinEditApp::slotRotateLocal() {
	cerr << "PinEditApp::slotRotateLocal" << endl;
// 	this->setMode(EM_SHAPE_MODE);
	p_Doc->setCommand(p_CommandRotateLocal);
}

void PinEditApp::slotResize() {
	cerr << "PinEditApp::slotResize" << endl;
// 	this->setMode(EM_SHAPE_MODE);
	p_Doc->setCommand(p_CommandResize);
}

void PinEditApp::slotResizeLocal() {
	cerr << "PinEditApp::slotResizeLocal" << endl;
// 	this->setMode(EM_SHAPE_MODE);
	p_Doc->setCommand(p_CommandResizeLocal);
}


void PinEditApp::slotCut() {
  statusBar()->message(tr("Cutting selection..."));
  statusBar()->message(tr("Ready."));
}

void PinEditApp::slotCopy() {
	cerr << "PinEditApp::slotCopy" << endl;
	CommandContext context;
	context.clear();
	context.shape = p_Doc->getCurrentShape();
	if (context.shape != NULL) {
		Command * command = new CommandCopy(p_Doc);
		command->execute(context);
	}
}

void PinEditApp::slotPaste() {
	cerr << "PinEditApp::slotPaste" << endl;
	CommandContext context;
	context.clear();
	context.shape = p_Doc->getCurrentShape();
	if (context.shape != NULL) {
		Command * command = new CommandPaste(p_Doc);
		command->execute(context);
	}
}

void PinEditApp::slotNewPolygon() {
	cerr << "PinEditApp::slotNewPolygon" << endl;
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
	cerr << "PinEditApp::slotHideSelected" << endl;
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
	cerr << "pineditapp::slotflip" << endl;
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

void PinEditApp::slotMoveGroup() {
	cerr << "pinedit::slotmovegroup" << endl;
// 	this->setMode(EM_GROUP_MODE);
	p_Doc->setCommand(p_CommandMoveGroup);
}

void PinEditApp::slotRotateGroup() {
	cerr << "pinedit::slotrotategroup" << endl;
// 	this->setMode(EM_GROUP_MODE);
	p_Doc->setCommand(p_CommandRotateGroup);
}

void PinEditApp::slotNewGroup() {
	cerr << "pineditapp::slotnewgroup" << endl;
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
	cerr << "PinEditApp::slotDeletePolygon" << endl;
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
	cerr << "PinEditApp::slotDeleteVertex" << endl;
}

void PinEditApp::slotDeleteGroup() {
	CommandContext context;
	context.clear();
	context.group = p_Doc->getCurrentGroup();
	if (context.group == NULL) {
		QMessageBox::information( this, "Delete Group", "No Group selected.");
	} else {
		Command * command = new CommandDeleteGroup(p_Doc);
		command->execute(context);
	}
	cerr << "PinEditApp::slotDeleteGroup" << endl;
}

void PinEditApp::slotNewShape() {
	cerr << "PinEditApp::slotNewShape" << endl;
	CommandContext context;
	context.clear();
	context.group = p_Doc->getCurrentGroup();
	if (context.group != NULL) {
		Command * command = new CommandNewShape(p_Doc);
		command->execute(context);
	} else {
		QMessageBox::information( this, "New Polygon", "No Shape selected.");
	}
}

void PinEditApp::slotDeleteShape() {
	cerr << "PinEditApp::slotDeleteShape" << endl;
	CommandContext context;
	context.clear();
	context.shape = p_Doc->getCurrentShape();
	context.group = p_Doc->getCurrentGroup();
	if (context.group == NULL) {
		QMessageBox::information( this, "Delete Shape", "No Group selected.");
	} else if (context.shape == NULL) {
		QMessageBox::information( this, "Delete Shape", "No Shape selected.");
	} else {
		Command * command = new CommandDeleteShape(p_Doc);
		command->execute(context);
	}
}

// void PinEditApp::slotMode(int index) {
// 	cerr << "pineditapp::slotmode " << index << endl;
// 	if (index == 0) {
// 		this->setMode(EM_SHAPE_MODE);
// 	} else if (index == 1) {
// 		this->setMode(EM_GROUP_MODE);
// 	}
// }

void PinEditApp::slotZoom(int zoom) {
	cerr << "pineditapp::slotzoom " << zoom << endl;
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
	cerr << "PinEditApp::slotSnap" << endl;
	p_SnapDialog->show();
}

void PinEditApp::slotExtrude() {
	cerr << "PinEditApp::slotExtrude" << endl;
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

