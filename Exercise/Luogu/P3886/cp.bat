@echo off
:be
python gen.py
std
P3886
fc data.out data.ans > nul
if %errorlevel% == 1 (
    echo diff!
    :stop
    pause
    goto stop
)
echo done
goto be