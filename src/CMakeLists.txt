find_package(Qt5 COMPONENTS DBus Xml Core Widgets REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5DBus_INCLUDE_DIRS}  ${Qt5Xml_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

include_directories(gui model base)

qt5_add_dbus_interface(dbusadapter org.povmodeler.xml povmodeleradaptor)

add_compile_options(-fPIC)

add_subdirectory(base)
add_subdirectory(gui)
add_subdirectory(model)

add_library(pmapp ${dbusadapter}
    main.cpp          pmdockwidget_private.cpp  pmlibrarymanager.cpp  pmoutputdevice.cpp  pmresourcelocator.cpp  pmshell.cpp
    pmdockwidget.cpp  pmiomanager.cpp           pmlibraryobject.cpp   pmpart.cpp          pmrendermanager.cpp  pmserializer.cpp       pmviewlayoutmanager.cpp
    )
