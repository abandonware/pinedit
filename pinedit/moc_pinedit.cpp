/****************************************************************************
** PinEditApp meta object code from reading C++ file 'pinedit.h'
**
** Created: Wed Oct 30 13:26:46 2002
**      by: The Qt MOC ($Id: moc_pinedit.cpp,v 1.2 2002/10/30 14:53:28 henqvist Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "pinedit.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 19)
#error "This file was generated using the moc from 3.0.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *PinEditApp::className() const
{
    return "PinEditApp";
}

QMetaObject *PinEditApp::metaObj = 0;
static QMetaObjectCleanUp cleanUp_PinEditApp;

#ifndef QT_NO_TRANSLATION
QString PinEditApp::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PinEditApp", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString PinEditApp::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PinEditApp", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* PinEditApp::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"slotFileNew", 0, 0 };
    static const QUMethod slot_1 = {"slotFileOpen", 0, 0 };
    static const QUMethod slot_2 = {"slotFileSave", 0, 0 };
    static const QUMethod slot_3 = {"slotFileSaveAs", 0, 0 };
    static const QUMethod slot_4 = {"slotFileSaveGroup", 0, 0 };
    static const QUMethod slot_5 = {"slotFileClose", 0, 0 };
    static const QUMethod slot_6 = {"slotFilePrint", 0, 0 };
    static const QUMethod slot_7 = {"slotFileQuit", 0, 0 };
    static const QUMethod slot_8 = {"slotEditCut", 0, 0 };
    static const QUMethod slot_9 = {"slotEditCopy", 0, 0 };
    static const QUMethod slot_10 = {"slotEditPaste", 0, 0 };
    static const QUParameter param_slot_11[] = {
	{ "toggle", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"slotViewToolBar", 1, param_slot_11 };
    static const QUParameter param_slot_12[] = {
	{ "toggle", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_12 = {"slotViewStatusBar", 1, param_slot_12 };
    static const QUMethod slot_13 = {"slotHelpAbout", 0, 0 };
    static const QUMethod slot_14 = {"slotUndo", 0, 0 };
    static const QUMethod slot_15 = {"slotLoadGroup", 0, 0 };
    static const QUMethod slot_16 = {"slotNewVertex", 0, 0 };
    static const QUMethod slot_17 = {"slotSelect", 0, 0 };
    static const QUMethod slot_18 = {"slotAddSelect", 0, 0 };
    static const QUMethod slot_19 = {"slotUnSelect", 0, 0 };
    static const QUMethod slot_20 = {"slotMove", 0, 0 };
    static const QUMethod slot_21 = {"slotRotate", 0, 0 };
    static const QUMethod slot_22 = {"slotRotateLocal", 0, 0 };
    static const QUMethod slot_23 = {"slotResize", 0, 0 };
    static const QUMethod slot_24 = {"slotResizeLocal", 0, 0 };
    static const QUMethod slot_25 = {"slotHideSelected", 0, 0 };
    static const QUMethod slot_26 = {"slotNewPolygon", 0, 0 };
    static const QUMethod slot_27 = {"slotNewGroup", 0, 0 };
    static const QUMethod slot_28 = {"slotNewShape", 0, 0 };
    static const QUMethod slot_29 = {"slotFlip", 0, 0 };
    static const QUMethod slot_30 = {"slotMoveGroup", 0, 0 };
    static const QUMethod slot_31 = {"slotRotateGroup", 0, 0 };
    static const QUMethod slot_32 = {"slotDeleteGroup", 0, 0 };
    static const QUMethod slot_33 = {"slotDeleteShape", 0, 0 };
    static const QUMethod slot_34 = {"slotDeletePolygon", 0, 0 };
    static const QUMethod slot_35 = {"slotDeleteVertex", 0, 0 };
    static const QUMethod slot_36 = {"slotExtrude", 0, 0 };
    static const QUMethod slot_37 = {"slotSnap", 0, 0 };
    static const QUParameter param_slot_38[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_38 = {"slotMode", 1, param_slot_38 };
    static const QUParameter param_slot_39[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_39 = {"slotZoom", 1, param_slot_39 };
    static const QUParameter param_slot_40[] = {
	{ "mode", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_40 = {"setMode", 1, param_slot_40 };
    static const QMetaData slot_tbl[] = {
	{ "slotFileNew()", &slot_0, QMetaData::Public },
	{ "slotFileOpen()", &slot_1, QMetaData::Public },
	{ "slotFileSave()", &slot_2, QMetaData::Public },
	{ "slotFileSaveAs()", &slot_3, QMetaData::Public },
	{ "slotFileSaveGroup()", &slot_4, QMetaData::Public },
	{ "slotFileClose()", &slot_5, QMetaData::Public },
	{ "slotFilePrint()", &slot_6, QMetaData::Public },
	{ "slotFileQuit()", &slot_7, QMetaData::Public },
	{ "slotEditCut()", &slot_8, QMetaData::Public },
	{ "slotEditCopy()", &slot_9, QMetaData::Public },
	{ "slotEditPaste()", &slot_10, QMetaData::Public },
	{ "slotViewToolBar(bool)", &slot_11, QMetaData::Public },
	{ "slotViewStatusBar(bool)", &slot_12, QMetaData::Public },
	{ "slotHelpAbout()", &slot_13, QMetaData::Public },
	{ "slotUndo()", &slot_14, QMetaData::Public },
	{ "slotLoadGroup()", &slot_15, QMetaData::Public },
	{ "slotNewVertex()", &slot_16, QMetaData::Public },
	{ "slotSelect()", &slot_17, QMetaData::Public },
	{ "slotAddSelect()", &slot_18, QMetaData::Public },
	{ "slotUnSelect()", &slot_19, QMetaData::Public },
	{ "slotMove()", &slot_20, QMetaData::Public },
	{ "slotRotate()", &slot_21, QMetaData::Public },
	{ "slotRotateLocal()", &slot_22, QMetaData::Public },
	{ "slotResize()", &slot_23, QMetaData::Public },
	{ "slotResizeLocal()", &slot_24, QMetaData::Public },
	{ "slotHideSelected()", &slot_25, QMetaData::Public },
	{ "slotNewPolygon()", &slot_26, QMetaData::Public },
	{ "slotNewGroup()", &slot_27, QMetaData::Public },
	{ "slotNewShape()", &slot_28, QMetaData::Public },
	{ "slotFlip()", &slot_29, QMetaData::Public },
	{ "slotMoveGroup()", &slot_30, QMetaData::Public },
	{ "slotRotateGroup()", &slot_31, QMetaData::Public },
	{ "slotDeleteGroup()", &slot_32, QMetaData::Public },
	{ "slotDeleteShape()", &slot_33, QMetaData::Public },
	{ "slotDeletePolygon()", &slot_34, QMetaData::Public },
	{ "slotDeleteVertex()", &slot_35, QMetaData::Public },
	{ "slotExtrude()", &slot_36, QMetaData::Public },
	{ "slotSnap()", &slot_37, QMetaData::Public },
	{ "slotMode(int)", &slot_38, QMetaData::Public },
	{ "slotZoom(int)", &slot_39, QMetaData::Public },
	{ "setMode(int)", &slot_40, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"PinEditApp", parentObject,
	slot_tbl, 41,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_PinEditApp.setMetaObject( metaObj );
    return metaObj;
}

void* PinEditApp::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "PinEditApp" ) ) return (PinEditApp*)this;
    return QMainWindow::qt_cast( clname );
}

bool PinEditApp::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotFileNew(); break;
    case 1: slotFileOpen(); break;
    case 2: slotFileSave(); break;
    case 3: slotFileSaveAs(); break;
    case 4: slotFileSaveGroup(); break;
    case 5: slotFileClose(); break;
    case 6: slotFilePrint(); break;
    case 7: slotFileQuit(); break;
    case 8: slotEditCut(); break;
    case 9: slotEditCopy(); break;
    case 10: slotEditPaste(); break;
    case 11: slotViewToolBar((bool)static_QUType_bool.get(_o+1)); break;
    case 12: slotViewStatusBar((bool)static_QUType_bool.get(_o+1)); break;
    case 13: slotHelpAbout(); break;
    case 14: slotUndo(); break;
    case 15: slotLoadGroup(); break;
    case 16: slotNewVertex(); break;
    case 17: slotSelect(); break;
    case 18: slotAddSelect(); break;
    case 19: slotUnSelect(); break;
    case 20: slotMove(); break;
    case 21: slotRotate(); break;
    case 22: slotRotateLocal(); break;
    case 23: slotResize(); break;
    case 24: slotResizeLocal(); break;
    case 25: slotHideSelected(); break;
    case 26: slotNewPolygon(); break;
    case 27: slotNewGroup(); break;
    case 28: slotNewShape(); break;
    case 29: slotFlip(); break;
    case 30: slotMoveGroup(); break;
    case 31: slotRotateGroup(); break;
    case 32: slotDeleteGroup(); break;
    case 33: slotDeleteShape(); break;
    case 34: slotDeletePolygon(); break;
    case 35: slotDeleteVertex(); break;
    case 36: slotExtrude(); break;
    case 37: slotSnap(); break;
    case 38: slotMode((int)static_QUType_int.get(_o+1)); break;
    case 39: slotZoom((int)static_QUType_int.get(_o+1)); break;
    case 40: setMode((int)static_QUType_int.get(_o+1)); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool PinEditApp::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool PinEditApp::qt_property( int _id, int _f, QVariant* _v)
{
    return QMainWindow::qt_property( _id, _f, _v);
}
#endif // QT_NO_PROPERTIES
