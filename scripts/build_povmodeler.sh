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
    opensuse-leap)
        export OSPACKAGE=RPM
    ;;
    debian)
        export OSPACKAGE=DEB
    ;;
    linuxmint)
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
##  go to the requested branch
BRANCH=${1:-original}
git checkout $BRANCH
##
##  re-create build environment
cmake .
##
##  cleanup old build
make clean
##
##  build
make -j$((CPUCOUNT+1))
##
##  strip the symbols from the executable.
strip povmodeler
##
##  make the package
cpack -G ${OSPACKAGE}

