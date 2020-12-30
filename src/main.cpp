#include <iostream>
#include <vector>
#include <sstream>
#include "tclap/CmdLine.h"

#define cimg_use_png
#define cimg_display 0
#include "CImg.h"

std::string sat_name;
std::string date_time;
std::string misc_text = "Your text/signature here";

int offsetX, offsetY, bar_height;
unsigned int text_size;

//set ratios for calculating bar size
float bar_ratio = 0.02;
float text_ratio = 0.015;
float offsetXratio = 0.005;
float offsetYratio = 0.0025;


int main(int argc, char *argv[])
{
    //TClap stuff
    TCLAP::CmdLine cmd("Overlay by Zbychu", ' ', "1.0");

    // Define the arguments
    TCLAP::SwitchArg valueDepth("8", "8bit", "whether to use 8 bit depth", false);
    TCLAP::SwitchArg valueChannel("r", "RGB", "enables user to process RGB images", false);
    TCLAP::ValueArg<std::string> valueInput("i", "input", "input image", true, "", "in image");
    TCLAP::ValueArg<std::string> valueOutput("o", "output", "Output image file", true, "", "out image");

    cmd.add(valueInput);
    cmd.add(valueOutput);
    cmd.add(valueDepth);
    cmd.add(valueChannel);

    try
    {
        cmd.parse(argc, argv);
    }
    catch (TCLAP::ArgException &e)
    {
        std::cout << e.error() << '\n';
        return 0;
    }

    bool is8bit = valueDepth.getValue();
    bool rgb = valueChannel.getValue();

    std::string filename = valueInput.getValue();

    const size_t last_slash_idx = filename.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        filename.erase(0, last_slash_idx + 1);
    }

    std::stringstream instream(filename);
    std::string segment;
    std::vector<std::string> seglist;

    while (std::getline(instream, segment, '_'))
    {
        seglist.push_back(segment);
    }

    date_time = seglist[2].substr(6, 2) + '/' + seglist[2].substr(4, 2) + '/' + seglist[2].substr(0, 4) + ' ' + seglist[2].substr(9, 2) + ':' + seglist[2].substr(11,2)+" UTC";
    sat_name = seglist[0];
    if (seglist[0]=="EWS-G1")
    sat_name += "/GOES-13";
    sat_name += " | Band " + seglist[1];
    if (seglist[1]=="1" && (seglist[0]=="EWS-G1" || seglist[0]=="FY-2G" || seglist[0]=="FY-2H")) sat_name += " (VIS)";

    cimg_library::CImg<unsigned short> imgtext, imgtext1, imgtext2, inimage(valueInput.getValue().c_str());

    if(is8bit){
        cimg_library::CImg<unsigned char> imgtext, imgtext1, imgtext2, inimage(valueInput.getValue().c_str());
    }

    bar_height = inimage.width()*bar_ratio;
    text_size = inimage.width()*text_ratio;
    offsetX = inimage.width()*offsetXratio;
    offsetY = inimage.width()*offsetYratio;

    cimg_library::CImg<unsigned short> outimage(inimage.width(), inimage.height() + 2 * bar_height, 1, 3, 0);

    if(is8bit){
        cimg_library::CImg<unsigned char> outimage(inimage.width(), inimage.height() + 2 * bar_height, 1, 3, 0);
    }

    unsigned short color;
    if (is8bit)
    {
       color = 255;
    }
    else
    {
        color = 65535;
    }

    outimage.fill(0);
    imgtext.draw_text(0, 0, sat_name.c_str(), &color, 0, 1, cimg_library::CImgList<unsigned short>::font(text_size, false));
    imgtext1.draw_text(0, 0, date_time.c_str(), &color, 0, 1, cimg_library::CImgList<unsigned short>::font(text_size, false));
    imgtext2.draw_text(0, 0, misc_text.c_str(), &color, 0, 1, cimg_library::CImgList<unsigned short>::font(text_size, false));

    
    outimage.draw_image(offsetX, offsetY, 0, 0, imgtext);
    outimage.draw_image(outimage.width()-imgtext1.width()-offsetX, offsetY, 0, 0, imgtext1);
    outimage.draw_image(offsetX, bar_height+inimage.height()+offsetY, 0, 0, imgtext2);
    outimage.draw_image(0, bar_height, inimage);
    if (rgb)
    {
        outimage.draw_image(offsetX, offsetY, 0, 1, imgtext);
        outimage.draw_image(offsetX, offsetY, 0, 2, imgtext);
        
        outimage.draw_image(outimage.width() - imgtext1.width() - offsetX, offsetY, 0, 1, imgtext1);
        outimage.draw_image(outimage.width() - imgtext1.width() - offsetX, offsetY, 0, 2, imgtext1);
        
        outimage.draw_image(offsetX, bar_height + inimage.height() + offsetY, 0, 1, imgtext2);
        outimage.draw_image(offsetX, bar_height + inimage.height() + offsetY, 0, 2, imgtext2);

        outimage.save_png(valueOutput.getValue().c_str());
    }else{
        outimage.channel(0).save_png(valueOutput.getValue().c_str());
    }
    
}
    
