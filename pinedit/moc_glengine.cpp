/****************************************************************************
** GLEngine meta object code from reading C++ file 'glengine.h'
**
** Created: Fri Sep 27 14:12:05 2002
**      by: The Qt MOC ($Id: moc_glengine.cpp,v 1.1.1.1 2002/09/27 13:23:40 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "glengine.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GLEngine::className() const
{
    return "GLEngine";
}

QMetaObject *GLEngine::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GLEngine;

#ifndef QT_NO_TRANSLATION
QString GLEngine::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLEngine", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GLEngine::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLEngine", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GLEngine::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGLWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"GLEngine", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GLEngine.setMetaObject( metaObj );
    return metaObj;
}

void* GLEngine::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GLEngine" ) ) return (GLEngine*)this;
    if ( !qstrcmp( clname, "Updateable" ) ) return (Updateable*)this;
    return QGLWidget::qt_cast( clname );
}

bool GLEngine::qt_invoke( int _id, QUObject* _o )
{
    return QGLWidget::qt_invoke(_id,_o);
}

bool GLEngine::qt_emit( int _id, QUObject* _o )
{
    return QGLWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool GLEngine::qt_property( int _id, int _f, QVariant* _v)
{
    return QGLWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
