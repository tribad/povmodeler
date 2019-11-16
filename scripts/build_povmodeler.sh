#!/bin/bash
##
##
## This is a build script mainly used to produce os-specific package on some of my very own
## virtual machines.
##
## Making it more robust is coming some day.
##
## Checking the more and more getting available of the os-release information
if [ -e /etc/os-release ] ; then
    source /etc/os-release
    export OSID=$ID
    export OSVERSION=$VERSION_ID
else
    echo "Could not find os-release information"
fi;
##
##  Checking the number of CPUs available
CPUCOUNT=`cat /proc/cpuinfo | grep processor -c`
##
##  Detect the packager
case $OSID in
    fedora)
    export OSPACKAGE=RPM
    ;;
    debian)
    export OSPACKAGE=DEB
    ;;
    *)
    export OSPACKAGE=TGZ
esac

echo "Building for "${OSID}"-"${OSVERSION}" a "${OSPACKAGE}" package"

##
## if  we are root expecting a clone there.
if [ "$UID" = "0" ]; then
    cd /usr/src/povmodeler
fi;
##
##
##
##  Get the last updates
git pull
##
##  go to the original
git checkout original
##
##  cleanup old build
make clean
##
##  re-create build environment
cmake .
##
##  build
make -j${CPUCOUNT}
##
##  make the package
cpack -G ${OSPACKAGE}

