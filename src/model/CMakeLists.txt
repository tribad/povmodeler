##
##  Here we define anything we need to build the libpmmodel.a library
add_library(pmmodel
    pmbicubicpatch.cpp       pmcone.cpp          pmglobalphotons.cpp     pmlight.cpp        pmnamedobject.cpp          pmpovray31format.cpp         pmradiosity.cpp                pmsorsegment.cpp     pmtranslate.cpp
    pmblendmapmodifiers.cpp  pmcontrolpoint.cpp  pmglobalsettings.cpp    pmlightgroup.cpp   pmnormal.cpp               pmpovray31serialization.cpp  pmrainbow.cpp                  pmsphere.cpp         pmtriangle.cpp
    pmblob.cpp               pmcsg.cpp           pmgraphicalobject.cpp   pmline.cpp         pmobject.cpp               pmpovray35format.cpp         pmraw.cpp                      pmspheresweep.cpp    pmviewstructure.cpp
    pmblobcylinder.cpp       pmcylinder.cpp      pmheightfield.cpp       pmlistpattern.cpp  pmobjectlink.cpp           pmpovray35serialization.cpp  pmrecursiveobjectiterator.cpp  pmsplinememento.cpp  pmwarp.cpp
    pmblobsphere.cpp         pmdeclare.cpp       pmimagemap.cpp          pmlookslike.cpp    pmpalettevaluememento.cpp  pmpovrayformat.cpp           pmrotate.cpp                   pmsplinesegment.cpp
    pmboundedby.cpp          pmdensity.cpp       pminsertrulesystem.cpp  pmmapmemento.cpp   pmparser.cpp               pmpovraymatrix.cpp           pmscale.cpp                    pmsqe.cpp
    pmbox.cpp                pmdetailobject.cpp  pminterior.cpp          pmmaterial.cpp     pmpattern.cpp              pmpovrayparser.cpp           pmscene.cpp                    pmsymboltable.cpp
    pmbumpmap.cpp            pmdisc.cpp          pminteriortexture.cpp   pmmaterialmap.cpp  pmphotons.cpp              pmprism.cpp                  pmskysphere.cpp                pmtext.cpp
    pmcamera.cpp             pmenumproperty.cpp  pmisosurface.cpp        pmmedia.cpp        pmpigment.cpp              pmprismmemento.cpp           pmslope.cpp                    pmtexturebase.cpp
    pmclippedby.cpp          pmface.cpp          pmjuliafractal.cpp      pmmemento.cpp      pmplane.cpp                pmprojectedthrough.cpp       pmsolidcolor.cpp               pmtexture.cpp
    pmcomment.cpp            pmfinish.cpp        pmlathe.cpp             pmmesh.cpp         pmpoint.cpp                pmprototypemanager.cpp       pmsolidobject.cpp              pmtexturemap.cpp
    pmcompositeobject.cpp    pmfog.cpp           pmlibraryhandle.cpp     pmmetaobject.cpp   pmpolynom.cpp              pmquickcolor.cpp             pmsor.cpp                      pmtorus.cpp


    )
