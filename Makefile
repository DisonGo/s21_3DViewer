PROJECT_NAME		=	3D_Viewer

cc					=	gcc $(flags)
flags				=	-Werror -std=c11

all: clean build


build:
	$(cc) *.c -o $(PROJECT_NAME)

clean:
	rm -rf *.out