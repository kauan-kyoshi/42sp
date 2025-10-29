
import sys

if __name__ == '__main__':
    if len(sys.argv) == 2:
        input_name = sys.argv[1]
        
        COLOR_GREEN = '\033[92m'
        COLOR_RED = '\033[91m'
        COLOR_END = '\033[0m'


        result = fit(input_name)
        length = len(result)

        if length <= 26:
            status_color = COLOR_GREEN
            status_text = "OK - Parabéns!! =)"
        else:
            status_color = COLOR_RED
            status_text = "KO - Tente Novamente =("

        colored_status = f"{status_color}{status_text}{COLOR_END}"

        status = "OK" if length <= 26 else "FALHA (Excede o limite)"
        
        print(f"Original:  {input_name} (caracteres: {len(input_name)})")
        print(f"Resultado: {result} (caracteres: {length})")
        print(f"Status:    {colored_status} (Limite: 26)")
        print("------------------------------------------------")
        
    elif len(sys.argv) < 2:
        print("Erro: Forneça um nome completo como argumento.")
        print('Uso: python3 cardnames.py "Nome Completo Aqui"')
        sys.exit(1)
    
    else:
        print("Erro: Número incorreto de argumentos.")
        sys.exit(1)