#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define BYTE_BOUND(value) value < 0 ? 0 : (value > 255 ? 255 : value)
#include "receipt.h"
#include "stb_image.h"
#include "stb_image_write.h"

#define MAX 690000
#define PRO 540000
#define MINI 320000

#define DELIVER 10000


Image::Image(const char* filename)
{
    Image::image_log("Proceeding to read image \n");

    if (!read(filename))
    {
        Image::image_log("Image could not be read \n");
    }
    else
    {
        Image::image_log("Image was read \n");
        size = w * h * channels;
        printf("Height: %d, Width: %d, Channels: %d, Size: %ld \n", h, w, channels,size);
    }
    
}

Image::~Image()
{
    stbi_image_free(data);
}

void Image::image_log(const char *message)
{
    printf("Message: %s \n",message);
}

ImageType Image::getFileType(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if(ext != nullptr) {
        if(strcmp(ext, ".png") == 0) {
            return PNG;
        }
        else if(strcmp(ext, ".jpg") == 0) {
            return JPG;
        }
        else if(strcmp(ext, ".bmp") == 0) {
            return BMP;
        }
        else if(strcmp(ext, ".tga") == 0) {
            return TGA;
        }
    }
            return PNG;
}

Image &Image::overlayText(const char *txt, const Font &font, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    size_t len = strlen(txt);
    SFT_Char c;
    int32_t dx, dy;
    uint8_t* dstPx;
    uint8_t srcPx;
    uint8_t color[4] = {r, g, b, a};

    for (size_t i = 0; i < len; i++)
    {
        if(sft_char(&font.sft, txt[i], &c) != 0) {
            printf("\e[31m[ERROR] Font is missing character '%c'\e[0m\n", txt[i]);
			continue;
        }

        for (uint16_t sy = 0; sy < c.height; sy++)
        {
            dy = sy + y + c.y;
            if (dy < 0) { continue; }
            else if(dy >= h){ break; }
            for (uint16_t sx = 0; sx < c.width; sx++)
            {
                dx = sx + x + c.x;
                if (dx < 0) { continue; }
                else if(dx >= w){ break; }

                dstPx = &data[(dy * w + dx) * channels];
                srcPx = c.image[sx + sy * c.width];

                if (srcPx != 0)
                {
                    float srcAlpha = (srcPx / 255.f) * (a / 255.f);
                    float dstAlpha = channels < 4 ? 1 : dstPx[3] / 255.f;

                    if(srcAlpha > .99 && dstAlpha > .99) {
                        memcpy(dstPx, color, channels);
                    }
                    else {
                        float outAlpha = srcAlpha + dstAlpha * (1 - srcAlpha);
                        if(outAlpha < .01) {
                            memset(dstPx, 0, channels);
                        } else {
                            for (int chnl = 0; chnl < channels; chnl++)
                            {
                                dstPx[chnl] = (uint8_t)BYTE_BOUND((color[chnl]/255.f * srcAlpha + dstPx[chnl]/255.f * dstAlpha * (1 - srcAlpha)) / outAlpha * 255.f);
                            }
                            if(channels > 3) { dstPx[3] = (uint8_t)BYTE_BOUND(outAlpha * 255.f); }
                        }
                    }

                }
                
            }
        }
        x += c.advance;
        free(c.image);
    }
    return *this;
}

bool Image::read(const char *filename)
{
    data = stbi_load(filename, &w, &h, &channels, 0);
    return data != NULL;
}

bool Image::write(const char *filename)
{
    ImageType type = getFileType(filename);
    int success;
    switch (type)
    {
    case PNG:
        success = stbi_write_png(filename, w, h, channels, data, w * channels);
        break;

    case BMP:
        success = stbi_write_bmp(filename, w, h, channels, data);
        break;

    case JPG:
        success = stbi_write_jpg(filename, w, h, channels, data, 100);
        break;

    case TGA:
        success = stbi_write_tga(filename, w, h, channels, data);
        break;

    }

    return success != 0;
}

Customer::Customer()
{
    std::cout << "What is the customer's name?" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, name);
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    std::cout << "What is the customer's phone number?" << std::endl;
    std::getline(std::cin, phone);
    phone.insert(0, "Phone: ");

    std::cout << "What is the customer's address?" << std::endl;
    std::getline(std::cin, address);
    address.insert(0, "Address: ");

   
}


Receipt::Receipt(): customer() , items{Item("", 0, 0), Item("", 0, 0), Item("", 0, 0), 
                      Item("", 0, 0), Item("", 0, 0), Item("", 0, 0)}
{
    addItems();
    calculateTime();
}
long Receipt::mainPrice = 0; 

void Receipt::addItems()
{
        std::cout << "Enter the items and their prices" << std::endl;
        std::cout << "Use this format: Item-Quantity-Price. Milk--2--30" << std::endl;
        char str[50];
        int quantity, price;
        int cont = 1, i = 0;

        do
        {
            if (totalItems >= 6) 
            {
                std::cout << " You have entered the maximum number of items" << std::endl;
                break;
            } else {
                std::cout << "Enter another input" << std::endl;
            }
            std::cin.ignore();
            scanf("%50[^-] -- %d -- %d", str, &quantity, &price);
            items[i] = Item(str, quantity, price);
            i++;
            totalItems = i;
            std::cout << "Do you want to enter another item. 0 for No and 1 for Yes" << std::endl;
            std::cin.ignore();
            std::cin >> cont;
        } while (cont);
        
        
    }

   

Item::Item(std::string name, short quantity, long price): name(name)
{
    int tp = quantity * price;
    this->price = "#" + addCommas(price);
    this->totalPrice = "#" + addCommas(tp);
    Receipt::mainPrice += tp;
}


std::string Item::addCommas(int number)
{
    return addCommas(static_cast<long>(number));
}

std::string Item::addCommas(long number)
{
    std::string numStr = std::to_string(number);
    int len = numStr.length();
    std::string result = "";

    int count = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        if (count == 3)
        {
            result.insert(0, 1, ',');
            count = 0;
        }
        result.insert(0, 1, numStr[i]);
        count++;
    }
    return result;
}

void Receipt::calculateTime()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);


    const char* months[] = {"January", "February", "March", "April", "May", "June", 
                            "July", "August", "September", "October", "November", "December"};

    currentdate = "DATE: " + std::string(months[tm.tm_mon]) + " " + std::to_string(tm.tm_mday) + ", " + std::to_string(tm.tm_year + 1900);
}

std::string Receipt::getMainPrice()
{
    std::string numStr = std::to_string(mainPrice);
    int len = numStr.length();
    std::string result = "";

    int count = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        if (count == 3)
        {
            result.insert(0, 1, ',');
            count = 0;
        }
        result.insert(0, 1, numStr[i]);
        count++;
    }
    return result;
}
