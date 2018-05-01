title -==[Building OrionViewer documentation]==-
echo off
cls
echo Building OrionViewer documentation..
pause
..\doc\doxygen.exe doxygen.cfg
"\Program Files\HTML Help Workshop\HHC.EXE" docs_doxy\html\index.hhp
copy .\docs_doxy\html\index.chm ..\doc\win32_doc\orionviewer.chm /Y
start ..\doc\win32_doc\orionviewer.chm