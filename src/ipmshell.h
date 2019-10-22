#ifndef IPMSHELL_H
#define IPMSHELL_H
//
//  System includes
#include <QString>
//
//  Some forwards
class PMIMenuBar;

class IPMShell
{
public:
    IPMShell();
    virtual ~IPMShell() {}
    //
    //  The interface that PMPart uses.
    virtual PMIMenuBar* GetMainWindowMenuBar() = 0;
    virtual void modified(bool m) = 0;
    virtual void slotControlPointMsg( const QString& msg = QString() ) = 0;
};

#endif // IPMSHELL_H
