AUTOMAKE_OPTIONS = gnu

bin_PROGRAMS = pinedit #unittest

#noinst_LIBRARIES = libeditstatic.a

pinedit_LDADD   = -lGL -lGLU -lemilia_pin -lemilia_base -lemilia_addon -lXext -lX11 $(QT_LDADD) @LIBLTDL@ 
pinedit_LDFLAGS = -L. -export-dynamic

#unittest_LDADD   = -lGL -lGLU -lglut -lemilia_pin -lemilia_base -lemilia_addon -lXext -lX11
#unittest_LDFLAGS = -L../../pinball/base -L../../pinball/addon -L../../pinball/visitor -L../../pinball/src -L.

INCLUDES = @INCLTDL@

dnl MOC = $(EM_QTDIR)/bin/moc

moc_%.cpp : %.h
	@echo "Creating Meta $< ..."
	$(MOC) $< -o $@

#unittest_SOURCES = \
#unittest.cpp

#pinedit_SOURCES = \
#main.cpp

pinedit_SOURCES = \
main.cpp \
command.cpp \
commandselect.cpp \
commandsnap.cpp \
commandaddselect.cpp \
commandnewvertex.cpp \
commandnewpolygon.cpp \
commanddeletepolygon.cpp \
commanddeletevertex.cpp \
commandunselect.cpp \
commandnewgroup.cpp \
commandnewshape.cpp \
commandnewbehavior.cpp \
commandmove.cpp \
commandflip.cpp \
commandflipsmart.cpp \
commandmovegroup.cpp \
commandrotategroup.cpp \
commandrotate.cpp \
commandrotatelocal.cpp \
commanddeletegroup.cpp \
commanddeleteshape.cpp \
commandresize.cpp \
commandresizelocal.cpp \
commandextrude.cpp \
commandtexcoord.cpp \
commandhideselected.cpp \
commandcopy.cpp \
commandpaste.cpp \
commandmirror.cpp \
commandmirrorlocal.cpp \
glengine.cpp \
view2d.cpp \
shapeview.cpp \
textureview.cpp \
statedialog.cpp \
bumperdialog.cpp \
armdialog.cpp \
lightdialog.cpp \
texcoorddialog.cpp \
snapdialog.cpp \
textdialog.cpp \
polygonview.cpp \
pineditview.cpp \
pineditdoc.cpp \
pinedit.cpp \
fileutil.cpp \
moduledialog.cpp \
moc_glengine.cpp \
moc_pinedit.cpp \
moc_pineditdoc.cpp \
moc_pineditview.cpp \
moc_view2d.cpp \
moc_shapeview.cpp \
moc_textureview.cpp \
moc_statedialog.cpp \
moc_bumperdialog.cpp \
moc_armdialog.cpp \
moc_lightdialog.cpp \
moc_snapdialog.cpp \
moc_textdialog.cpp \
moc_polygonview.cpp \
moc_texcoorddialog.cpp \
moc_moduledialog.cpp

noinst_HEADERS = \
command.h \
commandnewvertex.h \
commandnewpolygon.h \
commanddeletepolygon.h \
commanddeletevertex.h \
commandselect.h \
commandsnap.h \
commandaddselect.h \
commandunselect.h \
commandnewgroup.h \
commandnewshape.h \
commandnewbehavior.h \
commandmove.h \
commandflip.h \
commandflipsmart.h \
commandmovegroup.h \
commandrotategroup.h \
commandrotate.h \
commandrotatelocal.h \
commanddeletegroup.h \
commanddeleteshape.h \
commandresize.h \
commandresizelocal.h \
commandextrude.h \
commandtexcoord.h \
commandhideselected.h \
commandcopy.h \
commandpaste.h \
commandmirror.h \
commandmirrorlocal.h \
testcommand.h \
testpineditdoc.h \
glengine.h \
view2d.h \
shapeview.h \
textureview.h \
statedialog.h \
bumperdialog.h \
armdialog.h \
lightdialog.h \
listitem.h \
texcoorddialog.h \
snapdialog.h \
textdialog.h \
polygonview.h \
pinedit.h \
pineditdoc.h \
pineditview.h \
fileutil.h \
moduledialog.h \
lo32-app-pinedit.png \
lo16-app-pinedit.png \
editicon.xpm \
manual.xpm \
tutorial.xpm \
filesave.xpm \
fileopen.xpm \
filenew.xpm \
filesavegroup.xpm \
filesaveshape.xpm \
workloadshape.xpm \
workloadgroup.xpm \
worknewvertex.xpm \
workselect.xpm \
workaddselect.xpm \
workunselect.xpm \
worknewpolygon.xpm \
worknewshape.xpm \
worknewgroup.xpm \
workmove.xpm \
workflip.xpm \
workflipsmart.xpm \
workmovegroup.xpm \
workrotategroup.xpm \
workrotate.xpm \
workrotatelocal.xpm \
workdeletegroup.xpm \
workdeleteshape.xpm \
workdeletepolygon.xpm \
workdeletevertex.xpm \
worksnap.xpm \
workresize.xpm \
workresizelocal.xpm \
workextrude.xpm \
workhideselected.xpm \
workundo.xpm \
workcopy.xpm \
workpaste.xpm \
workmirrorx.xpm \
workmirrory.xpm \
workmirrorz.xpm \
workmirrorlocalx.xpm \
workmirrorlocaly.xpm \
workmirrorlocalz.xpm


