CXX=g++
all: sparse_vector_test weight_vector_test data_set_test hash_inline_test
sparse_vector_test:sparse_vector_test.cpp
	$(CXX) -L.. sparse_vector_test.cpp -lsvmformat -o $@

weight_vector_test:weight_vector_test.cpp
	$(CXX) -L.. weight_vector_test.cpp -lsvmformat -o $@

data_set_test:data_set_test.cpp
	$(CXX) -L.. -I.. data_set_test.cpp -lsvmformat -o $@

hash_inline_test:hash_inline_test.cpp
	$(CXX) -L.. -I.. hash_inline_test.cpp -lsvmformat -o $@

clean:
	rm sparse_vector_test
	rm weight_vector_test
	rm data_set_test
	rm hash_inline_test
