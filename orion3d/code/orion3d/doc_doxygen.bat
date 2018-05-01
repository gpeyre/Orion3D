title -==[Building Orion3D documentation]==-
echo off
cls
echo Building Orion3D documentation..
pause
..\doc\doxygen.exe doxygen.cfg
"\Program Files\HTML Help Workshop\HHC.EXE" docs_doxy\html\index.hhp
copy .\docs_doxy\html\index.chm ..\doc\win32_doc\orion3d.chm /Y
start ..\doc\win32_doc\orion3d.chm