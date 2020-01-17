#pragma once

#include "shape.h"

/*---------------I_Pattern------------------------*/

class I_PATTERN: public Shape {
public:
    I_PATTERN(int org_x = GAME_BG::BG_ORIGIN_X + 11, int org_y = GAME_BG::BG_ORIGIN_Y + 3);
    virtual ~I_PATTERN() = default;
    void set_shape();
};

/*---------------I_Pattern  end-------------------*/

/*---------------O_Pattern------------------------*/

class O_PATTERN: public Shape {
public:
    O_PATTERN(int org_x = GAME_BG::BG_ORIGIN_X + 11, int org_y = GAME_BG::BG_ORIGIN_Y + 3);
    virtual ~O_PATTERN() = default;
    void set_shape();
};

/*---------------O_Pattern  end-------------------*/

/*---------------Z_Pattern------------------------*/

class Z_PATTERN: public Shape {
public:
    Z_PATTERN(int org_x = GAME_BG::BG_ORIGIN_X + 11, int org_y = GAME_BG::BG_ORIGIN_Y + 3);
    virtual ~Z_PATTERN() = default;
    void set_shape();
};

/*---------------Z_Pattern  end-------------------*/

/*---------------ZZ_Pattern-----------------------*/

class ZZ_PATTERN: public Shape {
public:
    ZZ_PATTERN(int org_x = GAME_BG::BG_ORIGIN_X + 11, int org_y = GAME_BG::BG_ORIGIN_Y + 3);
    virtual ~ZZ_PATTERN() = default;
    void set_shape();
};

/*---------------ZZ_Pattern  end------------------*/

/*---------------T_Pattern------------------------*/

class T_PATTERN: public Shape {
public:
    T_PATTERN(int org_x = GAME_BG::BG_ORIGIN_X + 11, int org_y = GAME_BG::BG_ORIGIN_Y + 3);
    virtual ~T_PATTERN() = default;
    void set_shape();
};

/*---------------T_Pattern  end-------------------*/

/*---------------L_Pattern------------------------*/

class L_PATTERN: public Shape {
public:
    L_PATTERN(int org_x = GAME_BG::BG_ORIGIN_X + 11, int org_y = GAME_BG::BG_ORIGIN_Y + 3);
    virtual ~L_PATTERN() = default;
    void set_shape();
};

/*---------------L_Pattern  end-------------------*/

/*---------------LL_Pattern-----------------------*/

class LL_PATTERN: public Shape {
public:
    LL_PATTERN(int org_x = GAME_BG::BG_ORIGIN_X + 11, int org_y = GAME_BG::BG_ORIGIN_Y + 3);
    virtual ~LL_PATTERN() = default;
    void set_shape();
};

/*---------------LL_Pattern  end------------------*/