##
##  Here is all we need for the libpmbase.a library
add_library(pmbase
    pm2dcontrolpoint.cpp  pmcontrolpoint.cpp          pmmath.cpp          pmplanenormalcontrolpoint.cpp  pmscalecontrolpoint.cpp      pmvariant.cpp             pmxmlhelper.cpp
    pm3dcontrolpoint.cpp  pmdistancecontrolpoint.cpp  pmmatrix.cpp        pmrendermode.cpp               pmsorcontrolpoint.cpp        pmvectorcontrolpoint.cpp  pmxmlparser.cpp
    pmcolor.cpp           pmheightfieldroam.cpp       pmpalettevalue.cpp  pmrotatecontrolpoint.cpp       pmtranslatecontrolpoint.cpp  pmvector.cpp

    )
