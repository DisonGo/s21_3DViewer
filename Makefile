PROJECT_NAME		=	3D_Viewer

cc					=	gcc $(flags)
flags				=	-Werror -std=c11

all: clean build


build:
	$(cc) sources/parser/sources/*.c -o $(PROJECT_NAME)

clean:
	rm -rf *.out
	rm -rf $(PROJECT_NAME)