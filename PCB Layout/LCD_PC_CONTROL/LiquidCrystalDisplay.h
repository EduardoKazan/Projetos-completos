#ifndef LiquidCrystalDisplay_h
#define LiquidCrystalDisplay_h

class LiquidCrystalDisplay {
public:
    LiquidCrystalDisplay();
    void begin(unsigned char cols, unsigned char rows);
    void clear();
    void setCursor(unsigned char col, unsigned char row);
    void write(unsigned char data);
    void command(unsigned char cmd);
    void printNumber(int num, unsigned char row, unsigned char col);
    void printText(const char* text, unsigned char row, unsigned char col);

private:
    void sendNibble(unsigned char nibble, unsigned char isData);
    void pulseEnable();

    unsigned char _cols;
    unsigned char _rows;
};

#endif