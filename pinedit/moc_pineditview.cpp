/****************************************************************************
** PinEditView meta object code from reading C++ file 'pineditview.h'
**
** Created: Wed Oct 30 13:26:56 2002
**      by: The Qt MOC ($Id: moc_pineditview.cpp,v 1.2 2002/10/30 14:53:28 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "pineditview.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *PinEditView::className() const
{
    return "PinEditView";
}

QMetaObject *PinEditView::metaObj = 0;
static QMetaObjectCleanUp cleanUp_PinEditView;

#ifndef QT_NO_TRANSLATION
QString PinEditView::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PinEditView", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString PinEditView::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PinEditView", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* PinEditView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotDocumentChanged", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotDocumentChanged()", &slot_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"PinEditView", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_PinEditView.setMetaObject( metaObj );
    return metaObj;
}

void* PinEditView::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "PinEditView" ) ) return (PinEditView*)this;
    return QWidget::qt_cast( clname );
}

bool PinEditView::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotDocumentChanged(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool PinEditView::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool PinEditView::qt_property( int _id, int _f, QVariant* _v)
{
    return QWidget::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
