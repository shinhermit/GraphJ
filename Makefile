cmake:
	cd build; cmake .. -G"Unix Makefiles"

%.o:
	g++ -Wall -Wextra -Iinc -Itemplates -g -c src/$(@:.o=.cpp)

%:
	cd build; make $@

cleantemp:
	rm -f *~ headers/*~ src/*~ tests/*~ templates/*~ algorithmes/*~ build/*~ res/*~

cleanres:
	cd res; rm -f *

distclean:
	rm -f bin/*

buildclean:
	rm -rf build/*

clean: cleantemp distclean
	cd build; make clean
