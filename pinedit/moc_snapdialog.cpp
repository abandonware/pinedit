/****************************************************************************
** SnapDialog meta object code from reading C++ file 'snapdialog.h'
**
** Created: Mon May 19 21:17:57 2003
**      by: The Qt MOC ($Id: moc_snapdialog.cpp,v 1.2 2003/05/20 21:15:24 pedro_nf Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "snapdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *SnapDialog::className() const
{
    return "SnapDialog";
}

QMetaObject *SnapDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_SnapDialog;

#ifndef QT_NO_TRANSLATION
QString SnapDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SnapDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString SnapDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SnapDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* SnapDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"slotSnap", 0, 0 };
    static const QUMethod slot_1 = {"slotCancel", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotSnap()", &slot_0, QMetaData::Public },
	{ "slotCancel()", &slot_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"SnapDialog", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_SnapDialog.setMetaObject( metaObj );
    return metaObj;
}

void* SnapDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "SnapDialog" ) ) return (SnapDialog*)this;
    return QDialog::qt_cast( clname );
}

bool SnapDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotSnap(); break;
    case 1: slotCancel(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool SnapDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool SnapDialog::qt_property( int _id, int _f, QVariant* _v)
{
    return QDialog::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
