#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstring> 
#include "receipt.h" 



int main() {
    //temporal buffer
    char temp[30];

    // File paths
    const std::string imagePath = "image/green.png";
    const std::string outputImagePath = "image/new.png";

    // Initialize image and font objects
    Image r(imagePath.c_str());
    Font l("OpenSans-VariableFont_wdth,wght.ttf", 25);

    Receipt receipt;

    // Input customer's detail
    r.overlayText(receipt.customer.name.c_str(), l, 101, 620, 92, 154, 100, 255);
    r.overlayText(receipt.customer.phone.c_str(), l, 101, 660, 0, 0, 0, 230);
    r.overlayText(receipt.customer.address.c_str(), l, 101, 700, 0, 0, 0, 230);

    // Input curret date
    r.overlayText(receipt.currentdate.c_str(), l, 101, 490, 0, 0, 0, 230);

    int yPadding = 940;
    int spacing = 70;

    // Input items
    for (int i = 0; i < receipt.totalItems; i++)
        {
          r.overlayText(std::to_string((i + 1)).c_str(), l, 155, (yPadding + (spacing * i)), 0, 0, 0, 230);
           r.overlayText(receipt.items[i].name.c_str(), l, 270, (yPadding + (spacing * i)), 0, 0, 0, 230);
            r.overlayText(receipt.items[i].price.c_str(), l, 890, (yPadding + (spacing * i)), 0, 0, 0, 230);
            r.overlayText(receipt.items[i].totalPrice.c_str(), l, 1145, (yPadding + (spacing * i)), 0, 0, 0, 230); 
        }

    l.setSize(40);
    sprintf(temp, "Total:\t#%s",receipt.getMainPrice().c_str());
    r.overlayText(temp, l, 890, 1490, 0, 0, 0, 230);

    

    // Save the resulting image

    if (r.write(outputImagePath.c_str()))
    {
      printf("Image was written sucessfully \n");
    }
    else
    {
      printf("Image was not written sucessfully \n");
    }
    
    

    return 0;
}
