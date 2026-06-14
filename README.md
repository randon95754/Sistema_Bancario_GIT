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
* `develop` → integração das funcionalidades
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
   g++ -std=c++17 -I include src/main/main.cpp src/business/Banco.cpp src/business/ServicoBanco.cpp src/model/Conta.cpp src/model/ContaBonus.cpp src/model/ContaPoupanca.cpp -o bin/app.exe
   ```

3. **Execute o programa**:
   ```powershell
   .\bin\app.exe
   ```

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
