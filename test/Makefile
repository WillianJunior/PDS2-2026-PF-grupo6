CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -Ithird_party --coverage 

TESTE_APP = testes

TEXT_FILES =\
	test/main_test.cpp\
	test/testeCliente.cpp\
	test/testeProduto.cpp\
	test/testeAdministrador.cpp\
	test/testeCarrinho.cpp\
	test/testePedido.cpp\
	test/testeEstoque.cpp\
	test/testeCatalogo.cpp\

test:
$(CXX) $(CXXFLAGS) $(TEST_FILES) -o $(TEST_APP)
./$(TEST_APP)
gcovr -r . --html --html-details -o coverage.html

clean:
	rm -f $(TEST_APP)
	rm -f *.gcda
	rm -f *.gcno
	rm -f coverage.html




