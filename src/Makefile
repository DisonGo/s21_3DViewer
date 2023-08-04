PROJECT_NAME 		= 3D_Viewer
BUILD_PATH 			= ../build
EXE_DIR 			= /exe
PROJECT_EXE_PATH 	= ${PROJECT_NAME}.app/Contents/MacOS
EXE_PATH 			= ${BUILD_PATH}${EXE_DIR}/${PROJECT_EXE_PATH}/${PROJECT_NAME}
UNAME_S				:= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	OPEN_CMD = xdg-open
endif

ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
endif
all: install tests open
build:
	@cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" -Wno-dev -B ${BUILD_PATH} .
build_3D_Viewer:
	@cmake --build ${BUILD_PATH} --target 3D_Viewer --parallel 8
build_debug:
	@cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Debug" -Wno-dev -B ${BUILD_PATH} .


install: build build_3D_Viewer

uninstall:
	rm -rf ${BUILD_PATH}

clean:
	@cmake --build ${BUILD_PATH} --target clean
tests: build
	@cmake --build ${BUILD_PATH} --target TESTING --parallel 8
	@./${BUILD_PATH}/exe/TESTING
run: build
	cd ${BUILD_PATH}${EXE_DIR}/${PROJECT_EXE_PATH} && ./${PROJECT_NAME}

open:
	@./${EXE_PATH}
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
