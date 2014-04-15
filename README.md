Raspberry Pi Dashboard
======================

Small app to output system stats to an ili 3941 LCD display.

Requires ajstarks openvg

Compile "gcc -Wall -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I.. -o dashboard dashboard.c ../libshapes.o ../oglinit.o -L/opt/vc/lib -lGLESv2 -ljpeg"
