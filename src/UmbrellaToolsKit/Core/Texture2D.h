#ifndef _TEXTURE_2D_H_
#define _TEXTURE_2D_H_

class Texture2D
{
private:
    int _width;
    int _hight;
    unsigned char *_data;

public:
    int GetWidth();
    int GetHight();
    unsigned char *GetData();
};

#endif //_TEXTURE_2D_H_