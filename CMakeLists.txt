##
##  This is the cmake intro
cmake_minimum_required(VERSION 2.6)
project(povmodeler)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
##
##  Here we look for the OpenGL support.
set(OpenGL_GL_PREFERENCE GLVND)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(POVMODELER_GL_LIB ${OPENGL_gl_LIBRARY})
    set(POVMODELER_GLU_LIB ${OPENGL_glu_LIBRARY})
    if(CMAKE_VERSION VERSION_LESS "3.5.0")
    endif()
else()
    set(POVMODELER_TARGETS OpenGL::OpenGL OpenGL::GLU Freetype::Freetype)
endif()

find_package (OpenGL COMPONENTS OpenGL REQUIRED)
##
##  Here we try to find the freetype library support.

set(POVMODELER_FREETYPE_LIB "freetype")

find_package(Freetype REQUIRED)
##
##  Here we try to find the qt components.
if (NOT DEFINED $ENV{OSID} OR $ENV{OSID} STREQUAL "slackware")
    ##
    ##  setting up the include directories needed.
    if (NOT DEFINED $ENV{QT_INCLUDE_DIR})
        ##message( FATAL_ERROR "QT_INCLUDE_DIR not set")
    endif()
    include_directories($ENV{QT_INCLUDE_DIR}/QtDBus)   
    include_directories($ENV{QT_INCLUDE_DIR}/Qt)   
    include_directories($ENV{QT_INCLUDE_DIR}/QtXml)   
    include_directories($ENV{QT_INCLUDE_DIR}/QtCore)   
    include_directories($ENV{QT_INCLUDE_DIR}/QtGui)   
    include_directories($ENV{QT_INCLUDE_DIR}/QtOpenGL)   
    ##
    ##  Setting up the libraries.
    set(POVMODELER_QT_LIB -lQtGui -lQtCore -lQtDBus -lQtXml -lQtOpenGL -lX11)
    find_package(Qt4)
else()
    if ($ENV{QT_VERSION_MAJOR} STREQUAL "5")
        find_package(Qt5 COMPONENTS DBus Xml Core Widgets REQUIRED)
    else()
        if ($ENV{QT_VERSION_MAJOR} STREQUAL "4")
            find_package(Qt4 REQUIRED DBus Xml Core Widgets OpenGL)
        endif()
    endif()
endif()


set(
    CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
)
##
##  This is the application install dir. Set fixed for now. Should be changed.
set (XDG_APPS_INSTALL_DIR /usr/local/bin)


set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(FeatureSummary)
include(GNUInstallDirs)


add_feature_info(FREETYPE_FOUND "libfreetype" "FreeType lib is needed to build the povmodeler project" "http://freetype.sf.net" FALSE "" "")
##
##  Setup the version info to be used in version.h and the packages.
set(POVMODELER_VERSION_MAJOR "1")
set(POVMODELER_VERSION_MINOR "1")
set(POVMODELER_VERSION_PATCH "4")

configure_file(config-povmodeler.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-povmodeler.h )
configure_file(version.h.in src/version.h)
configure_file(config.h.in src/config.h)

include_directories(${FREETYPE_INCLUDE_DIR})
include_directories("/usr/include/freetype2")
add_compile_options (-O0 -g -Wall -std=c++11)

include_directories(src ${CMAKE_SOURCE_DIR})
add_subdirectory(src)

add_executable(povmodeler add-png-icons.qrc)
##
##  Static linkage to the povmodeler sub-systems.
##  Using --start-group/--end-group to have a recursive symbol resolution.
target_link_libraries(povmodeler -std=c++11 -Wl,--start-group ${POVMODELER_QT_LIB} ${POVMODELER_GLU_LIB} ${POVMODELER_GL_LIB} ${POVMODELER_TARGETS} ${POVMODELER_FREETYPE_LIB} pmgui pmapp pmmodel pmbase -Wl,--end-group)
##
##
##  Here we describe the files and positions of
##  to be installed files.
install( PROGRAMS povmodeler DESTINATION  ${CMAKE_INSTALL_BINDIR} )
##
##  desktop file
install( FILES povmodeler.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
##
##  application specific files
install( FILES povraydocmap.xml baseinsertrules.xml questionmark.png DESTINATION  ${CMAKE_INSTALL_DATAROOTDIR}/povmodeler)
##
## Examples and libraries.
install( DIRECTORY examples/ DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/povmodeler/examples )
install( DIRECTORY library/ DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/povmodeler/library )
##
##  Icon files in various resolutions
install( FILES hi48-app-povmodeler.png DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/48x48/apps/ RENAME povmodeler.png)
install( FILES hi32-app-povmodeler.png DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/32x32/apps/ RENAME povmodeler.png)
install( FILES hi22-app-povmodeler.png DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/22x22/apps/ RENAME povmodeler.png)
install( FILES hi16-app-povmodeler.png DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/16x16/apps/ RENAME povmodeler.png)
##
##  Packaging setup.
##
##  Only supported on unix systems.
IF (UNIX)
##
##  Debian specific switches
SET (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
## SET (CPACK_DEBIAN_PACKAGE_DEBUG ON)
##
##  RPM specific switches
set (CPACK_RPM_PACKAGE_DEBUG OFF)
set (CPACK_RPM_PACKAGE_AUTOREQ ON)
##
##  Some systems do not like it to have the directories in the files to create
set (CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr/share/applications"
                                                   "/usr/share/icons"
                                                   "/usr/share/icons/hicolor"
                                                   "/usr/share/icons/hicolor/16x16"
                                                   "/usr/share/icons/hicolor/16x16/apps"
                                                   "/usr/share/icons/hicolor/22x22"
                                                   "/usr/share/icons/hicolor/22x22/apps"
                                                   "/usr/share/icons/hicolor/32x32"
                                                   "/usr/share/icons/hicolor/32x32/apps"
                                                   "/usr/share/icons/hicolor/48x48"
                                                   "/usr/share/icons/hicolor/48x48/apps"
                                                   )

##set (CPACK_RPM_PACKAGE_REQUIRES "libQt5Widgets, libQt5Xml, libQt5DBus,libOpenGL, libGLU, libfreetype, libQt5Gui, libQt5Core, libGLX, libstdc++, libm, libgcc_s, libc")
##
##
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "This is the former KPovModeler now PovModeler because stripped off the KDE stuff")
SET(CPACK_PACKAGE_VENDOR "Simulated-Universe")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
SET(CPACK_PACKAGE_VERSION_MAJOR ${POVMODELER_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${POVMODELER_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${POVMODELER_VERSION_PATCH})
SET(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")
SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-$ENV{OSID}-$ENV{OSVERSION}")
SET(CPACK_PACKAGE_CONTACT "Hans-Juergen Lange <hjl@simulated-universe.de>")
SET(CPACK_PACKAGE_SECTION "graphics")
INCLUDE(CPack)
ENDIF (UNIX)
