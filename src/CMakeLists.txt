set(CMAKE_AUTOUIC ON)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5DBus_INCLUDE_DIRS}  ${Qt5Xml_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

include_directories(newui base model)

qt5_add_dbus_interface(dbusadapter org.povmodeler.xml povmodeleradaptor)

add_compile_options(-fPIC)

add_subdirectory(base)
add_subdirectory(newui)
add_subdirectory(model)
