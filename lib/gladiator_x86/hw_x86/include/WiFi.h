#ifndef _WIFI_X86_H_
#define _WIFI_X86_H_


#define ESP_NOW_ETH_ALEN             6         /*!< Length of ESPNOW peer MAC address */
#define ESP_NOW_KEY_LEN              16  
#define ESP_OK          0       /*!< esp_err_t value indicating success (no error) */
#define ESP_FAIL        -1
#include "Arduino.h"
#include <stdio.h>
#include <thread>
#include <vector>
#include <iostream>
#include <sio_client.h>
#include <sio_message.h>
#include "fct_utils.h"
#include "user_utils.h"
#include "base64.h"

typedef enum {
    ESP_NOW_SEND_SUCCESS = 0,       /**< Send ESPNOW data successfully */
    ESP_NOW_SEND_FAIL,              /**< Send ESPNOW data fail */
} esp_now_send_status_t;


typedef void (*esp_now_recv_cb_t)(const uint8_t *mac_addr, const uint8_t *data, int data_len);
typedef void (*esp_now_send_cb_t)(const uint8_t *mac_addr, esp_now_send_status_t status);




typedef enum {
    ESP_IF_WIFI_STA = 0,     /**< ESP32 station interface */
    ESP_IF_WIFI_AP,          /**< ESP32 soft-AP interface */
    ESP_IF_ETH,              /**< ESP32 ethernet interface */
    ESP_IF_MAX
} esp_interface_t;
typedef enum {
    WIFI_MODE_NULL = 0,  /**< null mode */
    WIFI_MODE_STA,       /**< WiFi station mode */
    WIFI_MODE_AP,        /**< WiFi soft-AP mode */
    WIFI_MODE_APSTA,     /**< WiFi station + soft-AP mode */
    WIFI_MODE_MAX
} wifi_mode_t;
#define WIFI_STA     WIFI_MODE_STA
typedef enum {
    WIFI_IF_STA = ESP_IF_WIFI_STA,
    WIFI_IF_AP  = ESP_IF_WIFI_AP,
} wifi_interface_t;
typedef int esp_err_t;
typedef struct esp_now_peer_info {
    uint8_t peer_addr[ESP_NOW_ETH_ALEN];    /**< ESPNOW peer MAC address that is also the MAC address of station or softap */
    uint8_t lmk[ESP_NOW_KEY_LEN];           /**< ESPNOW peer local master key that is used to encrypt data */
    uint8_t channel;                        /**< Wi-Fi channel that peer uses to send/receive ESPNOW data. If the value is 0,
                                                 use the current channel which station or softap is on. Otherwise, it must be
                                                 set as the channel that station or softap is on. */
    wifi_interface_t ifidx;                 /**< Wi-Fi interface that peer uses to send/receive ESPNOW data */
    bool encrypt;                           /**< ESPNOW data that this peer sends/receives is encrypted or not */
    void *priv;                             /**< ESPNOW peer private data */
} esp_now_peer_info_t;

bool esp_now_is_peer_exist(const uint8_t *peer_addr);
esp_err_t esp_now_del_peer(const uint8_t *peer_addr);
esp_err_t esp_now_init(void);
esp_err_t esp_now_add_peer(const esp_now_peer_info_t *peer);
esp_err_t esp_now_send(const uint8_t *peer_addr, const uint8_t *data, size_t len);
esp_err_t esp_now_register_send_cb(esp_now_send_cb_t cb);
esp_err_t esp_now_register_recv_cb(esp_now_recv_cb_t cb);

class WiFiClass {
    public:
        WiFiClass();
        void mode(int mode);
        String macAddress();
        void bindEvents();
        void setup(RobotData data);
        
    private:
        sio::client antennaClient;
        sio::socket::ptr antennaClienttSocket;

        sio::client falconClient;
        sio::socket::ptr falconClienttSocket;
        
        int lastSentReq = 0;
        String mac;
        uint8_t id;
        std::string genAddress();
        uint8_t genId ();
        bool initialized = false;
        
};
extern WiFiClass WiFi;
#endif