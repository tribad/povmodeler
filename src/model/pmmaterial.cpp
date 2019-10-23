/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2000-2002 by Andreas Zehender
    email                : zehender@kde.org
**************************************************************************

**************************************************************************
*                                                                        *
*  This program is free software; you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by  *
*  the Free Software Foundation; either version 2 of the License, or     *
*  (at your option) any later version.                                   *
*                                                                        *
**************************************************************************/


#include "pmmaterial.h"
#include "pmxmlhelper.h"
#include "pmmemento.h"
#include "pmmaterialedit.h"



PMMetaObject* PMMaterial::s_pMetaObject = 0;
PMObject* createNewMaterial( )
{
   return new PMMaterial( );
}

PMMaterial::PMMaterial( )
      : Base( )
{
}

PMMaterial::PMMaterial( const PMMaterial& m )
      : Base( m )
{
}

PMMaterial::~PMMaterial()
{
}

PMMetaObject* PMMaterial::metaObject() const
{
   if( !s_pMetaObject )
   {
      s_pMetaObject = new PMMetaObject( "Material", Base::metaObject(),
                                        createNewMaterial );
   }
   return s_pMetaObject;
}

void PMMaterial::cleanUp() const
{
   if( s_pMetaObject )
   {
      delete s_pMetaObject;
      s_pMetaObject = 0;
   }
   Base::cleanUp();
}

QString PMMaterial::description() const
{
   return ( "material" );
}

