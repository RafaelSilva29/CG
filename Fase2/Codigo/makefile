C++FLAGS_MAC = tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinystr.cpp -framework OpenGL -framework GLUT

C++FLAGS_LINUX = tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinystr.cpp -IGL -Iglut -IGLU

mac: generator.c renderscene.cpp
		make clear
		make generator
		make renderscene_mac

linux: generator.c renderscene.cpp
		make clear
		make generator
		make renderscene_linux

generator: generator.c
	$(CC) generator.c -o generator -lm

renderscene_mac: renderScene.cpp
	$(CXX) $(C++FLAGS_MAC) renderScene.cpp -o renderscene

renderscene_linux: renderScene.cpp
	$(CXX) renderScene.cpp -o renderscene $(C++FLAGS_LINUX)

cleanfigures:
	rm -f 3D/*.3d
	rm -f XML/*.xml
	
clear: 
	rm -f generator
	rm -f renderscene

	



