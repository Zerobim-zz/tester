T_FO=bin
H_FO=include
S_FO=lib
LIB=libtester.so

EXE=$(T_FO)/main
TESTS_FO=testing_the_tester
S_TESTS=$(wildcard $(TESTS_FO)/*.cpp)
OB_TESTS=$(subst $(TESTS_FO),$(T_FO),$(S_TESTS:.cpp=.o))

H_FIS=$(wildcard $(H_FO)/*.h)
S_FIS=$(subst $(H_FO),$(S_FO),$(H_FIS:.h=.cpp))
OBJS=$(subst $(H_FO),$(T_FO),$(H_FIS:.h=.o))


LINK=gcc
CC=g++

C_IN=-I $(H_FO)
C_OUT=-o $@
L_OUT=-o $@

install: C_FLAGS = -g -c -fpic
install: clean $(OBJS)
	@ls /root 2>/dev/null &&\
	sudo chmod 0777 -R bin &&\
	sudo $(LINK) -shared -o $(LIB) $(OBJS) &&\
	sudo cp -i -t /usr/local/include/ $(H_FIS)  &&\
	sudo cp -i $(LIB) /usr/local/lib/ ||\
	echo "Root privileges needed, try with sudo"

all:C_FLAGS = -g -c
all:$(EXE)

$(EXE): $(OBJS) $(OB_TESTS)
	@$(LINK) $(L_OUT) $^
	
$(OB_TESTS):$(T_FO)/%.o: $(TESTS_FO)/%.cpp | $(T_FO)
	$(CC) $(C_FLAGS) $(C_IN) $(C_OUT) $^

$(OBJS):$(T_FO)/%.o:$(H_FO)/%.h $(S_FO)/%.cpp | $(T_FO)
	$(CC) $(C_FLAGS) $(C_IN) $(C_OUT) $(filter %.cpp,$^)
	
$(T_FO):
	@[ -d $@ ] || mkdir $@

clean:
	@rm -f $(T_FO)/*.o $(T_FO)/main;\
	find . -maxdepth 1 -mindepth 1 -name $(T_FO) -type d -empty -delete;\
	rm -f $(LIB)