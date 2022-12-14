#include "Enemy.h"
#include "cmath"

void Enemy::update(Rocket rocket, double dt)
{
    // takes in deltatime and updates
    // rocket position
    float rocx = rocket.rect.x;
    float rocy = rocket.rect.y;

    float distx = rocx - rect.x;
    float disty = rocy - rect.y;

    // normalize vector
    float mag = 0;
    // magnitude of distance vector between ship and rocket
    mag = sqrt((distx * distx) + (disty * disty));
    // normalize
    float normx = distx / mag;
    float normy = disty / mag;

    // Enemy direction angle
    angleCalc(rocket, dt);

    // if enemy ship is getting closer to rocket speed up
    if (mag < max_dist)
    {
        // translate enemy ship
        rect.x += normx * (dt / 1000.0f) * speed;
        rect.y += normy * (dt / 1000.0f) * speed;
    }
    else if (mag > max_dist)
    {
        rect.x += normx * (dt / 1000.0f) * stallSpeed;
        rect.y += normy * (dt / 1000.0f) * stallSpeed;
    }

    // enemy doesn't rotate towards rocket
}

void Enemy::angleCalc(Rocket rocket, double dt)
{
    // take the rocket cx and cy
    float cx, cy;
    cx = rocket.rect.x + rocket.rect.w / 2;
    cy = rocket.rect.y + rocket.rect.h / 2;

    // find deltax and deltay
    float deltax, deltay;
    deltax = (rect.x + rect.w / 2) - cx;
    deltay = (rect.y - rect.h / 2) - cy;
    /* deltax = deltax / (sqrt((deltax * deltax) + (deltay * deltay)));
    deltay = deltay / (sqrt((deltax * deltax) + (deltay * deltay))); */

    // deltax and deltay is rocket ship center - enemy ship rotation point
    // the angle is (atan2(delta_y, delta_x)/degtorad
    angle = ((atan2(deltay, deltax) * 180.00000) / 3.141592) - 90.0f;
}

void Enemy::angleCheck()
{
    if (angle < 0)
        angle = 360;

    if (angle > 360)
        angle = 0;
}

bool Enemy::lifeEmpty()
{
    // check if health is empty,
    if (health <= 0)
    {
        return true;
    }

    // return true if empty
    // else false
    return false;
}

bool Enemy::collision(SDL_FRect other)
{
    // Check for collision with other rect
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    // Sides of Bullet rect
    leftA = rect.x;
    rightA = rect.x + rect.w;
    topA = rect.y;
    bottomA = rect.y + rect.h;

    // Sides of other rect
    leftB = other.x;
    rightB = other.x + other.w;
    topB = other.y;
    bottomB = other.y + other.h;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}

void Enemy::takeHit(CustomEnums::Entity e)
{
    if (e == CustomEnums::Entity::Bullet)
    {
        // Bullet collision
        if (health >= 0)
        {
            health -= 0.5f;
        }
    }
    else if (e == CustomEnums::Entity::Rock)
    {
        // Rock collision
    }
    else if (e == CustomEnums::Entity::Rocket)
    {
        // Rocket collision
    }

    // calcHealthP();
}

void Enemy::calcHealthP()
{
    //
    if (health > healthMax)
    {
        health = healthMax;
    }
    else if (health < 0.0f)
    {
        health = 0.0f;
    }
    healthPercent = (health / healthMax) * 1.0f;
}

EnemyShoot Enemy::attack(Rocket rocket)
{
    float rcx, rcy; // rocket centres
    float cx, cy;   // enemy centres
    float disx, disy;
    float distance;
    rcx = rocket.rect.x + rocket.rect.w / 2;
    rcy = rocket.rect.y + rocket.rect.h / 2;
    cx = rect.x + rect.w / 2;
    cy = rect.y + rect.h / 2;
    disx = abs(cx - rcx);
    disy = abs(cy - rcy);
    distance = sqrt((disy * disy) + (disx * disx));

    EnemyShoot shoot;
    shoot.btype = CustomEnums::BulletT::RegularB;
    shoot.shoot = false;
    shoot.speed = 0.0f;

    // check rocket position
    // based on enemy type, we perform certain actions
    if (type == CustomEnums::EnemyT::Regular)
    {

        if (attackRange > distance)
        {
            if (interval == 0)
            // if ((interval % 50) == 0)
            {
                shoot.btype = CustomEnums::BulletT::RegularB;
                shoot.shoot = true;
                shoot.speed = 50.0f;

                interval = 100;
            }

            interval -= 1;
            return shoot;
        }
    }
    else if (type == CustomEnums::EnemyT::SpaceBane)
    {
        // Do another thing if enemy is Space Bane
        return shoot;
    }
    else if (type == CustomEnums::EnemyT::WarVet)
    {
        // Do another thing if enemy is War Vet
        return shoot;
    }

    return shoot;
}

void Enemy::rocketAim(Rocket rocket, float &normy, float &normx)
{
    float dx, dy, mag;
    dx = (rocket.rect.x + rocket.rect.w / 2) - (rect.x + rect.w / 2); // distance between rocket centres
    dy = (rocket.rect.y + rocket.rect.h / 2) - (rect.y + rect.h / 2); // distance between rocket centresF
    mag = sqrt((dx * dx) + (dy * dy));                                // the magnitude
    normx = (dx / mag) * 30.0f + (rect.x + rect.w / 2);               // aim from ship centre towards rocket centre
    normy = (dy / mag) * 30.0f + (rect.y + rect.h / 2);               // aim from ship centre towards rocket centreF
}

void Enemy::renderHealthBar(SDL_Renderer *renderer)
{
    // calc health percentage
    calcHealthP();

    // use percentage to render life
    // RED BACKGROUND
    float bgx = rect.x + 20;
    float bgy = rect.y + rect.h + 10;
    float bgw = rect.w - 20;
    float bgh = 2;
    SDL_FRect bgrect = {bgx, bgy, bgw, bgh};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(renderer, &bgrect);
    // GREEN FOREGROUND
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    float fw = bgw * healthPercent;
    float fx = bgx + (bgw - fw);
    SDL_FRect fgrect = {fx, bgy, fw, bgh};
    SDL_RenderFillRectF(renderer, &fgrect);
    // Setting color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void Enemy::render(SDL_Renderer *renderer, SDL_Texture *texture, Rocket rocket, double dt)
{
    update(rocket, dt); // Takes in reference to rocket ship for knowledge on its position
    // render function for enemy ships

    // draw aim from centre of enemy towards center of rocket
    float normx, normy;
    rocketAim(rocket, normy, normx);

    SDL_RenderCopyExF(renderer, texture, nullptr, &rect, angle, NULL, SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // SDL_RenderFillRectF(renderer, &rect);
    renderHealthBar(renderer);
}

// angle and position should change based on rocket position

Enemy::Enemy(int x, int y, CustomEnums::EnemyT t)
{
    rect.x = x;
    rect.y = y;
    rect.w = 60;
    rect.h = 45;
    type = t;
}

Enemy::~Enemy() {}

/*
    For enemy ships manager,
    have a function which generates random places to spawn
    ships at
    Enemy manager class on instantiating should set the
    max number of ships on screen and rendering each of them per
    frame. The enemy ships would hold their own rendering and update
    function.
    From where the enemy ship starts from and the angle it starts at
    is decided by the enemy manager.
 */

/*
    TODO:
    Implement enemy update and render functions
    Implement enemy Manager functions
    Test implementations
    Set textures for enemy ships
    Move texture instantiation and creation to class constructor
 */

/*
    Aim enemy ship toward centre of rocket to aim and shoot
    When aim is locked then enemy ship shoots.
    Aim can be set up as a short line from the top centre point
    of the enemy ship rect, pointing outwards. That line must always
    chase the rocket centre. When aim is selected then the ship shoots

    *   *   *   *   *   *   *   *
    .           *
    .           .
    .           .
(xmin,ymin)     .   //If this is xmin ymin
             (cx,cy) //Then this is the centre from the top
    *   *   *   *   *   *   *   *

    *   *   *   *   *   *   *   *

    *   *   *   *   *   *   *   *
 */

/*
    Get enemy ship center top, will be same same xmin ymin, shifted
    to the right by half of its width.
    draw line outwards.
    Point must always point to center of rocket
    Get center of rocket.
    Get direction towards the rocket from the centre top.
    get angle from such direction and rotate enemy ship towards that direction.
 */