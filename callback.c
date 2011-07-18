/************************************************* 
               信号回调函数 
 ************************************************* */

#include "drawui.h"
#define CALL_DEBUG 0

/*信号回调函数*/ 
/*probe*/
void D1_D2(GtkWidget *widget, gpointer data);
void transmi_trans_longi(GtkWidget *widget, gpointer data);
void recev_trans_longi(GtkWidget *widget, gpointer data);
void Pitch_Catch(GtkWidget *widget, gpointer data);
void WedgeSeparation(GtkWidget *widget, gpointer data);
void probe_skew(GtkWidget *widget, gpointer data);
void probe_frequency(GtkWidget *widget, gpointer data);
void probe_ele_num(GtkWidget *widget, gpointer data);
void probe_sec_ele_num(GtkWidget *widget, gpointer data);//
void probe_pri_axis_pitch(GtkWidget *widget, gpointer data);
void probe_sec_axis_pitch(GtkWidget *widget, gpointer data);
void probe_pri_elem_size(GtkWidget *widget, gpointer data);
void probe_sec_elem_size(GtkWidget *widget, gpointer data);
void probe_skew_r(GtkWidget *widget, gpointer data);
void probe_frequency_r(GtkWidget *widget, gpointer data);
void probe_ele_num_r(GtkWidget *widget, gpointer data);
void probe_sec_ele_num_r(GtkWidget *widget, gpointer data);//
void probe_pri_axis_pitch_r(GtkWidget *widget, gpointer data);
void probe_sec_axis_pitch_r(GtkWidget *widget, gpointer data);
void probe_pri_elem_size_r(GtkWidget *widget, gpointer data);
void probe_sec_elem_size_r(GtkWidget *widget, gpointer data);
void SequenceSelect2DR(GtkWidget *widget, gpointer data);
void SequenceSelect2DT(GtkWidget *widget, gpointer data);
/*wedge*/
//发送 
void wg_wedge_angle(GtkWidget *widget, gpointer data);
void wg_roof_angle(GtkWidget *widget, gpointer data);
void wg_lon_vel(GtkWidget *widget, gpointer data);
void wg_trans_vel(GtkWidget *widget, gpointer data);
void wg_density(GtkWidget *widget, gpointer data);
void wg_heigh_fir(GtkWidget *widget, gpointer data);
void wg_pri_elem_offset_fir(GtkWidget *widget, gpointer data);
void wg_sec_elem_offset_fir(GtkWidget *widget, gpointer data);
void wg_pri_axis_reference(GtkWidget *widget, gpointer data);
void wg_sec_axis_reference(GtkWidget *widget, gpointer data);
void wg_length(GtkWidget *widget, gpointer data);
void wg_width(GtkWidget *widget, gpointer data);
void wg_height(GtkWidget *widget, gpointer data);
void import_material(GtkWidget *widget, gpointer data);///////////
void selection_material(GtkTreeSelection *selection, gpointer data);
//接收 
void wg_wedge_angle_r(GtkWidget *widget, gpointer data);
void wg_roof_angle_r(GtkWidget *widget, gpointer data);
void wg_lon_vel_r(GtkWidget *widget, gpointer data);
void wg_trans_vel_r(GtkWidget *widget, gpointer data);
void wg_density_r(GtkWidget *widget, gpointer data);
void wg_heigh_fir_r(GtkWidget *widget, gpointer data);
void wg_pri_elem_offset_fir_r(GtkWidget *widget, gpointer data);
void wg_sec_elem_offset_fir_r(GtkWidget *widget, gpointer data);
void wg_pri_axis_reference_r(GtkWidget *widget, gpointer data);
void wg_sec_axis_reference_r(GtkWidget *widget, gpointer data);
void wg_length_r(GtkWidget *widget, gpointer data);
void wg_width_r(GtkWidget *widget, gpointer data);
void wg_height_r(GtkWidget *widget, gpointer data);
/*scanner*/
void scan_axis_off(GtkWidget *widget, gpointer data);
void index_axis_off(GtkWidget *widget, gpointer data);
void usound_axis_off(GtkWidget *widget, gpointer data);
void scan_axis_ori(GtkWidget *widget, gpointer data);
void index_axis_ori(GtkWidget *widget, gpointer data);
void usound_axis_ori(GtkWidget *widget, gpointer data);
/* beam angle selection */
void beam_pri_steer_angle_start(GtkWidget *widget, gpointer data);
void beam_pri_steer_angle_stop(GtkWidget *widget, gpointer data);
void beam_pri_steer_angle_resolution(GtkWidget *widget, gpointer data);
void beam_sec_steer_angle_start(GtkWidget *widget, gpointer data);
void beam_sec_steer_angle_stop(GtkWidget *widget, gpointer data);
void beam_sec_steer_angle_resolution(GtkWidget *widget, gpointer data);
void beam_refrac_angle_start(GtkWidget *widget, gpointer data);
void beam_refrac_angle_stop(GtkWidget *widget, gpointer data);
void beam_refrac_angle_resolution(GtkWidget *widget, gpointer data);
void beam_skew_angle_start(GtkWidget *widget, gpointer data);
void beam_skew_angle_stop(GtkWidget *widget, gpointer data);
void beam_skew_angle_resolution(GtkWidget *widget, gpointer data);
void beam_angle_sel(GtkWidget *widget, gpointer data);
void beam_type(GtkWidget *widget, gpointer data);
void btn_beam(GtkWidget *widget, gpointer data);
/* focal selection selection */
void focal_focus_type(GtkWidget *widget, gpointer data);
void focal_focus_point_start(GtkWidget *widget, gpointer data);
void focal_focus_point_stop(GtkWidget *widget, gpointer data);
void focal_focus_point_resolution(GtkWidget *widget, gpointer data);
void offset_start(GtkWidget *widget, gpointer data);
void offset_end(GtkWidget *widget, gpointer data);
void depth_start(GtkWidget *widget, gpointer data);
void depth_end(GtkWidget *widget, gpointer data);
/*element selection*/
void primary_axis_s(GtkWidget *widget, gpointer data);
void primary_axis_e(GtkWidget *widget, gpointer data);
void primary_axis_r(GtkWidget *widget, gpointer data);
void seconary_axis_s(GtkWidget *widget, gpointer data);
void seconary_axis_e(GtkWidget *widget, gpointer data);
void seconary_axis_r(GtkWidget *widget, gpointer data);
void pri_axis_ape(GtkWidget *widget, gpointer data);
void sec_axis_ape(GtkWidget *widget, gpointer data);
void connection(GtkWidget *widget, gpointer data);
/* specimen settings*/
void speci_longitudinal_wave(GtkWidget *widget, gpointer data);
void speci_transverse_wave(GtkWidget *widget, gpointer data);
void speci_length(GtkWidget *widget, gpointer data);
void speci_height(GtkWidget *widget, gpointer data);
void speci_width(GtkWidget *widget, gpointer data);
void speci_setting_def(GtkWidget *widget, gpointer data);
void Inspection_od(GtkWidget *widget, gpointer data);
void Inspection_id(GtkWidget *widget, gpointer data);
void Inspection_od_id(GtkWidget *widget, gpointer data);
/*location*/
void rotation1(GtkWidget *widget, gpointer data);
void rotation2(GtkWidget *widget, gpointer data);
void rotation3(GtkWidget *widget, gpointer data);
void axis0(GtkWidget *widget, gpointer data);
void axis1(GtkWidget *widget, gpointer data);
void axis2(GtkWidget *widget, gpointer data);
void axis3(GtkWidget *widget, gpointer data);
void axis4(GtkWidget *widget, gpointer data);
void axis5(GtkWidget *widget, gpointer data);
void axis6(GtkWidget *widget, gpointer data);
void axis7(GtkWidget *widget, gpointer data);
void axis8(GtkWidget *widget, gpointer data);
/*projected squence*/
void circum_axial(GtkWidget *widget, gpointer data);



/*----probe----*/
void D1_D2(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->D1_D2=gtk_combo_box_get_active(GTK_COMBO_BOX(p->linear_wg[0])); 
     
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     switch(p->probe_p->D1_D2)
     {
         case 0:
#if CALL_DEBUG
              g_printf("1-D \n");
#endif                          
              
              gtk_widget_hide(GTK_WIDGET(p->D2ShowHBox[0]));
              gtk_widget_hide(GTK_WIDGET(p->D2ShowHBox[1]));
              gtk_widget_hide(GTK_WIDGET(p->D2ShowHBox[2]));
              gtk_widget_hide(GTK_WIDGET(p->D2ShowHBox[3]));
              p->beam_angle->beam_angle_sel = 1;
              p->element_sel->sec_axis_ape = 1;
              p->selection = 0;
              break;
         case 1:
              gtk_widget_show(GTK_WIDGET(p->D2ShowHBox[0]));
              gtk_widget_show(GTK_WIDGET(p->D2ShowHBox[1]));
              gtk_widget_show(GTK_WIDGET(p->D2ShowHBox[2]));
              gtk_widget_show(GTK_WIDGET(p->D2ShowHBox[3]));
              p->element_sel->sec_axis_ape = p->probe_p->ele_num_sec;
              p->beam_angle->beam_angle_sel = 3;
              
              p->selection = 1;
#if CALL_DEBUG
              g_printf("2-D \n");
#endif               
              
              break;                       
     }
     
     force_updata(p); 
}

void transmi_trans_longi(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->transmi_trans_longi=gtk_combo_box_get_active(GTK_COMBO_BOX(p->linear_wg[1]));
     switch(p->probe_p->transmi_trans_longi)
     {
         case 0:
#if CALL_DEBUG
              g_printf("Transvers\n");
#endif               
              
              break;
         case 1:
#if CALL_DEBUG
              g_printf("Longitudinal \n");
#endif               
              
              break;                       
     }
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void recev_trans_longi(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->recev_trans_longi=gtk_combo_box_get_active(GTK_COMBO_BOX(p->linear_wg[2]));
     switch(p->probe_p->recev_trans_longi)
     {
         case 0:
#if CALL_DEBUG
              g_printf("Transvers\n");
#endif               
              
              break;
         case 1:
#if CALL_DEBUG
              g_printf("Longitudinal \n");
#endif               
              
              break;                       
     }
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void Pitch_Catch(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     gint i;
     p->probe_p->Pitch_Catch  = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(widget)) ;

     gtk_widget_set_sensitive(p->SequenceComm[1],p->probe_p->Pitch_Catch);
     gtk_widget_set_sensitive (p->check_btn_p[2], p->probe_p->Pitch_Catch);
     gtk_widget_set_sensitive (p->check_btn_p[4], p->probe_p->Pitch_Catch);
     for(i=0;i<=18;i+=2)
     {
           gtk_widget_set_sensitive (p->entry[i], p->probe_p->Pitch_Catch);
     }
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void WedgeSeparation(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->wedge_r->wg_separation = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_skew(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->pb_skew_angle=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[3]));
     gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[4]),p->probe_p->pb_skew_angle);
	 p->probe_p->pb_skew_angle_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[4]));
	 p->DrawResult = 0 ;
	 p->is_draw_focus = 1;
	 gtk_widget_set_sensitive (p->combo, p->DrawResult);
	 force_updata(p);
}

void probe_frequency(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->pb_frequency=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[5]));
     gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[6]),p->probe_p->pb_frequency);
	 p->probe_p->pb_frequency_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[6]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_ele_num(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->ele_num_pri=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[7]));
     gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[8]),p->probe_p->ele_num_pri);
	 p->probe_p->ele_num_pri_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[8]));
	 //
	 p->element_sel->pri_axis_ape = p->probe_p->ele_num_pri;
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_sec_ele_num(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->ele_num_sec = gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[15]));
     gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[16]),p->probe_p->ele_num_sec);
	 p->probe_p->ele_num_sec_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[16]));
	 p->element_sel->sec_axis_ape = p->probe_p->ele_num_sec;
//	 p->element_sel->pri_axis_ape = 
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_sec_ele_num_r(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->ele_num_sec_r = gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[16]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_pri_axis_pitch(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->pri_axis_pitch=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[9]));
     gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[10]),p->probe_p->pri_axis_pitch);
	 p->probe_p->pri_axis_pitch_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[10]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_pri_elem_size(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->pri_ele_size=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[11]));
     gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[12]),p->probe_p->pri_ele_size);
	 p->probe_p->pri_ele_size_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[12]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_sec_elem_size(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->sec_ele_size=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[13]));
     gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[14]),p->probe_p->sec_ele_size);
	 p->probe_p->sec_ele_size_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[14]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_skew_r(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->pb_skew_angle_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[4]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_frequency_r(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->pb_frequency_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[6]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_ele_num_r(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->ele_num_pri_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[8]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_pri_axis_pitch_r(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->pri_axis_pitch_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[10]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_pri_elem_size_r(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->pri_ele_size_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[12]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_sec_elem_size_r(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->sec_ele_size_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[14]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_sec_axis_pitch(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->sec_axis_pitch = gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[17])) ;  
     gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[18]),p->probe_p->sec_axis_pitch);
	 p->probe_p->sec_axis_pitch_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[18])); 
     p->DrawResult = 0 ; 
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void probe_sec_axis_pitch_r(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->probe_p->sec_axis_pitch_r = gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry[18])) ;
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void SequenceSelect2DT(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     int i = gtk_combo_box_get_active(GTK_COMBO_BOX(widget)); 
     switch(i)
     {
         case 0:
#if CALL_DEBUG
              g_printf("selection 0 \n");
#endif               
              
              break;
         case 1:
#if CALL_DEBUG
              g_printf("selection 1 \n");
#endif                             
              
              break;                       
     }
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void SequenceSelect2DR(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     int i = gtk_combo_box_get_active(GTK_COMBO_BOX(widget)); 
     switch(i)
     {
         case 0:
#if CALL_DEBUG
             g_printf("selection 0 \n"); 
#endif                             
              
              break;
         case 1:              
#if CALL_DEBUG
              g_printf("selection 1 \n");
#endif               
              
              break;                       
     }
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

/*----wedge----*/
//发送
void wg_wedge_angle(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->wedge_p->wg_wedge_angle=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[2]));
     gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[3]),p->wedge_p->wg_wedge_angle);
	 p->wedge_r->wg_wedge_angle=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[3]));
	 p->DrawResult = 0 ;
	 p->is_draw_focus = 1;
	 gtk_widget_set_sensitive (p->combo, p->DrawResult);
	 force_updata(p);
}

void wg_roof_angle(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->wedge_p->wg_roof_angle=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[4])); 
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[5]),-(p->wedge_p->wg_roof_angle));
	p->wedge_r->wg_roof_angle=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[5]));
	p->DrawResult = 0 ;
	p->is_draw_focus = 1;
	gtk_widget_set_sensitive (p->combo, p->DrawResult);
	force_updata(p);
}

void wg_lon_vel(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->wedge_p->wg_lon_vel=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[6]));
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[7]),p->wedge_p->wg_lon_vel);
	 p->wedge_r->wg_lon_vel=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[7])); 
	 p->DrawResult = 0 ;
	 p->is_draw_focus = 1;
	 gtk_widget_set_sensitive (p->combo, p->DrawResult);
	 force_updata(p);
}

void wg_trans_vel(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->wedge_p->wg_trans_vel=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[8])); 
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[9]),p->wedge_p->wg_trans_vel);
	 p->wedge_r->wg_trans_vel=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[9]));
	 p->DrawResult = 0 ;
	 p->is_draw_focus = 1;
	 gtk_widget_set_sensitive (p->combo, p->DrawResult);
	 force_updata(p);
}

void wg_density(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->wedge_p->wg_density=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[10])); 
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[11]),p->wedge_p->wg_density);
	 p->wedge_r->wg_density=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[11]));
	 p->DrawResult = 0 ;
	 p->is_draw_focus = 1;
	 gtk_widget_set_sensitive (p->combo, p->DrawResult);
	 force_updata(p);
}

void wg_heigh_fir(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->wedge_p->wg_heigh_fir=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[12])); 
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[13]),p->wedge_p->wg_heigh_fir);
	 p->wedge_r->wg_heigh_fir=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[13]));
	 p->DrawResult = 0 ;
	 p->is_draw_focus = 1;
	 gtk_widget_set_sensitive (p->combo, p->DrawResult);
	 force_updata(p);
}

void wg_pri_elem_offset_fir(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_p->wg_pri_elem_offset_fir=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[14])); 
   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[15]),p->wedge_p->wg_pri_elem_offset_fir);
	 p->wedge_r->wg_pri_elem_offset_fir=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[15])); 
	 p->DrawResult = 0 ;
	 p->is_draw_focus = 1;
	 gtk_widget_set_sensitive (p->combo, p->DrawResult);
	 force_updata(p);
}

void wg_sec_elem_offset_fir(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_p->wg_sec_elem_offset_fir=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[16])); 
   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[17]),p->wedge_p->wg_sec_elem_offset_fir);
   p->wedge_r->wg_sec_elem_offset_fir=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[17]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}

void wg_pri_axis_reference(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_p->wg_pri_axis_reference=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[18]));  
   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[19]),p->wedge_p->wg_pri_axis_reference);
   p->wedge_r->wg_pri_axis_reference = gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[19]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}

void wg_sec_axis_reference(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_p->wg_sec_axis_reference=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[20]));  
   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[21]),p->wedge_p->wg_sec_axis_reference);
   p->wedge_r->wg_sec_axis_reference = gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[21]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void wg_length(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_p->wg_length=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[22])); 
   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[23]),p->wedge_p->wg_length);
	 p->wedge_r->wg_length=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[23]));
	 p->DrawResult = 0 ;
	 p->is_draw_focus = 1;
	 gtk_widget_set_sensitive (p->combo, p->DrawResult);
	 force_updata(p);
}

void wg_width(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_p->wg_width=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[24])); 
   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[25]),p->wedge_p->wg_width);
	p->wedge_r->wg_width=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[25]));
	p->DrawResult = 0 ;
	p->is_draw_focus = 1;
	gtk_widget_set_sensitive (p->combo, p->DrawResult);
	force_updata(p);
}


void wg_height(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_p->wg_height=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[26]));   
   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[27]),p->wedge_p->wg_height);
   p->wedge_r->wg_height=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[27]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
//
void import_material(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   GtkWidget *dialog;
   GtkWidget *label[2];
   GtkWidget *vbox;
   GtkWidget *hbox;
   GtkWidget *fix;
   GtkWidget *frame[2];
   
   gint i;
   gchar tmp[20];
   GtkWidget *sw;
   GtkTreeIter iter;
   GtkListStore *store; 
   GtkWidget *treeview;    
   GtkTreeSelection *selection;
   /* Create the widgets */
   dialog = gtk_dialog_new_with_buttons ("Selection Material",
                                         GTK_WINDOW (p->window),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK,
                                         GTK_RESPONSE_ACCEPT,
                                         GTK_STOCK_CANCEL,
                                         GTK_RESPONSE_CANCEL,
                                         NULL);
   gtk_widget_set_size_request(GTK_WIDGET (dialog), 500, 350);
   gtk_window_set_modal (GTK_WINDOW(dialog), TRUE);//激活该窗口禁止主窗口 

   vbox = GTK_WIDGET(GTK_DIALOG(dialog)->vbox);
   //
   hbox = gtk_hbox_new(FALSE,0);
   gtk_container_add (GTK_CONTAINER (vbox), hbox);
   frame[0]=gtk_frame_new("Material List");
   frame[1]=gtk_frame_new("Material Attributes");
   gtk_widget_set_size_request(GTK_WIDGET(frame[0]),200,300);
   gtk_widget_set_size_request(GTK_WIDGET(frame[1]),280,300);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(frame[0]),FALSE,FALSE,5);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(frame[1]),FALSE,FALSE,5);
   //frame0                                                                        
   sw = gtk_scrolled_window_new (NULL, NULL);
   gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
   gtk_container_add (GTK_CONTAINER (frame[0]), sw);
   //create model
   store = gtk_list_store_new (2,G_TYPE_INT,G_TYPE_STRING);
   for (i = 0; i < G_N_ELEMENTS (p->material); i++)
   {
          gtk_list_store_append (store, &iter);
          gtk_list_store_set (store, &iter,0, p->material[i]->index,
                                           1, p->material[i]->name,-1); 
   }
   //create treeview
   treeview = gtk_tree_view_new_with_model ( GTK_TREE_MODEL(store) ); 
   gtk_container_add (GTK_CONTAINER (sw), treeview);    
   //add column 0 
   GtkTreeModel      *model    = gtk_tree_view_get_model (GTK_TREE_VIEW(treeview));
   GtkCellRenderer   *renderer = gtk_cell_renderer_text_new ();		    
   GtkTreeViewColumn *column   = gtk_tree_view_column_new_with_attributes (NULL,
                                 renderer,"text",0,NULL);
   gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column); 
   //add column 1 
   model    = gtk_tree_view_get_model (GTK_TREE_VIEW(treeview));
   renderer = gtk_cell_renderer_text_new ();		    
   column   = gtk_tree_view_column_new_with_attributes (NULL,
                                 renderer,"text",1,NULL);
   gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column); 
   selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));    
   g_signal_connect (selection,"changed",G_CALLBACK (selection_material),(gpointer)p );
   //frame1
   vbox = gtk_vbox_new(FALSE,0);
   gtk_container_add (GTK_CONTAINER (frame[1]), vbox);
   //
   fix = gtk_fixed_new();
   label[0] = gtk_label_new("Name");
   p->entry_material[0] = gtk_entry_new();
   gtk_entry_set_text(GTK_ENTRY(p->entry_material[0]),p->material[p->db_count]->name);
   gtk_widget_set_size_request(GTK_WIDGET(p->entry_material[0]),80,20);
   gtk_fixed_put(GTK_FIXED(fix),label[0],5,5);
   gtk_fixed_put(GTK_FIXED(fix),p->entry_material[0],140,0);
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(fix),FALSE,FALSE,5);
   //
   fix = gtk_fixed_new();
   label[0] = gtk_label_new("State");
   p->entry_material[1] = gtk_entry_new();
   gtk_entry_set_text(GTK_ENTRY(p->entry_material[1]),p->material[p->db_count]->state);
   gtk_widget_set_size_request(GTK_WIDGET(p->entry_material[1]),80,20);
   gtk_fixed_put(GTK_FIXED(fix),label[0],5,5);
   gtk_fixed_put(GTK_FIXED(fix),p->entry_material[1]   ,140,0);
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(fix),FALSE,FALSE,5);
   //
   fix = gtk_fixed_new();
   label[0] = gtk_label_new("Longitudinal Velocity");
   p->entry_material[2] = gtk_entry_new();
   sprintf(tmp,"%.0lf",p->material[p->db_count]->longi_vel);
   gtk_entry_set_text(GTK_ENTRY(p->entry_material[2]),tmp);
   gtk_widget_set_size_request(GTK_WIDGET(p->entry_material[2]),60,20);
   label[1] = gtk_label_new("m/s");
   gtk_fixed_put(GTK_FIXED(fix),label[0],5,5);
   gtk_fixed_put(GTK_FIXED(fix),p->entry_material[2]   ,140,0);
   gtk_fixed_put(GTK_FIXED(fix),label[1],205,5);
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(fix),FALSE,FALSE,5);
   //
   fix = gtk_fixed_new();
   label[0] = gtk_label_new("Transverse Velocity");
   p->entry_material[3] = gtk_entry_new();
   sprintf(tmp,"%.0lf",p->material[p->db_count]->trans_vel);
   gtk_entry_set_text(GTK_ENTRY(p->entry_material[3]),tmp);
   gtk_widget_set_size_request(GTK_WIDGET(p->entry_material[3]),60,20);
   label[1] = gtk_label_new("m/s");
   gtk_fixed_put(GTK_FIXED(fix),label[0],5,5);
   gtk_fixed_put(GTK_FIXED(fix),p->entry_material[3]   ,140,0);
   gtk_fixed_put(GTK_FIXED(fix),label[1],205,5);
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(fix),FALSE,FALSE,5);
   //
   fix = gtk_fixed_new();
   label[0] = gtk_label_new("Density");
   p->entry_material[4] = gtk_entry_new();
   sprintf(tmp,"%.0lf",p->material[p->db_count]->density);
   gtk_entry_set_text(GTK_ENTRY(p->entry_material[4]),tmp);
   gtk_widget_set_size_request(GTK_WIDGET(p->entry_material[4]),60,20);
   label[1] = gtk_label_new("kg/m3");
   gtk_fixed_put(GTK_FIXED(fix),label[0],5,5);
   gtk_fixed_put(GTK_FIXED(fix),p->entry_material[4]   ,140,0);
   gtk_fixed_put(GTK_FIXED(fix),label[1],205,5);
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(fix),FALSE,FALSE,5);
   //
  
   gtk_widget_show_all (dialog);   
   if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)//捕捉OK按钮信号
   {
       if( widget == p->btn_wg)//wedge
       {
           p->wedge_p->wg_lon_vel   = p->material[p->db_count]->longi_vel; 
           p->wedge_p->wg_trans_vel = p->material[p->db_count]->trans_vel;
           p->wedge_p->wg_density   = (gint)p->material[p->db_count]->density;       
           gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[6]),p->wedge_p->wg_lon_vel);
           gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[8]),p->wedge_p->wg_trans_vel);
           gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[10]),p->wedge_p->wg_density); 
       }
       else //specimen
       {
            strcpy(p->specimen->material,p->material[p->db_count]->name);
            p->specimen->speci_longitudinal_wave   = p->material[p->db_count]->longi_vel; 
            p->specimen->speci_transverse_wave     = p->material[p->db_count]->trans_vel;
            gtk_entry_set_text(GTK_ENTRY(p->entry_def[1]),p->specimen->material);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_def[2]),p->specimen->speci_longitudinal_wave);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_def[3]),p->specimen->speci_transverse_wave);
       }
                 
   }
   
   gtk_widget_destroy(dialog);  
     
}

void selection_material(GtkTreeSelection *selection, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     
     GtkTreeView *treeView;    
     GtkTreeModel *model; 
     GtkTreeIter iter; 
     gchar tmp[20];      
     
     treeView = gtk_tree_selection_get_tree_view(selection);    
     model = gtk_tree_view_get_model(treeView);    
     gtk_tree_selection_get_selected(selection, &model, &iter);    
     //get index
     gtk_tree_model_get(model, &iter,0, &p->db_count,-1);    
   
     gtk_entry_set_text(GTK_ENTRY(p->entry_material[0]),p->material[p->db_count]->name);
     gtk_entry_set_text(GTK_ENTRY(p->entry_material[1]),p->material[p->db_count]->state);
     sprintf(tmp,"%.0lf",p->material[p->db_count]->longi_vel);
     gtk_entry_set_text(GTK_ENTRY(p->entry_material[2]),tmp);
     sprintf(tmp,"%.0lf",p->material[p->db_count]->trans_vel);
     gtk_entry_set_text(GTK_ENTRY(p->entry_material[3]),tmp);
     sprintf(tmp,"%.0lf",p->material[p->db_count]->density);
     gtk_entry_set_text(GTK_ENTRY(p->entry_material[4]),tmp);
}

//接收 
void wg_wedge_angle_r(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->wedge_r->wg_wedge_angle=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[3]));
     p->DrawResult = 0 ;
     p->is_draw_focus = 1;
     gtk_widget_set_sensitive (p->combo, p->DrawResult);
     force_updata(p);
}

void wg_roof_angle_r(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->wedge_r->wg_roof_angle=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[5])); 
    p->DrawResult = 0 ;
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}

void wg_lon_vel_r(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->wedge_r->wg_lon_vel=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[7])); 
    p->DrawResult = 0 ;
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}

void wg_trans_vel_r(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->wedge_r->wg_trans_vel=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[9]));
    p->DrawResult = 0 ; 
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}

void wg_density_r(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->wedge_r->wg_density=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[11])); 
    p->DrawResult = 0 ;
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}

void wg_heigh_fir_r(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->wedge_r->wg_heigh_fir=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[13])); 
    p->DrawResult = 0 ;
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}

void wg_pri_elem_offset_fir_r(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_r->wg_pri_elem_offset_fir=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[15]));
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1; 
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}

void wg_sec_elem_offset_fir_r(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_r->wg_sec_elem_offset_fir=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[17]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}

void wg_pri_axis_reference_r(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_r->wg_pri_axis_reference=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[19]));
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1; 
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}

void wg_sec_axis_reference_r(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_r->wg_sec_axis_reference=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[21])); 
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void wg_length_r(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_r->wg_length=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[23])); 
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}

void wg_width_r(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_r->wg_width=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[25]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}

void wg_height_r(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->wedge_r->wg_height=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_wg[27]));   
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
} 

/*scanner*/
void scan_axis_off(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->scanner->scan_axis_off=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_sc[0]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void index_axis_off(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->scanner->index_axis_off=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_sc[1]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void usound_axis_off(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->scanner->usound_axis_off=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_sc[2]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void scan_axis_ori(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->scanner->scan_axis_ori=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_sc[3]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void index_axis_ori(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->scanner->index_axis_ori=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_sc[4]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void usound_axis_ori(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->scanner->usound_axis_ori=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_sc[5]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}

/* focal selection selection */
void focal_focus_type(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->focal_point->focal_focus_type=gtk_combo_box_get_active(GTK_COMBO_BOX(p->combox_focal));
   
   gint i;
   for(i=0;i<7;i++)
        gtk_widget_set_sensitive (p->entry_foc[i], FALSE);
   
   if(p->probe_p->Pitch_Catch)
   {
       switch(p->focal_point->focal_focus_type)  
       {
          case 0://Half path
               gtk_widget_set_sensitive (p->entry_foc[0], TRUE);
               break; 
          case 1://True Depth
               gtk_widget_set_sensitive (p->entry_foc[0], TRUE);
               break;
          case 2://Automatic
               
               break;                                                
       }                        
   }
   else
   {
       if(p->beam_angle-> beam_type == 2)
       {
          gtk_widget_set_sensitive (p->entry_foc[0], TRUE);
          gtk_widget_set_sensitive (p->entry_foc[1], TRUE);
          gtk_widget_set_sensitive (p->entry_foc[2], TRUE);                
       }
       else
       {
           switch(p->focal_point->focal_focus_type)  
           {
               case 0://True Depth
                    gtk_widget_set_sensitive (p->entry_foc[0], TRUE);
                    break;
               case 1://Half path
                    gtk_widget_set_sensitive (p->entry_foc[0], TRUE);
                    break;
               case 2://Projection
                    gtk_widget_set_sensitive (p->entry_foc[3], TRUE);
                    break;
               case 3://Focal plane
                    gtk_widget_set_sensitive (p->entry_foc[3], TRUE);
                    gtk_widget_set_sensitive (p->entry_foc[4], TRUE);
                    gtk_widget_set_sensitive (p->entry_foc[5], TRUE);
                    gtk_widget_set_sensitive (p->entry_foc[6], TRUE);
                    break;
           } 
       }
   }

   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void focal_focus_point_start(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->focal_point->focal_focus_point_start=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_foc[0]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void focal_focus_point_stop(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->focal_point->focal_focus_point_stop=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_foc[1]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void focal_focus_point_resolution(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->focal_point->focal_focus_point_resolution=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_foc[2]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void offset_start(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->focal_point->offset_start=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_foc[3]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void offset_end(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->focal_point->offset_end=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_foc[4]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void depth_start(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->focal_point->depth_start=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_foc[5]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void depth_end(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->focal_point->depth_end=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_foc[6]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}


/*element selection*/
void primary_axis_s(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->element_sel->primary_axis_s=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_elem[0])); 
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void primary_axis_e(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->element_sel->primary_axis_e=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_elem[1]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void primary_axis_r(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->element_sel->primary_axis_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_elem[2])); 
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void seconary_axis_s(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->element_sel->seconary_axis_s=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_elem[3])); 
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void seconary_axis_e(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->element_sel->seconary_axis_e=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_elem[4]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void seconary_axis_r(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->element_sel->seconary_axis_r=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_elem[5]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void pri_axis_ape(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->element_sel->pri_axis_ape=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_elem[6])); 
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1;         
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}  
void sec_axis_ape(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->element_sel->sec_axis_ape=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_elem[7]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void connection(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->element_sel->connection=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_elem[8]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}

/* ----beam angle selection---- */
void beam_pri_steer_angle_start(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_pri_steer_angle_start=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[0])); 
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_pri_steer_angle_stop(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_pri_steer_angle_stop=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[1]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_pri_steer_angle_resolution(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_pri_steer_angle_resolution=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[2])); 
   p->DrawResult = 0 ;  
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_sec_steer_angle_start(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_pri_steer_angle_start=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[3])); 
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_sec_steer_angle_stop(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_pri_steer_angle_start=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[4])); 
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_sec_steer_angle_resolution(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_pri_steer_angle_start=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[5])); 
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_refrac_angle_start(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_refrac_angle_start=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[6])); 
   p->DrawResult = 0 ;
   p->is_draw_focus = 1; 
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_refrac_angle_stop(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_refrac_angle_stop=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[7]));
   p->DrawResult = 0 ;   
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_refrac_angle_resolution(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_refrac_angle_resolution=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[8])); 
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_skew_angle_start(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_skew_angle_start=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[9])); 
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_skew_angle_stop(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_skew_angle_stop=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[10])); 
   p->DrawResult = 0 ;
   p->is_draw_focus = 1; 
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_skew_angle_resolution(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_skew_angle_resolution=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_beam[11])); 
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void beam_type(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_type=gtk_combo_box_get_active(GTK_COMBO_BOX(p->combox_beam[0]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   p->element_sel->linear = 0;
   gint i;
   for(i=0;i<12;i++)
        gtk_widget_set_sensitive (p->entry_beam[i], FALSE);
   switch(p->probe_p->D1_D2)
   {
       case 0://1D
            switch(p->beam_angle->beam_type)
            {
                case 0://Azimuthal
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Refracted angle
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[7], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[8], TRUE);
                                break;
                          case 1://Primary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[1], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[2], TRUE);
                                break;
                          case 2://Beam screw angle 
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[10], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[11], TRUE);
                                break;  
                      } 
                      break;
                case 1://Linear
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Refracted angle
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 1://Primary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                break;
                          case 2://Beam screw angle 
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;  
                      }
                      
                      //element selection
                      p->element_sel->linear = 1;
                      break;
                case 2://Depth
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Refracted angle
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 1://Primary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                break;
                          case 2://Beam screw angle 
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;  
                      }                      
                      break;
                case 3://Static
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Refracted angle
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 1://Primary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                break;
                          case 2://Beam screw angle 
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;  
                      }
                      break;              
            }
            
            break;
       case 1://2D
            switch(p->beam_angle->beam_type)
            {
                case 0://Azimuthal
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Primary/Secondary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[1], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[2], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[4], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[5], TRUE);
                                break;
                          case 1://Primary/Beam skew angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[1], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[2], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[10], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[11], TRUE);
                                break;
                          case 2://Secondary/Refracted angle 
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[4], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[5], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[7], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[8], TRUE);
                                break;
                          case 3://Refracted/Beam skew angle 
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[7], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[8], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[10], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[11], TRUE);
                                break; 
                      } 
                      break;
                case 1://Linear
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Primary/Secondary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                break;
                          case 1://Primary/Beam skew angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;
                          case 2://Secondary/Refracted angle 
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 3://Refracted/Beam skew angle 
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break; 
                      }
                      
                      //element selection
                      p->element_sel->linear = 1;
                      break;
                case 2://Depth
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Primary/Secondary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                break;
                          case 1://Primary/Beam skew angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;
                          case 2://Secondary/Refracted angle 
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 3://Refracted/Beam skew angle 
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break; 
                      } 
                      break;
                case 3://Static
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Primary/Secondary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                break;
                          case 1://Primary/Beam skew angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;
                          case 2://Secondary/Refracted angle 
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 3://Refracted/Beam skew angle 
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break; 
                      } 
                      break;              
            }            
            
            break;              
   }            
               
   force_updata(p);
}

void btn_beam(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}

void beam_angle_sel(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->beam_angle->beam_angle_sel=gtk_combo_box_get_active(GTK_COMBO_BOX(p->combox_beam[1]));
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   p->element_sel->linear = 0;
   gint i;
   for(i=0;i<12;i++)
        gtk_widget_set_sensitive (p->entry_beam[i], FALSE);
   switch(p->probe_p->D1_D2)
   {
       case 0://1D
            switch(p->beam_angle->beam_type)
            {
                case 0://Azimuthal
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Refracted angle
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[7], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[8], TRUE);
                                break;
                          case 1://Primary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[1], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[2], TRUE);
                                break;
                          case 2://Beam screw angle 
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[10], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[11], TRUE);
                                break;  
                      } 
                      break;
                case 1://Linear
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Refracted angle
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 1://Primary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                break;
                          case 2://Beam screw angle 
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;  
                      }
                      
                      //element selection
                      p->element_sel->linear = 1;
                      break;
                case 2://Depth
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Refracted angle
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 1://Primary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                break;
                          case 2://Beam screw angle 
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;  
                      }
                      break;
                case 3://Static
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Refracted angle
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 1://Primary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                break;
                          case 2://Beam screw angle 
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;  
                      }
                      break;              
            }
            
            break;
       case 1://2D
            switch(p->beam_angle->beam_type)
            {
                case 0://Azimuthal
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Primary/Secondary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[1], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[2], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[4], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[5], TRUE);
                                break;
                          case 1://Primary/Beam skew angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[1], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[2], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[10], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[11], TRUE);
                                break;
                          case 2://Secondary/Refracted angle 
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[4], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[5], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[7], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[8], TRUE);
                                break;
                          case 3://Refracted/Beam skew angle 
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[7], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[8], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[10], TRUE);
                                gtk_widget_set_sensitive (p->entry_beam[11], TRUE);
                                break; 
                      } 
                      break;
                case 1://Linear
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Primary/Secondary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                break;
                          case 1://Primary/Beam skew angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;
                          case 2://Secondary/Refracted angle 
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 3://Refracted/Beam skew angle 
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break; 
                      }
                      
                      //element selection
                      p->element_sel->linear = 1;
                      break;
                case 2://Depth
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Primary/Secondary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                break;
                          case 1://Primary/Beam skew angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;
                          case 2://Secondary/Refracted angle 
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 3://Refracted/Beam skew angle 
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break; 
                      } 
                      break;
                case 3://Static
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Primary/Secondary steering angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                break;
                          case 1://Primary/Beam skew angle
                                gtk_widget_set_sensitive (p->entry_beam[0], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break;
                          case 2://Secondary/Refracted angle 
                                gtk_widget_set_sensitive (p->entry_beam[3], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                break;
                          case 3://Refracted/Beam skew angle 
                                gtk_widget_set_sensitive (p->entry_beam[6], TRUE);
                                
                                gtk_widget_set_sensitive (p->entry_beam[9], TRUE);
                                break; 
                      } 
                      break;              
            }            
            
            break;              
   }
   force_updata(p);            
}


/* ----specimen settings----*/
void speci_longitudinal_wave(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->specimen->speci_longitudinal_wave=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_def[2]));  
   p->DrawResult = 0 ;  
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void speci_transverse_wave(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   p->specimen->speci_transverse_wave=gtk_spin_button_get_value(GTK_SPIN_BUTTON(p->entry_def[3]));  
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void speci_length(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   if(!strcmp(gtk_combo_box_get_active_text(GTK_COMBO_BOX(p->combox_def)),"Flat" ) ) 
           p->specimen->speci_length_flat=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_def[4]));                                                      
   else                  
           p->specimen->speci_inside_cylindrical=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_def[7]));          
    
    p->DrawResult = 0 ; 
    p->is_draw_focus = 1;                                               
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}
void speci_height(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   if(!strcmp(gtk_combo_box_get_active_text(GTK_COMBO_BOX(p->combox_def)),"Flat" ) )
           p->specimen->speci_height_flat=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_def[5]));                                                      
   else                  
           p->specimen->speci_outside_cylindrical=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_def[8])); 
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void speci_width(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   if(!strcmp(gtk_combo_box_get_active_text(GTK_COMBO_BOX(p->combox_def)),"Flat" ) )
           p->specimen->speci_width_flat=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_def[6]));                                                      
   else                
           p->specimen->speci_length_cylindrical=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_def[9]));
    p->DrawResult = 0 ;
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}
void speci_setting_def(GtkWidget *widget, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->specimen->flat_cylindrical=gtk_combo_box_get_active(GTK_COMBO_BOX(p->combox_def));
     if(!strcmp(gtk_combo_box_get_active_text(GTK_COMBO_BOX(p->combox_def)),"Flat" ) ) /*如果选中 Flat */
       {
#if CALL_DEBUG
            g_printf("Flat\n");  
#endif 
           
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_f[0]));
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_f[1]));
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_f[2]));
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_c[0]));
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_c[1]));
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_c[2]));
          
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[4]),p->specimen->speci_length_flat); 
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[5]),p->specimen->speci_height_flat);
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[6]),p->specimen->speci_width_flat);   
           
           p->footprint  = 0 ;                                                         
       }
     else                                                               /*如果选中 Cylindrical */
       {
#if CALL_DEBUG
            g_printf("Cylindrical\n");   
#endif 
          
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_f[0]));
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_f[1]));
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_f[2]));
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_c[0]));
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_c[1]));
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_c[2]));
           
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[7]),p->specimen->speci_inside_cylindrical); 
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[8]),p->specimen->speci_outside_cylindrical);
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[9]),p->specimen->speci_length_cylindrical);
           

           p->footprint  = 1 ;              
       }
    p->DrawResult = 0 ;
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}
void Inspection_od_id(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->radio_pro[0])) ) 
       {
         strcpy(p->specimen->Inspection_od_id,"OD");
         p->footprint  = 1 ;
       }
   if( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p->radio_pro[1])) )      
       {
         strcpy(p->specimen->Inspection_od_id,"ID");
         p->footprint  = 2 ;
       }
//   g_printf("%s\n",p->specimen->Inspection_od_id);
    p->DrawResult = 0 ;
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}

/*location*/
void rotation1(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->location->st1=gtk_combo_box_get_active(GTK_COMBO_BOX(p->combo_loca[0])); 
    p->DrawResult = 0 ; 
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}
void rotation2(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->location->st2=gtk_combo_box_get_active(GTK_COMBO_BOX(p->combo_loca[1]));  
    p->DrawResult = 0 ;
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}
void rotation3(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    p->location->st3=gtk_combo_box_get_active(GTK_COMBO_BOX(p->combo_loca[2]));  
    p->DrawResult = 0 ;
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    force_updata(p);
}
void axis0(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->location->center_x=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_loca[0]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void axis1(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->location->center_y=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_loca[1]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void axis2(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->location->center_z=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_loca[2])); 
   p->DrawResult = 0 ;
   p->is_draw_focus = 1; 
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void axis3(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->location->rotation_x=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_loca[3]));
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1; 
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void axis4(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->location->rotation_y=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_loca[4]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void axis5(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->location->rotation_z=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_loca[5])); 
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void axis6(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->location->translation_x=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_loca[6])); 
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void axis7(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->location->translation_y=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_loca[7])); 
   p->DrawResult = 0 ; 
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}
void axis8(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data); 
   p->location->translation_z=gtk_spin_button_get_value( GTK_SPIN_BUTTON(p->entry_loca[8]));  
   p->DrawResult = 0 ;
   p->is_draw_focus = 1;
   gtk_widget_set_sensitive (p->combo, p->DrawResult);
   force_updata(p);
}

/*projected squence*/
void circum_axial(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);  
    p->project->circum_axial=gtk_combo_box_get_active(GTK_COMBO_BOX(p->combo_pro[2]));
    p->DrawResult = 0 ;
    p->is_draw_focus = 1;
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    switch(p->project->circum_axial)
    {
        case 0:
//             g_printf("Circumferential\n");   
             break;
        case 1:
//             g_printf("Axial\n");  
             break;
    }
    force_updata(p);
}



