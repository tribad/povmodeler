##
##  This is the cmake intro
cmake_minimum_required(VERSION 3.0)
project(povmodeler)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(OpenGL_GL_PREFERENCE GLVND)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package (OpenGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(Qt5 COMPONENTS DBus Xml Core Widgets REQUIRED)

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

configure_file(config-povmodeler.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-povmodeler.h )

include_directories(${FREETYPE_INCLUDE_DIR})
include_directories("/usr/include/freetype2")
add_compile_options (-O0 -g -Wall)

include_directories(src ${CMAKE_SOURCE_DIR})
add_subdirectory(src)

add_executable(povmodeler add-png-icons.qrc)

target_link_libraries(povmodeler Qt5::Widgets Qt5::Core Qt5::Xml Qt5::DBus OpenGL::OpenGL OpenGL::GLU Freetype::Freetype -Wl,--start-group pmgui pmapp pmmodel pmbase -Wl,--end-group)

########### install files ###############

install( PROGRAMS povmodeler DESTINATION  ${CMAKE_INSTALL_BINDIR} )
install( FILES povmodeler.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
install( FILES povraydocmap.xml baseinsertrules.xml
    hi16-app-kpovmodeler.png   hi22-app-kpovmodeler.png hi32-app-kpovmodeler.png  hi48-app-kpovmodeler.png questionmark.png
    DESTINATION  ${CMAKE_INSTALL_DATAROOTDIR}/povmodeler )

install( DIRECTORY examples/ DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/povmodeler/examples )
install( DIRECTORY library/ DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/povmodeler/library )
