#ifndef CONFIG_FLASH_H_
#define CONFIG_FLASH_H_

typedef struct{
	unsigned int version;

	char wifiSSID[64];
	char wifiPassword[64];
	char mqttHost[64];
	int mqttPort;
	int mqttKeepalive;
	char mqttUsername[64];
	char mqttPassword[64];
	int mqttVersion;
	unsigned int sta_type;
} configFlash_t;


typedef struct {
    char flag;
    char pad[3];
} configFlashSaveFlag_t;

configFlash_t configFlash;

void configFlashSave(void);
void configFlashLoad(void);
void configFlashInit(void);

#endif // CONFIG_FLASH_H_