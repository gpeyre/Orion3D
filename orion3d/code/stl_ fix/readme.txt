---

THIS IS VERY IMPORTANT :

Due to a major bug in Visual C++ 6.0 STL, 
you have to replace the file 'xtree' in your
include/ directory by this one.

If you do not so, any access to a STL map in a
multithreads application will cause Orion3D to
crach. And there are a *lot* of maps in Orion3D ...

More infomations about this trouble can be found
on the Dinkumware web site :
http://www.dinkumware.com/

----