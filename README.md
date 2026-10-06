# TM1_G9
## Tema: Sistema de Gerenciamento de Gastos Pessoais

## Integrantes

- Giulia Coacci Brum
- João Paulo Varjão Trancoso
- Maísa Oliveira dos Santos de Sá
  

## Descrição do Projeto

O **Sistema de Gerenciamento de Gastos Pessoais** é um sistema desenvolvido em C++ com foco na aplicação dos conceitos de Programação Orientada a Objetos estudados na disciplina de Programação e Desenvolvimento de Software II (PDS II).

O sistema permite o controle completo das finanças pessoais do usuário, possibilitando o cadastro de contas, o registro de receitas e despesas, a organização por categorias e a definição de orçamentos com alertas de estouro. Também oferece a geração de relatórios financeiros e a persistência dos dados em arquivos de texto.

A aplicação foi desenvolvida utilizando conceitos como herança, polimorfismo, abstração, encapsulamento, tratamento de exceções e testes unitários.

## Funcionalidades

### Controle de Usuário e Contas

- Cadastro e autenticação do usuário
- Cadastro de múltiplas contas (corrente, poupança, carteira)
- Atualização automática de saldo a cada transação
- Consulta de extrato por conta

### Controle de Transações

- Registro de receitas e despesas
- Validação dos dados da transação (valor, data, descrição)
- Aplicação polimórfica do efeito da transação sobre o saldo

### Categorias

- Classificação das transações por categoria (alimentação, transporte, lazer, etc.)
- Agrupamento de transações para fins de relatório

### Orçamentos

- Definição de limite de gastos por categoria e período
- Verificação automática de estouro de orçamento
- Emissão de alertas quando o limite é ultrapassado

### Relatórios

- Resumo de receitas e despesas por período
- Totais agregados por categoria
- Estatísticas gerais das finanças do usuário

### Persistência

- Armazenamento dos dados em arquivos de texto
- Carregamento dos dados salvos ao iniciar o sistema

### Interface

- Interface textual interativa via terminal
- Validação de entradas do usuário
- Tratamento de erros através de exceções

## Estrutura do Projeto

### Usuário e Contas

- `Usuario`
- `Conta`

### Transações

- `Transacao` (classe abstrata)
  - `Receita`
  - `Despesa`

### Classificação e Controle

- `Categoria`
- `Orcamento`

### Classe Coordenadora

- `GerenciadorFinanceiro`

## Tecnologias Utilizadas

- C++
- Programação Orientada a Objetos (POO)
- Testes unitários
- Makefile
- Doxygen

## Compilação e Execução

### Compilar o sistema

```
make
```

### Executar o sistema

```
make run
```

### Compilar os testes

```
make tests
```

### Executar os testes

```
make run_tests
```

### Gerar documentação com Doxygen

```
make documentation
```

## Cobertura de Testes

*(a preencher conforme os testes unitários forem desenvolvidos)*

## Aplicabilidade

O sistema pode ser utilizado como base para soluções de controle financeiro pessoal, servindo tanto para uso individual quanto como ponto de partida para sistemas de gestão financeira mais amplos (familiar, de pequenos negócios, etc.).

Além da aplicação prática, o projeto demonstra a utilização de boas práticas de desenvolvimento orientado a objetos, servindo como exemplo acadêmico para sistemas de controle e gerenciamento de dados.

