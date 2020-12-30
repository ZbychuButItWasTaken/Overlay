# Overlay
Small program to put text on your sat images (or any images really)

## Usage
Using the program is really simple. It takes two arguments (in and out) and 2 optional flags (-8 -r). An example command would look like this:

`Overlay -i EWS-G1_5_20201121T084100Z.png -o EWS-G1_5_20201121T084100Z_overlay.png -8 -r`
It uses a specific file naming format, soon to be implememnted for EWS-G1 in https://github.com/altillimity/GVAR-Ingestor.

The format is:
`prefix_channel_yyyyMMddTHHmmssZ.png`, so for example `EWS-G1_5_20201121T084100Z.png` would mean Image from EWS-G1 taken on 08:41 UTC on 21/11/2020, Channel 5.

The flags enable user to use Overlay on 8 bit deep images and RGB images. when using the `-8` flag the program will assume in and out are 8 bits (if otherwise weird things can happen). The `-r` flag will set the program ro RGB mode, where input and output will be RGB (if in was not RGB it can result in weird things happening). If only `-r` flag is uesd, it will gererate 48bit image output.

For now editing the misc text (for example signature) is done in the code, by replacing the "Your text/signature here" with your desired text.

NOTE: By default the program accepts 16bit depth greyscale images.

## Instalation
### It requires [libpng](https://github.com/glennrp/libpng) and [zlib](https://github.com/madler/zlib)!
This program uses Cmake, so compiling would be done like this:

```
sudo apt-get install zlib1g-dev libpng-dev
mkdir build && cd build
cmake ..
make
sudo make install
```
## Example image from EWS-G1
![Example Image](/images/out2k.png)
