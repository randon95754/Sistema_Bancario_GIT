# 💰 Sistema Bancário (FlowBank)

## 📌 Descrição

Projeto de um sistema bancário simples, desenvolvido como parte da disciplina **Gerência de Configuração e Mudanças**.
O sistema irá contemplar operações básicas de contas bancárias, com foco na organização do repositório e boas práticas de versionamento.

---

## 👥 Equipe

* **Ivison Santana Cau Filho**
  
  GitHub: https://github.com/IvisonFilho

* **Randson Thiago Sales Da Silva Lima**
  
  GitHub: https://github.com/randon95754


---


## 🛠️ Tecnologias e Stack

* **Linguagem:** C++
* **Paradigma:** Programação Orientada a Objetos
* **Interface:** Console (CLI)
* **Compilador:** g++
* **Controle de Versão:** Git + GitHub
* **Fluxo de Branches:** GitLab Flow


---

## 🌿 Estratégia de Branches

O projeto segue o padrão **GitLab Flow**, com as seguintes branches:

* `main` → versão estável
* `staging` → homologação e estabilização
* `feature/*` → desenvolvimento de novas funcionalidades
* `bugfix/*` → correção de erros

> Nenhuma branch será removida durante o projeto, conforme as regras da disciplina.

---

## 📋 Organização do Projeto

O sistema será estruturado em camadas:

* **Camada de Interface (UI)** → Responsável pela interação com o usuário via terminal.
* **Camada de Negócio** → regras e operações bancárias

---

## 🔗 Repositório

Link do projeto:
👉 https://github.com/randon95754/Sistema_Bancario_GIT/tree/main

---

## � Como Executar

### Pré-requisitos
- Compilador C++: g++ (disponível no MinGW ou MSYS2 no Windows)
- Sistema operacional: Windows, Linux ou macOS

### Passos para Compilar e Executar

1. **Clone o repositório** (se ainda não clonou):
   ```powershell
   git clone https://github.com/randon95754/Sistema_Bancario_GIT.git
   cd Sistema_Bancario_GIT
   ```

2. **Compile o projeto (g++)** — compila todos os arquivos fontes e coloca o binário em `bin/app.exe`:
   ```powershell
   mkdir -Force bin
   g++ -std=c++17 -I include src/main/main.cpp src/business/Banco.cpp src/business/ServicoBanco.cpp src/model/Conta.cpp src/model/ContaBonus.cpp src/model/ContaPoupanca.cpp -o bin/app.exe -lws2_32
   ```\

3. **Execute o programa**:
   ```powershell
   .\bin\app.exe
   ```\

4. **Teste o servidor REST** (em outro terminal):
   ```powershell
   curl -s -X POST http://localhost:8080/banco/conta/ -H "Content-Type: application/json" -d "{\"numero\":101,\"tipo\":\"bonus\"}"
   curl -s http://localhost:8080/banco/conta/101
   curl -s http://localhost:8080/banco/conta/101/saldo
   curl -s -X PUT http://localhost:8080/banco/conta/101/credito -H "Content-Type: application/json" -d "{\"valor\":150.0}"
   curl -s -X PUT http://localhost:8080/banco/conta/101/debito -H "Content-Type: application/json" -d "{\"valor\":50.0}"
   curl -s -X PUT http://localhost:8080/banco/conta/transferencia -H "Content-Type: application/json" -d "{\"from\":101,\"to\":102,\"amount\":25.0}"
   curl -s -X PUT http://localhost:8080/banco/conta/rendimento -H "Content-Type: application/json" -d "{\"numero\":102,\"taxa\":1.5}"
   ```
   O primeiro comando cria uma conta; o segundo consulta essa conta; o terceiro consulta o saldo; o quarto credita a conta; o quinto debita a conta; o sexto transfere entre contas; o sétimo aplica rendimento a uma conta poupança.


Alternativa (MSVC/Visual Studio Developer Prompt):
   ```powershell
   cl /EHsc /I include src\main\main.cpp src\business\Banco.cpp src\business\ServicoBanco.cpp src\model\Conta.cpp src\model\ContaBonus.cpp src\model\ContaPoupanca.cpp /Fe:bin\app.exe
   .\bin\app.exe
   ```

O programa exibirá saídas no console com exemplos de operações (criação de contas, depósitos, transferências, testes de ContaBonus e ContaPoupanca).

---

## �📌 Observações

* Todas as alterações são vinculadas a *issues* (tarefas)
* O projeto prioriza boas práticas de versionamento, não a complexidade da aplicação
* Não há uso de banco de dados nesta fase

---

## ⚓ Git Hooks (Validação de Commits)

Este repositório possui uma política de validação de mensagens de commit integrada localmente via Git Hooks. 

### Regras de Validação (commit-msg):
1. **Formato**: A primeira linha da mensagem do commit deve iniciar com o número de uma issue correspondente no formato `#NUM_ISSUE – MENSAGEM` (ex: `#33 – Correção da tela`). O script aceita hífen simples (`-`), meia-risca (`–`) ou travessão (`—`) cercados por espaços.
2. **Existência da Issue**: O `#NUM_ISSUE` é validado automaticamente via API pública do GitHub para garantir que a issue realmente existe no repositório. Commits inválidos são rejeitados localmente. *(Em caso de falha de conexão ou offline, o script emitirá um `AVISO` e permitirá o commit para não travar o desenvolvimento).*

---

### Como Configurar e Usar

Existem duas formas de configurar este validador no seu repositório local:

#### Opção A: Utilizando a pasta `hooks/` da raiz do repositório (Recomendado/Entregável)
Esta opção lê o script versionado diretamente na raiz do projeto. Qualquer alteração ou atualização no script de validação é automaticamente sincronizada via Git.

1. No terminal, execute o seguinte comando na raiz do projeto para configurar o Git a ler os hooks desta pasta:
   ```powershell
   git config core.hooksPath hooks
   ```
2. Caso esteja no Linux ou macOS, dê permissão de execução ao script rodando:
   ```bash
   chmod +x hooks/commit-msg
   ```
   *(No Windows, a permissão de execução já foi adicionada ao rastreamento do Git).*

#### Opção B: Utilizando a pasta interna oculta do Git (`.git/hooks/`)
Se preferir usar o comportamento padrão do Git sem alterar a configuração global de caminhos de hooks do seu repositório local:

1. Copie o script `hooks/commit-msg` para dentro da pasta oculta `.git/hooks/`:
   * **Windows (PowerShell)**:
     ```powershell
     Copy-Item -Path hooks/commit-msg -Destination .git/hooks/commit-msg -Force
     ```
   * **Linux/macOS/Git Bash**:
     ```bash
     cp hooks/commit-msg .git/hooks/commit-msg
     chmod +x .git/hooks/commit-msg
     ```
2. Certifique-se de remover a configuração de caminho customizado do seu repositório local (caso a tenha ativado anteriormente):
   ```powershell
   git config --unset core.hooksPath
   ```

