/****************************************************************************
** LightDialog meta object code from reading C++ file 'lightdialog.h'
**
** Created: Fri Sep 27 14:12:43 2002
**      by: The Qt MOC ($Id: moc_lightdialog.cpp,v 1.1.1.1 2002/09/27 13:23:40 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "lightdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *LightDialog::className() const
{
    return "LightDialog";
}

QMetaObject *LightDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_LightDialog;

#ifndef QT_NO_TRANSLATION
QString LightDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "LightDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString LightDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "LightDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* LightDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"slotDone", 0, 0 };
    static const QUMethod slot_1 = {"slotCancel", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotDone()", &slot_0, QMetaData::Protected },
	{ "slotCancel()", &slot_1, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"LightDialog", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_LightDialog.setMetaObject( metaObj );
    return metaObj;
}

void* LightDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "LightDialog" ) ) return (LightDialog*)this;
    return QDialog::qt_cast( clname );
}

bool LightDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotDone(); break;
    case 1: slotCancel(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool LightDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool LightDialog::qt_property( int _id, int _f, QVariant* _v)
{
    return QDialog::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
