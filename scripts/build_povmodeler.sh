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
    slackware)
        export OSPACKAGE=SLACK
    ;;
    *)
        export OSPACKAGE=TGZ
esac

echo "Building for "${OSID}"-"${OSVERSION}" a "${OSPACKAGE}" package"

##
## if  we are root expecting a clone there.
cd /tmp
##
##
##
##  Get the last updates
git clone https://github.com/tribad/povmodeler.git
cd povmodeler
##
##  go to the requested branch
BRANCH=${1:-original}
git checkout $BRANCH
##
##  before starting to build get the version
if [ -e VERSION ] ; then
    source VERSION
else
    echo "Could not read version info"
fi;
##
##  re-create build environment
mkdir build
cd build
cmake ..
##
##  build
make -j$((CPUCOUNT+1))
##
##  strip the symbols from the executable.
strip -s povmodeler
##
##  make the package
if [ "$OSPACKAGE" != "SLACK" ] ; then
    cpack -G ${OSPACKAGE}
else
    mkdir -p /tmp/build/install
    make install DESTDIR=/tmp/build
    cp ../slack-desc /tmp/build/install
    cd /tmp/build/
    makepkg -l y -c n ../povmodeler-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-x86_64-${OSVERSION}.tgz
    cp -a ../povmodeler-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-x86_64-${OSVERSION}.tgz /root/
fi;
rm -rf /tmp/povmodeler

