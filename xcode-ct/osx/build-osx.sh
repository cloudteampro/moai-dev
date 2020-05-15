#!/bin/bash

set -e # exit on error

pushd $(dirname "${0}")/../../xcode-ct/osx > /dev/null

OSX_LIB=../lib/osx
OSX_BIN=../bin/osx

#---------------------------------------------------------------
# build osx
xcodebuild -derivedDataPath build -configuration Release -project moai-osx.xcodeproj -scheme moai-osx -verbose || exit 1

popd > /dev/null