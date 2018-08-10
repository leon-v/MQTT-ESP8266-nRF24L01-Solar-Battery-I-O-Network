#ifndef CONFIG_FLASH_H_
#define CONFIG_FLASH_H_

typedef struct{
	unsigned int version;

	char wifiSSID[64];
	char wifiPassword[64];
	unsigned int sta_type;

	char mqtt_host[64];
	unsigned int mqtt_port;
	char mqtt_user[32];
	char mqtt_pass[32];
	unsigned int mqtt_keepalive;
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