#pragma once
#include "mbed.h"

class NewHavenDisplay
{
private:
    typedef enum
    {
        SetCursorPosition = 0x45,
        ClearScreen = 0x51,
        ReservedPrefix = 0xFE,
    } Commands;

    Serial *_PORT;
    int _baudPort;

    void sendCommand(uint8_t);
    void sendCommandWP(uint8_t, uint8_t); //with parameter

public:
    NewHavenDisplay(PinName uartTX, PinName uartRX, int uartBaud);
    ~NewHavenDisplay();

    void printf(const char *format, ...);
    void clear();
    void setCursor(uint8_t, uint8_t);
};

NewHavenDisplay::NewHavenDisplay(PinName uartTX, PinName uartRX, int uartBaud)
{
    _baudPort = uartBaud;
    _PORT = new Serial(uartTX, uartRX, _baudPort);
}

NewHavenDisplay::~NewHavenDisplay()
{
}

void NewHavenDisplay::printf(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    va_end(arg);
    _PORT->vprintf(format, arg);
    return;
}

void NewHavenDisplay::clear()
{
    sendCommand(ClearScreen);
    this->setCursor(1, 1);
    return;
}

void NewHavenDisplay::setCursor(uint8_t rows, uint8_t columns)
{
    uint8_t position = 0;
    switch (rows)
    {
    case 1:
        position += 0x00;
        break;
    case 2:
        position += 0x40;
        break;
    case 3:
        position += 0x14;
        break;
    case 4:
        position += 0x54;
        break;
    default:
        position = 0;
        break;
    }
    position += (columns - 1);
    sendCommandWP(SetCursorPosition, position);
    return;
}

void NewHavenDisplay::sendCommand(uint8_t command)
{
    _PORT->putc(ReservedPrefix);
    _PORT->putc(command);
    return;
}

void NewHavenDisplay::sendCommandWP(uint8_t command, uint8_t param)
{
    _PORT->putc(ReservedPrefix);
    _PORT->putc(command);
    _PORT->putc(param);
    return;
}
