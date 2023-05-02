#include "mbed.h"
#include "TextLCD.h"
#include "drivers/DigitalOut.h"

#include "erpc_simple_server.hpp"
#include "erpc_basic_codec.hpp"
#include "erpc_crc16.hpp"
#include "UARTTransport.h"
#include "DynamicMessageBufferFactory.h"
#include "blink_led_server.h"

mbed::DigitalOut led1(LED1, 1);
mbed::DigitalOut led2(LED2, 1);
mbed::DigitalOut led3(LED3, 1);
mbed::DigitalOut* leds[] = { &led1, &led2, &led3 };

I2C i2c_lcd(D14, D15); // SDA, SCL
//TextLCD_SPI lcd(&spi_lcd, p8, TextLCD::LCD40x4);   // SPI bus, 74595 expander, CS pin, LCD Type
TextLCD_I2C lcd(&i2c_lcd, 0x4E, TextLCD::LCD16x2);   // I2C bus, PCF8574 Slaveaddress, LCD Type
                                                     //TextLCD_I2C lcd(&i2c_lcd, 0x42, TextLCD::LCD16x2, TextLCD::WS0010);
                                                     // I2C bus, PCF8574 Slaveaddress, LCD Type, Device Type
                                                     //TextLCD_SPI_N lcd(&spi_lcd, p8, p9);
                                                     // SPI bus, CS pin, RS pin, LCDType=LCD16x2, BL=NC, LCDTCtrl=ST7032_3V3
//TextLCD_I2C_N lcd(&i2c_lcd, ST7032_SA, TextLCD::LCD16x2, NC, TextLCD::ST7032_3V3);
// I2C bus, Slaveaddress, LCD Type, BL=NC, LCDTCtrl=ST7032_3V3

/****** erpc declarations *******/

void led_on(uint8_t led) {
  if(0 < led && led <= 3) {
          *leds[led - 1] = 0;
        printf("LED %d is On.\n", led);
  }
}

void led_off(uint8_t led) {
  if(0 < led && led <= 3) {
          *leds[led - 1] = 1;
  printf("LED %d is Off.\n", led);
  }
}

void locate(int32_t column, int32_t row) {
    lcd.cls();
    lcd.locate(column, row);
}

void Putc(int32_t c) {
    lcd.putc(static_cast<char>(c));
}

/** erpc infrastructure */
ep::UARTTransport uart_transport(D1, D0, 9600);
ep::DynamicMessageBufferFactory dynamic_mbf;
erpc::BasicCodecFactory basic_cf;
erpc::Crc16 crc16;
erpc::SimpleServer rpc_server;

/** LED service */
LEDBlinkService_service led_service;

int main(void) {

  // Initialize the rpc server
  uart_transport.setCrc16(&crc16);

  printf("Initializing server.\n");
  rpc_server.setTransport(&uart_transport);
  rpc_server.setCodecFactory(&basic_cf);
  rpc_server.setMessageBufferFactory(&dynamic_mbf);

  // Add the led service to the server
  printf("Adding LED server.\n");
  rpc_server.addService(&led_service);

  // Run the server. This should never exit
  printf("Running server.\n");
  rpc_server.run();
}
