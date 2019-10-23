find_package(Qt5Core REQUIRED)

##
##
##
##
##
##
##
##
##
##
##
##
add_library(pmmodel

    pmobject.cpp pmmodel.cpp pmprototypemanager.cpp pmmetaobject.cpp pminsertrulesystem.cpp
    pmcompositeobject.cpp pmnamedobject.cpp pmgraphicalobject.cpp pmdetailobject.cpp pmsolidobject.cpp
    pmglobalsettings.cpp
    pmbox.cpp pmsphere.cpp pmcylinder.cpp
    pmfog.cpp           pmlibraryhandle.cpp        pmpolynom.cpp              pmquickcolor.cpp             pmsor.cpp                      pmtorus.cpp
    pmcomment.cpp            pmfinish.cpp        pmlathe.cpp             pmmesh.cpp         pmpoint.cpp                                     pmtexturemap.cpp
    pmclippedby.cpp          pmface.cpp          pmjuliafractal.cpp      pmmemento.cpp      pmplane.cpp                pmprojectedthrough.cpp       pmsolidcolor.cpp               pmtexture.cpp
    pmcamera.cpp             pmenumproperty.cpp  pmisosurface.cpp        pmmedia.cpp        pmpigment.cpp              pmprismmemento.cpp           pmslope.cpp                    pmtexturebase.cpp
    pmbumpmap.cpp            pmdisc.cpp          pminteriortexture.cpp   pmmaterialmap.cpp  pmphotons.cpp              pmprism.cpp                  pmskysphere.cpp                pmtext.cpp
    pminterior.cpp          pmmaterial.cpp     pmpattern.cpp              pmpovrayparser.cpp           pmscene.cpp                    pmsymboltable.cpp
    pmboundedby.cpp          pmdensity.cpp         pmmapmemento.cpp   pmparser.cpp               pmpovraymatrix.cpp           pmscale.cpp                    pmsqe.cpp
    pmblobsphere.cpp         pmdeclare.cpp       pmimagemap.cpp          pmlookslike.cpp    pmpalettevaluememento.cpp  pmpovrayformat.cpp           pmrotate.cpp                   pmsplinesegment.cpp
    pmblobcylinder.cpp             pmheightfield.cpp       pmlistpattern.cpp  pmobjectlink.cpp           pmpovray35serialization.cpp  pmrecursiveobjectiterator.cpp  pmsplinememento.cpp  pmwarp.cpp
    pmblob.cpp               pmcsg.cpp              pmline.cpp         pmpovray35format.cpp         pmraw.cpp                      pmspheresweep.cpp    pmviewstructure.cpp
    pmblendmapmodifiers.cpp  pmcontrolpoint.cpp      pmlightgroup.cpp   pmnormal.cpp               pmpovray31serialization.cpp  pmrainbow.cpp                           pmtriangle.cpp
    pmbicubicpatch.cpp       pmcone.cpp          pmglobalphotons.cpp     pmlight.cpp        pmpovray31format.cpp         pmradiosity.cpp                pmsorsegment.cpp     pmtranslate.cpp
    )
