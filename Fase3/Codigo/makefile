C++FLAGS_MAC = tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinystr.cpp /usr/local/lib/libGLEW.dylib -framework OpenGL -framework GLUT

C++FLAGS_LINUX = tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinystr.cpp -IGL -Iglut -IGLU -IGLEW

mac: generator.cpp renderscene.cpp
		make clear
		make generator
		make renderscene_mac

linux: generator.cpp renderscene.cpp
		make clear
		make generator
		make renderscene_linux

generator: generator.cpp
	$(CXX) generator.cpp -o generator

renderscene_mac: renderScene.cpp
	$(CXX) $(C++FLAGS_MAC) renderScene.cpp -o renderScene

renderscene_linux: renderScene.cpp
	$(CXX) renderScene.cpp -o renderscene $(C++FLAGS_LINUX)

cleanfigures:
	rm -f 3D/*.3d
	rm -f XML/*.xml
	
clear: 
	rm -f generator
	rm -f renderscene
