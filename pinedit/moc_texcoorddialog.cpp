/****************************************************************************
** TexCoordDialog meta object code from reading C++ file 'texcoorddialog.h'
**
** Created: Fri Sep 27 14:12:58 2002
**      by: The Qt MOC ($Id: moc_texcoorddialog.cpp,v 1.1 2002/09/27 13:23:40 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "texcoorddialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *TexCoordDialog::className() const
{
    return "TexCoordDialog";
}

QMetaObject *TexCoordDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_TexCoordDialog;

#ifndef QT_NO_TRANSLATION
QString TexCoordDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TexCoordDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString TexCoordDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TexCoordDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* TexCoordDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"slotTexCoord", 0, 0 };
    static const QUMethod slot_1 = {"slotCancel", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotTexCoord()", &slot_0, QMetaData::Public },
	{ "slotCancel()", &slot_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"TexCoordDialog", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_TexCoordDialog.setMetaObject( metaObj );
    return metaObj;
}

void* TexCoordDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "TexCoordDialog" ) ) return (TexCoordDialog*)this;
    return QDialog::qt_cast( clname );
}

bool TexCoordDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotTexCoord(); break;
    case 1: slotCancel(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool TexCoordDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool TexCoordDialog::qt_property( int _id, int _f, QVariant* _v)
{
    return QDialog::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
