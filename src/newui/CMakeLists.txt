set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS DBus Xml Core Widgets REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5DBus_INCLUDE_DIRS}  ${Qt5Xml_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

add_compile_options(-fPIC)

add_library(pmnewui
    pmapp.cpp                 pmmainwindow.ui           ipmviewmenu.cpp     sigpmviewmenu.cpp
)
