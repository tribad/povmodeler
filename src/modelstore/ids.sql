-- *************************************************************************************************************
--
--  Modul-Name     : ids.sql
--
--  Copyrights by Hans-Juergen Lange <hjl@simulated-universe.de>. All rights reserved.
--
-- *************************************************************************************************************
#ifndef __IDS_INC__
#define __IDS_INC__
--
--
--  This is the list of object ids used to identify object types in the DB
#define IDO_BICUBICPATCH         cast (x'e0ffb190cc8135ae' as bigint)
#define IDO_BLOB                 cast (x'8735a71ac9753573' as bigint)
#define IDO_BOX                  cast (x'b3d06d8a67f03546' as bigint)
#define IDO_CAMERA               cast (x'e605a5961472634d' as bigint)
#define IDO_CONE                 cast (x'27bd9d502d1be332' as bigint)
#define IDO_CYLINDER             cast (x'e0c10378cb5065e4' as bigint)
#define IDO_DIFFERENCE           cast (x'2d5d89dbb771ff50' as bigint)
#define IDO_DISC                 cast (x'1cf211b599101169' as bigint)
#define IDO_FINISH               cast (x'bb8408ad45e6fdd4' as bigint)
#define IDO_HALO                 cast (x'77b55c31a289fe0e' as bigint)
#define IDO_HEIGHTFIELD          cast (x'503ca38958f6df1b' as bigint)
#define IDO_INTERSECTION         cast (x'b44862be89e481a1' as bigint)
#define IDO_ISOSURFACE           cast (x'0ca9ea1ba1f82b3e' as bigint)
#define IDO_JULIAFRACTAL         cast (x'b24bfe3743d723c5' as bigint)
#define IDO_LATHE                cast (x'f25ccc811f8d84cb' as bigint)
#define IDO_LIGHTGROUP           cast (x'd3dddcbedd8522c3' as bigint)
#define IDO_LIGHTSOURCE          cast (x'ab0a21f74fe572fb' as bigint)
#define IDO_MERGE                cast (x'e5b0a54bc73d5bbe' as bigint)
#define IDO_MESH                 cast (x'dce5132574109b8c' as bigint)
#define IDO_MESH2                cast (x'c1debc6029903f83' as bigint)
#define IDO_NORMAL               cast (x'2c5ed2c004b23b3b' as bigint)
#define IDO_OBJECTBASE           cast (x'd7d7fba997361cda' as bigint)
#define IDO_OVUS                 cast (x'9c5580b710afd5b1' as bigint)
#define IDO_PARAMETRIC           cast (x'3fdf09955224c5db' as bigint)
#define IDO_PATTERNEDTEXTURE     cast (x'2e4c478d4e309021' as bigint)
#define IDO_PIGMENT              cast (x'5fac9d3b4cf250a4' as bigint)
#define IDO_POLYGON              cast (x'cb5215f9ce55aa01' as bigint)
#define IDO_PRISM                cast (x'791d57b9ebfb4c02' as bigint)
#define IDO_PROJECT              cast (x'd488ea14033d86f8' as bigint)
#define IDO_SCENE                cast (x'407a76b8ff3b2600' as bigint)
#define IDO_SMOOTHTRIANGLE       cast (x'3cf79e322ce338db' as bigint)
#define IDO_SPHERE               cast (x'ce84cbffa0a2586e' as bigint)
#define IDO_SPHERESWEAP          cast (x'1d267d2e22c78518' as bigint)
#define IDO_SUPERQUADRICELIPSOID cast (x'8c38bb2eca23924f' as bigint)
#define IDO_SURFACEOFREVOLUTION  cast (x'16847f998083b5eb' as bigint)
#define IDO_TEXT                 cast (x'e1b44377806eeb20' as bigint)
#define IDO_TEXTURE              cast (x'4afb14df35684398' as bigint)
#define IDO_TORUS                cast (x'69b4fd5e45a90879' as bigint)
#define IDO_TRIANGLE             cast (x'b579af2a7e288d4d' as bigint)
#define IDO_UNION                cast (x'0ec5dd421a392046' as bigint)
#define IDO_UVMAPPING            cast (x'611703fc15adf3f6' as bigint)
--
--
--  This is the list of attribute ids used to identify object attributes in the DB
#define IDA_                     cast (x'393985c5a9d65040' as bigint)
#define IDA_CONTAINED            cast (x'1bc8faac8dfa28fb' as bigint)
#define IDA_NAME                 cast (x'842f3af822536317' as bigint)
#define IDA_OBJECTSAFTER         cast (x'd13a065a54dcaf71' as bigint)
#define IDA_OBJECTSBEFORE        cast (x'2a1abb6f6646910d' as bigint)
#define IDA_STATE                cast (x'9abc62b337d172c6' as bigint)
--
--
--  This is the list of enumeration ids used to identify enumerator values in the DB

#endif

