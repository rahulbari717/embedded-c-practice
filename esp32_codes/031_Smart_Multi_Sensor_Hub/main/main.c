#include <stdio.h>
#include "esp_debub.h"
#include "esp_config.h"

void app_main()
{
	ResetReason();
	menu_config();

	printf("Hello, World!\n");
}