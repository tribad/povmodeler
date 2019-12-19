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

#include <iostream>
#include <QApplication>
#include <QLocale>
#include "pmshell.h"
//#include "pmrendermanager.h"
#include "version.h"

static void print_help() {
}

static void process_long_parameter(QString parameter)
{
    if (parameter == "help") {
        print_help();
    } else {
    std::cerr << "unrecognized long option : " << parameter.toUtf8().constData() << std::endl;
    }
}

int main( int argc, char* argv[] )
{
    PMShell* shell = nullptr;

    QApplication app( argc, argv ); // PORTING SCRIPT: move this to before the KAboutData initialization

    /*
     * Parse the program parameters.
     */
    QList<QString> positionalArguments;
    int i = 1;

    while ((i<argc) && (argv[i]!=0)) {
        char *s=argv[i];

        if (*s=='-') {
            s++;
            switch (*s) {
            case 'h':
            case '?':
            case '-':    //  Long parameter
                s++;     //  Move on to parameter name
                process_long_parameter(s);
                break;
            default:
                std::cerr << "unrecognized option : " << s << std::endl;
                break;
            }
        } else {
            positionalArguments.push_back(QString(s));
        }
        i++;
    }

    QCoreApplication::setOrganizationName( "povmodeler" );
    QCoreApplication::setApplicationName( "povmodeler" );

    if( positionalArguments.count() > 0 )
    {
        for( int i = 0 ; i < positionalArguments.count() ; i++ )
        {
            shell = new PMShell( positionalArguments.at( i ) );
            shell->show();
        }
    }
    else
    {
        shell = new PMShell;
        shell->show();
    }
    return app.exec();
}
