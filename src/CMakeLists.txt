set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS DBus Xml Core Widgets REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5DBus_INCLUDE_DIRS}  ${Qt5Xml_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

include_directories(newui base model gui)

qt5_add_dbus_interface(dbusadapter org.povmodeler.xml povmodeleradaptor)

add_compile_options(-fPIC)

add_subdirectory(base)
add_subdirectory(newui)
add_subdirectory(model)

add_library(pmapp
    main.cpp
)
