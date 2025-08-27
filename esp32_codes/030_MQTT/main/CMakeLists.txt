idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES my_mqtt wifi_connect sntp_time
                    )
