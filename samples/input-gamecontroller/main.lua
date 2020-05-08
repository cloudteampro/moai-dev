----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

WIDTH, HEIGHT = 600, 480
HALFW, HALFH = WIDTH*0.5, HEIGHT*0.5

MOAISim.openWindow ( "test", WIDTH, HEIGHT )

viewport = MOAIViewport.new ()
viewport:setSize ( WIDTH, HEIGHT )
viewport:setScale ( WIDTH, HEIGHT )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

gfxQuad = MOAIGfxQuad2D.new ()
gfxQuad:setTexture ( "moai.png" )
gfxQuad:setRect ( -128, 128, 128, -128 )
gfxQuad:setUVRect ( 0, 0, 1, 1 )

prop = MOAIProp2D.new ()
prop:setDeck ( gfxQuad )
layer:insertProp ( prop )
prop:setScl( 0.3, 0.3 )

moveX = 0
moveY = 0

speed = 200

function updateLoc( dt )
	local x, y = moveX, moveY
	if x ~= 0 or y ~= 0 then
		local cx, cy = prop:getLoc()
		local nx, ny = cx + x * speed * dt, cy + y * speed * dt

		if nx > HALFW then nx = HALFW
		elseif nx < -HALFW then nx = -HALFW end

		if ny > HALFH then ny = HALFH
		elseif ny < -HALFH then ny = -HALFH end

		prop:setLoc( nx, ny )
	end
end

exitGame = false

local thread = MOAICoroutine.new()
thread:run(
	function()
	    local dt = MOAISim.getStep()
	    while true do
	        if exitGame then
	        	print("GAME EXIT")
	            break
	        end

        	updateLoc( dt )

	        dt = coroutine.yield()
	    end
	end
)

MOAIInputMgr.gamepad1.up:setCallback ( function( state ) if state then moveY = 1 else moveY = 0 end end )
MOAIInputMgr.gamepad1.down:setCallback ( function( state ) if state then moveY = -1 else moveY = 0 end end )
MOAIInputMgr.gamepad1.left:setCallback ( function( state ) if state then moveX = -1 else moveX = 0 end end )
MOAIInputMgr.gamepad1.right:setCallback ( function( state ) if state then moveX = 1 else moveX = 0 end end )

MOAIInputMgr.gamepad1.axisLeft:setCallback ( function( x, y ) moveX = x ; moveY = -y end )
MOAIInputMgr.gamepad1.axisRight:setCallback ( function( x, y ) moveX = x ; moveY = -y end )

MOAIInputMgr.gamepad1.a:setCallback ( function( state ) if state then exitGame = true end end )

-- ----------------------------------------------------------------
-- --
-- --

-- local function printf ( ... )
-- 	return io.stdout:write ( string.format ( ... ))
-- end 

-- print ( MOAIInputMgr.configuration )

-- local CONTROLLER_BUTTONS = {
-- 	"a",
--     "b",
--     "x",
--     "y",
--     "back",
--     "guide",
--     "start",
--     "leftStick",
--     "rightStick",
--     "leftShoulder",
--     "rightShoulder",
--     "up",
--     "down",
--     "left",
--     "right",
-- }

-- local CONTROLLER_AXIS = {
-- 	"axisLeft",
--     "axisRight",
--     "axisTrigger",
-- }

-- ----------------------------------------------------------------
-- -- button events

-- for _, name in ipairs(CONTROLLER_BUTTONS) do
-- 	local function onButtonEvent ( flag )
-- 		local i = flag and 1 or 0
-- 		printf ( "joystick %s button: %d\n", name, i )
-- 	end
-- 	MOAIInputMgr.gamepad1[name]:setCallback ( onButtonEvent )
-- end


-- ----------------------------------------------------------------
-- -- axis events

-- for _, name in ipairs(CONTROLLER_AXIS) do
-- 	local function onAxisEvent ( x, y )
-- 		printf ( "joystick %s axis: %d %d\n", name, x, y )
-- 	end

-- 	MOAIInputMgr.gamepad1[name]:setCallback ( onAxisEvent )
-- end
