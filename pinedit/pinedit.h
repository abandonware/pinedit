/***************************************************************************
                          pinedit.h  -  description
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

#ifndef PINEDIT_H
#define PINEDIT_H

// qt includes
#include <qapp.h>
#include <qmainwindow.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qprinter.h>
#include <qpainter.h>
#include <qdialog.h>

class PinEditView;
class PinEditDoc;
class QComboBox;
class QSpinBox;
class SnapDialog;
class TextDialog;
class CommandNewVertex;
class CommandSelect;
class CommandUnSelect;
//class CommandNewGroup;
//class CommandNewShape;
class CommandMove;
class CommandMoveGroup;
class CommandRotateGroup;
class CommandRotate;
class CommandRotateLocal;
class CommandAddSelect;
class CommandContext;
class CommandResize;
class CommandResizeLocal;

/** This Class is the base class for the application. It sets up the main
 * window and providing a menubar, toolbar
 * and statusbar. For the main view, an instance of class PinEditView is
 * created which creates the view. */
class PinEditApp : public QMainWindow {
  Q_OBJECT
		
 public:
	PinEditApp();
	~PinEditApp();
	void initActions();
	void initMenuBar();
	void initToolBar();
	void initWorkBar();
	void initStatusBar();
	void initDoc();
	void initView();
	void initCommands();
	
	/** overloaded for Message box on last window exit */
	bool queryExit();
	bool queryModified();

	PinEditDoc * getDoc() { return p_Doc; };
	static PinEditApp * p_CurrentApp;
	
 public slots:
	/** Generate a new document in the actual view */
	void slotFileNew();
	/** Open a document */
	void slotFileOpen();
	/** Save the document */
	void slotFileSave();
	/** Save the document under a different filename*/
	void slotFileSaveAs();
	void slotFileSaveGroup();
/* 	void slotFileSaveShape(); */
	/** Close the actual file */
	void slotFileClose();
	/** Print the actual file */
	void slotFilePrint();
	/** Exits the application */
	void slotFileQuit();
	/** Toggle the toolbar*/
	void slotViewToolBar(bool toggle);
	/** Toggle the statusbar*/
	void slotViewStatusBar(bool toggle);
	/** Ahows an about dlg*/
	void slotHelpAbout();
	void slotTutorial();
	void slotManual();
	
/* 	void slotLoadShape(); */
	void slotUndo();
	void slotLoadGroup();
	void slotNewVertex();
	void slotSelect();
	void slotAddSelect();
	void slotUnSelect();

	void slotMove();
	void slotRotate();
	void slotRotateLocal();
	void slotResize();
	void slotResizeLocal();

	void slotCut();
	void slotCopy();
	void slotPaste();
	void slotMirrorX();
	void slotMirrorY();
	void slotMirrorZ();
	void slotMirrorLocalX();
	void slotMirrorLocalY();
	void slotMirrorLocalZ();
	void slotHideSelected();
	void slotNewPolygon();
	void slotNewGroup();
	void slotNewShape();
	void slotFlip();
	void slotMoveGroup();
	void slotRotateGroup();
	void slotDeleteGroup();
	void slotDeleteShape();
	void slotDeletePolygon();
	void slotDeleteVertex();
	void slotExtrude();
	void slotSnap();
	
/* 	void slotMode(int index); */
	void slotZoom(int index);
	
	void setMode(int mode);
	
 private:
	
	/** view is the main widget which represents your working area. The View
	 * class should handle all events of the view widget.  It is kept empty so
	 * you can create your view according to your application's needs by
	 * changing the view class. */
	PinEditView *p_View;
	/** doc represents your actual document and is created only once. It keeps
	 * information such as filename and does the serialization of your files. */
	PinEditDoc *p_Doc;

	TextDialog *p_TextDialog;
	SnapDialog *p_SnapDialog;
	
	QPopupMenu *fileMenu;
	QPopupMenu *editMenu;
	QPopupMenu *viewMenu;
	QPopupMenu *helpMenu;
	QPopupMenu *workMenu;
	
	/** the main toolbar */
	QToolBar *fileToolbar;
	/** actions for the application initialized in initActions() and used to en/disable them
	 * according to your needs during the program */
	QAction *fileNew;
	QAction *fileOpen;
	QAction *fileSave;
	QAction *fileSaveAs;
	QAction *fileSaveGroup;
/* 	QAction *fileSaveShape; */
	QAction *fileClose;
	QAction *filePrint;
	QAction *fileQuit;
	
	QAction *viewToolBar;
	QAction *viewStatusBar;
	
	QAction *helpAboutApp;
	QAction *helpTutorial;
	QAction *helpManual;
	
	/** the work toolbar */
	QToolBar *workToolbar;
	QActionGroup *workGroup;
	
/* 	QAction *workLoadShape; */
	QAction *workUndo;
	QAction *workLoadGroup;
	QAction *workNewVertex;
	QAction *workSelect;
	QAction *workAddSelect;
	QAction *workUnSelect;
	QAction *workMove;
	QAction *workRotate;
	QAction *workRotateLocal;
	QAction *workResize;
	QAction *workResizeLocal;

	QAction *workMirrorX;
	QAction *workMirrorY;
	QAction *workMirrorZ;
	QAction *workMirrorLocalX;
	QAction *workMirrorLocalY;
	QAction *workMirrorLocalZ;
	QAction *workCopy;
	QAction *workPaste;
	QAction *workHideSelected;
	QAction *workNewPolygon;
	QAction *workNewShape;
	QAction *workNewGroup;
	QAction *workFlip;
	QAction *workMoveGroup;
	QAction *workRotateGroup;
	QAction *workDeleteGroup;
	QAction *workDeleteShape;
	QAction *workDeletePolygon;
	QAction *workDeleteVertex;
	QAction *workExtrude;
	QAction *workSnap;
	
	QComboBox *workMode;
	QSpinBox *workZoom;
	QComboBox *workShapeType;
	
	/** commands */
	CommandContext * p_CommandContext;
	CommandNewVertex * p_CommandNewVertex;
	CommandSelect * p_CommandSelect;
	CommandAddSelect * p_CommandAddSelect;
	CommandUnSelect * p_CommandUnSelect;
	CommandMove * p_CommandMove;
	CommandRotate * p_CommandRotate;
	CommandRotateLocal * p_CommandRotateLocal;
	CommandMoveGroup * p_CommandMoveGroup;
	CommandRotateGroup * p_CommandRotateGroup;
	CommandResize * p_CommandResize;
	CommandResizeLocal * p_CommandResizeLocal;
};

#endif 

