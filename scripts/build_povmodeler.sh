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
## Check if QMAKE is set to some location
if [ -z $QMAKE ] ; then
    for QMAKE in /usr/local/bin /usr/bin ; do 
        if [ -x ${QMAKE}/qmake ] ; then 
            echo Checking $QMAKE for a usable qt version.
            ##
            ##  Get the qmake version info
            QMAKE_RESULT=`${QMAKE}/qmake --version`
            ##
            ##  Get the version
            export QT_VERSION=`echo $QMAKE_RESULT | awk '{print substr($0, match ($0, "[0-9]+[.][0-9]+[.][0-9]+"), RLENGTH)}'`
            qt_version=( ${QT_VERSION//./ } )
            export QT_VERSION_MAJOR="${qt_version[0]}"
            export QT_VERSION_MINOR="${qt_version[1]}"
            export QT_VERSION_PATCH="${qt_version[2]}"
            ##
            ##  Get the path. Be aware of the bunch of backslashes. They are because they get more and more reduced so at the end
            ##  awk see's a \s
            export QMAKE_PATH=`echo $QMAKE_RESULT | awk '{print substr($0, match ($0, "[0-9]+[.][0-9]+[.][0-9]+\\\\sin\\\\s")+RLENGTH)}'`
            export QT_INCLUDE_DIR=${QMAKE_PATH}/../include
        fi;
    done 
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
        export OSPACKAGE=NONE
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
if [ "$OSPACKAGE" != "NONE" ] ; then
    cpack -G ${OSPACKAGE}
fi;

