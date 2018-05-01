title -==[Building GW documentation]==-
echo off
cls
echo Building GWML documentation..
pause
doxygen.exe doxygen.cfg
"c:\Program Files\HTML Help Workshop\HHC.EXE" docs_doxy\html\index.hhp
mv ./docs_doxy/html/index.chm ./GWML_doc.chm
tar -cf GWML_Doc.tar docs_doxy/html/
gzip GWML_doc.tar
start ./GWML_doc.chm
pause