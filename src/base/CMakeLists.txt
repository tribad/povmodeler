find_package(Qt5 COMPONENTS Core REQUIRED)

##
##                                      pmxmlparser.cpp
##


add_library(pmbase
    pmmatrix.cpp pmvariant.cpp pmvector.cpp pmmath.cpp pmcolor.cpp pmxmlhelper.cpp pm3dcontrolpoint.cpp pmdistancecontrolpoint.cpp
    pmplanenormalcontrolpoint.cpp  pmplanenormalcontrolpoint.cpp pm2dcontrolpoint.cpp pmsorcontrolpoint.cpp pmvectorcontrolpoint.cpp
    pmcontrolpoint.cpp pmscalecontrolpoint.cpp pmrotatecontrolpoint.cpp pmtranslatecontrolpoint.cpp pmresourcelocator.cpp pmtruetypecache.cpp
    pmrendermode.cpp pmmessage.cpp  pmpalettevalue.cpp
    pmheightfieldroam.cpp
    )
