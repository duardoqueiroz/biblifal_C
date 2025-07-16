# Sistema de Biblioteca IFAL Arapiraca

## Descrição Geral

Este programa é um sistema simples de gerenciamento de biblioteca, desenvolvido em C, que permite:
- Cadastrar e listar alunos
- Cadastrar e listar livros
- Solicitar empréstimo de livros (fila de espera)
- Registrar devolução de livros (pilha de devoluções)
- Consultar a fila de espera de empréstimos
- Consultar o histórico de livros devolvidos

O sistema é totalmente interativo via terminal.

---

## Como Executar

1. Compile o código com:
   ```sh
   gcc -o biblioteca biblioteca.c
   ```
2. Execute o programa:
   ```sh
   ./biblioteca
   ```

---

## Funcionamento do Programa

Ao iniciar, o usuário verá um menu principal com as opções:
1. Gerenciar alunos (cadastrar, listar)
2. Gerenciar livros (cadastrar, listar)
3. Solicitar empréstimo de livro
4. Devolver livro
5. Consultar fila de espera
6. Consultar livros devolvidos
7. Sair

### Fluxos principais:
- **Cadastro de alunos/livros:**
  - Permite adicionar novos alunos e livros ao sistema.
- **Solicitação de empréstimo:**
  - O usuário informa a matrícula do aluno e o código do livro. A solicitação entra em uma fila de espera.
- **Devolução de livro:**
  - O usuário informa o código do livro devolvido, que é registrado em uma pilha de devoluções.
- **Consulta de fila de espera:**
  - Mostra todos os empréstimos pendentes, em ordem de chegada.
- **Consulta de livros devolvidos:**
  - Mostra o histórico dos livros devolvidos, do mais recente para o mais antigo.

---

## Justificativa das Estruturas de Dados

### 1. Fila de Solicitações de Empréstimo (`LoanRequestQueue`)
- **Por quê?**
  - A fila (queue) garante que os empréstimos sejam processados na ordem em que foram solicitados (primeiro a entrar, primeiro a sair - FIFO).
  - Isso é fundamental para garantir justiça entre os usuários, sejam eles alunos, funcionários ou usuários externos, evitando privilégios indevidos.
- **Como funciona?**
  - Cada solicitação de empréstimo é um nó na fila, contendo a matrícula do aluno e o código do livro.
  - O sistema processa as solicitações na ordem de chegada.

### 2. Pilha de Livros Devolvidos (`ReturnedBooksStack`)
- **Por quê?**
  - A pilha (stack) permite registrar rapidamente os livros devolvidos, sempre colocando o mais recente no topo (último a entrar, primeiro a sair - LIFO).
  - Isso facilita consultas rápidas sobre os livros devolvidos recentemente, útil para controle interno e auditoria.
- **Como funciona?**
  - Cada devolução adiciona o código do livro ao topo da pilha.
  - Ao consultar, o sistema mostra do mais recente para o mais antigo.

### 3. Vetores Dinâmicos para Alunos e Livros
- **Por quê?**
  - Permitem armazenar um número variável de alunos e livros, crescendo conforme a necessidade.
  - Atende tanto a demanda de usuários internos (alunos, funcionários) quanto externos, sem limitação rígida.

---

## Situação de Usuários Internos e Externos

- **Usuários internos (alunos, funcionários):**
  - Podem cadastrar-se, solicitar empréstimos e devolver livros normalmente.
  - A fila garante que todos sejam atendidos por ordem de solicitação, sem privilégios.
- **Usuários externos:**
  - O sistema pode ser facilmente adaptado para incluir outros tipos de usuários, bastando cadastrar seus dados como "alunos" ou criar uma estrutura similar.
  - O controle por fila e pilha garante tratamento igualitário e histórico confiável para todos.

---

## Observações
- O sistema é simples e pode ser expandido para incluir mais funcionalidades, como autenticação, relatórios, etc.
- O uso de fila e pilha torna o controle de empréstimos e devoluções eficiente e justo. 
