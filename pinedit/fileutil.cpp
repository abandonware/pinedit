/***************************************************************************
                          pineditdoc.cpp  -  description
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

// general includes
#include <cassert>
// qt includes
#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
// application includes
#include "fileutil.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "Pinball.h"
#include "Engine.h"
#include "Group.h"
#include "Shape3D.h"
#include "Polygon.h"
#include "Behavior.h"
#include "BumperBehavior.h"
#include "ArmBehavior.h"
#include "StateBehavior.h"
#include "FakeModuleBehavior.h"
#include "Light.h"
#include "TextureUtil.h"
#include "SoundUtil.h"
#include "Script.h"
#include "Loader.h"
#include "StdAnimation.h"

FileUtil::FileUtil(PinEditDoc * doc) {
	assert(doc != NULL);
	p_Doc = doc;
}

FileUtil::~FileUtil() {
}

int FileUtil::saveFile(const QString & fn, Group * group) {
	assert(group != NULL);
	
	try {
		QFile f(fn);
    QFile fbak(fn + ".bak");
		if (f.open(IO_ReadOnly)) {
			if (!fbak.open(IO_WriteOnly)) {
				throw QString("FileUtil::saveFile could not open file for writing: ") + fn + ".bak";
			}
			
			while (!f.atEnd()) {
				if (fbak.putch(f.getch()) == -1) {
					throw QString("FileUtil::saveFile error writing bakup file: ") + fn + ".bak";
				}
			}
			f.close();
			fbak.close();
		}
		//QFile f(fn);
		if (!f.open(IO_WriteOnly)) {
			throw QString("FileUtil::saveFile could not open file for writing: ") + QString(fn);
		}
		QTextStream file(&f);
		// write root group
		Vertex3D vtxT, vtxR;
		group->getTranslation(vtxT.x, vtxT.y, vtxT.z);
		group->getRotation(vtxR.x, vtxR.y, vtxR.z);
		group->setTransform(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		this->writeGroup(file, group);
		group->setTransform(vtxT.x, vtxT.y, vtxT.z, vtxR.x, vtxR.y, vtxR.z);
		// write subgroups
		int grindex = 0;
		Group * g = group->getGroup(grindex);
		while (g != NULL) {
			this->writeGroup(file, g);
			grindex++;
			g = group->getGroup(grindex);
		}
		f.close();
	} catch (QString str) {
		cerr << "**************************************************" << endl;
		cerr << "Error when saving file!" << endl;
		cerr << str << endl;
		cerr << "**************************************************" << endl;
		return -1;
	}
	return 0;
}

int FileUtil::writeGroup(QTextStream & file, Group * group) {
	assert(group != NULL);
	// don't write groups beginning with #
	string::size_type i = string(group->getName()).find("#");
	if (i != string::npos && i == 0) {
		EM_CERR("fileutil::writegroup(): omiting " << group->getName());
		return 0;
	}
	// header
	file << "object " << group->getName() << " {" << endl;
	Vertex3D vtxT, vtxR;
	group->getTranslation(vtxT.x, vtxT.y, vtxT.z);
	group->getRotation(vtxR.x, vtxR.y, vtxR.z);
	file << "  " << vtxT.x <<" "<< vtxT.y <<" "<< vtxT.z << endl;
	file << "  " << vtxR.x <<" "<< vtxR.y <<" "<< vtxR.z << endl;

	if (group->getGroup(0) != NULL) {
		EM_CERR("fileutil::writegroup(): sub groups not yet supported !!!");
	}
	// write shapes
	int shindex = 0;
	Shape3D * shape = group->getShape3D(shindex);
	while (shape != NULL) {
		this->writeShape(file, shape);
		++shindex;
		shape = group->getShape3D(shindex);
	}
	// write behaviors
// 	int behindex = 0;
// 	Behavior * beh = group->getBehavior(behindex);
// 	while (beh != NULL) {
// 		this->writeBehavior(file, beh);
// 		++behindex;
// 		beh = group->getBehavior(behindex);
// 	}
 	Behavior * beh = group->getBehavior();
 	if (beh != NULL) {
 		this->writeBehavior(file, beh);
 	}

	file << "  properties {" << endl;
	if (group->getCollisionBounds() != NULL) {
		file << "    collision" << endl;
	}
	if (group->getProperties() & (EM_GROUP_TRANSFORM_ONCE | EM_GROUP_NO_TRANSFORM)) {
		file << "    transform_once" << endl;
	}
	if (group->getUserProperties() & PBL_WALLS) {
		file << "    wall" << endl;
	}
	if (group->getUserProperties() & PBL_WALLS_ONE) {
		file << "    wall_one_way" << endl;
	}
	file << "    group_1" << endl;
	file << "  }" << endl;

	file << "}" << endl;

	return 0;
}

int FileUtil::writeShape(QTextStream & file, Shape3D * shape) {
	assert(shape != NULL);
	file << "  shape {" << endl;
	file << "    vts { " << shape->getVertex3DSize() << " }" << endl;
	file << "    pls { " << shape->getPolygonSize() << " }" << endl;

	if (shape->getProperties() & EM_SHAPE3D_HIDDEN) {
		file << "    hid { }" << endl;
	}
	if (shape->getProperties() & EM_SHAPE3D_BEHIND) {
		file << "    bhi { }" << endl;
	}
	if (shape->getProperties() & EM_SHAPE3D_BEHIND2) {
		file << "    bh2 { }" << endl;
	}
	if (shape->getProperties() & EM_SHAPE3D_ALLWAYSLIT) {
		file << "    lit { }" << endl;
	}

	if (shape->getTexture() != NULL) {
		file << "    tex { " << endl;
		QString filename(TextureUtil::getInstance()->getTextureName(shape->getTexture()));
		int last = filename.findRev("/");
		if (last != -1) {
			filename.remove(0, last+1);
		}
		file << "      " << filename.data() << endl;
		file << "    }" << endl;
	}

	int vtxindex = 0;
	Vertex3D * vtx = shape->getVertex3D(vtxindex);
#if EM_USE_SHARED_COLOR
	Color * color = shape->getColor(vtxindex);
	TexCoord * tex = shape->getTexCoord(vtxindex);
	while (vtx != NULL) {
		file << "    vtx { " << endl;
		file << "      " << vtx->x <<" "<< vtx->y <<" "<< vtx->z << endl;
		file << "      " << color->r <<" "<< color->g <<" "<< color->b <<" "<< color->a << endl;
		file << "      " << tex->u <<" "<< tex->v << endl;
		file << "    }" << endl;
		vtxindex++;
		vtx = shape->getVertex3D(vtxindex);
		color = shape->getColor(vtxindex);
		tex = shape->getTexCoord(vtxindex);
	}
#else
	while (vtx != NULL) {
		file << "    vtx { " << vtx->x <<" "<< vtx->y <<" "<< vtx->z << " }" << endl;
		vtxindex++;
		vtx = shape->getVertex3D(vtxindex);
	}
#endif

	int polyindex = 0;
	Polygon * poly = shape->getPolygon(polyindex);
	while (poly != NULL) {
		file << "    ply {" << endl;
		file << "      pes { " << poly->getIndexSize() <<" }"<< endl;
		if (poly->getProperties() & EM_POLY_TRANS) {
			file << "      tpt { }" << endl;
		}

		int edgeindex = 0;
		int index = poly->getIndex(edgeindex);
		while (index != -1) {
#if EM_USE_SHARED_COLOR
			file << "      ple { " << index <<" ";
#else
			TexCoord * tex = poly->getTexCoord(edgeindex);
			Color * color = poly->getColor(edgeindex);
			assert(tex != NULL);
			assert(color != NULL);
			file << "      ple { " << index <<" ";
			file << tex->u <<" "<< tex->v <<" ";
			file << color->r <<" "<< color->g <<" "<< color->b <<" "<< color->a <<" ";
#endif
			file << " }" << endl;
			++edgeindex;
			index = poly->getIndex(edgeindex);
		}
		file << "    }" << endl;
		++polyindex;
		poly = shape->getPolygon(polyindex);
	}

	file << "  }" << endl;
	return 0;
}

int FileUtil::writeBehavior(QTextStream & file, Behavior * beh) {
	EM_CERR("FileUtil::writeBehavior");
	assert(beh != NULL);
	// bumper behavior
	if (beh->getType() == PBL_TYPE_BUMPERBEH) {
		BumperBehavior * bumperbeh = (BumperBehavior*) beh;
		file << "  bumper_behavior {" << endl;
		if (bumperbeh->getSound() != -1) {
			QString filename(SoundUtil::getInstance()->getSoundName(bumperbeh->getSound()));
			int last = filename.findRev("/");
			if (last != -1) {
				filename.remove(0, last+1);
			}
			file << "    sound " << filename.data() << endl;
		} else {
			file << "    no_sound" << endl;
		}
	}
	// module
	else if (beh->getType() == PBL_TYPE_FAKEMODULEBEH) {
		FakeModuleBehavior * modbeh = (FakeModuleBehavior*) beh;
		file << "  module {" << endl;
		QString filename(modbeh->getName());
		int last = filename.findRev("/");
		if (last != -1) {
			filename.remove(0, last+1);
		}
		file << "    " << filename.data() << endl;
	}
	// module
	else if (beh->getType() == PBL_TYPE_ARMBEH) {
		ArmBehavior * armbeh = (ArmBehavior*) beh;
		file << "  arm_behavior {" << endl;
		file << "    " << (armbeh->getIsRight() ? "right" : "left") << endl;
		if (armbeh->getSound() != -1) {
			QString filename(SoundUtil::getInstance()->getSoundName(armbeh->getSound()));
			int last = filename.findRev("/");
			if (last != -1) {
				filename.remove(0, last+1);
			}
			file << "    sound " << filename.data() << endl;
		} else {
			file << "    no_sound" << endl;
		}
	}
	// state behavior
	else if (beh->getType() == PBL_TYPE_STATEBEH) {
		StateBehavior * statebeh = (StateBehavior*) beh;
		file << "  state_behavior {" << endl;

		int index = 0;
		StateItem * stateitem = statebeh->getStateItem(index);
		while (stateitem != NULL) {
			file << "    state_item {" << endl;
			// signals
			file << "      " << Loader::getInstance()->getSignal(stateitem->getActSig()) <<" "<< 
				Loader::getInstance()->getSignal(stateitem->getCollSig()) <<" ";
			file <<	stateitem->getCollState() <<" "<< stateitem->getDelayState() <<" "<< 
				stateitem->getDelay() << endl;
			// move
			if (statebeh->usesMove()) {
				file << "      move" << endl;
				file << "        " << stateitem->m_iMoveSteps << endl;
				file << "        " << stateitem->m_vtxTr.x <<" "<< stateitem->m_vtxTr.y <<" "<< 
					stateitem->m_vtxTr.z << endl;
				file << "        " << stateitem->m_vtxRot.x <<" "<< stateitem->m_vtxRot.y <<" "<< 
					stateitem->m_vtxRot.z << endl;
			} else {
				file << "      no_move" << endl;
			}
			// light
			file << "      " << (stateitem->m_bLight ? "light" : "no_light") << endl;
			// sound
			if (stateitem->getSound() != -1) {
				QString filename(SoundUtil::getInstance()->getSoundName(stateitem->getSound()));
				int last = filename.findRev("/");
				if (last != -1) {
					filename.remove(0, last+1);
				}
				file << "      sound " << filename.data() << endl;
			} else {
				file << "      no_sound" << endl;
			}
			// music
			if (stateitem->getMusic() != -1) {
				QString filename(SoundUtil::getInstance()->getMusicName(stateitem->getMusic()));
				int last = filename.findRev("/");
				if (last != -1) {
					filename.remove(0, last+1);
				}
				file << "      music " << filename.data() << endl;
			} else {
				file << "      no_music" << endl;
			}
			// properties
			if (stateitem->getProperty() != PBL_NULL) {
				file << "      property " << stateitem->getProperty() << endl;
			} else {
				file << "      no_property" << endl;
			}
			// texcoord
			if (statebeh->usesTexCoord()) {
				file << "      texcoord" << endl;
				file << "      " << stateitem->m_vTexCoord.size() << endl;
				vector<TexCoord>::iterator iter = stateitem->m_vTexCoord.begin();
				vector<TexCoord>::iterator end = stateitem->m_vTexCoord.end();
				for (; iter != end; ++iter) {
					file << "      " << (*iter).u << " " << (*iter).v << endl;
				}
			} else {
				file << "      no_texcoord" << endl;
			}
			// shape enable
			if (statebeh->usesShape()) {
				file << "      shape " << stateitem->m_vShapeEnable.size();
				vector<bool>::iterator iter = stateitem->m_vShapeEnable.begin();
				vector<bool>::iterator end = stateitem->m_vShapeEnable.end();
				for (; iter != end; ++iter) {
					file << " " << ((*iter) ? "1" : "0");
				}
				file << endl;
			} else {
				file << "      no_shape" << endl;
			}
			file << "    }" << endl;
			++index;
			stateitem = statebeh->getStateItem(index);
		}
	} else {
		file << "  error {" << endl;
	}
	
	Light * light = beh->getLight();
	if (light != NULL) {
		float r, g, b;
		light->getColor(r, g, b);
		file << "    light {" << endl;
		file << "      " << r <<" "<< g <<" "<< b << endl;
		file << "      0 3 0" << endl;
		Group * lp = light->getParent();
		assert(lp != NULL);
		Behavior * anim = lp->getBehavior();
		if (anim != NULL && anim->getType() == EM_TYPE_STDANIMATION) {
			file << "      animation {" << endl;
			file << "        light " << ((StdAnimation*)anim)->getStep() << endl;
			file << "        2" << endl;
			file << "        " << r <<" "<< g <<" "<< b << endl;
			file << "        0 0 0" << endl;
			file << "      }" << endl;
		}
		file << "    }" << endl;
	}

	file << "  }" << endl;
	return 0;
}
