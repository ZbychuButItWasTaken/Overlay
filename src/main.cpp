#include <iostream>
#include <vector>
#include <sstream>

#define cimg_use_png
#define cimg_display 0
#include "CImg.h"

std::string sat_name;
std::string date_time;
std::string misc_text = "Zbigniew Sztanga | station #01";

int offsetX, offsetY, bar_height;
unsigned int text_size;

float bar_ratio = 0.02;
float text_ratio = 0.015;
float offsetXratio = 0.005;
float offsetYratio = 0.0025;


int main(int argc, char *argv[])
{
    std::stringstream inpath(argv[1]);
    std::string pathsegment;
    std::vector<std::string> pathseglist;
    while (std::getline(inpath, pathsegment, '/'))
    {
        pathseglist.push_back(pathsegment);
    }

    std::string inname = pathseglist.back();
    std::stringstream instream(inname);
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
    if (seglist[1]=="5") sat_name += " (VIS)";

    cimg_library::CImg<unsigned short> imgtext,imgtext1, imgtext2, inimage(argv[1]);

    bar_height = inimage.width()*bar_ratio;
    text_size = inimage.width()*text_ratio;
    offsetX = inimage.width()*offsetXratio;
    offsetY = inimage.width()*offsetYratio;

    cimg_library::CImg<unsigned short> outimage(inimage.width(), inimage.height() + 2 * bar_height, 1, 1, 0);

    unsigned short color = 65535;
    outimage.fill(0);

    imgtext.draw_text(0,0,sat_name.c_str(),&color,0,1, cimg_library::CImgList<unsigned short>::font(text_size, false));
    outimage.draw_image(offsetX, offsetY, 0, 0, imgtext);

    imgtext1.draw_text(0,0,date_time.c_str(),&color,0,1, cimg_library::CImgList<unsigned short>::font(text_size, false));
    outimage.draw_image(outimage.width()-imgtext1.width()-offsetX, offsetY, 0, 0, imgtext1);

    imgtext2.draw_text(0, 0, misc_text.c_str(), &color, 0, 1, cimg_library::CImgList<unsigned short>::font(text_size, false));
    outimage.draw_image(offsetX, bar_height+inimage.height()+offsetY, 0, 0, imgtext2);

    outimage.draw_image(0, bar_height, inimage);
    outimage.save_png(argv[2]);
}