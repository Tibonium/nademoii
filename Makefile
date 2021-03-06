#*******************************************************************
#
#        Makefile for the GENeCIS test routines
#
#		 The user needs to have the environment variables
#		 GENECIS_BUILD and GENECIS_SRC set to the the source and
#		 build directories, respectively, on their system.
#
#*******************************************************************

include genecis_config.mk
V = 0
D = 1
VERB_0 = @
VERB_1 = 
OPT_0 = -O3
OPT_1 = -g -O0
OPENGL_LIBS = -lX11 -lGL -lGLU
INSTALL_PATH = /usr/local/include/genecis
GENECIS_FOLDERS = ai algorithm base container distribution tree \
	physics net math signal thread graphics probability base
CFLAGS = -I $(SRC_INCLUDE) -I $(BUILD_PATH)
CC = $(VERB_$(V))g++ $(OPT_$(D)) -Wall -std=c++98 $(CFLAGS)
TESTS = matrix_test distribution_test tree_test difq_test server_test \
	graph_test prime set_test vector_test mathfunc_test quadtree_test \
	container_test graph_array_test pattern_test signal_test numerics_test \
	thread_test	probability_test string_test #gravity_test socket_test
MISC_TESTS = hash_test reference_test boost_test buffer_test template_test \
	extraction_test
MATRIX = $(SRC_PATH)/math/matrix.h $(SRC_PATH)/math/matrix_expression.h \
	$(SRC_PATH)/math/matrix_operations.h $(SRC_PATH)/math/matrix_io.h
VECTOR = $(SRC_PATH)/math/bvector.h $(SRC_PATH)/math/svector.h \
	$(SRC_PATH)/math/cvector.h $(SRC_PATH)/math/vector_expression.h
CONTAINER = $(SRC_PATH)/container/array.h $(SRC_PATH)/container/dynamic_array.h \
	$(SRC_PATH)/container/container_io.h $(SRC_PATH)/container/container_expression.h \
	$(SRC_PATH)/base/genecis_functions.h
MATH_HDR = ${wildcard $(SRC_PATH)/math/*.h}
AI_HDR = ${wildcard $(SRC_PATH)/ai/*.h}
ALGO_HDR = ${wildcard $(SRC_PATH)/algorithm/*.h}
BASE_HDR = ${wildcard $(SRC_PATH)/base/*.h}
CONT_HDR = ${wildcard $(SRC_PATH)/container/*.h}
DIST_HDR = ${wildcard $(SRC_PATH)/distribution/*.h}
TREE_HDR = ${wildcard $(SRC_PATH)/tree/*.h}
PHYS_HDR = ${wildcard $(SRC_PATH)/physics/*.h}
PROB_HDR = ${wildcard $(SRC_PATH)/probability/*.h}
SRVR_HDR = ${wildcard $(SRC_PATH)/net/*.h}
SIG_HDR = ${wildcard $(SRC_PATH)/signal/*.h}
THRD_HDR = ${wildcard $(SRC_PATH)/thread/*.h}
GRPHX_HDR = ${wildcard $(SRC_PATH)/graphics/*.h}

GRPHX_O = sphere.o
GRPHX_OBJ = $(addprefix $(BUILD_PATH)/graphics/, $(GRPHX_O))
MATH_O = graph_array.o ode.o numerics.o
MATH_OBJ = $(addprefix $(BUILD_PATH)/math/, $(MATH_O))
AI_O = number_pattern.o
AI_OBJ = $(addprefix $(BUILD_PATH)/ai/, $(AI_O))
PHYS_O = gravity.o gravity_netcdf.o
PHYS_OBJ = $(addprefix $(BUILD_PATH)/phsyics/, $(PHYS_O))
SRVR_O = isocket.o genecis_server.o
SRVR_OBJ = $(addprefix $(BUILD_PATH)/net/, $(SRVR_O))
SIG_O =
SIG_OBJ = $(addprefix $(BUILD_PATH)/signal/, $(SIG_O))
OBJS = $(AI_O) $(MATH_O) $(SRVR_O) $(SIG_O) $(PHYS_O)

all: regression_test misc_test
	@date
	
install:
	@for main in $(INSTALL_PATH) ; do \
		if [ ! -d "$(INSTALL_PATH)" ] ; \
		then \
			mkdir -p $$main ; \
		fi ; \
	done
	@for folder in $(GENECIS_FOLDERS) ; do \
		if [ ! -d "$(INSTALL_PATH)/$$folder" ] ; \
		then \
			mkdir -p $(INSTALL_PATH)/$$folder ; \
		fi ; \
	done
	@for file in $(AI_HDR) ; do \
		cp $$file $(INSTALL_PATH)/ai/ ; \
	done
	@for file in $(ALGO_HDR) ; do \
		cp $$file $(INSTALL_PATH)/algorithm/ ; \
	done
	@for file in $(BASE_HDR) ; do \
		cp $$file $(INSTALL_PATH)/base/ ; \
	done
	@for file in $(CONT_HDR) ; do \
		cp $$file $(INSTALL_PATH)/container/ ; \
	done
	@for file in $(DIST_HDR) ; do \
		cp $$file $(INSTALL_PATH)/distribution/ ; \
	done
	@for file in $(TREE_HDR) ; do \
		cp $$file $(INSTALL_PATH)/tree/ ; \
	done
	@for file in $(MATH_HDR) ; do \
		cp $$file $(INSTALL_PATH)/math/ ; \
	done
	@for file in $(PHYS_HDR) ; do \
		cp $$file $(INSTALL_PATH)/physics/ ; \
	done
	@for file in $(GRPHX_HDR) ; do \
		cp $$file $(INSTALL_PATH)/graphics/ ; \
	done
	@for file in $(SRVR_HDR) ; do \
		cp $$file $(INSTALL_PATH)/net/ ; \
	done
	@for file in $(SIG_HDR) ; do \
		cp $$file $(INSTALL_PATH)/signal/ ; \
	done
	@for file in $(THRD_HDR) ; do \
		cp $$file $(INSTALL_PATH)/thread/ ; \
	done
	
clean:
	@for test in $(TESTS) ; do \
		if [ -f $$test ] ; \
		then \
			rm $(BUILD_PATH)/$$test ; \
		fi ; \
	done
	@for test in $(MISC_TESTS) ; do \
		if [ -f $$test ] ; \
		then \
			rm $(BUILD_PATH)/$$test ; \
		fi ; \
	done
	@find $(BUILD_PATH) -name "*.o" -exec rm '{}' \;
	@echo "removed $(OBJS)"

# Various miscellaneous test
misc_test: $(MISC_TESTS)
	@echo "Miscellaneous Tests built"

reference_test: $(SRC_PATH)/misc_test/reference_test.cc
	@echo "Building reference_test..."
	$(CC) -o $(BUILD_PATH)/reference_test $(SRC_PATH)/misc_test/reference_test.cc
	
boost_test: $(SRC_PATH)/misc_test/boost_test.cc
	@echo "Building boost_test..."
	$(CC) -o $(BUILD_PATH)/boost_test $(SRC_PATH)/misc_test/boost_test.cc
	
hash_test: $(SRC_PATH)/misc_test/hash_test.cc
	@echo "Building hash_test..."
	$(CC) -o $(BUILD_PATH)/hash_test $(SRC_PATH)/misc_test/hash_test.cc

buffer_test: $(SRC_PATH)/misc_test/buffer_test.cc
	@echo "Building buffer_test..."
	$(CC) -o $(BUILD_PATH)/buffer_test $(SRC_PATH)/misc_test/buffer_test.cc

template_test: $(SRC_PATH)/misc_test/template_test.cc
	@echo "Building template_test..."
	$(CC) -o $(BUILD_PATH)/template_test $(SRC_PATH)/misc_test/template_test.cc

extraction_test: $(SRC_PATH)/misc_test/extraction_test.cc $(CONTAINER)
	@echo "Building extraction_test..."
	$(CC) -o $(BUILD_PATH)/extraction_test $(SRC_PATH)/misc_test/extraction_test.cc

# Regression Tests
regression_test: $(TESTS)
	@echo "Regression Tests built"

$(BUILD_PATH)/math/ode.o: $(SRC_PATH)/math/ode.cc $(SRC_PATH)/math/ode.h
	@echo "Creating obj file ode.o..."
	$(CC) -c $(SRC_PATH)/math/ode.cc -o $(BUILD_PATH)/math/ode.o
	
difq_test: $(SRC_PATH)/test/difq_test.cc $(BUILD_PATH)/math/ode.o
	@echo "Building difq_test..."
	$(CC) -o $(BUILD_PATH)/difq_test $(SRC_PATH)/test/difq_test.cc $(BUILD_PATH)/math/ode.o
		
matrix_test: $(SRC_PATH)/test/matrix_test.cc $(MATRIX) $(CONTAINER)
	@echo "Building matrix_test..."
	$(CC) -o $(BUILD_PATH)/matrix_test $(SRC_PATH)/test/matrix_test.cc
	
distribution_test: $(SRC_PATH)/test/distribution_test.cc
	@echo "Building distribution_test..."
	$(CC) -o $(BUILD_PATH)/distribution_test $(SRC_PATH)/test/distribution_test.cc

tree_test: $(SRC_PATH)/test/tree_test.cc $(CONTAINER) $(TREE_HDR)
	@echo "Building tree_test..."
	$(CC) -o $(BUILD_PATH)/tree_test $(SRC_PATH)/test/tree_test.cc
	
graph_test: $(SRC_PATH)/test/graph_test.cc
	@echo "Building graph_test..."
	$(CC) -o $(BUILD_PATH)/graph_test $(SRC_PATH)/test/graph_test.cc
	
vector_test: $(SRC_PATH)/test/vector_test.cc $(VECTOR)
	@echo "Building vector_test..."
	$(CC) -o $(BUILD_PATH)/vector_test $(SRC_PATH)/test/vector_test.cc

container_test: $(SRC_PATH)/test/container_test.cc $(CONTAINER)
	@echo "Building container_test..."
	$(CC) -o $(BUILD_PATH)/container_test $(SRC_PATH)/test/container_test.cc

prime: $(SRC_PATH)/test/prime.cc
	@echo "Building prime_test..."
	$(CC) -o $(BUILD_PATH)/prime $(SRC_PATH)/test/prime.cc
	
mathfunc_test:  $(SRC_PATH)/test/mathfunc_test.cc
	@echo "Building mathfunc_test..."
	$(CC) -o $(BUILD_PATH)/mathfunc_test $(SRC_PATH)/test/mathfunc_test.cc
	
$(BUILD_PATH)/math/graph_array.o: $(SRC_PATH)/math/graph_array.cc $(SRC_PATH)/math/graph_array.h
	@echo "Creating obj file graph_array.o..."
	$(CC) -c $(SRC_PATH)/math/graph_array.cc -o $(BUILD_PATH)/math/graph_array.o
	
graph_array_test: $(SRC_PATH)/test/graph_array_test.cc $(BUILD_PATH)/math/graph_array.o
	@echo "Building graph_array_test..."
	$(CC) -o $(BUILD_PATH)/graph_array_test $(SRC_PATH)/test/graph_array_test.cc $(BUILD_PATH)/math/graph_array.o

$(BUILD_PATH)/ai/number_pattern.o: $(SRC_PATH)/ai/number_pattern.cc $(SRC_PATH)/ai/number_pattern.h
	@echo "Creating obj file number_pattern.o..."
	$(CC) -c $(SRC_PATH)/ai/number_pattern.cc -o $(BUILD_PATH)/ai/number_pattern.o

pattern_test: $(SRC_PATH)/test/pattern_test.cc $(BUILD_PATH)/ai/number_pattern.o
	@echo "Building pattern_test..."
	$(CC) -o $(BUILD_PATH)/pattern_test $(SRC_PATH)/test/pattern_test.cc $(BUILD_PATH)/ai/number_pattern.o

$(BUILD_PATH)/math/numerics.o: $(SRC_PATH)/math/numerics.cc $(SRC_PATH)/math/numerics.h
	@echo "Creating obj file numerics.o..."
	$(CC) -c $(SRC_PATH)/math/numerics.cc -o $(BUILD_PATH)/math/numerics.o
	
numerics_test: $(SRC_PATH)/test/numerics_test.cc $(BUILD_PATH)/math/numerics.o
	@echo "Building numerics_test..."
	$(CC) -o $(BUILD_PATH)/numerics_test $(SRC_PATH)/test/numerics_test.cc $(BUILD_PATH)/math/numerics.o

set_test: $(SRC_PATH)/test/set_test.cc $(SRC_PATH)/math/set.h $(SRC_PATH)/math/functional_logic.h $(CONTAINER) 
	@echo "Building set_test..."
	$(CC) -o $(BUILD_PATH)/set_test $(SRC_PATH)/test/set_test.cc

quadtree_test: $(SRC_PATH)/test/quadtree_test.cc $(TREE_HDR) $(CONTAINER) 
	@echo "Building quadtree_test..."
	$(CC) -o $(BUILD_PATH)/quadtree_test $(SRC_PATH)/test/quadtree_test.cc

$(BUILD_PATH)/graphics/sphere.o: $(SRC_PATH)/graphics/sphere.cc $(SRC_PATH)/graphics/sphere.h $(CONTAINER)
	@echo "Creating obj file sphere.o..."
	$(CC) -c $(SRC_PATH)/graphics/sphere.cc -o $(BUILD_PATH)/graphics/sphere.o

graphics_test: $(SRC_PATH)/test/graphics_test.cc $(GRPHX_OBJ) $(SRC_PATH)/base/gtime.h
	@echo "Building graphics_test..."
	$(CC) -o $(BUILD_PATH)/graphics_test $(SRC_PATH)/test/graphics_test.cc $(BUILD_PATH)/graphics/sphere.o $(OPENGL_LIBS)
	
probability_test: $(SRC_PATH)/test/probability_test.cc $(PROB_HDR) $(MATH_HDR)
	@echo "Building probability_test..."
	$(CC) -o $(BUILD_PATH)/probability_test $(SRC_PATH)/test/probability_test.cc
	
$(BUILD_PATH)/base/genecis_string.o: $(SRC_PATH)/base/genecis_string.cc $(SRC_PATH)/base/genecis_string.h
	@echo "Creating obj file genecis_string.o...."
	$(CC) -c $(SRC_PATH)/base/genecis_string.cc -o $(BUILD_PATH)/base/genecis_string.o
	
$(BUILD_PATH)/base/genecis_stringlist.o: $(SRC_PATH)/base/genecis_stringlist.cc $(SRC_PATH)/base/genecis_stringlist.h
	@echo "Creating obj file genecis_stringlist.o...."
	$(CC) -c $(SRC_PATH)/base/genecis_stringlist.cc -o $(BUILD_PATH)/base/genecis_stringlist.o
	
string_test: $(SRC_PATH)/test/string_test.cc $(BUILD_PATH)/base/genecis_string.o $(BUILD_PATH)/base/genecis_stringlist.o
	@echo "Building string_test..."
	$(CC) -o $(BUILD_PATH)/string_test $(SRC_PATH)/test/string_test.cc $(BUILD_PATH)/base/genecis_string.o $(BUILD_PATH)/base/genecis_stringlist.o
	
# Server Tests
server: client_test server_test
	@echo "Server build complete"
	@date

$(BUILD_PATH)/net/isocket.o: $(SRC_PATH)/net/isocket.cc $(SRC_PATH)/net/isocket.h
	@echo "Creating server obj file net/isocket.o..."
	$(CC) -c $(SRC_PATH)/net/isocket.cc -o $(BUILD_PATH)/net/isocket.o

$(BUILD_PATH)/net/genecis_server.o: $(SRC_PATH)/net/genecis_server.cc
	@echo "Creating server obj file net/genecis_server.o..."
	$(CC) -c $(SRC_PATH)/net/genecis_server.cc -o $(BUILD_PATH)/net/genecis_server.o

client_test: $(SRC_PATH)/test/client_test.cc $(SRVR_OBJ)
	@echo "Building client_test..."
	$(CC) -o $(BUILD_PATH)/client_test $(SRC_PATH)/test/client_test.cc $(SRVR_OBJ)

server_test: $(SRC_PATH)/test/server_test.cc $(SRVR_OBJ)
	@echo "Building server_test..."
	$(CC) -o $(BUILD_PATH)/server_test $(SRC_PATH)/test/server_test.cc $(SRVR_OBJ)
	
# Physics Tests
gravity_test: $(SRC_PATH)/test/gravity_test.cc $(BUILD_PATH)/physics/gravity.o physics/gravity.h
	@echo "Building gravity_test..."
	$(CC) -o $(BUILD_PATH)/gravity_test $(SRC_PATH)/test/gravity_test.cc $(BUILD_PATH)/physics/gravity.o
		
$(BUILD_PATH)/physics/gravity.o: $(SRC_PATH)/physics/gravity.cc
	@echo "Creating obj file gravity.o..."
	$(CC) -c $(SRC_PATH)/physics/gravity.cc -o $(BUILD_PATH)/physics/gravity.o
	
#physics/gravity_netcdf.o: $(SRC_PATH)/physics/gravity_netcdf.cc
#	@echo "Creating obj file gravity_netcdf.o..."
#	$(CC) -c $(SRC_PATH)/physics/gravity_netcdf.cc -o -lnetcdf $(SRC_PATH)/physics/gravity_netcdf.o

# Signal processing Tests
signal_test: $(SRC_PATH)/test/signal_test.cc $(SIG_HDR)
	@echo "Building signal_test..."
	$(CC) -o $(BUILD_PATH)/signal_test $(SRC_PATH)/test/signal_test.cc

# Thread tests
thread_test: $(SRC_PATH)/test/thread_test.cc $(THRD_HDR)
	@echo "Building thread_test..."
	$(CC) -o $(BUILD_PATH)/thread_test $(SRC_PATH)/test/thread_test.cc -lpthread
