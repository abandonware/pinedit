/****************************************************************************
** ModuleDialog meta object code from reading C++ file 'moduledialog.h'
**
** Created: Fri Sep 27 14:13:01 2002
**      by: The Qt MOC ($Id: moc_moduledialog.cpp,v 1.1.1.1 2002/09/27 13:23:40 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "moduledialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ModuleDialog::className() const
{
    return "ModuleDialog";
}

QMetaObject *ModuleDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ModuleDialog;

#ifndef QT_NO_TRANSLATION
QString ModuleDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ModuleDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ModuleDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ModuleDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ModuleDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"slotDone", 0, 0 };
    static const QUMethod slot_1 = {"slotChooseModule", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotDone()", &slot_0, QMetaData::Protected },
	{ "slotChooseModule()", &slot_1, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"ModuleDialog", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ModuleDialog.setMetaObject( metaObj );
    return metaObj;
}

void* ModuleDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ModuleDialog" ) ) return (ModuleDialog*)this;
    return QDialog::qt_cast( clname );
}

bool ModuleDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotDone(); break;
    case 1: slotChooseModule(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ModuleDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ModuleDialog::qt_property( int _id, int _f, QVariant* _v)
{
    return QDialog::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
