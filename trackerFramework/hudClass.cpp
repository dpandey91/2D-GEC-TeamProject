#include "hudClass.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "aaline.h"

HudClass& HudClass::getInstance(){
    static HudClass instance;
    return instance;
}

HudClass::HudClass():
    hudWidth(Gamedata::getInstance().getXmlInt("hudBar/width")),
    hudHeight(Gamedata::getInstance().getXmlInt("hudBar/height")),
    xPos(Gamedata::getInstance().getXmlInt("hudBar/startLoc/x")),
    yPos(Gamedata::getInstance().getXmlInt("hudBar/startLoc/y")),
    rgbVal(Gamedata::getInstance().getXmlInt("hudBar/color/red"),
           Gamedata::getInstance().getXmlInt("hudBar/color/blue"),
           Gamedata::getInstance().getXmlInt("hudBar/color/green"))
{}

HudClass::~HudClass()
{}

void HudClass::drawHud(SDL_Surface* const screen, const IOManager& io, int seconds, int fps, int health) const{

    const Uint32 color = SDL_MapRGB(screen->format, rgbVal.red, rgbVal.blue, rgbVal.green);
    Draw_AALine(screen, xPos, yPos+hudHeight/2, xPos+hudWidth, yPos+hudHeight/2, hudHeight, 0, 0, 0, 0xff/2);
    io.printMessageAt("Press:", xPos+5, yPos+5);
    io.printMessageAt("W -> UP     S -> DOWN   V->SMASH", xPos+5, yPos+30);
    io.printMessageAt("A -> LEFT   D -> RIGHT  SPACE->SPLICE", xPos+5, yPos+55);
    io.printMessageAt("G->GOD MODE", xPos+25, yPos+80);
    io.printMessageAt("F1-> To read Help", xPos+10, yPos+105);
    io.printMessageValueAt("Seconds: ", seconds, xPos+10, yPos+135);
    io.printMessageValueAt("fps: ", fps, xPos+10, yPos+160);
    io.printMessageValueAt("Health: ", health, xPos+250, yPos+160);
    Draw_AALine(screen, xPos, yPos, xPos + hudWidth, yPos, color);
    //Draw_AALine(screen, xPos, yPos, xPos, yPos+hudHeight, color);
    //Draw_AALine(screen, xPos + hudWidth, yPos, xPos + hudWidth, yPos+hudHeight, color);
    Draw_AALine(screen, xPos, yPos+hudHeight, xPos + hudWidth, yPos+hudHeight, color);
}