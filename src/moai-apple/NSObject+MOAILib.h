#import <Foundation/Foundation.h>
#import <moai-core/headers.h>

#define OBJC_TO_LUA(obj,state)								\
	if ( obj == nil ) {										\
		lua_pushnil ( state );								\
	}														\
	else {													\
		[ obj toLua:state ];								\
	}

//================================================================//
// NSObject ( MOAILib )
//================================================================//
@interface NSObject ( MOAILib )

	//----------------------------------------------------------------//
	-( id )		isOf				:( id )base;
	+( id )		objectFromLua		:( lua_State* )state stackIndex:( int )idx;
	-( void )	performSelector		:( SEL )selector afterDelay:( float )delay;
	-( void	)	toLua				:( lua_State* )state;

@end

//----------------------------------------------------------------//
extern void loadMoaiLib_NSObject ();
