COMMON = {
	
	[ '3rdparty/LICENSE' ]							= true,

	[ 'src/ct-util/host.h' ]						= 'include/ct-util/host.h',

	[ 'src/lua-headers/moai_lua.h' ]				= 'include/lua-headers/moai_lua.h',
	[ 'src/lua-headers/moai_test_mgr_lua.h' ]		= 'include/lua-headers/moai_test_mgr_lua.h',

	[ 'src/moai-audio-sampler/host.h' ]				= 'include/moai-audio-sampler/host.h',
	[ 'src/moai-box2d/host.h' ]						= 'include/moai-box2d/host.h',
	[ 'src/moai-core/host.h' ]						= 'include/moai-core/host.h',
	[ 'src/moai-crypto/host.h' ]					= 'include/moai-crypto/host.h',
	[ 'src/moai-fmod-studio/host.h' ]				= 'include/moai-fmod-studio/host.h',
	[ 'src/moai-http-client/host.h' ]				= 'include/moai-http-client/host.h',
	[ 'src/moai-http-server/host.h' ]				= 'include/moai-http-server/host.h',
	[ 'src/moai-luaext/host.h' ]					= 'include/moai-luaext/host.h',
	[ 'src/moai-sdl/host.h' ]						= 'include/moai-sdl/host.h',
	[ 'src/moai-sim/host.h' ]						= 'include/moai-sim/host.h',
	[ 'src/moai-sim/MOAIKeyCodeEnum.h' ]			= 'include/moai-sim/MOAIKeyCodeEnum.h',
	[ 'src/moai-sim/MOAIParticle.h' ]				= 'include/moai-sim/MOAIParticle.h',
	[ 'src/moai-sim/host_particles.h' ]				= 'include/moai-sim/host_particles.h',
	[ 'src/moai-spine/host.h' ]						= 'include/moai-spine/host.h',
	[ 'src/moai-untz/host.h' ]						= 'include/moai-untz/host.h',
	[ 'src/moai-util/host.h' ]						= 'include/moai-util/host.h',

	[ 'src/moai-image-jpg/host.h' ]					= 'include/moai-image-jpg/host.h',
	[ 'src/moai-image-png/host.h' ]					= 'include/moai-image-png/host.h',
	[ 'src/moai-image-pvr/host.h' ]					= 'include/moai-image-pvr/host.h',
	[ 'src/moai-image-webp/host.h' ]				= 'include/moai-image-webp/host.h',

	[ 'src/zl-common' ]								= 'include/zl-common',
}

IOS = {

	-- [ 'src/host-ios' ]								= true,
	
	[ 'src/moai-apple/host.h' ]						= 'include/moai-apple/host.h',

	[ 'src/moai-ios/host.h' ]						= 'include/moai-ios/host.h',
	[ 'src/moai-ios-billing/host.h' ]				= 'include/moai-ios-billing/host.h',
	[ 'src/moai-ios-chartboost/host.h' ]			= 'include/moai-ios-chartboost/host.h',
	[ 'src/moai-ios-crashlytics/host.h' ]			= 'include/moai-ios-crashlytics/host.h',
	[ 'src/moai-ios-facebook/host.h' ]				= 'include/moai-ios-facebook/host.h',
	[ 'src/moai-ios-flurry/host.h' ]				= 'include/moai-ios-flurry/host.h',
	[ 'src/moai-ios-gamecenter/host.h' ]			= 'include/moai-ios-gamecenter/host.h',
	[ 'src/moai-ios-motion/host.h' ]				= 'include/moai-ios-motion/host.h',
	[ 'src/moai-ios-movie/host.h' ]					= 'include/moai-ios-movie/host.h',
	[ 'src/moai-ios-unityads/host.h' ]				= 'include/moai-ios-unityads/host.h',

	[ 'lib/ios' ]									= true,

	-- 3rdparty
	[ '3rdparty/Flurry-iOS-7.3.0/Flurry/Flurry.h' ] 			= 'include/Flurry/Flurry.h',
	[ '3rdparty/Flurry-iOS-7.3.0/Flurry/libFlurry_7.3.0.a' ] 	= 'lib/ios/libFlurry_7.3.0.a',

	[ '3rdparty/facebook-ios-sdk-4.7/Bolts.framework' ]			= 'lib/ios/Bolts.framework',
	[ '3rdparty/facebook-ios-sdk-4.7/FBSDKCoreKit.framework' ]	= 'lib/ios/FBSDKCoreKit.framework',
	[ '3rdparty/facebook-ios-sdk-4.7/FBSDKLoginKit.framework' ]	= 'lib/ios/FBSDKLoginKit.framework',
	[ '3rdparty/facebook-ios-sdk-4.7/FBSDKShareKit.framework' ]	= 'lib/ios/FBSDKShareKit.framework',

	[ '3rdparty/chartboost-6.1/Chartboost.framework' ]			= 'lib/ios/Chartboost.framework',
	[ '3rdparty/crashlytics/Crashlytics.framework' ]			= 'lib/ios/Crashlytics.framework',
	[ '3rdparty/crashlytics/Fabric.framework' ]					= 'lib/ios/Fabric.framework',

	[ '3rdparty/fmod-studio/lib/ios/libfmod_iphoneos.a' ]		= 'lib/ios/libfmod_iphoneos.a',

	[ '3rdparty/unity-ads/UnityAds.bundle' ]		= 'lib/ios/UnityAds.bundle',
	[ '3rdparty/unity-ads/UnityAds.framework' ]		= 'lib/ios/UnityAds.framework',
}

CLEAN_DIRS = {
	-- 'lib/android/armeabi-v7a/objs'
}
