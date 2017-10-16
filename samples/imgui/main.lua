
MOAISim.openWindow ( "cathead", 960, 640 )

viewport = MOAIViewport.new ()
viewport:setSize ( 960, 640 )
viewport:setScale ( 960, 640 )

print(MOAIImGui)
print(imgui)

MOAIRenderMgr.setRenderTable {
    MOAIImGuiRenderable.new()
}

MOAIImGui.init()
MOAIImGui.newFrame(960, 640)

MOAIGfxDevice.getFrameBuffer():setClearColor(0.5, 0.5, 1, 1)

local pointerSensor = MOAIInputMgr.device.pointer
local mouseLeftSensor = MOAIInputMgr.device.mouseLeft
local mouseRightSensor = MOAIInputMgr.device.mouseRight
local mouseMiddleSensor = MOAIInputMgr.device.mouseMiddle
local wheelSensor = MOAIInputMgr.device.mouseWheel
local keyboardSensor = MOAIInputMgr.device.keyboard

keyboardSensor:setCharCallback(function(char)
    MOAIImGui.setTextInput(char)
end)

keyboardSensor:setKeyCallback(function(code, down)
    MOAIImGui.setKeyDown(code, down)
end)

thread = MOAICoroutine.new()
thread:run(function()

    local dt = coroutine.yield()
    local open = true
    while true do
        MOAIImGui.setMouseDown(0, mouseLeftSensor:isDown())
        MOAIImGui.setMouseDown(1, mouseRightSensor:isDown())
        MOAIImGui.setMouseDown(2, mouseMiddleSensor:isDown())

        MOAIImGui.setMouseMoved(pointerSensor:getLoc())

        -- scale down wheel a bit. It is too fast on SDL/Mac_OS (not sure about win)
        MOAIImGui.setWheelDelta(0.3 * wheelSensor:getDelta())

        MOAIImGui.newFrame(960, 640, dt)
        open = imgui.ShowTestWindow(open)

        MOAIImGui.endFrame()
        dt = coroutine.yield()
    end
end)

