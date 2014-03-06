CPP=g++

CFLAGS=-g -Wall -std=c++0x

CC=$(CPP) $(CFLAGS)

LFLAGS=-O2

INC=/usr/local/include/SDL2/

LIB=-lSDL2

EXEC=main

# all objects designed to build
BASIC_GEOMETRY=Point.o Vector.o

BASIC=RGBColor.o $(BASIC_GEOMETRY)

GEOMETRY_OBJECTS=GeometryObject.o Plane.o Sphere.o Polygon.o

MATERIAL=Material.o Matte.o Phong.o 

RAY_CASTING=Tracer.o RayCasting.o MultipleObjects.o

BRDF_MODEL=Lambertian.o GlossySpecular.o

LIGHT=Light.o AmbientOccluder.o

SAMPLER=Sampler.o 

CAMERA=Camera.o PinHole.o

RENDER_STRUCTURE=ViewPlane.o Ray.o World.o ShadeRec.o $(RAY_CASTING)

GUI=Drawing.o

WORKING=BuildFunctions.o Testing.o

COMMON=common_linux.o

OBJ=$(BASIC) $(GEOMETRY_OBJECTS) $(LIGHT) $(BRDF_MODEL) $(SAMPLER) $(CAMERA) $(MATERIAL) $(RENDER_STRUCTURE) $(GUI) $(WORKING) $(COMMON)

$(EXEC):$(OBJ) ../main.cpp 
	$(CC) $(LFLAGS) -I$(INC) $^ $(LIB) -o $@ 

# Geometry
Point.o: ../Point.cpp 
	$(CC) -c $^

Vector.o: ../Vector.cpp
	$(CC) -c $^

# RGBColor
RGBColor.o: ../RGBColor.cpp
	$(CC) -c $^

# GeometryObject
GeometryObject.o: ../GeometryObject.cpp
	$(CC) -c $^

Sphere.o: ../Sphere.cpp
	$(CC) -c $^

Plane.o: ../Plane.cpp
	$(CC) -c $^

Polygon.o: ../Polygon.cpp
	$(CC) -c $^

# Render Structure 
Ray.o: ../Ray.cpp
	$(CC) -c $^

World.o: ../World.cpp ../BuildFunctions.cpp
	$(CC) -c $^ -I$(INC)

ShadeRec.o: ../ShadeRec.cpp
	$(CC) -c $^

# Ray Casting
Tracer.o: ../Tracer.cpp
	$(CC) -c $^ -I$(INC)

RayCasting.o: ../RayCasting.cpp
	$(CC) -c $^ -I$(INC)

MultipleObjects.o: ../MultipleObjects.cpp
	$(CC) -c $^ -I$(INC)

# Vie Plane
ViewPlane.o: ../ViewPlane.cpp
	$(CC) -c $^

# BRDF
Lambertian.o: ../Lambertian.cpp
	$(CC) -c $^

GlossySpecular.o: ../GlossySpecular.cpp
	$(CC) -c $^

# Material
Material.o: ../Material.cpp
	$(CC) -c $^

Matte.o: ../Matte.cpp
	$(CC) -c $^ -I$(INC)

Phong.o: ../Phong.cpp
	$(CC) -c $^ -I$(INC)

# Light
Light.o: ../Light.cpp
	$(CC) -c $^ -I$(INC)

AmbientOccluder.o: ../AmbientOccluder.cpp
	$(CC) -c $^ -I$(INC)

Sampler.o: ../Sampler.cpp
	$(CC) -c $^ -I$(INC)

# Camera
Camera.o:../Camera.cpp
	$(CC) -c $^ -I$(INC)

PinHole.o:../PinHole.cpp
	$(CC) -c $^ -I$(INC)

# GUI
Drawing.o: ../Drawing.cpp
	$(CC) -c $^ -I$(INC)

# Real Working Stuffs 
Testing.o: ../Testing.cpp
	$(CC) -c $^ -I$(INC)

BuildFunctions.o: ../BuildFunctions.cpp
	$(CC) -c $^ -I$(INC)

# common functions
common_linux.o: common_linux.cpp
	$(CC) -c $^ -I$(INC)

clean:
	-rm -f $(EXEC) $(OBJ)
