@echo off

where iojs.exe >nul 2>nul
if %errorlevel%==1 (
  @echo iojs not found!
  set continue=1
)
if %errorlevel%==0 (
  echo found iojs
  iojs setup.js
  exit
)

set errorlevel=0

if %continue%==1 (
  where node.exe >nul 2>nul
  if %errorlevel%==1 (
    @echo node not found!
  )
  if %errorlevel%==0 (
    echo found node
    node setup.js
  )
)
