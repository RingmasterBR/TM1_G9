# TM1_G9
## Tema: Sistema de Gerenciamento de Gastos Pessoais

## Integrantes

- Giulia Coacci Brum
- João Paulo Varjão Trancoso
- Maísa Oliveira dos Santos de Sá

## Descrição do Projeto

O **Sistema de Gerenciamento de Gastos Pessoais** é um sistema desenvolvido em C++ com foco na aplicação dos conceitos de Programação Orientada a Objetos estudados na disciplina de Programação e Desenvolvimento de Software II (PDS II).

O sistema permite que cada usuário cadastre contas, registre receitas e despesas classificadas por categoria, defina orçamentos mensais com alerta de estouro, consulte o extrato de cada conta, gere relatórios mensais e exporte seus dados para um arquivo de texto. Tudo é feito por uma interface textual interativa no terminal.

## Funcionalidades

### Usuários e Contas

- Cadastro de usuário com nome e senha, e login com autenticação
- Cada usuário pode ter várias contas (ex: Corrente, Poupança) e alternar entre elas
- Saldo e dívida da conta atualizados automaticamente a cada lançamento
- Extrato da conta com todos os lançamentos

### Receitas e Despesas

- Registro de receitas e despesas com valor, categoria, data e indicação de lançamento fixo
- Despesas com data até hoje diminuem o saldo; despesas com data futura entram como dívida
- Receitas com data futura ficam pendentes e só entram no saldo quando a data chegar
- Validação de todos os dados (valor positivo, data existente, categoria e conta obrigatórias)

### Categorias

- Classificação por tipo de gasto (Alimentação, Transporte, Lazer, Saúde, Educação, Outros) e forma de pagamento (Crédito, Débito, Pix)

### Orçamentos

- Definição de limite de gastos por tipo de gasto e mês/ano
- Contabilização automática das despesas do mesmo tipo e período (inclusive as já registradas antes do orçamento)
- Alerta quando o limite é ultrapassado

### Relatórios e Persistência

- Relatório mensal com os lançamentos de cada conta, total de receitas e despesas, resultado do mês, gastos por tipo e situação dos orçamentos
- Exportação dos dados do usuário (contas, lançamentos e orçamentos) para arquivo de texto
- Leitura e validação de arquivos exportados

## Estrutura do Projeto

```
TM1_G9/
├── include/      arquivos .hpp (uma classe por arquivo)
├── src/          arquivos .cpp (implementação e main.cpp)
├── tests/        testes de unidade (doctest)
├── design/       User Stories e cartões CRC
├── obj/          arquivos objeto gerados na compilação
├── bin/          executáveis gerados na compilação
├── Makefile
└── Doxyfile
```

### Classes

| Classe | Responsabilidade |
|---|---|
| `Usuario` | Dados de login, autenticação e criação das próprias contas |
| `Conta` | Saldo, dívida, histórico de lançamentos e transações |
| `Lancamentos` (abstrata) | Dados comuns de um lançamento e interface polimórfica |
| `Receita` / `Despesa` | Implementam como cada lançamento afeta saldo e dívida |
| `Transacao` | Aplica os lançamentos pendentes e registra saldo/dívida antes e depois |
| `Categoria` | Tipo de gasto e forma de pagamento |
| `Orcamento` | Limite de gastos por tipo e período |
| `GerenciadorFinanceiro` | Coordena conta, lançamentos e orçamentos; relatórios e exportação |
| `InterfaceTerminal` | Menus, leitura e validação das entradas do usuário |

## Principais Decisões de Implementação

- **Herança e polimorfismo:** `Lancamentos` é uma classe abstrata com os métodos virtuais puros `aplicarEfeito`, `isDespesa` e `getTipoTexto`. `Receita` e `Despesa` implementam cada um do seu jeito, e a `Transacao` percorre os lançamentos pela classe base sem precisar saber qual é qual.
- **Encapsulamento:** todos os atributos são privados (ou protegidos em `Lancamentos`, para as subclasses) e acessados por métodos. Atributos privados terminam com `_` e métodos seguem lowerCamelCase.
- **Tratamento de exceções:** as classes validam seus parâmetros e lançam `std::invalid_argument` quando recebem dados inválidos, e `std::runtime_error` em erros de arquivo. A interface captura essas exceções, mostra a mensagem e continua funcionando.
- **Sanitização das entradas:** a `InterfaceTerminal` lê sempre linhas inteiras, converte com verificação e repete a pergunta enquanto o valor for inválido (texto no lugar de número, valor fora do intervalo, data inexistente, campo vazio).
- **Gerenciamento de memória:** cada objeto tem um único dono responsável por desalocá-lo. O `Usuario` libera suas contas e seu gerenciador, a `Conta` libera suas transações e a `InterfaceTerminal` libera os usuários, categorias, lançamentos e orçamentos que criou. As classes donas não podem ser copiadas.
- **Interface testável:** a `InterfaceTerminal` recebe os fluxos de entrada e saída no construtor, o que permite testar os menus com `std::stringstream`. O `main.cpp` contém apenas a função `main`.

## Compilação e Execução

Requisitos: `g++` com suporte a C++20 e `make`.

| Comando | O que faz |
|---|---|
| `make` | Compila o sistema (`bin/sistema`) |
| `make run` | Compila e executa o sistema |
| `make tests` | Compila os testes (`bin/exec_tests`) |
| `make run_tests` | Compila e executa os testes |
| `make coverage` | Executa os testes e mostra a cobertura de cada arquivo (gcov) |
| `make documentation` | Gera a documentação com Doxygen na pasta `html/` |
| `make clean` | Apaga os arquivos gerados na compilação |

## Testes e Cobertura

Os testes de unidade usam a biblioteca [doctest](https://github.com/doctest/doctest) e ficam na pasta `tests/`, um arquivo por classe. Eles cobrem o funcionamento normal de cada classe, os casos de erro (exceções) e os fluxos da interface.

Cobertura de linhas medida com `make coverage`: **cerca de 97%** do código em `src/`. Apenas o `main.cpp` (8 linhas, que só cria a interface) não é executado pelos testes.

## Limitações e Trabalhos Futuros

- Lançamentos fixos são registrados e identificados, mas ainda não são repetidos automaticamente nos meses seguintes.
- Uma despesa futura é contada como dívida; quando a data chega, ela ainda não é transferida da dívida para o saldo.
- Os dados ficam em memória durante a execução; o arquivo exportado é validado na leitura, mas ainda não é usado para restaurar o estado do sistema.
- As User Stories de gestão familiar (US2) e de gerente financeiro (US3) não foram implementadas nesta versão.

## Aplicabilidade

O sistema pode ser utilizado como base para soluções de controle financeiro pessoal, servindo tanto para uso individual quanto como ponto de partida para sistemas de gestão financeira mais amplos (familiar, de pequenos negócios, etc.).
