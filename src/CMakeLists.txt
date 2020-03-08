

if (NOT DEFINED ID OR ${ID} STREQUAL "slackware")
     find_package(Qt4)
else()
     find_package(Qt5 COMPONENTS DBus Xml Core Widgets REQUIRED)
     qt5_add_dbus_interface(dbusadapter org.povmodeler.xml povmodeleradaptor)
endif()
##
##  Here we define anything related to the components and files and other that is part of
##  the povmodeler source tree.
include_directories(gui model base)

add_compile_options(-fPIC)

add_library(pmapp
    main.cpp
)
