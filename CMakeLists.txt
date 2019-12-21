##
##  This is the cmake intro
cmake_minimum_required(VERSION 2.6)
project(povmodeler)
##
##  Load values from the os-release information.
if (EXISTS "/etc/os-release")
    file(STRINGS "/etc/os-release" OSINFO)
    foreach(NameAndValue ${ConfigContents})
        # Strip leading spaces
        string(REGEX REPLACE "^[ ]+" "" NameAndValue ${NameAndValue})
        # Find variable name
        string(REGEX MATCH "^[^=]+" Name ${NameAndValue})
        # Find the value
        string(REPLACE "${Name}=" "" Value ${NameAndValue})
        # Set the variable
        set(${Name} "${Value}")
    endforeach()
else()
    message(WARNING "os-release info not found")
endif()
##
##
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
##  We expect a working pkg-config tool cause this is the most common way to 
##  extract information of the installation pathes and more for the packages.
find_program(PKG_CONFIG "pkg-config")
if (DEFINED PKG_CONFIG)
    foreach(qt_module Core Gui Widgets OpenGL Xml DBus)
        exec_program(pkg-config ARGS --cflags-only-I --silence-errors Qt${qt_module} OUTPUT_VARIABLE QT_INCLUDE)
        ##
        ##  Only process found module info.
        if (NOT ${QT_INCLUDE} STREQUAL "")
            ##
            ##  if there are multiple -I's in the result we need to make a list of it.
            string(REPLACE " " ";" QT_INCLUDE ${QT_INCLUDE})
            ##
            ## and make a big list from it.
            list(APPEND inclist ${QT_INCLUDE})
        endif()
        ##
        ##  Doing it again for the libraries.
        exec_program(pkg-config ARGS --libs-only-l --silence-errors Qt${qt_module} OUTPUT_VARIABLE QT_LIBS)
        ##
        ##  Only process found module info.
        if (NOT ${QT_LIBS} STREQUAL "")
            ##
            ##  if there are multiple -I's in the result we need to make a list of it.
            string(REPLACE " " ";" QT_LIBS ${QT_LIBS})
            ##
            ## and make a big list from it.
            list(APPEND liblist ${QT_LIBS})
        endif()
    endforeach(qt_module)
    ##
    ##  Reduce the list.
    list(REMOVE_DUPLICATES inclist)
    ##
    ##  Now add them to the compiler options.
    foreach(inc ${inclist})
        add_compile_options(${inc})
    endforeach(inc)
    list(REMOVE_DUPLICATES liblist)
    foreach(lib ${liblist})
        ##string(REPLACE POVMODELER_QT_LIB ${POVMODELER_QT_LIB} " " ${lib})
    endforeach(lib)
else()
    message("pkg-config not found")
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
target_link_libraries(povmodeler -std=c++11 -Wl,--start-group -lX11 ${liblist} ${POVMODELER_QT_LIB} ${POVMODELER_GLU_LIB} ${POVMODELER_GL_LIB} ${POVMODELER_TARGETS} ${POVMODELER_FREETYPE_LIB} pmgui pmapp pmmodel pmbase -Wl,--end-group)
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
