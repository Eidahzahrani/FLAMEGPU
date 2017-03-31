/*
*
* Functions.c for The Benchmark Model.
*
* Author: Eidah Alzahrani
*
*/
#include <header.h>
#include <vector>

#ifndef _FLAMEGPU_FUNCTIONS
#define _FLAMEGPU_FUNCTIONS
#define AGENT_STATE_DEAD 3
#define AGENT_STATE_BIND 2
#define XMAX 		10.0f
#define YMAX		  	10.0f
#define ZMAX		  	10.0f
#define radius 0.10f//Interaction radius
#define DT 0.01
#define MOVEMENT_TIME_RANGE 15//by increasing this we will make agents move across a larger amount of area and increase the chance that they will be within range of another agent to interact with
#define MIN_MOVEMENT_TIME 5

std::vector<int>Acounter;
std::vector<int>Bcounter;
std::vector<int>Ccounter;
std::vector<int>iteration;
unsigned int h_iteration = 0;
#define AGENT_STATE_A_DEFAULT 1
#define AGENT_STATE_B_DEFAULT 4
#define AGENT_STATE_C_DEFAULT 5
/*
 *init_Function.....
*/
__FLAME_GPU_INIT_FUNC__ void initFunction(){

Acounter.push_back(get_agent_A_moving_A_count());
Bcounter.push_back(get_agent_B_moving_B_count());
Ccounter.push_back(get_agent_C_moving_C_count());
iteration.push_back(0);
fflush(stdout);
 }
/*
 *step_Function.....
*/
__FLAME_GPU_STEP_FUNC__ void stepFunction(){

h_iteration++;
iteration.push_back(h_iteration);
Acounter.push_back(get_agent_A_moving_A_count());
Bcounter.push_back(get_agent_B_moving_B_count());
Ccounter.push_back(get_agent_C_moving_C_count());
fflush(stdout);
}
/*
 *Exit_Function.....
*/
__FLAME_GPU_EXIT_FUNC__ void exitFunction(){

FILE *output = fopen("output.dat",  "w");

fprintf(output, "#IA B C \n ");

for (int i = 0; i < h_iteration; i++){
fprintf(output, "%u %d %d %d \n ", iteration[i],Acounter[i], Bcounter[i], Ccounter[i]);
}
fclose(output);
}
/*
 * move_A FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_A(xmachine_memory_A* agent, RNG_rand48* rand48){

  float vx;
  float vy;
  float vz;

  float x = agent->x;
  float y = agent->y;
  float z = agent->z;

  //generate a new direction by creating a new random velocity
   if (agent->count == 0) {
      float r_x = (rnd(rand48) - 0.5f)*2.0f;
	   float r_y = (rnd(rand48) - 0.5f)*2.0f;
	   float r_z = (rnd(rand48) - 0.5f)*2.0f;

      agent->vx = r_x;
      agent->vy = r_y;
      agent->vz = r_z;

      agent->count = (int)(rnd(rand48)*(float)MOVEMENT_TIME_RANGE) + MIN_MOVEMENT_TIME;
 }
  //get the velocity
      vx=agent->vx ;
      vy=agent->vy ;
      vz=agent->vz ;

  //move according to velocity
      x = x + vx*DT;
      y = y + vy*DT;
      z = z + vz*DT;

//(Clamp position to environment)
   x = x >= XMAX ? XMAX : x;
   x = x <= 0.0 ? 0.0 : x;
   y = y >= YMAX ? YMAX : y;
   y = y <= 0.0 ? 0.0 : y;
   z = z >= ZMAX ? ZMAX : z;
   z = z <= 0.0 ? 0.0 : z;

		agent->x = x;
       agent->y = y;
       agent->z = z;
       agent->count--;
       agent->state = AGENT_STATE_A_DEFAULT;

return 0;
}
/*
 * death_A FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int death_A(xmachine_memory_A* agent){

  return 1;

}
/*
 * move_B FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_B(xmachine_memory_B* agent, RNG_rand48* rand48){

  float vx;
  float vy;
  float vz;

  float x = agent->x;
  float y = agent->y;
  float z = agent->z;

  //generate a new direction by creating a new random velocity
   if (agent->count == 0) {
      float r_x = (rnd(rand48) - 0.5f)*2.0f;
	   float r_y = (rnd(rand48) - 0.5f)*2.0f;
	   float r_z = (rnd(rand48) - 0.5f)*2.0f;

      agent->vx = r_x;
      agent->vy = r_y;
      agent->vz = r_z;

      agent->count = (int)(rnd(rand48)*(float)MOVEMENT_TIME_RANGE) + MIN_MOVEMENT_TIME;
 }
  //get the velocity
      vx=agent->vx ;
      vy=agent->vy ;
      vz=agent->vz ;

  //move according to velocity
      x = x + vx*DT;
      y = y + vy*DT;
      z = z + vz*DT;

//(Clamp position to environment)
   x = x >= XMAX ? XMAX : x;
   x = x <= 0.0 ? 0.0 : x;
   y = y >= YMAX ? YMAX : y;
   y = y <= 0.0 ? 0.0 : y;
   z = z >= ZMAX ? ZMAX : z;
   z = z <= 0.0 ? 0.0 : z;

		agent->x = x;
       agent->y = y;
       agent->z = z;
       agent->count--;
       agent->state = AGENT_STATE_B_DEFAULT;

return 0;
}
/*
 * send_locationB FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_locationB(xmachine_memory_B* agent, xmachine_message_locationB_list* locationB_messages){

    int id, s, t, c_id;
    float x, y, z, c_point;
    id = agent->id;
    x = agent->x;
	 y = agent->y;
    z = agent->z;
    s = agent->state;
	 t = agent->type;
	c_point = agent->closest_point;
c_id = agent->closest_id;
add_locationB_message(locationB_messages, c_id ,c_point , id, s,t, x, y, z );

return 0;
}

/*
 * receive_bindB FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int receive_bindB(xmachine_memory_B* agent, xmachine_message_bindB_list* bindB_messages, xmachine_message_bindB_PBM* partition_matrix){
   int c = 0, nearest_id = 0;
	float nearest_distance = 0.0f;
 xmachine_message_bindB* current_message = get_first_bindB_message(bindB_messages, partition_matrix, agent->x, agent->y, agent->z);

  while (current_message)
   {
     if (current_message->id != agent->id){
        if (agent->id == current_message->closest_id){
           if (c == 0){
               c++;
               nearest_distance = current_message->closest_point;
               nearest_id = current_message->id;
             }
             else if (nearest_distance > current_message->closest_point){
                 nearest_distance = current_message->closest_point;
                 nearest_id = current_message->id;
             }
         }
    }
   current_message = get_next_bindB_message(current_message, bindB_messages, partition_matrix);

   }
 if (c == 1) {
agent->state = AGENT_STATE_DEAD;
agent->closest_point = nearest_distance;
agent->closest_id = nearest_id;
}
  else{
     agent->closest_id = -1;
   }

return 0;
}
/*
 * send_combinedB FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_combinedB(xmachine_memory_B*  agent ,xmachine_message_combinedB_list* combinedB_messages){

int id, s, t, c_id;
float x, y, z, c_point;
id = agent->id;
x = agent->x;
y = agent->y;
z = agent->z;
s = agent->state;
t = agent->type;
c_point = agent->closest_point;
c_id = agent->closest_id;
add_combinedB_message(combinedB_messages, c_id ,c_point , id, s,t, x, y, z );
return 1;
}
/*
 * need_locationB FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int need_locationB(xmachine_memory_A* agent, xmachine_message_locationB_list* locationB_messages, xmachine_message_locationB_PBM* partition_matrix){

    int c = 0, nearest_id;
    float distance_check, x1, x2, y1, y2, z1, z2;
    float nearest_distance = 0.0f;
    x1 = agent->x;
	 y1 = agent->y;
    z1 = agent->z;

xmachine_message_locationB* current_message = get_first_locationB_message(locationB_messages, partition_matrix, agent->x, agent->y, agent->z);

  while (current_message)
   {
      if (current_message->id != agent->id){
           x2 = current_message->x;
	        y2 = current_message->y;
	        z2 = current_message->z;
           distance_check = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) + (z1 - z2)*(z1 - z2));
               if (distance_check <= radius) {
                     if (c == 0) {
                           c++;
                           nearest_distance = distance_check;
                           nearest_id = current_message->id;
                      }
                 else if (nearest_distance > distance_check){
                        nearest_distance = distance_check;
                        nearest_id = current_message->id;
                     }
                  }
          }
   current_message = get_next_locationB_message(current_message, locationB_messages, partition_matrix);

   }
 if (c == 1) {
agent->state = AGENT_STATE_BIND;
agent->closest_point = nearest_distance;
agent->closest_id = nearest_id;
}
  else{
     agent->closest_id = -1;
   }

return 0;
}
/*
 * send_bindB FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_bindB(xmachine_memory_A* agent, xmachine_message_bindB_list* bindB_messages){

int id, s, t, c_id;
	float x, y, z, c_point;
id = agent->id;
	x = agent->x;
y = agent->y;
z = agent->z;
t = agent->type;
	s = agent->state;
	c_point = agent->closest_point;
c_id = agent->closest_id;
add_bindB_message(bindB_messages, c_id ,c_point , id, s,t, x, y, z );
return 0;
}
/*
 * created_C FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int created_C0(xmachine_memory_A* agent, xmachine_memory_C_list* C_agents, xmachine_message_combinedB_list* combinedB_messages, xmachine_message_combinedB_PBM* partition_matrix, RNG_rand48* rand48){
int c = 0;

  xmachine_message_combinedB* current_message = get_first_combinedB_message(combinedB_messages, partition_matrix, agent->x, agent->y, agent->z);

  while (current_message)
  {
      if (current_message->id != agent->id){
      if (current_message->closest_id == agent->id) {
c++;
     }
    else
    {
        current_message->state = AGENT_STATE_DEAD;
    }
    }
      current_message = get_next_combinedB_message(current_message, combinedB_messages, partition_matrix);
         }
         if(c >= 1) {
        agent->state = 6;
        add_C_agent(C_agents, 0.0, 0, agent->count, agent->id,  AGENT_STATE_C_DEFAULT, 1 ,agent->vx, agent->vy, agent->vz, agent->x, agent->y, agent->z );
    }
     return 0;
  }
/*
 * move_C FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_C(xmachine_memory_C* agent, RNG_rand48* rand48){

  float vx;
  float vy;
  float vz;

  float x = agent->x;
  float y = agent->y;
  float z = agent->z;

  //generate a new direction by creating a new random velocity
   if (agent->count == 0) {
      float r_x = (rnd(rand48) - 0.5f)*2.0f;
	   float r_y = (rnd(rand48) - 0.5f)*2.0f;
	   float r_z = (rnd(rand48) - 0.5f)*2.0f;

      agent->vx = r_x;
      agent->vy = r_y;
      agent->vz = r_z;

      agent->count = (int)(rnd(rand48)*(float)MOVEMENT_TIME_RANGE) + MIN_MOVEMENT_TIME;
 }
  //get the velocity
      vx=agent->vx ;
      vy=agent->vy ;
      vz=agent->vz ;

  //move according to velocity
      x = x + vx*DT;
      y = y + vy*DT;
      z = z + vz*DT;

//(Clamp position to environment)
   x = x >= XMAX ? XMAX : x;
   x = x <= 0.0 ? 0.0 : x;
   y = y >= YMAX ? YMAX : y;
   y = y <= 0.0 ? 0.0 : y;
   z = z >= ZMAX ? ZMAX : z;
   z = z <= 0.0 ? 0.0 : z;

		agent->x = x;
       agent->y = y;
       agent->z = z;
       agent->count--;
       agent->state = AGENT_STATE_C_DEFAULT;

return 0;
}
#endif //_FLAMEGPU_FUNCTIONS
