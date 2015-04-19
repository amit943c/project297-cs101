#include<iostream>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_primitives.h>
#include<ctime>
#include<cstdlib>
#include<sstream>
#include<string>

using namespace std;

#define ScrnWdth 800

#define ScrnHght 600

int score=0;
// A function which will allow to check whether it collide with enemy or touchs coin to eat.
bool collision(float px,float py,float ex,float ey,int width,int height)
{

    if( px + width<ex || px>ex+width || py + height<ey || py>ey+height)
    {

        return false;
    }

    else
    {
        return true;
    }
}








int main()
{
    ALLEGRO_DISPLAY* first;  // will create a display
    ALLEGRO_BITMAP* Hero;    // will reserve memory for hero
    ALLEGRO_BITMAP* villain;
    const float FPS = 60.0;
    enum Direction { DOWN, LEFT, RIGHT, UP };
    ALLEGRO_BITMAP* background;
    ALLEGRO_BITMAP* coin;
    ALLEGRO_FONT* font=al_load_font("stocky.ttf",10,10);   // load font which we can use in the executed window

    al_set_new_display_flags(ALLEGRO_RESIZABLE);            // will make the window resizable so that user can resize according to his choice

    if(!al_init())
    {
        // will create error message box


        al_show_native_message_box(0 , "Display", "ERROR" , "Your library is not Working!",0,0 );

    }
    if(!first)
    {
        al_show_native_message_box(0, "Error", 0, "Could not create Allegro Display", 0, 0);
    }


    bool out=true, active=false,draw=true, show=false;;
    int dir=DOWN;
    float sourceX=0;
    float x=10 , y=10;
    float p=200;
    float q=200;
    int score=0;

    bool side=true;
    al_install_keyboard(); // will install keyboard for user input

    al_install_mouse();    // will install mouse for user input

    al_init_primitives_addon();// will allow to draw primitives on game screen

    al_init_image_addon(); // will initialize image addon

    al_init_ttf_addon();  // will initialize font addon

    al_install_audio();    // will initialize audio addon

    al_init_acodec_addon();

    villain=al_load_bitmap("villain1.png"); // load images into allocated memory

    Hero= al_load_bitmap("hero.png");

    background=al_load_bitmap("back.jpg");

    coin=al_load_bitmap("coin.png");

    font=al_load_font("stocky.ttf",30,30); // loads font into allegro variable


    ALLEGRO_SAMPLE* sound3= al_load_sample("back1.wav"); // loads sound into allegro variable

    al_reserve_samples(1);

    ALLEGRO_TIMER* timer1 =  al_create_timer(1.0/60.0);

    first=al_create_display(ScrnWdth,ScrnHght); // creates display of width ScrnWdth,height of ScrnHght
    bool go = false;

    bool over = true;

    // windows settings
    al_set_window_position(first,100,400);

    al_set_window_title(first, "DEAD SOULS");

    ALLEGRO_EVENT_QUEUE* select1= al_create_event_queue(); // create an event called select1

    ALLEGRO_FONT* font1= al_load_font("leadcoat.ttf",100,100);

    // registering all events created

    al_register_event_source(select1, al_get_display_event_source(first)); // registers display

    al_register_event_source(select1, al_get_mouse_event_source()); // registers mouse

    al_register_event_source(select1, al_get_timer_event_source(timer1)); // registers timer

    al_hide_mouse_cursor(first);


    ALLEGRO_EVENT_QUEUE* select2=al_create_event_queue();

    al_register_event_source(select2, al_get_keyboard_event_source()); // registers keyboard event

    al_register_event_source(select2, al_get_timer_event_source(timer1));

    al_register_event_source(select2, al_get_mouse_event_source());

    ALLEGRO_KEYBOARD_STATE keystate1;

    al_start_timer(timer1); // starts timer


    while(!go)
    {
        ALLEGRO_EVENT choose1;
        al_wait_for_event( select2, &choose1 );

        ALLEGRO_EVENT choose;
        al_wait_for_event(select1,&choose);

        if(choose.type==ALLEGRO_EVENT_DISPLAY_CLOSE) // checks whether display is closed
        {
            go=true;
            break;
        }

        al_get_keyboard_state(&keystate1); // take input from keyboard


        if(choose1.type == ALLEGRO_EVENT_KEY_UP) // checks whether key is pressed

        {


            switch(choose1.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE : // press esc to close game
                go=true;
                break;

            }

        }
        else   if(choose1.type== ALLEGRO_EVENT_TIMER)
        {
            if(choose1.timer.source==timer1)
            {

                if( al_key_down(&keystate1 , ALLEGRO_KEY_Q)) // press Q to quit game
                {
                    go=true;
                    out=true;

                    std::cout<< "GOOD BYE!! SEE U AGAIN!!"<<endl;
                }

                else if( al_key_down(&keystate1, ALLEGRO_KEY_ENTER))
                {
                    go=true;
                    side=false;

                }

                al_draw_text(font1 , al_map_rgb(255,67,0) , 400 , 25 , ALLEGRO_ALIGN_CENTRE , "DEAD SOULS"); // draws images on buffer window

                al_draw_text(font , al_map_rgb(100,207,0) , 400 , 195 , ALLEGRO_ALIGN_CENTRE , "Press ENTER To Play"); // draws text on buffer window

                al_draw_text(font , al_map_rgb(100,207,0) , 400 , 345 , ALLEGRO_ALIGN_CENTRE , "OR Press 'Q' to QUIT ");

                al_play_sample(sound3,2.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);

                al_flip_display(); // flips buffer on to game screen

                al_clear_to_color(al_map_rgb(0,50,80)); // it clears whole window
            }
        }
    }

    // destroying whole allocated memory

    al_destroy_display(first);

    al_destroy_timer(timer1);

    al_destroy_event_queue(select1);

    al_destroy_event_queue(select2);

    al_destroy_sample(sound3);




















    if(!side)
    {

        ALLEGRO_DISPLAY* help;

        help=al_create_display(ScrnWdth,ScrnHght);

        al_set_window_position(help,100,400);

        al_set_window_title(help, "DEAD SOULS");

        ALLEGRO_FONT* font4=al_load_font("lead.ttf",30,30);



        if(!help)
        {
            al_show_native_message_box(0, "Error", 0, "Could not create Allegro Display", 0, 0);
        }

        ALLEGRO_EVENT_QUEUE* select5=al_create_event_queue();

        al_register_event_source(select5, al_get_display_event_source(help));

        al_register_event_source(select5, al_get_keyboard_event_source());

        ALLEGRO_KEYBOARD_STATE keystate3;

        while(!side)
        {
            ALLEGRO_EVENT choose4;
            al_wait_for_event(select5,&choose4);

            al_get_keyboard_state(&keystate3);


            if(choose4.type == ALLEGRO_EVENT_KEY_UP)

            {


                switch(choose4.keyboard.keycode)
                {
                case ALLEGRO_KEY_ESCAPE :

                    side=true;
                    over=true;

                    std::cout<< "GOOD BYE!! SEE U AGAIN!!"<<endl;

                    break;

                case ALLEGRO_KEY_SPACE :

                    side=true;
                    out=false;

                }
            }


            al_draw_text(font4 , al_map_rgb(255,207,0) , 400 , 25 , ALLEGRO_ALIGN_CENTRE ,"INSTRUCTIONS");

            al_draw_text(font4 , al_map_rgb(100,207,0) , 400 , 100 , ALLEGRO_ALIGN_CENTRE , "Use “UP” arrow key for moving in upward direction");

            al_draw_text(font4 , al_map_rgb(100,207,0) , 400 , 175 , ALLEGRO_ALIGN_CENTRE , "Use “DOWN” arrow key for moving in downward direction.");

            al_draw_text(font4, al_map_rgb(100,207,0) , 400 , 250 , ALLEGRO_ALIGN_CENTRE , "Use “LEFT”arrow key for moving in left direction.");

            al_draw_text(font4 , al_map_rgb(100,207,0) , 400 , 325 , ALLEGRO_ALIGN_CENTRE , "Use “RIGHT” arrow key for moving in right direction. ");

            al_draw_text(font4 , al_map_rgb(255,207,0) , 400 , 450 , ALLEGRO_ALIGN_RIGHT , " WARNING:                               ");

            al_draw_text(font4 , al_map_rgb(100,207,0) , 300 , 490 , ALLEGRO_ALIGN_CENTRE ,"Don't touch enemies else game will over.");

            al_draw_text(font4 , al_map_rgb(100,207,0) , 400 , 400 , ALLEGRO_ALIGN_CENTRE ,"Your aim is to collect the coins");

            al_draw_text(font4 , al_map_rgb(255,255,255) , 650 , 570 , ALLEGRO_ALIGN_CENTRE ,"Press SPACE To Continue");

            al_draw_text(font4 , al_map_rgb(255,255,255) , 370, 570 , ALLEGRO_ALIGN_RIGHT,"Press ESC To Discontinue the Game");

            al_flip_display();

            al_clear_to_color(al_map_rgb(10,80,80));
        }


        al_destroy_display(help);

        al_destroy_event_queue(select5);

        al_destroy_font(font4);



    }





















    if(out==false)
    {

        ALLEGRO_DISPLAY* GameScreen;

        GameScreen = al_create_display( ScrnWdth, ScrnHght);

        if(!GameScreen)
        {
            al_show_native_message_box(0, "Error", 0, "Could not create Allegro Display", 0, 0);
        }

        al_set_new_display_flags(ALLEGRO_RESIZABLE);

        al_set_window_position(GameScreen,100,400);

        al_set_window_title(GameScreen, "DEAD SOULS");

        ALLEGRO_TIMER* timer =  al_create_timer(1.0/FPS);
        const float frameFPS = 10.0;

        ALLEGRO_TIMER* frameTimer=al_create_timer(1.0/frameFPS);

        ALLEGRO_SAMPLE* sound= al_load_sample("beep5.wav");
        ALLEGRO_SAMPLE* sound1= al_load_sample("beep18.wav");
        ALLEGRO_SAMPLE* sound4= al_load_sample("back2.wav");

        al_reserve_samples(3);

        ALLEGRO_KEYBOARD_STATE keystate;

        ALLEGRO_EVENT_QUEUE* run=al_create_event_queue();

        al_register_event_source(run, al_get_keyboard_event_source());

        al_register_event_source(run, al_get_timer_event_source(timer));

        al_register_event_source(run,al_get_timer_event_source(frameTimer));

        al_register_event_source(run, al_get_display_event_source(GameScreen));

        al_register_event_source(run, al_get_mouse_event_source());


        al_start_timer(timer);

        al_start_timer(frameTimer);

        // start of game loop

        while( !out )
        {
            ALLEGRO_EVENT run1;
            al_wait_for_event( run, &run1 );
            al_get_keyboard_state(&keystate);


            if(run1.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                out=true;
                show=true;


            }

            else if(run1.type == ALLEGRO_EVENT_KEY_UP)

            {


                switch(run1.keyboard.keycode)
                {
                case ALLEGRO_KEY_ESCAPE :

                    out=true;

                    show=true;

                    break;

                }

            }
            else   if(run1.type== ALLEGRO_EVENT_TIMER)
            {
                if(run1.timer.source==timer)
                {
                    active=true;


                    if( al_key_down(&keystate , ALLEGRO_KEY_DOWN)) // checks whether key is pressed
                    {
                        if(y<550)
                        {
                            y+=8;
                            dir = DOWN;

                        }
                        al_play_sample(sound,1.0,0,2.0,ALLEGRO_PLAYMODE_ONCE,0);

                    }
                    else if( al_key_down(&keystate , ALLEGRO_KEY_UP))
                    {
                        if(y>0)
                        {
                            y-=8;
                            dir= UP;
                        }
                        al_play_sample(sound,1.0,0,2.0,ALLEGRO_PLAYMODE_ONCE,0);
                    }
                    else if( al_key_down(&keystate , ALLEGRO_KEY_RIGHT))
                    {
                        if(x<770)
                        {
                            x+=8;
                            dir = RIGHT;
                        }
                        al_play_sample(sound,1.0,0,2.0,ALLEGRO_PLAYMODE_ONCE,0); // plays sound when key is pressed
                    }
                    else if( al_key_down(&keystate , ALLEGRO_KEY_LEFT))
                    {
                        if(x>6)
                        {
                            x-=8;
                            dir = LEFT;
                        }
                        al_play_sample(sound,1.0,0,2.0,ALLEGRO_PLAYMODE_ONCE,0);

                    }

                    else active=false;
                }


                else if(run1.timer.source == frameTimer)
                {
                    if (active)
                    {
                        sourceX += al_get_bitmap_width(Hero) / 4;
                    }
                    else sourceX =0;

                    if(sourceX >= al_get_bitmap_width(Hero))
                    {
                        sourceX=0;
                    }
                }
                draw=true;

            }



            // drawing all images on game window

            if(draw)
            {

                float j=rand()%(600-10+1)+10;
                float k=rand()%(600-30+1);



                al_draw_bitmap(background,0,0,0);

                al_draw_bitmap_region(Hero ,sourceX, dir*48,32,48,x, y , 0);

                if(collision(x,y,p,q,14,16))
                {


                    p=j;

                    q=k;

                    al_play_sample(sound1,1.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);

                    score+=5;

                    std::cout<<score<<endl;

                }

                al_convert_mask_to_alpha(coin,al_map_rgb(255,255,255));

                if(q>2&& p<770 && p > 2 && q < 570)
                {
                    al_draw_bitmap(coin,p,q,0);
                }
                al_draw_bitmap(villain,p-80,q+50,0);

                if(collision(x,y,p-80,q+50,14,16)) // checks whether collision is happened
                {


                    out=true;

                }

                al_draw_bitmap(villain,p+200,q+400,0);

                if(collision(x,y,p+200,q+400,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p+50,q+100,0);

                if(collision(x,y,p+50,q+100,14,16))
                {


                    out=true;

                }


                al_draw_bitmap(villain,p+89,q+200,0);

                if(collision(x,y,p+89,q+200,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p+300,q+200,0); // draws image on game window

                if(collision(x,y,p+300,q+200,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p-100,q-289,0);

                if(collision(x,y,p-100,q-289,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p-200,q,0);

                if(collision(x,y,p-200,q,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p-460,q-550,0);

                if(collision(x,y,p-460,q-550,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p-300,q+90,0);


                if(collision(x,y,p-300,q+90,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p+400,q-90,0);

                if(collision(x,y,p+400,q-90,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p+90,q-250,0);


                if(collision(x,y,p+90,q-250,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p-30,q+400,0);

                if(collision(x,y,p-30,q+400,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p+100,q+300,0);

                if(collision(x,y,p+100,q+300,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p+98,q-200,0);

                if(collision(x,y,p+98,q-200,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p,q+280,0);

                if(collision(x,y,p,q+280,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p+12,q+390,0);

                if(collision(x,y,p+12,q+390,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p-23,q+38,0);

                if(collision(x,y,p-23,q+38,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p+89,q+89,0);

                if(collision(x,y,p+89,q+89,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p-55,q-30,0);

                if(collision(x,y,p-55,q-30,14,16))
                {


                    out=true;

                }

                al_draw_bitmap(villain,p+30,q-30,0);


                if(collision(x,y,p+30,q-30,14,16))
                {


                    out=true;

                }


                al_flip_display();

                al_clear_to_color(al_map_rgb(255,255,255));

            }
        }

        over=0;
        std::cout<<"Your Score is "<< score <<endl;

        std::ostringstream convert;

        convert << score;

        al_play_sample(sound4,3.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);

        al_destroy_bitmap(Hero);

        al_destroy_timer(timer);

        al_destroy_timer(frameTimer);

        al_destroy_event_queue(run);

        al_destroy_display(GameScreen);

        al_destroy_bitmap(coin);

        al_destroy_sample(sound1);

        al_destroy_sample(sound);

        al_destroy_sample(sound4);




















        if(!over && !show)
        {


            ALLEGRO_DISPLAY* last;

            last=al_create_display(ScrnWdth,ScrnHght);

            al_set_window_position(last,100,400);

            al_set_window_title(last, "DEAD SOULS");

            if(!last)
            {
                al_show_native_message_box(0, "Error", 0, "Could not create Allegro Display", 0, 0);
            }

            ALLEGRO_FONT* font2;

            font2= al_load_font("coat.ttf",25,25);

            ALLEGRO_SAMPLE* sound3= al_load_sample("ack.wav");

            al_reserve_samples(1);



            ALLEGRO_FONT* font1= al_load_font("leadcoat.ttf",100,100);

            ALLEGRO_EVENT_QUEUE* select4=al_create_event_queue();

            al_register_event_source(select4, al_get_display_event_source(last));

            al_register_event_source(select4, al_get_keyboard_event_source());

            ALLEGRO_KEYBOARD_STATE keystate2;

            while(!over)
            {
                ALLEGRO_EVENT choose3;
                al_wait_for_event(select4,&choose3);

                al_get_keyboard_state(&keystate2);


                if(choose3.type == ALLEGRO_EVENT_KEY_UP)

                {


                    switch(choose3.keyboard.keycode)
                    {
                    case ALLEGRO_KEY_ESCAPE :

                        over=true;

                        std::cout<< "GOOD BYE!! SEE U AGAIN!!"<<endl;

                        break;

                    }
                }

                al_play_sample(sound3,2.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,0);

                al_draw_text(font1 , al_map_rgb(255,67,0) , 400 , 25 , ALLEGRO_ALIGN_CENTRE , "CREDITS");

                al_draw_text(font2 , al_map_rgb(100,207,0) , 400 , 175 , ALLEGRO_ALIGN_CENTRE , "AMIT KR. TOMAR     140010029");

                al_draw_text(font2 , al_map_rgb(100,207,0) , 400 , 250 , ALLEGRO_ALIGN_CENTRE , "S VINAY KUMAR      140110079");

                al_draw_text(font2 , al_map_rgb(100,207,0) , 400 , 325 , ALLEGRO_ALIGN_CENTRE , "VIJAY RAJ KHINCHI  140010022 ");

                al_draw_text(font2 , al_map_rgb(100,207,0) , 400 , 400 , ALLEGRO_ALIGN_CENTRE , "D SAI BALAJI       140010052  ");

                al_draw_text(font1 , al_map_rgb(255,70,0) , 300 , 490 , ALLEGRO_ALIGN_CENTRE ,"SCORE : ");

                al_draw_text(font1 , al_map_rgb(255,70,0) , 520 , 490 , ALLEGRO_ALIGN_CENTRE ,convert.str().c_str());

                al_draw_text(font2 , al_map_rgb(255,255,255) , 690 , 570 , ALLEGRO_ALIGN_CENTRE ,"Press ESC To EXIT");


                al_flip_display();

                al_clear_to_color(al_map_rgb(0,70,70));
            }



            // destroying all allocated memory
            al_destroy_font(font);

            al_destroy_font(font1);

            al_destroy_font(font2);

            al_destroy_display(last);

            al_destroy_event_queue(select4);

            al_destroy_sample(sound3);
        }
        return 0;

    }

    // end of the game

}


