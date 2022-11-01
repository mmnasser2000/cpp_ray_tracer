tracer: camera.o Image.o main.o objectabst.o objectsphere.o ray.o RayTracerApp.o scene.o lightabst.o pointlight.o geotrans.o objectplane.o objectcone.o
	g++ -o tracer main.o RayTracerApp.o Image.o scene.o camera.o ray.o objectabst.o objectsphere.o lightabst.o pointlight.o geotrans.o objectplane.o objectcone.o -lSDL2 -std=c++17 -w -Ofast

main.o: main.cpp
	g++ -c main.cpp -lSDL2 -std=c++17 -w -Ofast
RayTracerApp.o: RayTracerApp.cpp RayTracerApp.h
	g++ -c RayTracerApp.cpp -lSDL2 -std=c++17 -w -Ofast
Image.o: Image.cpp Image.hpp
	g++ -c Image.cpp -lSDL2 -std=c++17 -w -Ofast
scene.o: scene.cpp scene.h
	g++ -c scene.cpp -lSDL2 -std=c++17 -w -Ofast
camera.o: camera.cpp camera.hpp
	g++ -c camera.cpp -lSDL2 -std=c++17 -w -Ofast
ray.o: ray.cpp ray.h
	g++ -c ray.cpp -lSDL2 -std=c++17 -w -Ofast
objectabst.o: objectabst.cpp objectabst.hpp
	g++ -c objectabst.cpp -lSDL2 -std=c++17 -w -Ofast
objectsphere.o: objectsphere.cpp objectsphere.hpp
	g++ -c objectsphere.cpp -lSDL2 -std=c++17 -w -Ofast
lightabst.o: lightabst.cpp lightabst.hpp
	g++ -c lightabst.cpp -lSDL2 -std=c++17 -w -Ofast
pointlight.o: pointlight.cpp pointlight.hpp
	g++ -c pointlight.cpp -lSDL2 -std=c++17 -w -Ofast
geotrans.o: geotrans.cpp geotrans.hpp
	g++ -c geotrans.cpp -lSDL2 -std=c++17 -w -Ofast
objectplane.o: objectplane.cpp objectplane.hpp
	g++ -c objectplane.cpp -lSDL2 -std=c++17 -w -Ofast
objectcone.o: objectcone.cpp objectcone.hpp
	g++ -c objectcone.cpp -lSDL2 -std=c++17 -w -Ofast

clean:
	rm *.o tracer