# NVS Quick Reference
Professional Product Documentation
Component: NVS (Non-Volatile Storage)
Platform: ESP32, ESP-IDF
Function: Stores key-value pairs in flash memory for persistent data.

**1. Core Concepts** 

Key-Value Pairs: Data is saved using a key (a short string) to identify a value (e.g., a number, string, or blob).

Namespaces: Keys are grouped into namespaces, which act like folders to keep your data organized (e.g., wifi_creds, sensor_data).

**2. Basic Steps**

Step 1: Initialize
Must be called once at the start of your program.

Code: nvs_init_storage()

Purpose: Prepares the NVS flash partition.

Step 2: Write Data
To save a value:

Open: nvs_open() with the namespace and NVS_READWRITE mode.

Set: Use a nvs_set_... function (e.g., nvs_set_str(), nvs_set_i32()).

Close: nvs_close().

Step 3: Read Data
To retrieve a value:

Open: nvs_open() with the namespace and NVS_READONLY mode.

Get: Use a nvs_get_... function (e.g., nvs_get_str(), nvs_get_i32()).

Close: nvs_close().