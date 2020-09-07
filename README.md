# cub3d
pseudo 3D game

open readme.md in editing mode

To run mandatory part: 'make && ./cub3D map.cub'

To run bonus part: 'make bonus && ./cub3D bonus/map.cub'

To make a screenshot: add '--save' to 2 previous commands

To modify the map: open map.cub or bonus/map.cub for bonus part

R - stands for window resolution (if greater than screen size -> reduces to screen size)
C - stands for ceiling color in RGB (for bonus part is substituted with sky box)
F - stands for floor color in RGB
NO - stands for north wall texture path. (You are free to modify it if you have xpm files or you can have the same texture at every wall)
SO - stands for south wall texture path.
WE - stands for west wall texture path.
EA - stands for east wall texture path.
S - stands for sprite texture path.
B - stands for another sprite texture path. (just for bonus map)

You are free to change the order of keys as long as there are no double keys or unsupported keys.
Keep in mind that map should always be the last in the config. file and the config file should always end with '.cub' extension (in case you want to make your own config file).

Map itself consists only of several possible symbols otherwise it will be consider invalid:

' ' - empty. space outside of the maze
0 - empty space within the walls
1 - walls
2 - sprite
3 - another sprite (for bonus part)
N - player position with spawning orientation to north
S - player position with spawning orientation to south
W - player position with spawning orientation to west
E - player position with spawning orientation to east

Note that map can't be divided with empty lines and walls must enclose player in the maze. If there is a hole in a wall map will be considered invalid

Example of a valid map: (remove 3 to get a valid map for mandatory part)

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000002000001
        1001003000000000000000001
111111111011000001110000000020001
100000000011000301110111100011111
11110111111111011100000010001
1110111111111011101010012001
1100000011010101110000010201
10002000000000001100000010201
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 111111 111111111111

Controls:

W - move forward
S - move back
A - move left
D - move right

left arrow - turn left
right arrow - turn right
escape - close the game

Bonus part controls:

H - put HUD on/off
- - decrease amount of HP
+ - increase amount of HP
mouse to the left border of the screen - turn left
mouse to the right border of the screen - turn right

Main goal:
drink sprite in cans to increase HP
drink sprite in bottles to decrease HP
enjoy the music
walk around the maze
contemplate walls and the sky
