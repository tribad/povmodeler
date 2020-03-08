set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS DBus Xml Core Widgets REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5DBus_INCLUDE_DIRS}  ${Qt5Xml_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS}, widgets)

add_compile_options(-fPIC)

add_library(pmnewui
    pmmainwindow.ui widgets/boxedit.ui
    main.cpp
    pmapp.cpp pmmodel.cpp pmsettings.cpp pmrecentfilelist.cpp
    ipmviewmenu.cpp ipmfilemenu.cpp
    sigpmviewmenu.cpp sigpmtreewidget.cpp sigpmpropertywidget.cpp sigpmfilemenu.cpp

    widgets/pmfactory.cpp widgets/pmeditbase.cpp widgets/pmvectortable.cpp widgets/pmboxedit.cpp
)
