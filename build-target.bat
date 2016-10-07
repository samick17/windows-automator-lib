:@echo off

echo %1 %2
call node-gyp configure build --target=%1
echo copy
call copy .\build\Release\Automator.node .\dist\Automator%2.node