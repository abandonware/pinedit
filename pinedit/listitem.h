/***************************************************************************
                          listitem.h  -  description
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

#ifndef LISTITEM_H
#define LISTITEM_H

// qt includes
#include <qlistview.h>

#define LISTITEM_NULL 0
#define LISTITEM_GROUP 1
#define LISTITEM_SHAPE 2
#define LISTITEM_BEHAVIOR 3
#define LISTITEM_STATEITEM 4
#define LISTITEM_POLYGON 6
#define LISTITEM_VERTEX 7
#define LISTITEM_LAST 8

/** @author Henrik Enqvist IB  */
class ListItem : public QListViewItem {
 public:
	ListItem(QListView * parent, QString name) : QListViewItem(parent, name) {
		p_Object = NULL;
		m_iType = LISTITEM_NULL;
	};
	ListItem(ListItem * parent, QString name) : QListViewItem(parent, name) {
		p_Object = NULL;
		m_iType = LISTITEM_NULL;
	}; 
	~ListItem() {};
	int getObjectType() {
		return m_iType;
	};
	void * getObject() {
		return p_Object;
	};
	void setObject(void * object, int type) {
		assert(object != NULL || type == LISTITEM_NULL);
		assert(object == NULL || type != LISTITEM_NULL);
		assert(type >= LISTITEM_NULL && type < LISTITEM_LAST);
		p_Object = object;
		m_iType = type;
	}
 private:
	void * p_Object;
	int m_iType;
};

#endif
