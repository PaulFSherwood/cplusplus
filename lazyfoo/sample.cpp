void My_Dot::handle_input() 
{ 
int x = 0, y = 0; 

//If a mouse button was pressed 
if( event.type == SDL_MOUSEBUTTONDOWN ) 
{ 
//If the left mouse button was pressed 
if( event.button.button == SDL_BUTTON_LEFT ) 
{ 
//Get the mouse offsets 
x = event.button.x; 
y = event.button.y; 

//temporary object 
My_Dot *some_dot = NULL; 

//If the mouse is over the button 
//mark that 
d_pushed = true; 
for (int i = 0;i < 3;i++) //there are 3 My_Dot objects in My_Dot *array[] 
{ 
//get collission box 
SDL_Rect box = array[i]->GetBox(); 
//if the mouse pointer is within the bounds of collission box 
if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) 
{ 
//put the array element in the temporary object 
some_dot = array[i]; 
} 
} 
} 
} 
//If a mouse button was released 
if( event.type == SDL_MOUSEBUTTONUP ) 
{ 
//If the left mouse button was released 
if( event.button.button == SDL_BUTTON_LEFT ) 
{ 
//mark the left button release 
d_pushed = false; 
//make the object null 
some_dot = NULL; 

} 
} 

if( event.type == SDL_MOUSEMOTION && d_pushed) 
{ 
//Get the mouse offsets 
x = event.motion.x; 
y = event.motion.y; 

//now get the some_dot collission box 
SDL_Rect box = some_dot->GetBox(); 
//and make it track the mouse offset 
box.x += x; 
box.y += y; 

} 
} 
