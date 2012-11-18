##VARIABLES
inc = ../inc
src = ../src
obj = ../obj
tmp = ../templates
paths = -I$(inc) -I$(tmp)
flags = -Wall -g
cc = g++
cmd = $(cc) $(flags) $(paths) $@.cpp $(obj)/*.o -o ../$@.out


##CIBLES

test_node:
	$(cmd)

test_directed:
	$(cmd)

test_acm:
	$(cmd)

