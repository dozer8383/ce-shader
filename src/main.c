#include <graphx.h>
#include <keypadc.h>
#include <math.h>

uint8_t RGBto256(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t palcolor;
    double tempr = r/32;
    double tempg = g/32;
    double tempb = b/64;
    palcolor = tempg+(tempb*8)+(tempr*32);
    return palcolor;
}

uint8_t shader0(int x, int y, int t ,int res) {
    return RGBto256(x,y,64);
}

uint8_t shader1(int x, int y, int t, int res) {
    uint8_t displacement[10] = {1,2,1,0,3,2,0,1,1,4};
    int transformx = displacement[x%10]*10*sin(y)+(sin(t)*5);
    int transformy = displacement[y%10]*10;
    return RGBto256(x+transformx,y+transformy,64);
}

uint8_t shader2(int x, int y, int t, int res) {
    int transformx = (x%2)*res;
    int transformy = (y%2)*res;
    return RGBto256(x+transformx,y+transformy,64);
}

uint8_t resolution = 2;

int main(void) {
    gfx_Begin();
    gfx_FillScreen(255);
    int time = 1;
    // gfx_SetDrawBuffer();
    do {
        for (int y = 0; y < 240; y+=resolution) {
            for (int x = 0; x < 256; x+=resolution) {
                gfx_SetColor(shader2(x,y,time,resolution));
                // gfx_SetPixel(x, y);
                gfx_FillRectangle_NoClip(x,y,resolution,resolution);
            }
            kb_Scan();
            if (kb_Data[1] == kb_2nd) {
                break;
            }
        }
        ++time;
        // gfx_SwapDraw();
    } while (kb_Data[1] != kb_2nd);
    gfx_End();
    return 0;
}