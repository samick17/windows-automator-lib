@echo off

call node-gyp configure build
call copy .\build\Release\Automator.node .\dist\Automator.node