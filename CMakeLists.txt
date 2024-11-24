idf_component_register(
    SRCS "mqtt-V01.c" "RFID_V01.c"
    INCLUDE_DIRS "."
    REQUIRES rc522
             esp_netif 
             esp_wifi
             esp_http_server
             nvs_flash
             
)