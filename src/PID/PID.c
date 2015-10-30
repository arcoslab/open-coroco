/*
 * Copyright (C) 2013 ARCOS-Lab Universidad de Costa Rica
 * Author:      Federico Ruiz Ugalde            <memeruiz@gmail.com>
 * Modified by: Sebastian Chinchilla Gutierrez  <tumacher@gmail.com>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

int pi_mode=0;
bool collected_permission=false;
bool initial_rotor_position_start=false;


float  psi_ref_user=0.0f;
bool   user_input  =false;
float  load_angle=0.0f;


float timer=0.0f;

float   ref_freq_SVM=0.0f;

float   angle_hall1=0.0f;
float   t_e_ref=0.0f;//-1.5;//-0.9f;//-0.15;//-1.6f;
int     print_selection              = 0;
bool    flux_linkage_capture         = false;
int     flux_linkage_capture_counter = 0;
int     flux_linkage_capture_timer   = 0;
int     flux_limit_counter_1=0;
int     flux_limit_counter_2=0;
int     flux_limit_counter_3=0;
int     flux_limit_counter_4=0;
int     flux_limit_counter_5=0;
int     flux_limit_counter_6=0;
int     flux_limit_counter_7=0;
int     flux_limit_counter_8=0;
int     flux_limit_counter_9=0;

float attenuation=1.0f;//MIN_ATTENUATION;
	
uint ticks;
uint period;
uint temp_period;
float est_angle=0;
float duty_a=0.0f;
float duty_b=0.0f;
float duty_c=0.0f;
float ref_freq=0.0f;//1;

float cur_angle=0.0f;
float final_ref_freq=40;

float cmd_angle;
int close_loop=false;
int first_closed=false;
int motor_off=true;//false;

//colecting current command
bool collecting_current=false;
bool collecting_speed  =false;
bool regular_print=true;


int hall_a = 0;
int hall_b = 0;
float hall_freq;
int previous_hall_a=0;
int previous_hall_b=0;
int  old_hall_a;
static int  old_hall_b;

float frequency_direction_two_hall_sensors_AB(float frequency)
{
    static bool first_spin=true;
 
    //float actual_frequency=0.0;
    static float sign=1.0f;

    if (first_spin==true)
    {
        previous_hall_a=hall_a;
        previous_hall_b=hall_b;       
        old_hall_a=hall_a;
        old_hall_b=hall_b;
        first_spin=false; 
    }

    if (old_hall_a!=hall_a || old_hall_b!=hall_b)
    {  
        previous_hall_a=old_hall_a;
        previous_hall_b=old_hall_b;
    }

    if (previous_hall_a!=hall_a || previous_hall_b!=hall_b)
    {
    if      (hall_a==0 && hall_b==0 && previous_hall_a >0 && previous_hall_b==0)    sign =-1.0f;
    else if (hall_a==0 && hall_b >0 && previous_hall_a==0 && previous_hall_b==0)    sign =-1.0f;
    else if (hall_a >0 && hall_b >0 && previous_hall_a==0 && previous_hall_b >0)    sign =-1.0f;
    else if (hall_a >0 && hall_b==0 && previous_hall_a >0 && previous_hall_b >0)    sign =-1.0f;
    else                                                                            sign = 1.0;
    }
    


    old_hall_a=hall_a;
    old_hall_b=hall_b;

/*
if (previous_hall_a!=hall_a || previous_hall_b!=hall_b)
{
    if      (hall_a==0 && hall_b==0 && previous_hall_a >0 && previous_hall_b==0)    sign =-1.0f;
    else if (hall_a==0 && hall_b >0 && previous_hall_a==0 && previous_hall_b==0)    sign =-1.0f;
    else if (hall_a >0 && hall_b >0 && previous_hall_a==0 && previous_hall_b >0)    sign =-1.0f;
    else if (hall_a >0 && hall_b==0 && previous_hall_a >0 && previous_hall_b >0)    sign =-1.0f;
    else                                                                            sign = 1.0;


    }

    previous_hall_a=hall_a;
    previous_hall_b=hall_b;

*/
    return frequency*sign;    
}

void calc_freq(void) 
{
  static bool first=true;
  //static int  hall_a = 0;
  static int  hall_a_last=0;
  static uint last_fall_hall_a_ticks=0;
  static int hall_bounce_counter=0;
  //hall_a=HALL_A();
  //hall_b=HALL_B();
  hall_a=HALL_B();
  hall_b=HALL_A(); 

  if (first) 
  {
    hall_a_last=hall_a;
    ticks=0;
    period=UINT_MAX;
    last_fall_hall_a_ticks=ticks;
    first=false;
  } 

  else 
  {
    //one more period wating for hall change
    ticks++;

    //ticks overflow
    if (ticks == UINT_MAX) 
    {
      ticks=0;
    }

    hall_bounce_counter+=1;
    if ((hall_a_last > 0) && (hall_a == 0) ) 
    {
      //hall falling edge: new cycle
      //new rotor position measurement
      est_angle=0;
      angle_hall1=0.0f;  //***
      hall_bounce_counter=0;

      if (ticks > last_fall_hall_a_ticks) 
      { //updating period
	period=ticks-last_fall_hall_a_ticks;
      } 
      else 
      {
	period=UINT_MAX-last_fall_hall_a_ticks+ticks;
      }
      last_fall_hall_a_ticks=ticks;
    } 

    else 
    {
      //we update period only if is bigger than before
      if (ticks > last_fall_hall_a_ticks) 
      {
	temp_period=ticks-last_fall_hall_a_ticks;
      } 
      else 
      {
	temp_period=UINT_MAX-last_fall_hall_a_ticks+ticks;
      }

      if (temp_period > period) 
      {
	    period=temp_period;
      }
     
      //update estimated current angle
      //est_angle+=2.0f*PI_CTE*TICK_PERIOD/(period/TICK_PERIOD);

      angle_hall1+=360.0f*TICK_PERIOD*CUR_FREQ;//***
      if (angle_hall1>=360.0f)
        { angle_hall1=0.0f; }


      est_angle+=2.0f*PI_CTE/period;///TICK_PERIOD);
      if (est_angle > 2.0f*PI_CTE) 
      {
	est_angle=0.0f;
      }
    }
  }
  hall_a_last=hall_a;
     
}




bool first_dtc=true;
bool dtc_on=true;
#define FREQ_TO_STOP_MOTOR          30.0f
void frequency_input(void)
{

    char cmd_s[50]="";
    char cmd[10]="";
    float value=0.0f;

    if (receive_a_string(cmd_s) )
    {
        printf("%s", cmd_s);
        sscanf(cmd_s, "%s %f", cmd, &value);

        if      (strcmp(cmd, "d") == 0)  {   ref_freq_SVM   =value; }		
        else if (strcmp(cmd, "p") == 0)  {   print_selection=value; }	
    }

      
}


