#!/bin/bash

#----------------------------------------------------------------#
# Copyright (c) 2010-2011 Zipline Games, Inc.
# All Rights Reserved.
# http://getmoai.com
#----------------------------------------------------------------#

set -e # exit on error

pushd $(dirname "${0}") > /dev/null

scheme="Release"
value=$1
schemes=(Release Debug AdHoc Distribution)
if [[ " ${schemes[@]} " =~ " ${value} " ]]; then
    scheme=$1
fi

xcodebuild -derivedDataPath build -configuration $scheme -project cloudteam.xcodeproj -scheme libmoai-osx-all clean

popd > /dev/null