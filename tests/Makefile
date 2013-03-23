##VARIABLES
inc = ../inc
src = ../src
obj = ../obj
tmp = ../templates
paths = -I$(inc) -I$(tmp)
flags = -Wall -g
cc = g++
sys = -D_SYSTEM
cmd = $(cc) $(flags) $(paths) $@.cpp $(obj)/*.o -o ../$@.out
cmd_sys = $(cmd) $(sys)

########### CIBLES ###########

#### Validations

BaseGraph_validation:
	$(cmd)

DirectableGraph_validation:
	$(cmd)

PonderableGraph_validation:
	$(cmd)

Graph_validation:
	$(cmd)

CanonicalNetwork_validation:
	$(cmd)



#### Tests

test_node:
	$(cmd_sys)

test_directed:
	$(cmd_sys)

test_acm_directed:
	$(cmd_sys)

test_acm:
	$(cmd_sys)

test_coloring:
	$(cmd_sys)

test_dijkstra:
	$(cmd_sys)

test_dijkstra_maximize:
	$(cmd_sys)

test_bellman:
	$(cmd_sys)

test_Xdijkstra:
	$(cmd_sys)

test_Xbellman:
	$(cmd_sys)

test_weights_transformations:
	$(cmd_sys)

test_preceedence_table:
	$(cmd)

test_network_builder:
	$(cmd)

reseau_routier:
	$(cmd_sys)

feux_tricolores:
	$(cmd_sys)

gps:
	$(cmd_sys)

gps_multichemin:
	$(cmd_sys)

plannification:
	$(cmd_sys)

plannification_interfaced:
	$(cmd_sys)
