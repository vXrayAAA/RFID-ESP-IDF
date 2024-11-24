# RFID-ESP-IDF
Firmware do Projeto


# Leitor RFID RC522 com ESP32

Este projeto demonstra como integrar o módulo RFID RC522 com o ESP32 para ler tags RFID. Quando uma tag é detectada, as informações são impressas no console, e uma mensagem é exibida quando a tag é removida.

---

## Funcionalidades
- Inicialização e configuração do módulo RC522 via SPI.
- Detecção de estado das tags (PICC).
- Impressão das informações da tag quando ativada.
- Notificação no console quando a tag é removida.

---

## Hardware Necessário
- **ESP32**
- **Módulo RFID RC522**
- **Cabos jumper para conexões**

---

## Pinagem
Conexões entre o ESP32 e o RC522:

| **RC522 Pin** | **ESP32 GPIO** |
|---------------|----------------|
| SDA (CS)      | GPIO 22        |
| SCK           | GPIO 19        |
| MOSI          | GPIO 23        |
| MISO          | GPIO 25        |
| IRQ           | Não conectado  |
| GND           | GND            |
| RST           | Não conectado (-1 no código) |
| 3.3V          | 3.3V           |

---

## Como Utilizar

1. **Conecte o RC522 ao ESP32** conforme a pinagem descrita acima.
2. **Clone este repositório** ou copie o código fonte para o seu ambiente de desenvolvimento.
3. Certifique-se de ter o **ambiente ESP-IDF configurado**.
4. Flash e abra o monitor serial para visualizar as saídas:
 

   ```bash
    idf.py -p (PORTA COM) flash monitor
  




## Dependências
- ESP-IDF instalado e configurado.
- Bibliotecas do RC522 incluídas no projeto.


