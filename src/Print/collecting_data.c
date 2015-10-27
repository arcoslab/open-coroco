bool collecting_sensorless_data = true;
bool transmitting_to_python = false;

#define SAMPLES 300
#define COLLECTING_SPEED_DELAY 0

float hall_angle=0.0f;
float PID_angle[SAMPLES];
bool  inductance_measure=true;
int collected_pointer=0;
bool serial_print_collected_data=false; 


void collecting_floating_data(void)
{
  if (collecting_sensorless_data==true)
  {
    collecting_sensorless_data=false;
    collecting_samples();
    transmitting_to_python=true;
  }
    timer=timer+1.0f;
    if (timer<0.0f)
        timer=0.0f;
    if (timer >=16777210.0f)
        timer =0.0f;
}

void collecting_samples(void)
{

        data_V_s           = V_s;
        data_w_r           = w_r;
        data_ref_freq_SVM  = ref_freq_SVM;


        data_CUR_FREQ  =hall_freq;
        data_U_d       =U_d;

        data_i_sA =i_sA;
        data_i_sB =i_sB;
        data_U_d  =U_d;

        data_i_sD=i_sD;
        data_i_sQ=i_sQ;



        data_V_sD=V_sD;
        data_V_sQ=V_sQ;
        data_V_s =V_s;
        data_cita_V_s=cita_V_s;
        data_cita_V_s_relative_angle=cita_V_s;


        data_required_V_sD      =required_V_sD;
        data_required_V_sQ      =required_V_sQ;
        data_required_V_s       =required_V_s;
        data_required_cita_V_s  =required_cita_V_s;

        data_psi_sD=psi_sD;
        data_psi_sQ=psi_sQ;
        data_psi_s =psi_s;
        data_psi_alpha=psi_alpha;
        data_psi_s_alpha_SVM=psi_s_alpha_SVM;
        data_timer=timer;

        data_timer=timer;


        data_t_e=t_e;
        

        data_psi_s_ref=psi_s_ref;
        data_t_e_ref=t_e_ref;

        data_d_psi=d_psi;
        data_d_te=d_te;
        data_psi_delta_percentage=psi_delta_percentage;
        data_t_e_delta_percentage=t_e_delta_percentage;

        data_w_r=w_r;   

        data_phase_advance_SVM=phase_advance_SVM;
        data_V_s_ref_relative_angle=V_s_ref_relative_angle;

        data_pi_control_SVM	=SVM_pi_control;
        data_rotating_angle_SVM =psi_rotating_angle_SVM;
        data_pi_max=pi_max;

        data_strain_gauge=strain_gauge;
        data_electric_angle          = electric_angle;
        data_mechanical_angle        = mechanical_angle;
        data_gear_angle              = gear_angle;
        data_mechanical_frequency    = mechanical_frequency;
        data_gear_frequency          = gear_frequency;


        data_strain_gauge=strain_gauge;
        data_hall_a = hall_a;
        data_hall_b = hall_b;
        data_previous_hall_a = previous_hall_a;
        data_previous_hall_b = previous_hall_b;

    //-------values calculated with i neglected-----
        data_psi_sD_i_neglected=psi_sD_NO_i;
        data_psi_sQ_i_neglected=psi_sQ_NO_i;
        data_wr_i_neglected=w_r_NO_i;
        
}


union float_union_t
{
    float f;
    char byte[sizeof(float)];
};





void print_regular_data(void)
{
    char checksum=0;
    printf ("X")   ;

    if      (print_selection==0)
    {
        checksum=           print_float_as_bytes(data_timer       );
        //checksum=checksum+           print_float_as_bytes(ref_freq_SVM       );
        checksum=checksum  +print_float_as_bytes(data_CUR_FREQ);
    }
    else if (print_selection==1)
    {
        checksum=           print_float_as_bytes(data_i_sD );
        checksum=checksum  +print_float_as_bytes(data_i_sQ );
    }
    else if (print_selection==2)
    {
        checksum=           print_float_as_bytes(data_V_sD );
        checksum=checksum  +print_float_as_bytes(data_V_sQ );
    }
    else if (print_selection==3)
    {
        checksum=           print_float_as_bytes(data_timer       );
        checksum=checksum  +print_float_as_bytes(data_U_d         );
    }
    else if (print_selection==4)
    {
        checksum=           print_float_as_bytes(data_psi_sD);
        checksum=checksum  +print_float_as_bytes(data_psi_sQ);
    }
    else if (print_selection==5)
    {
        checksum=           print_float_as_bytes(data_timer                   );
        checksum=checksum  +print_float_as_bytes(data_t_e                     );
    }
    else if (print_selection==6)
    {
        checksum=           print_float_as_bytes(data_timer                   );
        checksum=checksum  +print_float_as_bytes(data_pi_control_SVM          );
    }
    else if (print_selection==7)
    {
        checksum=           print_float_as_bytes(data_timer       );
        checksum=checksum  +print_float_as_bytes(data_strain_gauge);
    }
        else if (print_selection==8)
    {
        checksum=           print_float_as_bytes(stiffness                    );
        checksum=checksum  +print_float_as_bytes(damping                      );
    }
        else if (print_selection==9)
    {
        checksum=           print_float_as_bytes(data_timer                   );
        checksum=checksum  +print_float_as_bytes(data_electric_angle          );
    }
    else if (print_selection==10)
    {
        checksum=           print_float_as_bytes(data_timer);
        checksum=checksum  +print_float_as_bytes(data_i_sA );
    }
    else if (print_selection==11)
    {
        checksum=           print_float_as_bytes(data_timer);
        checksum=checksum  +print_float_as_bytes(data_i_sB );
    }
    else if (print_selection==12)
    {
        checksum=           print_float_as_bytes(data_timer);
        checksum=checksum  +print_float_as_bytes(-data_i_sA-data_i_sB         );
    }
    else if (print_selection==13)
    {
        checksum=           print_float_as_bytes(data_timer);
        checksum=checksum  +print_float_as_bytes(data_w_r);
    }
    else if (print_selection==14)
    {
        checksum=           print_float_as_bytes(data_timer);
        checksum=checksum  +print_float_as_bytes(data_wr_i_neglected);
    }
    else if (print_selection==15)
    {
        checksum=           print_float_as_bytes(data_psi_sD_i_neglected);
        checksum=checksum  +print_float_as_bytes(data_psi_sQ_i_neglected);
    }
    else if (print_selection==16)
    {
        checksum=           print_float_as_bytes(data_timer);
        checksum=checksum  +print_float_as_bytes(data_te_i_neglected);
    }
    printf ("%c", checksum);
    printf ("m");

}


char print_float_as_bytes(float floating_value)
{
    unsigned int i=0;
    char checksum=0;
    union float_union_t float_byte;

    //hack for serial transmition (transmiting 0.01f causes a transmition error)
    if (floating_value==0.01f)
        floating_value= 0.010000001f;

    float_byte.f=floating_value;

    while (i<sizeof(float))
    {
      printf("%c",float_byte.byte[i]);
      checksum=checksum+float_byte.byte[i];
      i++;
    }
    return checksum;
}





void print_ascii_data(void)
{
    if      (print_selection==0)    printf("%10.0f %3.2f \n",data_timer,data_CUR_FREQ);
    else if (print_selection==1)    printf(" %3.2f %3.2f \n",data_i_sD,data_i_sQ);
    else if (print_selection==2)    printf(" %3.2f %3.2f \n",data_V_sD,data_V_sQ);
    else if (print_selection==3)    printf("%10.0f %3.2f \n",data_timer,data_U_d);
    else if (print_selection==4)    printf("%3.6f %3.6f \n",data_psi_sD,data_psi_sQ);
    else if (print_selection==5)    printf("%10.0f %3.3f \n",data_timer,data_t_e);
    else if (print_selection==6)    printf("%10.0f %3.5f \n",data_timer,data_pi_control_SVM);
    else if (print_selection==7)    printf("%10.0f %3.3f \n",data_timer,data_strain_gauge);
    else if (print_selection==8)    printf("%10.2f %10.2f \n",stiffness,damping);
    else if (print_selection==9)    printf("%10.0f %10.2f \n",data_timer,data_electric_angle);
    else if (print_selection==10)   printf("%10.0f %3.2f \n",data_timer,data_i_sA);
    else if (print_selection==11)   printf("%10.0f %3.2f \n",data_timer,data_i_sB);
    else if (print_selection==12)   printf("%10.0f %3.2f \n",data_timer,-data_i_sA-data_i_sB);
    else if (print_selection==13)   printf("%10.0f %3.3f \n",data_timer,data_w_r);
    else if (print_selection==14)   printf("%10.0f %3.3f \n",data_timer,data_wr_i_neglected);
    else if (print_selection==15)    printf("%3.6f %3.6f \n",data_psi_sD_i_neglected,data_psi_sQ_i_neglected);
    else if (print_selection==16)    printf("%10.0f %3.3f \n",data_timer,data_te_i_neglected);
    else                            printf("%10.0f %10.0f \n",data_timer,data_timer);  
}


