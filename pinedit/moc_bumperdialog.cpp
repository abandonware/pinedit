/****************************************************************************
** BumperDialog meta object code from reading C++ file 'bumperdialog.h'
**
** Created: Mon May 19 21:17:46 2003
**      by: The Qt MOC ($Id: moc_bumperdialog.cpp,v 1.4 2003/05/20 21:15:24 pedro_nf Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "bumperdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *BumperDialog::className() const
{
    return "BumperDialog";
}

QMetaObject *BumperDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_BumperDialog;

#ifndef QT_NO_TRANSLATION
QString BumperDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "BumperDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString BumperDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "BumperDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* BumperDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"slotDone", 0, 0 };
    static const QUMethod slot_1 = {"slotChooseSound", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotDone()", &slot_0, QMetaData::Protected },
	{ "slotChooseSound()", &slot_1, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"BumperDialog", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_BumperDialog.setMetaObject( metaObj );
    return metaObj;
}

void* BumperDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "BumperDialog" ) ) return (BumperDialog*)this;
    return QDialog::qt_cast( clname );
}

bool BumperDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotDone(); break;
    case 1: slotChooseSound(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool BumperDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool BumperDialog::qt_property( int _id, int _f, QVariant* _v)
{
    return QDialog::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
