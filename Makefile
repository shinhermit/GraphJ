##VARIABLES
inc = ./inc
src = ./src
obj = ./obj
tst = ./tests
tmp = ./templates
algo = ./algorithmes
cmd_src = cd $(src); make $@
cmd_exe = cd $(tst); make $@


##CIBLES

#Les classes

Node:
	$(cmd_src)

WeightedNeighbour:
	$(cmd_src)

Edge:
	$(cmd_src)

WeightedEdge:
	$(cmd_src)

DiGraph:
	$(cmd_src)

DirectableGraph:
	$(cmd_src)

PonderableGraph:
	$(cmd_src)

all_classes: Node Edge DiGraph DirectableGraph PonderableGraph

#Autres classes (utilitaires)

Color:
	$(cmd_src)

#les tests

test_node: Node
	$(cmd_exe)

test_directed: all_classes
	$(cmd_exe)

#Cleanings

cleantemp:
	rm -f *~ $(inc)/*~ $(src)/*~ $(tst)/*~ $(tmp)/*~ $(algo)/*~

cleanobj:
	rm -f $(obj)/*.o

distclean:
	rm -f *.out

cleanall: cleantemp cleanobj distclean