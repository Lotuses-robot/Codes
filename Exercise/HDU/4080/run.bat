@echo off
:be
maker
std
4080
fc 4080.out 4080.ans > nul
if %errorlevel% == 1 (
    echo diff!
    :stop
    pause
    goto stop
)
echo done
goto be