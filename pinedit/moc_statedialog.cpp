/****************************************************************************
** StateDialog meta object code from reading C++ file 'statedialog.h'
**
** Created: Fri Sep 27 14:12:31 2002
**      by: The Qt MOC ($Id: moc_statedialog.cpp,v 1.1 2002/09/27 13:23:40 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "statedialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *StateDialog::className() const
{
    return "StateDialog";
}

QMetaObject *StateDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_StateDialog;

#ifndef QT_NO_TRANSLATION
QString StateDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StateDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString StateDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "StateDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* StateDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"slotChanged", 0, 0 };
    static const QUMethod slot_1 = {"slotDone", 0, 0 };
    static const QUMethod slot_2 = {"slotAdd", 0, 0 };
    static const QUMethod slot_3 = {"slotDel", 0, 0 };
    static const QUMethod slot_4 = {"slotApply", 0, 0 };
    static const QUMethod slot_5 = {"slotNewSignal", 0, 0 };
    static const QUMethod slot_6 = {"slotChooseSound", 0, 0 };
    static const QUMethod slot_7 = {"slotChooseMusic", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotChanged()", &slot_0, QMetaData::Protected },
	{ "slotDone()", &slot_1, QMetaData::Protected },
	{ "slotAdd()", &slot_2, QMetaData::Protected },
	{ "slotDel()", &slot_3, QMetaData::Protected },
	{ "slotApply()", &slot_4, QMetaData::Protected },
	{ "slotNewSignal()", &slot_5, QMetaData::Protected },
	{ "slotChooseSound()", &slot_6, QMetaData::Protected },
	{ "slotChooseMusic()", &slot_7, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"StateDialog", parentObject,
	slot_tbl, 8,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_StateDialog.setMetaObject( metaObj );
    return metaObj;
}

void* StateDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "StateDialog" ) ) return (StateDialog*)this;
    return QDialog::qt_cast( clname );
}

bool StateDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotChanged(); break;
    case 1: slotDone(); break;
    case 2: slotAdd(); break;
    case 3: slotDel(); break;
    case 4: slotApply(); break;
    case 5: slotNewSignal(); break;
    case 6: slotChooseSound(); break;
    case 7: slotChooseMusic(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool StateDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool StateDialog::qt_property( int _id, int _f, QVariant* _v)
{
    return QDialog::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
