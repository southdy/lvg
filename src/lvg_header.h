#ifndef __TINYC__
#include <stddef.h>
#include <stdint.h>
#endif
#ifdef EMSCRIPTEN
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#endif

enum LVG_OBJECT_TYPE { LVG_OBJ_EMPTY = 0, LVG_OBJ_SHAPE, LVG_OBJ_IMAGE, LVG_OBJ_VIDEO, LVG_OBJ_GROUP, LVG_OBJ_BUTTON };
enum LVG_PLAY_STATE { LVG_PLAYING = 0, LVG_STOPPED };

typedef struct LVGObject
{
    int id, type, depth, ratio;
    float t[6];
    float color_mul[4];
    float color_add[4];
} LVGObject;

typedef struct LVGAction
{
    union {
        const void *data;
        int idata;
        unsigned short sdata;
    };
    unsigned short len;
    unsigned char opcode;
} LVGAction;

typedef struct LVGMovieClipFrame
{
    LVGObject *objects;
    LVGAction *actions;
    int num_objects, num_actions;
} LVGMovieClipFrame;

typedef struct LVGMovieClipGroup
{
    LVGMovieClipFrame *frames;
    int num_frames, cur_frame, play_state;
} LVGMovieClipGroup;

typedef struct LVGShapeCollection
{
    NSVGshape *shapes;
    float bounds[4];
    int num_shapes;
} LVGShapeCollection;

typedef struct LVGSound
{
    short *samples;
    int num_samples, rate, channels, cur_play_byte;
} LVGSound;

typedef struct LVGVideoFrame
{
    void *data;
    int len;
} LVGVideoFrame;

typedef struct LVGVideo
{
    LVGVideoFrame *frames;
    int codec, width, height, num_frames;
    int cur_frame, image;
} LVGVideo;

typedef struct LVGButton
{
    LVGObject *up_shapes;
    LVGObject *over_shapes;
    LVGObject *down_shapes;
    LVGObject *hit_shapes;
    LVGAction *actions;
    int num_up_shapes, num_over_shapes, num_down_shapes, num_hit_shapes, num_actions;
} LVGButton;

typedef struct LVGMovieClip
{
    LVGShapeCollection *shapes;
    int *images;
    LVGMovieClipGroup *groups;
    LVGSound *sounds;
    LVGVideo *videos;
    LVGButton *buttons;
    float bounds[4];
    NVGcolor bgColor;
    int num_shapes, num_images, num_groups, num_sounds, num_videos, num_buttons;
    float fps;
    double last_time;
} LVGMovieClip;

NVGpaint nvgLinearGradientTCC(NVGcontext* ctx, float sx, float sy, float ex, float ey,
    float ir, float ig, float ib, float ia, float or, float og, float ob, float oa);

char *lvgGetFileContents(const char *fname, uint32_t *size);
void lvgFree(void *buf);
void lvgDrawSVG(NSVGimage *image);
void lvgDrawClip(LVGMovieClip *clip);
NSVGimage *lvgLoadSVG(const char *file);
NSVGimage *lvgLoadSVGB(const char *file);
LVGMovieClip *lvgLoadSWF(const char *file);
LVGMovieClip *lvgLoadClip(const char *file);
int lvgStartAudio(int samplerate, int channels, int format, int buffer, int is_capture, void (*callback)(void *userdata, char *stream, int len), void *userdata);
short *lvgLoadMP3(const char *file, int *rate, int *channels, int *num_samples);
short *lvgLoadMP3Buf(const char *buf, uint32_t buf_size, int *rate, int *channels, int *nsamples);
void lvgPlaySound(LVGSound *sound);
void lvgStopAudio();
void lvgExecuteActions(LVGMovieClip *clip, LVGAction *actions, int num_actions);

#ifdef __TINYC__
extern NVGcontext *vg;
#endif
extern NVGcolor g_bgColor;
extern int winWidth;
extern int winHeight;
extern int width;
extern int height;
extern int mkeys;
extern double mx;
extern double my;
extern double g_time;

void *malloc(size_t);
void *calloc(size_t, size_t);
void *realloc(void *, size_t);
void free(void *);

double atof(const char*);
int atoi(const char*);
long int atol(const char*);

double sin(double);
double cos(double);
double tan(double);
double sinh(double);
double cosh(double);
double tanh(double);
double asin(double);
double acos(double);
double atan(double);
double atan2(double, double);
double exp(double);
double log(double);
double log10(double);
double pow(double, double);
double sqrt(double);
double ceil(double);
double floor(double);
double fabs(double);
double ldexp(double, int);
double frexp(double, int*);
double modf(double, double*);
double fmod(double, double);

float sinf(float);
float cosf(float);
float tanf(float);
float sinhf(float);
float coshf(float);
float tanhf(float);
float asinf(float);
float acosf(float);
float atanf(float);
float atan2f(float, float);
float expf(float);
float logf(float);
float log10f(float);
float powf(float, float);
float sqrtf(float);
float ceilf(float);
float floorf(float);
float fabsf(float);
float ldexpf(float, int);
float frexpf(float, int*);
float modff(float, float*);
float fmodf(float, float);

#ifdef __TINYC__
#define CHAR_BIT 8
#define SCHAR_MIN (-128)
#define SCHAR_MAX 127
#define UCHAR_MAX 255

#ifdef __CHAR_UNSIGNED__
#define CHAR_MIN 0
#define CHAR_MAX UCHAR_MAX
#else
#define CHAR_MIN SCHAR_MIN
#define CHAR_MAX SCHAR_MAX
#endif

#define SHRT_MIN (-32768)
#define SHRT_MAX 32767
#define USHRT_MAX 65535
#define INT_MIN (-INT_MAX - 1)
#define INT_MAX 2147483647
#define UINT_MAX 4294967295U

#if __WORDSIZE == 64
#define LONG_MAX 9223372036854775807L
#else
#define LONG_MAX 2147483647L
#endif
#define LONG_MIN (-LONG_MAX - 1L)

#if __WORDSIZE == 64
#define ULONG_MAX 18446744073709551615UL
#else
#define ULONG_MAX 4294967295UL
#endif

# define LLONG_MAX 9223372036854775807LL
# define LLONG_MIN (-LLONG_MAX - 1LL)
# define ULLONG_MAX 18446744073709551615ULL

typedef long int time_t;

struct timespec
{
  long int tv_sec;
  long int tv_nsec;
};

struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  long int tm_gmtoff;
  const char *tm_zone;
};

time_t time(time_t *t);
char *asctime(const struct tm *tm);
char *ctime(const time_t *timep);
struct tm *gmtime(const time_t *timep);
struct tm *localtime(const time_t *timep);
time_t mktime(struct tm *tm);
#endif