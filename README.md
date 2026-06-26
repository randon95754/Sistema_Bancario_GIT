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

## 🐳 Como Executar com Docker

Uma alternativa moderna e portável é executar a API REST através de um container Docker.

### Pré-requisitos
- [Docker Desktop](https://www.docker.com/products/docker-desktop/) instalado e em execução.

### Passos para Construir e Executar

1. **Construa a imagem Docker**:
   ```powershell
   docker build -t flowbank-api .
   ```

2. **Execute o container mapeando as portas**:
   Se a porta `8080` do seu computador estiver livre, execute:
   ```powershell
   docker run -d -p 8080:8080 --name flowbank-app flowbank-api
   ```
   Caso a porta `8080` já esteja em uso por algum outro processo local do sistema ou do próprio Docker/WSL, execute mapeando para a porta `8081` do host:
   ```powershell
   docker run -d -p 8081:8080 --name flowbank-app flowbank-api
   ```

3. **Teste os endpoints (usando a porta correspondente, ex: 8080 ou 8081)**:
   ```powershell
   # Exemplo testando na porta 8081:
   curl -s -X POST http://localhost:8081/banco/conta/ -H "Content-Type: application/json" -d "{\"numero\":101,\"tipo\":\"bonus\"}"
   curl -s http://localhost:8081/banco/conta/101
   curl -s http://localhost:8081/banco/conta/101/saldo
   ```


### ☁️ Executar a Imagem Oficial do Docker Hub

Se você quiser apenas rodar a API diretamente sem precisar clonar o repositório ou fazer o build manual, pode baixar e executar a imagem publicada no Docker Hub:

```powershell
# Se a porta 8080 estiver livre no seu host:
docker run -d -p 8080:8080 --name flowbank-app ivisonfilho/flowbank-api:latest

# Se a porta 8080 estiver ocupada, mapeie para a porta 8081:
docker run -d -p 8081:8080 --name flowbank-app ivisonfilho/flowbank-api:latest
```

4. **Gerenciamento do Container**:
   - Parar execução: `docker stop flowbank-app`
   - Iniciar execução parada: `docker start flowbank-app`
   - Remover container: `docker rm flowbank-app`
   - Visualizar logs: `docker logs -f flowbank-app`

---

## �📌 Observações

* Todas as alterações são vinculadas a *issues* (tarefas)
* O projeto prioriza boas práticas de versionamento, não a complexidade da aplicação
* Não há uso de banco de dados nesta fase
