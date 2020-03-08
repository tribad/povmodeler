#include "ipmshell.h"
#include "ipmpartextern.h"
#include "pmpart.h"

IPMPartExtern::IPMPartExtern()
{

}

IPMPartExtern* IPMPartExtern::construct(IPMShell* shellIfc) {
    IPMPartExtern* retval = new PMPart(shellIfc);

    return retval;
}
