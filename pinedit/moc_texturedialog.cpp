/****************************************************************************
** TextureImageWidget meta object code from reading C++ file 'texturedialog.h'
**
** Created: Fri Sep 27 14:12:46 2002
**      by: The Qt MOC ($Id: moc_texturedialog.cpp,v 1.1.1.1 2002/09/27 13:23:40 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "texturedialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *TextureImageWidget::className() const
{
    return "TextureImageWidget";
}

QMetaObject *TextureImageWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_TextureImageWidget;

#ifndef QT_NO_TRANSLATION
QString TextureImageWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TextureImageWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString TextureImageWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TextureImageWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* TextureImageWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"TextureImageWidget", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_TextureImageWidget.setMetaObject( metaObj );
    return metaObj;
}

void* TextureImageWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "TextureImageWidget" ) ) return (TextureImageWidget*)this;
    return QWidget::qt_cast( clname );
}

bool TextureImageWidget::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool TextureImageWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool TextureImageWidget::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES


const char *TextureDialog::className() const
{
    return "TextureDialog";
}

QMetaObject *TextureDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_TextureDialog;

#ifndef QT_NO_TRANSLATION
QString TextureDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TextureDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString TextureDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "TextureDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* TextureDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"slotDone", 0, 0 };
    static const QUMethod slot_1 = {"slotCancel", 0, 0 };
    static const QUMethod slot_2 = {"slotChanged", 0, 0 };
    static const QUMethod slot_3 = {"slotApply", 0, 0 };
    static const QUMethod slot_4 = {"slotSnap", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotDone()", &slot_0, QMetaData::Protected },
	{ "slotCancel()", &slot_1, QMetaData::Protected },
	{ "slotChanged()", &slot_2, QMetaData::Protected },
	{ "slotApply()", &slot_3, QMetaData::Protected },
	{ "slotSnap()", &slot_4, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"TextureDialog", parentObject,
	slot_tbl, 5,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_TextureDialog.setMetaObject( metaObj );
    return metaObj;
}

void* TextureDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "TextureDialog" ) ) return (TextureDialog*)this;
    return QDialog::qt_cast( clname );
}

bool TextureDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotDone(); break;
    case 1: slotCancel(); break;
    case 2: slotChanged(); break;
    case 3: slotApply(); break;
    case 4: slotSnap(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool TextureDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool TextureDialog::qt_property( int _id, int _f, QVariant* _v)
{
    return QDialog::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
