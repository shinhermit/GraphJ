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

test_acm_directed:
	$(cmd)

test_acm:
	$(cmd)

test_coloring:
	$(cmd)

test_dijkstra:
	$(cmd)

test_dijkstra_maximize:
	$(cmd)

test_dijkstra_negative:
	$(cmd)

test_bellman:
	$(cmd)

test_Xdijkstra:
	$(cmd)

test_Xbellman:
	$(cmd)

test_weights_transformations:
	$(cmd)

reseau_routier:
	$(cmd)

feux_tricolores:
	$(cmd)

gps:
	$(cmd)

gps_multichemin:
	$(cmd)
