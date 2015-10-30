#!/bin/bash

set -e # exit on error

pushd $(dirname "${0}")/../../xcode-ct/libmoai > /dev/null

xcodebuild -derivedDataPath build -configuration Release -project cloudteam.xcodeproj -scheme build_all_ios -sdk iphoneos || exit 1

popd > /dev/null