#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char latin[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZFM";
#define LATIN_SIZE ((int)(sizeof(latin) - 1))
char digits[] = "123456789";
#define DIGITS_SIZE ((int)(sizeof(digits) - 1))
#define SUBJ_SIZE 20

#define FNAME_SIZE 32
#define MAX_SIZE 32
#define INDEX_MAX_SIZE 4
#define BUF_SIZE (4 * 1024 * 1024)

char buf[BUF_SIZE] = { '\0' };
static unsigned int g_seed = 0;


static inline void fast_srand(int seed)
{
    g_seed = seed;
}

static inline int fast_rand()
{
    g_seed = (214013 * g_seed + 2531011 * time(0));
    return (g_seed >> 16) & 0x7FFF;
}


int main(int argc, char *argv[])
{
    int qty = 10;// * 1000 * 1000;
    if (argc >= 2) {
        qty = atoi(argv[1]);
    }
    
    char fname[FNAME_SIZE] = "_input.txt";
    if (argc >= 3) {
        strncat(argv[2], fname, FNAME_SIZE - 1);
    }
    
    FILE *f = fopen(fname, "wb");
    if (!f) {
        fprintf(stderr, "Error: can't open file '%s'.\n", fname);
        return 1;
    }
    
    fast_srand(0);

    register int buf_pos = 0;
    for (int i = 0; i < qty; ++i) {
        register int index_size = fast_rand() % INDEX_MAX_SIZE + 1;
        for (register int j = 0; j < index_size; ++j) {
            buf[buf_pos++] = latin[fast_rand() % LATIN_SIZE];
        }
        buf[buf_pos++] = ' ';

        index_size = fast_rand() % INDEX_MAX_SIZE + 1;

        for (register int j = 0; j < index_size; ++j) {
            buf[buf_pos++] = digits[fast_rand() % DIGITS_SIZE];
        }

        buf[buf_pos++] = ' ';

        index_size = fast_rand() % MAX_SIZE + 1;

        for(int k = 0; k < index_size; ++k) {
            buf[buf_pos++] = latin[fast_rand() % LATIN_SIZE];
        }

        buf[buf_pos++] = '\n';
        buf[buf_pos + 1] = '\0';

        if (buf_pos >= BUF_SIZE - 64) {
            fwrite(buf, sizeof(buf[0]), buf_pos, f);
            buf_pos = 0;
        }
    }

    if (buf_pos > 0) {
        fwrite(buf, sizeof(buf[0]), buf_pos, f);
    }
    
    fclose(f);
    
    return 0;
}