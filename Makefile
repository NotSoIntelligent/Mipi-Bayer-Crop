all rawProcess : rawProcess.o 
	cc rawProcess.o appCommon.o ignoreLines.o -o rawProcess

rawProcess.o : appCommon.o ignoreLines.o rawProcess.h
	cc -c -Wall rawProcess.c -I ./ -o rawProcess.o

appCommon.o : appCommon.c appCommon.h
	cc -c -Wall appCommon.c -I ./ -o appCommon.o

ignoreLines.o : ignoreLines.c
	cc -c -Wall ignoreLines.c -o ignorelines.o

clean: 
	rm -f appCommon.o ignoreLines.o rawProcess.o rawProcess *~

rebuild: clean rawProcess
