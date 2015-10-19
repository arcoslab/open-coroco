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

        if (print_selection==15)
        {
            data_electric_angle          = electric_angle;
            data_mechanical_angle        = mechanical_angle;
            data_gear_angle              = gear_angle;
            data_mechanical_frequency    = mechanical_frequency;
            data_gear_frequency          = gear_frequency;
            data_strain_gauge=strain_gauge;
        }
        if (print_selection==16)
        {
            data_hall_a = hall_a;
            data_hall_b = hall_b;
            data_previous_hall_a = previous_hall_a;
            data_previous_hall_b = previous_hall_b;
        }
            data_hall_a = hall_a;
            data_hall_b = hall_b;
            data_previous_hall_a = previous_hall_a;
            data_previous_hall_b = previous_hall_b;
}


union float_union_t
{
    float f;
    char byte[sizeof(float)];
};




/*
void print_regular_data(void)
{
    char checksum=0;
    printf ("X")   ;



    if      (print_selection==0)
    {
        printf ("t")  ;  checksum=           print_float_as_bytes(data_timer                   );
        printf ("r")  ;  checksum=checksum  +print_float_as_bytes(data_ref_freq_SVM            );
        printf ("e")  ;  checksum=checksum  +print_float_as_bytes(data_w_r                     );
        printf ("h")  ;  checksum=checksum  +print_float_as_bytes(data_CUR_FREQ               );
    }
    printf ("k");
    printf ("%c", checksum);
    printf ("m");

}
*/
void print_regular_data(void)
{
    char checksum=0;
    printf ("X")   ;



    if      (print_selection==0)
    {
        //printf ("t")  ;  checksum=           print_float_as_bytes(data_timer                   );
        //printf ("r")  ;  checksum=checksum  +print_float_as_bytes(data_ref_freq_SVM            );
        //printf ("h")  ;  checksum=checksum  +print_float_as_bytes(data_CUR_FREQ               );
        checksum=           print_float_as_bytes(data_timer       );
        checksum=checksum  +print_float_as_bytes(data_ref_freq_SVM);
        checksum=checksum  +print_float_as_bytes(data_CUR_FREQ    );
    }

    //printf ("k");
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
