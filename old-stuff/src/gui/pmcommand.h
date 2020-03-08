//-*-C++-*-
/*
**************************************************************************
                                 description
                             --------------------
    copyright            : (C) 2000-2001 by Andreas Zehender
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


#ifndef PMCOMMAND_H
#define PMCOMMAND_H



#include <qstring.h>

#include "pmmessage.h"
#include "pmerrorflags.h"
#include "pmchange.h"

class PMCommandManager;
class PMPart;

/**
 * Base class for all commands, that support undo/redo.
 */
class PMCommand
{
   friend class PMCommandManager; // only PMCommandManager can execute commands
public:
   /**
    * Creates an empty command object.
    */
   PMCommand() { }
   /**
    * Creates a command with command text text
    */
   PMCommand( const QString &text )
   { m_text = text; }
   /**
    * Deletes the command.
    */
   virtual ~PMCommand() { }

   /**
    * Command text shown in the undo/redo menues
    */
   QString text() const { return m_text; }
   /**
    * Sets the command text
    */
   void setText( const QString& s ) { m_text = s; }

   /**
    * Checks if the command is valid and sets the error message
    *
    * Returns a bitwise combination of @ref PMErrorFlags flags
    */
   virtual int errorFlags( PMPart* ) { return PMENone; }
   /**
    * Returns the error message
    */
   PMMessageList messages() { return m_errors; }

protected:
   /**
    * Executes the command and stores undo information.
    */
   virtual void execute( PMCommandManager* theManager ) = 0;
   /**
    * Undoes the command
    */
   virtual void undo( PMCommandManager* theManager ) = 0;
   /**
    * The error messages
    */
   PMMessageList m_errors;

private:
   /**
    * The command text.
    */
   QString m_text;
};

#endif
