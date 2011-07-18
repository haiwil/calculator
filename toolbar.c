/************************************************* 
            快捷菜单工具栏回调函数 
 *************************************************/


#include "drawui.h"

#define DEBUG 0
#define PI G_PI



void save_beam_setup(GtkWidget *widget,gpointer data);
void save_as_beam_setup(GtkWidget *widget,gpointer data);
void save_beam_data(gpointer data,FILE *fp);

void load_beam_setup(GtkWidget *widget,gpointer data);
void read_beam_data(gpointer data,FILE *fp);

void save_law(GtkWidget *widget,gpointer data);
void save_as_law(GtkWidget *widget,gpointer data);
void save_law_data(gpointer data,FILE *fp);



//********************************************************
//         保存beam配置文件  
//********************************************************
void save_beam_setup(GtkWidget *widget,gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   FILE *fp;
   
   if((fp = fopen("./beamdata1.BeamData","wb+"))==NULL)
   {
      g_printf("cannot open this file\n");  
      return ;
   }
   else
   {
#if DEBUG        
        g_printf("Save As Beam Data Setup\n");
#endif                          
        save_beam_data((gpointer)p ,fp);         
   }
   fclose(fp); 
}
//
void save_as_beam_setup(GtkWidget *widget,gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    GtkFileFilter* filter;
    FILE *fp;
    gint i,j,count;
    
    count = 0;
    p->filechooser = gtk_file_chooser_dialog_new ("Save Beam Data",
				      GTK_WINDOW (p->window),
				      GTK_FILE_CHOOSER_ACTION_SAVE,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
				      NULL);
    
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (p->filechooser), TRUE);
    //*****************文件选择类型过滤************************
    //后缀为*.BeamData的文件
    filter = gtk_file_filter_new();
    gtk_file_filter_set_name (filter, "Beam Data Files(*.BeamData)");
    gtk_file_filter_add_pattern(filter,"*.BeamData");
    gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (p->filechooser),filter);
    /*所有文件*/
    filter = gtk_file_filter_new();
    gtk_file_filter_set_name (filter, "*.All");
    gtk_file_filter_add_pattern(filter,"*");
    gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (p->filechooser),filter);
  
    gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (p->filechooser), "beamdata1.BeamData");

    if (gtk_dialog_run (GTK_DIALOG (p->filechooser)) == GTK_RESPONSE_ACCEPT)//捕捉保存按钮信号 
      {
        gchar *filename ;//= g_malloc0(sizeof(gchar))
        filename = g_locale_from_utf8( gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p->filechooser)),-1,NULL,NULL,NULL );
#if DEBUG        
        g_printf("%s\n",filename);
#endif
        //检查filename中有没有.BeamData字符串            
        for(i = 0;i < strlen(filename);i++)
        {
            if( filename[i] == '.')
            {                
                count ++;    
            }
        } 
        //没有.BeamData的时候 加上，没有的时候 不加        
        if(!count)
            strcat(filename,".BeamData");
            
       if((fp = fopen(filename,"wb+"))==NULL)
        {
          g_printf("cannot open this file\n");  
          return ;
        }
        else
        {                        
           save_beam_data((gpointer)p ,fp); 
        }        
        fclose (fp);
        g_free (filename);
      }
    gtk_widget_destroy (p->filechooser);
}
//
void save_beam_data(gpointer data,FILE *fp)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    //保存配置信息 
    
    //Probe---------transmitter
    fprintf(fp,"%d %d %d\015\012  %d %lf %lf\015\012  %d %d %lf\015\012  %lf %lf %lf\015\012", 
            p->probe_p->D1_D2, p->probe_p->Pitch_Catch, p->probe_p->transmi_trans_longi,
            p->probe_p->recev_trans_longi, p->probe_p->pb_skew_angle, p->probe_p->pb_frequency,
            p->probe_p->ele_num_pri, p->probe_p->ele_num_sec, p->probe_p->pri_axis_pitch,
            p->probe_p->sec_axis_pitch, p->probe_p->pri_ele_size, p->probe_p->sec_ele_size);
   //Probe---------receiver
   fprintf(fp," %lf %lf %d\015\012  %d %lf %lf\015\012  %lf %lf\015\012", 
            p->probe_p->pb_skew_angle_r, p->probe_p->pb_frequency_r, p->probe_p->ele_num_pri_r,
            p->probe_p->ele_num_sec_r, p->probe_p->pri_axis_pitch_r, p->probe_p->sec_axis_pitch_r,
            p->probe_p->pri_ele_size_r, p->probe_p->sec_ele_size_r );
            
   //Wedge---------transmitter
   fprintf(fp," %lf %lf %lf\015\012  %lf %d %lf\015\012  %lf %lf %lf\015\012  %lf %lf %lf\015\012  %lf %lf\015\012", 
            p->wedge_p->wg_wedge_angle, p->wedge_p->wg_roof_angle, p->wedge_p->wg_lon_vel,
            p->wedge_p->wg_trans_vel, p->wedge_p->wg_density, p->wedge_p->wg_heigh_fir,
            p->wedge_p->wg_pri_elem_offset_fir, p->wedge_p->wg_sec_elem_offset_fir, p->wedge_p->wg_pri_axis_reference,
            p->wedge_p->wg_sec_axis_reference, p->wedge_p->wg_length, p->wedge_p->wg_width,
            p->wedge_p->wg_height, p->wedge_p->wg_separation );
            
   //Wedge---------receiver
   fprintf(fp," %lf %lf %lf\015\012  %lf %d %lf\015\012  %lf %lf %lf\015\012  %lf %lf %lf\015\012  %lf %lf\015\012", 
            p->wedge_r->wg_wedge_angle, p->wedge_r->wg_roof_angle, p->wedge_r->wg_lon_vel,
            p->wedge_r->wg_trans_vel, p->wedge_r->wg_density, p->wedge_r->wg_heigh_fir,
            p->wedge_r->wg_pri_elem_offset_fir, p->wedge_r->wg_sec_elem_offset_fir, p->wedge_r->wg_pri_axis_reference,
            p->wedge_r->wg_sec_axis_reference, p->wedge_r->wg_length, p->wedge_r->wg_width,
            p->wedge_r->wg_height, p->wedge_r->wg_separation );
   
   //scanner
   fprintf(fp," %lf %lf %lf\015\012  %lf %lf %lf  \015\012", 
            p->scanner->scan_axis_off, p->scanner->index_axis_off, p->scanner->usound_axis_off,
            p->scanner->scan_axis_ori, p->scanner->index_axis_ori, p->scanner->usound_axis_ori );
   
   //Beam angle selection
   fprintf(fp," %lf %lf %lf\015\012  %lf %lf %lf\015\012  %lf %lf %lf\015\012  %lf %lf %lf\015\012  %d %d\015\012", 
            p->beam_angle->beam_pri_steer_angle_start, p->beam_angle->beam_pri_steer_angle_stop, p->beam_angle->beam_pri_steer_angle_resolution,
            p->beam_angle->beam_sec_steer_angle_start, p->beam_angle->beam_sec_steer_angle_stop, p->beam_angle->beam_sec_steer_angle_resolution,
            p->beam_angle->beam_refrac_angle_start, p->beam_angle->beam_refrac_angle_stop, p->beam_angle->beam_refrac_angle_resolution,
            p->beam_angle->beam_skew_angle_start, p->beam_angle->beam_skew_angle_stop, p->beam_angle->beam_skew_angle_resolution,
            p->beam_angle->beam_type, p->beam_angle->beam_angle_sel  );
            
   //focal point selection    
   fprintf(fp," %d %lf %lf\015\012  %lf %lf %lf %lf %lf \015\012", 
            p->focal_point->focal_focus_type, p->focal_point->focal_focus_point_start, p->focal_point->focal_focus_point_stop,
            p->focal_point->focal_focus_point_resolution, p->focal_point->offset_start, p->focal_point->offset_end,
            p->focal_point->depth_start, p->focal_point->depth_end   );  
            
   //element selection    
   fprintf(fp," %d %d %d\015\012  %d %d %d\015\012  %d %d %d\015\012  %d015\012", 
            p->element_sel->primary_axis_s, p->element_sel->primary_axis_e, p->element_sel->primary_axis_r,
            p->element_sel->seconary_axis_s, p->element_sel->seconary_axis_e, p->element_sel->seconary_axis_r,
            p->element_sel->pri_axis_ape, p->element_sel->sec_axis_ape, p->element_sel->connection,
            p->element_sel->linear );   
      
   //specimen settings    
   fprintf(fp," %d %d %lf\015\012  %lf %lf %lf\015\012  %lf %lf %d\015\012  %s\015\012", 
            p->specimen->speci_longitudinal_wave, p->specimen->speci_transverse_wave, p->specimen->speci_length_flat,
            p->specimen->speci_height_flat, p->specimen->speci_width_flat, p->specimen->speci_inside_cylindrical,
            p->specimen->speci_outside_cylindrical, p->specimen->speci_length_cylindrical, p->specimen->flat_cylindrical,
            p->specimen->Inspection_od_id  );
            
   //location    
   fprintf(fp," %lf %lf %lf\015\012  %lf %lf %lf\015\012  %lf %lf %lf\015\012  %d %d %d\015\012", 
            p->location->center_x, p->location->center_y, p->location->center_z,
            p->location->rotation_x, p->location->rotation_y, p->location->rotation_z,
            p->location->translation_x, p->location->translation_y, p->location->translation_z,
            p->location->st1, p->location->st2, p->location->st3  );
            
   //projected squence    
   fprintf(fp," %d %d\015\012", 
            p->project->circum_axial, p->project->state );
            
   
            
}



void load_beam_setup(GtkWidget *widget,gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    GtkFileFilter* filter;
    FILE *fp;
    gint i,j,count;
    
    count = 0;
    p->dialog = gtk_file_chooser_dialog_new ("Load Beam Data",
    				      GTK_WINDOW (p->window),
    				      GTK_FILE_CHOOSER_ACTION_OPEN,
    				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
    				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
    				      NULL);
    
    //*****************文件选择类型过滤************************
    //后缀为*.BeamData的文件
    filter = gtk_file_filter_new();
    gtk_file_filter_set_name (filter, "Beam Data Files(*.BeamData)");
    gtk_file_filter_add_pattern(filter,"*.BeamData");
    gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (p->dialog),filter);
    /*所有文件*/
    filter = gtk_file_filter_new();
    gtk_file_filter_set_name (filter, "*.All");
    gtk_file_filter_add_pattern(filter,"*");
    gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (p->dialog),filter);
    
    if (gtk_dialog_run (GTK_DIALOG (p->dialog)) == GTK_RESPONSE_ACCEPT)
      {
        char *filename;
        filename = g_locale_from_utf8( gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p->dialog)),-1,NULL,NULL,NULL );          
#if DEBUG        
        g_printf("filename=%s\n",filename);
#endif                  
       if((fp = fopen(filename,"r"))==NULL)
        {
          g_printf("cannot open this file\n");  
          return ;
        }
        else
        {                       
           read_beam_data((gpointer)p,fp);            
        }        
        fclose(fp);
        g_free (filename);
      }
    gtk_widget_destroy (p->dialog);

}
//读取磁盘上的.BeamData文件 
void read_beam_data(gpointer data,FILE *fp)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
     
    //Probe---------transmitter
    fscanf(fp,"%d %d %d\015\012  %d %lf %lf\015\012  %d %d %lf\015\012  %lf %lf %lf\015\012", 
            &p->probe_p->D1_D2, &p->probe_p->Pitch_Catch, &p->probe_p->transmi_trans_longi,
            &p->probe_p->recev_trans_longi, &p->probe_p->pb_skew_angle, &p->probe_p->pb_frequency,
            &p->probe_p->ele_num_pri, &p->probe_p->ele_num_sec, &p->probe_p->pri_axis_pitch,
            &p->probe_p->sec_axis_pitch, &p->probe_p->pri_ele_size, &p->probe_p->sec_ele_size);
      
   //Probe---------receiver
   fscanf(fp," %lf %lf %d\015\012  %d %lf %lf\015\012  %lf %lf\015\012", 
            &p->probe_p->pb_skew_angle_r, &p->probe_p->pb_frequency_r, &p->probe_p->ele_num_pri_r,
            &p->probe_p->ele_num_sec_r, &p->probe_p->pri_axis_pitch_r, &p->probe_p->sec_axis_pitch_r,
            &p->probe_p->pri_ele_size_r, &p->probe_p->sec_ele_size_r );
            
   //Wedge---------transmitter
   fscanf(fp," %lf %lf %lf\015\012  %lf %d %lf\015\012  %lf %lf %lf\015\012  %lf %lf %lf\015\012  %lf %lf\015\012", 
            &p->wedge_p->wg_wedge_angle, &p->wedge_p->wg_roof_angle, &p->wedge_p->wg_lon_vel,
            &p->wedge_p->wg_trans_vel, &p->wedge_p->wg_density, &p->wedge_p->wg_heigh_fir,
            &p->wedge_p->wg_pri_elem_offset_fir, &p->wedge_p->wg_sec_elem_offset_fir, &p->wedge_p->wg_pri_axis_reference,
            &p->wedge_p->wg_sec_axis_reference, &p->wedge_p->wg_length, &p->wedge_p->wg_width,
            &p->wedge_p->wg_height, &p->wedge_p->wg_separation );
   
   //Wedge---------receiver
   fscanf(fp," %lf %lf %lf\015\012  %lf %d %lf\015\012  %lf %lf %lf\015\012  %lf %lf %lf\015\012  %lf %lf\015\012", 
            &p->wedge_r->wg_wedge_angle, &p->wedge_r->wg_roof_angle, &p->wedge_r->wg_lon_vel,
            &p->wedge_r->wg_trans_vel, &p->wedge_r->wg_density, &p->wedge_r->wg_heigh_fir,
            &p->wedge_r->wg_pri_elem_offset_fir, &p->wedge_r->wg_sec_elem_offset_fir, &p->wedge_r->wg_pri_axis_reference,
            &p->wedge_r->wg_sec_axis_reference, &p->wedge_r->wg_length, &p->wedge_r->wg_width,
            &p->wedge_r->wg_height, &p->wedge_r->wg_separation );
            
   //scanner
   fscanf(fp," %lf %lf %lf\015\012  %lf %lf %lf  \015\012", 
            &p->scanner->scan_axis_off, &p->scanner->index_axis_off, &p->scanner->usound_axis_off,
            &p->scanner->scan_axis_ori, &p->scanner->index_axis_ori, &p->scanner->usound_axis_ori );
   
   //Beam angle selection
   fscanf(fp," %lf %lf %lf\015\012  %lf %lf %lf\015\012  %lf %lf %lf\015\012  %lf %lf %lf\015\012  %d %d\015\012", 
            &p->beam_angle->beam_pri_steer_angle_start, &p->beam_angle->beam_pri_steer_angle_stop, &p->beam_angle->beam_pri_steer_angle_resolution,
            &p->beam_angle->beam_sec_steer_angle_start, &p->beam_angle->beam_sec_steer_angle_stop, &p->beam_angle->beam_sec_steer_angle_resolution,
            &p->beam_angle->beam_refrac_angle_start, &p->beam_angle->beam_refrac_angle_stop, &p->beam_angle->beam_refrac_angle_resolution,
            &p->beam_angle->beam_skew_angle_start, &p->beam_angle->beam_skew_angle_stop, &p->beam_angle->beam_skew_angle_resolution,
            &p->beam_angle->beam_type, &p->beam_angle->beam_angle_sel  );
            
   //focal point selection    
   fscanf(fp," %d %lf %lf\015\012  %lf %lf %lf %lf %lf \015\012", 
            &p->focal_point->focal_focus_type, &p->focal_point->focal_focus_point_start, &p->focal_point->focal_focus_point_stop,
            &p->focal_point->focal_focus_point_resolution, &p->focal_point->offset_start, &p->focal_point->offset_end,
            &p->focal_point->depth_start, &p->focal_point->depth_end  );  
            
   //element selection    
   fscanf(fp," %d %d %d\015\012  %d %d %d\015\012  %d %d %d\015\012  %d015\012", 
            &p->element_sel->primary_axis_s, &p->element_sel->primary_axis_e, &p->element_sel->primary_axis_r,
            &p->element_sel->seconary_axis_s, &p->element_sel->seconary_axis_e, &p->element_sel->seconary_axis_r,
            &p->element_sel->pri_axis_ape, &p->element_sel->sec_axis_ape, &p->element_sel->connection,
            &p->element_sel->linear );   
      
   //specimen settings    
   fscanf(fp," %d %d %lf\015\012  %lf %lf %lf\015\012  %lf %lf %d\015\012  %s\015\012", 
            &p->specimen->speci_longitudinal_wave, &p->specimen->speci_transverse_wave, &p->specimen->speci_length_flat,
            &p->specimen->speci_height_flat, &p->specimen->speci_width_flat, &p->specimen->speci_inside_cylindrical,
            &p->specimen->speci_outside_cylindrical, &p->specimen->speci_length_cylindrical, &p->specimen->flat_cylindrical,
            &p->specimen->Inspection_od_id  );
            
   //location    
   fscanf(fp," %lf %lf %lf\015\012  %lf %lf %lf\015\012  %lf %lf %lf\015\012  %d %d %d\015\012", 
            &p->location->center_x, &p->location->center_y, &p->location->center_z,
            &p->location->rotation_x, &p->location->rotation_y, &p->location->rotation_z,
            &p->location->translation_x, &p->location->translation_y, &p->location->translation_z,
            &p->location->st1, &p->location->st2, &p->location->st3  );
            
   //projected squence    
   fscanf(fp," %d %d\015\012", 
            &p->project->circum_axial, &p->project->state );
     
                    
}


//********************************************************
//         保存.law文件  
//********************************************************
void save_law(GtkWidget *widget,gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    FILE *fp;
   
   if((fp = fopen("./law1.law","wb+"))==NULL)
   {
      g_printf("cannot open this file\n");  
      return ;
   }
   else
   {                       
        save_law_data((gpointer)p ,fp);          
   }
   fclose(fp);
}

void save_as_law(GtkWidget *widget,gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    GtkFileFilter* filter;
    FILE *fp;
    gint i,j,count;
    
    count = 0;
    p->filechooser = gtk_file_chooser_dialog_new ("Save .law File",
				      GTK_WINDOW (p->window),
				      GTK_FILE_CHOOSER_ACTION_SAVE,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
				      NULL);
    
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (p->filechooser), TRUE);
    //*****************文件选择类型过滤************************
    //后缀为*.BeamData的文件
    filter = gtk_file_filter_new();
    gtk_file_filter_set_name (filter, ".law File(*.law)");
    gtk_file_filter_add_pattern(filter,"*.law");
    gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (p->filechooser),filter);

    gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (p->filechooser), "law1.law");

    if (gtk_dialog_run (GTK_DIALOG (p->filechooser)) == GTK_RESPONSE_ACCEPT)//捕捉保存按钮信号 
      {
        char *filename;

        filename = g_locale_from_utf8( gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p->filechooser)),-1,NULL,NULL,NULL );
               
        //检查filename_1中有没有.law字符串            
        for(i = 0;i < strlen(filename);i++)
        {
            if( filename[i] == '.')
            {                
                count ++;    
            }
        }
        //没有.law的时候 加上，没有的时候 不加        
        if(!count)
            strcat(filename,".law");
                          
       if((fp = fopen(filename,"wb+"))==NULL)
        {
          g_printf("cannot open this file\n");  
          return ;
        }
        else
        {                    
           save_law_data((gpointer)p ,fp); 
        }        
        fclose(fp);
        g_free (filename);
      }
    gtk_widget_destroy (p->filechooser);
}

//
void save_law_data(gpointer data,FILE *fp)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    
    gint i,j,l;
    gdouble depth,path;
    gdouble a2,a3,a_,a_tmp;
    gdouble c1,c2;
    /* focus type */
    if     (p->focal_point->focal_focus_type==0) path=p->focal_point->focal_focus_point_start;//half path
    else if(p->focal_point->focal_focus_type==1) depth=p->focal_point->focal_focus_point_start;//true depth
    else if(p->focal_point->focal_focus_type==2) ;//Projection
    else if(p->focal_point->focal_focus_type==3) ;//Focal plane
    /*True depth（Yp）or Half Path（S）*/
    if((p->beam_angle->beam_angle_sel==1))
    {  
       a2=(p->beam_angle->beam_pri_steer_angle_start)*PI/180;
       a_tmp=a2;
       a3=(p->beam_angle->beam_pri_steer_angle_stop)*PI/180;
       a_=(p->beam_angle->beam_pri_steer_angle_resolution)*PI/180;
    }
    else if((p->beam_angle->beam_angle_sel==0))
    {
        a2 = (p->beam_angle->beam_refrac_angle_start)*PI/180; /*聚焦角度1*/
        a_tmp = a2;
        a3 = (p->beam_angle->beam_refrac_angle_stop)*PI/180; /*聚焦角度2*/
        a_ = (p->beam_angle->beam_refrac_angle_resolution)*PI/180; /*聚焦步进*/ 
    }
    /* 声速 */
    if(p->probe_p->transmi_trans_longi==0)
    {   
        c2  = p->specimen->speci_transverse_wave;    /* 样本横波声速 */  
    }                                           
    else                                 
    { 
        c2  = p->specimen->speci_longitudinal_wave;  /* 样本纵波声速 */
    }
   
   
   /*保存计算结果*/
   p->law[0].Version[0]='V';p->law[0].Version[1]='5';
   p->law[0].Version[2]='.';p->law[0].Version[3]='0';
   
   p->law[0].N_laws = p->probe_p->ele_num_pri;/*聚焦法则数量*/
   
   for(i=0; i < p->law[0].N_laws; i++)
   {
       p->law[i].N_ActiveElements = p->element_sel->pri_axis_ape;/*实际产生聚焦法则的数量*/ 
       p->law[i].frequency = p->probe_p->pb_frequency;/*频率*/
       p->law[i].cycle = 1;/* ??? */
       p->law[i].sumgain = 24;/* 增益 */ 
       p->law[i].mode = 1;/* ??? */
       p->law[i].filter = 0;/* ??? */
       p->law[i].R_angle = a2;/* 折射角 */ 
       p->law[i].S_angle = 0;/* 偏角 */
       p->law[i].T_first = i+1;/* 发射起始阵元 */
       p->law[i].R_first = i+1;/* 接收起始阵元 */
       p->law[i].Scan_offset = p->scanner->scan_axis_off;/*主轴扫描偏移*/
       p->law[i].Index_offset= p->scanner->index_axis_off;/*次轴扫描偏移*/
       p->law[i].G_delay = p->G_Time[p->k];
       p->law[i].F_depth = depth;/*聚焦深度*/
       p->law[i].M_velocity = c2;/* 材料声速 */

       for(l=0; l < p->final_num; l++)
       {
           for(j=0; j < p->law[i].N_ActiveElements; j++)
           {
              p->element[i][l][j].E_number = j+1; 
              p->element[i][l][j].FL_gain =  0; 
              p->element[i][l][j].T_delay = p->timedelay[l][j+1];/* 发送延时 */
              p->element[i][l][j].R_delay = p->timedelay[l][j+1];/* 接收延时 */  
              p->element[i][l][j].Amplitude = 180; 
              p->element[i][l][j].P_width = 250;/*发射脉宽*/  
           }
       }
   }
    
          
   fprintf(fp,"%s    %d\015\012",p->law[0].Version, p->law[0].N_laws );
   for(i=0; i < p->law[0].N_laws; i++)
   {
      fprintf(fp,"%d    %d    %d    %d    %d    %d    %d    %d    %d    %d    %d    %d    %d    %d    %d\015\012",
                p->law[i].N_ActiveElements, p->law[i].frequency, p->law[i].cycle, p->law[i].sumgain, p->law[i].mode,
                p->law[i].filter, p->law[i].R_angle, p->law[i].S_angle, p->law[i].T_first, p->law[i].R_first,
                p->law[i].Scan_offset, p->law[i].Index_offset, p->law[i].G_delay, p->law[i].F_depth, p->law[i].M_velocity );
      
      for(l=0; l < p->final_num; l++)
      {
          for(j=0; j < p->law[i].N_ActiveElements; j++)
                fprintf(fp,"%d    %d    %d    %d    %d    %d\015\012",          
                    p->element[i][l][j].E_number, p->element[i][l][j].FL_gain,   p->element[i][l][j].T_delay,
                    p->element[i][l][j].R_delay,  p->element[i][l][j].Amplitude, p->element[i][l][j].P_width ); 
                fprintf(fp,"\015\012");
     } 
   } 

   
}
