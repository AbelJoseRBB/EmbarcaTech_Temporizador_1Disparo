#include <stdio.h>
#include "pico/stdlib.h"

#define botao 5
#define pin_red 13
#define pin_blue 12
#define pin_green 11

volatile bool botao_press = false;  // Variável global que determina se o botão foi pressionado 
volatile bool timer_funcionando = false;    // Variável global que determina se o timer está em execução  
int cont = 0;   // Contador para determinar o estado dos LED's

// Função que inicializa todos os pinos
void inicializar_pinos(){
    gpio_init(botao);
    gpio_set_dir(botao, GPIO_IN);
    gpio_pull_up(botao);

    gpio_init(pin_red);
    gpio_set_dir(pin_red, GPIO_OUT);

    gpio_init(pin_blue);
    gpio_set_dir(pin_blue, GPIO_OUT);
    
    gpio_init(pin_green);
    gpio_set_dir(pin_green, GPIO_OUT);
}

// Função de interrupção para detectar o pressionamento do botão com debounce
void button_isr(uint gpio, uint32_t events){
    static absolute_time_t last_press = 0;  // Armazena o tempo do último pressionamento
    absolute_time_t now = get_absolute_time();  // Obtém o tempo atual

    // Impede que a lógica do botão seja detectado novamente enquanto o timer está sendo executado
    if(!timer_funcionando){     
        if(absolute_time_diff_us(last_press, now) > 100000){    // Debouncing de 100 ms
            if(!gpio_get(botao)){   // Verifica se o botâo está pressionado
                botao_press = true; // Sinaliza que o botão foi pressionado     
            }
            last_press = now;   // Atualiza o tempo do último pressionamento
        }
    }
}

// Funçao de callback do temporizador que controla o desligamento dos LED's
int64_t timer_callback(alarm_id_t id, void *user_data){
    switch(cont){
        case 0: gpio_put(pin_green, 0);
                cont++;
                break;
        case 1: gpio_put(pin_blue, 0);
                cont++;
                break;
        case 2: gpio_put(pin_red, 0);
                timer_funcionando = false;  // Finaliza o timer
                return 0;   // Interrompe o temporizador
                break;
    }
    return 3000 * 1000; // Retorna um delay de 3 segundos
}

int main()
{
    stdio_init_all();
    inicializar_pinos();

    // Configura o callback do botão  
    gpio_set_irq_enabled_with_callback(botao,  GPIO_IRQ_EDGE_FALL, true, &button_isr);

    while (true) {
        if(botao_press){
            printf("Botão Pressionado\n");
            botao_press = false;    // Botão parou de ser pressionado 
            timer_funcionando = true;   // Timer foi iniciado
            cont = 0;   // Reinicia o contador
            
            gpio_put(pin_green, 1);
            gpio_put(pin_blue, 1);
            gpio_put(pin_red, 1);
            
            // Inicia o temporizador com intervalo de 3 segundos
            add_alarm_in_ms(3000, timer_callback, NULL, false); 
        }
        sleep_ms(50);   // Pequena pausa para reduzir o uso da CPU
    }
    return 0;
}
