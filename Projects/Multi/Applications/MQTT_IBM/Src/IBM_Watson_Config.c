 /**
  ******************************************************************************
  * @file    IBM_Watson_Config.c
  * @author  Central LAB
  * @version V1.1.0
  * @date    07-July-2016
  * @brief   Configuration file for connection with IBM Watson IOT Platform service
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  * 
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "IBM_Watson_Config.h"



/** @addtogroup GreenSys IoT-Kit v1.0
  * @{
  */

/**
  * @brief  Compose URL for Quickstart visualization of sensors data
  * @param  url_ibm : output buffer containing the URL for data visualization
  * @param  macadd : buffer containing MAC address
  * @retval None
  */
 void Compose_Quickstart_URL ( uint8_t *url_ibm, uint8_t *macadd ) 
{
  strcpy((char *)url_ibm,"18.212.126.128"); // url is given here
  return;
}
/**
  * @brief  Configure MQTT parameters according to QUICKSTART/REGISTERED mode. REGISTERED mode requires custom information and a IBM Watson IOT account
  * @param  mqtt_ibm_setup : handler of parameters for connection with IBM MQTT broker; 
  *         macadd : mac address of Wi-Fi
  * @param macadd MAC address  
  * @retval None
  */
void Config_MQTT_IBM ( MQTT_vars *mqtt_ibm_setup,  uint8_t *macadd ) 
{
    mqtt_ibm_setup->ibm_mode = UnionNFCToken.configParams.ibm_mode;

    /* Quickstart visualization */  
    if (UnionNFCToken.configParams.ibm_mode == QUICKSTART)
    {
        strcpy((char*)mqtt_ibm_setup->pub_topic, "mqttTopic");  //iot-2/evt/status/fmt/json //edited by basha
        strcpy((char*)mqtt_ibm_setup->sub_topic, "mqttTopic");  
        strcpy((char*)mqtt_ibm_setup->clientid,(char const*)UnionNFCToken.configParams.clientid);
        mqtt_ibm_setup->qos = QOS2;     //2 QoS0
        strcpy((char*)mqtt_ibm_setup->username,(char const*)UnionNFCToken.configParams.username);
        strcpy((char*)mqtt_ibm_setup->password,(char const*)UnionNFCToken.configParams.password);  
        strcpy((char*)mqtt_ibm_setup->hostname,"18.212.126.128"); //quickstart.messaging.internetofthings.ibmcloud.com  //edited basha
        mqtt_ibm_setup->port = 1883; //TLS          // 8883
        mqtt_ibm_setup->protocol = 't'; // TLS no certificates  //s
     }
    else if (UnionNFCToken.configParams.ibm_mode == REGISTERED)
    {     
        strcpy((char*)mqtt_ibm_setup->pub_topic, "mqttTopic");
        strcpy((char*)mqtt_ibm_setup->sub_topic, "mqttTopic");   //iot-2/cmd/+/fmt/string      
        mqtt_ibm_setup->qos = UnionNFCToken.configParams.qos; 
        strcpy((char*)mqtt_ibm_setup->username, (char const*)UnionNFCToken.configParams.username); 
        strcpy((char*)mqtt_ibm_setup->password, (char const*)UnionNFCToken.configParams.password);
        strcpy((char*)mqtt_ibm_setup->hostname, (char const*)UnionNFCToken.configParams.hostname);
        strcpy((char *)mqtt_ibm_setup->clientid,(char const*)UnionNFCToken.configParams.clientid);
        mqtt_ibm_setup->port = 1883; //TLS   8883
        mqtt_ibm_setup->protocol = 't'; // TLS no certificates  //s
    }

    return;
}

/**
 * @}
 */
