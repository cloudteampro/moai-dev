#!/bin/bash

set -e # exit on error

pushd $(dirname "${0}")/../../xcode-ct/libmoai > /dev/null

scheme="Release"
value=$1
schemes=(Release Debug AdHoc Distribution)
if [[ " ${schemes[@]} " =~ " ${value} " ]]; then
    scheme=$1
fi

xcodebuild -derivedDataPath build -configuration $scheme -project cloudteam.xcodeproj -scheme build_all_osx MACOSX_DEPLOYMENT_TARGET=10.8

OSX_LIB=../../lib/osx

rm -rf $OSX_LIB
mkdir -p $OSX_LIB
cp -a ./build/Build/Products/$scheme/*.a $OSX_LIB

popd > /dev/null