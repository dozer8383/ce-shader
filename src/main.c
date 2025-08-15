#include <graphx.h>
#include <keypadc.h>
#include <math.h>

typedef struct vec3 {
    float x, y, z;
} vec3;

typedef struct vec2 {
    float x, y, z;
} vec2;

float length_vec2(float x, float y) {
  return sqrt(x * x + y * y);
}

float length_vec3(float x, float y, float z) {
  return sqrt(x * x + y * y + z * z);
}

float length_vec4(float x, float y, float z, float w) {
  return sqrt(x * x + y * y + z * z + w * w);
}

float distance_from_sphere(vec3 p, vec3 c, float r) {
    return length_vec3(p.x - c.x, p.y - c.y, p.z - c.z) - r;
}

vec3 ray_march(vec3 ro, vec3 rd) {
    float total_distance_traveled = 0.0;
    const int NUMBER_OF_STEPS = 32;
    const float MINIMUM_HIT_DISTANCE = 0.001;
    const float MAXIMUM_TRACE_DISTANCE = 1000.0;
    for (int i = 0; i < NUMBER_OF_STEPS; ++i)
    {
        vec3 current_position = {ro.x + total_distance_traveled * rd.x,ro.y + total_distance_traveled * rd.y,ro.z + total_distance_traveled * rd.z};
        
        float distance_to_closest = distance_from_sphere(current_position, (vec3){0.0, 0.0, 0.0}, 1.0);

        if (distance_to_closest < MINIMUM_HIT_DISTANCE) 
        {
            return (vec3){1.0, 0.0, 0.0};
        }

        if (total_distance_traveled > MAXIMUM_TRACE_DISTANCE)
        {
            break;
        }
        total_distance_traveled += distance_to_closest;
    }
    return (vec3){0.0, 0.0, 0.0};
}

uint8_t RGBto256(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t palcolor;
    double tempr = r/32;
    double tempg = g/32;
    double tempb = b/64;
    palcolor = tempg+(tempb*8)+(tempr*32);
    return palcolor;
}

uint8_t shader0(float x, float y, int t ,int res) {
    return RGBto256(x,y,64);
}

uint8_t shader1(int x, int y, int t, int res) {
    uint8_t displacement[10] = {1,2,1,0,3,2,0,1,1,4};
    int transformx = displacement[x%10]*10*sin(y)+(sin(t)*5);
    int transformy = displacement[y%10]*10;
    return RGBto256(x+transformx,y+transformy,64);
}

uint8_t shader2(int x, int y, int t, int res) {
    float transformx = sin(y/2)*5;
    float transformy = sin(x/2)*5;
    return RGBto256(x+transformx,y+transformy,64);
}

uint8_t shader3(float x, float y, int t ,int res) {
    vec2 uv = {x * 2.0 - 1.0, y * 2.0 - 1.0};

    vec3 camera_position = (vec3){0.0, 0.0, -5.0};
    vec3 ro = camera_position;
    vec3 rd = (vec3){uv.x, uv.y, 1.0};

    vec3 shaded_color = ray_march(ro, rd);
    return RGBto256(shaded_color.x*255,shaded_color.y*255,shaded_color.z*255);
}

uint8_t shader4(float x, float y, int t ,int res) {
    return RGBto256(x,y,64);
}

uint8_t resolution = 2;

int main(void) {
    gfx_Begin();
    gfx_FillScreen(255);
    int time = 1;
    // gfx_SetDrawBuffer();

    do {
        for (int y = 0; y < 240; y+=resolution) {
            for (int x = 0; x < 320; x+=resolution) {
                gfx_SetColor(shader3(x/320,y/240,time,resolution));
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