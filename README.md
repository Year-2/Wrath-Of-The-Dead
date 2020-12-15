# CMP5327-CPP-Programming-for-Games

## Wrath Of The Dead
 A 2D zombie shooter where the player has to protect the well in the middle of the screen, failure to do so will result in a loss of health. The player must kill zombies and collect power ups in order to survive. Players will battle for the top spot on the leaderboards. 

#### Features:
- Shooting
- Enemies
- UI
- Sound

#### Unique Mechanics:  
- Teleportation ( Costs score but allows the player to flee)
- Crates ( Drop rewards such as: score, weapon upgrade)

#### Libraries: 
- SDL2-2.0.12 
- SDL2_image-2.0.5
- SDL2_ttf-2.0.15
- SDL2_mixer-2.0.4

### Initial commit - 27/08/2020 
Repositry created in preperation for assignment. 

### Initial push - 3/10/2020
Initial push with a main file. SDL2, SDL2_image, SDL_ttf and SDL_mixer linked. Folder structure changed along with build output directories changed. Gameloop created with updates capped at 60 times per second. Main menu, hiscores, and gameplay screen added with basic input to test menu changing. 

### Sound, Image, Texture - 4/10/2020
Static Texture, Sound and Font managers classes added for loading and drawing/playing.

### File parser - 8/10/2020
Simple file parser created for hiscores. Reads a file line by line while inputing the line contents into a player score dynamic array.

### Improved input - 9/10/2020 
Improved input. SDLK was used for basic input which has its issues, for gameplay SDLK will cause delay on keys being held down. A keycode array has been implemented for better control over the game objects the player controls.

### Custom datatpyes - 10/10/2020 
Custom data types for Fonts, Textures and Sounds. This will streamline quickly creating game assets which hold all the data they need to draw to the screen.

### Buttons, Tilemap, Memory leaks - 16/10/2020
Buttons added to the main menu for simple navigation. Tilemap renderering to test the ideal tilesize for gameplay. All memory leaks were located and patched. Memory debugging techniques implented.

### Buttons, Menu UI and Custom Textures -  18/10/2020
Button code refactored, Buttonmanager is now responsible for all button input and textures. Main menu UI prototype implemented. Custom Texture datatype now supports image splicing and lossless upscaling.  

### Initial Performance Statistics
During gameplay -  
- 61MB of memory.  
- 60 UPS. (Updates per second)
- 2800~ FPS. (Frames per second) 

![Top Functions](./imgs/top-functions.jpg?raw=true "Top Functions")

