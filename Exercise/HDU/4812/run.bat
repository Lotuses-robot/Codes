@echo off
:be
maker
std
4812
fc 4812.out 4812.ans > nul
if %errorlevel% == 1 (
    echo diff!
    :stop
    pause
    goto stop
)
echo done
goto be