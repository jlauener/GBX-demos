#include "GBX.h"

#define TYPE_BALL 0
#define TYPE_PADDLE 1
#define TYPE_BRICK 2
#define TYPE_WALL 3

//-----------------------------------------------------------------------------
// Paddle
//-----------------------------------------------------------------------------

const uint16_t paddleSpriteData[] =
{
  // width, height
  16, 4,
  // transparent color
  0xF81F,
  // bitmap
  0xF81F, 0xfeb2, 0xfeb2, 0xfeb2, 0xfeb2, 0xfeb2, 0xfeb2, 0xfeb2, 0xfeb2, 0xfeb2, 0xfeb2, 0xfeb2, 0xfeb2, 0xfeb2, 0xfeb2, 0xF81F, 0xfeb2, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xfd42, 0xfeb2, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xcc68, 0xfd42, 0xF81F, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xfd42, 0xF81F
};

const uint8_t paddleSolidType[] =
{
  // count
  1,
  // entity types
  TYPE_WALL
};

class Paddle : public Entity
{
public:
  Paddle() :
    sprite(paddleSpriteData, -8, -2)
  {
    setHitbox(-8, -2, 16, 4);
  }

  void update()
  {
    if (gbx::isDown(BUTTON_LEFT))
    {
      moveBy(-2, 0, paddleSolidType);
    }
    else if (gbx::isDown(BUTTON_RIGHT))
    {
      moveBy(2, 0, paddleSolidType);
    }
  }

  void draw(int16_t x, int16_t y)
  {
    sprite.draw(x, y);
  }

private:
  Sprite sprite;
};

//-----------------------------------------------------------------------------
// Brick
//-----------------------------------------------------------------------------

const uint16_t brickSpriteData[] =
{
  // width, height
  8, 4,
  // transparent color
  0xF81F,
  // bitmap
  0xca30,0xca30,0xca30,0xca30,0xca30,0xca30,0xca30,0xd8e4,0xca30,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0x9008,0xca30,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0x9008,0xd8e4,0x9008,0x9008,0x9008,0x9008,0x9008,0x9008,0x9008,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xffff,0xffff,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xd8e4,0xd8e4,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0xd8e4,0x7ddf,0x7ddf,0x7ddf,0x7ddf,0x7ddf,0x7ddf,0x7ddf,0x4439,0x7ddf,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439,0x210,0x7ddf,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439,0x210,0x4439,0x210,0x210,0x210,0x210,0x210,0x210,0x210,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439,0xffff,0xffff,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0x4439,0x4439,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439,0x4439
};

#define IDLE 0
#define BREAK 1

const uint8_t brickAnimData[] =
{
  // IDLE (frame count, mode, interval, frames...)
  1, LOOP, 0, 0,
  // BREAK (frame count, mode, interval, frames...)
  2, ONE_SHOT, 2, 1, 2
};

#define BRICK_RED 0
#define BRICK_BLUE 1

class Brick : public Entity
{
public:
  Brick() :
    sprite(brickSpriteData, brickAnimData)
  {
    setHitbox(8, 4);
    sprite.play(IDLE);
  }

  void setBrickType(uint8_t brickType)
  {
    sprite.frameOffset = brickType * 3;
  }

  void draw(int16_t x, int16_t y)
  {
    sprite.draw(x, y);
  }

  void hit()
  {
    setFlag(FLAG_COLLIDABLE, false);
    sprite.play(BREAK);
  }

private:
  Anim sprite;
};

//-----------------------------------------------------------------------------
// Ball
//-----------------------------------------------------------------------------

const uint16_t ballSpriteData[] =
{
  // width, height
  4, 4,
  // transparent color
  0xF81F,
  // bitmap
  0xF81F,0xacd0,0xacd0,0xF81F,0xacd0,0xffff,0xffff,0xacd0,0xacd0,0xffff,0xacd0,0xacd0,0xF81F,0xacd0,0xacd0,0xF81F
};

const uint8_t ballSolidType[] =
{
  // count
  3,
  // entity types
  TYPE_PADDLE, TYPE_BRICK, TYPE_WALL
};

class Ball : public Entity
{
public:
  Ball() :
    sprite(ballSpriteData, -2, -2)
  {
    setHitbox(-2, -2, 4, 4);
  }

  void update()
  {
    moveBy(dx, dy, ballSolidType);
  }

  void draw(int16_t x, int16_t y)
  {
    sprite.draw(x, y);
  }

protected:
  bool onMoveCollideX(Entity& other)
  {
    if (other.getType() == TYPE_BRICK)
    {
      Brick& brick = (Brick&)other;
      brick.hit();
    }
    dx = -dx;
    return true;
  }

  bool onMoveCollideY(Entity& other)
  {
    if (other.getType() == TYPE_BRICK)
    {
      Brick& brick = (Brick&)other;
      brick.hit();
    }
    dy = -dy;
    return true;
  }

private:
  int16_t dx = 1;
  int16_t dy = -1;
  Sprite sprite;
};

//-----------------------------------------------------------------------------
// GameScene
//-----------------------------------------------------------------------------

class GameScene : public Scene
{
public:
  GameScene() :
    ball(this, TYPE_BALL, 1),
    paddle(this, TYPE_PADDLE, 1),
    bricks(this, TYPE_BRICK, 48),
    walls(this, TYPE_WALL, 4)
  {
  }

  void onInit()
  {
    walls.spawn()->setHitbox(-8, 0, 8, (uint8_t) gbx::height); // left wall
    walls.spawn()->setHitbox((int8_t) gbx::width, 0, 8, (uint8_t) gbx::height); // right wall
    walls.spawn()->setHitbox(0, -8, (uint8_t) gbx::width, 8); // top wall
    walls.spawn()->setHitbox(0, (int8_t) gbx::height, (uint8_t) gbx::width, 8); // bottom wall

    ball.spawn(gbx::width / 2, gbx::height - 16);

    paddle.spawn(gbx::width / 2, gbx::height - 8);

    bool flipFlop = false;
    for (int16_t ix = 0; ix < 8; ix++)
    {
      for (int16_t iy = 0; iy < 6; iy++)
      {
        bricks.spawn(8 + ix * 8, 8 + iy * 4)->setBrickType(flipFlop ? BRICK_RED : BRICK_BLUE);
        flipFlop = !flipFlop;
      }
      flipFlop = !flipFlop;
    }
  }

private:
  EntityPool<Ball> ball;
  EntityPool<Paddle> paddle;
  EntityPool<Brick> bricks;
  EntityPool<Entity> walls;
};

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------

GameScene gameScene;

void setup()
{
  gbx::init();
  gbx::setScene(gameScene);
}

void loop()
{
  gbx::update();
}
