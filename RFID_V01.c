#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include <string.h> // Inclui a biblioteca para manipulação de strings
#include <esp_log.h> // Inclui a biblioteca de log do ESP
#include "rc522.h" // Inclui o cabeçalho do RC522
#include "driver/rc522_spi.h" // Inclui o cabeçalho do driver SPI para RC522
#include "rc522_picc.h" // Inclui o cabeçalho para manipulação de PICC

static const char *TAG = "RFID_V01"; // Define uma constante para tag de log

#define RC522_SPI_BUS_GPIO_MISO    (25) // Define o pino MISO para o bus SPI
#define RC522_SPI_BUS_GPIO_MOSI    (23) // Define o pino MOSI para o bus SPI
#define RC522_SPI_BUS_GPIO_SCLK    (19) // Define o pino SCLK para o bus SPI
#define RC522_SPI_SCANNER_GPIO_SDA (22) // Define o pino SDA para o scanner SPI
#define RC522_SCANNER_GPIO_RST     (-1) // Define o pino RST para soft-reset

static rc522_spi_config_t driver_config = { // Inicializa a configuração do driver SPI do RC522
    .host_id = SPI3_HOST, // Define o host SPI a ser usado
    .bus_config = &(spi_bus_config_t){ // Configurações do bus SPI
        .miso_io_num = RC522_SPI_BUS_GPIO_MISO, // Atribui o pino MISO
        .mosi_io_num = RC522_SPI_BUS_GPIO_MOSI, // Atribui o pino MOSI
        .sclk_io_num = RC522_SPI_BUS_GPIO_SCLK, // Atribui o pino SCLK
    },
    .dev_config = { // Configurações do dispositivo SPI
        .spics_io_num = RC522_SPI_SCANNER_GPIO_SDA, // Atribui o pino CS (Chip Select)
    },
    .rst_io_num = RC522_SCANNER_GPIO_RST, // Atribui o pino RST (Reset)
};

static rc522_driver_handle_t driver; // Declaração estática do handle do driver RC522
static rc522_handle_t scanner; // Declaração estática do handle do scanner RC522

// Função de callback para mudanças no estado do PICC
static void on_picc_state_changed(void *arg, esp_event_base_t base, int32_t event_id, void *data)
{
    rc522_picc_state_changed_event_t *event = (rc522_picc_state_changed_event_t *)data; // Converte dados do evento para a estrutura apropriada
    rc522_picc_t *picc = event->picc; // Obtém o PICC do evento

    if (picc->state == RC522_PICC_STATE_ACTIVE) { // Verifica se o estado do PICC está ativo
        rc522_picc_print(picc); // Imprime informações do PICC ativo
    }
    else if (picc->state == RC522_PICC_STATE_IDLE && event->old_state >= RC522_PICC_STATE_ACTIVE) { // Verifica se o PICC está inativo após estar ativo
        ESP_LOGI(TAG, "Cartão Removido!"); // Loga a remoção do cartão
    }
}



void app_main(void)     // Função principal
{
     
    rc522_spi_create(&driver_config, &driver); // Cria a instância SPI para o RC522         //rc522_spi_create cria uma instância do driver SPI para o RC522 com a configuração definida
    if (rc522_driver_install(driver) != ESP_OK) { // Instala o driver e verifica se foi bem-sucedido
        ESP_LOGE(TAG, "Falha ao instalar o driver RC522"); // Loga erro se a instalação falhar
        return; // Sai da função se houve falha na instalação
    }

    rc522_config_t scanner_config = {
        .driver = driver, // Associa o driver criado à configuração do scanner
    };

    rc522_create(&scanner_config, &scanner); // Cria a instância do scanner RC522 com a configuração definida
    rc522_register_events(scanner, RC522_EVENT_PICC_STATE_CHANGED, on_picc_state_changed, NULL); // Registra o callback para eventos de mudança de estado do PICC
    rc522_start(scanner); // Inicia o scanner RC522
}
