/****************************************************************************
** ArmDialog meta object code from reading C++ file 'armdialog.h'
**
** Created: Fri Sep 27 14:12:39 2002
**      by: The Qt MOC ($Id: moc_armdialog.cpp,v 1.1 2002/09/27 13:23:40 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "armdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ArmDialog::className() const
{
    return "ArmDialog";
}

QMetaObject *ArmDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ArmDialog;

#ifndef QT_NO_TRANSLATION
QString ArmDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ArmDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ArmDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ArmDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ArmDialog::staticMetaObject()
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
	"ArmDialog", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ArmDialog.setMetaObject( metaObj );
    return metaObj;
}

void* ArmDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ArmDialog" ) ) return (ArmDialog*)this;
    return QDialog::qt_cast( clname );
}

bool ArmDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotDone(); break;
    case 1: slotChooseSound(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ArmDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ArmDialog::qt_property( int _id, int _f, QVariant* _v)
{
    return QDialog::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
