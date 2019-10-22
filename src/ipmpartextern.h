#ifndef IPMPARTEXTERN_H
#define IPMPARTEXTERN_H
//
//  Some system header.
#include <vector>
//
//  Some Qt header
#include <QString>
//
// Some forwards
// Qt first
class QToolBar;
class QMenu;
//
//  All others.
class IPMShell;

class IPMPartExtern
{
public:
    IPMPartExtern();
    virtual ~IPMPartExtern() {}
    //
    //  This is the factory method to get a PMPart class only accessible through IPMPartExtern
    //  This factory is used by applications/shell classes.
    static IPMPartExtern* construct(IPMShell* shell);
    //
    //  Here starts the interface
    virtual std::vector<QToolBar*> toolbars() = 0;
    virtual QMenu* getMenu(const QString& title) = 0;
};

#endif // IPMPARTEXTERN_H
