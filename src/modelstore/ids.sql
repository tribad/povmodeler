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
#define IDO_BLOB         cast (x'8735a71ac9753573' as bigint)
#define IDO_BOX          cast (x'b3d06d8a67f03546' as bigint)
#define IDO_CAMERA       cast (x'e605a5961472634d' as bigint)
#define IDO_CONE         cast (x'27bd9d502d1be332' as bigint)
#define IDO_CYLINDER     cast (x'e0c10378cb5065e4' as bigint)
#define IDO_HEIGHTFIELD  cast (x'503ca38958f6df1b' as bigint)
#define IDO_ISOSURFACE   cast (x'0ca9ea1ba1f82b3e' as bigint)
#define IDO_JULIAFRACTAL cast (x'b24bfe3743d723c5' as bigint)
#define IDO_LATHE        cast (x'f25ccc811f8d84cb' as bigint)
#define IDO_LIGHTGROUP   cast (x'd3dddcbedd8522c3' as bigint)
#define IDO_LIGHTSOURCE  cast (x'ab0a21f74fe572fb' as bigint)
#define IDO_OVUS         cast (x'9c5580b710afd5b1' as bigint)
#define IDO_PARAMETRIC   cast (x'3fdf09955224c5db' as bigint)
#define IDO_PRISM        cast (x'791d57b9ebfb4c02' as bigint)
#define IDO_PROJECT      cast (x'd488ea14033d86f8' as bigint)
#define IDO_SCENE        cast (x'407a76b8ff3b2600' as bigint)
--
--
--  This is the list of attribute ids used to identify object attributes in the DB
#define IDA_NAME         cast (x'842f3af822536317' as bigint)
#define IDA_STATE        cast (x'9abc62b337d172c6' as bigint)
--
--
--  This is the list of enumeration ids used to identify enumerator values in the DB

#endif

