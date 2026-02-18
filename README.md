This project has been created as part of the 42 curriculum by vivaz-ca, jomunoz
# cub3d

### Description

Cub3D is a 3D graphical project that explores the foundations of Raycasting. Inspired by the world-famous 90s game Wolfenstein 3D, the goal is to create a dynamic first-person perspective view inside a maze.

The project serves as a deep dive into computer graphics, requiring the implementation of a mathematical engine that transforms a grid-based map into a pseudo-3D world in real-time. It involves rigorous data parsing of .cub configuration files, ensuring map integrity through validation algorithms (like flood-fill to check for closed walls), and managing window events using the MinilibX library. Key features implemented in this version include: 

    *Raycasting Engine: Real-time calculation of wall distances and perspective.

    *Interactive Minimap: A top-down view showing the player's position, field of vision (FOV), and enemy locations.

    *Collision Detection: Prevention of movement through walls.

    *Texture Mapping: Support for North, South, East, and West wall textures.

    *Sound System: Integrated background and "terror" music using process forking and signal management.


### Instalation
    In order to install and compile it's dependencies, you will have to have git installed on your machine. After that, you do
        make lib
        make          # For the mandatory version
        OR
        make extra    # For the version with extra features

    Execution
        To run the program, provide a map file with the .cub extension as an argument: ./cub3D maps/classic.cub

### Resources

    Lode's Raycasting Tutorial: The primary mathematical reference for the DDA (Digital Differential Analyzer) algorithm.
    MinilibX Documentation: For window management and pixel manipulation.
    Unix System Programming: References for fork(), waitpid(), and signal() used in the sound system.

    AI Usage
    AI was used in this project as a technical consultant for the following tasks:
        *Refactoring: Optimization of the vini_utils logic and the recursive get_map_with_style function.

        *Debugging: Identifying edge cases in the flood-fill algorithm used for map validation.

        *Boilerplate: Generating initial structures for RGB and texture path validation logic.

        *Optimization: Suggesting the use of ft_clamp and mathematical simplifications in the minimap ray rendering.

### Feature list
    Key [m] -> enable/disalbe minimap
    key [i] -> enable/disable information
    key [f] -> decreases player_fog
    key [l] -> increases player_fog
    key [ctl] -> run
    key [shift] -> slow walk
    key [z] -> decreases minimap zoom leve
    key [x] -> increases minimap zoom level
    key [r] -> restore to the default values
    key [t] -> activates/disactivate terror mode
    key [e] -> show/hide enemy on minimap
    key [caps lock] -> activates/disactivates mouse on screen
    keys [1] - [5] -> choosee which songs to play in normal mode
    key [6] -> stop all music (unless in terror mode, you can't run from that)
    
