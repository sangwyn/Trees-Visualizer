#include "Globals.h"

sf::Vector2f root_pos = {500.0f, 50.0f};
float global_scale = 1.0f;
int *selected_key = nullptr;
bool couldnt_insert = false;

int StrToInt(std::string str) {
    int res = 0;
    int pcf_govno = 1;
    for (int i = str.size() - 1; i >= 0; --i) {
        res += (str[i] - '0') * pcf_govno;
        pcf_govno *= 10;
    }
    return res;
}

float DegToRad(float deg) {
    return deg * (M_PI / 180.0f);
}