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

void HudClass::drawHud(SDL_Surface* const screen, const IOManager& io, int seconds, int fps) const{

    const Uint32 color = SDL_MapRGB(screen->format, rgbVal.red, rgbVal.blue, rgbVal.green);
    Draw_AALine(screen, xPos, yPos+hudHeight/2, xPos+hudWidth, yPos+hudHeight/2, hudHeight, 0, 0, 0, 0xff/2);
    io.printMessageAt("Press:", xPos+5, yPos+5);
    io.printMessageAt("A -> LEFT   D-> RIGHT   ", xPos+10, yPos+30);
    io.printMessageAt("W -> UP     S -> DOWN   ", xPos+10, yPos+52);
    io.printMessageAt("K -> BOOST  HEALTH    ", xPos+10, yPos+72);
    io.printMessageAt("Z -> Increase Speed",xPos+10, yPos+92);
    io.printMessageAt("X -> Decrease Speed",xPos+10, yPos+112); 
    io.printMessageAt("F1-> For Help F4 -> to generate frames", xPos+10, yPos+138);
    io.printMessageValueAt("Seconds: ", seconds, xPos+10, yPos+160);
    io.printMessageValueAt("fps: ", fps, xPos+10, yPos+180);
    io.printMessageAt("N -> shoot  R-> reset" , xPos+10, yPos+200);
    io.printMessageAt("G -> God Mode ", xPos+10, yPos+220);
    io.printMessageAt("F2 -> Object Pool", xPos+10, yPos+240);
    Draw_AALine(screen, xPos, yPos, xPos + hudWidth, yPos, color);
    Draw_AALine(screen, xPos, yPos+hudHeight, xPos + hudWidth, yPos+hudHeight, color);
}

void HudClass::drawLose(SDL_Surface* const& screen, const IOManager& io ) const{
    
    const int HUD_W = 300;
    const int HUD_H = 100;
    int x = 300;
    int y = 200;
    const Uint32 color = SDL_MapRGB(screen->format, rgbVal.red, rgbVal.blue, rgbVal.green);
    Draw_AALine(screen, x, y+HUD_H/2, x+HUD_W, y+HUD_H/2, HUD_H, 0, 0, 0, 0xff/2);
    io.printMessageAt("Game Over", x+5, y+5);
    io.printMessageAt("You were attacked by ghost!", x+5, y+30);
    Draw_AALine(screen, x,y,x+HUD_W,y, color);
    Draw_AALine(screen, x,y+HUD_H,x+HUD_W,y+HUD_H, color);
    Draw_AALine(screen, x+HUD_W,y,x+HUD_W,y+HUD_H, color);
    Draw_AALine(screen, x,y,x,y+HUD_H, color);
}

void HudClass::drawWin(SDL_Surface* const& screen, const IOManager& io, int score ) const{
    
    const int HUD_W = 300;
    const int HUD_H = 100;
    int x = 300;
    int y = 200;
    const Uint32 color = SDL_MapRGB(screen->format, rgbVal.red, rgbVal.blue, rgbVal.green);
    Draw_AALine(screen, x, y+HUD_H/2, x+HUD_W, y+HUD_H/2, HUD_H, 0, 0, 0, 0xff/2);
    io.printMessageAt("You Won!", x+5, y+5);
    io.printMessageValueAt("Your score is !", score, x+5, y+30);
    io.printMessageAt("You reached home successfully!", x+5, y+60);
    Draw_AALine(screen, x,y,x+HUD_W,y, color);
    Draw_AALine(screen, x,y+HUD_H,x+HUD_W,y+HUD_H, color);
    Draw_AALine(screen, x+HUD_W,y,x+HUD_W,y+HUD_H, color);
    Draw_AALine(screen, x,y,x,y+HUD_H, color);
}

void HudClass::drawPoolHud(SDL_Surface* const screen, const IOManager& io, unsigned int bCount, unsigned int fCount) const{
    const int HUD_W = 120;
    const int HUD_H = 70;
    int x = 30;
    int y = 70;
    const Uint32 color = SDL_MapRGB(screen->format, rgbVal.red, rgbVal.blue, rgbVal.green);
    Draw_AALine(screen, x, y+HUD_H/2, x+HUD_W, y+HUD_H/2, HUD_H, 0, 0, 0, 0xff/2);
    io.printMessageValueAt("Bullet List: ", bCount, x+10, y+20);
    io.printMessageValueAt("Free List: ", fCount, x+10, y+40);
    
    Draw_AALine(screen, x,y,x+HUD_W,y, color);
    Draw_AALine(screen, x,y+HUD_H,x+HUD_W,y+HUD_H, color);
}