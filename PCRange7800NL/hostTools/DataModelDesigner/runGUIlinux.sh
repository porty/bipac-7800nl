#!/bin/bash

#
# If you execute this script from the hostTools/DataModelDesigner directory,
# then the following line automatically sets your BUILD_ROOT for you.
# Otherwise, set BUILD_ROOT to point to your CommEngine directory.
#
BUILD_ROOT=`pwd | sed -e 's/hostTools\/DataModelDesigner//'`

java -jar DataModelDesigner.jar -quiet -brcm_dev -buildroot $BUILD_ROOT 


