:@echo off

del /s /q /f .\build\Release\Automator.node

call node-gyp configure build --target=%1 --arch=ia32
echo copy
call copy .\build\Release\Automator.node .\dist\Automator%2_ia32.node
call node-gyp configure build --target=%1 --arch=x64
echo copy
call copy .\build\Release\Automator.node .\dist\Automator%2_x64.node