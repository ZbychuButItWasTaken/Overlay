# Overlay
Small program to put text on your sat images (or any images really)

## Usage
Using the program is really simple. It takes two arguments: in and out. An example command would look like this:

`Overlay EWS-G1_5_20201121T084100Z.png EWS-G1_5_20201121T084100Z_overlay.png`
It uses a specific file naming format, soon to be implememnted for EWS-G1 in https://github.com/altillimity/GVAR-Ingestor.

The format is:
`prefix_channel_yyyyMMddTHHmmssZ.png`, so for example `EWS-G1_5_20201121T084100Z.png` would mean Image from EWS-G1 taken on 08:41 UTC on 21/11/2020, Channel 5.

For now editing the misc text (for example sugnature) is done in the code, by replacing the "Your text/signature here" with your desired text.

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
