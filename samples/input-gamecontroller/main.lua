----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAISim.openWindow ( "test", 320, 480 )

local function printf ( ... )
	return io.stdout:write ( string.format ( ... ))
end 

print ( MOAIInputMgr.configuration )
print ( MOAIInputMgr.device.joystick )

----------------------------------------------------------------
-- joystick events

function onJoystickEvent ( x, y )
	printf ( "joystick axis: %d %d\n", x, y )
end

MOAIInputMgr.device.joystick:setCallback ( onJoystickEvent )
