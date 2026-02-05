//headers
//headers
//headers
//headers
//headers


	// Buffer para leitura em chunks (ajustado para 8192)
	// Ponteiro para onde a palavra alvo foi encontrada
	// Ponteiro móvel para percorrer o buffer atual
	// Quantidade de bytes lidos na última chamada read
	// Tamanho da palavra a ser filtrada
	// Contador para o loop de asteriscos
	// Tamanho do residual (sobra) que ficou no buffer

	// Validação de argumentos: precisa de exatamente 1 alvo não vazio


	// Loop principal: lê dados do stdin e coloca logo após o residual anterior

		// Atualiza o total de dados válidos no buffer
		// Reinicia o ponteiro de busca para o início do buffer

		// Busca por ocorrências enquanto houver dados suficientes para um match

			// Escreve tudo o que estava ANTES da palavra encontrada


			// Substitui a palavra encontrada por asteriscos


			// Move o ponteiro para depois da palavra filtrada

		// Calcula quanto sobrou no buffer que não foi processado (fragmento final)

		// Move esse residual para o início do buffer para a próxima rodada


	// Se o read retornar -1, houve um erro de sistema


	// Escreve o último residual que sobrou após o fim do arquivo (EOF)
