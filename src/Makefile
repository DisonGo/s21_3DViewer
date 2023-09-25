PROJECT_NAME 		= 3D_Viewer
BUILD_PATH 			= ../build
EXE_DIR 			= /exe
PROJECT_EXE_PATH 	= ${PROJECT_NAME}
EXE_PATH 			= ${BUILD_PATH}${EXE_DIR}/${PROJECT_EXE_PATH}
EXE_PATH_DEBUG 			= ${BUILD_PATH}_debug${EXE_DIR}/${PROJECT_EXE_PATH}
UNAME_S				:= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	OPEN_CMD = xdg-open
else ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
else
	OPEN_CMD = 
endif
all: install tests open
build:
	@cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" -Wno-dev -B ${BUILD_PATH} .
build_d:
	@cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Debug" -Wno-dev -B ${BUILD_PATH}_debug .
build_3D_Viewer:
	@cmake --build ${BUILD_PATH} --target 3D_Viewer --parallel 8
build_3D_Viewer_debug:
	@cmake --build ${BUILD_PATH}_debug --target 3D_Viewer --parallel 8
open:
	@$(OPEN_CMD) ${EXE_PATH}
open_d:
	@$(OPEN_CMD) ${EXE_PATH_DEBUG}
open_t:
	@$(OPEN_CMD) ${BUILD_PATH}/exe/TESTING

install: build build_3D_Viewer

uninstall:
	rm -rf ${BUILD_PATH}

clean:
	@cmake --build ${BUILD_PATH} --target clean
b_t:
	@cmake --build ${BUILD_PATH}_debug --target TESTING --parallel 8
tests: build_d b_t open_t
run: build
	cd ${BUILD_PATH}${EXE_DIR}/${PROJECT_EXE_PATH} && @$(OPEN_CMD) ${PROJECT_NAME}
b: build_3D_Viewer
b_d: build_3D_Viewer_debug



dist: install
	@cd ${BUILD_PATH}${EXE_DIR}/ && tar czf ../../src/${PROJECT_NAME}.tgz ./*
leaks: build_debug build_3D_Viewer
	leaks -atExit -- ./${EXE_PATH}
dvi:
	@$(OPEN_CMD) dvi/index.md

clang:
	clang-format --style=Google -n $(shell find . -name '*.cc') $(shell find . -name '*.h')
clang-replace:
	clang-format --style=Google -i $(shell find . -name '*.cc') $(shell find . -name '*.h')
.PHONY: all build run install uninstall open dist dvi clean clang clang-replace gcov_report
