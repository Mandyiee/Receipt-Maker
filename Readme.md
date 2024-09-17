# Receipt Maker

## Overview

After completing a previous project involving text rendering onto images, I decided to extend that functionality by developing a program to generate **receipts**. This project overlays customer information, transaction details, and itemized lists onto a receipt template image, saving the final product as a PNG file.

This program created this image 
![A Receipt](https://raw.githubusercontent.com/Mandyiee/Receipt-Maker/main/image/new.png)


## Dependencies

This project uses the following resources:
- **Image class**: Handles image manipulation and writing.
- **Font class**: For rendering custom fonts (in this case, OpenSans).
- **Receipt class**: Manages receipt details, including customer info, itemized lists, and total price.
- **C++ Standard Libraries**: Used for string manipulation, file handling, and formatting.

## How It Works

### 1. **Image and Font Initialization**
   - The receipt background is loaded from `image/green.png`.
   - The font `OpenSans.ttf` is loaded, with an initial size of 25px for standard text rendering.

### 2. **Adding Customer Information**
   - Customer details (name, phone, and address) are overlaid onto the receipt in specific positions .

### 3. **Adding Date**
   - The current date is retrieved and overlaid on the receipt image.

### 4. **Itemized List**
   - A loop iterates over the items in the receipt. Each item's name, price, and total price are rendered line by line in the appropriate sections of the receipt.
   - The y-axis is dynamically updated to ensure that items are spaced correctly.

### 5. **Adding Total Price**
   - After rendering the list of items, the total price is calculated and added at the bottom of the receipt in a larger font size (40px).

### 6. **Saving the Final Image**
   - The program writes the final output image (`new.png`) to the `image/` directory. It confirms whether the operation was successful or not.

## How to Run

1. **Set Up the Environment**:
   - Ensure you have the required libraries and fonts in place. Place the font file (`OpenSans.ttf`) in the project directory.
   - The receipt template image (`green.png`) should be located in the `image/` folder.

2. **Compile and Run**:
   Use a C++ compiler (e.g., `g++`) to compile the program:
   
   ```bash
  make
 ./program
   ```

3. **Check the Output**:
   - After running the program, the receipt will be saved as `new.png` in the `image/` folder.
   - You can open and view the generated receipt image.


---

This project lays the foundation for a practical receipt generation tool, with ample room for adding more features and enhancing its usability.
