/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2000-2003 by Andreas Zehender
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


#include "pmobject.h"
#include "pmcontrolpoint.h"
//#include "pmdialogeditbase.h"
#include "pmmemento.h"
#include "pmprototypemanager.h"
#include "pminsertrulesystem.h"
//#include "pmpart.h"

PMDefinePropertyClass( PMObject, PMObjectProperty );

PMMetaObject* PMObject::s_pMetaObject = nullptr;
//
//  The default constructor.
PMObject::PMObject( )
{
   m_pParent           = nullptr;
   m_selected          = false;
   m_pPrevSibling      = nullptr;
   m_pNextSibling      = nullptr;
   m_pMemento          = nullptr;
   m_readOnly          = false;
   not_visible_in_tree = false;
   map_image_preview   = 0;
   pmt_item            = nullptr;
}
//
//  The copy constructor.
PMObject::PMObject( const PMObject& o )
{
   m_pParent           = nullptr;
   m_selected          = false;
   m_pPrevSibling      = nullptr;
   m_pNextSibling      = nullptr;
   m_pMemento          = nullptr;
   m_readOnly          = false;
   not_visible_in_tree = false;
   map_image_preview   = 0;
   pmt_item            = nullptr;
}

PMObject::~PMObject()
{
}
//
//  The prototypeManager is only needed here in the PMObjects.
const PMPrototypeManager* PMObject::prototypeManager() {
    static PMPrototypeManager mProtoTypeManager;

    return &mProtoTypeManager;
}
//
//  Same with the insertRuleSystem. Is specific to povray objects.
const PMInsertRuleSystem* PMObject::insertRuleSystem() {
    static PMInsertRuleSystem mInsertRuleSystem(prototypeManager());

    return &mInsertRuleSystem;
}
//
//  Here we have some former pure virtuals implementation. This is to make the renewal of
//  the software somehow more comfortable.
//
//  The base class "deep" copy is the copy constructor.
PMObject* PMObject::copy() const {
    PMObject* retval = new PMObject(*this);

    return retval;
}

QString PMObject::description() const {
    return "unspecific object base";
}

void PMObject::serialize( QDomElement& e, QDomDocument& doc ) const {

}

QString PMObject::pixmap() const {
    return "unspecific pixmap";
}

PMMetaObject* PMObject::metaObject() const
{
   if( !s_pMetaObject )
   {
      s_pMetaObject = new PMMetaObject( "Object", nullptr );
      s_pMetaObject->addProperty(
         new PMObjectProperty( "readOnly", &PMObject::setReadOnly, &PMObject::isReadOnly ) );
      s_pMetaObject->addProperty(
         new PMObjectProperty( "numberOfChildren", nullptr, &PMObject::countChildren ) );
   }
   return s_pMetaObject;
}

PMObject* PMObject::newObject() const
{
   return metaObject()->newObject();
}

bool PMObject::insertChildAfter( PMObject*, PMObject* )
{
   qCritical() << "Tried to insert object into a non composite object" << "\n";
   return false;
}

bool PMObject::insertChildBefore( PMObject*, PMObject* )
{
   qCritical(  ) << "Tried to insert object into a non composite object" << "\n";
   return false;
}

void PMObject::setSelected( bool s )
{
   if( m_selected != s )
   {
      if( s )
      {
         if( isSelectable() )
         {
            m_selected = true;
            if( m_pParent )
               m_pParent->adjustSelectedChildren( 1 );
         }
      }
      else
      {
         m_selected = false;
         if( m_pParent )
            m_pParent->adjustSelectedChildren( -1 );
      }
   }
}


bool PMObject::isSelectable()
{
   bool is = true;
   PMObject* o;

   for( o = m_pParent; o && is; o = o->m_pParent )
      if( o->isSelected() )
         is = false;

   return is;
}

bool PMObject::isReadOnly() const
{
   if( m_readOnly )
      return true;
   if( m_pParent )
      return m_pParent->isReadOnly();
   return false;
}

bool PMObject::takeChild( PMObject* )
{
   qCritical(  ) << "Tried to remove object out of a non composite object" << "\n";
   return false;
}

bool PMObject::takeChild( uint )
{
   qCritical(  ) << "Tried to remove object out of a non composite object" << "\n";
   return false;
}

void PMObject::createMemento()
{
   if( m_pMemento )
      delete m_pMemento;
   m_pMemento = new PMMemento( this );
}

PMMemento* PMObject::takeMemento()
{
   PMMemento* tmp = m_pMemento;
   m_pMemento = nullptr;
   return tmp;
}

void PMObject::restoreMemento( PMMemento* /* s */ )
{
   // nothing to be done at the moment
}
PMMatrix PMObject::transformedWith() const
{
   PMMatrix result = PMMatrix::identity();
   const PMObject* o = this;

   if( o->firstChild() )
      o = o->firstChild();
   else if( o->nextSibling() )
      o = o->nextSibling();
   else
      o = o->parent();

   while( o )
   {
      if( o->hasTransformationMatrix() )
         result = o->transformationMatrix() * result;

      if( o->nextSibling() )
         o = o->nextSibling();
      else
         o = o->parent();
   }

   return result;
}

QDomElement PMObject::serialize( QDomDocument& doc ) const
{
   QDomElement e = doc.createElement( className().toLower() );
   serialize( e, doc );
   return e;
}

void PMObject::readAttributes( const PMXMLHelper& )
{
}

void PMObject::cleanUp() const
{
   if( s_pMetaObject )
   {
      delete s_pMetaObject;
      s_pMetaObject = nullptr;
   }
}

bool PMObject::setProperty( const QString& name, const PMVariant& v )
{
   PMPropertyBase* p = metaObject()->property( name );
   if( !p )
      return false;
   return p->setProperty( this, v );
}

QStringList PMObject::properties() const
{
	return metaObject()->properties();
}

PMVariant PMObject::property( const QString& name ) const
{
   PMPropertyBase* p = metaObject()->property( name );
   if( !p )
      return PMVariant();
   return p->getProperty( this );
}

//eticre add visibility in tree
bool PMObject::isVisibleInTree() const
{
   return not_visible_in_tree;
}
void PMObject::setTreeVisibility( bool nn )
{
   not_visible_in_tree = nn;
}


bool PMObject::isA( const QString& className ) const
{
   return prototypeManager()->isA( metaObject(), className );
}

QString PMObject::type() const
{
   return metaObject()->className();
}

bool PMObject::canInsert( const QString& className, const PMObject* after,
                          const PMObjectList* objectsBetween ) const
{
   return insertRuleSystem()->canInsert( this, className, after, objectsBetween );
}

bool PMObject::canInsert( const PMObject* o, const PMObject* after,
                          const PMObjectList* objectsBetween ) const
{
    return insertRuleSystem()->canInsert( this, o, after, objectsBetween );
}

int PMObject::canInsert( const PMObjectList& list, const PMObject* after ) const
{
   return insertRuleSystem()->canInsert( this, list, after );
}

int PMObject::canInsert( const QStringList& classes, const PMObject* after ) const
{
   return insertRuleSystem()->canInsert( this, classes, after );
}
