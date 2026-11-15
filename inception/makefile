NAME = Inception

# Caminho obrigatório dos volumes conforme o Subject da 42[cite: 1]
DATA_PATH = /home/kakubo-l/data

all:
	@printf "Construindo a infraestrutura do Inception...\n"
	@sudo mkdir -p $(DATA_PATH)/mariadb
	@sudo mkdir -p $(DATA_PATH)/wordpress
	@sudo chown -R $$USER:$$USER $(DATA_PATH)
	@docker compose -f srcs/docker-compose.yml up -d --build

down:
	@printf "Parando a infraestrutura...\n"
	@docker compose -f srcs/docker-compose.yml down

re: down all

clean:
	@printf "Limpando containers, redes e imagens...\n"
	@docker compose -f srcs/docker-compose.yml down --rmi all -v

fclean: clean
	@printf "Removendo volumes e dados do host...\n"
	@sudo rm -rf $(DATA_PATH)/mariadb/*
	@sudo rm -rf $(DATA_PATH)/wordpress/*

.PHONY: all down re clean fclean