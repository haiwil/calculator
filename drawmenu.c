/************************************************* 
               主菜单 
 ************************************************* */

#include "drawui.h"


/*函数声明*/
void draw_menu(DRAW_UI_P p);/*画菜单*/
extern void update_widget_bg(GtkWidget *widget, const gchar *img_file);
/*外部函数声明*/
/*probe*/
extern void D1_D2(GtkWidget *widget, gpointer data);
extern void transmi_trans_longi(GtkWidget *widget, gpointer data);
extern void recev_trans_longi(GtkWidget *widget, gpointer data);
extern void Pitch_Catch(GtkWidget *widget, gpointer data);
extern void WedgeSeparation(GtkWidget *widget, gpointer data);
extern void probe_skew(GtkWidget *widget, gpointer data);
extern void probe_frequency(GtkWidget *widget, gpointer data);
extern void probe_ele_num(GtkWidget *widget, gpointer data);
extern void probe_sec_ele_num(GtkWidget *widget, gpointer data);//
extern void probe_pri_axis_pitch(GtkWidget *widget, gpointer data);
extern void probe_pri_elem_size(GtkWidget *widget, gpointer data);
extern void probe_sec_elem_size(GtkWidget *widget, gpointer data);
extern void probe_skew_r(GtkWidget *widget, gpointer data);
extern void probe_frequency_r(GtkWidget *widget, gpointer data);
extern void probe_ele_num_r(GtkWidget *widget, gpointer data);
extern void probe_sec_ele_num_r(GtkWidget *widget, gpointer data);//
extern void probe_pri_axis_pitch_r(GtkWidget *widget, gpointer data);
extern void probe_pri_elem_size_r(GtkWidget *widget, gpointer data);
extern void probe_sec_elem_size_r(GtkWidget *widget, gpointer data);
extern void SequenceSelect2DR(GtkWidget *widget, gpointer data);
extern void SequenceSelect2DT(GtkWidget *widget, gpointer data);
extern void probe_sec_axis_pitch(GtkWidget *widget, gpointer data) ;
extern void probe_sec_axis_pitch_r(GtkWidget *widget, gpointer data);
extern void probe_sec_ele_num(GtkWidget *widget, gpointer data) ;
/*wedge*/
//发送 
extern void wg_wedge_angle(GtkWidget *widget, gpointer data);
extern void wg_roof_angle(GtkWidget *widget, gpointer data);
extern void wg_lon_vel(GtkWidget *widget, gpointer data);
extern void wg_trans_vel(GtkWidget *widget, gpointer data);
extern void wg_density(GtkWidget *widget, gpointer data);
extern void wg_heigh_fir(GtkWidget *widget, gpointer data);
extern void wg_pri_elem_offset_fir(GtkWidget *widget, gpointer data);
extern void wg_sec_elem_offset_fir(GtkWidget *widget, gpointer data);
extern void wg_pri_axis_reference(GtkWidget *widget, gpointer data);
extern void wg_sec_axis_reference(GtkWidget *widget, gpointer data);
extern void wg_length(GtkWidget *widget, gpointer data);
extern void wg_width(GtkWidget *widget, gpointer data);
extern void wg_height(GtkWidget *widget, gpointer data);
extern void import_material(GtkWidget *widget, gpointer data);////////////
//接收
extern void wg_wedge_angle_r(GtkWidget *widget, gpointer data);
extern void wg_roof_angle_r(GtkWidget *widget, gpointer data);
extern void wg_lon_vel_r(GtkWidget *widget, gpointer data);
extern void wg_trans_vel_r(GtkWidget *widget, gpointer data);
extern void wg_density_r(GtkWidget *widget, gpointer data);
extern void wg_heigh_fir_r(GtkWidget *widget, gpointer data);
extern void wg_pri_elem_offset_fir_r(GtkWidget *widget, gpointer data);
extern void wg_sec_elem_offset_fir_r(GtkWidget *widget, gpointer data);
extern void wg_pri_axis_reference_r(GtkWidget *widget, gpointer data);
extern void wg_sec_axis_reference_r(GtkWidget *widget, gpointer data);
extern void wg_length_r(GtkWidget *widget, gpointer data);
extern void wg_width_r(GtkWidget *widget, gpointer data);
extern void wg_height_r(GtkWidget *widget, gpointer data); 
/*scanner*/
extern void scan_axis_off(GtkWidget *widget, gpointer data);
extern void index_axis_off(GtkWidget *widget, gpointer data);
extern void usound_axis_off(GtkWidget *widget, gpointer data);
extern void scan_axis_ori(GtkWidget *widget, gpointer data);
extern void index_axis_ori(GtkWidget *widget, gpointer data);
extern void usound_axis_ori(GtkWidget *widget, gpointer data);
/* beam angle selection */
extern void beam_pri_steer_angle_start(GtkWidget *widget, gpointer data);
extern void beam_pri_steer_angle_stop(GtkWidget *widget, gpointer data);
extern void beam_pri_steer_angle_resolution(GtkWidget *widget, gpointer data);
extern void beam_sec_steer_angle_start(GtkWidget *widget, gpointer data);
extern void beam_sec_steer_angle_stop(GtkWidget *widget, gpointer data);
extern void beam_sec_steer_angle_resolution(GtkWidget *widget, gpointer data);
extern void beam_refrac_angle_start(GtkWidget *widget, gpointer data);
extern void beam_refrac_angle_stop(GtkWidget *widget, gpointer data);
extern void beam_refrac_angle_resolution(GtkWidget *widget, gpointer data);
extern void beam_angle_sel(GtkWidget *widget, gpointer data);
extern void beam_type(GtkWidget *widget, gpointer data);
extern void btn_beam(GtkWidget *widget, gpointer data);
extern void beam_skew_angle_start(GtkWidget *widget, gpointer data);
extern void beam_skew_angle_stop(GtkWidget *widget, gpointer data);
extern void beam_skew_angle_resolution(GtkWidget *widget, gpointer data);
/* focal selection selection */
extern void focal_focus_type(GtkWidget *widget, gpointer data);
extern void focal_focus_point_start(GtkWidget *widget, gpointer data);
extern void focal_focus_point_stop(GtkWidget *widget, gpointer data);
extern void focal_focus_point_resolution(GtkWidget *widget, gpointer data);
extern void offset_start(GtkWidget *widget, gpointer data);
extern void offset_end(GtkWidget *widget, gpointer data);
extern void depth_start(GtkWidget *widget, gpointer data);
extern void depth_end(GtkWidget *widget, gpointer data);
/*element selection*/
extern void primary_axis_s(GtkWidget *widget, gpointer data);
extern void primary_axis_e(GtkWidget *widget, gpointer data);
extern void primary_axis_r(GtkWidget *widget, gpointer data);
extern void seconary_axis_s(GtkWidget *widget, gpointer data);
extern void seconary_axis_e(GtkWidget *widget, gpointer data);
extern void seconary_axis_r(GtkWidget *widget, gpointer data);
extern void pri_axis_ape(GtkWidget *widget, gpointer data);
extern void sec_axis_ape(GtkWidget *widget, gpointer data);
extern void connection(GtkWidget *widget, gpointer data);
/* specimen settings*/
extern void speci_longitudinal_wave(GtkWidget *widget, gpointer data);
extern void speci_transverse_wave(GtkWidget *widget, gpointer data);
extern void speci_length(GtkWidget *widget, gpointer data);
extern void speci_height(GtkWidget *widget, gpointer data);
extern void speci_width(GtkWidget *widget, gpointer data);
extern void speci_setting_def(GtkWidget *widget, gpointer data);
extern void Inspection_od_id(GtkWidget *widget, gpointer data);
/*location*/
extern void rotation1(GtkWidget *widget, gpointer data);
extern void rotation2(GtkWidget *widget, gpointer data);
extern void rotation3(GtkWidget *widget, gpointer data); 
extern void axis0(GtkWidget *widget, gpointer data);
extern void axis1(GtkWidget *widget, gpointer data);
extern void axis2(GtkWidget *widget, gpointer data);
extern void axis3(GtkWidget *widget, gpointer data);
extern void axis4(GtkWidget *widget, gpointer data);
extern void axis5(GtkWidget *widget, gpointer data);
extern void axis6(GtkWidget *widget, gpointer data);
extern void axis7(GtkWidget *widget, gpointer data);
extern void axis8(GtkWidget *widget, gpointer data);
/*projected squence*/
extern void circum_axial(GtkWidget *widget, gpointer data);
/*database*/
extern void probe_import(GtkWidget *widget, gpointer data);
extern void probe_export(GtkWidget *widget, gpointer data);
extern void probe_delete(GtkWidget *widget, gpointer data);
extern void wedge_import(GtkWidget *widget, gpointer data);
extern void wedge_export(GtkWidget *widget, gpointer data);
extern void wedge_delete(GtkWidget *widget, gpointer data);

/*画菜单*/
void draw_menu(DRAW_UI_P p)
{
      gtk_widget_destroy(p->vbox_ldw);
    
    if(!strcmp(p->pos,"Hardware selection")) 
    {
        p->vbox_ldw=gtk_fixed_new(); 
        gint i;                      
        for(i=0;i<7;i++)
    	{        
            p->label_ldw[i]= gtk_label_new(g_locale_to_utf8(p->label[i],-1,NULL,NULL,NULL));
            p->text[i]=gtk_entry_new(); 
            gtk_entry_set_text(GTK_ENTRY(p->text[i]),g_locale_to_utf8(p->parament[i],-1,NULL,NULL,NULL));
            gtk_widget_set_sensitive (p->text[i], FALSE);
            gtk_widget_set_size_request(GTK_WIDGET(p->text[i]),60,20);
            gtk_fixed_put(GTK_FIXED(p->vbox_ldw),p->label_ldw[i],5  ,5+30*i);
            gtk_fixed_put(GTK_FIXED(p->vbox_ldw),p->text[i]     ,250,5+30*i); 
        }
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
        gtk_widget_show_all(p->vbox_ldw);                     
   }
   else if(!strcmp(p->pos,"Probe"))
   {
       p->vbox_ldw=gtk_vbox_new(FALSE,0);
       p->frame_ps=gtk_frame_new("Probe setup");
       p->frame=gtk_frame_new("Probe");
       gtk_widget_set_size_request(GTK_WIDGET(p->frame_ps),200,200);
       gtk_widget_set_size_request(GTK_WIDGET(p->frame),200,500);
       /*probe setup*/
       p->vbox_wg=gtk_vbox_new(FALSE,0);
       p->label_wg=gtk_label_new("Type");
       
       p->hbox_wg = gtk_fixed_new();
	   p->linear_wg[0]= gtk_combo_box_entry_new_text();
	   gtk_widget_set_size_request(GTK_WIDGET(p->linear_wg[0]),130,25);
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->linear_wg[0]), "1D Linear array");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->linear_wg[0]), "2D Matrix array");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->linear_wg[0]), p->probe_p->D1_D2);
       g_signal_connect(G_OBJECT(p->linear_wg[0]),"changed" ,G_CALLBACK(D1_D2),(gpointer) p );
       //add database
       GtkWidget *image[3];
       p->database_btn[0] = gtk_button_new_with_label(NULL);//Import
       p->database_btn[1] = gtk_button_new_with_label(NULL);//Export
       p->database_btn[2] = gtk_button_new_with_label(NULL);//Delete
       image[0] = gtk_image_new_from_file("./image/import.jpg");
       image[1] = gtk_image_new_from_file("./image/export.jpg");
       image[2] = gtk_image_new_from_file("./image/delete.jpg");
       gtk_container_add(GTK_CONTAINER(p->database_btn[0]),image[0]);
       gtk_container_add(GTK_CONTAINER(p->database_btn[1]),image[1]);
       gtk_container_add(GTK_CONTAINER(p->database_btn[2]),image[2]);
       
       gtk_widget_set_size_request(GTK_WIDGET(p->database_btn[0]),35,35);
       gtk_widget_set_size_request(GTK_WIDGET(p->database_btn[1]),35,35);
       gtk_widget_set_size_request(GTK_WIDGET(p->database_btn[2]),35,35);
       g_signal_connect(G_OBJECT(p->database_btn[0]),"clicked",G_CALLBACK(probe_import),(gpointer) (p));
       g_signal_connect(G_OBJECT(p->database_btn[1]),"clicked",G_CALLBACK(probe_export),(gpointer) (p));
       g_signal_connect(G_OBJECT(p->database_btn[2]),"clicked",G_CALLBACK(probe_delete),(gpointer) (p));
       
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,5);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->linear_wg[0],40  ,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->database_btn[0],200  ,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->database_btn[1],240  ,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->database_btn[2],280  ,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->label_wg=gtk_label_new("Probe separation       ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (p->wedge_r->wg_separation, 0.0, 10000.0, 1.0, 0.1, 0.0);
       p->entry[0] = gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_widget_set_sensitive (p->entry[0], p->probe_p->Pitch_Catch);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[0]),60,20);
       p->label_p=gtk_label_new("mm");
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_wg),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry[0]),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_p),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->check_btn_p[0]=gtk_check_button_new_with_label("Pitch and Catch");
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->check_btn_p[0]),FALSE,FALSE,5);
       gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->check_btn_p[0]),p->probe_p->Pitch_Catch);
       g_signal_connect(G_OBJECT(p->check_btn_p[0]),"toggled",G_CALLBACK(Pitch_Catch),(gpointer) p );
       g_signal_connect(G_OBJECT(p->entry[0]),"value-changed" ,G_CALLBACK(WedgeSeparation),(gpointer) p );
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_wg=gtk_label_new("Transmitter wave");
       p->linear_wg[1]= gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->linear_wg[1]), "Transvers");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->linear_wg[1]), "Longitudinal");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->linear_wg[1]), p->probe_p->transmi_trans_longi);
       g_signal_connect(G_OBJECT(p->linear_wg[1]),"changed" ,G_CALLBACK(transmi_trans_longi),(gpointer) p );
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->linear_wg[1],110,0); 
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_wg=gtk_label_new("Receiver wave   ");
       p->linear_wg[2]= gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->linear_wg[2]), "Transvers");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->linear_wg[2]), "Longitudinal");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->linear_wg[2]), p->probe_p->transmi_trans_longi);
       g_signal_connect(G_OBJECT(p->linear_wg[2]),"changed" ,G_CALLBACK(recev_trans_longi),(gpointer) p );
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->linear_wg[2],110,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       
       gtk_container_add(GTK_CONTAINER(p->frame_ps),p->vbox_wg);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_ps),FALSE,FALSE,0);
       /*probe*/
       p->vbox_wg=gtk_vbox_new(FALSE,0);
       ///////////////////////////////
       p->D2ShowHBox[0]=gtk_fixed_new();
       p->label_wg = gtk_label_new("Transmit Element /nCofiguration") ;  
       p->SequenceComm[0] = gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->SequenceComm[0]), "Squence Type One");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->SequenceComm[0]), "Squence Type Two");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->SequenceComm[0]), 0);
       gtk_widget_set_size_request(GTK_WIDGET(p->SequenceComm[0]),150,20);
       g_signal_connect(G_OBJECT(p->SequenceComm[0]),"changed" ,G_CALLBACK(SequenceSelect2DT),(gpointer) p );   // not connect yet
   
       gtk_fixed_put(GTK_FIXED(p->D2ShowHBox[0]),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->D2ShowHBox[0]),p->SequenceComm[0],200,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->D2ShowHBox[0]),FALSE,FALSE,5);     
       
       p->D2ShowHBox[1]=gtk_fixed_new();
       p->label_wg = gtk_label_new("Receiver Element /nCofiguration") ;  
       p->SequenceComm[1] = gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->SequenceComm[1]), "Squence Type One");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->SequenceComm[1]), "Squence Type Two");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->SequenceComm[1]), 0);
       gtk_widget_set_size_request(GTK_WIDGET(p->SequenceComm[1]),150,20);
       g_signal_connect(G_OBJECT(p->SequenceComm[1]),"changed" ,G_CALLBACK(SequenceSelect2DR),(gpointer) p );   // not connect yet
       gtk_widget_set_sensitive (GTK_WIDGET(p->SequenceComm[1]), FALSE);

       gtk_fixed_put(GTK_FIXED(p->D2ShowHBox[1]),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->D2ShowHBox[1]),p->SequenceComm[1],200,0);	                            
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET (p->D2ShowHBox[1]),FALSE,FALSE,5);
       //////////////////////////
       p->hbox_wg=gtk_fixed_new();
       p->label_wg=gtk_label_new("Transmitter probe name ");
       p->entry[1]=gtk_entry_new(); 
       gtk_entry_set_text(GTK_ENTRY(p->entry[1]),p->probe_p->name);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[1]),100,20);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[1],150,0);	
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_wg=gtk_label_new("Receiver probe name    ");
       p->entry[2]=gtk_entry_new(); 
       gtk_entry_set_text(GTK_ENTRY(p->entry[2]),p->probe_p->name);
       gtk_widget_set_sensitive (GTK_WIDGET(p->entry[2]), p->probe_p->Pitch_Catch);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[2]),100,20);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[2],150,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
       p->label_wg=gtk_label_new("Transmitter");
       p->label_p=gtk_label_new("Receiver");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,150,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,230,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Probe screw angle     ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 360.0, 0.1, 1.0, 0.0);
       p->entry[3]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[3]),p->probe_p->pb_skew_angle);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[3]),70,20);
       g_signal_connect(G_OBJECT(p->entry[3]),"value-changed" ,G_CALLBACK(probe_skew),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 360.0, 0.1, 1.0, 0.0);
       p->entry[4]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[4]),p->probe_p->pb_skew_angle_r);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[4]),70,20);
       g_signal_connect(G_OBJECT(p->entry[4]),"value-changed" ,G_CALLBACK(probe_skew_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry[4], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("deg");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[3],150,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[4],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,310,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Probe frequency       ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 50000.0, 0.1, 1.0, 0.0);
       p->entry[5]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[5]),p->probe_p->pb_frequency);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[5]),70,20);
       g_signal_connect(G_OBJECT(p->entry[5]),"value-changed" ,G_CALLBACK(probe_frequency),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 50000.0, 0.1, 1.0, 0.0);
       p->entry[6]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[6]),p->probe_p->pb_frequency_r);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[6]),70,20);
       g_signal_connect(G_OBJECT(p->entry[6]),"value-changed" ,G_CALLBACK(probe_frequency_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry[6], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("MHz");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[5],150,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[6],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,310,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Number of elements    \non primary axis");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (32, 1, 256, 1, 1, 0);
       p->entry[7]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[7]),p->probe_p->ele_num_pri);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[7]),70,20);
       g_signal_connect(G_OBJECT(p->entry[7]),"value-changed" ,G_CALLBACK(probe_ele_num),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (32, 1, 256, 1, 1, 0);
       p->entry[8]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[8]),p->probe_p->ele_num_pri_r);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[8]),70,20);
       g_signal_connect(G_OBJECT(p->entry[8]),"value-changed" ,G_CALLBACK(probe_ele_num_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry[8], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new(" ");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[7],150,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[8],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,310,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //***** add by ss for 2d probe
       p->D2ShowHBox[2]=gtk_fixed_new();
       p->label_wg=gtk_label_new("Number of elements    \non second axis");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (32, 1, 256, 1, 1, 0);
       p->entry[15]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[15]),p->probe_p->ele_num_sec);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[15]),70,20);
       g_signal_connect(G_OBJECT(p->entry[15]),"value-changed", G_CALLBACK(probe_sec_ele_num),(gpointer)p)  ;
               
       p->adj = (GtkAdjustment *) gtk_adjustment_new (32, 1, 256, 1, 1, 0);
       p->entry[16]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[16]),p->probe_p->ele_num_sec_r);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[16]),70,20);
       g_signal_connect(G_OBJECT(p->entry[16]),"value-changed" ,G_CALLBACK(probe_sec_ele_num_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry[16], p->probe_p->Pitch_Catch); 
               
       gtk_fixed_put(GTK_FIXED(p->D2ShowHBox[2]),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->D2ShowHBox[2]),p->entry[15],150,0);
       gtk_fixed_put(GTK_FIXED(p->D2ShowHBox[2]),p->entry[16],230,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),p->D2ShowHBox[2],FALSE,FALSE,5);  
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Primary axis pitch    ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 10000.0, 0.1, 1.0, 0.0);
       p->entry[9]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[9]),p->probe_p->pri_axis_pitch);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[9]),70,20);
       g_signal_connect(G_OBJECT(p->entry[9]),"value-changed" ,G_CALLBACK(probe_pri_axis_pitch),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 10000.0, 0.1, 1.0, 0.0);
       p->entry[10]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[10]),p->probe_p->pri_axis_pitch_r);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[10]),70,20);
       g_signal_connect(G_OBJECT(p->entry[10]),"value-changed" ,G_CALLBACK(probe_pri_axis_pitch_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry[10], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[9],150,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[10],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,310,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //***** add by ss for 2d probe
	   p->D2ShowHBox[3]=gtk_fixed_new();
      p->label_wg=gtk_label_new("Second axis pitch     ");
      p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 10000.0, 0.1, 1.0, 0.0);
      p->entry[17]= gtk_spin_button_new (p->adj, 1.0, 1);
      gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[17]),p->probe_p->sec_axis_pitch);
      gtk_widget_set_size_request(GTK_WIDGET(p->entry[17]),70,20);
      g_signal_connect(G_OBJECT(p->entry[17]),"value-changed" ,G_CALLBACK(probe_sec_axis_pitch),(gpointer) p );

      p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 10000.0, 0.1, 1.0, 0.0);
      p->entry[18]= gtk_spin_button_new (p->adj, 1.0, 1);
      gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[18]),p->probe_p->sec_axis_pitch_r);
      gtk_widget_set_size_request(GTK_WIDGET(p->entry[18]),70,20);
      g_signal_connect(G_OBJECT(p->entry[18]),"value-changed" ,G_CALLBACK(probe_sec_axis_pitch_r),(gpointer) p );
      gtk_widget_set_sensitive (p->entry[18], p->probe_p->Pitch_Catch);

      p->label_p=gtk_label_new("mm");
      gtk_fixed_put(GTK_FIXED(p->D2ShowHBox[3]),p->label_wg,5  ,0);
      gtk_fixed_put(GTK_FIXED(p->D2ShowHBox[3]),p->entry[17],150,0);
      gtk_fixed_put(GTK_FIXED(p->D2ShowHBox[3]),p->entry[18],230,0);
      gtk_fixed_put(GTK_FIXED(p->D2ShowHBox[3]),p->label_p ,310,0);
      gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->D2ShowHBox[3]),FALSE,FALSE,5);
       ///////////////////////
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Primary element size  ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 10000.0, 0.1, 1.0, 0.0);
       p->entry[11]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[11]),p->probe_p->pri_ele_size);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[11]),70,20);
       g_signal_connect(G_OBJECT(p->entry[11]),"value-changed" ,G_CALLBACK(probe_pri_elem_size),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 10000.0, 0.1, 1.0, 0.0);
       p->entry[12]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[12]),p->probe_p->pri_ele_size_r);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[12]),70,20);
       g_signal_connect(G_OBJECT(p->entry[12]),"value-changed" ,G_CALLBACK(probe_pri_elem_size_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry[12], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[11],150,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[12],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,310,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Secondary element size");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 10000.0, 0.1, 1.0, 0.0);
       p->entry[13]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[13]),p->probe_p->sec_ele_size);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[13]),70,20);
       g_signal_connect(G_OBJECT(p->entry[13]),"value-changed" ,G_CALLBACK(probe_sec_elem_size),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 10000.0, 0.1, 1.0, 0.0);
       p->entry[14]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[14]),p->probe_p->sec_ele_size_r);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry[14]),70,20);
       g_signal_connect(G_OBJECT(p->entry[14]),"value-changed" ,G_CALLBACK(probe_sec_elem_size_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry[14], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[13],150,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry[14],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,310,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Reverse primary axis ");
	   p->check_btn_p[1]=gtk_check_button_new();
	   p->check_btn_p[2]=gtk_check_button_new();
	   gtk_widget_set_sensitive (p->check_btn_p[2], p->probe_p->Pitch_Catch);
	   p->label_p=gtk_label_new("");
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->check_btn_p[1],150,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->check_btn_p[2],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,310,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Fit to surface       ");
	   p->check_btn_p[3]=gtk_check_button_new();
	   p->check_btn_p[4]=gtk_check_button_new();
	   gtk_widget_set_sensitive (p->check_btn_p[4], p->probe_p->Pitch_Catch);
	   p->label_p=gtk_label_new("");
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->check_btn_p[3],150,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->check_btn_p[4],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,310,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       
       gtk_container_add(GTK_CONTAINER(p->frame),p->vbox_wg);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame),FALSE,FALSE,5);
       
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
       gtk_widget_show_all(p->vbox_ldw); 
       switch(p->probe_p->D1_D2)
       {
         case 0:            
              gtk_widget_hide(GTK_WIDGET(p->D2ShowHBox[0]));
              gtk_widget_hide(GTK_WIDGET(p->D2ShowHBox[1]));
              gtk_widget_hide(GTK_WIDGET(p->D2ShowHBox[2]));
              gtk_widget_hide(GTK_WIDGET(p->D2ShowHBox[3]));
              break;
         case 1:
              gtk_widget_show(GTK_WIDGET(p->D2ShowHBox[0]));
              gtk_widget_show(GTK_WIDGET(p->D2ShowHBox[1]));
              gtk_widget_show(GTK_WIDGET(p->D2ShowHBox[2]));
              gtk_widget_show(GTK_WIDGET(p->D2ShowHBox[3]));
              break;                       
      }
   }
   else if(!strcmp(p->pos,"Wedge"))
   {
       p->vbox_ldw=gtk_vbox_new(FALSE,0);
       p->vbox_wg=gtk_vbox_new(FALSE,0);
       p->frame=gtk_frame_new(NULL);
       gtk_widget_set_size_request(GTK_WIDGET(p->frame),280,700);
       //
       p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->label_wg=gtk_label_new("Transmitter");
       p->entry_wg[0]=gtk_entry_new(); 
       gtk_entry_set_text(GTK_ENTRY(p->entry_wg[0]),p->wedge_p->name);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[0]),150,25);
       p->label_wg_l=gtk_label_new("  ");
       //add database
       GtkWidget *image[3];
       p->database_btn_wg[0] = gtk_button_new_with_label(NULL);//Import
       p->database_btn_wg[1] = gtk_button_new_with_label(NULL);//Export
       p->database_btn_wg[2] = gtk_button_new_with_label(NULL);//Delete
       image[0] = gtk_image_new_from_file("./image/import.jpg");
       image[1] = gtk_image_new_from_file("./image/export.jpg");
       image[2] = gtk_image_new_from_file("./image/delete.jpg");
       gtk_container_add(GTK_CONTAINER(p->database_btn_wg[0]),image[0]);
       gtk_container_add(GTK_CONTAINER(p->database_btn_wg[1]),image[1]);
       gtk_container_add(GTK_CONTAINER(p->database_btn_wg[2]),image[2]);
       gtk_widget_set_size_request(GTK_WIDGET(p->database_btn_wg[0]),35,35);
       gtk_widget_set_size_request(GTK_WIDGET(p->database_btn_wg[1]),35,35);
       gtk_widget_set_size_request(GTK_WIDGET(p->database_btn_wg[2]),35,35);      
       g_signal_connect(G_OBJECT(p->database_btn_wg[0]),"clicked",G_CALLBACK(wedge_import),(gpointer) (p));
       g_signal_connect(G_OBJECT(p->database_btn_wg[1]),"clicked",G_CALLBACK(wedge_export),(gpointer) (p));
       g_signal_connect(G_OBJECT(p->database_btn_wg[2]),"clicked",G_CALLBACK(wedge_delete),(gpointer) (p));
       
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_wg),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry_wg[0]),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_wg_l),FALSE,FALSE,2);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->database_btn_wg[0]),FALSE,FALSE,2);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->database_btn_wg[1]),FALSE,FALSE,2);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->database_btn_wg[2]),FALSE,FALSE,2);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_wg=gtk_label_new("Receiver");
       p->entry_wg[1]=gtk_entry_new(); 
       gtk_entry_set_text(GTK_ENTRY(p->entry_wg[1]),p->wedge_p->name);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[1]),150,25);
       gtk_widget_set_sensitive (p->entry_wg[1], p->probe_p->Pitch_Catch);
       p->label_wg_l=gtk_label_new("");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[1],80,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg_l ,100,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_wg=gtk_label_new("Footprint");
       p->flat_wg= gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->flat_wg), "Flat");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->flat_wg), "Pipe OD");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->flat_wg), "Pipe ID");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->flat_wg), p->footprint);
       gtk_widget_set_sensitive (p->flat_wg, p->probe_p->Pitch_Catch);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->flat_wg,80,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_wg=gtk_label_new("T");
       p->label_wg_l=gtk_label_new("R");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg  ,200,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg_l,280,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Wedge angle");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 89.9, 0.1, 1.0, 0.0);
       p->entry_wg[2]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[2]),p->wedge_p->wg_wedge_angle);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[2]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[2]),"value-changed" ,G_CALLBACK(wg_wedge_angle),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.0, 89.9, 0.1, 1.0, 0.0);
       p->entry_wg[3]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[3]),p->wedge_r->wg_wedge_angle);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[3]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[3]),"value-changed" ,G_CALLBACK(wg_wedge_angle_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[3], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("deg");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[2],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[3],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Roof angle                  ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -180.0, 180.0, 0.1, 1.0, 0.0);
       p->entry_wg[4]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[4]),p->wedge_p->wg_roof_angle);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[4]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[4]),"value-changed" ,G_CALLBACK(wg_roof_angle),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -180.0, 180.0, 0.1, 1.0, 0.0);
       p->entry_wg[5]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[5]),p->wedge_r->wg_roof_angle);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[5]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[5]),"value-changed" ,G_CALLBACK(wg_roof_angle_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[5], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("deg");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[4],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[5],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Longitudinal sound velocity ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 20000, 1, 1, 0.0);
       p->entry_wg[6]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[6]),p->wedge_p->wg_lon_vel);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[6]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[6]),"value-changed" ,G_CALLBACK(wg_lon_vel),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 20000, 1, 1, 0.0);
       p->entry_wg[7]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[7]),p->wedge_r->wg_lon_vel);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[7]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[7]),"value-changed" ,G_CALLBACK(wg_lon_vel_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[7], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("m/s");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[6],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[7],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Transverse sound velocity   ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 20000, 1, 1, 0.0);
       p->entry_wg[8]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[8]),p->wedge_p->wg_trans_vel);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[8]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[8]),"value-changed" ,G_CALLBACK(wg_trans_vel),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 20000, 1, 1, 0.0);
       p->entry_wg[9]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[9]),p->wedge_r->wg_trans_vel);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[9]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[9]),"value-changed" ,G_CALLBACK(wg_trans_vel_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[9], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("m/s");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[8],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[9],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Density                     ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000, 1, 1, 0.0);
       p->entry_wg[10]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[10]),p->wedge_p->wg_density);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[10]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[10]),"value-changed" ,G_CALLBACK(wg_density),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000, 1, 1, 0.0);
       p->entry_wg[11]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[11]),p->wedge_r->wg_density);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[11]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[11]),"value-changed" ,G_CALLBACK(wg_density_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[11], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("kg/m3");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[10],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[11],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Height at the middle of the \nfirst element");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 1.0, 1.0, 0.0);
       p->entry_wg[12]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[12]),p->wedge_p->wg_heigh_fir);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[12]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[12]),"value-changed" ,G_CALLBACK(wg_heigh_fir),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 1.0, 1.0, 0.0);
       p->entry_wg[13]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[13]),p->wedge_r->wg_heigh_fir);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[13]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[13]),"value-changed" ,G_CALLBACK(wg_heigh_fir_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[13], p->probe_p->Pitch_Catch);
      
       p->label_p=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[12],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[13],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Parimary axis offset of the \nmiddle of the first element");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[14]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[14]),p->wedge_p->wg_pri_elem_offset_fir);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[14]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[14]),"value-changed" ,G_CALLBACK(wg_pri_elem_offset_fir),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[15]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[15]),p->wedge_r->wg_pri_elem_offset_fir);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[15]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[15]),"value-changed" ,G_CALLBACK(wg_pri_elem_offset_fir_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[15], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[14],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[15],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Secondary axis offset of the\nmiddle of the first element");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[16]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[16]),p->wedge_p->wg_sec_elem_offset_fir);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[16]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[16]),"value-changed" ,G_CALLBACK(wg_sec_elem_offset_fir),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[17]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[17]),p->wedge_r->wg_sec_elem_offset_fir);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[17]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[17]),"value-changed" ,G_CALLBACK(wg_sec_elem_offset_fir_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[17], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[16],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[17],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Parimary axis position of   \n wedge reference ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, -10000.0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[18]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[18]),p->wedge_p->wg_pri_axis_reference);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[18]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[18]),"value-changed" ,G_CALLBACK(wg_pri_axis_reference),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, -10000.0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[19]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[19]),p->wedge_r->wg_pri_axis_reference);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[19]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[19]),"value-changed" ,G_CALLBACK(wg_pri_axis_reference_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[19], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[18],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[19],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Secondary axis position of  \n wedge reference ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, -10000.0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[20]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[20]),p->wedge_p->wg_sec_axis_reference);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[20]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[20]),"value-changed" ,G_CALLBACK(wg_sec_axis_reference),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, -10000.0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[21]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[21]),p->wedge_r->wg_sec_axis_reference);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[21]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[21]),"value-changed" ,G_CALLBACK(wg_sec_axis_reference_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[21], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[20],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[21],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Wedge length                ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[22]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[22]),p->wedge_p->wg_length);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[22]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[22]),"value-changed" ,G_CALLBACK(wg_length),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[23]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[23]),p->wedge_r->wg_length);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[23]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[23]),"value-changed" ,G_CALLBACK(wg_length_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[23], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[22],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[23],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Wedge width");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[24]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[24]),p->wedge_p->wg_width);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[24]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[24]),"value-changed" ,G_CALLBACK(wg_width),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[25]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[25]),p->wedge_r->wg_width);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[25]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[25]),"value-changed" ,G_CALLBACK(wg_width_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[25], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[24],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[25],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
	   p->label_wg=gtk_label_new("Wedge height                ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[26]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[26]),p->wedge_p->wg_height);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[26]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[26]),"value-changed" ,G_CALLBACK(wg_height),(gpointer) p );
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 0.1, 0.1, 0.0);
       p->entry_wg[27]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[27]),p->wedge_r->wg_height);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_wg[27]),70,20);
       g_signal_connect(G_OBJECT(p->entry_wg[27]),"value-changed" ,G_CALLBACK(wg_height_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_wg[27], p->probe_p->Pitch_Catch);
       
       p->label_p=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_wg,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[26],180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_wg[27],260,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_p ,340,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->btn_wg=gtk_button_new_with_label("Import Material");
       update_widget_bg(p->btn_wg, "./image/bg.jpg");
       g_signal_connect(G_OBJECT(p->btn_wg),"clicked" ,G_CALLBACK(import_material),(gpointer) p );
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->btn_wg ,200,5);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       
       gtk_container_add(GTK_CONTAINER(p->frame),p->vbox_wg);
       //gtk_container_add(GTK_CONTAINER(p->vbox_ldw),p->frame);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame),FALSE,FALSE,5);
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
       gtk_widget_show_all(p->vbox_ldw);
   }
   else if(!strcmp(p->pos,"Scanner"))
   {
       p->vbox_ldw=gtk_vbox_new(FALSE,0);
       p->frame_g=gtk_frame_new("Grouping");
       p->frame_pof=gtk_frame_new("Probe Offset");
       p->frame_por=gtk_frame_new("Probe Orientation");
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_g),FALSE,FALSE,5);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_pof),FALSE,FALSE,5);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_por),FALSE,FALSE,5);
       gtk_widget_set_size_request(GTK_WIDGET(p->frame_g),100,40);
       gtk_widget_set_size_request(GTK_WIDGET(p->frame_pof),100,120);
       gtk_widget_set_size_request(GTK_WIDGET(p->frame_por),100,120);      
       //
       p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->label_g=gtk_label_new("Group Number");
       p->grp_num= gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->grp_num),"");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->grp_num), 0);
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_g),FALSE,FALSE,5);
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->grp_num),FALSE,FALSE,5);
       gtk_container_add(GTK_CONTAINER(p->frame_g),p->hbox_wg);
       
       p->vbox_wg=gtk_vbox_new(FALSE,0);
       
       p->hbox_wg=gtk_fixed_new();
       p->label_g=gtk_label_new("Scan Axis  ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 0, 500.0, 0.1, 0.1, 0.0);
	   p->entry_sc[0]=gtk_spin_button_new (p->adj, 1.0, 1); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_sc[0]),p->scanner->scan_axis_off);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_sc[0]),50,20);
       g_signal_connect(G_OBJECT(p->entry_sc[0]),"value-changed" ,G_CALLBACK(scan_axis_off),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_sc[0], FALSE);
	   
       p->label_g_l=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_sc[0],80,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g_l,140,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_g=gtk_label_new("Index Axis ");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 0, 500.0, 0.1, 0.1, 0.0);
	   p->entry_sc[1]=gtk_spin_button_new (p->adj, 1.0, 1); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_sc[1]),p->scanner->index_axis_off);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_sc[1]),50,20);
       g_signal_connect(G_OBJECT(p->entry_sc[1]),"value-changed" ,G_CALLBACK(index_axis_off),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_sc[1], FALSE);
       
       p->label_g_l=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_sc[1],80,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g_l,140,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_g=gtk_label_new("Usound Axis");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 0, 500.0, 0.1, 0.1, 0.0);
	   p->entry_sc[2]=gtk_spin_button_new (p->adj, 1.0, 1); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_sc[2]),p->scanner->usound_axis_off);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_sc[2]),50,20);
       g_signal_connect(G_OBJECT(p->entry_sc[2]),"value-changed" ,G_CALLBACK(usound_axis_off),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_sc[2], FALSE);
       
       p->label_g_l=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_sc[2],80,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g_l,140,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       
       gtk_container_add(GTK_CONTAINER(p->frame_pof),p->vbox_wg);
       //
       p->vbox_wg=gtk_vbox_new(FALSE,0);
       ////////////////////////////
       p->hbox_wg=gtk_fixed_new();
       p->label_g=gtk_label_new("Scan Axis  ");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 0, 500.0, 0.1, 0.1, 0.0);
	   p->entry_sc[3]=gtk_spin_button_new (p->adj, 1.0, 1); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_sc[3]),p->scanner->scan_axis_ori);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_sc[3]),50,20);
       g_signal_connect(G_OBJECT(p->entry_sc[3]),"value-changed" ,G_CALLBACK(scan_axis_ori),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_sc[3], FALSE);
       
       p->label_g_l=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_sc[3],80,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g_l,140,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_g=gtk_label_new("Index Axis ");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 0, 500.0, 0.1, 0.1, 0.0);
	   p->entry_sc[4]=gtk_spin_button_new (p->adj, 1.0, 1); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_sc[4]),p->scanner->index_axis_ori);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_sc[4]),50,20);
       g_signal_connect(G_OBJECT(p->entry_sc[4]),"value-changed" ,G_CALLBACK(index_axis_ori),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_sc[4], FALSE);
       
       p->label_g_l=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_sc[4],80,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g_l,140,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_g=gtk_label_new("Usound Axis");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 0, 500.0, 0.1, 0.1, 0.0);
	   p->entry_sc[5]=gtk_spin_button_new (p->adj, 1.0, 1); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_sc[5]),p->scanner->usound_axis_ori);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_sc[5]),50,20);
       g_signal_connect(G_OBJECT(p->entry_sc[5]),"value-changed" ,G_CALLBACK(usound_axis_ori),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_sc[5], FALSE);
       
       p->label_g_l=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_sc[5],80,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_g_l,140,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       
       gtk_container_add(GTK_CONTAINER(p->frame_por),p->vbox_wg);
       
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
       gtk_widget_show_all(p->vbox_ldw);
   }
   else if(!strcmp(p->pos,"Beam angle selection"))
   {
       p->vbox_ldw=gtk_vbox_new(FALSE,0);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_beam=gtk_label_new("Type     "); 
	   p->combox_beam[0]= gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_beam[0]), "Azimuthal");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_beam[0]), "Linear");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_beam[0]), "Depth");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_beam[0]), "Static");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->combox_beam[0]), p->beam_angle->beam_type);
       g_signal_connect(G_OBJECT(p->combox_beam[0]),"changed" ,G_CALLBACK(beam_type),(gpointer) p );
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->combox_beam[0],80,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
       p->label_beam=gtk_label_new("Selection"); 
	   p->combox_beam[1]= gtk_combo_box_entry_new_text();
	   switch(p->probe_p->D1_D2)
	   {
          case 0:
                gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_beam[1]), "Refracted angle");
                gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_beam[1]), "Primary steering angle");
                gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_beam[1]), "Beam screw angle");
                break;
          case 1:
                gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_beam[1]), "Primary/Secondary steering angle");
                gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_beam[1]), "Primary/Beam skew angle");
                gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_beam[1]), "Secondary/Refracted angle");
                gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_beam[1]), "Refracted/Beam skew angle");
                break;        
       }
       
       
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->combox_beam[1]), p->beam_angle->beam_angle_sel);
       g_signal_connect(G_OBJECT(p->combox_beam[1]),"changed" ,G_CALLBACK(beam_angle_sel),(gpointer) p );
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->combox_beam[1],80,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
	   p->label_beam1=gtk_label_new("Start");
	   p->label_beam2=gtk_label_new("Stop");
	   p->label_beam3=gtk_label_new("Resolution");
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam1,180,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam2,250,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam3,305,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
	   p->label_beam=gtk_label_new("Primary steering angle  ");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -89.9, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[0]= gtk_spin_button_new (p->adj, 1.0, 1);
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -89.9, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[1]= gtk_spin_button_new (p->adj, 1.0, 1);
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.1, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[2]= gtk_spin_button_new (p->adj, 1.0, 1);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[0]),p->beam_angle->beam_pri_steer_angle_start);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[1]),p->beam_angle->beam_pri_steer_angle_stop);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[2]),p->beam_angle->beam_pri_steer_angle_resolution);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[0]),70,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[1]),70,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[2]),70,20);
       g_signal_connect(G_OBJECT(p->entry_beam[0]),"value-changed" ,G_CALLBACK(beam_pri_steer_angle_start),(gpointer) p );
       g_signal_connect(G_OBJECT(p->entry_beam[1]),"value-changed" ,G_CALLBACK(beam_pri_steer_angle_stop),(gpointer) p );
       g_signal_connect(G_OBJECT(p->entry_beam[2]),"value-changed" ,G_CALLBACK(beam_pri_steer_angle_resolution),(gpointer) p );
       p->label_beam1=gtk_label_new("deg");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[0],160,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[1],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[2],300,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam1  ,370,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
	   p->label_beam=gtk_label_new("Secondary steering angle");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -89.9, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[3]= gtk_spin_button_new (p->adj, 1.0, 1);
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -89.9, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[4]= gtk_spin_button_new (p->adj, 1.0, 1);
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.1, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[5]= gtk_spin_button_new (p->adj, 1.0, 1);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[3]),p->beam_angle->beam_sec_steer_angle_start);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[4]),p->beam_angle->beam_sec_steer_angle_stop);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[5]),p->beam_angle->beam_sec_steer_angle_resolution);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[3]),70,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[4]),70,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[5]),70,20);
       g_signal_connect(G_OBJECT(p->entry_beam[3]),"value-changed" ,G_CALLBACK(beam_sec_steer_angle_start),(gpointer) p );
       g_signal_connect(G_OBJECT(p->entry_beam[4]),"value-changed" ,G_CALLBACK(beam_sec_steer_angle_stop),(gpointer) p );
       g_signal_connect(G_OBJECT(p->entry_beam[5]),"value-changed" ,G_CALLBACK(beam_sec_steer_angle_resolution),(gpointer) p );
       p->label_beam1=gtk_label_new("deg");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[3],160,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[4],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[5],300,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam1  ,370,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
	   p->label_beam=gtk_label_new("Refraction angle        ");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -89.9, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[6]= gtk_spin_button_new (p->adj, 1.0, 1);
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -89.9, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[7]= gtk_spin_button_new (p->adj, 1.0, 1);
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0.1, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[8]= gtk_spin_button_new (p->adj, 1.0, 1);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[6]),p->beam_angle->beam_refrac_angle_start);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[7]),p->beam_angle->beam_refrac_angle_stop);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[8]),p->beam_angle->beam_refrac_angle_resolution);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[6]),70,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[7]),70,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[8]),70,20);
       g_signal_connect(G_OBJECT(p->entry_beam[6]),"value-changed" ,G_CALLBACK(beam_refrac_angle_start),(gpointer) p );
       g_signal_connect(G_OBJECT(p->entry_beam[7]),"value-changed" ,G_CALLBACK(beam_refrac_angle_stop),(gpointer) p );
       g_signal_connect(G_OBJECT(p->entry_beam[8]),"value-changed" ,G_CALLBACK(beam_refrac_angle_resolution),(gpointer) p );
       
       p->label_beam1=gtk_label_new("deg");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[6],160,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[7],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[8],300,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam1  ,370,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
	   p->label_beam=gtk_label_new("Beam screw angle        ");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -89.9, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[9]= gtk_spin_button_new (p->adj, 1.0, 1);
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -89.9, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[10]= gtk_spin_button_new (p->adj, 1.0, 1);
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -0.1, 89.9, 0.1, 1.0, 0.0);
	   p->entry_beam[11]= gtk_spin_button_new (p->adj, 1.0, 1);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[9]),p->beam_angle->beam_skew_angle_start);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[10]),p->beam_angle->beam_skew_angle_stop);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_beam[11]),p->beam_angle->beam_skew_angle_resolution);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[9]),70,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[10]),70,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_beam[11]),70,20);
       p->label_beam1=gtk_label_new("deg");
       g_signal_connect(G_OBJECT(p->entry_beam[9]),"value-changed" ,G_CALLBACK(beam_skew_angle_start),(gpointer) p );
       g_signal_connect(G_OBJECT(p->entry_beam[10]),"value-changed" ,G_CALLBACK(beam_skew_angle_stop),(gpointer) p );
       g_signal_connect(G_OBJECT(p->entry_beam[11]),"value-changed" ,G_CALLBACK(beam_skew_angle_resolution),(gpointer) p );
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam,5,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[9],160,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[10],230,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_beam[11],300,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_beam1  ,370,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   gint i;
       p->element_sel->linear = 0;
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
	   //
	   p->hbox_wg=gtk_fixed_new();
       p->btn_beam=gtk_button_new_with_label("Process angle");
	   g_signal_connect(G_OBJECT(p->btn_beam),"clicked" ,G_CALLBACK(btn_beam),(gpointer) p );
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->btn_beam,100  ,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
       gtk_widget_show_all(p->vbox_ldw);
   }
   else if(!strcmp(p->pos,"Focal point selection"))
   {
       p->vbox_ldw=gtk_vbox_new(FALSE,0);
       //
       p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->label_focal=gtk_label_new("Focusing type"); 
	   p->combox_focal= gtk_combo_box_entry_new_text();
	   if(p->probe_p->Pitch_Catch)
	   {
           gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_focal), "Half path");
           gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_focal), "True depth");  
           gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_focal), "Automatic");                                               
       }
       else
       {
           if(p->beam_angle-> beam_type == 2)
    	   {
               gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_focal), "Half path");
               gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_focal), "True depth");               
           }
           else
           {
               gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_focal), "Half path");
               gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_focal), "True depth");
               gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_focal), "Projection");
               gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_focal), "Focal plane");
           }
       }
           
              
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->combox_focal), p->focal_point->focal_focus_type);
       g_signal_connect(G_OBJECT(p->combox_focal),"changed" ,G_CALLBACK(focal_focus_type),(gpointer) p );
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_focal),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->combox_focal),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
	   p->label_focal1=gtk_label_new("Start");
	   p->label_focal2=gtk_label_new("Stop");
	   p->label_focal3=gtk_label_new("Resolution");
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_focal1,150  ,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_focal2,200  ,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_focal3,250  ,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
   	   p->hbox_wg=gtk_hbox_new(FALSE,0);
	   p->label_focal=gtk_label_new("Emission focus position");
	   
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 1, 1, 0.0);
	   p->entry_foc[0]=gtk_spin_button_new (p->adj, 1.0, 1);
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 1, 1, 0.0);
	   p->entry_foc[1]=gtk_spin_button_new (p->adj, 1.0, 1);
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000.0, 1, 1, 0.0);
	   p->entry_foc[2]=gtk_spin_button_new (p->adj, 1.0, 1);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_foc[0]),p->focal_point->focal_focus_point_start);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_foc[1]),p->focal_point->focal_focus_point_stop);
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_foc[2]),p->focal_point->focal_focus_point_resolution);
       
       g_signal_connect(G_OBJECT( p->entry_foc[0]),"value-changed" ,G_CALLBACK(focal_focus_point_start),(gpointer) p );
       g_signal_connect(G_OBJECT( p->entry_foc[1]),"value-changed" ,G_CALLBACK(focal_focus_point_stop),(gpointer) p );
       g_signal_connect(G_OBJECT( p->entry_foc[2]),"value-changed" ,G_CALLBACK(focal_focus_point_resolution),(gpointer) p );
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_foc[0]),50,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_foc[1]),50,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_foc[2]),50,20);
       
       p->label_focal1=gtk_label_new("mm");
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_focal),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry_foc[0]),FALSE,FALSE,0);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry_foc[1]),FALSE,FALSE,0);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry_foc[2]),FALSE,FALSE,0);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_focal1),FALSE,FALSE,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->frame_focal=gtk_frame_new("Focal plane position");
	   gtk_widget_set_size_request(GTK_WIDGET(p->frame_focal),100,120);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_focal),FALSE,FALSE,5);
	   p->vbox_wg=gtk_vbox_new(FALSE,0);
	   
	   p->hbox_wg=gtk_fixed_new();
	   p->label_focal1=gtk_label_new("Start");
	   p->label_focal2=gtk_label_new("Stop");
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_focal1,60,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_focal2,110,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new();
       p->label_focal=gtk_label_new("Offset");
	   
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -10000.0, 10000.0, 0.1, 1.0, 0.0);
       p->entry_foc[3]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_foc[3]),p->focal_point->offset_start);
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -10000.0, 10000.0, 0.1, 1.0, 0.0);
       p->entry_foc[4]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_foc[4]),p->focal_point->offset_end);
       g_signal_connect(G_OBJECT(p->entry_foc[3]),"value-changed" ,G_CALLBACK(offset_start),(gpointer) p );
       g_signal_connect(G_OBJECT(p->entry_foc[4]),"value-changed" ,G_CALLBACK(offset_end),(gpointer) p );
       
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_foc[3]),50,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_foc[4]),50,20);
       p->label_focal1=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_focal ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_foc[3],50,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_foc[4],100,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_focal1,150,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new();
       p->label_focal=gtk_label_new("Depth ");
       	   
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -10000.0, 10000.0, 0.1, 1.0, 0.0);
       p->entry_foc[5]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_foc[5]),p->focal_point->depth_start);
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, -10000.0, 10000.0, 0.1, 1.0, 0.0);
       p->entry_foc[6]= gtk_spin_button_new (p->adj, 1.0, 1);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_foc[6]),p->focal_point->depth_end);
       g_signal_connect(G_OBJECT(p->entry_foc[5]),"value-changed" ,G_CALLBACK(depth_start),(gpointer) p );
       g_signal_connect(G_OBJECT(p->entry_foc[6]),"value-changed" ,G_CALLBACK(depth_end),(gpointer) p );
       
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_foc[5]),50,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_foc[6]),50,20);
       p->label_focal1=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_focal ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_foc[5],50,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_foc[6],100,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_focal1,150,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   gtk_container_add(GTK_CONTAINER(p->frame_focal),p->vbox_wg);
	   //
	   gint i;
       for(i=0;i<7;i++)
            gtk_widget_set_sensitive (p->entry_foc[i], FALSE);
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
       if(p->beam_angle-> beam_type == 2)
       {
          gtk_widget_set_sensitive (p->entry_foc[0], TRUE);
          gtk_widget_set_sensitive (p->entry_foc[1], TRUE);
          gtk_widget_set_sensitive (p->entry_foc[2], TRUE);                
       }
       //
	   p->frame_focal=gtk_frame_new("DDF");
	   gtk_widget_set_size_request(GTK_WIDGET(p->frame_focal),100,120);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_focal),FALSE,FALSE,5);
	   p->vbox_wg=gtk_vbox_new(FALSE,0);
	   
       p->check_focal=gtk_check_button_new_with_label("DDF");
	   gtk_widget_set_sensitive (p->check_focal, FALSE);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->check_focal),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_hbox_new(FALSE,0);
	   p->label_focal=gtk_label_new("");
	   p->label_focal1=gtk_label_new("Start");
	   p->label_focal2=gtk_label_new("Stop");
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_focal),FALSE,FALSE,85);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_focal1),FALSE,FALSE,7);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_focal2),FALSE,FALSE,10);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->label_focal=gtk_label_new("Reception focus position");
	   p->entry_foc[7]=gtk_entry_new();
	   p->entry_foc[8]=gtk_entry_new();
	   gtk_entry_set_text(GTK_ENTRY(p->entry_foc[7]),"50.00");
	   gtk_entry_set_text(GTK_ENTRY(p->entry_foc[8]),"50.00");
       gtk_widget_set_sensitive (p->entry_foc[7], FALSE);
       gtk_widget_set_sensitive (p->entry_foc[8], FALSE);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_foc[7]),50,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_foc[8]),50,20);
       p->label_focal1=gtk_label_new("mm");
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_focal),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry_foc[7]),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry_foc[8]),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_focal1),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   gtk_container_add(GTK_CONTAINER(p->frame_focal),p->vbox_wg);
	   
       
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
       gtk_widget_show_all(p->vbox_ldw);
   }
   else if(!strcmp(p->pos,"Element selection"))
   {
       p->vbox_ldw=gtk_vbox_new(FALSE,0);
       p->frame_elem=gtk_frame_new("Transmitter");
	   gtk_widget_set_size_request(GTK_WIDGET(p->frame_elem),100,220);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_elem),FALSE,FALSE,5);
	   p->vbox_wg=gtk_vbox_new(FALSE,0);
	   	   
	   p->hbox_wg=gtk_fixed_new();
	   p->label_elem2=gtk_label_new("Start");
	   p->label_elem3=gtk_label_new("Stop");
	   p->label_elem4=gtk_label_new("Resolution");
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem2,160  ,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem3,210  ,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem4,260  ,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new(); 
       p->label_elem1=gtk_label_new("Primary axis");
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 1, 9999, 1, 1, 0);
	   p->entry_elem[0]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[0]),p->element_sel->primary_axis_s);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[0]),50,20);
       g_signal_connect(G_OBJECT(p->entry_elem[0]),"value-changed" ,G_CALLBACK(primary_axis_s),(gpointer) p );
//       gtk_widget_set_sensitive (p->entry_elem[0], FALSE);

       p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, 9999, 1, 1, 0);
	   p->entry_elem[1]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[1]),p->element_sel->primary_axis_e);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[1]),50,20);
       g_signal_connect(G_OBJECT(p->entry_elem[1]),"value-changed" ,G_CALLBACK(primary_axis_e),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_elem[1], p->element_sel->linear);
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, 9999, 1, 1, 0);
	   p->entry_elem[2]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[2]),p->element_sel->primary_axis_r);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[2]),50,20);
       g_signal_connect(G_OBJECT(p->entry_elem[2]),"value-changed" ,G_CALLBACK(primary_axis_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_elem[2], p->element_sel->linear);

       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem1  ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[0],160,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[1],210,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[2],260,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new();
       p->label_elem1=gtk_label_new("Seconary axis          ");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0);
	   p->entry_elem[3]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[3]),p->element_sel->seconary_axis_s);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[3]),50,20);
       g_signal_connect(G_OBJECT(p->entry_elem[3]),"value-changed" ,G_CALLBACK(seconary_axis_s),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_elem[3], p->selection);

       p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0);
	   p->entry_elem[4]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[4]),p->element_sel->seconary_axis_e);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[4]),50,20);
       g_signal_connect(G_OBJECT(p->entry_elem[4]),"value-changed" ,G_CALLBACK(seconary_axis_e),(gpointer) p );
       switch(p->selection)
       {
          case 0://1D
                gtk_widget_set_sensitive (p->entry_elem[4], FALSE);
                break;
          case 1://2D
                gtk_widget_set_sensitive (p->entry_elem[4], p->element_sel->linear);
                break;        
       }
       
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0);
	   p->entry_elem[5]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[5]),p->element_sel->seconary_axis_r);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[5]),50,20);
       g_signal_connect(G_OBJECT(p->entry_elem[5]),"value-changed" ,G_CALLBACK(seconary_axis_r),(gpointer) p );
       switch(p->selection)
       {
          case 0://1D
                gtk_widget_set_sensitive (p->entry_elem[5], FALSE);
                break;
          case 1://2D
                gtk_widget_set_sensitive (p->entry_elem[5], p->element_sel->linear);
                break;        
       }
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem1  ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[3],160,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[4],210,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[5],260,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new();
       p->label_elem1=gtk_label_new("Primary axis aperture  ");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0.0);
	   p->entry_elem[6]=gtk_spin_button_new (p->adj, 1, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[6]),p->element_sel->pri_axis_ape);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[6]),50,20);
       g_signal_connect(G_OBJECT(p->entry_elem[6]),"value-changed" ,G_CALLBACK(pri_axis_ape),(gpointer) p );
//       gtk_widget_set_sensitive (p->entry_elem[6], FALSE);
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem1  ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[6],160,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new();
       p->label_elem1=gtk_label_new("Secondary axis aperture");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0.0);
	   p->entry_elem[7]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[7]),p->element_sel->sec_axis_ape);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[7]),50,20);
       g_signal_connect(G_OBJECT(p->entry_elem[7]),"value-changed" ,G_CALLBACK(sec_axis_ape),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_elem[7], p->selection);//////
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem1  ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[7],160,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new();
       p->label_elem1=gtk_label_new("connection             ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0);
	   p->entry_elem[8]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[8]),p->element_sel->connection);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[8]),50,20);
       g_signal_connect(G_OBJECT(p->entry_elem[8]),"value-changed" ,G_CALLBACK(connection),(gpointer) p );
//       gtk_widget_set_sensitive (p->entry_elem[8], FALSE);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem1  ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[8],160,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   gtk_container_add(GTK_CONTAINER(p->frame_elem),p->vbox_wg);
	   /////////////
	   p->frame_elem=gtk_frame_new("Receiver");
	   gtk_widget_set_size_request(GTK_WIDGET(p->frame_elem),100,220);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_elem),FALSE,FALSE,5);
	   p->vbox_wg=gtk_vbox_new(FALSE,0);
	   
	   p->hbox_wg=gtk_fixed_new();
	   p->label_elem2=gtk_label_new("Start");
	   p->label_elem3=gtk_label_new("Stop");
	   p->label_elem4=gtk_label_new("Resolution");
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem2,160  ,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem3,210  ,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem4,260  ,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new(); 
       p->label_elem1=gtk_label_new("Primary axis");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0.0);
	   p->entry_elem[9]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[9]),p->element_sel->primary_axis_s);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[9]),50,20);
//       g_signal_connect(G_OBJECT(p->entry_elem[9]),"value-changed" ,G_CALLBACK(primary_axis_s),(gpointer) p );
//       gtk_widget_set_sensitive (p->entry_elem[9], FALSE);

       p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0.0);
	   p->entry_elem[10]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[10]),p->element_sel->primary_axis_e);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[10]),50,20);
//       g_signal_connect(G_OBJECT(p->entry_elem[10]),"value-changed" ,G_CALLBACK(primary_axis_e),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_elem[10], p->element_sel->linear);
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0.0);
	   p->entry_elem[11]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[11]),p->element_sel->primary_axis_r);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[11]),50,20);
//       g_signal_connect(G_OBJECT(p->entry_elem[11]),"value-changed" ,G_CALLBACK(primary_axis_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_elem[11], p->element_sel->linear);
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem1  ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[9],160,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[10],210,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[11],260,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new(); 
       p->label_elem1=gtk_label_new("Seconary axis          ");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0.0);
	   p->entry_elem[12]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[12]),p->element_sel->seconary_axis_s);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[12]),50,20);
//       g_signal_connect(G_OBJECT(p->entry_elem[12]),"value-changed" ,G_CALLBACK(primary_axis_s),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_elem[12], p->selection);

       p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0.0);
	   p->entry_elem[13]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[13]),p->element_sel->seconary_axis_e);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[13]),50,20);
//       g_signal_connect(G_OBJECT(p->entry_elem[13]),"value-changed" ,G_CALLBACK(primary_axis_e),(gpointer) p );
       switch(p->selection)
       {
          case 0://1D
                gtk_widget_set_sensitive (p->entry_elem[13], FALSE);
                break;
          case 1://2D
                gtk_widget_set_sensitive (p->entry_elem[13], p->element_sel->linear);
                break;        
       }
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0.0);
	   p->entry_elem[14]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[14]),p->element_sel->seconary_axis_r);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[14]),50,20);
//       g_signal_connect(G_OBJECT(p->entry_elem[14]),"value-changed" ,G_CALLBACK(primary_axis_r),(gpointer) p );
       switch(p->selection)
       {
          case 0://1D
                gtk_widget_set_sensitive (p->entry_elem[14], FALSE);
                break;
          case 1://2D
                gtk_widget_set_sensitive (p->entry_elem[14], p->element_sel->linear);
                break;        
       }
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem1  ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[12],160,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[13],210,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[14],260,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new(); 
       p->label_elem1=gtk_label_new("Primary axis aperture  ");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0.0);
	   p->entry_elem[15]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[15]),p->element_sel->pri_axis_ape);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[15]),50,20);
//       g_signal_connect(G_OBJECT(p->entry_elem[15]),"value-changed" ,G_CALLBACK(primary_axis_r),(gpointer) p );
//       gtk_widget_set_sensitive (p->entry_elem[15], FALSE);
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem1  ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[15],160,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new(); 
       p->label_elem1=gtk_label_new("Secondary axis aperture");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0.0);
	   p->entry_elem[16]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[16]),p->element_sel->sec_axis_ape);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[16]),50,20);
//       g_signal_connect(G_OBJECT(p->entry_elem[16]),"value-changed" ,G_CALLBACK(primary_axis_r),(gpointer) p );
       gtk_widget_set_sensitive (p->entry_elem[16], p->selection);
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem1  ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[16],160,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_fixed_new(); 
       p->label_elem1=gtk_label_new("connection");
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (0, 1, elements_num, 1, 1, 0.0);
	   p->entry_elem[17]=gtk_spin_button_new (p->adj, 1.0, 0); 
	   gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_elem[17]),p->element_sel->connection);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_elem[17]),50,20);
//       g_signal_connect(G_OBJECT(p->entry_elem[17]),"value-changed" ,G_CALLBACK(primary_axis_r),(gpointer) p );
//       gtk_widget_set_sensitive (p->entry_elem[17], FALSE);
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_elem1  ,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_elem[17],160,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   gtk_container_add(GTK_CONTAINER(p->frame_elem),p->vbox_wg);
	   gtk_widget_set_sensitive (p->frame_elem, p->probe_p->Pitch_Catch);
       
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
       gtk_widget_show_all(p->vbox_ldw);
   }
   else if(!strcmp(p->pos,"Paramenter"))
   {
       p->vbox_ldw=gtk_vbox_new(FALSE,0);
       /*第一个边框*/
       p->vbox_wg=gtk_vbox_new(FALSE,0);
       p->frame_pra1=gtk_frame_new("Sampling");
       p->frame_pra2=gtk_frame_new("Spatial");
       p->frame_pra3=gtk_frame_new("Time");
	   gtk_widget_set_size_request(GTK_WIDGET(p->frame_pra1),100,250);
	   gtk_widget_set_size_request(GTK_WIDGET(p->frame_pra2),100,120);
	   gtk_widget_set_size_request(GTK_WIDGET(p->frame_pra3),100,120);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->frame_pra2),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->frame_pra3),FALSE,FALSE,0);
       gtk_container_add(GTK_CONTAINER(p->frame_pra1),p->vbox_wg);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_pra1),FALSE,FALSE,5);
	   //
       p->vbox_wg=gtk_vbox_new(FALSE,0);
       p->hbox_wg=gtk_fixed_new(); 
       p->label_pra1=gtk_label_new("Primary");
       p->entry_pra=gtk_entry_new(); 
	   gtk_entry_set_text(GTK_ENTRY(p->entry_pra),"0.200");
	   gtk_widget_set_sensitive (p->entry_pra, FALSE);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_pra),40,20);
       p->label_pra2=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pra1,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_pra ,70 ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pra2,120,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);

       p->hbox_wg=gtk_fixed_new(); 
       p->label_pra1=gtk_label_new("Secondary");
       p->entry_pra=gtk_entry_new(); 
	   gtk_entry_set_text(GTK_ENTRY(p->entry_pra),"0.200");
	   gtk_widget_set_sensitive (p->entry_pra, FALSE);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_pra),40,20);
       p->label_pra2=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pra1,5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_pra ,70 ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pra2,120,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->btn_pra1=gtk_button_new_with_label("Decrease");
	   p->btn_pra2=gtk_button_new_with_label("Increase");
       gtk_widget_set_sensitive (p->btn_pra1, FALSE);
       gtk_widget_set_sensitive (p->btn_pra2, FALSE);
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->btn_pra1),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->btn_pra2),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   gtk_container_add(GTK_CONTAINER(p->frame_pra2),p->vbox_wg);
	   /////
	   p->vbox_wg=gtk_vbox_new(FALSE,0);
	   
	   p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->label_pra1=gtk_label_new("Frequency");
       p->entry_pra=gtk_entry_new(); 
	   gtk_entry_set_text(GTK_ENTRY(p->entry_pra),"40.00");
	   gtk_widget_set_sensitive (p->entry_pra, FALSE);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_pra),40,20);
       p->label_pra2=gtk_label_new("MHz");
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_pra1),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry_pra),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->btn_pra1=gtk_button_new_with_label("Decrease");
	   p->btn_pra2=gtk_button_new_with_label("Increase");
       gtk_widget_set_sensitive (p->btn_pra1, FALSE);
       gtk_widget_set_sensitive (p->btn_pra2, FALSE);
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->btn_pra1),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->btn_pra2),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   gtk_container_add(GTK_CONTAINER(p->frame_pra3),p->vbox_wg);
	   ////
	   p->btn_pra1=gtk_button_new_with_label("Reset samping");
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->btn_pra1),FALSE,FALSE,5);
	   gtk_widget_set_sensitive (p->btn_pra1, FALSE);
	   
	   /*第二个边框*/
	   p->frame_pra2=gtk_frame_new("Beam map(s)");
       gtk_widget_set_size_request(GTK_WIDGET(p->frame_pra2),100,150);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_pra2),FALSE,FALSE,5);
       
       p->vbox_wg=gtk_vbox_new(FALSE,0);
	   p->check_btn_pra1=gtk_check_button_new_with_label("L in specimen");
	   p->check_btn_pra2=gtk_check_button_new_with_label("T in specimen");
	   p->check_btn_pra3=gtk_check_button_new_with_label("Transmit-receiver Beam");
	   p->check_btn_pra4=gtk_check_button_new_with_label("Transmit Beam &receiver Beam");
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->check_btn_pra1),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->check_btn_pra2),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->check_btn_pra3),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->check_btn_pra4),FALSE,FALSE,5);
	   gtk_container_add(GTK_CONTAINER(p->frame_pra2),p->vbox_wg);
	   gtk_widget_set_sensitive (p->check_btn_pra1, FALSE);
	   gtk_widget_set_sensitive (p->check_btn_pra2, FALSE);
	   gtk_widget_set_sensitive (p->check_btn_pra3, FALSE);
	   gtk_widget_set_sensitive (p->check_btn_pra4, FALSE);
      
	   /*第三个边框*/
       p->frame_pra3=gtk_frame_new("Bandwidth");
       gtk_widget_set_size_request(GTK_WIDGET(p->frame_pra3),100,50);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_pra3),FALSE,FALSE,5);
       
       p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->entry_pra=gtk_entry_new(); 
       p->entry_pra1=gtk_entry_new(); 
	   gtk_entry_set_text(GTK_ENTRY(p->entry_pra),"2.8");
	   gtk_entry_set_text(GTK_ENTRY(p->entry_pra1),"70.2");
	   gtk_widget_set_sensitive (p->entry_pra, FALSE);
	   gtk_widget_set_sensitive (p->entry_pra1, FALSE);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_pra),40,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_pra1),40,20);
       p->label_pra1=gtk_label_new("MHz     ");
       p->label_pra2=gtk_label_new("%");
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry_pra),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_pra1),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry_pra1),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_pra2),FALSE,FALSE,5);
	   gtk_container_add(GTK_CONTAINER(p->frame_pra3),p->hbox_wg);
       
       
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
       gtk_widget_show_all(p->vbox_ldw);
   }
   else if(!strcmp(p->pos,"Exent"))
   {
       p->vbox_ldw=gtk_vbox_new(FALSE,0);
       
       p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->label_extent1=gtk_label_new("Start");
       p->label_extent2=gtk_label_new("End");
       p->label_extent3=gtk_label_new("Step");
       p->label_extent4=gtk_label_new("Quanity");
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_extent1),FALSE,FALSE,20);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_extent2),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_extent3),FALSE,FALSE,40);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_extent4),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
       p->label_extent1=gtk_label_new("X");
       p->entry_extent1=gtk_entry_new(); 
       p->entry_extent2=gtk_entry_new();
       p->entry_extent3=gtk_entry_new();
       p->entry_extent4=gtk_entry_new();
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent1),"0.00");
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent2),"0.00");
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent3),"1.00");
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent4),"1");
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent1),40,20);
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent2),40,20);
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent3),40,20);
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent4),40,20);
       p->label_extent2=gtk_label_new("mm    ");
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_extent1,5,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent1,20,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent2,70,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent3,120,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_extent2,170,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent4,200,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
       p->label_extent1=gtk_label_new("Y");
       p->entry_extent1=gtk_entry_new(); 
       p->entry_extent2=gtk_entry_new();
       p->entry_extent3=gtk_entry_new();
       p->entry_extent4=gtk_entry_new();
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent1),"0.00");
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent2),"0.00");
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent3),"1.00");
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent4),"1");
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent1),40,20);
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent2),40,20);
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent3),40,20);
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent4),40,20);
       p->label_extent2=gtk_label_new("mm    ");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_extent1,5,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent1,20,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent2,70,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent3,120,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_extent2,170,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent4,200,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->hbox_wg=gtk_fixed_new();
       p->label_extent1=gtk_label_new("Z");
       p->entry_extent1=gtk_entry_new(); 
       p->entry_extent2=gtk_entry_new();
       p->entry_extent3=gtk_entry_new();
       p->entry_extent4=gtk_entry_new();
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent1),"1.00");
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent2),"1.00");
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent3),"1.00");
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent4),"1");
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent1),40,20);
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent2),40,20);
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent3),40,20);
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent4),40,20);
       p->label_extent2=gtk_label_new("mm    ");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_extent1,5,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent1,20,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent2,70,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent3,120,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_extent2,170,0);
	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_extent4,200,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   //
	   p->chk_btn_extent=gtk_check_button_new_with_label("Set cusors to limits");
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->chk_btn_extent),FALSE,FALSE,5);
	   /////
	   p->frame_extent1=gtk_frame_new("Set limits");
	   gtk_widget_set_size_request(GTK_WIDGET(p->frame_extent1),100,150);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_extent1),FALSE,FALSE,5);
	   p->vbox_wg=gtk_vbox_new(FALSE,0);
	   gtk_container_add(GTK_CONTAINER(p->frame_extent1),p->vbox_wg);
	   
	   p->hbox_wg=gtk_hbox_new(FALSE,0);
	   p->radio_btn_extent1=gtk_radio_button_new_with_label(NULL,"Scale ranges by:");
	   p->entry_extent1=gtk_entry_new();
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent1),"2.0");
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent1),40,20);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->radio_btn_extent1),FALSE,FALSE,0);  
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry_extent1),FALSE,FALSE,5);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
	   p->radio_btn_extent2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(p->radio_btn_extent1))
                            ,"Extent non_zero ranges b");
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->radio_btn_extent2),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_hbox_new(FALSE,0);                     
       p->radio_btn_extent3=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(p->radio_btn_extent2))
                            ,"Extent all ranges b");
       p->entry_extent2=gtk_entry_new();
	   gtk_entry_set_text(GTK_ENTRY(p->entry_extent2),"10.00");
	   gtk_widget_set_size_request(GTK_WIDGET(p->entry_extent2),40,20); 
       p->label_extent1=gtk_label_new("mm"); 
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->radio_btn_extent3),FALSE,FALSE,0);  
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->entry_extent2),FALSE,FALSE,5);
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_extent1),FALSE,FALSE,5);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //                    
       p->radio_btn_extent4=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(p->radio_btn_extent3))
                            ,"get limits from cur");
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->radio_btn_extent4),FALSE,FALSE,0);              
       p->btn_extent=gtk_button_new_with_label("Set limits");
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->btn_extent),FALSE,FALSE,0);
       ////////
       p->frame_extent1=gtk_frame_new("Simulate");
	   gtk_widget_set_size_request(GTK_WIDGET(p->frame_extent1),100,100);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_extent1),FALSE,FALSE,5);
	   p->vbox_wg=gtk_vbox_new(FALSE,0);
	   gtk_container_add(GTK_CONTAINER(p->frame_extent1),p->vbox_wg); 
       p->radio_btn_extent1=gtk_radio_button_new_with_label(NULL,"All focal laws");
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->radio_btn_extent1),FALSE,FALSE,0); 
        
       p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->radio_btn_extent2=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(p->radio_btn_extent1))
                            ,"Current focal l");
	   p->combox_extent= gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_extent), "Azimuthal  R :40.00");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_extent), "Linear");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_extent), "Depth");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_extent), "Static");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->combox_extent), 0);
       
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->radio_btn_extent2),FALSE,FALSE,0);
       gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->combox_extent),FALSE,FALSE,5);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       p->btn_extent=gtk_button_new_with_label("Calculate"); 
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->btn_extent),FALSE,FALSE,5);
       gtk_widget_set_sensitive (p->frame_extent1, FALSE);
         
       p->label_extent1=gtk_label_new("Calculate button disabled because:\nNo focal present");
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->label_extent1),FALSE,FALSE,0);  
                            
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
       gtk_widget_show_all(p->vbox_ldw);
   }
   else if(!strcmp(p->pos,"Definition"))  
   {
       p->vbox_ldw=gtk_vbox_new(FALSE,0);
       
       p->hbox_wg=gtk_fixed_new();
       p->label_def[0]=gtk_label_new("Name:");
       p->entry_def[0]=gtk_entry_new();
       gtk_entry_set_text(GTK_ENTRY(p->entry_def[0]),p->specimen->name);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_def[0],5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_def[0],60,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_def[1]=gtk_label_new("Material");
       p->entry_def[1]=gtk_entry_new();
       gtk_entry_set_text(GTK_ENTRY(p->entry_def[1]),p->specimen->material);
       GtkWidget *btn = gtk_button_new_with_label("...");
       update_widget_bg(btn, "./image/bg.jpg");
       g_signal_connect(G_OBJECT( btn),"clicked" ,G_CALLBACK(import_material),(gpointer) p );
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_def[1],5  ,5);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_def[1],60,2);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),btn,220,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_def[2]=gtk_label_new("Longitudinal Wave");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000, 1, 1, 0.0);
       p->entry_def[2]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_def[2]),p->specimen->speci_longitudinal_wave);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_def[2]),70,20);
       g_signal_connect(G_OBJECT( p->entry_def[2]),"value-changed" ,G_CALLBACK(speci_longitudinal_wave),(gpointer) p );
       p->label_def[4]=gtk_label_new("m/s");
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_def[2],5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_def[2],120,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_def[4],200,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_fixed_new();
       p->label_def[3]=gtk_label_new("Transverse Wave");
       p->label_def[5]=gtk_label_new("m/s");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1, 0, 10000, 1, 1, 0.0);
       p->entry_def[3]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_def[3]),p->specimen->speci_transverse_wave);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_def[3]),70,20);
       g_signal_connect(G_OBJECT( p->entry_def[3]),"value-changed" ,G_CALLBACK(speci_transverse_wave),(gpointer) p );
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_def[3],5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_def[3],120,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_def[5],200,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
       //
       p->hbox_wg=gtk_hbox_new(FALSE,0);
       p->label_def[6]=gtk_label_new("Shap:");
       p->combox_def= gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_def), "Flat");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combox_def), "Cylindrical");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->combox_def), p->specimen->flat_cylindrical);
       g_signal_connect(G_OBJECT(p->combox_def),"changed" ,G_CALLBACK(speci_setting_def),(gpointer) p );///////////////////////
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->label_def[6]),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->hbox_wg),GTK_WIDGET(p->combox_def),FALSE,FALSE,5);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
	   
	   /*flat*/
       p->hbox_wg_f[0]=gtk_fixed_new();
       p->label_def[7]=gtk_label_new("Length ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (p->specimen->speci_length_flat, 0, 10000, 1, 1, 0.0);
       p->entry_def[4]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_def[4]),70,20);
       p->label_def[10]=gtk_label_new("mm");
       g_signal_connect(G_OBJECT( p->entry_def[4]),"value-changed" ,G_CALLBACK(speci_length),(gpointer) p );
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_f[0]),p->label_def[7],5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_f[0]),p->entry_def[4],60,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_f[0]),p->label_def[10],130,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg_f[0]),FALSE,FALSE,5);
       //
       p->hbox_wg_f[1]=gtk_fixed_new();
       p->label_def[8]=gtk_label_new("Height ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (p->specimen->speci_height_flat, 0, 10000, 1, 1, 0.0);
       p->entry_def[5]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_def[5]),70,20);
       p->label_def[10]=gtk_label_new("mm");
       g_signal_connect(G_OBJECT( p->entry_def[5]),"value-changed" ,G_CALLBACK(speci_height),(gpointer) p );
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_f[1]),p->label_def[8],5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_f[1]),p->entry_def[5],60,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_f[1]),p->label_def[10],130,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg_f[1]),FALSE,FALSE,5);
      //
       p->hbox_wg_f[2]=gtk_fixed_new();
       p->label_def[9]=gtk_label_new("Width  ");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (p->specimen->speci_width_flat, 0, 10000, 1, 1, 0.0);
       p->entry_def[6]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_def[6]),70,20);
       p->label_def[10]=gtk_label_new("mm");
       g_signal_connect(G_OBJECT( p->entry_def[6]),"value-changed" ,G_CALLBACK(speci_width),(gpointer) p );
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_f[2]),p->label_def[9],5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_f[2]),p->entry_def[6],60,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_f[2]),p->label_def[10],130,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg_f[2]),FALSE,FALSE,5);
	   
	   /*Cylindrical*/
       p->hbox_wg_c[0]=gtk_fixed_new();
       p->label_def[11]=gtk_label_new("Inside");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (p->specimen->speci_inside_cylindrical, 0, 10000, 1, 1, 0.0);
       p->entry_def[7]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_def[7]),70,20);
       p->label_def[10]=gtk_label_new("mm");
       g_signal_connect(G_OBJECT( p->entry_def[7]),"value-changed" ,G_CALLBACK(speci_length),(gpointer) p );
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_c[0]),p->label_def[11],5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_c[0]),p->entry_def[7],60,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_c[0]),p->label_def[10],130,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg_c[0]),FALSE,FALSE,5);
       //
       p->hbox_wg_c[1]=gtk_fixed_new();
       p->label_def[12]=gtk_label_new("Outside");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (p->specimen->speci_outside_cylindrical, 0, 10000, 1, 1, 0.0);
       p->entry_def[8]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_def[8]),70,20);
       p->label_def[10]=gtk_label_new("mm");
       g_signal_connect(G_OBJECT( p->entry_def[8]),"value-changed" ,G_CALLBACK(speci_height),(gpointer) p );
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_c[1]),p->label_def[12],5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_c[1]),p->entry_def[8],60,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_c[1]),p->label_def[10],130,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg_c[1]),FALSE,FALSE,5);
      //
       p->hbox_wg_c[2]=gtk_fixed_new();
       p->label_def[13]=gtk_label_new("Width");
       p->adj = (GtkAdjustment *) gtk_adjustment_new (p->specimen->speci_length_cylindrical, 0, 10000, 1, 1, 0.0);
       p->entry_def[9]= gtk_spin_button_new (p->adj, 1.0, 0);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_def[9]),70,20);
       p->label_def[10]=gtk_label_new("mm");
       g_signal_connect(G_OBJECT( p->entry_def[9]),"value-changed" ,G_CALLBACK(speci_width),(gpointer) p );
       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_c[2]),p->label_def[13],5  ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_c[2]),p->entry_def[9],60,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg_c[2]),p->label_def[10],130,0);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->hbox_wg_c[2]),FALSE,FALSE,5);	  

       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
       gtk_widget_show_all(p->vbox_ldw); 
       
       if(!strcmp(gtk_combo_box_get_active_text(GTK_COMBO_BOX(p->combox_def)),"Flat" ) ) /*如果选中 Flat */
       {
          // g_printf("Flat\n");
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_f[0]));
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_f[1]));
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_f[2]));
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_c[0]));
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_c[1]));
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_c[2]));
          
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[4]),p->specimen->speci_length_flat); 
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[5]),p->specimen->speci_height_flat);
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[6]),p->specimen->speci_width_flat);                                                            
       }
      else                                                               /*如果选中 Cylindrical */
       {
//           g_printf("Cylindrical\n");
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_f[0]));
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_f[1]));
           gtk_widget_hide(GTK_WIDGET(p->hbox_wg_f[2]));
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_c[0]));
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_c[1]));
           gtk_widget_show(GTK_WIDGET(p->hbox_wg_c[2]));
           
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[7]),p->specimen->speci_inside_cylindrical); 
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[8]),p->specimen->speci_outside_cylindrical);
           gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_def[9]),p->specimen->speci_length_cylindrical);                 
       }
   }
   else if(!strcmp(p->pos,"Location"))
   {
       p->vbox_ldw=gtk_vbox_new(FALSE,0);
       
       p->frame_loca[0]=gtk_frame_new("Rotation Center");
       gtk_widget_set_size_request(GTK_WIDGET(p->frame_loca[0]),100,100);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_loca[0]),FALSE,FALSE,5);
	   p->frame_loca[1]=gtk_frame_new("Rotation");
       gtk_widget_set_size_request(GTK_WIDGET(p->frame_loca[1]),100,100);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_loca[1]),FALSE,FALSE,5);
	   p->frame_loca[2]=gtk_frame_new("Translation");
       gtk_widget_set_size_request(GTK_WIDGET(p->frame_loca[2]),100,100);
	   gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->frame_loca[2]),FALSE,FALSE,5);
	   ////
	   p->vbox_wg=gtk_vbox_new(FALSE,0);
       gtk_container_add(GTK_CONTAINER(p->frame_loca[0]),p->vbox_wg);

	   p->hbox_wg=gtk_fixed_new();
	   p->label_loca[0]=gtk_label_new("X axis:");
       
       p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0, 700, 0.1, 1.0, 0.0);
       p->entry_loca[0]= gtk_spin_button_new (p->adj, 1.0, 2.0);
       gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_loca[0]),p->location->center_x);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_loca[0]),100,20);
       gtk_widget_set_sensitive (p->entry_loca[0], FALSE);
       g_signal_connect(G_OBJECT( p->entry_loca[0]),"value-changed" ,G_CALLBACK(axis0),(gpointer) p );
       
       p->label_loca[1]=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[0],5 ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_loca[0],60,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[1],130,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg), GTK_WIDGET(p->hbox_wg),FALSE,FALSE,0);
	   
	   p->hbox_wg=gtk_fixed_new();
	   p->label_loca[0]=gtk_label_new("Y axis:");
	   
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0, 700, 0.1, 1.0, 0.0);
       p->entry_loca[1]= gtk_spin_button_new (p->adj, 1.0, 2.0);
       gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_loca[1]),p->location->center_y);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_loca[1]),100,20);
       gtk_widget_set_sensitive (p->entry_loca[1], FALSE);
       g_signal_connect(G_OBJECT( p->entry_loca[1]),"value-changed" ,G_CALLBACK(axis1),(gpointer) p );
       
       p->label_loca[1]=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[0],5 ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_loca[1],60,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[1],130,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg), GTK_WIDGET(p->hbox_wg),FALSE,FALSE,0);
	   
	   p->hbox_wg=gtk_fixed_new();
	   p->label_loca[0]=gtk_label_new("Z axis:");
	   
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0, 700, 0.1, 1.0, 0.0);
       p->entry_loca[2]= gtk_spin_button_new (p->adj, 1.0, 2.0);
       gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_loca[2]),p->location->center_z);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_loca[2]),100,20);
       gtk_widget_set_sensitive (p->entry_loca[2], FALSE);
       g_signal_connect(G_OBJECT( p->entry_loca[2]),"value-changed" ,G_CALLBACK(axis2),(gpointer) p );
       
       p->label_loca[1]=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[0],5 ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_loca[2],60,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[1],130,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg), GTK_WIDGET(p->hbox_wg),FALSE,FALSE,0);
       ////
       p->vbox_wg=gtk_vbox_new(FALSE,0);
       gtk_container_add(GTK_CONTAINER(p->frame_loca[1]),p->vbox_wg);
       
       p->hbox_wg=gtk_fixed_new();
	   p->label_loca[0]=gtk_label_new("1st:");
	   
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0, 360, 0.1, 1.0, 0.0);
       p->entry_loca[3]= gtk_spin_button_new (p->adj, 1.0, 2.0);
       gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_loca[3]),p->location->rotation_x);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_loca[3]),100,20);
       g_signal_connect(G_OBJECT( p->entry_loca[3]),"value-changed" ,G_CALLBACK(axis3),(gpointer) p );
       
	   p->combo_loca[0]= gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_loca[0]), "X axis:");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_loca[0]), "Y axis:");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_loca[0]), "Z axis:");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo_loca[0]), p->location->st1);
       g_signal_connect(G_OBJECT(p->combo_loca[0]),"changed" ,G_CALLBACK(rotation1),(gpointer) p );
       
       gtk_widget_set_size_request(GTK_WIDGET(p->combo_loca[0]),100,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_loca[3]),50,20);
       gtk_widget_set_sensitive (p->combo_loca[0], FALSE);
       gtk_widget_set_sensitive (p->entry_loca[3], FALSE);
       p->label_loca[1]=gtk_label_new("deg");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[0],5 ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->combo_loca[0],50,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_loca[3],150,0);       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[1],200,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,0);
       
       p->hbox_wg=gtk_fixed_new();
	   p->label_loca[0]=gtk_label_new("2st:");
	   
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0, 360, 0.1, 1.0, 0.0);
       p->entry_loca[4]= gtk_spin_button_new (p->adj, 1.0, 2.0);
       gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_loca[4]),p->location->rotation_y);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_loca[4]),100,20);
       g_signal_connect(G_OBJECT( p->entry_loca[4]),"value-changed" ,G_CALLBACK(axis4),(gpointer) p );
       
	   p->combo_loca[1]= gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_loca[1]), "X axis:");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_loca[1]), "Y axis:");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_loca[1]), "Z axis:");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo_loca[1]), p->location->st2);
       g_signal_connect(G_OBJECT(p->combo_loca[1]),"changed" ,G_CALLBACK(rotation2),(gpointer) p );
       
       gtk_widget_set_size_request(GTK_WIDGET(p->combo_loca[1]),100,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_loca[4]),50,20);
       gtk_widget_set_sensitive (p->combo_loca[1], FALSE);
       gtk_widget_set_sensitive (p->entry_loca[4], FALSE);
       p->label_loca[1]=gtk_label_new("deg");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[0],5 ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->combo_loca[1],50,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_loca[4],150,0);       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[1],200,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,0);
       
       p->hbox_wg=gtk_fixed_new();
	   p->label_loca[0]=gtk_label_new("3st:");
	   
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0, 360, 0.1, 1.0, 0.0);
       p->entry_loca[5]= gtk_spin_button_new (p->adj, 1.0, 2.0);
       gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_loca[5]),p->location->rotation_z);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_loca[5]),100,20);
       g_signal_connect(G_OBJECT( p->entry_loca[5]),"value-changed" ,G_CALLBACK(axis5),(gpointer) p );
       
       p->combo_loca[2]= gtk_combo_box_entry_new_text();
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_loca[2]), "X axis:");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_loca[2]), "Y axis:");
       gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_loca[2]), "Z axis:");
       gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo_loca[2]), p->location->st3);
       g_signal_connect(G_OBJECT(p->combo_loca[2]),"changed" ,G_CALLBACK(rotation3),(gpointer) p );
       
       gtk_widget_set_size_request(GTK_WIDGET(p->combo_loca[2]),100,20);
       gtk_widget_set_size_request(GTK_WIDGET(p->entry_loca[5]),50,20);
       //gtk_widget_set_sensitive (p->combo_loca[2], FALSE);
       //gtk_widget_set_sensitive (p->entry_loca[5], FALSE);
       p->label_loca[1]=gtk_label_new("deg");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[0],5 ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->combo_loca[2],50,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_loca[5],150,0);       
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[1],200,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,0);
       
       ////
       p->vbox_wg=gtk_vbox_new(FALSE,0);
       gtk_container_add(GTK_CONTAINER(p->frame_loca[2]),p->vbox_wg);
       
       p->hbox_wg=gtk_fixed_new();
	   p->label_loca[0]=gtk_label_new("X axis:");
	   
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0, 700, 0.1, 1.0, 0.0);
       p->entry_loca[6]= gtk_spin_button_new (p->adj, 1.0, 2.0);
       gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_loca[6]),p->location->translation_x);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_loca[6]),100,20);
       gtk_widget_set_sensitive (p->entry_loca[6], FALSE);
       g_signal_connect(G_OBJECT( p->entry_loca[6]),"value-changed" ,G_CALLBACK(axis6),(gpointer) p );
       
       p->label_loca[1]=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[0],5 ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_loca[6],50,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[1],100,0);       
       gtk_box_pack_start(GTK_BOX(p->vbox_wg), GTK_WIDGET(p->hbox_wg),FALSE,FALSE,0);
	   
	   p->hbox_wg=gtk_fixed_new();
	   p->label_loca[0]=gtk_label_new("Y axis:");
	   
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0, 700, 0.1, 1.0, 0.0);
       p->entry_loca[7]= gtk_spin_button_new (p->adj, 1.0, 2.0);
       gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_loca[7]),p->location->translation_y);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_loca[7]),100,20);
       gtk_widget_set_sensitive (p->entry_loca[7], FALSE);
       g_signal_connect(G_OBJECT( p->entry_loca[7]),"value-changed" ,G_CALLBACK(axis7),(gpointer) p );
       
       p->label_loca[1]=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[0],5 ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_loca[7],50,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[1],100,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg), GTK_WIDGET(p->hbox_wg),FALSE,FALSE,0);
	   
	   p->hbox_wg=gtk_fixed_new();
	   p->label_loca[0]=gtk_label_new("Z axis:");
	   
	   p->adj = (GtkAdjustment *) gtk_adjustment_new (1.0, 0, 700, 0.1, 1.0, 0.0);
       p->entry_loca[8]= gtk_spin_button_new (p->adj, 1.0, 2.0);
       gtk_spin_button_set_value( GTK_SPIN_BUTTON(p->entry_loca[8]),p->location->translation_x);
       gtk_widget_set_size_request(GTK_WIDGET( p->entry_loca[8]),100,20);
       gtk_widget_set_sensitive (p->entry_loca[8], FALSE);
       g_signal_connect(G_OBJECT( p->entry_loca[8]),"value-changed" ,G_CALLBACK(axis8),(gpointer) p );
       
       p->label_loca[1]=gtk_label_new("mm");
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[0],5 ,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_loca[8],50,0);
       gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_loca[1],100,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_wg), GTK_WIDGET(p->hbox_wg),FALSE,FALSE,0);
       
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
       gtk_widget_show_all(p->vbox_ldw); 
   }
   else if(!strcmp(p->pos,"Projected Sequence"))
   {
       p->vbox_ldw=gtk_vbox_new(FALSE,0);
       p->vbox_wg=gtk_vbox_new(FALSE,0);
       gtk_box_pack_start(GTK_BOX(p->vbox_ldw),GTK_WIDGET(p->vbox_wg),FALSE,FALSE,0);
       
       if(p->specimen->flat_cylindrical==0 ) /*如果选中 Flat */
       {
           p->hbox_wg=gtk_fixed_new();
           p->label_pro[0]=gtk_label_new("Shape:    ");
    	   p->combo_pro[0]= gtk_combo_box_entry_new_text();
           gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_pro[0]), "Flat");
           gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_pro[0]), "Cylindrical");
           gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo_pro[0]), 0);
           gtk_widget_set_size_request(GTK_WIDGET(p->combo_pro[0]),150,20);
           gtk_widget_set_sensitive (p->combo_pro[0], FALSE);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[0],5 ,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->combo_pro[0],70,0);
           gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
           //
           p->hbox_wg=gtk_fixed_new();
           p->label_pro[0]=gtk_label_new("Thickness:");
           p->entry_pro=gtk_entry_new();           
           gtk_entry_set_text(GTK_ENTRY(p->entry_pro),"50");
           p->label_pro[1]=gtk_label_new("mm");
           gtk_widget_set_sensitive (p->entry_pro, FALSE);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[0],5 ,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_pro,70,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[1],250,0);
           gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);                                                           
       }
     else                                                               /*如果选中 Cylindrical */
       {
           gchar tmp[20];
           p->hbox_wg=gtk_fixed_new();
           p->label_pro[0]=gtk_label_new("Shape:");
    	   p->combo_pro[1]= gtk_combo_box_entry_new_text();
           gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_pro[1]), "Flat");
           gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_pro[1]), "Cylindrical");
           gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo_pro[1]), 1);
           gtk_widget_set_size_request(GTK_WIDGET(p->combo_pro[1]),150,20);
           gtk_widget_set_sensitive (p->combo_pro[1], FALSE);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[0],5 ,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->combo_pro[1],120,0);
           gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
           //
           p->hbox_wg=gtk_fixed_new();
           p->label_pro[0]=gtk_label_new("Thickness:");
           p->entry_pro=gtk_entry_new();
           sprintf(tmp,"%.0lf",(p->specimen->speci_outside_cylindrical-p->specimen->speci_inside_cylindrical)/2 );           
           gtk_entry_set_text(GTK_ENTRY(p->entry_pro),tmp);
           p->label_pro[1]=gtk_label_new("mm");
           gtk_widget_set_sensitive (p->entry_pro, FALSE);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[0],5 ,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_pro,120,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[1],300,0);
           gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
           //
           p->hbox_wg=gtk_fixed_new();
           p->label_pro[0]=gtk_label_new("Outside diameter:");
           p->entry_pro=gtk_entry_new();           
           sprintf(tmp,"%.0lf",p->specimen->speci_outside_cylindrical);
           gtk_entry_set_text(GTK_ENTRY(p->entry_pro),tmp);
           p->label_pro[1]=gtk_label_new("mm");
           gtk_widget_set_sensitive (p->entry_pro, FALSE);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[0],5 ,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_pro,120,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[1],300,0);
           gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5); 
           //
           p->hbox_wg=gtk_fixed_new();
           p->label_pro[0]=gtk_label_new("Inside diameter:");
           p->entry_pro=gtk_entry_new();
           sprintf(tmp,"%.0lf",p->specimen->speci_inside_cylindrical);
           gtk_entry_set_text(GTK_ENTRY(p->entry_pro),tmp);
           p->label_pro[1]=gtk_label_new("mm");
           gtk_widget_set_sensitive (p->entry_pro, FALSE);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[0],5 ,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->entry_pro,120,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[1],300,0);
           gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
           //
           p->hbox_wg=gtk_fixed_new();
           p->label_pro[0]=gtk_label_new("Inspection from:");
           p->radio_pro[0]=gtk_radio_button_new_with_label(NULL,"OD");
    	   gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[0],5 ,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->radio_pro[0],120,0);
           gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);          
           g_signal_connect(G_OBJECT(p->radio_pro[0]),"clicked" ,G_CALLBACK(Inspection_od_id),(gpointer) p );/////////
           
           p->hbox_wg=gtk_fixed_new();
           p->label_pro[0]=gtk_label_new("");
	       p->radio_pro[1]=gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(p->radio_pro[0])),"ID");                    
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[0],5 ,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->radio_pro[1],120,0);
           gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
           g_signal_connect(G_OBJECT(p->radio_pro[1]),"clicked" ,G_CALLBACK(Inspection_od_id),(gpointer) p );/////////
           
           if(!strcmp(p->specimen->Inspection_od_id,"OD"))
           {
              gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->radio_pro[0]),TRUE);
              gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->radio_pro[1]),FALSE);  
           }  
           else if(!strcmp(p->specimen->Inspection_od_id,"ID")) 
           {
              gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->radio_pro[0]),FALSE);
              gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(p->radio_pro[1]),TRUE);     
           }
           //
           p->hbox_wg=gtk_fixed_new();
           p->label_pro[0]=gtk_label_new("Scan axis oritation");
    	   p->combo_pro[2]= gtk_combo_box_entry_new_text();
           gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_pro[2]), "Circumferential");
           gtk_combo_box_append_text(GTK_COMBO_BOX(p->combo_pro[2]), "Axial");
           gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo_pro[2]), p->project->circum_axial);
           gtk_widget_set_size_request(GTK_WIDGET(p->combo_pro[2]),150,20);
           g_signal_connect(G_OBJECT(p->combo_pro[2]),"changed" ,G_CALLBACK(circum_axial),(gpointer) p );
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->label_pro[0],5 ,0);
           gtk_fixed_put(GTK_FIXED(p->hbox_wg),p->combo_pro[2],120,0);
           gtk_box_pack_start(GTK_BOX(p->vbox_wg),GTK_WIDGET(p->hbox_wg),FALSE,FALSE,5);
           
       }
       
       gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
       gtk_widget_show_all(p->vbox_ldw);  
   }
}
