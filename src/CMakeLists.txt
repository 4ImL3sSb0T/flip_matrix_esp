file(GLOB_RECURSE SRC_FILES "*.c")

idf_component_register(SRCS ${SRC_FILES}
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES driver esp_wifi nvs_flash esp_netif esp_event)
  