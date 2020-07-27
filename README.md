# pixify
This will generate a 3-bit RGB (actually 24-bit RGB though) pixel art for your pictures. It maintains its original resolution

Requires CMake (min. v3.0), SDL2, and SDL2_image in order to compile

Usage: `$ ./pixify <filename> [scale in (0,1) range]`

## Example Input
24-bit RGB, 1024x682 JPG image:
![input](https://github.com/michaelrk02/pixify/raw/master/docs/input.jpg)

## Example Output
Still 24-bit RGB, 1024x682 JPG image:
![output](https://github.com/michaelrk02/pixify/raw/master/docs/output.jpg)
