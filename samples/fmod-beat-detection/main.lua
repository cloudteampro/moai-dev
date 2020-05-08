----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAISim.openWindow ( "test", 480, 640 )

viewport = MOAIViewport.new ()
viewport:setSize ( 480, 640 )
viewport:setScale ( 480, -640 )

layer = MOAILayer2D.new ()
layer:setClearColor ( 1, 1, 1, 1 )
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

gfxQuad = MOAIGfxQuad2D.new ()
gfxQuad:setTexture ( "moai.png" )
gfxQuad:setRect ( -64, -64, 64, 64 )
gfxQuad:setUVRect ( 0, 0, 1, 1 )

local function addProp ( x, y, sx, sy )

	local prop = MOAIProp.new ()
	prop:setDeck ( gfxQuad )
	layer:insertProp ( prop )
	prop:setLoc ( x, y )
    prop:setScl ( sx or 1, sy or 1 )
    prop:setPiv ( 0, 64 )
    prop:setColor ( 0, 0, 0, 1 )
    prop.scl = 2
    return prop
end

-- player = addProp ( 0, 200, 0.5 )
-- obstacles = {}

-- for i = 1, 10 do
--     obstacles [ i ] = addProp ( 0, 0, 1, 1 )
--     obstacles [ i ]:setVisible ( false )
-- end


MOAIFmodStudio.init ( 100 )
MOAIFmodStudio.setLogEnabled ( true )

channel = MOAIFmodStudioChannel.new ()
sound = MOAIFmodStudioSound.new ()
sound:loadBGM ( "forward.mp3" )

channel:play ( sound )

detector = MOAIFmodBeatDetector.new ()
detector:attachToChannel ( channel )
detector:reserve ( 6 )

-- 48

-- log scale
-- 0-150Hz,  3
-- 150-400Hz, 6
-- 400-800Hz, 12
-- 800-1600Hz, 24
-- 1600-3200Hz, 48
-- 3200-inf 96

detector:setBand ( 1, 3 )
detector:setBand ( 2, 6 )
detector:setBand ( 3, 12 )
detector:setBand ( 4, 24 )
detector:setBand ( 5, 48 )
detector:setBand ( 6, 96 )

detector:start ()


local elapsed = 0

props = {
    addProp (-150, 100),
    addProp (-100, 100),
    addProp (-50, 100),
    addProp (0, 100),
    addProp (50, 100),
    addProp (100, 100),
    addProp (150, 100)
}

-- detector:setListener ( MOAIFmodBeatDetector.EVENT_BEAT, function ( self, idx )

--     if elapsed > 0.5 and idx == 0 then
--         local found = nil
--         for _, prop in pairs ( obstacles ) do
--             if prop:isVisible () == false then
--                 found = prop
--                 break
--             end
--         end

--         if found then
--             found:setVisible ( true )
--             found:setLoc ( 480, 0 )
--             local action = found:seekLoc ( -480, 0, 0, 2, MOAIEaseType.LINEAR )
--             action:setListener ( MOAIAction.EVENT_STOP, function ()
--                 found:setVisible ( false )
--             end )
--             elapsed = 0
--         end
        
--     end
--     player.scl = 2
--     -- local prop = props [ idx + 1 ]
--     -- prop.scl = 2
-- end )

detector:setListener ( MOAIFmodBeatDetector.EVENT_BEAT, function ( self, idx )

    if props [ idx + 1 ] then
        props [ idx + 1 ].scl = 2
    end
end)

thread = MOAICoroutine.new ()
thread:run ( function ()
    while true do
        for _, prop in pairs ( props ) do
            prop.scl = prop.scl * 0.95        
            prop:setScl ( 0.3, prop.scl )
        end
        coroutine.yield ()
        -- local dt = coroutine.yield ()
        -- elapsed = elapsed + dt
    end
end)




