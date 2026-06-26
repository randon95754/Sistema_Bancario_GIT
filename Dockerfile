# Estágio 1: Compilação do código C++ para Linux
FROM gcc:12 AS builder

WORKDIR /usr/src/app

# Copiar todos os arquivos para o container
COPY . .

# Compilar o executável para Linux (sem winsock, g++ definirá __linux__)
RUN g++ -std=c++17 -I include \
    src/main/main.cpp \
    src/business/Banco.cpp \
    src/business/ServicoBanco.cpp \
    src/model/Conta.cpp \
    src/model/ContaBonus.cpp \
    src/model/ContaPoupanca.cpp \
    -o app

# Estágio 2: Ambiente de Execução Enxuto
FROM debian:bookworm-slim

WORKDIR /app

# Copiar o binário compilado do estágio anterior
COPY --from=builder /usr/src/app/app .

# Expor a porta 8080 usada pela API REST
EXPOSE 8080

# Definir o comando padrão de execução
CMD ["./app"]
