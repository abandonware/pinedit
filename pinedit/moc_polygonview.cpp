/****************************************************************************
** PolygonView meta object code from reading C++ file 'polygonview.h'
**
** Created: Fri Sep 27 14:12:54 2002
**      by: The Qt MOC ($Id: moc_polygonview.cpp,v 1.1.1.1 2002/09/27 13:23:40 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "polygonview.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *PolygonView::className() const
{
    return "PolygonView";
}

QMetaObject *PolygonView::metaObj = 0;
static QMetaObjectCleanUp cleanUp_PolygonView;

#ifndef QT_NO_TRANSLATION
QString PolygonView::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PolygonView", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString PolygonView::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PolygonView", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* PolygonView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotChanged", 0, 0 };
    static const QUMethod slot_1 = {"slotApplyVertex", 0, 0 };
    static const QUMethod slot_2 = {"slotApplyColor", 0, 0 };
    static const QUMethod slot_3 = {"slotApplyProp", 0, 0 };
    static const QUMethod slot_4 = {"slotTexCoord", 0, 0 };
    static const QUMethod slot_5 = {"slotChoose", 0, 0 };
    static const QUMethod slot_6 = {"slotNone", 0, 0 };
    static const QUMethod slot_7 = {"slotAutoTexCoord", 0, 0 };
    static const QUMethod slot_8 = {"slotVertexUp", 0, 0 };
    static const QUMethod slot_9 = {"slotVertexDown", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotChanged()", &slot_0, QMetaData::Public },
	{ "slotApplyVertex()", &slot_1, QMetaData::Public },
	{ "slotApplyColor()", &slot_2, QMetaData::Public },
	{ "slotApplyProp()", &slot_3, QMetaData::Public },
	{ "slotTexCoord()", &slot_4, QMetaData::Public },
	{ "slotChoose()", &slot_5, QMetaData::Public },
	{ "slotNone()", &slot_6, QMetaData::Public },
	{ "slotAutoTexCoord()", &slot_7, QMetaData::Public },
	{ "slotVertexUp()", &slot_8, QMetaData::Public },
	{ "slotVertexDown()", &slot_9, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"PolygonView", parentObject,
	slot_tbl, 10,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_PolygonView.setMetaObject( metaObj );
    return metaObj;
}

void* PolygonView::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "PolygonView" ) ) return (PolygonView*)this;
    if ( !qstrcmp( clname, "Updateable" ) ) return (Updateable*)this;
    if ( !qstrcmp( clname, "Rebuildable" ) ) return (Rebuildable*)this;
    return QWidget::qt_cast( clname );
}

bool PolygonView::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotChanged(); break;
    case 1: slotApplyVertex(); break;
    case 2: slotApplyColor(); break;
    case 3: slotApplyProp(); break;
    case 4: slotTexCoord(); break;
    case 5: slotChoose(); break;
    case 6: slotNone(); break;
    case 7: slotAutoTexCoord(); break;
    case 8: slotVertexUp(); break;
    case 9: slotVertexDown(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool PolygonView::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool PolygonView::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
