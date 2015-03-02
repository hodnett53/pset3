//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle width and height
#define PADDLEH 10
#define PADDLEW 50

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // set initial velocity
    double x_velocity = (0.5 - drand48()) * 3;
    double y_velocity = 4.0;
    
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        updateScoreboard(window, label, points); 
        
        move(ball, x_velocity, y_velocity);
        
        pause(10);
        
        // TODO
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, HEIGHT * 4 / 5);
            }
        }
        
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            if (object == paddle)
            {
                if (y_velocity > 0)
                {
                    y_velocity = -y_velocity;
                }
            }
        
            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                y_velocity = -y_velocity;
                bricks--;
                points++;
            }
        }
        
        if(getX(ball) + getWidth(ball) >= getWidth(window))
        {
            x_velocity = -x_velocity;
        }
        
        if (getX(ball) <= 0)
        {
            x_velocity = -x_velocity;
        }
        
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            setLocation(ball, (WIDTH / 2) - RADIUS, (HEIGHT / 3) - RADIUS);
            setLocation(paddle, (WIDTH / 2) - (PADDLEW / 2), HEIGHT * 4 / 5);
            waitForClick();
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO fix columns so it changes when constant changes
    int rowSpacing = 10;
    int colSpacing = 50;
    // array containing the colors of each row
    char* colors[5] = {"RED", "ORANGE", "YELLOW", "GREEN", "BLUE"};
    char* rowColors[ROWS];
    for (int i = 0; i < ROWS; i++)
    {
        rowColors[i] = colors[i % 5];
    }
    
    int y = 50;
    
    // set rows
    for (int i = 0; i < ROWS; i++)
    {
        int x = 2;
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(x + 5, y, 35, 10);
            setColor(brick, rowColors[i]); 
            setFilled(brick, true);
            add(window, brick);
            x += 39;
        }
        y += 15;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    int startY = (HEIGHT / 3) - RADIUS;
    int startX = (WIDTH / 2) - RADIUS;
    GOval ball = newGOval(startX, startY, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int x = (WIDTH / 2) - (PADDLEW / 2);
    int y = HEIGHT * 4 / 5;
    GRect paddle = newGRect(x, y, PADDLEW, PADDLEH);
    setFilled(paddle, true);
    setColor(paddle, "RED");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-50");
    setColor(label, "C0C0C0");
    add(window, label);
    setLocation(label, 185, 300);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
