PROJECT_NAME 		= 3D_Viewer
BUILD_PATH 			= ./build
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
# @cd ${BUILD_PATH}; make
all: install open
build:
	@cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" -Wno-dev -B ${BUILD_PATH} .
	@cmake --build ${BUILD_PATH} --target 3D_Viewer --parallel 8
run: build
	cd ${BUILD_PATH}${EXE_DIR}/${PROJECT_EXE_PATH} && ./${PROJECT_NAME}
build_debug:
	@cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Debug" -B ${BUILD_PATH} .
install: build

run_t:
	@cmake --build ./build  --target TESTING -j 8 -- -s
	@./${BUILD_PATH}/exe/TESTING
uninstall:
	rm -rf ${BUILD_PATH}
open:
	./${EXE_PATH}
dist: install
	@tar cvzf ${PROJECT_NAME}.tgz build

dvi:
	@$(OPEN_CMD) dvi/index.md

clean:
	@cmake --build ${BUILD_PATH} --target clean
test:
	@cmake --build ${BUILD_PATH} --target TESTING --parallel 8
	@./${BUILD_PATH}/exe/TESTING
gcov_report:
	@cd transforms; make $@
	@cd obj_parser; make $@
	@genhtml -q --dark-mode -o report transforms/report.info obj_parser/report.info

	@$(OPEN_CMD) report/index.html
clang:
	clang-format --style=Google -n $(shell find . -name '*.cc') $(shell find . -name '*.h')
clang-replace:
	clang-format --style=Google -i $(shell find . -name '*.cc') $(shell find . -name '*.h')
.PHONY: all build run install uninstall open dist dvi clean clang clang-replace gcov_report
