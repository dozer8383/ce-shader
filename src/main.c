#include <graphx.h>
#include <keypadc.h>

void begin(void);
void end(void);
bool step(void);
void draw(void);

int main(void)
{
    bool partial_redraw = false;

    begin();
    gfx_Begin();
    gfx_SetDrawBuffer();
    do {
        for (int i = 0; i < 30; i++) {
            
        }
        gfx_SwapDraw();
    } while (kb_Data[1] != kb_2nd);
    gfx_End();
    end();

    return 0;
}
