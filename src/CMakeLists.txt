

file(GLOB SOURCES "*.cpp")
file(GLOB MOC_HEADERS "*.h")

include_directories(".")
include_directories("..")

find_package(Qt4 REQUIRED)
set(QT_USE_QT3SUPPORT TRUE)
set(QT_USE_QTOPENGL TRUE)
include(${QT_USE_FILE})


QT4_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )

add_executable(${PINEDIT_EXEC_NAME} ${SOURCES} ${MOC_SRCS})
target_link_libraries(${PINEDIT_EXEC_NAME} Qt4::Qt3Support Qt4::QtOpenGL)

find_package(Pinball REQUIRED)
include_directories(${PINBALL_INCLUDE_DIRS})
target_link_libraries (${PINEDIT_EXEC_NAME} ${PINBALL_LIBRARIES})

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})
target_link_libraries (${PINEDIT_EXEC_NAME} ${SDL_LIBRARY})

find_package(SDL_mixer REQUIRED)
include_directories(${SDL_MIXER_INCLUDE_DIRS})
target_link_libraries (${PINEDIT_EXEC_NAME} ${SDL_MIXER_LIBRARIES})

find_package(SDL_image REQUIRED)
include_directories(${SDL_IMAGE_INCLUDE_DIRS})
target_link_libraries (${PINEDIT_EXEC_NAME} ${SDL_IMAGE_LIBRARIES})

message( STATUS "Checking for libtool" )
find_path( LTDL_INCLUDE_DIR ltdl.h DOC "Libtool include dir" )
find_library( LTDL_LIB ltdl DOC "Libtool lib" )
include_directories(${LTDL_INCLUDE_DIR})
target_link_libraries (${PINEDIT_EXEC_NAME} ${LTDL_LIB})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries (${PINEDIT_EXEC_NAME} ${OPENGL_LIBRARIES})

# Install Target
install(TARGETS ${PINEDIT_EXEC_NAME} RUNTIME DESTINATION games)
