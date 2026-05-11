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

## 🚀 Como Executar

### Pré-requisitos

- Compilador C++ (g++) instalado no sistema.
- Sistema operacional Windows/Linux/Mac.

### Passos para Execução

1. **Clone o repositório:**
   ```
   git clone https://github.com/randon95754/Sistema_Bancario_GIT.git
   cd Sistema_Bancario_GIT
   ```

2. **Compile o projeto:**
   ```
   g++ -I include src/main/main.cpp src/business/Banco.cpp src/model/Conta.cpp -o banco.exe
   ```

3. **Execute o programa:**
   ```
   ./banco.exe
   ```

O programa irá executar operações bancárias básicas e exibir os saldos no console, incluindo testes para operações com saldo insuficiente.

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

## 📌 Observações

* Todas as alterações são vinculadas a *issues* (tarefas)
* O projeto prioriza boas práticas de versionamento, não a complexidade da aplicação
* Não há uso de banco de dados nesta fase
