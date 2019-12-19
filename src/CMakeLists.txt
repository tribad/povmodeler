

if (NOT DEFINED $ENV{OSID} OR $ENV{OSID} STREQUAL "slackware")
else()
     find_package(Qt5 COMPONENTS DBus Xml Core Widgets REQUIRED)
     qt5_add_dbus_interface(dbusadapter org.povmodeler.xml povmodeleradaptor)
endif()
##
##  Here we define anything related to the components and files and other that is part of
##  the povmodeler source tree.
include_directories(gui model base)

add_compile_options(-fPIC)

add_subdirectory(base)
add_subdirectory(gui)
add_subdirectory(model)

add_library(pmapp ${dbusadapter}
    main.cpp          pmdockwidget_private.cpp  pmlibrarymanager.cpp  pmoutputdevice.cpp  pmresourcelocator.cpp  pmshell.cpp
    pmdockwidget.cpp  pmiomanager.cpp           pmlibraryobject.cpp   pmpart.cpp          pmserializer.cpp       pmviewlayoutmanager.cpp
    ipmpartextern.cpp ipmshell.cpp
)
