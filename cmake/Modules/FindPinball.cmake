# - Try to find Pinball library
# Once done this will define
#  PINBALL_FOUND - System has Pinball
#  PINBALL_INCLUDE_DIRS - The Pinball include directories
#  PINBALL_LIBRARIES - The libraries needed to use Pinball
#  PINBALL_CONFIG - The pinball config tool

find_package(PkgConfig)
pkg_check_modules(PC_PINBALL QUIET pinball-dev)

find_file(PINBALL_CONFIG pinball-config PATHS /usr/games)

find_path(PINBALL_INCLUDE_DIR Pinball.h
          HINTS ${PC_PINBALL_INCLUDEDIR} ${PC_PINBALL_INCLUDE_DIRS} /usr/include/pinball
          PATH_SUFFIXES pinball )

set(PINBALL_LIBRARY_HINTS ${PC_PINBALL_LIBDIR} ${PC_PINBALL_LIBRARY_DIRS} /usr/lib/pinball /usr/lib/x86_64-linux-gnu/pinball)
find_library(PINBALL_LIBRARY_PIN NAMES libemilia_pin.a
             HINTS ${PINBALL_LIBRARY_HINTS})
find_library(PINBALL_LIBRARY_ADDON NAMES libemilia_addon.a
             HINTS ${PINBALL_LIBRARY_HINTS})
find_library(PINBALL_LIBRARY_BASE NAMES libemilia_base.a
             HINTS ${PINBALL_LIBRARY_HINTS})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PINBALL_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Pinball  DEFAULT_MSG
                                  PINBALL_LIBRARY_PIN PINBALL_LIBRARY_ADDON PINBALL_LIBRARY_BASE PINBALL_INCLUDE_DIR PINBALL_CONFIG)

mark_as_advanced(PINBALL_INCLUDE_DIR PINBALL_LIBRARY_PIN PINBALL_LIBRARY_ADDON PINBALL_LIBRARY_BASE PINBALL_CONFIG)

set(PINBALL_LIBRARIES ${PINBALL_LIBRARY_PIN} ${PINBALL_LIBRARY_ADDON} ${PINBALL_LIBRARY_BASE})
set(PINBALL_INCLUDE_DIRS ${PINBALL_INCLUDE_DIR} )

