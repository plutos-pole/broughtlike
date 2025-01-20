#ifndef SHARED_H
#define SHARED_H

#define WIDTH  100
#define HEIGHT 30
#define MIN_ROOM_W 5
#define MAX_ROOM_W 10
#define MIN_ROOM_H 3
#define MAX_ROOM_H 10

enum floor_type {FLOOR_OPEN, FLOOR_WALL, FLOOR_PATH, FLOOR_ROOM};
extern char floor_symb[];

#endif
