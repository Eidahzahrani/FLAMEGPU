
/*
 * Copyright 2011 University of Sheffield.
 * Author: Dr Paul Richmond 
 * Contact: p.richmond@sheffield.ac.uk (http://www.paulrichmond.staff.shef.ac.uk)
 *
 * University of Sheffield retain all intellectual property and 
 * proprietary rights in and to this software and related documentation. 
 * Any use, reproduction, disclosure, or distribution of this software 
 * and related documentation without an express license agreement from
 * University of Sheffield is strictly prohibited.
 *
 * For terms of licence agreement please attached licence or view licence 
 * on www.flamegpu.com website.
 * 
 */

#ifndef _FLAMEGPU_FUNCTIONS
#define _FLAMEGPU_FUNCTIONS

#include <header.h>


/**
 * move_A FLAMEGPU Agent Function
 * Automatically generated using functions.xslt
 * @param agent Pointer to an agent structre of type xmachine_memory_A. This represents a single agent instance and can be modified directly.
 * @param rand48 Pointer to the seed list of type RNG_rand48. Must be passed as an arument to the rand48 function for genertaing random numbers on the GPU.
 */
__FLAME_GPU_FUNC__ int move_A(xmachine_memory_A* agent, RNG_rand48* rand48){

    
  
    return 0;
}

/**
 * need_locationB FLAMEGPU Agent Function
 * Automatically generated using functions.xslt
 * @param agent Pointer to an agent structre of type xmachine_memory_A. This represents a single agent instance and can be modified directly.
 * @param locationB_messages  locationB_messages Pointer to input message list of type xmachine_message__list. Must be passed as an argument to the get_first_locationB_message and get_next_locationB_message functions.* @param partition_matrix Pointer to the partition matrix of type xmachine_message_locationB_PBM. Used within the get_first__message and get_next__message functions for spatially partitioned message access.
 */
__FLAME_GPU_FUNC__ int need_locationB(xmachine_memory_A* agent, xmachine_message_locationB_list* locationB_messages, xmachine_message_locationB_PBM* partition_matrix){

    
    /* //Template for input message itteration
     * 
     * xmachine_message_locationB* current_message = get_first_locationB_message(locationB_messages);
     * while (current_message)
     * {
     *     //INSERT MESSAGE PROCESSING CODE HERE
     *     
     *     current_message = get_next_locationB_message(current_message, locationB_messages);
     * }
     */
     
    
  
    return 0;
}

/**
 * send_bindB FLAMEGPU Agent Function
 * Automatically generated using functions.xslt
 * @param agent Pointer to an agent structre of type xmachine_memory_A. This represents a single agent instance and can be modified directly.
 * @param bindB_messages Pointer to output message list of type xmachine_message_bindB_list. Must be passed as an argument to the add_bindB_message function ??.
 */
__FLAME_GPU_FUNC__ int send_bindB(xmachine_memory_A* agent, xmachine_message_bindB_list* bindB_messages){

    
    /* //Template for message output function use 
     * 
     * int id = 0;
     * float x = 0;
     * float y = 0;
     * float z = 0;
     * int type = 0;
     * int state = 0;
     * float closest_point = 0;
     * int closest_id = 0;
     * add_bindB_message(bindB_messages, id, x, y, z, type, state, closest_point, closest_id);
     */
     
     
  
    return 0;
}

/**
 * created_C FLAMEGPU Agent Function
 * Automatically generated using functions.xslt
 * @param agent Pointer to an agent structre of type xmachine_memory_A. This represents a single agent instance and can be modified directly.
 * @param C_agents Pointer to agent list of type xmachine_memory_C_list. This must be passed as an argument to the add_C_agent function to add a new agent.* @param combinedB_messages  combinedB_messages Pointer to input message list of type xmachine_message__list. Must be passed as an argument to the get_first_combinedB_message and get_next_combinedB_message functions.* @param partition_matrix Pointer to the partition matrix of type xmachine_message_combinedB_PBM. Used within the get_first__message and get_next__message functions for spatially partitioned message access.
 */
__FLAME_GPU_FUNC__ int created_C(xmachine_memory_A* agent, xmachine_memory_C_list* C_agents, xmachine_message_combinedB_list* combinedB_messages, xmachine_message_combinedB_PBM* partition_matrix){

    
    /* //Template for input message itteration
     * 
     * xmachine_message_combinedB* current_message = get_first_combinedB_message(combinedB_messages);
     * while (current_message)
     * {
     *     //INSERT MESSAGE PROCESSING CODE HERE
     *     
     *     current_message = get_next_combinedB_message(current_message, combinedB_messages);
     * }
     */
     
    
     /* //Template for agent output functions 
      * 
      * int id = 0;
      * float x = 0;
      * float y = 0;
      * float z = 0;
      * int type = 0;
      * int state = 0;
      * float closest_point = 0;
      * add_C_agent(C_agents, int id, float x, float y, float z, int type, int state, float closest_point);
      */
     
  
    return 0;
}

/**
 * move_B FLAMEGPU Agent Function
 * Automatically generated using functions.xslt
 * @param agent Pointer to an agent structre of type xmachine_memory_B. This represents a single agent instance and can be modified directly.
 * @param rand48 Pointer to the seed list of type RNG_rand48. Must be passed as an arument to the rand48 function for genertaing random numbers on the GPU.
 */
__FLAME_GPU_FUNC__ int move_B(xmachine_memory_B* agent, RNG_rand48* rand48){

    
  
    return 0;
}

/**
 * send_locationB FLAMEGPU Agent Function
 * Automatically generated using functions.xslt
 * @param agent Pointer to an agent structre of type xmachine_memory_B. This represents a single agent instance and can be modified directly.
 * @param locationB_messages Pointer to output message list of type xmachine_message_locationB_list. Must be passed as an argument to the add_locationB_message function ??.
 */
__FLAME_GPU_FUNC__ int send_locationB(xmachine_memory_B* agent, xmachine_message_locationB_list* locationB_messages){

    
    /* //Template for message output function use 
     * 
     * int id = 0;
     * float x = 0;
     * float y = 0;
     * float z = 0;
     * int type = 0;
     * int state = 0;
     * float closest_point = 0;
     * int closest_id = 0;
     * add_locationB_message(locationB_messages, id, x, y, z, type, state, closest_point, closest_id);
     */
     
     
  
    return 0;
}

/**
 * receive_bindB FLAMEGPU Agent Function
 * Automatically generated using functions.xslt
 * @param agent Pointer to an agent structre of type xmachine_memory_B. This represents a single agent instance and can be modified directly.
 * @param bindB_messages  bindB_messages Pointer to input message list of type xmachine_message__list. Must be passed as an argument to the get_first_bindB_message and get_next_bindB_message functions.* @param partition_matrix Pointer to the partition matrix of type xmachine_message_bindB_PBM. Used within the get_first__message and get_next__message functions for spatially partitioned message access.
 */
__FLAME_GPU_FUNC__ int receive_bindB(xmachine_memory_B* agent, xmachine_message_bindB_list* bindB_messages, xmachine_message_bindB_PBM* partition_matrix){

    
    /* //Template for input message itteration
     * 
     * xmachine_message_bindB* current_message = get_first_bindB_message(bindB_messages);
     * while (current_message)
     * {
     *     //INSERT MESSAGE PROCESSING CODE HERE
     *     
     *     current_message = get_next_bindB_message(current_message, bindB_messages);
     * }
     */
     
    
  
    return 0;
}

/**
 * send_combinedB FLAMEGPU Agent Function
 * Automatically generated using functions.xslt
 * @param agent Pointer to an agent structre of type xmachine_memory_B. This represents a single agent instance and can be modified directly.
 * @param combinedB_messages Pointer to output message list of type xmachine_message_combinedB_list. Must be passed as an argument to the add_combinedB_message function ??.
 */
__FLAME_GPU_FUNC__ int send_combinedB(xmachine_memory_B* agent, xmachine_message_combinedB_list* combinedB_messages){

    
    /* //Template for message output function use 
     * 
     * int id = 0;
     * float x = 0;
     * float y = 0;
     * float z = 0;
     * int type = 0;
     * int state = 0;
     * float closest_point = 0;
     * int closest_id = 0;
     * add_combinedB_message(combinedB_messages, id, x, y, z, type, state, closest_point, closest_id);
     */
     
     
  
    return 0;
}

/**
 * move_C FLAMEGPU Agent Function
 * Automatically generated using functions.xslt
 * @param agent Pointer to an agent structre of type xmachine_memory_C. This represents a single agent instance and can be modified directly.
 * @param rand48 Pointer to the seed list of type RNG_rand48. Must be passed as an arument to the rand48 function for genertaing random numbers on the GPU.
 */
__FLAME_GPU_FUNC__ int move_C(xmachine_memory_C* agent, RNG_rand48* rand48){

    
  
    return 0;
}

/**
 * output_locationC FLAMEGPU Agent Function
 * Automatically generated using functions.xslt
 * @param agent Pointer to an agent structre of type xmachine_memory_C. This represents a single agent instance and can be modified directly.
 
 */
__FLAME_GPU_FUNC__ int output_locationC(xmachine_memory_C* agent){

    
  
    return 0;
}

  


#endif //_FLAMEGPU_FUNCTIONS
