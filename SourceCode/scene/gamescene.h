#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"

/*
   [game scene object]
*/
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Tree_L,
    Character_L,
    Projectile_L,
} EleType;
typedef struct _GameScene
{
    ALLEGRO_BITMAP *background;

    // ✅ 拖曳用的塔圖資料
    ALLEGRO_BITMAP *tower_img;  // robot-golem.png 圖片
    int tower_x, tower_y;       // 塔目前座標
    bool dragging;              // 是否正在拖曳
    bool tower_placed;          // 是否已經放好
} GameScene;

Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

#endif
