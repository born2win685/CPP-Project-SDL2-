#include "Math.h"
using namespace std;

int Math::choose_optype(int num_choices)
{
    srand(time(NULL));
    return rand() % num_choices;
}

int Math::gen_addscore(int ammo)
{
    srand(time(NULL));
    int score1 = 2 + rand() % 4;
    if (ammo == 1)
        return score1;
    srand(time(NULL));
    int score2 = (int)(ammo / 8) + rand() % ((int)((ammo / 2) - (ammo / 8)));
    return max(score1, score2);
}
int Math::gen_subscore(int ammo, int flag)
{
    if (ammo == 1 && flag == 0)
        return 0;
    if (ammo == 1 && flag == 1)
        return 1;
    srand(time(NULL));
    int score1 = 1 + rand() % 4;
    int score2;
    srand(time(NULL));
    if (flag == 0)
        score2 = (int)(ammo / 4) + rand() % ((int)((ammo * 1.2) - (ammo / 4)));
    else
        score2 = (int)(ammo / 8) + rand() % ((int)((ammo * 0.5) - (ammo / 8)));

    return max(score1, score2);
}

int Math::gen_addandsubscore(int ammo, int flag)
{
    if (flag == 0)
    {
        srand(time(NULL));
        int score1 = 2 + rand() % 4;
        if (ammo == 1)
            return score1;
        srand(time(NULL));
        int score2 = (int)(ammo / 8) + rand() % ((int)((ammo / 2) - (ammo / 8)));
        return max(score1, score2);
    }

    else
    {
        srand(time(NULL));
        int score1 = 1 + rand() % 4;
        int score2;
        srand(time(NULL));
        score2 = (int)(ammo / 3) + rand() % ((int)((ammo * 1.5) - (ammo / 3)));
        return max(score1, score2);
    }
}

double Math::gen_addandmulscore(int ammo, int flag)
{
    if (flag == 0)
    {
        srand(time(NULL));
        int score1 = 2 + rand() % 4;
        if (ammo == 1)
            return score1;
        srand(time(NULL));
        int score2 = (int)(ammo / 8) + rand() % ((int)((ammo / 2) - (ammo / 8)));
        return (double)max(score1, score2);
    }

    else
    {
        srand(time(NULL));
        int num = 8 + rand() % 9;
        double temp = (double)num;
        double score = temp / 8;
        return score;
    }
}

int Math::gen_subanddivscore(int ammo, int flag)
{
    if (flag == 0)
    {
        srand(time(NULL));
        int score1 = 1 + rand() % 4;
        int score2;
        srand(time(NULL));
        score2 = (int)(ammo / 4) + rand() % ((int)((ammo * 1.2) - (ammo / 4)));
        return max(score1, score2);
    }

    else
    {
        if (ammo <= 2)
            return 1;
        srand(time(NULL));
        int score = 2 + rand() % 9;
        return score;
    }
}