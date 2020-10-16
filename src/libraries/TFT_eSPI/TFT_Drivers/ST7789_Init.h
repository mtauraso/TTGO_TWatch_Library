
// This is the command sequence that initialises the ST7789 driver
//
// This setup information uses simple 8 bit SPI writecommand() and writedata() functions
//
// See ST7735_Setup.h file for an alternative format

{
  writecommand(ST7789_SLPOUT);   // Sleep out
  delay(120);

  writecommand(ST7789_NORON);    // Normal display mode on

  //------------------------------display and color format setting--------------------------------//
  writecommand(ST7789_MADCTL);
  //writedata(0x00);
  writedata(TFT_MAD_COLOR_ORDER);

  // JLX240 display datasheet
  writecommand(0xB6);
  writedata(0x0A);
  writedata(0x82);

  writecommand(ST7789_COLMOD);
  writedata(0x55);
  delay(10);

  //--------------------------------ST7789V Frame rate setting----------------------------------//
  writecommand(ST7789_PORCTRL);
  writedata(0x0c);
  writedata(0x0c);
  writedata(0x00);
  writedata(0x33);
  writedata(0x33);

  writecommand(ST7789_GCTRL);      // Voltages: VGH / VGL
  writedata(0x35);

  //---------------------------------ST7789V Power setting--------------------------------------//
  writecommand(ST7789_VCOMS);
  writedata(0x28);		// JLX240 display datasheet

  writecommand(ST7789_LCMCTRL);
  writedata(0x0C);

  writecommand(ST7789_VDVVRHEN);
  writedata(0x01);
  writedata(0xFF);

  writecommand(ST7789_VRHS);       // voltage VRHS
  writedata(0x10);

  writecommand(ST7789_VDVSET);
  writedata(0x20);

  writecommand(ST7789_FRCTR2);
  writedata(0x0f);

  writecommand(ST7789_PWCTRL1);
  writedata(0xa4);
  writedata(0xa1);

  //--------------------------------ST7789V gamma setting---------------------------------------//
  //#define ORIG_GAMMA
  #ifdef ORIG_GAMMA
  writecommand(ST7789_PVGAMCTRL);
  writedata(0xd0);
  writedata(0x00);
  writedata(0x02);
  writedata(0x07);
  writedata(0x0a);
  writedata(0x28);
  writedata(0x32);
  writedata(0x44);
  writedata(0x42);
  writedata(0x06);
  writedata(0x0e);
  writedata(0x12);
  writedata(0x14);
  writedata(0x17);

  writecommand(ST7789_NVGAMCTRL);
  writedata(0xd0);
  writedata(0x00);
  writedata(0x02);
  writedata(0x07);
  writedata(0x0a);
  writedata(0x28);
  writedata(0x31);
  writedata(0x54);
  writedata(0x47);
  writedata(0x0e);
  writedata(0x1c);
  writedata(0x17);
  writedata(0x1b);
  writedata(0x1e);
  #else

  writecommand(ST7789_PVGAMCTRL);
writedata(0xF8);
writedata(0x0A);
writedata(0x0E);
writedata(0x0E);
writedata(0x0E);
writedata(0x28);
writedata(0x36);
writedata(0x33);
writedata(0x53);
writedata(0x0E);
writedata(0x1C);
writedata(0x1A);
writedata(0x34);
writedata(0x38);

writecommand(ST7789_NVGAMCTRL);
writedata(0xF8);
writedata(0x0A);
writedata(0x0E);
writedata(0x0E);
writedata(0x0E);
writedata(0x28);
writedata(0x36);
writedata(0x33);
writedata(0x53);
writedata(0x0E);
writedata(0x1C);
writedata(0x1A);
writedata(0x34);
writedata(0x38);
#endif

#if 0
  writecommand(ST7789_PVGAMCTRL);
  writedata(0xD8);
  writedata(0x0A);
  writedata(0x0E);
  writedata(0x0E);
  writedata(0x0E);
  writedata(0x28);
  writedata(0x32);
  writedata(0x44);
  writedata(0x48);
  writedata(0x0E);
  writedata(0x1C);
  writedata(0x1A);
  writedata(0x24);
  writedata(0x28);

  writecommand(ST7789_NVGAMCTRL);
  writedata(0xD8);
  writedata(0x0A);
  writedata(0x0E);
  writedata(0x0E);
  writedata(0x0E);
  writedata(0x28);
  writedata(0x32);
  writedata(0x44);
  writedata(0x48);
  writedata(0x0E);
  writedata(0x1C);
  writedata(0x1A);
  writedata(0x24);
  writedata(0x28);
#endif


  writecommand(ST7789_DGMEN); // Digital gamma enable
  writedata(0x04); // on
  //writedata(0x0); // off

  writecommand(ST7789_DGMLUTR); // Digital Gamma lookup table for Red (64 entries)
  for (int i = 0; i < 64; i++) {
    float max_red_out = 63.0;
    float red_gamma_adjust = 1.0;
    int8_t red_gamma = round( pow(float(i)/63.0, red_gamma_adjust) * max_red_out);
    writedata(((red_gamma << 2) + 3) & 0xFF);
    //writedata(0x00);
  }

  writecommand(ST7789_DGMLUTB); // Digital Gamma lookup table for Blue (64 entries)
  for (int i = 0; i < 64; i++) {
    float max_blue_out = 56.0;
    float blue_gamma_adjust = 1.0;
    int8_t blue_gamma = round( pow(float(i)/63.0, blue_gamma_adjust) * max_blue_out);
    writedata(((blue_gamma << 2) + 3) & 0xFF);
  }
  

  writecommand(ST7789_GAMSET);
  writedata(0x01); // 2.2
  //writedata(0x02); // 1.8
  //writedata(0x03); // 2.5
  //writedata(0x04); // 1.0

  writecommand(ST7789_INVON);
  //writecommand(ST7789_INVOFF);

  writecommand(ST7789_CASET);    // Column address set
  writedata(0x00);
  writedata(0x00);
  writedata(0x00);
  writedata(0xE5);    // 239

  writecommand(ST7789_RASET);    // Row address set
  writedata(0x00);
  writedata(0x00);
  writedata(0x01);
  writedata(0x3F);    // 319

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  end_tft_write();
  delay(120);
  begin_tft_write();

  writecommand(ST7789_DISPON);    //Display on
  delay(120);

#ifdef TFT_BL
  // Turn on the back-light LED
  digitalWrite(TFT_BL, HIGH);
  pinMode(TFT_BL, OUTPUT);
#endif
}
