@echo off
echo Building Orion3DMAX documentation..
"..\doc\doxygen.exe" doxygen.cfg
"\Program Files\HTML Help Workshop\HHC.EXE" docs_doxy\html\index.hhp
copy .\docs_doxy\html\index.chm .\docs_doxy\orion3dmax.chm /Y
start .\docs_doxy\orion3dmax.chm