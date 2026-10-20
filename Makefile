CC = g++
CFLAGS = -std=c++20 -Wall -Wextra --coverage -Iinclude -Itests -O0

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

# --- Compilação das classes que você enviou ---
$(OBJ_DIR)/usuario.o: $(SRC_DIR)/usuario.cpp $(INC_DIR)/usuario.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/usuario.cpp -o $@

$(OBJ_DIR)/conta.o: $(SRC_DIR)/conta.cpp $(INC_DIR)/conta.hpp $(INC_DIR)/usuario.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/conta.cpp -o $@

$(OBJ_DIR)/lancamentos.o: $(SRC_DIR)/lancamentos.cpp $(INC_DIR)/lancamentos.hpp $(INC_DIR)/categoria.hpp $(INC_DIR)/conta.hpp $(INC_DIR)/transacao.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/lancamentos.cpp -o $@

$(OBJ_DIR)/despesa.o: $(SRC_DIR)/despesa.cpp $(INC_DIR)/despesa.hpp $(INC_DIR)/transacao.hpp $(INC_DIR)/categoria.hpp $(INC_DIR)/lancamentos.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/despesa.cpp -o $@

$(OBJ_DIR)/receita.o: $(SRC_DIR)/receita.cpp $(INC_DIR)/receita.hpp $(INC_DIR)/transacao.hpp $(INC_DIR)/categoria.hpp $(INC_DIR)/lancamentos.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/receita.cpp -o $@

$(OBJ_DIR)/transacao.o: $(SRC_DIR)/transacao.cpp $(INC_DIR)/transacao.hpp $(INC_DIR)/conta.hpp $(INC_DIR)/lancamentos.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/transacao.cpp -o $@

# --- Compilação opcional do sistema principal ---
sistema: $(OBJ_DIR)/usuario.o $(OBJ_DIR)/conta.o $(OBJ_DIR)/transacao.o $(BIN_DIR)
	@echo "Compilação do sistema principal omitida ou parcial devido a módulos pendentes."

# --- Compilação e Execução dos Testes Unitários ---
# Compila apenas os arquivos de teste correspondentes às classes prontas
$(OBJ_DIR)/main_test.o: $(TEST_DIR)/main_test.cpp $(TEST_DIR)/doctest.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/main_test.cpp -o $@

$(OBJ_DIR)/test_usuario.o: $(TEST_DIR)/test_usuario.cpp $(INC_DIR)/usuario.hpp $(TEST_DIR)/doctest.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_usuario.cpp -o $@

$(OBJ_DIR)/test_conta.o: $(TEST_DIR)/test_conta.cpp $(INC_DIR)/conta.hpp $(TEST_DIR)/doctest.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_conta.cpp -o $@

$(OBJ_DIR)/test_lancamentos.o: $(TEST_DIR)/test_lancamentos.cpp $(INC_DIR)/lancamentos.hpp $(TEST_DIR)/doctest.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_lancamentos.cpp -o $@

$(OBJ_DIR)/test_despesa.o: $(TEST_DIR)/test_despesa.cpp $(INC_DIR)/despesa.hpp $(TEST_DIR)/doctest.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_despesa.cpp -o $@

$(OBJ_DIR)/test_receita.o: $(TEST_DIR)/test_receita.cpp $(INC_DIR)/receita.hpp $(TEST_DIR)/doctest.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_receita.cpp -o $@

$(OBJ_DIR)/test_transacao.o: $(TEST_DIR)/test_transacao.cpp $(INC_DIR)/transacao.hpp $(TEST_DIR)/doctest.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_transacao.cpp -o $@

# Alvo unificado para rodar todos os testes implementados
test: $(OBJ_DIR)/main_test.o $(OBJ_DIR)/test_usuario.o $(OBJ_DIR)/test_conta.o $(OBJ_DIR)/test_lancamentos.o $(OBJ_DIR)/test_despesa.o $(OBJ_DIR)/test_receita.o $(OBJ_DIR)/test_transacao.o $(OBJ_DIR)/usuario.o $(OBJ_DIR)/conta.o $(OBJ_DIR)/lancamentos.o $(OBJ_DIR)/despesa.o $(OBJ_DIR)/receita.o $(OBJ_DIR)/transacao.o $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/main_test.o $(OBJ_DIR)/test_usuario.o $(OBJ_DIR)/test_conta.o $(OBJ_DIR)/test_lancamentos.o $(OBJ_DIR)/test_despesa.o $(OBJ_DIR)/test_receita.o $(OBJ_DIR)/test_transacao.o $(OBJ_DIR)/usuario.o $(OBJ_DIR)/conta.o $(OBJ_DIR)/lancamentos.o $(OBJ_DIR)/despesa.o $(OBJ_DIR)/receita.o $(OBJ_DIR)/transacao.o -o $(BIN_DIR)/exec_tests
	./$(BIN_DIR)/exec_tests

# Relatório de cobertura de código exigido pelo projeto (mínimo 60%)
coverage: test
	gcovr --root . --txt --print-summary
	gcovr --root . --html --html-details -o $(BIN_DIR)/cobertura.html

# Limpeza completa dos artefatos de compilação e cobertura
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) *.gcda *.gcno *.gcov