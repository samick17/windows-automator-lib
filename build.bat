@echo off

node-gyp configure build
copy .\build\Release\Automator.node .\dist\Automator.node