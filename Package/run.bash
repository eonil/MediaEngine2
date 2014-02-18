#!/bin/bash

set -e



build_one_target()
{
	COMP_NAME=$1
	PLATFORM_NAME=$2
	CONFIG_NAME=$3
	SCHEME_NAME="MediaEngine $COMP_NAME - $PLATFORM_NAME Static Library"

	# SYMROOT="$BUILD_ROOT"/"$COMP_NAME"
	# TARGET_BUILD_DIR="$BUILD_ROOT"/"$PLATFORM_NAME"/"$CONFIG_NAME"/"$COMP_NAME"
	SYMROOT="$BUILD_ROOT"
	TARGET_BUILD_DIR="$BUILD_ROOT"/"$PLATFORM_NAME"/"$CONFIG_NAME"

	cd $COMP_NAME
	xcodebuild -configuration "$CONFIG_NAME" -scheme "$SCHEME_NAME" SYMROOT="$SYMROOT" TARGET_BUILD_DIR="$TARGET_BUILD_DIR"
	cd ..
}
build_one_component()
{
	COMP_NAME=$1
	build_one_target "$COMP_NAME" "iOS" "Debug"
	build_one_target "$COMP_NAME" "iOS" "Release"
	build_one_target "$COMP_NAME" "OSX" "Debug"
	build_one_target "$COMP_NAME" "OSX" "Release"
}



BUILD_ROOT=`pwd`/Build
cd ..

build_one_component "Foundation"
build_one_component "Mathematics"
build_one_component "Graphics"
build_one_component "Transcoding"


