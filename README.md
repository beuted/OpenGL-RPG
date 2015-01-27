OpenGL-RPG (C++): 2013
======================

RPG created using C++ with openGL for a open 3D course in ENSIMAG.
This project meant to introduce to the basics of OpenGL and what could be done with it
(skybox, textures, light rendering, shadows, particles, animation structures, ...) 
But this is far from being a finished project...

To Play
-------

- Z Q S D    : moving
- espace     : jump
- A          : change point of view
- right clic : fire an energie bolt
- P          : screenshot
- escape     : quit

(you can change the field of view by changing the last number in the constructor of "carte" in game_engine.cpp)

Interesting Points
------------------

- Game architecture with different engines (game, graphical, ...)
- Physical engine with gravity, collisions, possibility to jump
- Transparency for water
- Really basic shadow rendering
- Ability to change point of view (first person, thrid person, reverted third person)
- Particle rendering when fireing "fireballs"
- Randomly generated map
- Ability for the player to destroy the map firing "fireballs"

Known Bugs
----------

- water transparency doesn't work anymore (broke it fixing textures)
- texture on the character should be changed (unless it become a concept)
- strange colors bug on the shadow zones ...
