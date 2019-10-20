##
##  This is the cmake intro
cmake_minimum_required(VERSION 3.0)
project(pov-qt5)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(OpenGL_GL_PREFERENCE GLVND)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package (OpenGL REQUIRED)
find_package(Freetype REQUIRED)

#find_package(ECM ${ECM_MIN_VERSION} CONFIG REQUIRED)

set(
    CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${ECM_MODULE_PATH}
)
##
##  This is the application install dir. Set fixed for now. Should be changed.
set (XDG_APPS_INSTALL_DIR /usr/local/bin)

#include(ECMInstallIcons)
#include(ECMAddAppIcon)
#include(ECMSetupVersion)

find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core)


find_package(OpenGL REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(Qt5Xml REQUIRED)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(FeatureSummary)

add_feature_info(FREETYPE_FOUND "libfreetype" "FreeType lib is needed to build the povmodeler project" "http://freetype.sf.net" FALSE "" "")

configure_file(config-povmodeler.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-povmodeler.h )

include_directories(${FREETYPE_INCLUDE_DIR})
include_directories("/usr/include/freetype2")
add_compile_options (-O0 -g -Wall)

include_directories(src ${CMAKE_SOURCE_DIR})
add_subdirectory(src)

add_executable(povmodeler add-png-icons.qrc)
target_link_libraries(povmodeler Qt5::Widgets Qt5::Core Qt5::Xml Qt5::DBus OpenGL::OpenGL OpenGL::GLU Freetype::Freetype -Wl,--start-group pmapp pmgui pmmodel pmbase -Wl,--end-group)

########### install files ###############

install( PROGRAMS povmodeler.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES povraydocmap.xml baseinsertrules.xml questionmark.png  DESTINATION  ${DATA_INSTALL_DIR}/povmodeler )

#install( FILES org.povmodeler.xml DESTINATION ${DBUS_INTERFACES_INSTALL_DIR} )
install( DIRECTORY examples/ DESTINATION ${DATA_INSTALL_DIR}/povmodeler/examples )
install( DIRECTORY library/ DESTINATION ${DATA_INSTALL_DIR}/povmodeler/library )

#ecm_install_icons(${ICON_INSTALL_DIR})
