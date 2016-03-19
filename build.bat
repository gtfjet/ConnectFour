call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"

rc -fo resource.res resource.rc
cvtres -machine:ix86 -out:resource.obj resource.res
cl connect_four.c /link resource.obj

del *.obj
del *.res

pause