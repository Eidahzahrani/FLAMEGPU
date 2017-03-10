#ifndef _FLAMEGPU_FUNCTIONS
#define _FLAMEGPU_FUNCTIONS
#include <header.h>
#define AGENT_STATE_DEAD 3
#define AGENT_STATE_BIND 2
#define XMAX 		10.0f
#define YMAX		  	10.0f
#define ZMAX		  	10.0f
//Interaction radius
#define radius 1.0f
#define SPEED 0.005f
#define AGENT_STATE_A_DEFAULT 1
#define AGENT_STATE_B_DEFAULT4
#define AGENT_STATE_C_DEFAULT5
#define AGENT_STATE_F_DEFAULT6
#define AGENT_STATE_D_DEFAULT7
#define AGENT_STATE_K_DEFAULT8
#define AGENT_STATE_E_DEFAULT 1
#define AGENT_STATE_G_DEFAULT4
#define AGENT_STATE_N_DEFAULT5
#define AGENT_STATE_L_DEFAULT6
#define AGENT_STATE_S_DEFAULT7
#define AGENT_STATE_A_DEFAULT 1
/*
 * move_A FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_A(xmachine_memory_A* agent, RNG_rand48* rand48){

  float x1 = agent->x;
  float y1 = agent->y;
  float z1 = agent->z;
  float random = rnd(rand48);
   if (random < 0.1f) {
		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;
 }
	else if (random < 0.2f) {
      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;
 }
	else if (random < 0.3f) {
      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;
 }
	else if (random < 0.4f){
      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;
 }
   else if (random < 0.5f) {
	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;
 }
   else  if (random < 0.6f){
    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;
 }
/* update memory with new parameters*/
		agent->x = x1;
       agent->y = y1;
       agent->z = z1;
       agent->state = AGENT_STATE_A_DEFAULT;

return 0;
}
/*
 * deathA FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int deathA(xmachine_memory_A* agent){

  return 1;

}
/*
 * move_B FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_B(xmachine_memory_B* agent, RNG_rand48* rand48){

  float x1 = agent->x;
  float y1 = agent->y;
  float z1 = agent->z;
  float random = rnd(rand48);
   if (random < 0.1f) {
		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;
 }
	else if (random < 0.2f) {
      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;
 }
	else if (random < 0.3f) {
      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;
 }
	else if (random < 0.4f){
      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;
 }
   else if (random < 0.5f) {
	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;
 }
   else  if (random < 0.6f){
    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;
 }
/* update memory with new parameters*/
		agent->x = x1;
       agent->y = y1;
       agent->z = z1;
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
add_locationB_message(locationB_messages, id, x, y, z, t, s, c_point, c_id);

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
__FLAME_GPU_FUNC__ int send_combinedB(xmachine_memory_B* agent){

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
        if (agent->type == 2){
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
add_bindB_message(bindB_messages, id, x, y, z, t, s, c_point, c_id);
return 0;
}
/*
 * move_C FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_C(xmachine_memory_C* agent, RNG_rand48* rand48){

  float x1 = agent->x;
  float y1 = agent->y;
  float z1 = agent->z;
  float random = rnd(rand48);
   if (random < 0.1f) {
		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;
 }
	else if (random < 0.2f) {
      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;
 }
	else if (random < 0.3f) {
      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;
 }
	else if (random < 0.4f){
      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;
 }
   else if (random < 0.5f) {
	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;
 }
   else  if (random < 0.6f){
    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;
 }
/* update memory with new parameters*/
		agent->x = x1;
       agent->y = y1;
       agent->z = z1;
       agent->state = AGENT_STATE_C_DEFAULT;

return 0;
}
/*
 * send_locationC FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_locationC(xmachine_memory_C* agent, xmachine_message_locationC_list* locationC_messages){

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
add_locationC_message(locationC_messages, id, x, y, z, t, s, c_point, c_id);

return 0;
}

/*
 * receive_bindC FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int receive_bindC(xmachine_memory_C* agent, xmachine_message_bindC_list* bindC_messages, xmachine_message_bindC_PBM* partition_matrix){
   int c = 0, nearest_id = 0;
	float nearest_distance = 0.0f;
 xmachine_message_bindC* current_message = get_first_bindC_message(bindC_messages, partition_matrix, agent->x, agent->y, agent->z);

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
   current_message = get_next_bindC_message(current_message, bindC_messages, partition_matrix);

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
 * send_combinedC FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_combinedC(xmachine_memory_C* agent){

return 1;
}
/*
 * need_locationC FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int need_locationC(xmachine_memory_A* agent, xmachine_message_locationC_list* locationC_messages, xmachine_message_locationC_PBM* partition_matrix){

    int c = 0, nearest_id;
    float distance_check, x1, x2, y1, y2, z1, z2;
    float nearest_distance = 0.0f;
    x1 = agent->x;
	 y1 = agent->y;
    z1 = agent->z;

xmachine_message_locationC* current_message = get_first_locationC_message(locationC_messages, partition_matrix, agent->x, agent->y, agent->z);

  while (current_message)
   {
     if (current_message->id != agent->id){
        if (agent->type == 2){
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
             }
   current_message = get_next_locationC_message(current_message, locationC_messages, partition_matrix);

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
 * send_bindC FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_bindC(xmachine_memory_A* agent, xmachine_message_bindC_list* bindC_messages){

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
add_bindC_message(bindC_messages, id, x, y, z, t, s, c_point, c_id);
return 0;
}
/*
 * move_F FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_F(xmachine_memory_F* agent, RNG_rand48* rand48){

  float x1 = agent->x;
  float y1 = agent->y;
  float z1 = agent->z;
  float random = rnd(rand48);
   if (random < 0.1f) {
		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;
 }
	else if (random < 0.2f) {
      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;
 }
	else if (random < 0.3f) {
      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;
 }
	else if (random < 0.4f){
      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;
 }
   else if (random < 0.5f) {
	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;
 }
   else  if (random < 0.6f){
    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;
 }
/* update memory with new parameters*/
		agent->x = x1;
       agent->y = y1;
       agent->z = z1;
       agent->state = AGENT_STATE_F_DEFAULT;

return 0;
}
/*
 * send_locationF FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_locationF(xmachine_memory_F* agent, xmachine_message_locationF_list* locationF_messages){

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
add_locationF_message(locationF_messages, id, x, y, z, t, s, c_point, c_id);

return 0;
}

/*
 * receive_bindF FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int receive_bindF(xmachine_memory_F* agent, xmachine_message_bindF_list* bindF_messages, xmachine_message_bindF_PBM* partition_matrix){
   int c = 0, nearest_id = 0;
	float nearest_distance = 0.0f;
 xmachine_message_bindF* current_message = get_first_bindF_message(bindF_messages, partition_matrix, agent->x, agent->y, agent->z);

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
   current_message = get_next_bindF_message(current_message, bindF_messages, partition_matrix);

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
 * send_combinedF FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_combinedF(xmachine_memory_F* agent){

return 1;
}
/*
 * need_locationF FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int need_locationF(xmachine_memory_A* agent, xmachine_message_locationF_list* locationF_messages, xmachine_message_locationF_PBM* partition_matrix){

    int c = 0, nearest_id;
    float distance_check, x1, x2, y1, y2, z1, z2;
    float nearest_distance = 0.0f;
    x1 = agent->x;
	 y1 = agent->y;
    z1 = agent->z;

xmachine_message_locationF* current_message = get_first_locationF_message(locationF_messages, partition_matrix, agent->x, agent->y, agent->z);

  while (current_message)
   {
     if (current_message->id != agent->id){
        if (agent->type == 2){
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
             }
   current_message = get_next_locationF_message(current_message, locationF_messages, partition_matrix);

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
 * send_bindF FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_bindF(xmachine_memory_A* agent, xmachine_message_bindF_list* bindF_messages){

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
add_bindF_message(bindF_messages, id, x, y, z, t, s, c_point, c_id);
return 0;
}
/*
 * move_D FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_D(xmachine_memory_D* agent, RNG_rand48* rand48){

  float x1 = agent->x;
  float y1 = agent->y;
  float z1 = agent->z;
  float random = rnd(rand48);
   if (random < 0.1f) {
		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;
 }
	else if (random < 0.2f) {
      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;
 }
	else if (random < 0.3f) {
      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;
 }
	else if (random < 0.4f){
      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;
 }
   else if (random < 0.5f) {
	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;
 }
   else  if (random < 0.6f){
    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;
 }
/* update memory with new parameters*/
		agent->x = x1;
       agent->y = y1;
       agent->z = z1;
       agent->state = AGENT_STATE_D_DEFAULT;

return 0;
}
/*
 * created_D FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int created_D(xmachine_memory_A* agent, xmachine_memory_D_list* D_agents, RNG_rand48* rand48){
  float r = rnd(rand48);
  int rr = r * 2147483647;
  agent->state = 6;
add_D_agent(D_agents, rr, agent->x, agent->y, agent->z, 1, AGENT_STATE_D_DEFAULT, 0.0, 0);
  return 0;
}
/*
 * move_K FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_K(xmachine_memory_K* agent, RNG_rand48* rand48){

  float x1 = agent->x;
  float y1 = agent->y;
  float z1 = agent->z;
  float random = rnd(rand48);
   if (random < 0.1f) {
		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;
 }
	else if (random < 0.2f) {
      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;
 }
	else if (random < 0.3f) {
      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;
 }
	else if (random < 0.4f){
      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;
 }
   else if (random < 0.5f) {
	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;
 }
   else  if (random < 0.6f){
    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;
 }
/* update memory with new parameters*/
		agent->x = x1;
       agent->y = y1;
       agent->z = z1;
       agent->state = AGENT_STATE_K_DEFAULT;

return 0;
}
/*
 * created_K FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int created_K(xmachine_memory_A* agent, xmachine_memory_K_list* K_agents, RNG_rand48* rand48){
  float r = rnd(rand48);
  int rr = r * 2147483647;
  agent->state = 6;
add_K_agent(K_agents, rr, agent->x, agent->y, agent->z, 1, AGENT_STATE_K_DEFAULT, 0.0, 0);
  return 0;
}
#define AGENT_STATE_E_DEFAULT 1
/*
 * move_E FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_E(xmachine_memory_E* agent, RNG_rand48* rand48){

  float x1 = agent->x;
  float y1 = agent->y;
  float z1 = agent->z;
  float random = rnd(rand48);
   if (random < 0.1f) {
		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;
 }
	else if (random < 0.2f) {
      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;
 }
	else if (random < 0.3f) {
      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;
 }
	else if (random < 0.4f){
      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;
 }
   else if (random < 0.5f) {
	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;
 }
   else  if (random < 0.6f){
    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;
 }
/* update memory with new parameters*/
		agent->x = x1;
       agent->y = y1;
       agent->z = z1;
       agent->state = AGENT_STATE_E_DEFAULT;

return 0;
}
/*
 * deathE FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int deathE(xmachine_memory_E* agent){

  return 1;

}
/*
 * move_G FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_G(xmachine_memory_G* agent, RNG_rand48* rand48){

  float x1 = agent->x;
  float y1 = agent->y;
  float z1 = agent->z;
  float random = rnd(rand48);
   if (random < 0.1f) {
		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;
 }
	else if (random < 0.2f) {
      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;
 }
	else if (random < 0.3f) {
      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;
 }
	else if (random < 0.4f){
      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;
 }
   else if (random < 0.5f) {
	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;
 }
   else  if (random < 0.6f){
    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;
 }
/* update memory with new parameters*/
		agent->x = x1;
       agent->y = y1;
       agent->z = z1;
       agent->state = AGENT_STATE_G_DEFAULT;

return 0;
}
/*
 * send_locationG FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_locationG(xmachine_memory_G* agent, xmachine_message_locationG_list* locationG_messages){

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
add_locationG_message(locationG_messages, id, x, y, z, t, s, c_point, c_id);

return 0;
}

/*
 * receive_bindG FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int receive_bindG(xmachine_memory_G* agent, xmachine_message_bindG_list* bindG_messages, xmachine_message_bindG_PBM* partition_matrix){
   int c = 0, nearest_id = 0;
	float nearest_distance = 0.0f;
 xmachine_message_bindG* current_message = get_first_bindG_message(bindG_messages, partition_matrix, agent->x, agent->y, agent->z);

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
   current_message = get_next_bindG_message(current_message, bindG_messages, partition_matrix);

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
 * send_combinedG FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_combinedG(xmachine_memory_G* agent){

return 1;
}
/*
 * need_locationG FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int need_locationG(xmachine_memory_E* agent, xmachine_message_locationG_list* locationG_messages, xmachine_message_locationG_PBM* partition_matrix){

    int c = 0, nearest_id;
    float distance_check, x1, x2, y1, y2, z1, z2;
    float nearest_distance = 0.0f;
    x1 = agent->x;
	 y1 = agent->y;
    z1 = agent->z;

xmachine_message_locationG* current_message = get_first_locationG_message(locationG_messages, partition_matrix, agent->x, agent->y, agent->z);

  while (current_message)
   {
     if (current_message->id != agent->id){
        if (agent->type == 2){
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
             }
   current_message = get_next_locationG_message(current_message, locationG_messages, partition_matrix);

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
 * send_bindG FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_bindG(xmachine_memory_E* agent, xmachine_message_bindG_list* bindG_messages){

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
add_bindG_message(bindG_messages, id, x, y, z, t, s, c_point, c_id);
return 0;
}
/*
 * move_N FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_N(xmachine_memory_N* agent, RNG_rand48* rand48){

  float x1 = agent->x;
  float y1 = agent->y;
  float z1 = agent->z;
  float random = rnd(rand48);
   if (random < 0.1f) {
		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;
 }
	else if (random < 0.2f) {
      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;
 }
	else if (random < 0.3f) {
      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;
 }
	else if (random < 0.4f){
      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;
 }
   else if (random < 0.5f) {
	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;
 }
   else  if (random < 0.6f){
    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;
 }
/* update memory with new parameters*/
		agent->x = x1;
       agent->y = y1;
       agent->z = z1;
       agent->state = AGENT_STATE_N_DEFAULT;

return 0;
}
/*
 * send_locationN FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_locationN(xmachine_memory_N* agent, xmachine_message_locationN_list* locationN_messages){

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
add_locationN_message(locationN_messages, id, x, y, z, t, s, c_point, c_id);

return 0;
}

/*
 * receive_bindN FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int receive_bindN(xmachine_memory_N* agent, xmachine_message_bindN_list* bindN_messages, xmachine_message_bindN_PBM* partition_matrix){
   int c = 0, nearest_id = 0;
	float nearest_distance = 0.0f;
 xmachine_message_bindN* current_message = get_first_bindN_message(bindN_messages, partition_matrix, agent->x, agent->y, agent->z);

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
   current_message = get_next_bindN_message(current_message, bindN_messages, partition_matrix);

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
 * send_combinedN FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_combinedN(xmachine_memory_N* agent){

return 1;
}
/*
 * need_locationN FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int need_locationN(xmachine_memory_E* agent, xmachine_message_locationN_list* locationN_messages, xmachine_message_locationN_PBM* partition_matrix){

    int c = 0, nearest_id;
    float distance_check, x1, x2, y1, y2, z1, z2;
    float nearest_distance = 0.0f;
    x1 = agent->x;
	 y1 = agent->y;
    z1 = agent->z;

xmachine_message_locationN* current_message = get_first_locationN_message(locationN_messages, partition_matrix, agent->x, agent->y, agent->z);

  while (current_message)
   {
     if (current_message->id != agent->id){
        if (agent->type == 2){
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
             }
   current_message = get_next_locationN_message(current_message, locationN_messages, partition_matrix);

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
 * send_bindN FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int send_bindN(xmachine_memory_E* agent, xmachine_message_bindN_list* bindN_messages){

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
add_bindN_message(bindN_messages, id, x, y, z, t, s, c_point, c_id);
return 0;
}
/*
 * move_L FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_L(xmachine_memory_L* agent, RNG_rand48* rand48){

  float x1 = agent->x;
  float y1 = agent->y;
  float z1 = agent->z;
  float random = rnd(rand48);
   if (random < 0.1f) {
		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;
 }
	else if (random < 0.2f) {
      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;
 }
	else if (random < 0.3f) {
      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;
 }
	else if (random < 0.4f){
      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;
 }
   else if (random < 0.5f) {
	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;
 }
   else  if (random < 0.6f){
    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;
 }
/* update memory with new parameters*/
		agent->x = x1;
       agent->y = y1;
       agent->z = z1;
       agent->state = AGENT_STATE_L_DEFAULT;

return 0;
}
/*
 * created_L FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int created_L(xmachine_memory_E* agent, xmachine_memory_L_list* L_agents, RNG_rand48* rand48){
  float r = rnd(rand48);
  int rr = r * 2147483647;
  agent->state = 6;
add_L_agent(L_agents, rr, agent->x, agent->y, agent->z, 1, AGENT_STATE_L_DEFAULT, 0.0, 0);
  return 0;
}
/*
 * move_S FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int move_S(xmachine_memory_S* agent, RNG_rand48* rand48){

  float x1 = agent->x;
  float y1 = agent->y;
  float z1 = agent->z;
  float random = rnd(rand48);
   if (random < 0.1f) {
		x1 = x1 <= 0.0 ? 0.0 : x1 - SPEED;
 }
	else if (random < 0.2f) {
      x1 = x1 >= XMAX ? XMAX : x1 + SPEED;
 }
	else if (random < 0.3f) {
      y1 = y1 >= YMAX ? YMAX : y1 + SPEED;
 }
	else if (random < 0.4f){
      y1 = y1 <= 0.0 ? 0.0 : y1 - SPEED;
 }
   else if (random < 0.5f) {
	   z1 = z1 >= ZMAX ? ZMAX : z1 + SPEED;
 }
   else  if (random < 0.6f){
    z1 = z1 <= 0.0 ? 0.0 : z1 - SPEED;
 }
/* update memory with new parameters*/
		agent->x = x1;
       agent->y = y1;
       agent->z = z1;
       agent->state = AGENT_STATE_S_DEFAULT;

return 0;
}
/*
 * created_S FLAMEGPU Agent Function
*/
__FLAME_GPU_FUNC__ int created_S(xmachine_memory_E* agent, xmachine_memory_S_list* S_agents, RNG_rand48* rand48){
  float r = rnd(rand48);
  int rr = r * 2147483647;
  agent->state = 6;
add_S_agent(S_agents, rr, agent->x, agent->y, agent->z, 1, AGENT_STATE_S_DEFAULT, 0.0, 0);
  return 0;
}
#endif //_FLAMEGPU_FUNCTIONS
