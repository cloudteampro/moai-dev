#!/bin/bash

#----------------------------------------------------------------#
# Copyright (c) 2010-2011 Zipline Games, Inc.
# All Rights Reserved.
# http://getmoai.com
#----------------------------------------------------------------#

set -e # exit on error

pushd $(dirname "${0}") > /dev/null

xcodebuild -derivedDataPath build -configuration Release -project cloudteam.xcodeproj -scheme build_all_ios -sdk iphonesimulator clean
xcodebuild -derivedDataPath build -configuration Release -project cloudteam.xcodeproj -scheme build_all_ios -sdk iphoneos clean

popd > /dev/null