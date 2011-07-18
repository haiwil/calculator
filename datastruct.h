/************************************************* 
               定义各种基本数据结构
               工件，楔块，探头等等 
 ************************************************* */

#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <gtk/gtk.h>

/*保存聚焦法则所需变量*/
/*探头(Probe)*/
typedef struct Probe 
{
	/* 1-D Linear array */
	/*transmitter*/
	gint      D1_D2;
	gint      Pitch_Catch;
    gint      transmi_trans_longi;//设置发送探头 横波 OR 纵波 、
    gint      recev_trans_longi;//设置接收探头 横波 OR 纵波  
	gdouble   pb_skew_angle;
	gdouble   pb_frequency;
	gint      ele_num_pri;//主轴阵元数
	gint      ele_num_sec;//副轴阵元数
    gdouble   pri_axis_pitch;//主轴间距
    gdouble   sec_axis_pitch;
    gdouble   pri_ele_size;
    gdouble   sec_ele_size;
    /*receiver*/ 
    gdouble   pb_skew_angle_r;
	gdouble   pb_frequency_r;
	gint      ele_num_pri_r;//阵元数
	gint      ele_num_sec_r;
    gdouble   pri_axis_pitch_r;//主轴间距
    gdouble   sec_axis_pitch_r;
    gdouble   pri_ele_size_r;
    gdouble   sec_ele_size_r;
    
    gchar     name[20];
} PROBE, *PROBE_P;

/*楔块(Wedge)*/
typedef struct Wedge
{
    gdouble   wg_wedge_angle; /* 楔块角 */
    gdouble   wg_roof_angle;/* 顶角 */
    gdouble   wg_lon_vel;/*纵波声速*/
    gdouble   wg_trans_vel;/*横波声速*/
    gint      wg_density;/* 密度 */
    gdouble   wg_heigh_fir;/*第一阵元高度*/
    gdouble   wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    gdouble   wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    gdouble   wg_pri_axis_reference;/*主轴楔块参考位置*/
    gdouble   wg_sec_axis_reference;/*次轴楔块参考位置*/
    gdouble   wg_length;/*楔块长度*/
    gdouble   wg_width;/*楔块宽度*/
    gdouble   wg_height;/*楔块高度*/
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

/* 波束角选择(Beam angle selection) */
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

/* 聚焦点选择(focal point selection) */
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

/* 样本设定(specimen settings) */
typedef struct specimen
{
    gchar   *name;
    gchar   material[30];
    guint   speci_longitudinal_wave;//样本纵波声速     
    guint   speci_transverse_wave;//样本横波声速 
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
