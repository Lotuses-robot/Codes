:st
python gen.py
C.exe
fc .out .ans > nul
if %errorlevel% == 0 (
    goto st
) else (
    pause
    goto st
)