CC = g++
CFLAGS = -std=c++17 -Wall -Iinclude

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin

all: sistema

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/usuario.o: $(SRC_DIR)/usuario.cpp $(INC_DIR)/usuario.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/usuario.cpp -o $@

$(OBJ_DIR)/conta.o: $(SRC_DIR)/conta.cpp $(INC_DIR)/conta.hpp $(INC_DIR)/usuario.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/conta.cpp -o $@

$(OBJ_DIR)/transacao.o: $(SRC_DIR)/transacao.cpp $(INC_DIR)/transacao.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/transacao.cpp -o $@

$(OBJ_DIR)/categoria.o: $(SRC_DIR)/categoria.cpp $(INC_DIR)/categoria.hpp $(INC_DIR)/usuario.hpp $(INC_DIR)/conta.hpp $(INC_DIR)/transacao.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/categoria.cpp -o $@

$(OBJ_DIR)/despesa.o: $(SRC_DIR)/despesa.cpp $(INC_DIR)/despesa.hpp $(INC_DIR)/transacao.hpp $(INC_DIR)/categoria.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/despesa.cpp -o $@

$(OBJ_DIR)/receita.o: $(SRC_DIR)/receita.cpp $(INC_DIR)/receita.hpp $(INC_DIR)/transacao.hpp $(INC_DIR)/categoria.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/receita.cpp -o $@

$(OBJ_DIR)/orcamento.o: $(SRC_DIR)/orcamento.cpp $(INC_DIR)/orcamento.hpp $(INC_DIR)/categoria.hpp $(INC_DIR)/transacao.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/orcamento.cpp -o $@

$(OBJ_DIR)/gerenciador_financeiro.o: $(SRC_DIR)/gerenciador_financeiro.cpp $(INC_DIR)/gerenciador_financeiro.hpp $(INC_DIR)/usuario.hpp $(INC_DIR)/conta.hpp $(INC_DIR)/transacao.hpp $(INC_DIR)/orcamento.hpp $(INC_DIR)/categoria.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/gerenciador_financeiro.cpp -o $@



sistema: $(OBJ_DIR)/usuario.o $(OBJ_DIR)/conta.o $(OBJ_DIR)/transacao.o $(OBJ_DIR)/categoria.o $(OBJ_DIR)/despesa.o $(OBJ_DIR)/receita.o $(OBJ_DIR)/orcamento.o $(OBJ_DIR)/gerenciador_financeiro.o $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/*.o main.cpp -o $(BIN_DIR)/sistema

# testes
$(OBJ_DIR)/main_test.o: $(TEST_DIR)/main_test.cpp $(TEST_DIR)/doctest.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/main_test.cpp -o $@

$(OBJ_DIR)/test_despesa.o: $(TEST_DIR)/test_despesa.cpp $(INC_DIR)/despesa.hpp $(TEST_DIR)/doctest.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_despesa.cpp -o $@

$(OBJ_DIR)/test_orcamento.o: $(TEST_DIR)/test_orcamento.cpp $(INC_DIR)/orcamento.hpp $(TEST_DIR)/doctest.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_orcamento.cpp -o $@

# Compilação e execução dos testes com suporte a cobertura de código
test: $(OBJ_DIR)/main_test.o $(OBJ_DIR)/test_despesa.o $(OBJ_DIR)/test_orcamento.o $(OBJ_DIR)/transacao.o $(OBJ_DIR)/categoria.o $(OBJ_DIR)/despesa.o $(OBJ_DIR)/orcamento.o $(BIN_DIR)
	$(CC) -std=c++17 -Wall -Iinclude -Itests --coverage -O0 $(TEST_DIR)/main_test.cpp $(TEST_DIR)/test_despesa.cpp $(TEST_DIR)/test_orcamento.cpp $(SRC_DIR)/transacao.cpp $(SRC_DIR)/categoria.cpp $(SRC_DIR)/despesa.cpp $(SRC_DIR)/orcamento.cpp -o $(BIN_DIR)/exec_tests
	./$(BIN_DIR)/exec_tests

# limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) *.gcda *.gcno