/***************************************************************************
                          pineditdoc.cpp  -  description
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

// qt includes
#include <qimage.h>
#include <qcolor.h>
// application includes
#include "pineditdoc.h"
#include "command.h"
#include "fileutil.h"
// emilia includes
#include "Private.h"
#include "Engine.h"
#include "Camera.h"
#include "Light.h"
#include "Group.h"
#include "Cube.h"
#include "Shape3D.h"
#include "Polygon.h"
#include "Loader.h"
#include "Config.h"
#include "SoundUtil.h"

PinEditDoc::PinEditDoc() : QObject() {
	cerr << "PinEditDoc::PinEditDoc" << endl;
  modified = false;
  p_Command = NULL;
	p_FileUtil = new FileUtil(this);

	this->newDoc();
	// must init sound to be able to load samples?
	//SoundUtil::getInstance()->initSound();

 	p_CurrentGroup = NULL;
	p_CurrentShape = NULL;
}

PinEditDoc::~PinEditDoc() {
	cerr << "PinEditDoc::~PinEditDoc" << endl;
	delete(p_Engine);
	delete(p_FileUtil);
}

void PinEditDoc::newDoc() {
	cerr << "PinEditDoc::newDoc" << endl;
	this->clearSelectedVertex();
	this->clearSelectedPolygon();
	this->setCurrentShape(NULL);
	this->setCurrentGroup(NULL);
	// TODO this will leak memory
 	// Create the engine.
	char * my_argv[] = {"exename", "-externgl", "-size", "300", "240" "-nosound"};
	int my_argc = 5;
  p_Engine = new Engine(my_argc, my_argv);
	p_Engine->setLightning(0.0f, 0.2f);
	p_Engine->setName("#engine");

	// Add a camera. Move a bit.
	Camera* camera = new Camera();
	Light* light = new Light(1, 0, 0);
	p_GroupCameraRot = new Group();
	p_GroupCameraRot->setName("#camera");
	p_GroupCameraTrans = new Group();
	p_GroupCameraTrans->setName("#camera");
	p_Engine->add(p_GroupCameraRot);
	p_GroupCameraRot->add(p_GroupCameraTrans);
	p_GroupCameraTrans->setCamera(camera);
	p_GroupCameraTrans->setLight(light);
	p_GroupCameraTrans->setTranslation(0, 0, 10);
	p_Engine->addLight(light);
	p_Engine->setEngineCamera(p_GroupCameraTrans);

	this->rebuildAll();
	this->updateAll();
}

bool PinEditDoc::save() {
	cerr << "PinEditDoc::save" << endl;
	if (this->getFileName().isEmpty()) {
		cerr << "PinEditDoc::save file name is empty" << endl;
		return false;
	}
	p_FileUtil->saveFile(this->getFileName(), p_Engine);
  return true;
}

bool PinEditDoc::saveAs(const QString &filename) {
	cerr << "PinEditDoc::saveAs" << endl;
	if (filename.isEmpty()) {
		cerr << "PinEditDoc::saveAs file name is empty" << endl;
		return false;
	}
	p_FileUtil->saveFile(filename, p_Engine);
  return true;
}

bool PinEditDoc::saveGroup(const QString & filename, Group * group) {
	cerr << "PinEditDoc::saveGroup" << endl;
	assert(group != NULL);
	if (filename.isEmpty()) {
		cerr << "PinEditDoc::saveGroup file name is empty" << endl;
		return false;
	}
	p_FileUtil->saveFile(filename, group);
	return true;
}

bool PinEditDoc::saveShape(const QString & filename, Shape3D * shape) {
	cerr << "PinEditDoc::saveShape" << endl;
	assert(shape != NULL);
	if (filename.isEmpty()) {
		cerr << "PinEditDoc::saveShape file name is empty" << endl;
		return false;
	}
	return true;
}

bool PinEditDoc::load(const QString &filename) {
	cerr << "PinEditDoc::load" << endl;
	m_sFileName = filename;
	// TODO: fix the data dir problem
	QString dir = filename;
	dir.truncate(filename.findRev('/'));
	cerr << dir << endl;
	this->newDoc();
	Config::getInstance()->setDataDir(dir.latin1());
	Loader::getInstance()->clearSignalVariable();
	Loader::getInstance()->useModules(false);
	Loader::getInstance()->loadFile(filename.latin1(), this->getEngine());
	this->getEngine()->setPropertyRecursive(EM_GROUP_NO_BEHAVIOR);
	p_GroupCameraRot->unsetPropertyRecursive(EM_GROUP_NO_BEHAVIOR);
	this->rebuildAll();
	this->updateAll();
  emit documentChanged();
  return true;
}

const QString & PinEditDoc::getFileName() {
	cerr << "PinEditDoc::getFileName" << endl;
	return m_sFileName;
}

bool PinEditDoc::loadShape(const QString &filename) {
	cerr << "PinEditDoc::loadShape" << endl;
	assert(this->getEngine() != NULL);
	Group * group = this->getCurrentGroup();
	if (group == NULL) {
		cerr << "pineditdoc::loadshape - current group NULL" << endl;
		return false;
	}
	ifstream file(filename);
	istringstream ist("");
	string str;
	file >> str;
	if (str != "shape") {
		cerr << "PinEditDoc::loadShape - file do not parse word 'shape' missing" << endl;
		return false;
	}
	Shape3D * s = Loader::getInstance()->loadShape3DChunk(file, ist);

	if (s == NULL) {
		cerr << "PinEditDoc::loadShape - could not load shape" << endl;
		return false;
	}
	group->addShape3D(s);
	
	this->rebuildAll();
	this->updateAll();
  emit documentChanged();
  return true;
}

bool PinEditDoc::loadGroup(const QString &filename) {
	try {
		Engine * engine = this->getEngine();
		if (engine == NULL) {
			throw string("engine NULL");
		}

		ifstream file(filename);
		if (!file) {
			throw string("Shape3DUtil::load() : file not found: ");
		}
		
		string str;
		istringstream ist("");
		while (file >> str) {
			if (str == "object") {
				Group * group = Loader::getInstance()->loadStdObject(file, ist, engine); 
				group->setPropertyRecursive(EM_GROUP_NO_BEHAVIOR);
				engine->add(group);
			}
		}
		
	} catch (string str){
		cerr << "*************************************************" << endl;
		cerr << "PinEditDoc::loadGroup - caugth exception" << endl;
		cerr << str << endl;
	}

	this->rebuildAll();
	this->updateAll();
  emit documentChanged();
  return true;
}


QImage * PinEditDoc::loadQImage(const QString & filename) {
	// find the image
	map<QString, QImage *>::iterator element = m_hQImage.find(filename);
	if (element != m_hQImage.end()) {
	cerr << "PinEditDoc::loadQImage found image in cache" << endl;
		return (*element).second;
	}
	QImage * image = new QImage(filename);
	m_hQImage.insert(pair<QString, QImage*>(filename, image));
	
	cerr << "PinEditDoc::loadQImage" << endl;
	return image;
}


bool PinEditDoc::isModified() const {
  return modified;
}

void PinEditDoc::pushUndo(Command * command) {
	delete command;
}

void PinEditDoc::setCommand(Command * command) {
	p_Command = command;
}
 
Command * PinEditDoc::buildCommand() {
	if (p_Command == NULL) return NULL;
	return p_Command->build();
}

const char * PinEditDoc::getCommandName() {
	if (p_Command == NULL) return "unknown";
	return p_Command->type();
}

void PinEditDoc::registerUpdateable(Updateable * u) {
	m_vUpdateable.push_back(u);
}

void PinEditDoc::updateAll() {
	cerr << "PinEditDoc::updateAll" << endl;
	vector<Updateable*>::iterator iter = m_vUpdateable.begin();
	vector<Updateable*>::iterator end = m_vUpdateable.end();
	for (; iter != end; ++iter) {
		(*iter)->doUpdate();
	}
	cerr << "PinEditdoc::updateAll updated " << m_vUpdateable.size() << " objects" << endl;
}

void PinEditDoc::updateAllExclude(Updateable * u) {
	vector<Updateable*>::iterator iter = m_vUpdateable.begin();
	vector<Updateable*>::iterator end = m_vUpdateable.end();
	for (; iter != end; ++iter) {
		if ((*iter) != u) { 
			(*iter)->doUpdate();
		}
	}
	cerr << "pineditdoc::updateallexclude updated " << m_vUpdateable.size() << " objects" << endl;
}

void PinEditDoc::registerRebuildable(Rebuildable * r) {
	m_vRebuildable.push_back(r);
}

void PinEditDoc::rebuildAll() {
	vector<Rebuildable*>::iterator iter = m_vRebuildable.begin();
	vector<Rebuildable*>::iterator end = m_vRebuildable.end();
	for (; iter != end; ++iter) {
		(*iter)->doRebuild();
	}
	cerr << "pineditdoc::updateall updated " << m_vRebuildable.size() << " objects" << endl;
}

void PinEditDoc::rebuildAllExclude(Rebuildable * u) {
	vector<Rebuildable*>::iterator iter = m_vRebuildable.begin();
	vector<Rebuildable*>::iterator end = m_vRebuildable.end();
	for (; iter != end; ++iter) {
		if ((*iter) != u) { 
			(*iter)->doRebuild();
		}
	}
	cerr << "pineditdoc::updateallexclude updated " << m_vRebuildable.size() << " objects" << endl;
}

////////////////////////////////////////////////////////////
// Engine functions

Engine * PinEditDoc::getEngine() {
	return p_Engine;
}

Group * PinEditDoc::getCameraRot() {
	return p_GroupCameraRot;
}

Group * PinEditDoc::getCameraTrans() {
	return p_GroupCameraTrans;
}

Shape3D * PinEditDoc::getCurrentShape() {
	return p_CurrentShape;
}

Group * PinEditDoc::getCurrentGroup() {
	return p_CurrentGroup;
}

void PinEditDoc::setCurrentGroup(Group * g) {
	p_CurrentGroup = g;
	if (g == NULL) {
		p_CurrentShape = NULL;
	} else {
		p_CurrentShape = p_CurrentGroup->getShape3D(0);
	}
}

void PinEditDoc::setCurrentShape(Shape3D * s) {
	p_CurrentShape = s;
	if (s == NULL) {
		p_CurrentGroup = NULL;
	} else {
		p_CurrentGroup = s->getParent();
	}
}

/////////////////////////////////////////////////////////////
// vertex functions

void PinEditDoc::clearSelectedVertex() {
	m_iVertexExtra = -1;
	m_vSelectedVertex.clear();
	cerr << "pineditdoc::clearselectedvertex" << endl;
}

void PinEditDoc::clearSelectedPolygon() {
	m_vSelectedPolygon.clear();
	cerr << "pineditdoc::clearselectedpolygon" << endl;
}

void PinEditDoc::selectVertex(int index) {
	assert(p_CurrentShape != NULL);
	m_vSelectedVertex.push_back(index);
	Vertex3D * vtx = p_CurrentShape->getVertex3D(index);
	cerr << "pineditdoc::selectvertex" << vtx->x <<" "<< vtx->y <<" "<< vtx->z << endl;
}

void PinEditDoc::selectVertexExtra(int index) {
	m_iVertexExtra = index;
}

void PinEditDoc::selectPolygon(Polygon * poly) {
	m_vSelectedPolygon.push_back(poly);
	cerr << "pineditdoc::selectpolygon" << endl;
}

void PinEditDoc::unSelectVertex(int index) {
	vector<int>::iterator iter = m_vSelectedVertex.begin();
	vector<int>::iterator end = m_vSelectedVertex.end();
	// is there a smarter way to do a erease, please tell me !!!
	for (; iter != end; iter++) {
		if ((*iter) == index) {
			m_vSelectedVertex.erase(iter);
			break; // the vector is now changes must break;
		}
	}
}

int PinEditDoc::getSelectedVertexExtra() {
	return m_iVertexExtra;
}

int PinEditDoc::getSelectedVertex(int index) {
	if (index < 0 || index >= (signed)m_vSelectedVertex.size()) {
		return -1;
	}
	return m_vSelectedVertex[index];
}

Polygon * PinEditDoc::getSelectedPolygon(int index) {
	if (index < 0 || (unsigned)index >= m_vSelectedPolygon.size()) {
		return NULL;
	}
	return m_vSelectedPolygon[index];
}

bool PinEditDoc::isVertexSelected(int index) {
	vector<int>::iterator iter = m_vSelectedVertex.begin();
	vector<int>::iterator end = m_vSelectedVertex.end();
	for (; iter != end; iter++) {
		if ((*iter) == index) {
			return true;
		}
	}
	return false;
}

void PinEditDoc::doSelectPolygons() {
	Shape3D * shape = this->getCurrentShape();
	if (shape == NULL) return;
	this->clearSelectedPolygon();
	int index = 0;
	Polygon * poly = shape->getPolygon(index); 
	while (poly != NULL) {
		bool selected = true;
		int polyindex = 0;
		int i = poly->getIndex(polyindex);
		while (i >= 0) {
			if (!(this->isVertexSelected(i))) {
				selected = false;
				break;
			}
			polyindex++;
			i = poly->getIndex(polyindex);
		}
		if (selected) {
			m_vSelectedPolygon.push_back(poly);
		}

		index++;
		poly = shape->getPolygon(index); 
	}
	cerr << "pineditdoc::doselecpolygons" << endl;
}

void PinEditDoc::getSelectedCenter(Vertex3D & vtxM) {
	assert(p_CurrentShape != NULL);
	// get local center of gravity
	vtxM.x = 0;
	vtxM.y = 0;
	vtxM.z = 0;
	int index = 0; 
	Vertex3D * vtx = p_CurrentShape->getVertex3D(this->getSelectedVertex(index));
	while (vtx != NULL) {
		vtxM.x += vtx->x;
		vtxM.y += vtx->y;
		vtxM.z += vtx->z;

		index++;
		vtx = p_CurrentShape->getVertex3D(this->getSelectedVertex(index));
	}
	if (index != 0) {
		vtxM.x /= index;
		vtxM.y /= index;
		vtxM.z /= index;
	}
}
