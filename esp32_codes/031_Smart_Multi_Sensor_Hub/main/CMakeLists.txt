idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_system_debug menu_config my_nvs_storage 
                    )
