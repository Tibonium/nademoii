#*******************************************************************
#
#        Makefile for the GENeCIS test routines
#
#*******************************************************************

CC = g++ -g -O0 -Wall -std=c++98
IDIR = /usr/local/include
CFLAGS = -I $(IDIR)
TESTS = matrix_test distribution_test tree_test difq_test server_test \
	socket_test graph_test prime sort_test vector_test mathfunc_test \
	container_test graph_array_test pattern_test#	gravity_test
MISC_TESTS = hash_test reference_test boost_test buffer_test template_test
MATRIX = math/matrix.h math/matrix_expression.h math/matrix_operations.h \
	math/matrix_io.h
VECTOR = math/math_vector.h math/bvector.h math/svector.h math/cvector.h \
	math/vector_expression.h
CONTAINER = container/array.h container/dynamic_array.h \
	container/container_io.h container/container_expression.h \
	container/container_functions.h
MATH_HDR = ${wildcard math/*.h}
DIST_HDR = ${wildcard distribution/*.h}
TREE_HDR = ${wildcard tree/*.h}
PHYS_HDR = ${wildcard physics/*.h}
SRVR_FILES = ${wildcard net/*.cc}

MATH_OBJ = ${wildcard math/*.o}
AI_OBJ = ${wildcard ai/*.o}
PHYS_OBJ = ${wildcard physics/*.o}
SRVR_OBJ = $(wildcard net/*.o)

all: regression_test misc_test
	@date

clean:
	@echo "The following tests have been removed: "
	@for test in $(TESTS) ; do \
		if [ -a $$test ] ; \
		then \
			rm $$test ; \
		fi ; \
		echo "  " $$test ; \
	done
	@for test in $(MISC_TESTS) ; do \
		if [ -a $$test ] ; \
		then \
			rm $$test ; \
		fi ; \
		echo "  " $$test ; \
	done

# Various miscellaneous test
misc_test: $(MISC_TESTS)
	@echo "Miscellaneous Tests built"

reference_test: misc_test/reference_test.cc
	@echo "Building reference_test..."
	@$(CC) -o reference_test misc_test/reference_test.cc $(CFLAGS)
	
boost_test: misc_test/boost_test.cc
	@echo "Building boost_test..."
	@$(CC) -o boost_test misc_test/boost_test.cc $(CFLAGS)
	
hash_test: misc_test/hash_test.cc
	@echo "Building hash_test..."
	@$(CC) -o hash_test misc_test/hash_test.cc $(CFLAGS)

buffer_test: misc_test/buffer_test.cc
	@echo "Building buffer_test..."
	@$(CC) -o buffer_test misc_test/buffer_test.cc $(CFLAGS)

template_test: misc_test/template_test.cc
	@echo "Building template_test..."
	@$(CC) -o template_test misc_test/template_test.cc $(CFLAGS)

# Regression Tests
regression_test: $(TESTS)
	@echo "Regression Tests built"

math/ode.o: math/ode.cc math/ode.h
	@echo "Creating obj file ode.o..."
	@$(CC) -c math/ode.cc -o math/ode.o
	
difq_test: test/difq_test.cc math/ode.o
	@echo "Building difq_test..."
	@$(CC) -o difq_test test/difq_test.cc math/ode.o $(CFLAGS)
		
matrix_test: test/matrix_test.cc $(MATRIX)
	@echo "Building matrix_test..."
	@$(CC) -o matrix_test test/matrix_test.cc $(CFLAGS)
	
distribution_test: test/distribution_test.cc
	@echo "Building distribution_test..."
	@$(CC) -o distribution_test test/distribution_test.cc $(CFLAGS)

tree_test: test/tree_test.cc
	@echo "Building tree_test..."
	@$(CC) -o tree_test test/tree_test.cc $(CFLAGS)
	
graph_test: test/graph_test.cc
	@echo "Building graph_test..."
	@$(CC) -o graph_test test/graph_test.cc $(CFLAGS)
	
vector_test: test/vector_test.cc $(VECTOR)
	@echo "Building vector_test..."
	@$(CC) -o vector_test test/vector_test.cc $(CFLAGS)

container_test: test/container_test.cc $(CONTAINER)
	@echo "Building container_test..."
	@$(CC) -o container_test test/container_test.cc $(CFLAGS)

prime: math/prime.cc
	@echo "Building prime_test..."
	@$(CC) -o prime math/prime.cc $(CFLAGS)
	
sort_test: test/sort_test.cc
	@echo "Building sort_test..."
	@$(CC) -o sort_test test/sort_test.cc $(CFLAGS)
	
mathfunc_test:  test/mathfunc_test.cc
	@echo "Building mathfunc_test..."
	@$(CC) -o mathfunc_test test/mathfunc_test.cc $(CFLAGS)
	
math/graph_array.o: math/graph_array.cc math/graph_array.h
	@echo "Creating obj file graph_array.o..."
	@$(CC) -c math/graph_array.cc -o math/graph_array.o
	
graph_array_test:  test/graph_array_test.cc math/graph_array.o
	@echo "Building graph_array_test..."
	@$(CC) -o graph_array_test test/graph_array_test.cc math/graph_array.o $(CFLAGS)

ai/number_pattern.o: ai/number_pattern.cc ai/number_pattern.h
	@echo "Creating obj file number_pattern.o..."
	@$(CC) -c ai/number_pattern.cc -o ai/number_pattern.o

pattern_test:  test/pattern_test.cc ai/number_pattern.o
	@echo "Building pattern_test..."
	@$(CC) -o pattern_test test/pattern_test.cc ai/number_pattern.o $(CFLAGS)
	
# Server Tests
server: socket_test server_test
	@echo "Server build complete"
	@date

net/isocket.o: net/isocket.cc net/isocket.h
	@echo "Creating server obj file net/isocket.o..."
	@$(CC) -c net/isocket.cc -o net/isocket.o

net/genecis_server.o: net/genecis_server.cc
	@echo "Creating server obj file net/genecis_server.o..."
	@$(CC) -c net/genecis_server.cc -o net/genecis_server.o

socket_test: test/socket_test.cc $(SRVR_OBJ)
	@echo "Building socket_test..."
	@$(CC) -o socket_test test/socket_test.cc net/isocket.o $(CFLAGS)

server_test: test/server_test.cc $(SRVR_OBJ)
	@echo "Building server_test..."
	@$(CC) -o server_test test/server_test.cc $(SRVR_OBJ) $(CFLAGS)
	
# Physics Tests
gravity_test: test/gravity_test.cc physics/gravity.o physics/gravity.h
	@echo "Building gravity_test..."
	@$(CC) -o gravity_test test/gravity_test.cc physics/gravity.o $(CFLAGS)
		
physics/gravity.o: physics/gravity.cc
	@echo "Creating obj file gravity.o..."
	@$(CC) -c physics/gravity.cc -o physics/gravity.o
	
#physics/gravity_netcdf.o: physics/gravity_netcdf.cc
#	@echo "Creating obj file gravity_netcdf.o..."
#	@$(CC) -c physics/gravity_netcdf.cc -o -lnetcdf physics/gravity_netcdf.o

