dnl Process this file with autoconf-2.53 to produce a configure script.

dnl init autoconf and automake
AC_INIT(pinedit, 0.0.4, [[henqvist@users.sourceforge.net]])

AM_CONFIG_HEADER(editconfig.h)

AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE

dnl this is a c++ program
CFLAGS="-g -W -Wall"
CXXFLAGS="-g -W -Wall"

AC_CONFIG_SUBDIRS(libltdl)

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_LIBTOOL_DLOPEN
AC_LIBLTDL_CONVENIENCE
AC_PROG_LIBTOOL

AC_SUBST(INCLTDL)
AC_SUBST(LIBLTDL)

dnl *******************************************
dnl PATHS AND DIRS ****************************
dnl data dirs, fuck I hate autoconf, spent 4 hours getting this right had to steal it from 
dnl xine and even that took a couple of hours
if test "x$prefix" = xNONE; then
  prefix="${ac_default_prefix}"
fi

if test "x$exec_prefix" = xNONE; then
  exec_prefix="$prefix"
fi

PIN_DATADIR="$datadir/$PACKAGE"
AC_SUBST(PIN_DATADIR)
eval PIN_DATAPATH=`eval echo "$PIN_DATADIR"`
AC_DEFINE_UNQUOTED(PIN_DATADIR, "$PIN_DATAPATH", [The datadir for the pinball game])

dnl *******************************************
dnl OPENGL ************************************
dnl Figure out which math and GL library to use
case "$target" in
    *-*-cygwin* | *-*-mingw32*)
        MATHLIB=""
        SYS_GL_LIBS="-lopengl32"
        ;;	
    *-*-beos*)
        MATHLIB=""
        SYS_GL_LIBS="-lGL"
        ;;
    *-*-darwin*)
        MATHLIB=""
        SYS_GL_LIBS=""
        ;;
    *-*-aix*)
        if test x$ac_cv_prog_gcc = xyes; then
            CFLAGS="-mthreads"
				fi
        SYS_GL_LIBS=""
        ;;
    *)
        MATHLIB="-lm"
        AC_PATH_X
        AC_PATH_XTRA
        if test x$have_x = xyes; then
            CFLAGS="$CFLAGS $X_CFLAGS"
            SYS_GL_LIBS="$X_PRE_LIBS $X_LIBS $X_EXTRA_LIBS -lGL -lGLU"
        else
            SYS_GL_LIBS="-lGL -lGLU"
        fi
        ;;
esac

AC_SUBST(MATHLIB)

dnl Check for OpenGL
AC_MSG_CHECKING(for OpenGL support)
AC_TRY_COMPILE([
 #if defined(__APPLE__) && defined(__MACH__)
 #include <OpenGL/gl.h>
 #else
 #include <GL/gl.h>
 #endif
], , , AC_MSG_ERROR([*** OpenGL not found on system!]))
AC_MSG_RESULT(yes)
GL_LIBS="$SYS_GL_LIBS"
AC_SUBST(GL_LIBS)
LIBS="$GL_LIBS $LIBS"

dnl *******************************************
dnl SDL ***************************************
AM_PATH_SDL( 1.2.0, , AC_MSG_ERROR([*** SDL version $SDL_VERSION not found! Make sure you have the development package of SDL installed - (www.libsdl.org) - or try to use the --with-sdl-prefix option]) )
CFLAGS="$CFLAGS $SDL_CFLAGS"
CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
LIBS="$SDL_LIBS $LIBS"

dnl SDL_image *********************************
AC_ARG_WITH(sdlimage-prefix, [  --with-sdlimage-prefix=PFX   Prefix where SDL_image library is installed (optional)], sdlimage_prefix="$withval", sdlimage_prefix="")
 
if test x"$sdlimage_prefix" != "x"; then
  SDLIMAGE_LIB="-L$sdlimage_prefix/lib"
  SDLIMAGE_CFLAGS="-I$sdlimage_prefix/include"
  LDFLAGS="$SDLIMAGE_LIB $LDFLAGS"
  CPPFLAGS="$CPPFLAGS $SDLIMAGE_CFLAGS"
  CFLAGS="$CFLAGS $SDLIMAGE_CFLAGS"
fi

AC_CHECK_LIB(SDL_image, IMG_Load, : ,AC_MSG_ERROR([*** libSDL_image not found! Make sure you have the development package of SDL_image installed - (www.libsdl.org) - or try to use the --with-sdlimage-prefix option]), )
 
LIBS="$LIBS -lSDL_image"

dnl SDL_mixer **********************************
AC_ARG_WITH(sdlmixer-prefix, [  --with-sdlmixer-prefix=PFX   Prefix where SDL_mixer library is installed (optinal)], sdlmixer_prefix="$withval", sdlmixer_prefix="")

if test x"$sdlmixer_prefix" != "x"; then
  SDLMIXER_LIB="-L$sdlmixer_prefix/lib"
  SDLMIXER_CFLAGS="-I$sdlmixer_prefix/include"
  LDFLAGS="$SDLMIXER_LIB $LDFLAGS"
  CPPFLAGS="$CPPFLAGS $SDLMIXER_CFLAGS"
  CFLAGS="$CFLAGS $SDLMIXER_CFLAGS"
fi

AC_CHECK_LIB(SDL_mixer, Mix_OpenAudio, : ,AC_MSG_ERROR([*** libSDL_mixer not found. Make sure you have the development package of SDL_mixer installed - (www.libsdl.org) - or try to use --with-sdlmixer-prefix option]), )

LIBS="$LIBS -lSDL_mixer"

dnl ********************************************
dnl PINBALL ************************************
AM_PATH_PINBALL( 0.2.0, , AC_MSG_ERROR([*** Pinball version $PINBALL_VERSION not found! Make sure you pinball installed - (pinball.sourceforge.net) - or try to use the --with-pinball-prefix option]) )
CFLAGS="$CFLAGS $PINBALL_CFLAGS"
CXXFLAGS="$CXXFLAGS $PINBALL_CFLAGS"
LIBS="$PINBALL_LIBS $LIBS"

dnl ********************************************
dnl CPP_UNIT ***********************************

AC_ARG_WITH(unittest, [  --with-unittest         Try to use unitest], use_unittest="yes", use_unittest="no")

if test x"$use_unittest" == "xyes"; then

AM_PATH_CPPUNIT(1.8.0, [
  AC_DEFINE_UNQUOTED(EM_UNIT_TEST, [1], [Unittests]) 
  CPPFLAGS="$CPPFLAGS $CPPUNIT_CFLAGS"	
  CFLAGS="$CFLAGS $CPPUNIT_CFLAGS" 
  LIBS="$LIBS $CPPUNIT_LIBS"
  ], AC_MSG_WARN([*** CppUnit was not found. No unit testing.]))

fi

dnl ********************************************
dnl QT TODO ************************************

gw_CHECK_QT

CPPFLAGS="$CPPFLAGS $QT_CXXFLAGS"
CFLAGS="$CPPFLAGS $QT_CXXFLAGS"


dnl EM_QTDIR=/usr/lib/qt3
dnl AC_SUBST(EM_QTDIR)
dnl CPPFLAGS="$CPPFLAGS -I$EM_QTDIR/include"
dnl CFLAGS="$CPPFLAGS -I$EM_QTDIR/include"
dnl LDFLAGS="$LDFLAGS -L$EM_QTDIR/lib"
dnl LIBS="$LIBS -lqt"

dnl ********************************************
dnl HEADERS ************************************
dnl Checks for header files.
AC_HEADER_STDC

AC_ARG_WITH(debug, [  --with-debug            Compile debug version], use_debug="yes", use_debug="no")

if test x"$use_debug" == "xyes"; then
AC_DEFINE_UNQUOTED(EM_DEBUG, [1], [Build a debug version])
fi

AC_DEFINE_UNQUOTED(EM_USE_SDL, [1], [Build a sdl version])

AC_CONFIG_FILES(Makefile pinedit/Makefile data/Makefile data/audio/Makefile data/template/Makefile data/template/pinball-template data/template/Make-template data/objects/Makefile doc/Makefile)

AC_OUTPUT
