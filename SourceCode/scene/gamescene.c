#include <allegro5/allegro_audio.h>
#include "gamescene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../Grid.h"








/*
   [GameScene function]
*/
Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);

    pDerivedObj->background = al_load_bitmap("assets/image/0523scene.png");
    pDerivedObj->tower_img = al_load_bitmap("assets/image/robot-golem.png");  // ✅ 新增
    pDerivedObj->tower_x = 100;   // ✅ 新增
    pDerivedObj->tower_y = 100;
    pDerivedObj->dragging = false;
    pDerivedObj->tower_placed = false;

    pObj->pDerivedObj = pDerivedObj;

    Grid_init();

    _Register_elements(pObj, New_Floor(Floor_L));
    _Register_elements(pObj, New_Teleport(Teleport_L));
    _Register_elements(pObj, New_Tree(Tree_L));
    _Register_elements(pObj, New_Character(Character_L));

    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;

    return pObj;
}


void game_scene_update(Scene *self)
{
    GameScene *gs = (GameScene *)(self->pDerivedObj);
    extern ALLEGRO_EVENT event;  // 確保你有在 global.h 宣告 extern

    float scale = 0.3;  // 與 draw 縮放比例一致
    int img_w = al_get_bitmap_width(gs->tower_img);
    int img_h = al_get_bitmap_height(gs->tower_img);
    int scaled_w = img_w * scale;
    int scaled_h = img_h * scale;

    // 除錯訊息：確認 update 有執行
    printf("[update] event.type = %d\n", event.type);

    // ✅ 拖曳處理（若塔還未放置）
    if (!gs->tower_placed) {
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mx = event.mouse.x;
            int my = event.mouse.y;
            printf("MOUSE DOWN at (%d, %d)\n", mx, my);

            if (mx >= gs->tower_x && mx <= gs->tower_x + scaled_w &&
                my >= gs->tower_y && my <= gs->tower_y + scaled_h) {
                gs->dragging = true;
                printf("👉 開始拖曳 tower！\n");
            }
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if (gs->dragging) {
                gs->tower_x = event.mouse.x - scaled_w / 2;
                gs->tower_y = event.mouse.y - scaled_h / 2;
                printf("🟡 拖曳中 tower 位置: (%d, %d)\n", gs->tower_x, gs->tower_y);
            }
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if (gs->dragging) {
                gs->dragging = false;
                printf("🟢 放開拖曳\n");
                // 👉 第二階段會加入格子合法檢查
            }
        }
    }

    // ✅ 更新 Elements（角色、子彈等）
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        ele->Update(ele);
    }

    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        ele->Interact(ele);
    }

    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
}


void game_scene_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = (GameScene *)(self->pDerivedObj);

    int w = al_get_bitmap_width(gs->background);
    int h = al_get_bitmap_height(gs->background);
    al_draw_scaled_bitmap(gs->background,
                          0, 0, w, h,
                          0, 0, WIDTH, HEIGHT, 0);

    Grid_draw();

    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++) {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }

    // ✅ 畫正在拖曳或預放置狀態的塔
    if (!gs->tower_placed) {
        float scale = 0.3;  // ✅ 縮小為原本的 30%
        int w = al_get_bitmap_width(gs->tower_img);
        int h = al_get_bitmap_height(gs->tower_img);
        al_draw_scaled_bitmap(gs->tower_img,
                              0, 0, w, h,
                              gs->tower_x, gs->tower_y,
                              w * scale, h * scale,
                              0);
    }
    
}


void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    al_destroy_bitmap(Obj->tower_img);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
