/****************************************************************************
** PinEditDoc meta object code from reading C++ file 'pineditdoc.h'
**
** Created: Fri Sep 27 14:12:15 2002
**      by: The Qt MOC ($Id: moc_pineditdoc.cpp,v 1.1.1.1 2002/09/27 13:23:40 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "pineditdoc.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *PinEditDoc::className() const
{
    return "PinEditDoc";
}

QMetaObject *PinEditDoc::metaObj = 0;
static QMetaObjectCleanUp cleanUp_PinEditDoc;

#ifndef QT_NO_TRANSLATION
QString PinEditDoc::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PinEditDoc", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString PinEditDoc::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PinEditDoc", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* PinEditDoc::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUMethod signal_0 = {"documentChanged", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "documentChanged()", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"PinEditDoc", parentObject,
	0, 0,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_PinEditDoc.setMetaObject( metaObj );
    return metaObj;
}

void* PinEditDoc::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "PinEditDoc" ) ) return (PinEditDoc*)this;
    return QObject::qt_cast( clname );
}

// SIGNAL documentChanged
void PinEditDoc::documentChanged()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

bool PinEditDoc::qt_invoke( int _id, QUObject* _o )
{
    return QObject::qt_invoke(_id,_o);
}

bool PinEditDoc::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: documentChanged(); break;
    default:
	return QObject::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool PinEditDoc::qt_property( int _id, int _f, QVariant* _v)
{
    return QObject::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
