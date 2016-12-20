#!/bin/bash

set -e # exit on error

pushd $(dirname "${0}") > /dev/null

scheme="Release"
value=$1
schemes=(Release Debug AdHoc Distribution)
if [[ " ${schemes[@]} " =~ " ${value} " ]]; then
    scheme=$1
fi

echo "Start building for ... $scheme"

xcodebuild -derivedDataPath build -configuration $scheme -project cloudteam.xcodeproj -scheme build_all_ios -sdk iphonesimulator
xcodebuild -derivedDataPath build -configuration $scheme -project cloudteam.xcodeproj -scheme build_all_ios -sdk iphoneos

pushd ./build/Build/Products/$scheme-iphoneos/ > /dev/null
rm -rf "../$scheme-universal" # clean out the old dir (if any)
mkdir -p "../$scheme-universal" # make the new dir
for f in *.a
do
	echo $f
	libs="$f ../$scheme-iphonesimulator/$f"

	if ! xcrun lipo -create -output "../$scheme-universal/$f" $libs; then
		echo >&2 "lipo failed, giving up."
		exit 1
	fi
done
popd > /dev/null

IOS_LIB=../../lib/ios

rm -rf $IOS_LIB
mkdir -p $IOS_LIB
cp -a ./build/Build/Products/$scheme-universal/*.a $IOS_LIB

popd > /dev/null