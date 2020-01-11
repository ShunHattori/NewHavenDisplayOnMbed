#include <mbed.h>
#include "NewHavenDisplay.hpp"

#define TX PA_9
#define RX NC

NewHavenDisplay NHD(TX, RX, 9600);

int main()
{
  NHD.clear();
  wait_ms(10);
  //NHD.setCursor(4, 1);

  NHD.printf("ABCDEFJHI:%d :)", 1234567);
  NHD.setCursor(2, 1);
  NHD.printf("ABCDEFJHI:%d :)", 1234567);
  NHD.setCursor(3, 1);
  NHD.printf("ABCDEFJHI:%d :)", 1234567);
  NHD.setCursor(4, 1);
  NHD.printf("ABCDEFJHI:%d :)", 1234567);

  while (1)
  {
  }
}
