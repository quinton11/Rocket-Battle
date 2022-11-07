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
    mag = sqrt((distx * distx) + (disty * disty));
    // normalize
    float normx = distx / mag;
    float normy = disty / mag;
    angleCalc(rocket, dt);

    if (mag > min_dist)
    {
        // translate enemy ship
        rect.x += normx * (dt / 1000.0f) * speed;
        rect.y += normy * (dt / 1000.0f) * speed;
        // angleCheck(); // Check if angle is passed bounds
        //(asin(normx) / degtorad) rot_speed
        //  angle += ((asin(normx) / degtorad) * (dt / 1000.0f));
        //  std::cout << angle << std::endl;
        /*
            Currently angle just increments, implement check
            to get correct direction to move angle in,whether
            increment or decrement to allow visual following
            of rocket's direcotry
         */
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

void Enemy::rocketAim(Rocket rocket, float &normy, float &normx)
{
    float dx, dy, mag;
    dx = (rocket.rect.x + rocket.rect.w / 2) - (rect.x + rect.w / 2); // distance between rocket centres
    dy = (rocket.rect.y + rocket.rect.h / 2) - (rect.y + rect.h / 2); // distance between rocket centresF
    mag = sqrt((dx * dx) + (dy * dy));                                // the magnitude
    normx = (dx / mag) * 30.0f + (rect.x + rect.w / 2);               // aim from ship centre towards rocket centre
    normy = (dy / mag) * 30.0f + (rect.y + rect.h / 2);               // aim from ship centre towards rocket centreF
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
    // SDL_RenderDrawLineF(renderer, (rect.x + rect.w / 2), rect.y, (rect.x + rect.w / 2), (rect.y - 50));

    // Drawing enemy ship aim
    SDL_RenderDrawLineF(renderer, (rect.x + rect.w / 2), (rect.y + rect.h / 2), (normx), (normy));
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    /* SDL_RenderDrawPointF(renderer, (rect.x + rect.w / 2), (rect.y + rect.h / 2));
    SDL_RenderDrawPointF(renderer, (rect.x), (rect.y));
    SDL_RenderDrawPointF(renderer, (rect.x + rect.w), (rect.y));
    SDL_RenderDrawPointF(renderer, (rect.x), (rect.y + rect.h));
    SDL_RenderDrawPointF(renderer, (rect.x + rect.w), (rect.y + rect.h)); */
}

// angle and position should change based on rocket position

Enemy::Enemy()
{
    rect.x = 20;
    rect.y = 180;
    rect.w = 60;
    rect.h = 45;
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