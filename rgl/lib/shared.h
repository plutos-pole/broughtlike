#ifndef SHARED_H
#define SHARED_H

#define WIDTH  100
#define HEIGHT 30
#define MIN_ROOM_W 6
#define MAX_ROOM_W 15 
#define MIN_ROOM_H 3
#define MAX_ROOM_H 6
#define MIN_ROOM_DISTANCE 10 * 10 
#define MAX_ROOMS 8

enum floor_type {FLOOR_OPEN, FLOOR_WALL, FLOOR_PATH, FLOOR_ROOM};
extern char floor_symb[];

#endif
