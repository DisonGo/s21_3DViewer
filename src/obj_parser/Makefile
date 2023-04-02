SHELL := /bin/bash

PROJECT_NAME	=obj_parser
TEST_NAME		= Test
O_DIR 			= obj
TEST_DIR		= tests

LIB_SRC_DIR		= src
LIB_INC_DIR		= includes
LIB_O_DIR		= $(O_DIR)/$(LIB_SRC_DIR)

TEST_SRC_DIR	= $(TEST_DIR)
TEST_INC_DIR	= $(LIB_INC_DIR)
TEST_O_DIR		= $(O_DIR)/$(TEST_SRC_DIR)

BUILD_DIR		= ../obj_parser
UNAME_S 		:= $(shell uname -s)
TEST_SRC		= $(TEST_DIR)/${PROJECT_NAME}_test.c
Flags 			= -std=c11 -Werror -Wall -Wextra $(Debug)
gcc 			= gcc $(Flags)
LIB_SOURCES		= $(shell find $(LIB_SRC_DIR) -name '*.c')
TEST_SOURCES	= $(shell find $(TEST_SRC_DIR) -name '*.c')
REPORT_FILES	= $(shell find . -name '*.gcno') $(shell find . -name '*.gcda')

LIB_OBJ 		= $(patsubst %.c,$(O_DIR)/%.o, $(LIB_SOURCES))
TEST_OBJ 		= $(patsubst %.c,$(O_DIR)/%.o, $(TEST_SOURCES))

OBJ				= $(LIB_SOURCES)
OBJ				+=$(TEST_OBJ)
DEBUG_SOURCE	= $(TEST_SRC)

ifeq ($(UNAME_S),Linux)
	TEST_CHECK_F= -lcheck
	OPEN_CMD = xdg-open
	ADD_LIB = -lm -lrt -lpthread
endif

ifeq ($(UNAME_S),Darwin)
	TEST_CHECK_F= $(shell pkg-config --cflags --libs check)
	OPEN_CMD = open
	ADD_LIB =
endif
# Source files build
$(LIB_O_DIR)/%.o: $(LIB_SRC_DIR)/%.c
	@$(gcc) -I${LIB_INC_DIR} $< -c -o $@

$(TEST_O_DIR)/%.o: $(TEST_SRC_DIR)/%.c 
	@$(gcc) -I${LIB_INC_DIR} -I${TEST_INC_DIR} $< -c -o $@
#

# Static libs build
$(BUILD_DIR)/$(PROJECT_NAME).a: $(LIB_OBJ)
	@ar rcs $@ $(LIB_O_DIR)/*.o
$(PROJECT_NAME).a: $(BUILD_DIR)/$(PROJECT_NAME).a

$(BUILD_DIR)/$(TEST_NAME).a: $(TEST_OBJ)
	@ar rcs $@ $(TEST_OBJ)
$(TEST_NAME).a: $(BUILD_DIR)/$(TEST_NAME).a
#
all: clear $(PROJECT_NAME).a
clear:
	clear
clean:
	@rm -rf *.out $(shell find ./obj -name '*.o')
	@rm -rf $(shell find ./obj -name '*.gc*')
	@rm -rf ./gcov/*.o ./gcov/*.gc*
	@rm -rf ./*.gc*
	@rm -rf *.a
	@rm -rf report*
	@rm -rf $(PROJECT_NAME)
test: set_test $(PROJECT_NAME)
	@./$(PROJECT_NAME)
set_test:
	$(eval DEBUG_SOURCE = $(TEST_SRC))
	@echo ${PROJECT_NAME}:Test build

set_report_gcc:
	$(eval gcc += -fprofile-arcs -ftest-coverage -fPIC)
	@echo ${PROJECT_NAME}:Check build

move_gc_files:
	@mv $(shell find $(O_DIR)/${LIB_SRC_DIR} -name '*.gc*') ./gcov

gcov_report: clean set_report_gcc test
	@gcov *.c ${LIB_SRC_DIR}/*.c -o $(ODIR)/${LIB_SRC_DIR}
	@make move_gc_files
	@lcov -t ./gcov -o report.info -c -q -d ./gcov

$(PROJECT_NAME): $(PROJECT_NAME).a $(TEST_NAME).a
	@$(gcc) $(DEBUG_SOURCE) -I${LIB_INC_DIR} -I${TEST_INC_DIR} -o $@ ${TEST_CHECK_F} $(PROJECT_NAME).a $(TEST_NAME).a
