@echo off
mingw32-make
if %ERRORLEVEL%==0 (
    .\HABAH_BABAH.exe
)