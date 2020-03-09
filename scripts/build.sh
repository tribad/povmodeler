#!/bin/bash
##
##  Check if we get called from the main dir or the build-dir
if [ -x ./build.sh ] ; then
    echo "In build dir"
else
    if [ -x ./scripts/build.sh ] ; then
        echo "In main dir"
    else
        echo "Go to main dir or scripts dir and start it again"
    fi;
fi;

