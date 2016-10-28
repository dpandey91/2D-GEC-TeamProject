# 2D-GEC
Student Name: Sapna Gandhi
Student User Name- sapnapg
Project Partner:Dipika Pandey
Project Partner User Name- dpandey
Game Name:Escape the Graveyard


Sapna’s individual Efforts:

Implementation of HUD:
1)Implemented the HUD for project which is displayed first when the game starts and it goes after some seconds which is specified in xml.
2)The HUD toggles on pressing key F1 and displays information for player.
3)The specification of HUD is flexible and its parameters can be set using xml.
4)The HUD class is singleton as we’ll be showing only one HUD throughout the game.

Common Efforts by both Partners:
1)Together, we have  implemented the painter’s algorithm. The frames created for scaled sprites are shallow copy. The number of actual frames created is defined by actual attribute of noOfObjects tag signifying different scales based on min and max scale and then its shallow copy is created for each instances. This leads in efficient implementation i.e. with increase in number of instances to be created will not impact the efficiency of code.

2)We have also implemented the health meter for player whose specifications are fetched using xml. The health of the player will keep decreasing if the player moves and will reach to zero gradually and thus the player will stop moving. You can press key K to boost player’s health so that it can move again. The health class is singleton as there is only one health bar.


Game Description:

As Halloween festival is approaching, we are planning to make Halloween theme based game in which one boy lost his way while going home and he has encountered some ghosts/skeletons (we are planning to put the ghost in the next assignment). Furthermore, he also gets terrified with flying Halloween Pumpkin (satisfies the painter’s algorithm-depth effect). To get scores and win the game,the player has to hide/save himself from the ghosts/skeletons and kill them for getting points. If some ghosts (defined by xml) are killed by the player, a next level of the game will begin in which ghosts will have power to shoot and the player has to save himself of being attacked and shoot the ghosts. The player will get scores as per the number of ghosts/skeletons killed. The game will end if the boy successfully reaches his home after surpassing or killing all the ghosts.

Effects: 

For creating Painter’s Algorithm effect: To design parallax scrolling at more depth, we have added flying pumpkin which will be flying across the sky and graveyard. Pumpkin closer to pathway will be flying at faster rate than the pumpkin who are far away.

Note:We have used four layers for parallax scrolling. Also, we have created one sprite  by ourselves  (layer4.png) as per our Project requirement.

References:

1)http://www.clipartkid.com/graveyard-cliparts/ ………….For Graveyard
2)https://www.behance.net/gallery/32271557/Button-Boy- …. for the boy object
3)http://www.clipartqueen.com/halloween-clip-art.html…. For Halloween Pumpkin
4)http://www.clipartkid.com/full-moon-transparent-cliparts/…. for Moon image
5)http://instantsprite.com/… for making spritesheet
6)http://ezgif.com/ …for frame extraction from Gif






