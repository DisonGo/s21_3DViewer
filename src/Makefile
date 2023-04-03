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
all: install open
build:
	@if [ ! -d ${BUILD_PATH} ]; then mkdir ${BUILD_PATH}; fi
	@cmake -B ${BUILD_PATH} .
	@cd ${BUILD_PATH}; make
run: build
	./${EXE_PATH}

install: build

uninstall:
	rm -rf ${BUILD_PATH}
open:
	./${EXE_PATH}
dist: install
	@tar cvzf ${PROJECT_NAME}.tgz build

dvi:
	@$(OPEN_CMD) dvi/index.md

clean:
	@cd transforms; make $@
	@cd obj_parser; make $@
	@rm -rf report
test:
	@cd transforms; make
	@cd obj_parser; make
	
	@clear
	@cd transforms; make $@
	@cd obj_parser; make $@
gcov_report:
	@cd transforms; make $@
	@cd obj_parser; make $@
	@genhtml -q --dark-mode -o report transforms/report.info obj_parser/report.info

	@$(OPEN_CMD) report/index.html
clang:
	clang-format --style=Google -n $(shell find ./transforms ./obj_parser -name '*.c') $(shell find ./transforms ./obj_parser -name '*.h')
clang-replace:
	clang-format --style=Google -i $(shell find ./transforms ./obj_parser -name '*.c') $(shell find ./transforms ./obj_parser -name '*.h')
.PHONY: all build run install uninstall open dist dvi clean clang clang-replace gcov_report