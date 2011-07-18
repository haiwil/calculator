/************************************************* 
               ������ֻ������ݽṹ
               ������Ш�飬̽ͷ�ȵ� 
 ************************************************* */

#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <gtk/gtk.h>

/*����۽������������*/
/*̽ͷ(Probe)*/
typedef struct Probe 
{
	/* 1-D Linear array */
	/*transmitter*/
	gint      D1_D2;
	gint      Pitch_Catch;
    gint      transmi_trans_longi;//���÷���̽ͷ �Შ OR �ݲ� ��
    gint      recev_trans_longi;//���ý���̽ͷ �Შ OR �ݲ�  
	gdouble   pb_skew_angle;
	gdouble   pb_frequency;
	gint      ele_num_pri;//������Ԫ��
	gint      ele_num_sec;//������Ԫ��
    gdouble   pri_axis_pitch;//������
    gdouble   sec_axis_pitch;
    gdouble   pri_ele_size;
    gdouble   sec_ele_size;
    /*receiver*/ 
    gdouble   pb_skew_angle_r;
	gdouble   pb_frequency_r;
	gint      ele_num_pri_r;//��Ԫ��
	gint      ele_num_sec_r;
    gdouble   pri_axis_pitch_r;//������
    gdouble   sec_axis_pitch_r;
    gdouble   pri_ele_size_r;
    gdouble   sec_ele_size_r;
    
    gchar     name[20];
} PROBE, *PROBE_P;

/*Ш��(Wedge)*/
typedef struct Wedge
{
    gdouble   wg_wedge_angle; /* Ш��� */
    gdouble   wg_roof_angle;/* ���� */
    gdouble   wg_lon_vel;/*�ݲ�����*/
    gdouble   wg_trans_vel;/*�Შ����*/
    gint      wg_density;/* �ܶ� */
    gdouble   wg_heigh_fir;/*��һ��Ԫ�߶�*/
    gdouble   wg_pri_elem_offset_fir;/*��һ������Ԫƫ��*/
    gdouble   wg_sec_elem_offset_fir;/*��һ������Ԫƫ��*/
    gdouble   wg_pri_axis_reference;/*����Ш��ο�λ��*/
    gdouble   wg_sec_axis_reference;/*����Ш��ο�λ��*/
    gdouble   wg_length;/*Ш�鳤��*/
    gdouble   wg_width;/*Ш����*/
    gdouble   wg_height;/*Ш��߶�*/
    gdouble   wg_separation;
    
    gchar     name[50];
}WEDGE, *WEDGE_P;

/*scanner*/
typedef struct scanner
{
    gdouble scan_axis_off;  
    gdouble index_axis_off;
    gdouble usound_axis_off;    
    
    gdouble scan_axis_ori;  
    gdouble index_axis_ori;
    gdouble usound_axis_ori;
}SCANNER ,*SCANNER_P;

/* ������ѡ��(Beam angle selection) */
typedef struct Beam_angle
{
    gdouble   beam_pri_steer_angle_start;
    gdouble   beam_pri_steer_angle_stop;
    gdouble   beam_pri_steer_angle_resolution;
    //
    gdouble   beam_sec_steer_angle_start;
    gdouble   beam_sec_steer_angle_stop;
    gdouble   beam_sec_steer_angle_resolution;
    //
    gdouble   beam_refrac_angle_start;  
    gdouble   beam_refrac_angle_stop;
    gdouble   beam_refrac_angle_resolution; 
    // 
    gdouble   beam_skew_angle_start;  
    gdouble   beam_skew_angle_stop;
    gdouble   beam_skew_angle_resolution;
    gint      beam_type;
    gint      beam_angle_sel;
}BEAM_ANGLE, *BEAM_ANGLE_P;

/* �۽���ѡ��(focal point selection) */
typedef struct Focal_point
{
    gint      focal_focus_type;
    gdouble   focal_focus_point_start;
    gdouble   focal_focus_point_stop; 
    gdouble   focal_focus_point_resolution; 
    
    gdouble   offset_start;
    gdouble   offset_end;
    gdouble   depth_start;
    gdouble   depth_end;
}FOCAL_POINT, *FOCAL_POINT_P;

/*element selection*/
typedef struct element_sel
{
    gint primary_axis_s;  
    gint primary_axis_e;
    gint primary_axis_r;    
    
    gint seconary_axis_s;  
    gint seconary_axis_e;
    gint seconary_axis_r;
    
    gint pri_axis_ape;
    gint sec_axis_ape;
    gint connection;
    
    gint linear;
}ELEMENT_SEL ,*ELEMENT_SEL_P;

/* �����趨(specimen settings) */
typedef struct specimen
{
    gchar   *name;
    gchar   material[30];
    guint   speci_longitudinal_wave;//�����ݲ�����     
    guint   speci_transverse_wave;//�����Შ���� 
    //
    gdouble speci_length_flat;
    gdouble speci_height_flat;
    gdouble speci_width_flat;  
    //
    gdouble speci_inside_cylindrical;
    gdouble speci_outside_cylindrical;
    gdouble speci_length_cylindrical; 
    gint    flat_cylindrical;
    //
    gchar   Inspection_od_id[2];  
}SPECIMEN,*SPECIMEN_P;

/*location*/
typedef struct location
{
    gdouble center_x;
    gdouble center_y;
    gdouble center_z;
    
    gdouble rotation_x;
    gdouble rotation_y;
    gdouble rotation_z;
    
    gdouble translation_x;
    gdouble translation_y;
    gdouble translation_z;
    
    gint st1;
    gint st2;
    gint st3;    
}LOCATION ,*LOCATION_P;

/*projected squence*/
typedef struct project
{
    gint     circum_axial;
    gboolean state;      
}PROJECT ,*PROJECT_P;

/*law parameters*/
typedef struct law_parameters
{
    gchar Version[32];
    gint  N_laws;
    
    gint N_ActiveElements;
	gint frequency;
	gint cycle;
	gint sumgain;
	gint mode;
	gint filter;
	gint R_angle;
	gint S_angle;
	gint T_first;
	gint R_first;
	gint Scan_offset;
	gint Index_offset;
	gint G_delay;
	gint F_depth;
	gint M_velocity;
}LAW;

/*element parameters*/
typedef struct element_parameters
{
    gint E_number;
	gint FL_gain;
	gint T_delay;
	gint R_delay;
	gint Amplitude;
	gint P_width;
}ELEMENT,*ELEMENT_P;

/*database--probe*/
typedef struct db_probe
{
  gint     db_index;
  gchar    *name;
  gdouble  skewangle;
  gdouble  frequency;
  gint     number_pri;
  gdouble  pri_axis_pitch;
  gdouble  pri_ele_size;
  gint     number_sec;
  gdouble  sec_axis_pitch;  
  gdouble  sec_ele_size;
}DB_PROBE,*DB_PROBE_P;

/*database--wedge*/
typedef struct db_wedge
{
  gint     db_index;
  gchar    *name;
  gdouble  wedge_angle;
  gdouble  roof_angle;
  gdouble  vel_longi;
  gdouble  height;
  gdouble  first_offset;
  gdouble  sec_offset;  
}DB_WEDGE,*DB_WEDGE_P;

typedef struct material
{
   gint    index;
   gchar   *name;
   gchar   *state;
   gdouble longi_vel;
   gdouble trans_vel;
   gdouble density;     
}MATERIAL, *MATERIAL_P;

#endif
