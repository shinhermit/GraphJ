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

GraphTypes:
	$(cmd_src)

Node:
	$(cmd_src)

WeightedNode:
	$(cmd_src)

Edge:
	$(cmd_src)

WeightedEdge:
	$(cmd_src)

BasicGraphException:
	$(cmd_src)

InvalidNodeID:
	$(cmd_src)

InvalidEdge:
	$(cmd_src)

InvalidOperation:
	$(cmd_src)

TopologyIterator:
	$(cmd_src)

DoubleNodeSetIterator:
	$(cmd_src)

BaseGraph:
	$(cmd_src)

DirectableGraph:
	$(cmd_src)

PonderableGraph:
	$(cmd_src)

NamedColor:
	$(cmd_src)

Visitor:
	$(cmd_src)

ColorizingVisitor:
	$(cmd_src)

TricolorBuilderVisitor:
	$(cmd_src)

all_classes: GraphTypes Node WeightedNode Edge WeightedEdge BasicGraphException InvalidNodeID InvalidEdge InvalidOperation TopologyIterator DoubleNodeSetIterator BaseGraph DirectableGraph PonderableGraph NamedColor ColorizingVisitor Visitor TricolorBuilderVisitor


#les validations

validation_dependencies:  BaseGraph DirectableGraph PonderableGraph Edge GraphTypes BasicGraphException InvalidNodeID  InvalidEdge InvalidOperation TopologyIterator DoubleNodeSetIterator

BaseGraph_validation: validation_dependencies
	$(cmd_exe)

DirectableGraph_validation: validation_dependencies
	$(cmd_exe)

PonderableGraph_validation: validation_dependencies
	$(cmd_exe)

Graph_validation: validation_dependencies
	$(cmd_exe)

#les tests

test_node: Node
	$(cmd_exe)

test_directed: all_classes
	$(cmd_exe)

test_acm_directed: all_classes
	$(cmd_exe)

test_acm: all_classes
	$(cmd_exe)

test_coloring: all_classes
	$(cmd_exe)

test_dijkstra: all_classes
	$(cmd_exe)

test_dijkstra_maximize: all_classes
	$(cmd_exe)

test_dijkstra_negative: all_classes
	$(cmd_exe)

test_bellman: all_classes
	$(cmd_exe)

test_Xdijkstra: all_classes
	$(cmd_exe)

test_Xbellman: all_classes
	$(cmd_exe)

test_weights_transformations: all_classes
	$(cmd_exe)

reseau_routier: all_classes
	$(cmd_exe)

feux_tricolores: all_classes
	$(cmd_exe)

gps: all_classes
	$(cmd_exe)

gps_multichemin: all_classes
	$(cmd_exe)

#Cleanings

cleantemp:
	rm -f *~ $(inc)/*~ $(src)/*~ $(tst)/*~ $(tmp)/*~ $(algo)/*~

cleanressources:
	rm -f *.jpg *.png *.dot *.graph

cleanobj:
	rm -f $(obj)/*.o

distclean:
	rm -f *.out

cleanall: cleantemp cleanobj distclean cleanressources