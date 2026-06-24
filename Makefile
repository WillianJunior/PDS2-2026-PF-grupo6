CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Itest --coverage

APP      = app
TEST_APP = test/testes

ARQUIVOS_ORIGEM = \
    src/Usuario.cpp \
    src/Cliente.cpp \
    src/Produto.cpp \
    src/Estoque.cpp \
    src/Carrinho.cpp \
    src/Pedido.cpp \
    src/Administrador.cpp \
    src/Catalogo.cpp

ARQUIVOS_DE_TESTE = \
    test/main_test.cpp \
    test/testeCliente.cpp \
    test/testeEstoque.cpp \
    test/testeProduto.cpp \
    test/testeCarrinho.cpp \
    test/testePedido.cpp \
    test/testeAdministrador.cpp \
    test/testeCatalogo.cpp \
    test/testeUsuario.cpp

test: clean_gcda $(TEST_APP)
	-./$(TEST_APP)
	@echo ""
	@echo "========== COBERTURA =========="
	gcovr --root . --exclude='test/.*' --print-summary

$(TEST_APP): $(ARQUIVOS_ORIGEM) $(ARQUIVOS_DE_TESTE)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(APP)
	./$(APP)

$(APP): $(ARQUIVOS_ORIGEM) src/Interface.cpp main.cpp
	$(CXX) -std=c++17 -Wall -Iinclude -o $@ $^

clean_gcda:
	find . -name "*.gcda" -delete 2>/dev/null || true

clean: clean_gcda
	rm -f $(TEST_APP) $(APP)
	find . -name "*.gcno" -delete