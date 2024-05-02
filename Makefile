##
## EPITECH PROJECT, 2024
## Hashmap in C
## File description:
## Makefile
##

LIB_NAME		:=	hashmap
LIB_PATH		:=	/usr/local/lib
INCLUDE_PATH	:=	/usr/local/include/$(LIB_NAME)

CC				:=	gcc
CPPFLAGS		:=	-Iinclude/
CFLAGS 			:=	-Wall -Wextra -Werror -pedantic -ansi -fPIC 		 \
					-fno-delete-null-pointer-checks -fno-strict-overflow \
					-fno-strict-aliasing -ftrivial-auto-var-init=zero    \
					-Wformat -Wimplicit-fallthrough 					 \
					-U_FORTIFY_SOURCE -D_GLIBCXX_ASSERTIONS 			 \
					-fstack-protector-strong

ifeq ($(PLATFORM),x86_64)
	CFLAGS		+=	-fcf-protection=full -Wl,-z,nodlopen -Wl,-z,noexecstack \
					-Wl,-z,relro -Wl,-z,now -fstack-clash-protection 		\
					-fstrict-flex-arrays=3 -Wtrampolines
endif

ifeq ($(PLATFORM),aarch64)
	CFLAGS		+=	-mbranch-protection=standard
endif

SRCS			:=	$(shell find src -name '*.c')
OBJS			:=	$(SRCS:.c=.o)

TESTS_CFLAGS	:=	-g -Wall -Wextra -Werror
TESTS_SRCS		:=	$(shell find tests -type f -name 'tests_*.c')
TESTS_OBJS		:=	$(TESTS_SRCS:.c=.o)

VALGRIND_FLAGS	:=	-s							\
					--leak-check=full			\
					--track-origins=yes			\
					--read-var-info=yes			\
					--trace-children=yes		\
					--show-leak-kinds=all		\
					--read-inline-info=yes		\
					--errors-for-leak-kinds=all

RM				:=	rm -rf

all:	$(OBJS)
	$(MAKE) lib$(LIB_NAME).a
	$(MAKE) lib$(LIB_NAME).so
	$(MAKE) lib$(LIB_NAME).dylib

lib$(LIB_NAME).so:	$(OBJS)
	@$(CC) -shared $(CFLAGS) $(OBJS) -o $@

lib$(LIB_NAME).dylib:	$(OBJS)
	@$(CC) -shared $(CFLAGS) $(OBJS) -o $@

lib$(LIB_NAME).a:	$(OBJS)
	@ar -rcs $@ $(OBJS)

tests/%.o:	CFLAGS = -Wall -Wextra -Werror
tests/%.o:	tests/%.c
	@$(CC) $(TESTS_CFLAGS) $(CPPFLAGS) -o $@ -c $<

tests_run:	CFLAGS += -g --coverage
tests_run:	fclean	$(OBJS)	$(TESTS_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(TESTS_OBJS) -o unit_tests -lcriterion
	@CRITERION_NO_EARLY_EXIT=1 ./unit_tests
	@gcovr -e tests .

install:	all
	@mkdir -p $(INCLUDE_PATH)
	@mv lib$(LIB_NAME).a $(LIB_PATH)
	@mv lib$(LIB_NAME).so $(LIB_PATH)
	@mv lib$(LIB_NAME).dylib $(LIB_PATH)
	@cp include/$(LIB_NAME).h $(INCLUDE_PATH)
	@echo "Lib installed. Use 'ldconfig' or 'update_dyld_shared_cache' to \
	refresh ld cache"

uninstall:
	@$(RM) $(LIB_PATH)/lib$(LIB_NAME).a
	@$(RM) $(LIB_PATH)/lib$(LIB_NAME).so
	@$(RM) $(LIB_PATH)/lib$(LIB_NAME).dylib
	@$(RM) $(INCLUDE_PATH)/$(LIB_NAME).h
	@echo "Lib uninstalled. Use 'ldconfig' or 'update_dyld_shared_cache' to \
	refresh ld cache"

valgrind:	tests_run
	valgrind $(VALGRIND_FLAGS) ./unit_tests

clean:
	@$(RM) $(OBJS)
	@$(RM) $(TESTS_OBJS)
	@$(RM) $(shell find . -type f -name '*.gcno')
	@$(RM) $(shell find . -type f -name '*.gcda')

fclean:	clean
	@$(RM) lib$(LIB_NAME).so lib$(LIB_NAME).a lib$(LIB_NAME).dylib
	@$(RM) unit_tests

re:	fclean	all
