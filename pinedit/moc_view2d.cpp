/****************************************************************************
** View2D meta object code from reading C++ file 'view2d.h'
**
** Created: Fri Sep 27 14:12:23 2002
**      by: The Qt MOC ($Id: moc_view2d.cpp,v 1.1.1.1 2002/09/27 13:23:40 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "view2d.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *View2D::className() const
{
    return "View2D";
}

QMetaObject *View2D::metaObj = 0;
static QMetaObjectCleanUp cleanUp_View2D;

#ifndef QT_NO_TRANSLATION
QString View2D::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "View2D", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString View2D::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "View2D", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* View2D::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"View2D", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_View2D.setMetaObject( metaObj );
    return metaObj;
}

void* View2D::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "View2D" ) ) return (View2D*)this;
    if ( !qstrcmp( clname, "Updateable" ) ) return (Updateable*)this;
    return QWidget::qt_cast( clname );
}

bool View2D::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool View2D::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool View2D::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
