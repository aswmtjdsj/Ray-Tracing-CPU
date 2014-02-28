
CC=c++

CFLAGS=-g -Wall -O2

LIB=./SDL2.framework/

INC=./SDL2.framework/Versions/A/Headers

lib=SDL2

EXEC=main

# all objects designed to build
BASIC_GEOMETRY=Point.o Vector.o

BASIC=RGBColor.o $(BASIC_GEOMETRY)

GEOMETRY_OBJECTS=GeometryObject.o Plane.o Sphere.o 

MATRIAL=Material.o Matte.o Phong.o 

RAY_CASTING=Tracer.o RayCasting.o

BRDF_MODEL=Lambertian.o GlossySpecular.o

RENDER_STRUCTURE=ViewPlane.o Ray.o World.o ShadeRec.o $(RAY_CASTING)

LIGHT=Light.o

GUI=Drawing.o

WORKING=BuildFunctions.o Testing.o

OBJ=$(BASIC) $(GEOMETRY_OBJECTS) $(LIGHT) $(BRDF_MODEL) $(MATRIAL) $(RENDER_STRUCTURE) $(GUI) $(WORKING)

$(EXEC):$(OBJ) ../main.cpp 
	$(CC) $(CFLAGS) $^ -I$(INC) $(LIB)$(lib) -o $@ 

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

ViewPlane.o: ../ViewPlane.cpp
	$(CC) -c $^

# BRDF
Lambertian.o: ../Lambertian.cpp
	$(CC) -c $^

GlossySpecular.o: ../GlossySpecular.cpp
	$(CC) -c $^

# Light
Light.o: ../Light.cpp
	$(CC) -c $^ -I$(INC)

# Material
Material.o: ../Material.cpp
	$(CC) -c $^

Matte.o: ../Matte.cpp
	$(CC) -c $^ -I$(INC)

Phong.o: ../Phong.cpp
	$(CC) -c $^ -I$(INC)

# GUI
Drawing.o: ../Drawing.cpp
	$(CC) -c $^ -I$(INC)

# Real Working Stuffs 
Testing.o: ../Testing.cpp
	$(CC) -c $^ -I$(INC)

BuildFunctions.o: ../BuildFunctions.cpp
	$(CC) -c $^ -I$(INC)

clean:
	rm -f $(EXEC) $(OBJ)
