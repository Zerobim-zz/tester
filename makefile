T_FO=bin
H_FO=include
S_FO=lib
EXE=$(T_FO)/main
TESTS_FO=testing_the_tester
S_TESTS=$(wildcard $(TESTS_FO)/*.cpp)
OB_TESTS=$(subst $(TESTS_FO),$(T_FO),$(S_TESTS:.cpp=.o))

H_FIS=$(wildcard $(H_FO)/*.h)
OBJS=$(subst $(H_FO),$(T_FO),$(H_FIS:.h=.o))

LIB_NAME=libtester.so
LINK=g++
CC=g++

C_IN=-I $(H_FO)
C_FLAGS=-g -c -fPIC
C_OUT=-o $@
L_OUT=-o $@

all:$(EXE)

$(EXE): $(OBJS) $(OB_TESTS)
	@$(LINK) $(L_OUT) $^
	
	
$(OB_TESTS):$(T_FO)/%.o: $(TESTS_FO)/%.cpp
		@$(CC) $(C_FLAGS) $(C_IN) $(C_OUT) $^

$(OBJS):$(T_FO)/%.o:$(H_FO)/%.h $(S_FO)/%.cpp | $(T_FO)
	$(CC) $(C_FLAGS) $(C_IN) $(C_OUT) $(filter %.cpp,$^)
	
$(T_FO):
	[ -d $@ ] || mkdir $@

$(LIB_NAME):$(OBJS)
	$(LINK) -shared -o $(LIB_NAME) $(OBJS)

install:$(LIB_NAME) $(H_FIS)
	@ls /root 2>/dev/null &&\
	cp -i-t /usr/local/include $(H_FIS) &&\
	cp -i $(LIB_NAME) /usr/local/lib || \
	echo "Error: Root privileges needed"
	
clean:
	@rm -f $(T_FO)/*.o $(T_FO)/main;\
	find . -maxdepth 1 -mindepth 1 -name $(T_FO) -type d -empty -delete;\
	rm -f $(LIB_NAME)