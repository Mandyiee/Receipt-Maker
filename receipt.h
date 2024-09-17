#include <stdint.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>    
#include <string>
#include <ctime>
#include "schrift.h"


enum ImageType
{
    PNG,
    JPG,
    BMP,
    TGA
};

struct Font;

struct Image
{
    uint8_t *data = NULL;
    size_t size = 0;
    int w;
    int h;
    int channels;

    Image(const char *filename);

    ~Image();

    bool read(const char *filename);
    bool write(const char *filename);

    ImageType getFileType(const char *filename);

    Image &overlayText(const char *txt, const Font &font, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    static void image_log(const char *message);
};

struct Font
{
    SFT sft = {NULL, 12, 12, 0, 0, SFT_DOWNWARD_Y | SFT_RENDER_IMAGE};

    Font(const char *fontfile, uint16_t size)
    {
        if ((sft.font = sft_loadfile(fontfile)) == NULL)
        {
            printf("\e[31m[ERROR] Failed to load\n");
            return;
        }
        setSize(size);
    }

    ~Font()
    {
        sft_freefont(sft.font);
    }

    void setSize(uint16_t size)
    {
        sft.xScale = size;
        sft.yScale = size;
    }
};

struct Customer
{
    std::string name;
    std::string phone;
    std::string address;

    Customer();
};

struct Item
{
    short id;
    std::string name;
    std::string price;
    std::string quantity;
    std::string totalPrice;

    Item(std::string name, short quantity, long price);

    std::string addCommas(int number);
    std::string addCommas(long number);
};



struct Receipt {
    Customer customer;
    Item items[6];
    int totalItems;
    static long mainPrice;
    std::string currentdate;
    

    Receipt();
    

    void addItems();
    void calculateTime();

    std::string getMainPrice();

};

