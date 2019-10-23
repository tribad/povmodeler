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


#include "pmprototypemanager.h"
#include "pmallobjects.h"

PMPrototypeManager::PMPrototypeManager( )
{
   addPrototype( new PMScene( ) );
   addPrototype( new PMGlobalSettings(  ) );
   addPrototype( new PMBox( ) );
   addPrototype( new PMSphere( ) );
   addPrototype( new PMCylinder(  ) );
   addPrototype( new PMCone( ) );
   addPrototype( new PMTorus( ) );
   addPrototype( new PMLathe( ) );
   addPrototype( new PMPrism( ) );

   addPrototype( new PMSurfaceOfRevolution( ) );
   addPrototype( new PMSuperquadricEllipsoid( ) );
   addPrototype( new PMHeightField( ) );
   addPrototype( new PMText( ) );
   addPrototype( new PMJuliaFractal( ) );

   addPrototype( new PMBlob( ) );
   addPrototype( new PMBlobSphere( ) );
   addPrototype( new PMBlobCylinder( ) );

   addPrototype( new PMPlane( ) );
   addPrototype( new PMPolynom( ) );

   addPrototype( new PMCSG( ) );
   //addPrototype( new PMDeclib( ) );
   addPrototype( new PMDeclare( ) );
   addPrototype( new PMObjectLink( ) );

   addPrototype( new PMDisc( ) );
   addPrototype( new PMBicubicPatch( ) );
   addPrototype( new PMTriangle( ) );

   addPrototype( new PMBoundedBy( ) );
   addPrototype( new PMClippedBy( ) );

   addPrototype( new PMTranslate( ) );
   addPrototype( new PMScale( ) );
   addPrototype( new PMRotate( ) );
   addPrototype( new PMPovrayMatrix( ) );
   addPrototype( new PMComment( ) );
   addPrototype( new PMRaw( ) );
   addPrototype( new PMCamera( ) );
   addPrototype( new PMLight( ) );
   addPrototype( new PMLooksLike( ) );
   addPrototype( new PMProjectedThrough( ) );

   addPrototype( new PMTexture( ) );
   addPrototype( new PMPigment( ) );
   addPrototype( new PMSolidColor( ) );
   addPrototype( new PMNormal( ) );
   addPrototype( new PMFinish( ) );
   addPrototype( new PMPattern( ) );
   addPrototype( new PMBlendMapModifiers( ) );
   addPrototype( new PMImageMap( ) );
   addPrototype( new PMTextureMap( ) );
   addPrototype( new PMColorMap( ) );
   addPrototype( new PMPigmentMap( ) );
   addPrototype( new PMNormalMap( ) );
   addPrototype( new PMSlopeMap( ) );
   addPrototype( new PMDensityMap( ) );
   addPrototype( new PMMaterialMap( ) );
   addPrototype( new PMBumpMap( ) );
   addPrototype( new PMTextureList( ) );
   addPrototype( new PMColorList( ) );
   addPrototype( new PMPigmentList( ) );
   addPrototype( new PMNormalList( ) );
   addPrototype( new PMDensityList( ) );
   addPrototype( new PMWarp( ) );
   addPrototype( new PMQuickColor( ) );
   addPrototype( new PMSlope( ) );
   addPrototype( new PMSkySphere( ) );
   addPrototype( new PMRainbow( ) );
   addPrototype( new PMFog( ) );
   addPrototype( new PMInterior( ) );
   addPrototype( new PMMedia( ) );
   addPrototype( new PMMaterial( ) );
   addPrototype( new PMDensity( ) );

   // POV-Ray 3.5 objects
   addPrototype( new PMIsoSurface( ) );
   addPrototype( new PMRadiosity( ) );
   addPrototype( new PMGlobalPhotons( ) );
   addPrototype( new PMPhotons( ) );
   addPrototype( new PMLightGroup( ) );
   addPrototype( new PMInteriorTexture( ) );
   addPrototype( new PMSphereSweep( ) );
   addPrototype( new PMMesh( ) );

   addDeclarationType( "GraphicalObject", ( "object declaration" ), "pmobjectdeclare" );
   addDeclarationType( "Light", ( "object declaration" ), "pmobjectdeclare" );
   addDeclarationType( "Texture", ( "texture declaration" ), "pmtexturedeclare" );
   addDeclarationType( "Pigment", ( "pigment declaration" ), "pmpigmentdeclare" );
   addDeclarationType( "Normal", ( "normal declaration" ), "pmnormaldeclare" );
   addDeclarationType( "Finish", ( "finish declaration" ), "pmfinishdeclare" );
   addDeclarationType( "TextureMap", ( "texture map declaration" ), "pmtexturemapdeclare" );
   addDeclarationType( "PigmentMap", ( "pigment map declaration" ), "pmpigmentmapdeclare" );
   addDeclarationType( "ColorMap", ( "color map declaration" ), "pmcolormapdeclare" );
   addDeclarationType( "NormalMap", ( "normal map declaration" ), "pmnormaldeclare" );
   addDeclarationType( "SlopeMap", ( "slope map declaration" ), "pmslopemapdeclare" );
   addDeclarationType( "DensityMap", ( "density map declaration" ), "pmdensitydeclare" );
   addDeclarationType( "Interior", ( "interior declaration" ), "pminteriordeclare" );
   addDeclarationType( "Media", ( "media declaration" ), "pmmediadeclare" );
   addDeclarationType( "SkySphere", ( "sky sphere declaration" ), "pmskyspheredeclare" );
   addDeclarationType( "Rainbow", ( "rainbow declaration" ), "pmrainbowdeclare" );
   addDeclarationType( "Fog", ( "fog declaration" ), "pmfogdeclare" );
   addDeclarationType( "Material", ( "material declaration" ), "pmmaterialdeclare" );
   addDeclarationType( "Density", ( "density declaration" ), "pmdensitydeclare" );
   addDeclarationType( "InteriorTexture", ( "texture declaration" ), "pminteriortexturedeclare" );
}

PMPrototypeManager::~PMPrototypeManager()
{
}

void PMPrototypeManager::addPrototype( PMObject* obj )
{
   if( !obj )
      return;

   PMMetaObject* metaObject = obj->metaObject();
	QMap<QString, PMMetaObject*>::iterator it = m_metaDict.find( metaObject->className() );
   if( it != m_metaDict.end() )
   {
      qCritical() << "PMPrototypeManager: Class '"
                        << metaObject->className()
                        << "' already registered." << endl;
   }
   else
   {
      if( metaObject->isAbstract() )
         qCritical() << "PMPrototypeManager: The meta object for the prototype "
                           << metaObject->className()
                           << " doesn't have a factory method" << endl;

      m_prototypes.append( metaObject );
      m_lowerCaseDict.insert( metaObject->className().toLower(), metaObject->className() );

      // insert the meta object and all super classes into the hash table
      while( metaObject )
      {
			it = m_metaDict.find( metaObject->className() );
         if( it != m_metaDict.end() )
            metaObject = nullptr;
         else
         {
            m_metaDict.insert( metaObject->className(), metaObject );
            metaObject = metaObject->superClass();
         }
      }
   }
   delete obj;
}

void PMPrototypeManager::addDeclarationType( const QString& className,
                                             const QString& description,
                                             const QString& pixmap )
{
   PMMetaObject* m = metaObject( className );
   if( !m )
      qCritical() << "PMPrototypeManager::addDeclarationType: Unknown class " << className << endl;
   else
      m_declareDescriptions.push_back( PMDeclareDescription( m, description, pixmap ) );
}

const QList<PMMetaObject*>& PMPrototypeManager::prototypes() const
{
   return m_prototypes;
}

const QList<PMDeclareDescription>& PMPrototypeManager::declarationTypes() const
{
   return m_declareDescriptions;
}

PMObject* PMPrototypeManager::newObject( const QString& name ) const
{
   if( name.isEmpty() )
      return nullptr;

	QMap<QString, PMMetaObject*>::const_iterator it = m_metaDict.find( name );
   if( it == m_metaDict.end() )
      return nullptr;
   return it.value()->newObject( );
}

PMMetaObject* PMPrototypeManager::metaObject( const QString& name ) const
{
   if( name.isNull() )
      return nullptr;
	QMap<QString, PMMetaObject*>::const_iterator it = m_metaDict.find( name );
   if( it == m_metaDict.end() )
      return nullptr;
   return it.value();
}

bool PMPrototypeManager::isA( const QString& className,
                              const QString& baseClass ) const
{
   return isA( metaObject( className ), baseClass );
}

bool PMPrototypeManager::isA( const PMMetaObject* c,
                              const QString& baseClass ) const
{
   PMMetaObject* bc = metaObject( baseClass );
   while( c && c != bc )
      c = c->superClass();
   return( c && ( c == bc ) );
}

QString PMPrototypeManager::className( const QString& lowercase ) const
{
   QMap<QString, QString>::const_iterator it = m_lowerCaseDict.find( lowercase );
   if( it != m_lowerCaseDict.end() )
      return *it;
   return QString();
}
