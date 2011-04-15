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
#include <iostream>
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
#include "PlungerBehavior.h"

FileUtil::FileUtil(PinEditDoc * doc) {
  assert(doc != NULL);
  p_Doc = doc;
  m_iIndent = 0;
}

#define WriteLine(file, str) {               \
  for (int em_a=0; em_a<m_iIndent; ++em_a) { \
    file << "  ";                            \
  }                                          \
  file << str << endl;                       \
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
    // write version
    WriteLine(file, "version { 0 3 0 }");
    // write root group
    Vertex3D vtxT, vtxR;
    group->getTranslation(vtxT.x, vtxT.y, vtxT.z);
    group->getRotation(vtxR.x, vtxR.y, vtxR.z);
    // why do we do this ???
    group->setTransform(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    this->resetIndent();
    this->writeGroup(file, group);
    group->setTransform(vtxT.x, vtxT.y, vtxT.z, vtxR.x, vtxR.y, vtxR.z);
    // write objects
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
  WriteLine(file, "object " << group->getName() << " {");
  Vertex3D vtxT, vtxR, vtxS;
  group->getTranslation(vtxT.x, vtxT.y, vtxT.z);
  group->getRotation(vtxR.x, vtxR.y, vtxR.z);
  group->getScale(vtxS.x, vtxS.y, vtxS.z);
  this->incIndent();
  WriteLine(file, vtxT.x <<" "<< vtxT.y <<" "<< vtxT.z );
  WriteLine(file, vtxR.x <<" "<< vtxR.y <<" "<< vtxR.z );
  WriteLine(file, vtxS.x <<" "<< vtxS.y <<" "<< vtxS.z );
  
  int gindex = 0;
  Group * subgroup = group->getGroup(gindex);
  while (subgroup != NULL) {
    this->writeGroup(file, subgroup);
    ++gindex;
    subgroup = group->getGroup(gindex);
  }
  //if (group->getGroup(0) != NULL) {
  //  EM_CERR("fileutil::writegroup(): sub groups not yet supported !!!");
  //}
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
  
  WriteLine(file, "properties {" );
  this->incIndent();
  if (group->getCollisionBounds() != NULL) {
    WriteLine(file, "collision" );
  }
  if (group->getProperties() & (EM_GROUP_TRANSFORM_ONCE | EM_GROUP_NO_TRANSFORM)) {
    WriteLine(file, "transform_once" );
  }
  if (group->getUserProperties() & PBL_WALLS) {
    WriteLine(file, "wall" );
  }
  if (group->getUserProperties() & PBL_WALLS_ONE) {
    WriteLine(file, "wall_one_way" );
  }
  WriteLine(file, "group_1" );
  this->decIndent();
  WriteLine(file, "}" );

  this->decIndent();
  WriteLine(file, "}" );

  return 0;
}

int FileUtil::writeShape(QTextStream & file, Shape3D * shape) {
  assert(shape != NULL);
  WriteLine(file, "shape {" );
  this->incIndent();
  WriteLine(file, "vts { " << shape->getVertex3DSize() << " }" );
  WriteLine(file, "pls { " << shape->getPolygonSize() << " }" );

  if (shape->getProperties() & EM_SHAPE3D_HIDDEN) {
    WriteLine(file, "hid { }" );
  }
  if (shape->getProperties() & EM_SHAPE3D_BEHIND) {
    WriteLine(file, "bhi { }" );
  }
  if (shape->getProperties() & EM_SHAPE3D_BEHIND2) {
    WriteLine(file, "bh2 { }" );
  }
  if (shape->getProperties() & EM_SHAPE3D_ALWAYSLIT) {
    WriteLine(file, "lit { }" );
  }

  if (shape->getTexture() != NULL) {
    WriteLine(file, "tex { " );
    QString filename(TextureUtil::getInstance()->getTextureName(shape->getTexture()));
    int last = filename.findRev("/");
    if (last != -1) {
      filename.remove(0, last+1);
    }
    WriteLine(file, "  " << filename.data() );
    WriteLine(file, "}" );
  }

  int vtxindex = 0;
  Vertex3D * vtx = shape->getVertex3D(vtxindex);
  Color * color = shape->getColor(vtxindex);
  TexCoord * tex = shape->getTexCoord(vtxindex);
  while (vtx != NULL) {
    WriteLine(file, "vtx { " );
    WriteLine(file, "  " << vtx->x <<" "<< vtx->y <<" "<< vtx->z );
    WriteLine(file, "  " << color->r <<" "<< color->g <<" "<< color->b <<" "<< color->a );
    WriteLine(file, "  " << tex->u <<" "<< tex->v );
    WriteLine(file, "}" );
    vtxindex++;
    vtx = shape->getVertex3D(vtxindex);
    color = shape->getColor(vtxindex);
    tex = shape->getTexCoord(vtxindex);
  }

  int polyindex = 0;
  Polygon3D * poly = shape->getPolygon(polyindex);
  while (poly != NULL) {
    WriteLine(file, "ply {" );
    WriteLine(file, "  pes { " << poly->getIndexSize() <<" }");
    if (poly->getProperties() & EM_POLY_TRANS) {
      WriteLine(file, "  tpt { }" );
    }

    int edgeindex = 0;
    int index = poly->getIndex(edgeindex);
    while (index != -1) {
      WriteLine(file, "  ple { " << index <<" }");
      ++edgeindex;
      index = poly->getIndex(edgeindex);
    }
    WriteLine(file, "}" );
    ++polyindex;
    poly = shape->getPolygon(polyindex);
  }

  this->decIndent();
  WriteLine(file, "}" );
  return 0;
}

int FileUtil::writeBehavior(QTextStream & file, Behavior * beh) {
  EM_CERR("FileUtil::writeBehavior");
  assert(beh != NULL);
  // bumper behavior
  if (beh->getType() == PBL_TYPE_BUMPERBEH) {
    BumperBehavior * bumperbeh = (BumperBehavior*) beh;
    WriteLine(file, "bumper_behavior {" );
    WriteLine(file, "  " << bumperbeh->getPower());
    if (bumperbeh->getSound() != -1) {
      QString filename(SoundUtil::getInstance()->getSoundName(bumperbeh->getSound()));
      int last = filename.findRev("/");
      if (last != -1) {
	filename.remove(0, last+1);
      }
      WriteLine(file, "  sound " << filename.data() );
    } else {
      WriteLine(file, "  no_sound" );
    }
  }
  // plunger behavior
  else if (beh->getType() == PBL_TYPE_PLUNGERBEH) {
    PlungerBehavior * plungerbeh = (PlungerBehavior*) beh;
    WriteLine(file, "plunger_behavior {" );
    if (plungerbeh->getSound() != -1) {
      QString filename(SoundUtil::getInstance()->getSoundName(plungerbeh->getSound()));
      int last = filename.findRev("/");
      if (last != -1) {
	filename.remove(0, last+1);
      }
      WriteLine(file, "  sound " << filename.data() );
    } else {
      WriteLine(file, "  no_sound" );
    }
  }
  // module
  else if (beh->getType() == PBL_TYPE_FAKEMODULEBEH) {
    FakeModuleBehavior * modbeh = (FakeModuleBehavior*) beh;
    WriteLine(file, "module {" );
    QString filename(modbeh->getName());
    int last = filename.findRev("/");
    if (last != -1) {
      filename.remove(0, last+1);
    }
    WriteLine(file, "    " << filename.data() );
  }
  // module
  else if (beh->getType() == PBL_TYPE_ARMBEH) {
    ArmBehavior * armbeh = (ArmBehavior*) beh;
    WriteLine(file, "arm_behavior {" );
    WriteLine(file, "  " << (armbeh->getIsRight() ? "right" : "left") );
    if (armbeh->getSound() != -1) {
      QString filename(SoundUtil::getInstance()->getSoundName(armbeh->getSound()));
      int last = filename.findRev("/");
      if (last != -1) {
	filename.remove(0, last+1);
      }
      WriteLine(file, "  sound " << filename.data() );
    } else {
      WriteLine(file, "  no_sound" );
    }
  }
  // state behavior
  else if (beh->getType() == PBL_TYPE_STATEBEH) {
    StateBehavior * statebeh = (StateBehavior*) beh;
    WriteLine(file, "state_behavior {" );

    int index = 0;
    StateItem * stateitem = statebeh->getStateItem(index);
    while (stateitem != NULL) {
      WriteLine(file, "  state_item {" );
      // signals
      WriteLine(file, "    " << Loader::getInstance()->getSignal(stateitem->getActSig()) <<" "<< 
	Loader::getInstance()->getSignal(stateitem->getCollSig()) <<" ";
      file <<	stateitem->getCollState() <<" "<< stateitem->getDelayState() <<" "<< 
	stateitem->getDelay() );
      // move
      if (statebeh->usesMove()) {
	WriteLine(file, "    move" );
	WriteLine(file, "      " << stateitem->m_iMoveSteps );
	WriteLine(file, "      " << stateitem->m_vtxTr.x <<" "<< stateitem->m_vtxTr.y <<" "<< 
	  stateitem->m_vtxTr.z );
	WriteLine(file, "      " << stateitem->m_vtxRot.x <<" "<< stateitem->m_vtxRot.y <<" "<< 
	  stateitem->m_vtxRot.z );
      } else {
	WriteLine(file, "    no_move" );
      }
      // light
      WriteLine(file, "      " << (stateitem->m_bLight ? "light" : "no_light") );
      // sound
      if (stateitem->getSound() != -1) {
	QString filename(SoundUtil::getInstance()->getSoundName(stateitem->getSound()));
	int last = filename.findRev("/");
	if (last != -1) {
	  filename.remove(0, last+1);
	}
	WriteLine(file, "    sound " << filename.data() );
      } else {
	WriteLine(file, "    no_sound" );
      }
      // music
      if (stateitem->getMusic() != -1) {
	QString filename(SoundUtil::getInstance()->getMusicName(stateitem->getMusic()));
	int last = filename.findRev("/");
	if (last != -1) {
	  filename.remove(0, last+1);
	}
	WriteLine(file, "    music " << filename.data() );
      } else {
	WriteLine(file, "    no_music" );
      }
      // properties
      if (stateitem->getUserProperty() != PBL_NULL) {
	WriteLine(file, "    user_property " << stateitem->getUserProperty() );
      } else {
	WriteLine(file, "    no_user_property" );
      }
      if (stateitem->getShapeProperty() != 0) {
	WriteLine(file, "    shape_property " << stateitem->getShapeProperty() );
      } else {
	WriteLine(file, "    no_shape_property" );
      }
      // texcoord
      if (statebeh->usesTexCoord()) {
	WriteLine(file, "    texcoord" );
	WriteLine(file, "    " << stateitem->m_vTexCoord.size() );
	vector<TexCoord>::iterator iter = stateitem->m_vTexCoord.begin();
	vector<TexCoord>::iterator end = stateitem->m_vTexCoord.end();
	for (; iter != end; ++iter) {
	  WriteLine(file, "    " << (*iter).u << " " << (*iter).v );
	}
      } else {
	WriteLine(file, "    no_texcoord" );
      }
      // shape enable
      if (statebeh->usesShape()) {
	WriteLine(file, "    shape " << stateitem->m_vShapeEnable.size());
	vector<bool>::iterator iter = stateitem->m_vShapeEnable.begin();
	vector<bool>::iterator end = stateitem->m_vShapeEnable.end();
	for (; iter != end; ++iter) {
	  WriteLine(file, "      " << ((*iter) ? "1" : "0"));
	}
      } else {
	WriteLine(file, "    no_shape" );
      }
      WriteLine(file, "  }" );
      ++index;
      stateitem = statebeh->getStateItem(index);
    }
  } else {
    WriteLine(file, "error {" );
  }
  
  Light * light = beh->getLight();
  if (light != NULL) {
    float r, g, b;
    light->getColor(r, g, b);
    WriteLine(file, "  light {" );
    WriteLine(file, "    " << r <<" "<< g <<" "<< b );
    WriteLine(file, "    0 3 0" );
    Group * lp = light->getParent();
    assert(lp != NULL);
    Behavior * anim = lp->getBehavior();
    if (anim != NULL && anim->getType() == EM_TYPE_STDANIMATION) {
      WriteLine(file, "    animation {" );
      WriteLine(file, "      light " << ((StdAnimation*)anim)->getStep() );
      WriteLine(file, "      2" );
      WriteLine(file, "      " << r <<" "<< g <<" "<< b );
      WriteLine(file, "      0 0 0" );
      WriteLine(file, "    }" );
    }
    WriteLine(file, "  }" );
  }
  
  WriteLine(file, "}" );
  return 0;
}

#undef WriteLine
