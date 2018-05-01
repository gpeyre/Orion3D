@echo off
echo ------------------- copying lib --------------------
copy ..\binaries\orion3d_dll\orion3d.dll %windir%\system\ /Y
copy ..\binaries\orion3d_dll\orion3d_dbg.dll %windir%\system\ /Y
echo ----------------------------------------------------
