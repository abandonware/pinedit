/****************************************************************************
** PinEditApp meta object code from reading C++ file 'pinedit.h'
**
** Created: Mon May 19 21:17:19 2003
**      by: The Qt MOC ($Id: moc_pinedit.cpp,v 1.3 2003/05/20 21:15:24 pedro_nf Exp $)
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
    static const QUParameter param_slot_8[] = {
	{ "toggle", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"slotViewToolBar", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "toggle", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"slotViewStatusBar", 1, param_slot_9 };
    static const QUMethod slot_10 = {"slotHelpAbout", 0, 0 };
    static const QUMethod slot_11 = {"slotTutorial", 0, 0 };
    static const QUMethod slot_12 = {"slotManual", 0, 0 };
    static const QUMethod slot_13 = {"slotUndo", 0, 0 };
    static const QUMethod slot_14 = {"slotLoadGroup", 0, 0 };
    static const QUMethod slot_15 = {"slotNewVertex", 0, 0 };
    static const QUMethod slot_16 = {"slotSelect", 0, 0 };
    static const QUMethod slot_17 = {"slotAddSelect", 0, 0 };
    static const QUMethod slot_18 = {"slotUnSelect", 0, 0 };
    static const QUMethod slot_19 = {"slotMove", 0, 0 };
    static const QUMethod slot_20 = {"slotRotate", 0, 0 };
    static const QUMethod slot_21 = {"slotRotateLocal", 0, 0 };
    static const QUMethod slot_22 = {"slotResize", 0, 0 };
    static const QUMethod slot_23 = {"slotResizeLocal", 0, 0 };
    static const QUMethod slot_24 = {"slotCut", 0, 0 };
    static const QUMethod slot_25 = {"slotCopy", 0, 0 };
    static const QUMethod slot_26 = {"slotPaste", 0, 0 };
    static const QUMethod slot_27 = {"slotMirrorX", 0, 0 };
    static const QUMethod slot_28 = {"slotMirrorY", 0, 0 };
    static const QUMethod slot_29 = {"slotMirrorZ", 0, 0 };
    static const QUMethod slot_30 = {"slotMirrorLocalX", 0, 0 };
    static const QUMethod slot_31 = {"slotMirrorLocalY", 0, 0 };
    static const QUMethod slot_32 = {"slotMirrorLocalZ", 0, 0 };
    static const QUMethod slot_33 = {"slotHideSelected", 0, 0 };
    static const QUMethod slot_34 = {"slotNewPolygon", 0, 0 };
    static const QUMethod slot_35 = {"slotNewGroup", 0, 0 };
    static const QUMethod slot_36 = {"slotNewShape", 0, 0 };
    static const QUMethod slot_37 = {"slotFlip", 0, 0 };
    static const QUMethod slot_38 = {"slotMoveGroup", 0, 0 };
    static const QUMethod slot_39 = {"slotRotateGroup", 0, 0 };
    static const QUMethod slot_40 = {"slotDeleteGroup", 0, 0 };
    static const QUMethod slot_41 = {"slotDeleteShape", 0, 0 };
    static const QUMethod slot_42 = {"slotDeletePolygon", 0, 0 };
    static const QUMethod slot_43 = {"slotDeleteVertex", 0, 0 };
    static const QUMethod slot_44 = {"slotExtrude", 0, 0 };
    static const QUMethod slot_45 = {"slotSnap", 0, 0 };
    static const QUParameter param_slot_46[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_46 = {"slotZoom", 1, param_slot_46 };
    static const QUParameter param_slot_47[] = {
	{ "mode", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_47 = {"setMode", 1, param_slot_47 };
    static const QMetaData slot_tbl[] = {
	{ "slotFileNew()", &slot_0, QMetaData::Public },
	{ "slotFileOpen()", &slot_1, QMetaData::Public },
	{ "slotFileSave()", &slot_2, QMetaData::Public },
	{ "slotFileSaveAs()", &slot_3, QMetaData::Public },
	{ "slotFileSaveGroup()", &slot_4, QMetaData::Public },
	{ "slotFileClose()", &slot_5, QMetaData::Public },
	{ "slotFilePrint()", &slot_6, QMetaData::Public },
	{ "slotFileQuit()", &slot_7, QMetaData::Public },
	{ "slotViewToolBar(bool)", &slot_8, QMetaData::Public },
	{ "slotViewStatusBar(bool)", &slot_9, QMetaData::Public },
	{ "slotHelpAbout()", &slot_10, QMetaData::Public },
	{ "slotTutorial()", &slot_11, QMetaData::Public },
	{ "slotManual()", &slot_12, QMetaData::Public },
	{ "slotUndo()", &slot_13, QMetaData::Public },
	{ "slotLoadGroup()", &slot_14, QMetaData::Public },
	{ "slotNewVertex()", &slot_15, QMetaData::Public },
	{ "slotSelect()", &slot_16, QMetaData::Public },
	{ "slotAddSelect()", &slot_17, QMetaData::Public },
	{ "slotUnSelect()", &slot_18, QMetaData::Public },
	{ "slotMove()", &slot_19, QMetaData::Public },
	{ "slotRotate()", &slot_20, QMetaData::Public },
	{ "slotRotateLocal()", &slot_21, QMetaData::Public },
	{ "slotResize()", &slot_22, QMetaData::Public },
	{ "slotResizeLocal()", &slot_23, QMetaData::Public },
	{ "slotCut()", &slot_24, QMetaData::Public },
	{ "slotCopy()", &slot_25, QMetaData::Public },
	{ "slotPaste()", &slot_26, QMetaData::Public },
	{ "slotMirrorX()", &slot_27, QMetaData::Public },
	{ "slotMirrorY()", &slot_28, QMetaData::Public },
	{ "slotMirrorZ()", &slot_29, QMetaData::Public },
	{ "slotMirrorLocalX()", &slot_30, QMetaData::Public },
	{ "slotMirrorLocalY()", &slot_31, QMetaData::Public },
	{ "slotMirrorLocalZ()", &slot_32, QMetaData::Public },
	{ "slotHideSelected()", &slot_33, QMetaData::Public },
	{ "slotNewPolygon()", &slot_34, QMetaData::Public },
	{ "slotNewGroup()", &slot_35, QMetaData::Public },
	{ "slotNewShape()", &slot_36, QMetaData::Public },
	{ "slotFlip()", &slot_37, QMetaData::Public },
	{ "slotMoveGroup()", &slot_38, QMetaData::Public },
	{ "slotRotateGroup()", &slot_39, QMetaData::Public },
	{ "slotDeleteGroup()", &slot_40, QMetaData::Public },
	{ "slotDeleteShape()", &slot_41, QMetaData::Public },
	{ "slotDeletePolygon()", &slot_42, QMetaData::Public },
	{ "slotDeleteVertex()", &slot_43, QMetaData::Public },
	{ "slotExtrude()", &slot_44, QMetaData::Public },
	{ "slotSnap()", &slot_45, QMetaData::Public },
	{ "slotZoom(int)", &slot_46, QMetaData::Public },
	{ "setMode(int)", &slot_47, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"PinEditApp", parentObject,
	slot_tbl, 48,
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
    case 8: slotViewToolBar((bool)static_QUType_bool.get(_o+1)); break;
    case 9: slotViewStatusBar((bool)static_QUType_bool.get(_o+1)); break;
    case 10: slotHelpAbout(); break;
    case 11: slotTutorial(); break;
    case 12: slotManual(); break;
    case 13: slotUndo(); break;
    case 14: slotLoadGroup(); break;
    case 15: slotNewVertex(); break;
    case 16: slotSelect(); break;
    case 17: slotAddSelect(); break;
    case 18: slotUnSelect(); break;
    case 19: slotMove(); break;
    case 20: slotRotate(); break;
    case 21: slotRotateLocal(); break;
    case 22: slotResize(); break;
    case 23: slotResizeLocal(); break;
    case 24: slotCut(); break;
    case 25: slotCopy(); break;
    case 26: slotPaste(); break;
    case 27: slotMirrorX(); break;
    case 28: slotMirrorY(); break;
    case 29: slotMirrorZ(); break;
    case 30: slotMirrorLocalX(); break;
    case 31: slotMirrorLocalY(); break;
    case 32: slotMirrorLocalZ(); break;
    case 33: slotHideSelected(); break;
    case 34: slotNewPolygon(); break;
    case 35: slotNewGroup(); break;
    case 36: slotNewShape(); break;
    case 37: slotFlip(); break;
    case 38: slotMoveGroup(); break;
    case 39: slotRotateGroup(); break;
    case 40: slotDeleteGroup(); break;
    case 41: slotDeleteShape(); break;
    case 42: slotDeletePolygon(); break;
    case 43: slotDeleteVertex(); break;
    case 44: slotExtrude(); break;
    case 45: slotSnap(); break;
    case 46: slotZoom((int)static_QUType_int.get(_o+1)); break;
    case 47: setMode((int)static_QUType_int.get(_o+1)); break;
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
