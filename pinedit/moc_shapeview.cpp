/****************************************************************************
** ShapeView meta object code from reading C++ file 'shapeview.h'
**
** Created: Mon May 19 21:17:35 2003
**      by: The Qt MOC ($Id: moc_shapeview.cpp,v 1.3 2003/05/20 21:15:24 pedro_nf Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "shapeview.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ShapeView::className() const
{
    return "ShapeView";
}

QMetaObject *ShapeView::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ShapeView;

#ifndef QT_NO_TRANSLATION
QString ShapeView::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ShapeView", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ShapeView::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ShapeView", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ShapeView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QVBox::staticMetaObject();
    static const QUMethod slot_0 = {"slotChanged", 0, 0 };
    static const QUMethod slot_1 = {"slotApplyProp", 0, 0 };
    static const QUMethod slot_2 = {"slotAdd", 0, 0 };
    static const QUMethod slot_3 = {"slotEdit", 0, 0 };
    static const QUMethod slot_4 = {"slotLight", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotChanged()", &slot_0, QMetaData::Public },
	{ "slotApplyProp()", &slot_1, QMetaData::Public },
	{ "slotAdd()", &slot_2, QMetaData::Public },
	{ "slotEdit()", &slot_3, QMetaData::Public },
	{ "slotLight()", &slot_4, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ShapeView", parentObject,
	slot_tbl, 5,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ShapeView.setMetaObject( metaObj );
    return metaObj;
}

void* ShapeView::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ShapeView" ) ) return (ShapeView*)this;
    if ( !qstrcmp( clname, "Updateable" ) ) return (Updateable*)this;
    if ( !qstrcmp( clname, "Rebuildable" ) ) return (Rebuildable*)this;
    return QVBox::qt_cast( clname );
}

bool ShapeView::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotChanged(); break;
    case 1: slotApplyProp(); break;
    case 2: slotAdd(); break;
    case 3: slotEdit(); break;
    case 4: slotLight(); break;
    default:
	return QVBox::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ShapeView::qt_emit( int _id, QUObject* _o )
{
    return QVBox::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ShapeView::qt_property( int _id, int _f, QVariant* _v)
{
    return QVBox::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
