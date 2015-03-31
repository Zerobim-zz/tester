T_FO=bin
H_FO=include
S_FO=lib

COMP=g++ -g -c
LINK=g++
C_OP=-o $(T_FO)/$@.o -I $(H_FO)
L_OP=-o $@
C_PA=$<
L_PA=$<

DEF_DEP=$(H_FO)/$@.h $(S_FO)/$@.cpp

all:exec

exec:$(T_FO)/*.o
	$(LINK) $(L_OP) $(L_PA)

test:$(DE_DEP)
	$(COMP)$(C_OP)
	
temp:

clean: