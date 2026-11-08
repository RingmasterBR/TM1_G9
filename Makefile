CXX = g++
CFLAGS = -std=c++20 -Wall -Wextra --coverage -Iinclude -Itests -O0

# Arquivos objeto das classes do sistema
OBJS = obj/usuario.o obj/conta.o obj/categoria.o obj/lancamentos.o \
       obj/despesa.o obj/receita.o obj/transacao.o obj/orcamento.o \
       obj/gerenciadorfinanceiro.o

# Arquivos objeto dos testes
TEST_OBJS = obj/main_test.o obj/test_usuario.o obj/test_conta.o \
            obj/test_categoria.o obj/test_lancamentos.o obj/test_despesa.o \
            obj/test_receita.o obj/test_transacao.o obj/test_orcamento.o \
            obj/test_gerenciadorfinanceiro.o

all: sistema

# --- Sistema principal ---
sistema: $(OBJS) obj/main.o
	$(CXX) $(CFLAGS) $(OBJS) obj/main.o -o bin/sistema

run: sistema
	./bin/sistema

# --- Testes ---
tests: $(OBJS) $(TEST_OBJS)
	$(CXX) $(CFLAGS) $(OBJS) $(TEST_OBJS) -o bin/exec_tests

run_tests: tests
	./bin/exec_tests

# --- Regras de compilacao ---
# $< e o arquivo .cpp e $@ e o arquivo .o que sera gerado
obj/%.o: src/%.cpp include/*.hpp
	$(CXX) $(CFLAGS) -c $< -o $@

obj/%.o: tests/%.cpp include/*.hpp
	$(CXX) $(CFLAGS) -c $< -o $@

# --- Documentacao ---
documentation:
	doxygen Doxyfile

# --- Limpeza ---
clean:
	rm -f obj/*.o obj/*.gcda obj/*.gcno bin/sistema bin/exec_tests bin/*.exe