##VARIABLES
inc = ./inc
src = ./src
obj = ./obj
tst = ./tests
tmp = ./templates
cmd_src = cd $(src); make $@
cmd_exe = cd $(tst); make $@


##CIBLES

#Les classes

Node:
	$(cmd_src)

Edge:
	$(cmd_src)

DiGraph:
	$(cmd_src)

DirectableGraph:
	$(cmd_src)

PonderableGraph:
	$(cmd_src)

all_classes: Node Edge DiGraph DirectableGraph PonderableGraph

#les tests

test_node: Node
	$(cmd_exe)

test_graph: all_classes
	$(cmd_exe)

#Cleanings

cleantemp:
	rm -f *~ $(inc)/*~ $(src)/*~ $(tst)/*~ $(tmp)/*~

cleanobj:
	rm -f $(obj)/*.o

distclean:
	rm -f *.out

cleanall: cleantemp cleanobj distclean