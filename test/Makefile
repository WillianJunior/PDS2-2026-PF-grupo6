
CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -Ithird_party --coverage

TEST_APP = testes

SRC_FILES = \
	src/Cliente.cpp \
	src/Produto.cpp \
	src/Administrador.cpp \
	src/Carrinho.cpp \
	src/Estoque.cpp \
	src/Catalogo.cpp \
	src/Pedido.cpp

TEST_FILES = \
	test/main_test.cpp \
	test/testeCliente.cpp \
	test/testeProduto.cpp \
	test/testeAdministrador.cpp \
	test/testeCarrinho.cpp \
	test/testeEstoque.cpp \
	test/testeCatalogo.cpp \
	test/testePedido.cpp

test:
	$(CXX) $(CXXFLAGS) $(SRC_FILES) $(TEST_FILES) -o $(TEST_APP)
	./$(TEST_APP) > test/test.txt	
	gcovr -r . --html --html-details -o coverage.html

clean:
	rm -f $(TEST_APP)
	rm -f *.gcda
	rm -f *.gcno
	rm -f coverage.html
	rm -f test/test.txt




