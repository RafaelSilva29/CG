C++FLAGS = tinyxml/tinyxml.cpp tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinystr.cpp -framework OpenGL -framework GLUT

all: generator.c renderScene.cpp
	make clear
	make generator
	make renderscene

generator: generator.c
	$(CC) generator.c -o generator 

renderscene: renderScene.cpp
	$(CXX) $(C++FLAGS) renderScene.cpp -o renderscene

cleanfigures:
	rm -f 3D/*.3d
	rm -f XML/*.xml
	
clear: 
	rm -f generator
	rm -f renderscene

	



