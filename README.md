# EmbarcaTech_Temporizador_1Disparo
Tarefa do EmbarcaTech para projetar um sistema de temporização do acionamento de LED's que inicia por meio do clique de botão

# Intruções
Para executar o código em questão, deve-se possuir a extensão Wokwi Simulator instalada no Visual Studio Code. 

Acesse o arquivo diagram.json, com a extensão Wokwi Simulator instalada, para gerar o ambiente de simulação de uma placa RaspBerry Pi Pico W composto de 3 leds (vermelho, verde e azul), ligados a 3 resitores com 330Ω e um botão(pushbutton).

Ao começar a simulação, não ocorrerá nada até que o botão seja pressionado, apenas após isso, será iniciado de fato o programa que acenderá todos os LED's. Depois de intervalos de 3 segundos um deles se apagará por vez até que todos estejam apagados e o botão seja pressionado novamente para reinício do programa, nâo sendo possível reinicia-lo enquanto a execução ocorre. 

# Composição do código
**Temporizador_1Disparo.c**
- `inicializar_pinos()`: Prepara o pino do botão e dos LED's para uso.
- `button_isr`: Trata a interrupção gerada pelo botão e implementada o debouncing. 
- `timer_callback`: Controla o estado dos LEDs em etapas, com intervalo de 3 segundos entre cada etapa.
- `main`: Lógica que configura e inicia o programa.

# Desenvolvedor
Abel José Rocha Barros Bezerra