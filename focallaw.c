/************************************************* 
               ¾Û½¹·¨Ôò 
 ************************************************* */

#include "drawui.h"
#include <math.h>
#define PI G_PI

void focal_law(GtkWidget *widget, gpointer data);/*»Øµ÷º¯Êý*/
void focal_law_type(gpointer data, gdouble RefractAngle, gdouble ScrewAnlge, gdouble FocusLocation) ;
void current_focal_law(gpointer data);
void clear_focal_law(gpointer data); //¾Û½¹·¨ÔòÊý¾ÝÇåÁã 
void LinearFocusLaw(gpointer p, gdouble RefractAngle, gdouble ScrewAngle);
void DepthFocusLaw(gpointer data, gdouble RefractAngle, gdouble ScrewAngle);

/*¾Û½¹·¨ÔòËã·¨ÊµÏÖ*/
void flat_1d_roof(gpointer data, gdouble angle1, gdouble depth);
void flat_2d_roof(gpointer data, gdouble angle1, gdouble angle2, gdouble depth);
void flat_1d_pr(gpointer data, gdouble angle1, gdouble depth);
void flat_1d_wedge_pr(gpointer data, gdouble angle1, gdouble depth);
void flat_1d_roof_pr(gpointer data, gdouble angle1, gdouble depth);
void flat_2d_roof_pr(gpointer data, gdouble angle1, gdouble angle2, gdouble depth);
void cylinder_2d_roof_od (gpointer data, gdouble angle1, gdouble angle2, gdouble depth);
void cylinder_2d_roof_id(gpointer data, gdouble angle1, gdouble angle2 , gdouble depth);
void cylinder_2d_roof_od_pr(gpointer data, gdouble angle1, gdouble angle2, gdouble depth);
void cylinder_2d_roof_id_pr(gpointer data, gdouble angle1, gdouble angle2, gdouble depth);
/*  angle and depth transfer  */
int ProjectionToDepth_1d_roof (gpointer data, double RefractAngle, double Projection, double* FocusDepth);
int PlaneToDepth_1d_roof (gpointer data, double RefractAngle, double* FocusDepth);
int AngleSteerToRefract_1d_roof( gpointer data , gdouble beam_steer_angle, gdouble* RefractAngle);
int BeamSkewToRefract_1d_roof( gpointer data , gdouble beam_skew_angle, gdouble* RefractAngle);
int PlaneToDepth_2d_roof (gpointer data, gdouble angle1, gdouble angle2, double* FocusDepth) ;
int ProjectionToDepth_2d_roof(gpointer data,gdouble angle1,gdouble angle2,double Projection,double * FocusDepth);

void focal_law(GtkWidget *widget, gpointer data) 
{ 
     DRAW_UI_P p = (DRAW_UI_P)(data);
     gdouble ScrewAnlge ; 
     gdouble depth;
     gdouble a2,a3,a_;
	 
     depth =p->focal_point->focal_focus_point_start; 
     ScrewAnlge  =  p->beam_angle->beam_skew_angle_start ;
     /*True depth£¨Yp£©or Half Path£¨S£©*/
	 switch(p->probe_p->D1_D2)
     {
          case 0://1D
                if((p->beam_angle->beam_angle_sel==0))
                {
                    a2 = (p->beam_angle->beam_refrac_angle_start); 
                    a3 = (p->beam_angle->beam_refrac_angle_stop); 
                    a_ = (p->beam_angle->beam_refrac_angle_resolution);
                }
                else if((p->beam_angle->beam_angle_sel==1))
                {  
                    a2=(p->beam_angle->beam_pri_steer_angle_start);
                    a3=(p->beam_angle->beam_pri_steer_angle_stop);
                    a_=(p->beam_angle->beam_pri_steer_angle_resolution);
                }
                else if((p->beam_angle->beam_angle_sel==2))
                {
                    a2 = (p->beam_angle->beam_skew_angle_start);
                    a3 = (p->beam_angle->beam_skew_angle_stop); 
                    a_ = (p->beam_angle->beam_skew_angle_resolution);
                }
               break;
          case 1://2D
               if((p->beam_angle->beam_angle_sel==0))
                {
                    
                }
                else if((p->beam_angle->beam_angle_sel==1))
                {  
                    
                }
                else if((p->beam_angle->beam_angle_sel==2))
                {
                    
                }
                else if((p->beam_angle->beam_angle_sel==3))
                {
                    a2 = (p->beam_angle->beam_refrac_angle_start); 
                    a3 = (p->beam_angle->beam_refrac_angle_stop); 
                    a_ = (p->beam_angle->beam_refrac_angle_resolution);
                }
               break;                            
     }
	 
     //¾Û½¹·¨ÔòÊý¾ÝÏÈÇåÁã 
     clear_focal_law(p);
     p->k = 0;    
     switch(p->probe_p->D1_D2)
     {
       case 0://1D
            switch(p->beam_angle->beam_type)
            {
                case 0://Azimuthal
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Refracted angle
                                current_focal_law(p);
                                break;
                          case 1://Primary steering angle
                                current_focal_law(p);
                                break;
                          case 2://Beam screw angle 
                                current_focal_law(p);
                                break;  
                      }
                      break;
                case 1://Linear
                       switch(p->beam_angle->beam_angle_sel)
                        {
                           case 0://Refracted
                                LinearFocusLaw(p, a2, 0);
                                break;
                           case 1://Primary steering
                                p->is_draw_focus = AngleSteerToRefract_1d_roof(p,a2,&a2);
                                if(p->is_draw_focus)
                                     LinearFocusLaw(p, a2, 0);
								else 
									 WarnningDialog(p);
                                break;
                           case 2://Beam skew
                                p->is_draw_focus = BeamSkewToRefract_1d_roof(p,a2,&a2);
                                if(p->is_draw_focus)
                                     LinearFocusLaw(p, a2, 0);
								else 
									 WarnningDialog(p);
                                break;  
                        }
                      break;
                case 2://Depth
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Refracted angle
							    DepthFocusLaw(p, a2, 0);
                                break;
                          case 1://Primary steering angle
	  							p->is_draw_focus = AngleSteerToRefract_1d_roof(p,a2,&a2);  
                                if(p->is_draw_focus)
	  								   DepthFocusLaw(p, a2, 0);
	  							else 
	  								   WarnningDialog(p);
                                break;
                          case 2://Beam screw angle 
							    p->is_draw_focus = BeamSkewToRefract_1d_roof(p,a2,&a2);
                                if(p->is_draw_focus)
								      DepthFocusLaw(p, a2, 0);
							    else 
								      WarnningDialog(p);
                                break;  
                      }
                      break;
                case 3://Static
                       switch(p->beam_angle->beam_angle_sel)
                        {
                           case 0://Refracted
                                g_printf("\ndegree=%f \n",a2);
                                focal_law_type(p, a2, ScrewAnlge, depth) ;
                                break;
                           case 1://Primary steering
                                g_printf("\ndegree=%f \n",a2);
						        p->is_draw_focus = AngleSteerToRefract_1d_roof(p,a2,&a2);
                                if(p->is_draw_focus)
	                                 focal_law_type(p, a2, ScrewAnlge, depth) ;
                                else WarnningDialog(p);
                                break;
                           case 2://Beam skew
                                p->is_draw_focus = BeamSkewToRefract_1d_roof(p,a2,&a2);
                                if(p->is_draw_focus)
	                                  focal_law_type(p, a2, ScrewAnlge, depth) ;
                                else WarnningDialog(p);
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
                                current_focal_law(p);
                                break;
                          case 1://Primary/Beam skew angle
                                current_focal_law(p);
                                break;
                          case 2://Secondary/Refracted angle 
                                current_focal_law(p);
                                break;
                          case 3://Refracted/Beam skew angle 
                                current_focal_law(p);
                                break; 
                      } 
                      break;
                case 1://Linear
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Primary/Secondary steering angle
                              
                                break;
                          case 1://Primary/Beam skew angle

                                break;
                          case 2://Secondary/Refracted angle 

                                break;
                          case 3://Refracted/Beam skew angle 
                                LinearFocusLaw(p, a2, ScrewAnlge);
                                break; 
                      } 
                      break;
                case 2://Depth
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Primary/Secondary steering angle

                                break;
                          case 1://Primary/Beam skew angle

                                break;
                          case 2://Secondary/Refracted angle 

                                break;
                          case 3://Refracted/Beam skew angle 
							    DepthFocusLaw(p, a2, ScrewAnlge);
                                break; 
                      } 
                      break;
                case 3://Static
                      switch(p->beam_angle->beam_angle_sel)
                      {
                          case 0://Primary/Secondary steering angle
 
                                break;
                          case 1://Primary/Beam skew angle

                                break;
                          case 2://Secondary/Refracted angle 

                                break;
                          case 3://Refracted/Beam skew angle 
                                g_printf("\ndegree=%f \n",a2);
                                focal_law_type(p, a2, ScrewAnlge, depth) ;
                                break; 
                      } 
                      break;              
            }            
            
            break;              
     }     
    
    p->DrawResult = 1;
    //
    gtk_widget_destroy(p->hbox_delay);
    p->hbox_delay = ShowElementDelay_time(p);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->ScrooledWindow),p->hbox_delay);
    if(p->show_hide)
       gtk_widget_show_all(p->ScrooledWindow);
    //µ±Ìõ¼þ³ÉÁ¢Ê±¸üÐÂ
    if( p->is_draw_focus)
    {
        InsertCurrentFocallaw(p);//µ±Ç°¾Û½¹ÐÅÏ¢
        InsertElementDelay(p);//ÊµÊ±¸üÐÂÑÓÊ±ÐÅÏ¢
    }           
    force_updata(p);
}

void current_focal_law(gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data); 
    gdouble diameter;
    gdouble ScrewAnlge; 
    gdouble depth;
    gdouble a1,a2,a3,a_,a_tmp,sin_t;
	gdouble screwStart, screwEnd, screwStep, screwTemp ;
    gdouble c1,c2;
    gint l;
    gint temp1 , temp2 , temp3 ;
    gint count ;
	
    count = 0;
    a1 = p->wedge_p->wg_wedge_angle; /*Ð¨¿é½Ç¶È*/
    ScrewAnlge  =  p->beam_angle->beam_skew_angle_start ;
    if( !strcmp(p->specimen->Inspection_od_id,"ID") ) // ID
       diameter= p->specimen->speci_inside_cylindrical;/*Ö±¾¶*/
    else
       diameter= p->specimen->speci_outside_cylindrical;/*Ö±¾¶*/
    /* ÉùËÙ */
    if(p->probe_p->transmi_trans_longi==0)
    {   
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
        c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
    }                                           
    else                                 
    {
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
        c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
    }

	if(p->focal_point->focal_focus_type == 0 || p->focal_point->focal_focus_type == 1)
         depth = p->focal_point->focal_focus_point_start;//half path
    else 
		 depth = p->focal_point->offset_start    ;
	
    /*True depth£¨Yp£©or Half Path£¨S£©*/
    switch(p->probe_p->D1_D2)
       {
          case 0://1D
                if((p->beam_angle->beam_angle_sel==0))
                {
                    a2 = (p->beam_angle->beam_refrac_angle_start);
                    a_tmp=a2; 
                    a3 = (p->beam_angle->beam_refrac_angle_stop); 
                    a_ = (p->beam_angle->beam_refrac_angle_resolution);
                }
                else if((p->beam_angle->beam_angle_sel==1))
                {  
                    a2=(p->beam_angle->beam_pri_steer_angle_start);
                    a_tmp=a2;
                    a3=(p->beam_angle->beam_pri_steer_angle_stop);
                    a_=(p->beam_angle->beam_pri_steer_angle_resolution);
                }
                else if((p->beam_angle->beam_angle_sel==2))
                {
                    a2 = (p->beam_angle->beam_skew_angle_start);
                    a_tmp=a2;
                    a3 = (p->beam_angle->beam_skew_angle_stop); 
                    a_ = (p->beam_angle->beam_skew_angle_resolution);
                }
               break;
          case 1://2D
               if((p->beam_angle->beam_angle_sel==0))
                {
                    
                }
                else if((p->beam_angle->beam_angle_sel==1))
                {  
                    
                }
                else if((p->beam_angle->beam_angle_sel==2))
                {
                    
                }
                else if((p->beam_angle->beam_angle_sel==3))
                {
                    a2 = (p->beam_angle->beam_refrac_angle_start);
                    a_tmp = a2; 
                    a3 = (p->beam_angle->beam_refrac_angle_stop); 
                    a_ = (p->beam_angle->beam_refrac_angle_resolution);
					screwStart = (p->beam_angle->beam_skew_angle_start);
                    screwTemp  = screwStart;
                    screwEnd  = (p->beam_angle->beam_skew_angle_stop); 
                    screwStep = (p->beam_angle->beam_skew_angle_resolution);     
                }
               break;                            
       }
    
	
    if(a_ == 0) return;//kill the impossible thing    
    
    l = (gint) ((a3 - a2) / a_);
    if((a2 > a3))//kill the impossible thing
    {
        WarnningDialog(p);
        return;
    }
    
    ///Ö»ÓÐ Azimuthal Ê±£¬²Å»áÓÐ 
    if(p->beam_angle->beam_type == 0)//
    {
        
        switch(p->probe_p->D1_D2)
        {
           case 0://1D
                  switch(p->beam_angle->beam_angle_sel)
                  {
                       case 0://Refracted angle
                            for ( p->tmp_k = 0; p->tmp_k < l + 1; p->tmp_k ++ ) 
                            {
            	                  p->k     = p->tmp_k;
            	                  p->del_k = p->tmp_k;
            	                  a2 = a_tmp + a_ * (p->k);
            	                  g_printf("\ndegree=%f \n",a2);
            	                  focal_law_type(p, a2, ScrewAnlge, depth) ;
                            }
                            break;
                       case 1://Primary steering angle
                            for ( p->tmp_k = 0; p->tmp_k < l + 1; p->tmp_k ++ ) 
                            {
            	                  p->k     = p->tmp_k;
            	                  p->del_k = p->tmp_k;
            	                  a2 = a_tmp + a_ * (p->k);
            	                  g_printf("\ndegree=%f \n",a2);
            					  // angle transfer
            	                  p->is_draw_focus = AngleSteerToRefract_1d_roof(p,a2,&a2);
                                  if(p->is_draw_focus)
            	                         focal_law_type(p, a2, ScrewAnlge, depth) ;
                                  else   
                                  {
                                     count++;
                                     if(count==1)
                                         WarnningDialog(p);
                                  }
                            }
                            count = 0;
                            break;
                       case 2://Beam screw angle 
                            for ( p->tmp_k = 0; p->tmp_k < l + 1; p->tmp_k ++ ) 
                            {
            	                  p->k     = p->tmp_k;
            	                  p->del_k = p->tmp_k;
            	                  a2 = a_tmp + a_ * (p->k);
            	                  g_printf("\ndegree=%f \n",a2);
            					  // angle transfer
            	                  p->is_draw_focus = BeamSkewToRefract_1d_roof(p,a2,&a2);
                                  if(p->is_draw_focus)
            	                          focal_law_type(p, a2, ScrewAnlge, depth);
                                  else   
                                  {
                                     count++;
                                     if(count==1)
                                     {
                                          WarnningDialog(p);       
                                          p->DrawResult = 1 ;
                                     }   
                                  }
                            }
                            count = 0;
                            break;  
                  } 
                  break;
           case 1://2D
                  switch(p->beam_angle->beam_angle_sel)
                  {
                      case 0://Primary/Secondary steering angle
                            
                            break;
                      case 1://Primary/Beam skew angle
                            
                            break;
                      case 2://Secondary/Refracted angle 
                            
                            break;
                      case 3://Refracted/Beam skew angle 
                            if(screwEnd < screwStart) break ;
                            temp3 =1+ (gint)((screwEnd - screwStart) / screwStep) ;
							l = (l+1) * temp3 ;
                            for ( p->tmp_k = 0; p->tmp_k < l ; p->tmp_k ++ ) 
                            {
            	                  p->k     = p->tmp_k;
            	                  p->del_k = p->tmp_k;
								  temp1 = p->tmp_k / temp3 ;
								  temp2 = p->tmp_k % temp3 ;
								  
            	                  a2 = a_tmp + a_ * temp1;
								  screwTemp = screwStart + screwStep * temp2 ;
            	                  g_printf("\ndegree=%f \n",a2);
            	                   
            	                  focal_law_type(p, a2, screwTemp, depth) ;
                            }
                            break; 
                 } 
                 break;              
         }     
    }
}


void LinearFocusLaw(gpointer data, gdouble RefractAngle, gdouble ScrewAngle)
{
          DRAW_UI_P p = (DRAW_UI_P)(data);
		  gdouble a1 = RefractAngle;
		  gdouble a2 = ScrewAngle;
		  int l;
		  
		  int ElementStart = p->element_sel->primary_axis_s-  1   ;
          int ElementColumn= p->probe_p->ele_num_pri              ;
          int SelectColumn = p->element_sel->pri_axis_ape         ;
		  int LinearStop   = p->element_sel->primary_axis_e       ;
          int ElementStop  =   SelectColumn+ LinearStop           ;
		  int PriElementResolution = p->element_sel->primary_axis_r;
		  if(ElementStop>ElementColumn)  
		  {
		      WarnningDialog(p);
			  return  ;
		  }
		  switch(p->probe_p->D1_D2)
		   {
			  case 0://1D
                    
					l =  1+(LinearStop -1 - ElementStart)/PriElementResolution  ;
                    for ( p->tmp_k = 0; p->tmp_k < l ; p->tmp_k ++ ) 
                    {        
    	                  p->element_sel->primary_axis_s = ElementStart + p->tmp_k * PriElementResolution + 1;
						  if(p->element_sel->primary_axis_s > ElementColumn )  continue ;
						  p->k     = p->tmp_k;
    	                  p->del_k = p->tmp_k;
    	                  focal_law_type(p, a1, 0, p->focal_point->focal_focus_point_start);                        
                    }
					p->element_sel->primary_axis_s = ElementStart + 1 ;
					break;
			  case 1://2D
			        l =  1+(LinearStop -1 - ElementStart)/PriElementResolution  ;
                    for ( p->tmp_k = 0; p->tmp_k < l ; p->tmp_k ++ ) 
                    {        
    	                  p->element_sel->primary_axis_s = ElementStart + p->tmp_k * PriElementResolution + 1;
						  if(p->element_sel->primary_axis_s > ElementColumn )  continue ;
						  p->k     = p->tmp_k;
    	                  p->del_k = p->tmp_k;
    	                  focal_law_type(p, a1, a2, p->focal_point->focal_focus_point_start);                        
                    }
					p->element_sel->primary_axis_s = ElementStart + 1 ;
			        break ;
			}	  
      
}

void DepthFocusLaw(gpointer data, gdouble RefractAngle, gdouble ScrewAngle)
{
          DRAW_UI_P p = (DRAW_UI_P)(data);
		  gdouble a1 = RefractAngle;
		  gdouble a2 = ScrewAngle;
		  int l;
          double DepthStart = p->focal_point->focal_focus_point_start  ;
		  double DepthEnd   = p->focal_point->focal_focus_point_stop   ;
		  double Resolution = p->focal_point->focal_focus_point_resolution;
          if(DepthStart > DepthEnd ) return ;
		  l = 1 + (int)(DepthEnd - DepthStart)/Resolution     ;

		  for ( p->tmp_k = 0; p->tmp_k < l ; p->tmp_k ++ ) 
		  {        
		      DepthEnd = DepthStart + Resolution * p->tmp_k  ;
			  p->k     = p->tmp_k;
		      p->del_k = p->tmp_k;
		      focal_law_type(p, a1, a2, DepthEnd);                        
		  }
				
}


/*¾Û½¹ÀàÐÍº¯Êý*/
// input           data:  pointer to parameters of wedge  probe specimen beam  focuspoint
//         RefractAngle:   Refract angle  (-90  to  90 degree)
//          ScrewAngle :    Screw angle  (-180  to 180 degree)
//        FocusLocation:  Could be True depth and half path
//return    0  :  normal ending
//            1  :   sender wedge focus point error
//            2  :   receiver wedge focus point error
//          -1  :   refract point error 
void focal_law_type(gpointer data, gdouble RefractAngle, gdouble ScrewAnlge, gdouble FocusLocation) 
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     gdouble FocusDepth;
	 gdouble temp;
	 gdouble r1 = p->specimen->speci_outside_cylindrical/2;
	 gdouble r2 = p->specimen->speci_inside_cylindrical/2 ;
	 gdouble a1 = RefractAngle*PI/180;
	 gdouble a2 = ScrewAnlge*PI/180;
	 gdouble AngleProjection;
	 
     switch(p->probe_p->D1_D2)
     {                         
         case 0:
            /* 1-D ¾Û½¹Ëã·¨ */
	        if(p->probe_p->Pitch_Catch == 0)
	        {
                      switch(p->specimen->flat_cylindrical)
                      {
                       /*Èç¹ûÑ¡ÖÐ Flat*/				   
                       case 0:
					   	           if(p->focal_point->focal_focus_type==0)      //half path
					   	                 { FocusDepth = FocusLocation*cos(a1);flat_1d_roof( p, RefractAngle, FocusDepth); }
								   else if(p->focal_point->focal_focus_type==1) //true depth
                                          {FocusDepth = FocusLocation ;flat_1d_roof( p, RefractAngle, FocusDepth);   }
                                   else if(p->focal_point->focal_focus_type==2) //projection
                                        {  
                                               if(!ProjectionToDepth_1d_roof(p,RefractAngle,FocusLocation,&FocusDepth))
                                                         WarnningDialog(p);
                                               else 
                                                         flat_1d_roof( p, RefractAngle, FocusDepth);   
                                        }
								   else if(p->focal_point->focal_focus_type==3)  //focal plane
                                        { 
                                              if(!PlaneToDepth_1d_roof(p, RefractAngle, &FocusDepth)) WarnningDialog(p);
                                              else flat_1d_roof( p, RefractAngle, FocusDepth);   
                                        }
						           
                           break;
                       /* Èç¹ûÑ¡ÖÐ Cylindrical */
                       case 1:        
					   	     
                             if( !strcmp(p->specimen->Inspection_od_id,"OD") ) // ID 
                             {  
                                 if(p->wedge_p->wg_roof_angle==0)
                                 {                                     
								     if(     p->focal_point->focal_focus_type==0)//half path
								     {
                                            temp = sqrt(r1*r1+FocusLocation*FocusLocation-2*r1*FocusLocation*cos(a1));
									        FocusDepth = r1 - temp;
                                     }
								     else if(p->focal_point->focal_focus_type==1)//true depth
                                            FocusDepth = FocusLocation ;
                                     else if(p->focal_point->focal_focus_type==2)//projection
                                            ;
                                     else   //focal plane
                                            ;
									 cylinder_2d_roof_od( p, RefractAngle, ScrewAnlge, FocusDepth); 
                                 }
                             }
                             else 
                             {
                                 if(p->wedge_p->wg_roof_angle==0)
                                 {                                    								     
								     if(     p->focal_point->focal_focus_type==0)//half path
								     {
                                            temp = sqrt(r2*r2+FocusLocation*FocusLocation+2*r2*FocusLocation*cos(a1));
									        FocusDepth = temp - r2;
                                     }
								     else if(p->focal_point->focal_focus_type==1)//true depth
                                            FocusDepth = FocusLocation ;
                                     else if(p->focal_point->focal_focus_type==2)//projection
                                            ;
                                     else   //focal plane
                                            ;
                                     cylinder_2d_roof_id(p, RefractAngle, ScrewAnlge, FocusDepth); 
                                 }
                             }
						   break;
					   default:
					   	   break;
                      }     
	        	}
    	   else
	       { 
	               if(!p->specimen->flat_cylindrical)
	               {
					     if(     p->focal_point->focal_focus_type==0)//half path
					     {
                                FocusDepth = FocusLocation*cos(a1);
                         }
					     else if(p->focal_point->focal_focus_type==1)//true depth
                                FocusDepth = FocusLocation ;
                         else if(p->focal_point->focal_focus_type==2)//projection
                                ;
                         else   //focal plane
                                ;
					     
			             flat_1d_pr(p, RefractAngle, FocusDepth);
	               }
	               else
	               {
                        
                    	p->DrawResult = 0;
                    	return ;
                    }
	       }
        break;
    case 1:
    /* 2-D¾Û½¹Ëã·¨ */
	   if(p->probe_p->Pitch_Catch == 0)
		{
	  		if(p->specimen->flat_cylindrical == 0)
	  		{
		            if(     p->focal_point->focal_focus_type==0)//half path
				     {
                            FocusDepth = FocusLocation*cos(a1);
							flat_2d_roof(p, RefractAngle, ScrewAnlge, FocusDepth ); 	 
                     }
				     else if(p->focal_point->focal_focus_type==1)//true depth
				     {
					        FocusDepth = FocusLocation ;
							flat_2d_roof(p, RefractAngle, ScrewAnlge, FocusDepth ); 	 
				     }
                     else if(p->focal_point->focal_focus_type==2)//projection
                     {
                            if(ProjectionToDepth_2d_roof(p, RefractAngle, ScrewAnlge, FocusLocation, &FocusDepth))
							       flat_2d_roof(p, RefractAngle, ScrewAnlge, FocusDepth ); 	
							else 
								   WarnningDialog(p);
                     } 
					 else   //focal plane
                     {
                          if(PlaneToDepth_2d_roof (p, RefractAngle, ScrewAnlge, &FocusDepth))
					            flat_2d_roof(p, RefractAngle, ScrewAnlge, FocusDepth ); 	  	
						  else
						  	    WarnningDialog(p);
                     }
	  		}
			else
	  		{
	  	 		if(!strcmp(p->specimen->Inspection_od_id,"OD"))   
	  	 		{
			        if(p->focal_point->focal_focus_type==0)
					{
					      if(a2 == 0)
					      {
							  temp = sqrt(r1*r1+FocusLocation*FocusLocation-2*r1*FocusLocation*cos(a1));
							  FocusDepth = r1 - temp;
					      }
                          else if(a1 != 0) 
						  {
					   	      temp = FocusLocation*cos(a1)           ;
							  AngleProjection = atan(tan(a1)*cos(a2)); 
							  FocusDepth = temp/cos(AngleProjection) ;
							  temp = sqrt(r1*r1+FocusDepth*FocusDepth-2*r1*FocusDepth*cos(AngleProjection));
							  FocusDepth = r1 - temp ;
						  }
						  else FocusDepth  = FocusLocation ;
					}
		            else   FocusDepth = FocusLocation ;
               		cylinder_2d_roof_od(p, RefractAngle, ScrewAnlge, FocusDepth); 
	  	 		}
				else
				{
			        if(p->focal_point->focal_focus_type==0)
					{
					      if(a2 == 0)
					      {
							  temp = sqrt(r2*r2+FocusLocation*FocusLocation+2*r2*FocusLocation*cos(a1));
							  FocusDepth = temp - r2 ;
					      }
                          else if(a1 != 0) 
						  {
					   	      temp = FocusLocation*cos(a1)           ;
							  AngleProjection = atan(tan(a1)*cos(a2)); 
							  FocusDepth = temp/cos(AngleProjection) ;
							  temp = sqrt(r2*r2+FocusDepth*FocusDepth+2*r2*FocusDepth*cos(AngleProjection));
							  FocusDepth = temp - r2 ;
						  }
						  else FocusDepth = FocusLocation ;
					}
		            else   FocusDepth = FocusLocation ;
               		cylinder_2d_roof_id(p, RefractAngle, ScrewAnlge, FocusDepth ); 
				}
	  		}	  
		}
		else
		{
	  			if(p->specimen->flat_cylindrical == 0)
		        {
		             if(p->focal_point->focal_focus_type==0)
					 {
					   	   FocusDepth = FocusLocation*cos(a1);
					 }
				     else   FocusDepth = FocusLocation ;
          			 flat_2d_roof_pr(p, RefractAngle, ScrewAnlge, FocusDepth ); 
	  			}
				else
	  			{
	  	 			if(!strcmp(p->specimen->Inspection_od_id,"OD"))   
	  	 			{
						  if(p->focal_point->focal_focus_type==0)
					      {
					          if(a2 == 0)
					          {
							      temp = sqrt(r1*r1+FocusLocation*FocusLocation-2*r1*FocusLocation*cos(a1));
							      FocusDepth = r1 - temp;
					          }
                              else if(a1 != 0) 
						      {
					   	          temp = FocusLocation*cos(a1)           ;
							  	  AngleProjection = atan(tan(a1)*cos(a2)); 
							  	  FocusDepth = temp/cos(AngleProjection) ;
							  	  temp = sqrt(r1*r1+FocusDepth*FocusDepth-2*r1*FocusDepth*cos(AngleProjection));
							      FocusDepth = r1 - temp ;
						      }
						      else FocusDepth  = FocusLocation ;
					      }
		                  else   FocusDepth = FocusLocation ;
               			  cylinder_2d_roof_od_pr(p, RefractAngle, ScrewAnlge, FocusDepth); 
	  	 			}
         			else
         			{
         				 if(p->focal_point->focal_focus_type==0)
					     {
					         if(a2 == 0)
					         {
							     temp = sqrt(r2*r2+FocusLocation*FocusLocation+2*r2*FocusLocation*cos(a1));
							     FocusDepth = temp - r2 ;
					         }
                             else if(a1 != 0) 
						     {
					   	         temp = FocusLocation*cos(a1)           ;
							     AngleProjection = atan(tan(a1)*cos(a2)); 
							     FocusDepth = temp/cos(AngleProjection) ;
							     temp = sqrt(r2*r2+FocusDepth*FocusDepth+2*r2*FocusDepth*cos(AngleProjection));
							     FocusDepth = temp - r2 ;
						     }
						     else FocusDepth = FocusLocation ;
					     }
		                 else   FocusDepth = FocusLocation ;
               			 cylinder_2d_roof_id_pr(p, RefractAngle, ScrewAnlge, FocusDepth); 	
         			}
	 			}	
    	}   
	    break;
	default:
		break;
    }

}



//*************************************************************************
//  Condition: true depth, refract angle, deflect angle
//  2d focus with roof angle
//*************************************************************************
#define SearchGate 0.001

/*
  Name:  flat_1d_roof
  Copyright: Dopplor 
  Author: Sheng Shen
  Date: 17-03-11 13:40
  Description:   Æ½Ãæ¹¤¼þ1D ´øROOF½Ç ¾Û½¹·¨Ôò 
  Input:  data: structure point to wedge probe .... coefficients
  angle1: refract angle
  depth : focus depth of sonic beam
*/
void flat_1d_roof(gpointer data, gdouble angle1, gdouble depth)
{
	DRAW_UI_P p = (DRAW_UI_P) data ;
	
	gdouble c1 ;			// wave speed
	gdouble c2 ;
	gdouble k1 ;  
	gdouble h0 = p->wedge_p->wg_heigh_fir ;				      // first element high

    int ElementStart = p->element_sel->primary_axis_s - 1;
    int ElementColumn= p->probe_p->ele_num_pri           ;
	int SelectColumn  = p->element_sel->pri_axis_ape     ;
	int ElementStop  =   SelectColumn+ ElementStart      ;
    
	gdouble Intervalx = p->probe_p->pri_axis_pitch ;		  // x direction interval distance
	gdouble pri_ele_size = p->probe_p->pri_ele_size ;      
	gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
	gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	gdouble  a1 = angle1*PI/180;							  // refract angle	
	gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180	; // roofangle	 y-z platform
	gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180	; // wedgeangle  x-z platform	  
	gdouble  FocusDepth = depth;							  //  true focus depth
	gdouble xTemp, yTemp, zTemp ;
	gdouble x0,y0,z0;										  // element center coordinate
	gdouble xP, yP, zP; 									  // focus point coordinate
	// get focus point coordinate		   
	gdouble tanw;
	gdouble tanr;
	gdouble para1,para2;
	gdouble vx1,vy1,vz1,vx2,vy2,vz2;
	gdouble desirex,desirey,desirez;
	gdouble min_angle1 ;
	gdouble min_angle2 ;
	gdouble refract_x;
	gdouble refract_y;
	gdouble tempR;
    gdouble len1;
	gdouble len2;
	gdouble len3;
	// variable for search method  // 
    gdouble SearchLength , SearchPoint;
    gdouble TempLength;
    gdouble TempResult;
    gdouble sina;
    gdouble tana;    
    gdouble sinb;
    gdouble tanb;     
    gdouble sinTmp;
    gdouble cosTmp;
    gdouble tanTmp;
    gdouble disTmp;     
    gdouble xxx;
    gdouble yyy;
    gint i, j; 
    int count;
	// variable for refract point
    gdouble aa1,bb1;
	gdouble aa2,bb2;
	//  time delay calculation
	gdouble dis1;
	gdouble dis2;
	gdouble timemax ;

	if(ElementStop > ElementColumn)  return ;
    z0 = Intervalx*ElementStart*sin(wedgeangle);
	x0 = Intervalx*ElementStart*cos(wedgeangle);
	
	gdouble *time = malloc(ElementColumn * sizeof(gdouble));
	
	// kill the impossible condition
	if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
	
	if(p->probe_p->transmi_trans_longi==0)
    {   
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
        c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
    }                                           
    else                                 
    {
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
        c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
    }

	// refract coefficient
	k1 =c1/c2 ; 	  
	// center probe element    (x0,y0,z0)			 
	z0 = -(z0 + h0 + Intervalx*(SelectColumn - 1)*sin(wedgeangle)/2);
	x0 = x0 + wg_pri_axis_reference + wg_pri_elem_offset_fir + Intervalx*(SelectColumn-1)*cos(wedgeangle)/2;
    if(roofangle<0)
		 {wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;a1=-a1;}
	y0 = -wg_sec_axis_reference - wg_sec_elem_offset_fir;
    // get focus point coordinate 
    // desirex desirey desirez : ÈëÉäµã×ø±ê          
    if(roofangle == 0)
    {
          TempLength = FocusDepth*tan(a1) ;
		  p->focus_x[p->k] =  x0+TempLength ;
		  TempLength =  fabs(z0)*tan(asin(sin(a1)*k1));
		  p->focus_x[p->k] += TempLength ;
		  p->focus_y[p->k] =  y0 ;
          p->focus_z[p->k] =  FocusDepth;
          xP = p->focus_x[p->k];
          yP = p->focus_y[p->k];
          zP = p->focus_z[p->k];
    }
	else
	{
	    if(wedgeangle==0)
        {
            desirex = x0 ;
	   		desirey = y0-fabs(z0)*tan(roofangle);
	   		desirez = 0;
    	}
		else
		{
	    		tanw = -tan(wedgeangle);
	            tanr = tan(roofangle)  ;
	            vx1  = tanw*tanr       ;
	            vy1  = -(1+tanw*tanw)  ;
	            vz1  = -tanr           ;
		        // (x-para1)/vx2 = y-para2   
	     		//¹ýÌ½Í·ÓëÐ¨¿éÃæ´¹Ö±ÃæÓëZ=0ÃæµÄ½»Ïß·½³Ì
	    		para1 = x0             ;
	    		para2 = y0 + z0*vz1/vy1;
	    		vx2 = -vy1/vx1         ;
	    		//ÖÐÐÄÌ½Í·Óë½»ÏßµÄ´¹Ö±µã
	    		desirex = (vx2*x0+y0+para1/vx2 - para2)/(vx2+1/vx2);
	    		desirey = para2 + (desirex - para1)/vx2 ;
	    		desirez = 0 ;
		}
    		// Çó×îÐ¡ÈëÉä½Ç
		min_angle1 = atan(sqrt((desirex-x0)*(desirex-x0)+(desirey-y0)*(desirey-y0))/fabs(z0));
    	min_angle2 = sin(min_angle1)/k1;
    	if(min_angle2>=1)
    	{
            // Èç¹û×îÐ¡ÈëÉä½Ç·¢ÉúÈ«·´ÉäÈ¡½¹µãÎªÖÐÐÄÌ½Í·×ø±ê
        	xP = x0;
        	yP = y0;
        	a1 = 0 ;
    	}
		else 
		{
	      if(asin(min_angle2)>=fabs(a1))
	      {
	          //Èç¹û ×îÐ¡ÕÛÉä½Ç´óÓÚ¸ø¶¨ÕÛÉä½Ç,È¡´¹Ö±µã×÷ÎªÖÐÐÄÌ½Í·ÈëÉäµã 
	          refract_x = desirex;
		      refract_y = desirey;
		      a1 = min_angle2 ;
	      }
          else
          {
              // ¼ÆËãÕý³£Çé¿öÏÂ½¹µãµÄ×ø±ê
              //refract point ÕÛÉäµã×ø±ê 
              min_angle2 = asin(sin(a1)*k1);
              tempR = z0*tan(min_angle2);
		      TempLength = sqrt(tempR*tempR - (desirex-x0)*(desirex-x0)-(desirey-y0)*(desirey-y0));
		      if(a1>=0)
		      {
	                 refract_x = desirex-TempLength*vx2/sqrt(1+vx2*vx2);
			         refract_y = desirey-TempLength/sqrt(1+vx2*vx2);
              }
              else
              {
	                 refract_x = desirex+TempLength*vx2/sqrt(1+vx2*vx2);
			         refract_y = desirey+TempLength/sqrt(1+vx2*vx2);
              }
          }		  
          TempLength = FocusDepth*tan(a1) ;
		  len1 = refract_x - x0;
		  len2 = refract_y - y0;
		  len3 = sqrt(len1*len1+len2*len2);
          if(a1>=0)
          {
                xP = refract_x+TempLength*len1/len3;
		        yP = refract_y+TempLength*len2/len3;
          }
          else
          {
                xP = refract_x-TempLength*len1/len3;
		        yP = refract_y-TempLength*len2/len3;
          }
          }
          p->focus_x[p->k] =  xP ;
          p->focus_y[p->k] =  yP ;
          p->focus_z[p->k] =  FocusDepth;
	 }
	 //g_print("Focus x=%f,y=%f,z=%f\n",p->focus_x[p->k],p->focus_y[p->k],p->focus_z[p->k]);
     //first element location 
     p->probe_x[p->k][0] =   wg_pri_axis_reference + wg_pri_elem_offset_fir ;
     p->probe_y[p->k][0] =   -wg_sec_axis_reference - wg_sec_elem_offset_fir;
     p->probe_z[p->k][0] =   -h0  ;
	  
     for(i = ElementStart; i< ElementStop; i++)
     {
            //  get each element coordinates
            zTemp = p->probe_z[p->k][0]  - i*Intervalx*sin(wedgeangle);
            xTemp = p->probe_x[p->k][0]  + Intervalx*cos(wedgeangle)*i;
            yTemp = p->probe_y[p->k][0];
            p->probe_x[p->k][i] = xTemp;
            p->probe_y[p->k][i] = yTemp;
            p->probe_z[p->k][i] = zTemp;   

			if(zTemp>=0)
            {    // kill special situation when probe under the detect surface
                 p->horizontal_x[p->k][i] = xTemp  ;
                 p->horizontal_y[p->k][i] = yTemp  ;
                 p->horizontal_z[p->k][i] = zTemp  ; 
				 continue ;
            }			
            xxx = xP-xTemp ;
            yyy = yP-yTemp ;
            if(a1 != 0&&roofangle!=0)
            {
                   // Ö±Ïß1 :¹ýÌ½Í·ÓëWEDGE´¹Ö±ÃæÓëZ=0 µÄ½»Ïß
                   // Ö±Ïß2 :Ì½Í·ºÍ½¹µãÁ¬ÏßÔÚZ=0ÃæÉÏµÄÍ¶Ó°
                   // Ì½Í·µÄÈëÉäµãÎªÖ±Ïß1ºÍÖ±Ïß2µÄ½»µã
                   if(xxx==0)
                   {
                       p->horizontal_x[p->k][i] = xTemp  ;
                       if(wedgeangle != 0) 
                       p->horizontal_y[p->k][i] = (xTemp-para1)/vx2+para2;
                       else 
                       p->horizontal_y[p->k][i] = desirey ;
                       p->horizontal_z[p->k][i] = 0 ; 					   
                   }
			       else
				   {
				       if(wedgeangle==0)
				       {
						   p->horizontal_y[p->k][i] = y0-fabs(z0)*tan(roofangle)			   ;
						   p->horizontal_x[p->k][i] = xP+(p->horizontal_y[p->k][i]-yP)*(xP-xTemp)/(yP-yTemp);
                           p->horizontal_z[p->k][i] = 0                                      ;
				       }
				       else
					   {
					       aa1 = yyy/xxx ;
				           aa2 = 1/vx2   ;
					       p->horizontal_x[p->k][i] = (aa2*para1-aa1*xP+yP-para2)/(aa2-aa1)  ;
                           p->horizontal_y[p->k][i] = (p->horizontal_x[p->k][i]-para1)/vx2+para2   ;
                           p->horizontal_z[p->k][i] = 0                                      ;
				       }
	
			       }				  
            }
            else
            {
                   //A1 ==0 Ê±°´Ò»Î¬ROOF½ÇµÈÓÚ0µÄÇé¿ö×÷ËÑË÷
                   TempLength = sqrt(xxx*xxx+yyy*yyy);
                   SearchLength = TempLength/2 ;
 
                   if(TempLength==0||zTemp==0)
                   {
                       p->horizontal_x[p->k][i] = xTemp  ;
                       p->horizontal_y[p->k][i] = yTemp  ;
                       p->horizontal_z[p->k][i] = 0      ;     
                       continue ;     
                   }                      
                   // do search in temporary coordinate
                   SearchPoint = 0 ;
                   TempResult =  0 ;
                   count = 0;                          
                   do
                   {
                       SearchPoint += SearchLength ;      
                       //printf("search point :%f \n",SearchPoint);
                       tana = SearchPoint/zTemp;
                       sina = sqrt(tana*tana/(1+tana*tana));
                       sinb = sina/k1;
					   
                       if(sinb>=1)  
                       {
                           SearchLength = -fabs(SearchLength)/2 ;                   
                       }
                       else
                       {
                           tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
                           TempResult=SearchPoint+tanb*FocusDepth ;
                           if(TempResult>TempLength)   SearchLength = -fabs(SearchLength)/2 ;
                           if(TempResult<TempLength)   SearchLength =  fabs(SearchLength)/2 ;                       
                       }                   
                       count++;         
                   }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;      
                 
                 p->horizontal_x[p->k][i] = xTemp + SearchPoint*xxx/TempLength ;
                 p->horizontal_y[p->k][i] = yTemp + SearchPoint*yyy/TempLength ;
                 p->horizontal_z[p->k][i] = 0 ;  	
				 //g_print("No %d x=%f,y=%f,z=%f\n",i,p->horizontal_x[p->k][i],p->horizontal_y[p->k][i],p->horizontal_z[p->k][i]);
            }
     }  
     //calculate the transfer time
     for(i = ElementStart; i< ElementStop ; i++)
     {     
              dis1 = sqrt((p->probe_x[p->k][i]-p->horizontal_x[p->k][i])*(p->probe_x[p->k][i]-p->horizontal_x[p->k][i])
                             +(p->probe_y[p->k][i]-p->horizontal_y[p->k][i])*(p->probe_y[p->k][i]-p->horizontal_y[p->k][i])
                             +(p->probe_z[p->k][i]-p->horizontal_z[p->k][i])*(p->probe_z[p->k][i]-p->horizontal_z[p->k][i]));
              dis2 = sqrt((p->horizontal_x[p->k][i]-p->focus_x[p->k])*(p->horizontal_x[p->k][i]-p->focus_x[p->k])
                            +(p->horizontal_y[p->k][i]-p->focus_y[p->k])*(p->horizontal_y[p->k][i]-p->focus_y[p->k])
                            +(p->horizontal_z[p->k][i]-p->focus_z[p->k])*(p->horizontal_z[p->k][i]-p->focus_z[p->k]));
              time[i] = dis1/c1+dis2/c2;          
     }
     // get the time delay
     timemax = time[0];
     for(i = ElementStart ; i< ElementStop ; i++)
     {
           if(timemax < time[i])  timemax = time[i] ;                   
     } 
     for(i = ElementStart; i< ElementStop ; i++)
     {
   //       g_printf("No.%d,time[%d] = %f,¦¤t=%d\n",i+1,i+1,time[i],(gint)((timemax - time[i])*1000000+0.5));
          p->timedelay[p->k][i] = (gint)((timemax - time[i])*1000000+0.5);     
     }
     p->G_Time[p->k] = timemax;
     free(time);
}

/*
  Name:  flat_2d_roof
  Copyright: Dopplor 
  Author: Sheng Shen
  Date: 17-03-11 13:40
  Description:   Æ½Ãæ¹¤¼þ2D  ¾Û½¹·¨Ôò 
  Input:  data: structure point to wedge probe .... coefficients
        angle1: refract angle
        angle2: skew angle
        depth : focus depth of sonic beam
*/
void flat_2d_roof(gpointer data, gdouble angle1, gdouble angle2, gdouble depth)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
     
     gdouble c1 ;            // wave speed
     gdouble c2 ;
     gdouble k1 ;  
     gdouble h0 =  p->wedge_p->wg_heigh_fir ;                  // first element high
//     gint Row      =  p->element_sel->sec_axis_ape  ;                  // element y direction numble
//     gint Column   = p->element_sel->pri_axis_ape;                  // element x direction numble
//     if((Row*Column) > (p->probe_p->ele_num_pri * p->probe_p->ele_num_sec))
//            return;
     int PriElementStart = p->element_sel->primary_axis_s -1  ;
     int PriElementNum   = p->probe_p->ele_num_pri            ;
     int SecElementStart = p->element_sel->seconary_axis_s -1 ;
	 int SecElementNum   = p->probe_p->ele_num_sec            ;
	 int PriElementSelect= p->element_sel->pri_axis_ape       ;
	 int SecElementSelect= p->element_sel->sec_axis_ape       ;
     int PriElementStop  = PriElementStart +  PriElementSelect;
	 int SecElementStop  = SecElementStart +  SecElementSelect;

     gdouble Intervaly = p->probe_p->sec_axis_pitch ;          // y direction interval
     gdouble Intervalx = p->probe_p->pri_axis_pitch ;          // x direction interval distance
     gdouble pri_ele_size = p->probe_p->pri_ele_size ;
     gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
     gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
     gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
     gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
     gdouble  a1 = angle1*PI/180;                              // refract angle
     gdouble  a2 = angle2*PI/180;                              // deflect angle

     gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180   ; // roofangle   y-z platform
     gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ; // wedgeangle  x-z platform     
     gdouble  FocusDepth = depth;                              //  true focus depth
     
     gdouble xTemp, yTemp, zTemp ;
     gdouble x0,y0,z0;                                         // element center coordinate
     gdouble xP, yP, zP;                                       // focus point coordinate
     //  element offset in each direction
     gdouble x;
     gdouble y;
     gdouble z;
     gdouble d;
     gdouble s_x;
     gdouble s_y;
     gdouble s_zy;
     gdouble s_zx;     
     // variable for search method
     gdouble SearchLength , SearchPoint;
     gdouble TempLength;
     gdouble TempResult;
     gdouble sina;
     gdouble tana;    
     gdouble sinb;
     gdouble tanb;
     
     gdouble sinTmp;
     gdouble cosTmp;
     gdouble tanTmp;
     gdouble disTmp;
     
     gdouble xxx;
     gdouble yyy;
     gint i, j; 
     int count;
     
     gdouble dis1;
     gdouble dis2;
     gdouble timemax ;

	 if(PriElementStop > PriElementNum )  return ;
	 if(SecElementStop > SecElementNum )  return ;	 
     gdouble *time = malloc(PriElementNum*SecElementNum*sizeof(gdouble));
     
     // kill the impossible condition
	 if(p->probe_p->D1_D2 == 0) {SecElementNum = 1;  SecElementStart = 0; SecElementStop = 1;}
     if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
 
     if(p->probe_p->transmi_trans_longi==0)
     {   
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
        c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
     }                                           
     else                                 
     {
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
        c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
     }
     // refract coefficient
     k1 =c1/c2 ;      

     // element location offset calculate
     // ÔÚROOF½Ç²»µÈÓÚ0Ê±,ÔÚ´¹Ö±ÓÚWEDGE ½ÇÉÏ±ß·½ÏòÉÏÃ¿×ßÒ»¶Î¾àÀë
     // ¶ÔÓ¦µÄ X Y Z Èý¸ö·½ÏòÉÏ¶¼»áÓÐÒ»¸öÎ»ÖÃ±ä»¯SX SY SZ
     if((wedgeangle != 0) && (roofangle != 0))
     {
          x = 1;
          y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
          z = y*tan(roofangle) ;
          d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
          s_x  = -Intervaly/d    ;
          s_y  = -Intervaly*y/d   ;
          s_zy  = -Intervaly*(z-tan(wedgeangle))/d   ;          
     }
     else
     {   
          s_y = -Intervaly*cos(roofangle);
          s_x = 0 ;
          s_zy = -Intervaly*sin(roofangle);
     }     
	 //calc offset generated by element selection

	 z0 = SecElementStart*s_zy - PriElementStart*Intervalx*sin(wedgeangle);
	 x0 = Intervalx*cos(wedgeangle)*PriElementStart + SecElementStart*s_x ;
	 y0 = s_y*SecElementStart   ;

     // center probe element    (x0,y0,z0)            
     z0 = -(z0 + h0 + Intervalx*(PriElementSelect - 1)*sin(wedgeangle)/2 - s_zy*(SecElementSelect - 1)/2);
     x0 = x0 + wg_pri_axis_reference + wg_pri_elem_offset_fir + Intervalx*(PriElementSelect - 1)*cos(wedgeangle)/2 + (SecElementSelect - 1)*s_x/2 ;
     if(roofangle<0)
		 wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;
	 y0 = y0 -wg_sec_axis_reference - wg_sec_elem_offset_fir + s_y*(SecElementSelect - 1)/2 ;   
     // get focus point coordinate 
     if(a1<0)
     {  
        a1 = -a1 ;
        if(a2>=0)  a2 = a2-PI ;
		else       a2 = PI+a2 ;
     }// Í¨¹ý´Ë´¦±ä»»Ê¹Ö§³Ö A1 (-90,90) A2(-180,180)          
     yTemp = sqrt(sin(a2)*sin(a2)*FocusDepth*FocusDepth*tan(a1)*tan(a1))  ;         
     if(a2==PI/2||a2==-PI/2)
        xTemp = 0;
     else
        xTemp = sqrt(tan(a1)*tan(a1)*FocusDepth*FocusDepth - yTemp*yTemp) ;   
	 if(a2 < 0)   yTemp= -yTemp ;
     if(xTemp==0)
     {
         sinTmp = sqrt(tan(a1)*tan(a1)/(1+tan(a1)*tan(a1)));
         sinTmp = sinTmp*k1;
         tanTmp = sqrt(sinTmp*sinTmp/(1-sinTmp*sinTmp));   
         if(yTemp == 0)
         {          
           xP =  x0 ;
           yP =  y0 ;
           zP =  FocusDepth;
         }
         else
         {
           disTmp = fabs(z0)*tanTmp;
           xP =  x0 ;
           yP =  y0  - yTemp*(sqrt(xTemp*xTemp+yTemp*yTemp)+disTmp)/sqrt(xTemp*xTemp+yTemp*yTemp);
           zP =  FocusDepth;
         }
     }
     else
     {          
         if( (a2 > PI/2) || (a2 < -PI/2))  xTemp = -xTemp ;
         //            
         sinTmp = sqrt(tan(a1)*tan(a1)/(1+tan(a1)*tan(a1)));
         sinTmp = sinTmp*k1;
         tanTmp = sqrt(sinTmp*sinTmp/(1-sinTmp*sinTmp));
         //
         if(yTemp == 0)
         {
           if(xTemp>=0)
               xP =  x0 + xTemp + fabs(z0)*tanTmp;
           else
               xP =  x0 + xTemp +  z0*tanTmp     ;
           yP =  y0 ;
        }
        else
        {
           disTmp = fabs(z0)*tanTmp;
           xP =  x0  + xTemp*(sqrt(xTemp*xTemp+yTemp*yTemp)+disTmp)/sqrt(xTemp*xTemp+yTemp*yTemp) ;
           yP =  y0  - yTemp*(sqrt(xTemp*xTemp+yTemp*yTemp)+disTmp)/sqrt(xTemp*xTemp+yTemp*yTemp) ;
           zP =  FocusDepth;
        }
     }     
     p->focus_x[p->k] =  xP ;
     p->focus_y[p->k] =  yP ;
     p->focus_z[p->k] =  FocusDepth;        
     //first element location 
     p->probe_x[p->k][0] =   wg_pri_axis_reference + wg_pri_elem_offset_fir ;
     p->probe_y[p->k][0] =   -wg_sec_axis_reference - wg_sec_elem_offset_fir;
     p->probe_z[p->k][0] =   -h0  ;                 
     for(i = PriElementStart; i< PriElementStop; i++)
     {
           for(j = SecElementStart; j< SecElementStop; j++)
           {
                 //  get elements' coordinates
                 zTemp = p->probe_z[p->k][0] + j*s_zy - i*Intervalx*sin(wedgeangle);
                 xTemp = p->probe_x[p->k][0] + Intervalx*cos(wedgeangle)*i + j*s_x ;
                 yTemp = p->probe_y[p->k][0] + s_y*j   ;
                 p->probe_x[p->k][i*SecElementNum+j] = xTemp;
                 p->probe_y[p->k][i*SecElementNum+j] = yTemp;
                 p->probe_z[p->k][i*SecElementNum+j] = zTemp;
                                  
                 xxx = xP-xTemp ;
                 yyy = yP-yTemp ;
                 TempLength = sqrt(xxx*xxx+yyy*yyy);
                 SearchLength = TempLength/2 ;
                 
                 if(TempLength==0||zTemp==0)
                 {
                       p->horizontal_x[p->k][i*SecElementNum+j] = xTemp  ;
                       p->horizontal_y[p->k][i*SecElementNum+j] = yTemp  ;
                       p->horizontal_z[p->k][i*SecElementNum+j] = 0 ;     
                       continue ;     
                 }                      
                 // do search in temporary coordinate
                 SearchPoint = 0 ;
                 TempResult =  0 ;
                 count = 0;                
				 // ÔÚÒÔÌ½Í·×ø±êÎªX Y ·½ÏòÔ­µã,Ì½Í·µ½½¹µã·½ÏòÎªX·½ÏòµÄ×ø±êÉÏ
				 // ËÑË÷ºÏÊÊµÄÈëÉäµã
                 do
                 {
                       SearchPoint += SearchLength ;      
                       //printf("search point :%f \n",SearchPoint);
                       tana = SearchPoint/zTemp;
                       sina = sqrt(tana*tana/(1+tana*tana));
                       sinb = sina/k1;
					   
                       if(sinb>=1)  
                       {
                           SearchLength = -fabs(SearchLength)/2 ;                   
                       }
                       else
                       {
                           tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
                           TempResult=SearchPoint+tanb*FocusDepth ;
                           if(TempResult>TempLength)   SearchLength = -fabs(SearchLength)/2 ;
                           if(TempResult<TempLength)   SearchLength =  fabs(SearchLength)/2 ;                       
                       }                   
                       count++;         
                 }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;                 
                 // translate the search result  into common coordiniate
                 p->horizontal_x[p->k][i*SecElementNum+j] = xTemp + SearchPoint*xxx/TempLength ;
                 p->horizontal_y[p->k][i*SecElementNum+j] = yTemp + SearchPoint*yyy/TempLength ;
                 p->horizontal_z[p->k][i*SecElementNum+j] = 0 ;
           }
     }  
     //calculate the transfer time
     for(i=PriElementStart; i< PriElementStop ; i++)
     {
         for(j = SecElementStart; j< SecElementStop; j++)
         {
              dis1 = sqrt((p->probe_x[p->k][i*SecElementNum+j]-p->horizontal_x[p->k][i*SecElementNum+j])*(p->probe_x[p->k][i*SecElementNum+j]-p->horizontal_x[p->k][i*SecElementNum+j])
                             +(p->probe_y[p->k][i*SecElementNum+j]-p->horizontal_y[p->k][i*SecElementNum+j])*(p->probe_y[p->k][i*SecElementNum+j]-p->horizontal_y[p->k][i*SecElementNum+j])
                            +(p->probe_z[p->k][i*SecElementNum+j]-p->horizontal_z[p->k][i*SecElementNum+j])*(p->probe_z[p->k][i*SecElementNum+j]-p->horizontal_z[p->k][i*SecElementNum+j]));
              dis2 = sqrt((p->horizontal_x[p->k][i*SecElementNum+j]-p->focus_x[p->k])*(p->horizontal_x[p->k][i*SecElementNum+j]-p->focus_x[p->k])
                            +(p->horizontal_y[p->k][i*SecElementNum+j]-p->focus_y[p->k])*(p->horizontal_y[p->k][i*SecElementNum+j]-p->focus_y[p->k])
                            +(p->horizontal_z[p->k][i*SecElementNum+j]-p->focus_z[p->k])*(p->horizontal_z[p->k][i*SecElementNum+j]-p->focus_z[p->k]));
              time[i*SecElementNum+j] = dis1/c1+dis2/c2;
         }
     }
     // get the time delay
     timemax = time[PriElementStart*SecElementNum + SecElementStart]; 

     for(i=PriElementStart; i< PriElementStop ; i++)
     {
         for(j = SecElementStart; j< SecElementStop; j++)
         {
               if(timemax < time[i*SecElementNum + j ])  timemax = time[i*SecElementNum + j ] ;
         }
     }

     g_print("***********\n") ;
     g_print("    x1 x2 x3\n")  ;
     g_print("y1  0  3  6  \n") ;
     g_print("y2  1  4  7  \n") ;
     g_print("y3  2  5  8  \n") ;
     g_print("***********\n");      
     
	 for(i=PriElementStart; i< PriElementStop ; i++)
     {
         for(j = SecElementStart; j< SecElementStop; j++)
         {
              g_printf("No.[%d][%d],time = %f,¦¤t=%d\n",i+1,j+1,time[i*SecElementNum + j ],(gint)((timemax - time[i*SecElementNum + j ])*1000000+0.5));
              p->timedelay[p->k][i*SecElementNum + j] = (gint)((timemax - time[i*SecElementNum + j ])*1000000+0.5)                                  ;
         }
     }
     p->G_Time[p->k] = timemax;
     free(time);
}


/*
  Name:  flat_1d_roof_pr
  Copyright: Dopplor 
  Author: Sheng Shen
  Date: 17-03-11 13:40
  Description:   Æ½Ãæ¹¤¼þ1D µÄË«¾§ ¾Û½¹·¨Ôò 
  Input:  data: structure point to wedge probe .... coefficients
        angle1: refract angle
        depth : focus depth of sonic beam
*/

void flat_1d_pr(gpointer data, gdouble angle1, gdouble depth)
{
	DRAW_UI_P p = (DRAW_UI_P) data ;
	
	gdouble c1 ;			// wave speed
	gdouble c2 ;
	gdouble k1 ;  
	gdouble h0 =  p->wedge_p->wg_heigh_fir ;				  // first element high
	gint Column   = p->element_sel->pri_axis_ape;				  // element x direction numble
    if((Column) > (p->probe_p->ele_num_pri))
                  return;
	gdouble Intervalx = p->probe_p->pri_axis_pitch ;		  // x direction interval distance
	gdouble pri_ele_size = p->probe_p->pri_ele_size ;
	gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
	gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	gdouble  a1 = angle1*PI/180;							  // refract angle	
	gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180	; // roofangle	 y-z platform
	gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180	; // wedgeangle  x-z platform	  
    gdouble separation = p->wedge_r->wg_separation ;

	
	gdouble  FocusDepth = depth;							  //  true focus depth
	gdouble xTemp, yTemp, zTemp ;
	gdouble x0,y0,z0;										  // element center coordinate
	gdouble xP, yP, zP; 									  // focus point coordinate
	// get focus point coordinate		   
	gdouble tanw;
	gdouble tanr;
	gdouble para1,para2;
	gdouble vx1,vy1,vz1,vx2,vy2,vz2;
	gdouble desirex,desirey,desirez;
	gdouble min_angle1 ;
	gdouble min_angle2 ;
	gdouble refract_x;
	gdouble refract_y;
	gdouble tempR;
    gdouble len1;
	gdouble len2;
	gdouble len3;
	// variable for search method  // 
    gdouble SearchLength , SearchPoint;
    gdouble TempLength;
    gdouble TempResult;
    gdouble sina;
    gdouble tana;    
    gdouble sinb;
    gdouble tanb;     
    gdouble sinTmp;
    gdouble cosTmp;
    gdouble tanTmp;
    gdouble disTmp;     
    gdouble xxx;
    gdouble yyy;
    gint i, j; 
    int count;
	// variable for refract point
    gdouble aa1,bb1;
	gdouble aa2,bb2;
	//  time delay calculation
	gdouble dis1;
	gdouble dis2;
	gdouble timemax ;
	gdouble *time = malloc(Column*sizeof(gdouble));
	
	// kill the impossible condition
	if(Column<=0) return ;
	if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
	
	if(p->probe_p->transmi_trans_longi==0)
    {   
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
        c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
    }                                           
    else                                 
    {
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
        c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
    }

	// refract coefficient
	k1 =c1/c2 ; 	  
	// center probe element    (x0,y0,z0)			 
	z0 = -(h0 + Intervalx*(Column - 1)*sin(wedgeangle)/2);
	x0 = wg_pri_axis_reference + wg_pri_elem_offset_fir + Intervalx*(Column-1)*cos(wedgeangle)/2;
    if(roofangle<0)
		 {wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;a1=-a1;}
	y0 = -wg_sec_axis_reference - wg_sec_elem_offset_fir;
    // get focus point coordinate 
    // desirex desirey desirez : ÈëÉäµã×ø±ê          
    if(roofangle == 0)
    {
          TempLength = FocusDepth*tan(a1) ;
		  p->focus_x[p->k] =  x0+TempLength ;
		  TempLength =  fabs(z0)*tan(asin(a1*k1));
		  p->focus_x[p->k] += TempLength ;
		  p->focus_y[p->k] =  y0 ;
          p->focus_z[p->k] =  FocusDepth;
          xP = p->focus_x[p->k];
          yP = p->focus_y[p->k];
          zP = p->focus_z[p->k];
    }
	else
	{
	    if(wedgeangle==0)
        {
            desirex = x0 ;
	   		desirey = y0-fabs(z0)*tan(roofangle);
	   		desirez = 0;
    	}
		else
		{
	    		tanw = -tan(wedgeangle);
	            tanr = tan(roofangle)  ;
	            vx1  = tanw*tanr       ;
	            vy1  = -(1+tanw*tanw)  ;
	            vz1  = -tanr           ;
		        // (x-para1)/vx2 = y-para2   
	     		//¹ýÌ½Í·ÓëÐ¨¿éÃæ´¹Ö±ÃæÓëZ=0ÃæµÄ½»Ïß·½³Ì
	    		para1 = x0             ;
	    		para2 = y0 + z0*vz1/vy1;
	    		vx2 = -vy1/vx1         ;
	    		//ÖÐÐÄÌ½Í·Óë½»ÏßµÄ´¹Ö±µã
	    		desirex = (vx2*x0+y0+para1/vx2 - para2)/(vx2+1/vx2);
	    		desirey = para2 + (desirex - para1)/vx2 ;
	    		desirez = 0 ;
		}
    		// Çó×îÐ¡ÈëÉä½Ç
		min_angle1 = atan(sqrt((desirex-x0)*(desirex-x0)+(desirey-y0)*(desirey-y0))/fabs(z0));
    	min_angle2 = sin(min_angle1)/k1;
    	if(min_angle2>=1)
    	{
        // Èç¹û×îÐ¡ÈëÉä½Ç·¢ÉúÈ«·´ÉäÈ¡½¹µãÎªÖÐÐÄÌ½Í·×ø±ê
        	xP = x0;
        	yP = y0;
        	a1 = 0 ;
    	}
		else 
		{
	      if(asin(min_angle2)>=fabs(a1))
	      {
	          //Èç¹û ×îÐ¡ÕÛÉä½Ç´óÓÚ¸ø¶¨ÕÛÉä½Ç,È¡´¹Ö±µã×÷ÎªÖÐÐÄÌ½Í·ÈëÉäµã 
	          refract_x = desirex;
		      refract_y = desirey;
		      a1 = min_angle2 ;
	      }
          else
          {
              // ¼ÆËãÕý³£Çé¿öÏÂ½¹µãµÄ×ø±ê
              //refract point ÕÛÉäµã×ø±ê 
              min_angle2 = asin(sin(a1)*k1);
              tempR = z0*tan(min_angle2);
		      TempLength = sqrt(tempR*tempR - (desirex-x0)*(desirex-x0)-(desirey-y0)*(desirey-y0));
		      if(a1>=0)
		      {
                 refract_x = desirex-TempLength*vx2/sqrt(1+vx2*vx2);
		         refract_y = desirey-TempLength/sqrt(1+vx2*vx2);
              }
              else
              {
                 refract_x = desirex+TempLength*vx2/sqrt(1+vx2*vx2);
		         refract_y = desirey+TempLength/sqrt(1+vx2*vx2);
              }
          }		  
          TempLength = FocusDepth*tan(a1) ;
		  len1 = refract_x - x0;
		  len2 = refract_y - y0;
		  len3 = sqrt(len1*len1+len2*len2);
          if(a1>=0)
          {
                xP = refract_x+TempLength*len1/len3;
		        yP = refract_y+TempLength*len2/len3;
          }
          else
          {
                xP = refract_x-TempLength*len1/len3;
		        yP = refract_y-TempLength*len2/len3;
          }
          }
          p->focus_x[p->k] =  xP ;
          p->focus_y[p->k] =  yP ;
          p->focus_z[p->k] =  FocusDepth;
	 }
     //first element location 
     p->probe_x[p->k][0] =   wg_pri_axis_reference + wg_pri_elem_offset_fir ;
     p->probe_y[p->k][0] =   -wg_sec_axis_reference - wg_sec_elem_offset_fir;
     p->probe_z[p->k][0] =   -h0  ;
	  
     for(i = 0; i< Column; i++)
     {
            //  get each element coordinates
            zTemp = p->probe_z[p->k][0]  - i*Intervalx*sin(wedgeangle);
            xTemp = p->probe_x[p->k][0] +  Intervalx*cos(wedgeangle)*i;
            yTemp = p->probe_y[p->k][0];
            p->probe_x[p->k][i] = xTemp;
            p->probe_y[p->k][i] = yTemp;
            p->probe_z[p->k][i] = zTemp;   

			if(zTemp>=0)
            {    // kill special situation when probe under the detect surface
                 p->horizontal_x[p->k][i] = xTemp  ;
                 p->horizontal_y[p->k][i] = yTemp  ;
                 p->horizontal_z[p->k][i] = zTemp  ; 
				 continue ;
            }			
            xxx = xP-xTemp ;
            yyy = yP-yTemp ;
            if(a1 != 0&&roofangle!=0)
            {
                   // Ö±Ïß1 :¹ýÌ½Í·ÓëWEDGE´¹Ö±ÃæÓëZ=0 µÄ½»Ïß
                   // Ö±Ïß2 :Ì½Í·ºÍ½¹µãÁ¬ÏßÔÚZ=0ÃæÉÏµÄÍ¶Ó°
                   // Ì½Í·µÄÈëÉäµãÎªÖ±Ïß1ºÍÖ±Ïß2µÄ½»µã
                   if(xxx==0)
                   {
                       p->horizontal_x[p->k][i] = xTemp  ;
                       if(wedgeangle != 0) 
                       p->horizontal_y[p->k][i] = (xTemp-para1)/vx2+para2;
                       else 
                       p->horizontal_y[p->k][i] = desirey ;
                       p->horizontal_z[p->k][i] = 0 ; 					   
                   }
			       else
				   {
				       if(wedgeangle==0)
				       {
						   p->horizontal_y[p->k][i] = y0-fabs(z0)*tan(roofangle)			   ;
						   p->horizontal_x[p->k][i] = xP+(p->horizontal_y[p->k][i]-yP)*(xP-xTemp)/(yP-yTemp);
                           p->horizontal_z[p->k][i] = 0                                      ;
				       }
				       else
					   {
					       aa1 = yyy/xxx ;
				           aa2 = 1/vx2   ;
					       p->horizontal_x[p->k][i] = (aa2*para1-aa1*xP+yP-para2)/(aa2-aa1)  ;
                           p->horizontal_y[p->k][i] = (p->horizontal_x[p->k][i]-para1)/vx2+para2   ;
                           p->horizontal_z[p->k][i] = 0                                      ;
				       }
	
			       }				  
            }
            else
            {
                   //A1 ==0 Ê±°´Ò»Î¬ROOF½ÇµÈÓÚ0µÄÇé¿ö×÷ËÑË÷
                   TempLength = sqrt(xxx*xxx+yyy*yyy);
                   SearchLength = TempLength/2 ;
 
                   if(TempLength==0||zTemp==0)
                   {
                       p->horizontal_x[p->k][i] = xTemp  ;
                       p->horizontal_y[p->k][i] = yTemp  ;
                       p->horizontal_z[p->k][i] = 0      ;     
                       continue ;     
                   }                      
                   // do search in temporary coordinate
                   SearchPoint = 0 ;
                   TempResult =  0 ;
                   count = 0;                          
                   do
                   {
                       SearchPoint += SearchLength ;      
                       //printf("search point :%f \n",SearchPoint);
                       tana = SearchPoint/zTemp;
                       sina = sqrt(tana*tana/(1+tana*tana));
                       sinb = sina/k1;
					   
                       if(sinb>=1)  
                       {
                           SearchLength = -fabs(SearchLength)/2 ;                   
                       }
                       else
                       {
                           tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
                           TempResult=SearchPoint+tanb*FocusDepth ;
                           if(TempResult>TempLength)   SearchLength = -fabs(SearchLength)/2 ;
                           if(TempResult<TempLength)   SearchLength =  fabs(SearchLength)/2 ;                       
                       }                   
                       count++;         
                   }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;      
                 
                 p->horizontal_x[p->k][i] = xTemp + SearchPoint*xxx/TempLength ;
                 p->horizontal_y[p->k][i] = yTemp + SearchPoint*yyy/TempLength ;
                 p->horizontal_z[p->k][i] = 0 ;  	
            }
     }  
     //calculate the transfer time
     for(i=0;i<Column;i++)
     {     
              dis1 = sqrt((p->probe_x[p->k][i]-p->horizontal_x[p->k][i])*(p->probe_x[p->k][i]-p->horizontal_x[p->k][i])
                             +(p->probe_y[p->k][i]-p->horizontal_y[p->k][i])*(p->probe_y[p->k][i]-p->horizontal_y[p->k][i])
                             +(p->probe_z[p->k][i]-p->horizontal_z[p->k][i])*(p->probe_z[p->k][i]-p->horizontal_z[p->k][i]));
              dis2 = sqrt((p->horizontal_x[p->k][i]-p->focus_x[p->k])*(p->horizontal_x[p->k][i]-p->focus_x[p->k])
                            +(p->horizontal_y[p->k][i]-p->focus_y[p->k])*(p->horizontal_y[p->k][i]-p->focus_y[p->k])
                            +(p->horizontal_z[p->k][i]-p->focus_z[p->k])*(p->horizontal_z[p->k][i]-p->focus_z[p->k]));
              time[i] = dis1/c1+dis2/c2;          
     }
     // get the time delay
     timemax = time[0];
     for(i=0;i<Column;i++)
     {
           if(timemax < time[i])  timemax = time[i] ;                   
     } 
     g_printf("\nTransmitte\n");
     for(i = 0 ;i<Column ; i++)
     {
          
          g_printf("No.%d,time[%d] = %f,¦¤t=%d\n",i+1,i+1,time[i],(gint)((timemax - time[i])*1000000+0.5));
          p->timedelay[p->k][i] = (gint)((timemax - time[i])*1000000+0.5);
     }

	h0 =  p->wedge_r->wg_heigh_fir ;				  // first element high
	Column   = p->element_sel->pri_axis_ape;				  // element x direction numble
    if( Column > p->probe_p->ele_num_pri )
                  return;
	Intervalx = p->probe_p->pri_axis_pitch ;		  // x direction interval distance
	pri_ele_size = p->probe_p->pri_ele_size ;
	wg_pri_axis_reference  = p->wedge_r->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	wg_sec_axis_reference  = p->wedge_r->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
	wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	roofangle = p->wedge_r->wg_roof_angle*PI/180	; // roofangle	 y-z platform
	wedgeangle= p->wedge_r->wg_wedge_angle*PI/180	; // wedgeangle  x-z platform	  
    a1 = angle1*PI/180;
	z0 = -(h0 + Intervalx*(Column - 1)*sin(wedgeangle)/2);
	x0 = wg_pri_axis_reference + wg_pri_elem_offset_fir + Intervalx*(Column-1)*cos(wedgeangle)/2;
    if(roofangle<0)
		 {wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir; a1 = -a1;}
	
	y0 = y0-separation ;
    // get focus point coordinate 
    // desirex desirey desirez : ÈëÉäµã×ø±ê          
    if(roofangle == 0)
    {
          TempLength = FocusDepth*tan(a1) ;
		  p->focus_xr[p->k] =  x0+TempLength ;
		  TempLength =  fabs(z0)*tan(asin(a1*k1));
		  p->focus_xr[p->k] += TempLength ;
		  p->focus_yr[p->k] =  y0 ;
          p->focus_zr[p->k] =  FocusDepth;
          xP = p->focus_xr[p->k];
          yP = p->focus_yr[p->k];
          zP = p->focus_zr[p->k];
    }
	else
	{
	    if(wedgeangle==0)
        {
            desirex = x0 ;
	   		desirey = y0-fabs(z0)*tan(roofangle);
	   		desirez = 0;
    	}
		else
		{
	    		tanw = -tan(wedgeangle);
	            tanr = tan(roofangle)  ;
	            vx1  = tanw*tanr       ;
	            vy1  = -(1+tanw*tanw)  ;
	            vz1  = -tanr           ;
		        // (x-para1)/vx2 = y-para2   
	     		//¹ýÌ½Í·ÓëÐ¨¿éÃæ´¹Ö±ÃæÓëZ=0ÃæµÄ½»Ïß·½³Ì
	    		para1 = x0             ;
	    		para2 = y0 + z0*vz1/vy1;
	    		vx2 = -vy1/vx1         ;
	    		//ÖÐÐÄÌ½Í·Óë½»ÏßµÄ´¹Ö±µã
	    		desirex = (vx2*x0+y0+para1/vx2 - para2)/(vx2+1/vx2);
	    		desirey = para2 + (desirex - para1)/vx2 ;
	    		desirez = 0 ;
		}
    		// Çó×îÐ¡ÈëÉä½Ç
		min_angle1 = atan(sqrt((desirex-x0)*(desirex-x0)+(desirey-y0)*(desirey-y0))/fabs(z0));
    	min_angle2 = sin(min_angle1)/k1;
    	if(min_angle2>=1)
    	{
        // Èç¹û×îÐ¡ÈëÉä½Ç·¢ÉúÈ«·´ÉäÈ¡½¹µãÎªÖÐÐÄÌ½Í·×ø±ê
        	xP = x0;
        	yP = y0;
        	a1 = 0 ;
    	}
		else 
		{
	      if(asin(min_angle2)>=fabs(a1))
	      {
	          //Èç¹û ×îÐ¡ÕÛÉä½Ç´óÓÚ¸ø¶¨ÕÛÉä½Ç,È¡´¹Ö±µã×÷ÎªÖÐÐÄÌ½Í·ÈëÉäµã 
	          refract_x = desirex;
		      refract_y = desirey;
		      a1 = min_angle2 ;
	      }
          else
          {
              // ¼ÆËãÕý³£Çé¿öÏÂ½¹µãµÄ×ø±ê
              //refract point ÕÛÉäµã×ø±ê 
              min_angle2 = asin(sin(a1)*k1);
              tempR = z0*tan(min_angle2);
		      TempLength = sqrt(tempR*tempR - (desirex-x0)*(desirex-x0)-(desirey-y0)*(desirey-y0));
		      if(a1>=0)
		      {
                 refract_x = desirex-TempLength*vx2/sqrt(1+vx2*vx2);
		         refract_y = desirey-TempLength/sqrt(1+vx2*vx2);
              }
              else
              {
                 refract_x = desirex+TempLength*vx2/sqrt(1+vx2*vx2);
		         refract_y = desirey+TempLength/sqrt(1+vx2*vx2);
              }
          }		  
          TempLength = FocusDepth*tan(a1) ;
		  len1 = refract_x - x0;
		  len2 = refract_y - y0;
		  len3 = sqrt(len1*len1+len2*len2);
          if(a1>=0)
          {
                xP = refract_x+TempLength*len1/len3;
		        yP = refract_y+TempLength*len2/len3;
          }
          else
          {
                xP = refract_x-TempLength*len1/len3;
		        yP = refract_y-TempLength*len2/len3;
          }
          }
          p->focus_xr[p->k] =  xP ;
          p->focus_yr[p->k] =  yP ;
          p->focus_zr[p->k] =  FocusDepth;
	 }
     //first element location 
     p->probe_xr[p->k][0] =   wg_pri_axis_reference + wg_pri_elem_offset_fir ;
     p->probe_yr[p->k][0] =   p->probe_y[p->k][0]-separation;
     p->probe_zr[p->k][0] =   -h0  ;
	  
     for(i = 0; i< Column; i++)
     {
            //  get each element coordinates
            zTemp = p->probe_zr[p->k][0]  - i*Intervalx*sin(wedgeangle);
            xTemp = p->probe_xr[p->k][0] +  Intervalx*cos(wedgeangle)*i;
            yTemp = p->probe_yr[p->k][0];
            p->probe_xr[p->k][i] = xTemp;
            p->probe_yr[p->k][i] = yTemp;
            p->probe_zr[p->k][i] = zTemp;   

			if(zTemp>=0)
            {    // kill special situation when probe under the detect surface
                 p->horizontal_xr[p->k][i] = xTemp  ;
                 p->horizontal_yr[p->k][i] = yTemp  ;
                 p->horizontal_zr[p->k][i] = zTemp  ; 
				 continue ;
            }			
            xxx = xP-xTemp ;
            yyy = yP-yTemp ;
            if(a1 != 0&&roofangle!=0)
            {
                   // Ö±Ïß1 :¹ýÌ½Í·ÓëWEDGE´¹Ö±ÃæÓëZ=0 µÄ½»Ïß
                   // Ö±Ïß2 :Ì½Í·ºÍ½¹µãÁ¬ÏßÔÚZ=0ÃæÉÏµÄÍ¶Ó°
                   // Ì½Í·µÄÈëÉäµãÎªÖ±Ïß1ºÍÖ±Ïß2µÄ½»µã
                   if(xxx==0)
                   {
                       p->horizontal_xr[p->k][i] = xTemp  ;
                       if(wedgeangle != 0) 
                       p->horizontal_yr[p->k][i] = (xTemp-para1)/vx2+para2;
                       else 
                       p->horizontal_yr[p->k][i] = desirey ;
                       p->horizontal_zr[p->k][i] = 0 ; 					   
                   }
			       else
				   {
				       if(wedgeangle==0)
				       {
						   p->horizontal_yr[p->k][i] = y0-fabs(z0)*tan(roofangle)			   ;
						   p->horizontal_xr[p->k][i] = xP+(p->horizontal_yr[p->k][i]-yP)*(xP-xTemp)/(yP-yTemp);
                           p->horizontal_zr[p->k][i] = 0                                      ;
				       }
				       else
					   {
					       aa1 = yyy/xxx ;
				           aa2 = 1/vx2   ;
					       p->horizontal_xr[p->k][i] = (aa2*para1-aa1*xP+yP-para2)/(aa2-aa1)  ;
                           p->horizontal_yr[p->k][i] = (p->horizontal_xr[p->k][i]-para1)/vx2+para2   ;
                           p->horizontal_zr[p->k][i] = 0                                      ;
				       }
	
			       }				  
            }
            else
            {
                   //A1 ==0 Ê±°´Ò»Î¬ROOF½ÇµÈÓÚ0µÄÇé¿ö×÷ËÑË÷
                   TempLength = sqrt(xxx*xxx+yyy*yyy);
                   SearchLength = TempLength/2 ;
 
                   if(TempLength==0||zTemp==0)
                   {
                       p->horizontal_xr[p->k][i] = xTemp  ;
                       p->horizontal_yr[p->k][i] = yTemp  ;
                       p->horizontal_zr[p->k][i] = 0      ;     
                       continue ;     
                   }                      
                   // do search in temporary coordinate
                   SearchPoint = 0 ;
                   TempResult =  0 ;
                   count = 0;                          
                   do
                   {
                       SearchPoint += SearchLength ;      
                       //printf("search point :%f \n",SearchPoint);
                       tana = SearchPoint/zTemp;
                       sina = sqrt(tana*tana/(1+tana*tana));
                       sinb = sina/k1;
					   
                       if(sinb>=1)  
                       {
                           SearchLength = -fabs(SearchLength)/2 ;                   
                       }
                       else
                       {
                           tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
                           TempResult=SearchPoint+tanb*FocusDepth ;
                           if(TempResult>TempLength)   SearchLength = -fabs(SearchLength)/2 ;
                           if(TempResult<TempLength)   SearchLength =  fabs(SearchLength)/2 ;                       
                       }                   
                       count++;         
                   }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;      
                 
                 p->horizontal_xr[p->k][i] = xTemp + SearchPoint*xxx/TempLength ;
                 p->horizontal_yr[p->k][i] = yTemp + SearchPoint*yyy/TempLength ;
                 p->horizontal_zr[p->k][i] = 0 ;  	
            }
     }  
     //calculate the transfer time
     for(i=0;i<Column;i++)
     {     
              dis1 = sqrt((p->probe_xr[p->k][i]-p->horizontal_xr[p->k][i])*(p->probe_xr[p->k][i]-p->horizontal_xr[p->k][i])
                             +(p->probe_yr[p->k][i]-p->horizontal_yr[p->k][i])*(p->probe_yr[p->k][i]-p->horizontal_yr[p->k][i])
                             +(p->probe_zr[p->k][i]-p->horizontal_zr[p->k][i])*(p->probe_zr[p->k][i]-p->horizontal_zr[p->k][i]));
              dis2 = sqrt((p->horizontal_xr[p->k][i]-p->focus_xr[p->k])*(p->horizontal_xr[p->k][i]-p->focus_xr[p->k])
                            +(p->horizontal_yr[p->k][i]-p->focus_yr[p->k])*(p->horizontal_yr[p->k][i]-p->focus_yr[p->k])
                            +(p->horizontal_zr[p->k][i]-p->focus_zr[p->k])*(p->horizontal_zr[p->k][i]-p->focus_zr[p->k]));
              time[i] = dis1/c1+dis2/c2;          
     }
     // get the time delay
     timemax = time[0];
     for(i=0;i<Column;i++)
     {
           if(timemax < time[i])  timemax = time[i] ;                   
     } 
     g_printf("\nReceviver\n");
     for(i = 0 ;i<Column ; i++)
     {
          
          g_printf("No.%d,time[%d] = %f,¦¤t=%d\n",i+1,i+1,time[i],(gint)((timemax - time[i])*1000000+0.5));
          p->timedelay[p->k][i] = (gint)((timemax - time[i])*1000000+0.5);
     }
     p->G_Time[p->k] = timemax;
	free(time);
}
/*
  Name:  flat_2d_roof_pr
  Copyright: Dopplor 
  Author: Sheng Shen
  Date: 17-03-11 13:40
  Description:   Æ½Ãæ¹¤¼þ2D µÄË«¾§ ¾Û½¹·¨Ôò 
  Input:  data: structure point to wedge probe .... coefficients
        angle1: refract angle
        angle2: skew angle
        depth : focus depth of sonic beam
*/
void flat_2d_roof_pr(gpointer data, gdouble angle1, gdouble angle2, gdouble depth)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
     
     gdouble c1 ;            // wave speed
     gdouble c2 ;
     gdouble k1 ;  
     gdouble h0 =  p->wedge_p->wg_heigh_fir ;                  // first element high
     gint Row      =  p->element_sel->sec_axis_ape  ;                  // element y direction numble
     gint Column   = p->element_sel->pri_axis_ape;                  // element x direction numble
     if((Row*Column) > (p->probe_p->ele_num_pri * p->probe_p->ele_num_sec))
            return;
     
     gdouble Intervaly = p->probe_p->sec_axis_pitch ;          // y direction interval
     gdouble Intervalx = p->probe_p->pri_axis_pitch ;          // x direction interval distance
     gdouble pri_ele_size = p->probe_p->pri_ele_size ;
     gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
     gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
     gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
     gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	 gdouble separation  = p->wedge_r->wg_separation ;

     gdouble  a1 = angle1*PI/180;                              // refract angle
     gdouble  a2 = angle2*PI/180;                              // deflect angle
 
     gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180   ; // roofangle   y-z platform
     gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ; // wedgeangle  x-z platform     
     gdouble  FocusDepth = depth;                              //  true focus depth
     
     gdouble xTemp, yTemp, zTemp ;
     gdouble x0,y0,z0;                                         // element center coordinate
     gdouble xP, yP, zP;                                       // focus point coordinate
     //  element offset in each direction
     gdouble x;
     gdouble y;
     gdouble z;
     gdouble d;
     gdouble s_x;
     gdouble s_y;
     gdouble s_zy;
     gdouble s_zx;     
     // variable for search method
     gdouble SearchLength , SearchPoint;
     gdouble TempLength;
     gdouble TempResult;
     gdouble sina;
     gdouble tana;    
     gdouble sinb;
     gdouble tanb;
     
     gdouble sinTmp;
     gdouble cosTmp;
     gdouble tanTmp;
     gdouble disTmp;
     
     gdouble xxx;
     gdouble yyy;
     gint i, j; 
     int count;
     
     gdouble dis1;
     gdouble dis2;
     gdouble timemax ;
	 gdouble timemax1;
     gdouble *time = malloc(2*Row*Column*sizeof(gdouble));
     
     // kill the impossible condition
     if(Column<=0||Row<=0) return ;
	 if(p->probe_p->D1_D2 == 0)  Row = 1 ;
     if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
 
     if(p->probe_p->transmi_trans_longi==0)
    {   
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
        c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
    }                                           
    else                                 
    {
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
        c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
    }
     // refract coefficient
     k1 =c1/c2 ;      

     // element location offset calculate
     if((wedgeangle != 0) && (roofangle != 0))
     {
          x = 1;
          y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
          z = y*tan(roofangle) ;
          d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
          s_x  = -Intervaly/d    ;
          s_y  = -Intervaly*y/d   ;
          s_zy  = -Intervaly*(z-tan(wedgeangle))/d   ;          
     }
     else
     {   
          s_y = -Intervaly*cos(roofangle);
          s_x = 0 ;
          s_zy = -Intervaly*sin(roofangle);
     }     
     // center probe element    (x0,y0,z0)            
     
     z0 = -(h0 + Intervalx*(Column - 1)*sin(wedgeangle)/2 - s_zy*(Row-1)/2);
     x0 = wg_pri_axis_reference + wg_pri_elem_offset_fir + Intervalx*(Column - 1)*cos(wedgeangle)/2 + (Row-1)*s_x/2 ;
     // y0   i s the middle point of two wedge
	 y0 = -wg_sec_axis_reference - wg_sec_elem_offset_fir - separation/2 ;   

    // get focus point coordinate 
     if(a1<0)
     {  a1 = -a1 ;
        if(a2>=0)  a2 = a2-PI ;
		else       a2 = PI+a2 ;
     }// Í¨¹ý´Ë´¦±ä»»Ê¹Ö§³Ö A1 (-90,90) A2(-180,180)          
     yTemp = sqrt(sin(a2)*sin(a2)*FocusDepth*FocusDepth*tan(a1)*tan(a1))  ;         
     if(a2==PI/2||a2==-PI/2)
        xTemp = 0;
     else
        xTemp = sqrt(tan(a1)*tan(a1)*FocusDepth*FocusDepth - yTemp*yTemp) ;   
	 if(a2 < 0)   yTemp= -yTemp ;
     if(xTemp==0)
     {
         sinTmp = sqrt(tan(a1)*tan(a1)/(1+tan(a1)*tan(a1)));
         sinTmp = sinTmp*k1;
         tanTmp = sqrt(sinTmp*sinTmp/(1-sinTmp*sinTmp));   
         if(yTemp == 0)
         {          
           xP =  x0 ;
           yP =  y0 ;
           zP =  FocusDepth;
         }
         else
         {
           disTmp = fabs(z0)*tanTmp;
           xP =  x0 ;
           yP =  y0  - yTemp*(sqrt(xTemp*xTemp+yTemp*yTemp)+disTmp)/sqrt(xTemp*xTemp+yTemp*yTemp);
           zP =  FocusDepth;
         }
     }
     else
     {          
         if( (a2 > PI/2) || (a2 < -PI/2))  xTemp = -xTemp ;
         //            
         sinTmp = sqrt(tan(a1)*tan(a1)/(1+tan(a1)*tan(a1)));
         sinTmp = sinTmp*k1;
         tanTmp = sqrt(sinTmp*sinTmp/(1-sinTmp*sinTmp));
         //
         if(yTemp == 0)
         {
           if(xTemp>=0)
               xP =  x0 + xTemp + fabs(z0)*tanTmp;
           else
               xP =  x0 + xTemp +  z0*tanTmp     ;
           yP =  y0 ;
        }
        else
        {
           disTmp = fabs(z0)*tanTmp;
           xP =  x0  + xTemp*(sqrt(xTemp*xTemp+yTemp*yTemp)+disTmp)/sqrt(xTemp*xTemp+yTemp*yTemp) ;
           yP =  y0  - yTemp*(sqrt(xTemp*xTemp+yTemp*yTemp)+disTmp)/sqrt(xTemp*xTemp+yTemp*yTemp) ;
           zP =  FocusDepth;
        }
     }         
     p->focus_x[p->k] =  xP ;
     p->focus_y[p->k] =  yP ;
     p->focus_z[p->k] =  FocusDepth;        
	 p->focus_xr[p->k] =  xP ;
     p->focus_yr[p->k] =  yP ;
     p->focus_zr[p->k] =  FocusDepth;        
     //first element location 
     p->probe_x[p->k][0] =   wg_pri_axis_reference + wg_pri_elem_offset_fir ;
     p->probe_y[p->k][0] =   -wg_sec_axis_reference - wg_sec_elem_offset_fir;
     p->probe_z[p->k][0] =   -h0  ;    
                
     for(i = 0; i< Column; i++)
     {
           for(j = 0; j< Row; j++)
           {
                 //  get elements' coordinates
                 zTemp = p->probe_z[p->k][0] + j*s_zy - i*Intervalx*sin(wedgeangle);
                 xTemp = p->probe_x[p->k][0] + Intervalx*cos(wedgeangle)*i + j*s_x ;
                 yTemp = p->probe_y[p->k][0] + s_y*j   ;
                 p->probe_x[p->k][i*Row+j] = xTemp;
                 p->probe_y[p->k][i*Row+j] = yTemp;
                 p->probe_z[p->k][i*Row+j] = zTemp;
                                  
                 xxx = xP-xTemp ;
                 yyy = yP-yTemp ;
                 TempLength = sqrt(xxx*xxx+yyy*yyy);
                 SearchLength = TempLength/2 ;
                 
                 if(TempLength==0||zTemp==0)
                 {
                       p->horizontal_x[p->k][i*Row+j] = xTemp  ;
                       p->horizontal_y[p->k][i*Row+j] = yTemp  ;
                       p->horizontal_z[p->k][i*Row+j] = 0 ;     
                       continue ;     
                 }                      
                 // do search in temporary coordinate
                 SearchPoint = 0 ;
                 TempResult  = 0 ;
                 count = 0;                          
                 do
                 {
                       SearchPoint += SearchLength ;      
                       //printf("search point :%f \n",SearchPoint);
                       tana = SearchPoint/zTemp;
                       sina = sqrt(tana*tana/(1+tana*tana));
                       sinb = sina/k1;
					   
                       if(sinb>=1)  
                       {
                           SearchLength = -fabs(SearchLength)/2 ;                   
                       }
                       else
                       {
                           tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
                           TempResult=SearchPoint+tanb*FocusDepth ;
                           if(TempResult>TempLength)   SearchLength = -fabs(SearchLength)/2 ;
                           if(TempResult<TempLength)   SearchLength =  fabs(SearchLength)/2 ;                       
                       }                   
                       count++;         
                 }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;                 
                 // translate into common coordiniate
                 p->horizontal_x[p->k][i*Row+j] = xTemp + SearchPoint*xxx/TempLength ;
                 p->horizontal_y[p->k][i*Row+j] = yTemp + SearchPoint*yyy/TempLength ;
                 p->horizontal_z[p->k][i*Row+j] = 0 ;                 
           }
     }  
	 for(i=0;i<Column;i++)
     {
         for(j =0;j<Row; j++)
         {
              dis1 = sqrt((p->probe_x[p->k][i*Row+j]-p->horizontal_x[p->k][i*Row+j])*(p->probe_x[p->k][i*Row+j]-p->horizontal_x[p->k][i*Row+j])
                             +(p->probe_y[p->k][i*Row+j]-p->horizontal_y[p->k][i*Row+j])*(p->probe_y[p->k][i*Row+j]-p->horizontal_y[p->k][i*Row+j])
                            +(p->probe_z[p->k][i*Row+j]-p->horizontal_z[p->k][i*Row+j])*(p->probe_z[p->k][i*Row+j]-p->horizontal_z[p->k][i*Row+j]));
              dis2 = sqrt((p->horizontal_x[p->k][i*Row+j]-p->focus_x[p->k])*(p->horizontal_x[p->k][i*Row+j]-p->focus_x[p->k])
                            +(p->horizontal_y[p->k][i*Row+j]-p->focus_y[p->k])*(p->horizontal_y[p->k][i*Row+j]-p->focus_y[p->k])
                            +(p->horizontal_z[p->k][i*Row+j]-p->focus_z[p->k])*(p->horizontal_z[p->k][i*Row+j]-p->focus_z[p->k]));
              time[i*Row+j] = dis1/c1+dis2/c2;
         }
     }

	 timemax = time[0];
     for(i=0;i<Column*Row;i++)
     {
           if(timemax < time[i])  timemax = time[i] ;                   
     }
     g_print("*************\n") ;
     g_print("    x1 x2 x3 \n")  ;
     g_print("y1  0  3  6  \n") ;
     g_print("y2  1  4  7  \n") ;
     g_print("y3  2  5  8  \n") ;
     g_print("***********\n");      
     
     g_print("Signal Element:\n");
     for(i = 0 ;i<Column*Row ; i++)
     {
          g_printf("No.%d,time[%d] = %f,¦¤t=%d\n",i+1,i+1,time[i],(gint)((timemax - time[i])*1000000+0.5));
          p->timedelay[p->k][i] = (gint)((timemax - time[i])*1000000+0.5);
     }

     h0 =  p->wedge_r->wg_heigh_fir ;                  // first element high
     Row      =  p->element_sel->sec_axis_ape  ;                  // element y direction numble
     Column   = p->element_sel->pri_axis_ape;                  // element x direction numble
     if((Row*Column) > (p->probe_p->ele_num_pri * p->probe_p->ele_num_sec))
                  return;
     
     Intervaly = p->probe_p->sec_axis_pitch ;          // y direction interval
     Intervalx = p->probe_p->pri_axis_pitch ;          // x direction interval distance
     pri_ele_size = p->probe_p->pri_ele_size ;
     wg_pri_axis_reference  = p->wedge_r->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
     wg_sec_axis_reference  = p->wedge_r->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
     wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
     wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	 roofangle = p->wedge_r->wg_roof_angle*PI/180   ; // roofangle   y-z platform
     wedgeangle= p->wedge_r->wg_wedge_angle*PI/180  ; // wedgeangle  x-z platform     

     if((wedgeangle != 0) && (roofangle != 0))
     {
          x = 1;
          y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
          z = y*tan(roofangle) ;
          d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
          s_x  = -Intervaly*x/d    ;
          s_y  = Intervaly*y/d     ;
          s_zy  = -Intervaly*(z-x*tan(wedgeangle))/d   ;          
     }
     else
     {   
          s_y = -Intervaly*cos(roofangle);
          s_x = 0 ;
          s_zy = -Intervaly*sin(roofangle);
     }  
	 
	 p->probe_xr[p->k][0] =   wg_pri_axis_reference + wg_pri_elem_offset_fir ;
     p->probe_yr[p->k][0] =   p->probe_y[p->k][0]  - separation;
     p->probe_zr[p->k][0] =   -h0  ;    
                
     for(i = 0; i< Column; i++)
     {
           for(j = 0; j< Row; j++)
           {
                 //  get elements' coordinates
                 zTemp = p->probe_zr[p->k][0] + j*s_zy - i*Intervalx*sin(wedgeangle);
                 xTemp = p->probe_xr[p->k][0] + Intervalx*cos(wedgeangle)*i + j*s_x ;
                 yTemp = p->probe_yr[p->k][0] - s_y*j   ;
                 p->probe_xr[p->k][i*Row+j] = xTemp;
                 p->probe_yr[p->k][i*Row+j] = yTemp;
                 p->probe_zr[p->k][i*Row+j] = zTemp;
                                  
                 xxx = xP-xTemp ;
                 yyy = yP-yTemp ;
                 TempLength = sqrt(xxx*xxx+yyy*yyy);
                 SearchLength = TempLength/2 ;
                 
                 if(TempLength==0||zTemp==0)
                 {
                       p->horizontal_xr[p->k][i*Row+j] = xTemp  ;
                       p->horizontal_yr[p->k][i*Row+j] = yTemp  ;
                       p->horizontal_zr[p->k][i*Row+j] = 0 ;     
                       continue ;     
                 }                      
                 // do search in temporary coordinate
                 SearchPoint = 0 ;
                 TempResult =  0 ;
                 count = 0;                          
                 do
                 {
                       SearchPoint += SearchLength ;      
                       //printf("search point :%f \n",SearchPoint);
                       tana = SearchPoint/zTemp;
                       sina = sqrt(tana*tana/(1+tana*tana));
                       sinb = sina/k1;
					   
                       if(sinb>=1)  
                       {
                           SearchLength = -fabs(SearchLength)/2 ;                   
                       }
                       else
                       {
                           tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
                           TempResult=SearchPoint+tanb*FocusDepth ;
                           if(TempResult>TempLength)   SearchLength = -fabs(SearchLength)/2 ;
                           if(TempResult<TempLength)   SearchLength =  fabs(SearchLength)/2 ;                       
                       }                   
                       count++;         
                 }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;                 
                 // translate into common coordiniate
                 p->horizontal_xr[p->k][i*Row+j] = xTemp + SearchPoint*xxx/TempLength ;
                 p->horizontal_yr[p->k][i*Row+j] = yTemp + SearchPoint*yyy/TempLength ;
                 p->horizontal_zr[p->k][i*Row+j] = 0 ;                 
           }
     }  
     //calculate the transfer time

	 //calculate the transfer time
     for(i=0;i<Column;i++)
     {
         for(j =0;j<Row; j++)
         {
              dis1 = sqrt((p->probe_xr[p->k][i*Row+j]-p->horizontal_xr[p->k][i*Row+j])*(p->probe_xr[p->k][i*Row+j]-p->horizontal_xr[p->k][i*Row+j])
                             +(p->probe_yr[p->k][i*Row+j]-p->horizontal_yr[p->k][i*Row+j])*(p->probe_yr[p->k][i*Row+j]-p->horizontal_yr[p->k][i*Row+j])
                            +(p->probe_zr[p->k][i*Row+j]-p->horizontal_zr[p->k][i*Row+j])*(p->probe_zr[p->k][i*Row+j]-p->horizontal_zr[p->k][i*Row+j]));
              dis2 = sqrt((p->horizontal_xr[p->k][i*Row+j]-p->focus_xr[p->k])*(p->horizontal_xr[p->k][i*Row+j]-p->focus_xr[p->k])
                            +(p->horizontal_yr[p->k][i*Row+j]-p->focus_yr[p->k])*(p->horizontal_yr[p->k][i*Row+j]-p->focus_yr[p->k])
                            +(p->horizontal_zr[p->k][i*Row+j]-p->focus_zr[p->k])*(p->horizontal_zr[p->k][i*Row+j]-p->focus_zr[p->k]));
              time[i*Row+j] = dis1/c1+dis2/c2;          
         }
     }
     // get the time delay

	 timemax1 = time[0] ;
	 for(i=0;i<Column*Row;i++)
     {
           if(timemax1 < time[i])  timemax1 = time[i] ;                   
     }

	 g_print("Receive Element:\n") ;
	 for(i = 0 ;i<Column*Row ; i++)
     {
          g_printf("No.%d,time[%d] = %f,¦¤t=%d\n",i+1,i+1,time[i],(gint)((timemax - time[i])*1000000+0.5));
          p->timedelay[p->k][i] = (gint)((timemax - time[i])*1000000+0.5);
     }
     p->G_Time[p->k] = timemax;
     free(time);
}

/*
  Name:  cylinder_2d_roof_od
  Copyright: Dopplor 
  Author: Sheng Shen
  Date: 17-03-11 13:40
  Description:   2 DIMENSION ´øROOF ½ÇµÄ OD ¾Û½¹·¨Ôò 
  Input:  data: structure point to wedge probe .... coefficients
        angle1: refract angle
        angle2: skew angle
        depth : focus depth of sonic beam
*/
void cylinder_2d_roof_od (gpointer data, gdouble angle1, gdouble angle2, gdouble depth)
{
		 DRAW_UI_P p = (DRAW_UI_P) data ;
		 
		 gdouble c1 ;			 // wave speed
		 gdouble c2 ;
		 gdouble k1 ;  
		 gdouble r  ;
		 gdouble h0 =  p->wedge_p->wg_heigh_fir ;				   // first element high
//		 gint Row      =  p->element_sel->sec_axis_ape  ;                  // element y direction numble
//         gint Column   =  p->element_sel->pri_axis_ape;                  // element x direction numble
//         if((Row*Column) > (p->probe_p->ele_num_pri * p->probe_p->ele_num_sec))
//            return;
		 int PriElementStart = p->element_sel->primary_axis_s - 1  ;
		 int PriElementNum	 = p->probe_p->ele_num_pri			  ;
		 int SecElementStart = p->element_sel->seconary_axis_s -1 ;
		 int SecElementNum	 = p->probe_p->ele_num_sec			  ;
		 int PriElementSelect= p->element_sel->pri_axis_ape 	  ;
		 int SecElementSelect= p->element_sel->sec_axis_ape 	  ;
		 int PriElementStop  = PriElementStart +  PriElementSelect;
		 int SecElementStop  = SecElementStart +  SecElementSelect;
		 
		 gdouble Intervaly = p->probe_p->sec_axis_pitch ;		   // y direction interval
		 gdouble Intervalx = p->probe_p->pri_axis_pitch ;		   // x direction interval distance
		 gdouble pri_ele_size = p->probe_p->pri_ele_size ;        
		 gdouble wg_pri_axis_reference	= p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
		 gdouble wg_sec_axis_reference	= p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
		 gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
		 gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
         gdouble length = p->wedge_p->wg_length ;                              // wedge length
		 gdouble CylinderExtDiameter = p->specimen->speci_outside_cylindrical ;// outside cylinder diameter
		 	  
		 gdouble  a1 = fabs(angle1*PI/180);						   // refract angle
		 gdouble  a2 = fabs(angle2*PI/180);						   // deflect angle
	     if(a2>PI/2) a2 = PI-a2 ;
		 
		 gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180	 ; // roofangle   y-z platform
		 gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180 ; // wedgeangle  x-z platform	   
		 gdouble  FocusDepth = depth;							   //  true focus depth
 
		 // refraction calculation 
		 gdouble aSinTemp;
		 gdouble aProjection;
		 gdouble bProjection;
		 gdouble zHightTemp;
		 
		 gdouble tempangle1;
		 gdouble tempangle2;
		 gdouble tempangle3;

		 gdouble tempFocusxxx;
		 gdouble tempFocusyyy;
		 gdouble tempFocuszzz;
		 gdouble angle_rotate;
		 
		 gdouble xTemp, yTemp, zTemp ;
		 gdouble x0,y0,z0;			  // element center coordinate
		 //  element offset in each direction
		 gdouble x;
		 gdouble y;
		 gdouble z;
		 gdouble d;
		 gdouble s_x;
		 gdouble s_y;
		 gdouble s_zy;
		 gdouble s_zx;	   
		 // variable for search method
		 gdouble SearchLength , SearchAngle;
		 gdouble TempAngle;
		 gdouble TempResult;
		 gdouble SkewAngleTemp;
		 gdouble SearchPoint ;
		 gdouble TempLength  ;
		 gdouble tana,tanb,sina,sinb ;
		 
         gdouble r_depth;
         gdouble a;
		 gdouble b;
		 
		 gdouble xxx;
		 gdouble yyy;
		 gdouble zzz;
		 
		 gint i, j; 
		 int count;
		 // variable for time calculation
		 gdouble dis1;
		 gdouble dis2;
		 gdouble timemax ;
 
		gdouble *time = malloc(PriElementNum*SecElementNum*sizeof(gdouble));
	    if(p->probe_p->D1_D2 == 0) {SecElementNum = 1;  SecElementStart = 0; SecElementStop = 1;}
		 
		if(PriElementStop > PriElementNum )  return ;
		if(SecElementStop > SecElementNum )  return ;	

		r = CylinderExtDiameter/2.0 ;
		// kill the impossible condition
		if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
	 
		if(p->probe_p->transmi_trans_longi==0)
        {   
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
            c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
        }                                           
        else                                 
        {
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
            c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
        }
		 // refract coefficient
		 k1 = c1/c2 ;

		 // element location offset calculate
		 // ÔÚROOF½Ç²»µÈÓÚ0Ê±,ÔÚ´¹Ö±ÓÚWEDGE ½ÇÉÏ±ß·½ÏòÉÏÃ¿×ßÒ»¶Î¾àÀë
         // ¶ÔÓ¦µÄ X Y Z Èý¸ö·½ÏòÉÏ¶¼»áÓÐÒ»¸öÎ»ÖÃ±ä»¯SX SY SZ
		 if((wedgeangle != 0) && (roofangle != 0))
		 {
			  x = 1;
			  y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
			  z = y*tan(roofangle) ;
			  d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
			  s_x  = -Intervaly/d	 ;
			  s_y  = -Intervaly*y/d   ;
			  s_zy	= -Intervaly*(z-tan(wedgeangle))/d	 ;			
		 }
		 else
		 {	 
			  s_y = -Intervaly*cos(roofangle);
			  s_x = 0 ;
			  s_zy = -Intervaly*sin(roofangle);
		 }	   

	     //calc offset generated by element selection
		 z0 = SecElementStart*s_zy - PriElementStart*Intervalx*sin(wedgeangle);
		 x0 = Intervalx*cos(wedgeangle)*PriElementStart + SecElementStart*s_x ;
		 y0 = s_y*SecElementStart   ;

		 // center probe element	(x0,y0,z0)			  
		 z0 = -(z0 +h0 + Intervalx*(PriElementSelect - 1)*sin(wedgeangle)/2 - s_zy*(SecElementSelect -1)/2) -sqrt(CylinderExtDiameter*CylinderExtDiameter - length*length)/2;
		 x0 = x0 -length/2 + wg_pri_elem_offset_fir + Intervalx*(PriElementSelect - 1)*cos(wedgeangle)/2 + (SecElementSelect-1)*s_x/2 ;
         if(roofangle<0)
		     wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;
		 y0 = y0 - wg_sec_axis_reference - wg_sec_elem_offset_fir + s_y*(SecElementSelect-1)/2 ;
         //ÒÔÏÂºÍ1Î¬CylinderÇé¿öÀàËÆ.
         //Ö»ÊÇ½«3Î¬µÄ×ø±êÍ¶Ó°µ½X-ZÃæ
         //¿Õ¼ä½Ç¶ÈºÍÍ¶Ó°½ÇÆ«×ª½ÇÖ®¼äµÄ¹ØÏµ
         // tan(Projection) = tan(SpaceAngle)*cos(SkewAngle);
		 // get focus point coordinate 
		 aSinTemp = asin(k1*sin(a1));
		 aProjection = atan(tan(aSinTemp)*cos(a2));
		 zHightTemp = sqrt(z0*z0 + x0*x0);
		 
		 tempangle1 = asin(r*sin(aProjection)/zHightTemp);
		 tempangle2 = aProjection - tempangle1;   //tempangle2  keep for the below calculation
         // refract point
		 xxx = r * sin(tempangle2);
		 zzz = r * cos(tempangle2);
		 
         bProjection = atan(tan(a1)*cos(a2));
         tempangle3 = asin(sin(bProjection)*r/(r-FocusDepth));  // tempangle3 is sure to be large than 90 degree
		 tempangle1 = tempangle3 - bProjection               ;
		 // µ±ÕÛÉä½ÇºÍÆ«×ª½ÇÉè¶¨,¼È¿ÉÇóµÃ×î´ó¾Û½¹Éî¶È.
		 // R*SIN(PROJECTION)
         //if(FocusDepth>r*sin(bProjection))  FocusDepth =  r*sin(bProjection);
		 //g_print("MaxDepth:%f\n", r*sin(bProjection))        ;  // when a1 and a2 is setted, there will exist a max focus depth		 
		 tempFocusxxx = (r-FocusDepth) * sin(tempangle1+tempangle2) ;
		 tempFocuszzz = (r-FocusDepth) * cos(tempangle1+tempangle2) ;
         tempFocusyyy = zHightTemp*sin(tempangle2)+sin(tempangle1)*(r-FocusDepth);         
		 tempFocusyyy = tempFocusyyy*tan(a2) ;
		 //Ö®Ç°  gdouble  a1 = fabs(angle1*PI/180); 						   // refract angle
		 // 		   gdouble	  a2 = fabs(angle2*PI/180); 						   // deflect angle
		 // 		   if(a2>PI/2)	a2 = PI-a2 ;
		 //µ±a1 a2	  ¶¼´óÓÚ0Ê±,Ïà¶ÔÓÚÌ½Í·ÖÐÐÄµãµÄ×ø±êÏµµÄÈëÉäµã×ø±ê
		 // TEMPFOCUSXXX TEMPFOCUSYYY TEMPFOCUSZZZ
		 //ÇóµÃÁÙÊ±×ø±êºó,ÔÙ¸ù¾Ýa1 a2µÄÊµ¼ÊÇé¿ö,½«×ø±êµÄÕý¸ºÖµÉè¶¨
         if(angle1>=0)
         {
             if(angle2>=0)
             {
                 if(angle2>90)
                 {
                      tempFocusxxx=-tempFocusxxx;
                 }
             }
			 else
			 {
			     if(a2>PI/2)
			     {
			          tempFocusxxx=-tempFocusxxx;
			     }
				 tempFocusyyy = -tempFocusyyy;
			 }
         }
		 else
		 {
		     if(angle2>=0)
             {
                 if(angle2>90)
                 {
                      tempFocusyyy = -tempFocusyyy;
                 }
				 else
				 {
				      tempFocusyyy=-tempFocusyyy;
					  tempFocusxxx = -tempFocusxxx;
				 }
             }
			 else
			 {
			     if(a2<PI/2)
			     {
			          tempFocusxxx=-tempFocusxxx;
			     }		 
			 }
		 }
		 //×ø±êÐý×ª,½«½¹µã×ø±êÓÉÖÐÐÄÌ½Í·×ø±êÐý×ªµ½Êµ¼Ê×ø±ê
		 p->focus_y[p->k]   = y0 - tempFocusyyy    ;
		 angle_rotate = -asin(x0/zHightTemp) ;
		 p->focus_x[p->k] = tempFocusxxx*cos(angle_rotate) - tempFocuszzz*sin(angle_rotate);
		 p->focus_z[p->k] = -(tempFocusxxx*sin(angle_rotate) + tempFocuszzz*cos(angle_rotate));
		 //µÚÒ»¸öÌ½Í·µÄ×ø±ê
		 p->probe_x[p->k][0] =   -length/2 + wg_pri_elem_offset_fir ;
		 p->probe_y[p->k][0] =   -wg_sec_axis_reference - wg_sec_elem_offset_fir;
		 p->probe_z[p->k][0] =   -h0	- sqrt(CylinderExtDiameter*CylinderExtDiameter- length*length)/2;	  
		 tempangle2 = asin(p->focus_x[p->k]/(r-FocusDepth)) ;
		 r_depth    = r - FocusDepth ;
		 
		 for(i = PriElementStart; i< PriElementStop; i++)
		 {
			  for(j = SecElementStart; j< SecElementStop; j++)
			  {
					//get elements' coordinates
					zTemp = p->probe_z[p->k][0] + j*s_zy - i*Intervalx*sin(wedgeangle);
					xTemp = p->probe_x[p->k][0] + Intervalx*cos(wedgeangle)*i + j*s_x ;
					yTemp = p->probe_y[p->k][0] + s_y*j;
					p->probe_x[p->k][i*SecElementNum+j] = xTemp  ;
					p->probe_y[p->k][i*SecElementNum+j] = yTemp  ;
					p->probe_z[p->k][i*SecElementNum+j] = zTemp  ;
					if((xTemp*xTemp+zTemp*zTemp)<r*r)
					{
					   	p->horizontal_x[p->k][i*SecElementNum+j] = xTemp  ;
					    p->horizontal_y[p->k][i*SecElementNum+j] = yTemp ;
					    p->horizontal_z[p->k][i*SecElementNum+j] = zTemp ;
					    continue ;
					}
                    count = 0;
					zHightTemp   = sqrt(xTemp*xTemp + zTemp*zTemp);
					angle_rotate = -asin(xTemp/zHightTemp)        ;
					tempangle3   = tempangle2 + angle_rotate      ;
                    if(tempangle3 == 0)
                    { // µ±Í¶Ó°½ÇÎª0Ê±,ÔÚY·½Ïò×÷ËÑË÷.ÀàËÆÓÚÒ»Î¬ËÑË÷
					    xxx = 0;
						zzz = r ;			
					    if(yTemp == p->focus_y[p->k])
					       yyy = yTemp ;
					    else 
					    {
					         zTemp = zHightTemp - r;
							 TempLength = fabs(yTemp-p->focus_y[p->k]);
							 SearchLength = TempLength/2 ;
							 SearchPoint = 0 ;
							 TempResult = 0 ;
                             do
                             {
                                  SearchPoint += SearchLength ;      
                                   //printf("search point :%f \n",SearchPoint);
                                  tana = SearchPoint/zTemp;
                                  sina = sqrt(tana*tana/(1+tana*tana));
                                  sinb = sina/k1;				   
                                  if(sinb>=1)  
                                  {
                                       SearchLength = -fabs(SearchLength)/2 ;                   
                                  }
                                  else
                                  {
                                       tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
                                       TempResult=SearchPoint+tanb*FocusDepth ;
                                       if(TempResult>TempLength)   SearchLength = -fabs(SearchLength)/2 ;
                                       if(TempResult<TempLength)   SearchLength =  fabs(SearchLength)/2 ;                 
                                  }                   
                                  count++;         
                             }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;   

                             yyy = yTemp + SearchPoint*(p->focus_y[p->k]-yTemp)/fabs(p->focus_y[p->k] - yTemp); 
							 
					    }
                        
					    p->horizontal_x[p->k][i*SecElementNum+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)  ;
					    p->horizontal_y[p->k][i*SecElementNum+j] = yyy ;
					    p->horizontal_z[p->k][i*SecElementNum+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate));
						continue ;
                    }
					tempangle1   = fabs(tempangle3);
					SearchLength = tempangle1/2                   ;
					SearchAngle  = 0                              ;
					TempResult   = 0                              ;
					
					yyy = fabs(p->focus_y[p->k] - yTemp) ;
					//TempResult = TempLength + SearchGate ;
					do
					{// ËÑË÷X-ZÍ¶Ó°½Ç
						  SearchAngle += SearchLength ; 	 
						  //printf("search point :%f \n",SearchPoint);
						  aProjection = atan(zHightTemp*sin(SearchAngle)/(zHightTemp*cos(SearchAngle)-r));
						  SkewAngleTemp = atan(yyy/(zHightTemp*sin(SearchAngle)+(r-FocusDepth)*sin(tempangle1-SearchAngle)));
                          a = atan(tan(aProjection)/cos(SkewAngleTemp));
                          if(fabs(sin(a)/k1)>=1)
                          {
                                 SearchLength = -fabs(SearchLength)/2 ;
                          }
                          else
                          {						  
                             b = asin(sin(a)/k1)                          ;
						     bProjection = atan(tan(b)*cos(SkewAngleTemp));
                             TempResult  = r*sin(bProjection)/sin(bProjection+tempangle1-SearchAngle)  ;
						     if(TempResult>r_depth)   SearchLength = -fabs(SearchLength)/2 ;
                             if(TempResult<r_depth)   SearchLength =  fabs(SearchLength)/2 ;
                          }
						  count++;
					}while( (fabs(TempResult-r_depth) > SearchGate) && ( count<=20 )) ;	   
					// translate into common coordiniate
                    if(tempangle3<=0)
					       xxx = -r*sin(SearchAngle) ;
					else   
						   xxx = r*sin(SearchAngle);
					
					if(yTemp>p->focus_y[p->k])
					    yyy = yTemp - sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp) ;
					else 
					    yyy = yTemp + sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp);
                    zzz = r*cos(SearchAngle);
					p->horizontal_x[p->k][i*SecElementNum+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)  ;
					p->horizontal_y[p->k][i*SecElementNum+j] = yyy ;
					p->horizontal_z[p->k][i*SecElementNum+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate)) ;				   
			  }
		 }
		//calculate the transfer time
		for(i = PriElementStart; i< PriElementStop; i++)
		{
			for(j = SecElementStart; j< SecElementStop; j++)
			{
				 dis1 = sqrt((p->probe_x[p->k][i*SecElementNum+j]-p->horizontal_x[p->k][i*SecElementNum+j])*(p->probe_x[p->k][i*SecElementNum+j]-p->horizontal_x[p->k][i*SecElementNum+j])
								+(p->probe_y[p->k][i*SecElementNum+j]-p->horizontal_y[p->k][i*SecElementNum+j])*(p->probe_y[p->k][i*SecElementNum+j]-p->horizontal_y[p->k][i*SecElementNum+j])
							   +(p->probe_z[p->k][i*SecElementNum+j]-p->horizontal_z[p->k][i*SecElementNum+j])*(p->probe_z[p->k][i*SecElementNum+j]-p->horizontal_z[p->k][i*SecElementNum+j]));
				 dis2 = sqrt((p->horizontal_x[p->k][i*SecElementNum+j]-p->focus_x[p->k])*(p->horizontal_x[p->k][i*SecElementNum+j]-p->focus_x[p->k])
							   +(p->horizontal_y[p->k][i*SecElementNum+j]-p->focus_y[p->k])*(p->horizontal_y[p->k][i*SecElementNum+j]-p->focus_y[p->k])
							   +(p->horizontal_z[p->k][i*SecElementNum+j]-p->focus_z[p->k])*(p->horizontal_z[p->k][i*SecElementNum+j]-p->focus_z[p->k]));
				 time[i*SecElementNum+j] = dis1/c1+dis2/c2;		   
			}
		}
		// get the time delay
		timemax = time[PriElementStart*SecElementNum + SecElementStart]; 
		
		for(i=PriElementStart; i< PriElementStop ; i++)
		{
			for(j = SecElementStart; j< SecElementStop; j++)
			{
				  if(timemax < time[i*SecElementNum + j ])	timemax = time[i*SecElementNum + j ] ;
			}
		}
		
		g_print("***********\n") ;
		g_print("	 x1 x2 x3\n")  ;
		g_print("y1  0	3  6  \n") ;
		g_print("y2  1	4  7  \n") ;
		g_print("y3  2	5  8  \n") ;
		g_print("***********\n");	   
		
		for(i=PriElementStart; i< PriElementStop ; i++)
		{
			for(j = SecElementStart; j< SecElementStop; j++)
			{
				 g_printf("No.[%d][%d],time = %f,¦¤t=%d\n",i+1,j+1,time[i*SecElementNum + j ],(gint)((timemax - time[i*SecElementNum + j ])*1000000+0.5));
				 p->timedelay[p->k][i*SecElementNum + j] = (gint)((timemax - time[i*SecElementNum + j ])*1000000+0.5)								   ;
			}
		}
		p->G_Time[p->k] = timemax;
		free(time);


}


/*
  Name:  cylinder_1d_od_zero
  Copyright: Dopplor 
  Author: Sheng Shen
  Date: 10 -05-11 13:40
  Description:   1 DIMENSION ´øROOF ½ÇµÄ OD ¾Û½¹·¨Ôò  ROTATION Z = 0
  Input:  data: structure point to wedge probe .... coefficients
        angle1: refract angle
        angle2: skew angle
        depth : focus depth of sonic beam
*/
void cylinder_1d_od_zero (gpointer data, gdouble angle1, gdouble angle2, gdouble depth)
{
	 DRAW_UI_P p = (DRAW_UI_P) data ;
	 
	 gdouble c1 ;			 // wave speed
	 gdouble c2 ;
	 gdouble k1 ;  
	 gdouble h0 = p->wedge_p->wg_heigh_fir ;				   // first element high
	
	 int ElementStart = p->element_sel->primary_axis_s - 1;
	 int ElementColumn= p->probe_p->ele_num_pri 		  ;
	 int SelectColumn  = p->element_sel->pri_axis_ape	  ;
	 int ElementStop  =   SelectColumn+ ElementStart	  ;
	 
	 gdouble Intervalx = p->probe_p->pri_axis_pitch ;		   // x direction interval distance
	 gdouble pri_ele_size = p->probe_p->pri_ele_size ;		
	 gdouble wg_pri_axis_reference	= p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	 //gdouble wg_sec_axis_reference	= p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	 gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
	 gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	 gdouble  a1 = angle1*PI/180;							   // refract angle  

	 gdouble width = p->wedge_p->wg_width ;
	 gdouble r = p->specimen->speci_outside_cylindrical / 2.0  ;
	 gdouble zHeight = -sqrt(r*r - width*width/4);
	 //gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180	 ; // roofangle   y-z platform
	 gdouble wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ; // wedgeangle  x-z platform	   
	 gdouble FocusDepth = depth;							   //  true focus depth
	 gdouble xTemp, yTemp, zTemp ;
	 gdouble x0,y0,z0;										   // element center coordinate
	 gdouble xP, yP, zP;									   // focus point coordinate
	 // get focus point coordinate			
	 gdouble tanw;
	 gdouble tanr;
	 gdouble para1,para2;
	 gdouble vx1,vy1,vz1,vx2,vy2,vz2;
	 gdouble desirex,desirey,desirez;
	 gdouble min_angle1 ;
	 gdouble min_angle2 ;
	 gdouble refract_x;
	 gdouble refract_y;
	 gdouble tempR;
	 gdouble len1;
	 gdouble len2;
	 gdouble len3;
	 // variable for search method	// 
	 gdouble SearchLength , SearchPoint;
	 gdouble TempLength;
	 gdouble TempResult;
	 gdouble sina;
	 gdouble tana;	  
	 gdouble sinb;
	 gdouble tanb;	   
	 gdouble sinTmp;
	 gdouble cosTmp;
	 gdouble tanTmp;
	 gdouble disTmp;	 
	 gdouble xxx;
	 gdouble yyy;
	 gint i, j; 
	 int count;
	 // variable for refract point
	 gdouble aa1,bb1;
	 gdouble aa2,bb2;
	 //  time delay calculation
	 gdouble dis1;
	 gdouble dis2;
	 gdouble timemax ;
	 gdouble roofangle;
	
	 if(ElementStop > ElementColumn)  return ;
	 z0 = Intervalx*ElementStart*sin(wedgeangle);
	 x0 = Intervalx*ElementStart*cos(wedgeangle);
	 
	 gdouble *time = malloc(ElementColumn * sizeof(gdouble));
	 
	 // kill the impossible condition
	 //if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
	 
	 if(p->probe_p->transmi_trans_longi==0)
	 {	 
		 c1  = p->wedge_p->wg_lon_vel ; 			  /* Ð¨¿é×Ý²¨ÉùËÙ */ 
		 c2  = p->specimen->speci_transverse_wave;	  /* Ñù±¾ºá²¨ÉùËÙ */  
	 }											 
	 else								  
	 {
		 c1  = p->wedge_p->wg_lon_vel ; 			  /* Ð¨¿é×Ý²¨ÉùËÙ */	
		 c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
	 }
	
	 // refract coefficient
	 k1 =c1/c2 ;	   
	 // center probe element	(x0,y0,z0)			  
	 z0 = -(z0 + h0 + Intervalx*(SelectColumn - 1)*sin(wedgeangle)/2) +zHeight;
	 x0 = x0 + wg_pri_axis_reference + wg_pri_elem_offset_fir + Intervalx*(SelectColumn-1)*cos(wedgeangle)/2;
	 y0 = width/2 - wg_sec_elem_offset_fir;
	 // get focus point coordinate 
	 // desirex desirey desirez : ÈëÉäµã×ø±ê		  
	 if(roofangle == 0)
	 {
		   TempLength = FocusDepth*tan(a1) ;
		   p->focus_x[p->k] =  x0+TempLength ;
		   TempLength =  fabs(z0)*tan(asin(sin(a1)*k1));
		   p->focus_x[p->k] += TempLength ;
		   p->focus_y[p->k] =  y0 ;
		   p->focus_z[p->k] =  FocusDepth;
		   xP = p->focus_x[p->k];
		   yP = p->focus_y[p->k];
		   zP = p->focus_z[p->k];
	 }
	 else
	 {
		 if(wedgeangle==0)
		 {
			 desirex = x0 ;
			 desirey = y0-fabs(z0)*tan(roofangle);
			 desirez = 0;
		 }
		 else
		 {
				 tanw = -tan(wedgeangle);
				 tanr = tan(roofangle)	;
				 vx1  = tanw*tanr		;
				 vy1  = -(1+tanw*tanw)	;
				 vz1  = -tanr			;
				 // (x-para1)/vx2 = y-para2   
				 //¹ýÌ½Í·ÓëÐ¨¿éÃæ´¹Ö±ÃæÓëZ=0ÃæµÄ½»Ïß·½³Ì
				 para1 = x0 			;
				 para2 = y0 + z0*vz1/vy1;
				 vx2 = -vy1/vx1 		;
				 //ÖÐÐÄÌ½Í·Óë½»ÏßµÄ´¹Ö±µã
				 desirex = (vx2*x0+y0+para1/vx2 - para2)/(vx2+1/vx2);
				 desirey = para2 + (desirex - para1)/vx2 ;
				 desirez = 0 ;
		 }
			 // Çó×îÐ¡ÈëÉä½Ç
		 min_angle1 = atan(sqrt((desirex-x0)*(desirex-x0)+(desirey-y0)*(desirey-y0))/fabs(z0));
		 min_angle2 = sin(min_angle1)/k1;
		 if(min_angle2>=1)
		 {
			 // Èç¹û×îÐ¡ÈëÉä½Ç·¢ÉúÈ«·´ÉäÈ¡½¹µãÎªÖÐÐÄÌ½Í·×ø±ê
			 xP = x0;
			 yP = y0;
			 a1 = 0 ;
		 }
		 else 
		 {
		   if(asin(min_angle2)>=fabs(a1))
		   {
			   //Èç¹û ×îÐ¡ÕÛÉä½Ç´óÓÚ¸ø¶¨ÕÛÉä½Ç,È¡´¹Ö±µã×÷ÎªÖÐÐÄÌ½Í·ÈëÉäµã 
			   refract_x = desirex;
			   refract_y = desirey;
			   a1 = min_angle2 ;
		   }
		   else
		   {
			   // ¼ÆËãÕý³£Çé¿öÏÂ½¹µãµÄ×ø±ê
			   //refract point ÕÛÉäµã×ø±ê 
			   min_angle2 = asin(sin(a1)*k1);
			   tempR = z0*tan(min_angle2);
			   TempLength = sqrt(tempR*tempR - (desirex-x0)*(desirex-x0)-(desirey-y0)*(desirey-y0));
			   if(a1>=0)
			   {
					  refract_x = desirex-TempLength*vx2/sqrt(1+vx2*vx2);
					  refract_y = desirey-TempLength/sqrt(1+vx2*vx2);
			   }
			   else
			   {
					  refract_x = desirex+TempLength*vx2/sqrt(1+vx2*vx2);
					  refract_y = desirey+TempLength/sqrt(1+vx2*vx2);
			   }
		   }	   
		   TempLength = FocusDepth*tan(a1) ;
		   len1 = refract_x - x0;
		   len2 = refract_y - y0;
		   len3 = sqrt(len1*len1+len2*len2);
		   if(a1>=0)
		   {
				 xP = refract_x+TempLength*len1/len3;
				 yP = refract_y+TempLength*len2/len3;
		   }
		   else
		   {
				 xP = refract_x-TempLength*len1/len3;
				 yP = refract_y-TempLength*len2/len3;
		   }
		   }
		   p->focus_x[p->k] =  xP ;
		   p->focus_y[p->k] =  yP ;
		   p->focus_z[p->k] =  FocusDepth;
	  }
	  //g_print("Focus x=%f,y=%f,z=%f\n",p->focus_x[p->k],p->focus_y[p->k],p->focus_z[p->k]);
	  //first element location 
	  p->probe_x[p->k][0] =   wg_pri_axis_reference + wg_pri_elem_offset_fir ;
	  //p->probe_y[p->k][0] =   -wg_sec_axis_reference - wg_sec_elem_offset_fir;
	  p->probe_z[p->k][0] =   -h0  ;
	   
	  for(i = ElementStart; i< ElementStop; i++)
	  {
			 //  get each element coordinates
			 zTemp = p->probe_z[p->k][0]  - i*Intervalx*sin(wedgeangle);
			 xTemp = p->probe_x[p->k][0]  + Intervalx*cos(wedgeangle)*i;
			 yTemp = p->probe_y[p->k][0];
			 p->probe_x[p->k][i] = xTemp;
			 p->probe_y[p->k][i] = yTemp;
			 p->probe_z[p->k][i] = zTemp;	
	
			 if(zTemp>=0)
			 {	  // kill special situation when probe under the detect surface
				  p->horizontal_x[p->k][i] = xTemp	;
				  p->horizontal_y[p->k][i] = yTemp	;
				  p->horizontal_z[p->k][i] = zTemp	; 
				  continue ;
			 }			 
			 xxx = xP-xTemp ;
			 yyy = yP-yTemp ;
			 if(a1 != 0&&roofangle!=0)
			 {
					// Ö±Ïß1 :¹ýÌ½Í·ÓëWEDGE´¹Ö±ÃæÓëZ=0 µÄ½»Ïß
					// Ö±Ïß2 :Ì½Í·ºÍ½¹µãÁ¬ÏßÔÚZ=0ÃæÉÏµÄÍ¶Ó°
					// Ì½Í·µÄÈëÉäµãÎªÖ±Ïß1ºÍÖ±Ïß2µÄ½»µã
					if(xxx==0)
					{
						p->horizontal_x[p->k][i] = xTemp  ;
						if(wedgeangle != 0) 
						p->horizontal_y[p->k][i] = (xTemp-para1)/vx2+para2;
						else 
						p->horizontal_y[p->k][i] = desirey ;
						p->horizontal_z[p->k][i] = 0 ;						
					}
					else
					{
						if(wedgeangle==0)
						{
							p->horizontal_y[p->k][i] = y0-fabs(z0)*tan(roofangle)				;
							p->horizontal_x[p->k][i] = xP+(p->horizontal_y[p->k][i]-yP)*(xP-xTemp)/(yP-yTemp);
							p->horizontal_z[p->k][i] = 0									  ;
						}
						else
						{
							aa1 = yyy/xxx ;
							aa2 = 1/vx2   ;
							p->horizontal_x[p->k][i] = (aa2*para1-aa1*xP+yP-para2)/(aa2-aa1)  ;
							p->horizontal_y[p->k][i] = (p->horizontal_x[p->k][i]-para1)/vx2+para2	;
							p->horizontal_z[p->k][i] = 0									  ;
						}
	 
					}				   
			 }
			 else
			 {
					//A1 ==0 Ê±°´Ò»Î¬ROOF½ÇµÈÓÚ0µÄÇé¿ö×÷ËÑË÷
					TempLength = sqrt(xxx*xxx+yyy*yyy);
					SearchLength = TempLength/2 ;
	
					if(TempLength==0||zTemp==0)
					{
						p->horizontal_x[p->k][i] = xTemp  ;
						p->horizontal_y[p->k][i] = yTemp  ;
						p->horizontal_z[p->k][i] = 0	  ; 	
						continue ;	   
					}					   
					// do search in temporary coordinate
					SearchPoint = 0 ;
					TempResult =  0 ;
					count = 0;							
					do
					{
						SearchPoint += SearchLength ;	   
						//printf("search point :%f \n",SearchPoint);
						tana = SearchPoint/zTemp;
						sina = sqrt(tana*tana/(1+tana*tana));
						sinb = sina/k1;
						
						if(sinb>=1)  
						{
							SearchLength = -fabs(SearchLength)/2 ;					 
						}
						else
						{
							tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
							TempResult=SearchPoint+tanb*FocusDepth ;
							if(TempResult>TempLength)	SearchLength = -fabs(SearchLength)/2 ;
							if(TempResult<TempLength)	SearchLength =	fabs(SearchLength)/2 ;						 
						}					
						count++;		 
					}while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;		
				  
				  p->horizontal_x[p->k][i] = xTemp + SearchPoint*xxx/TempLength ;
				  p->horizontal_y[p->k][i] = yTemp + SearchPoint*yyy/TempLength ;
				  p->horizontal_z[p->k][i] = 0 ;	 
				  //g_print("No %d x=%f,y=%f,z=%f\n",i,p->horizontal_x[p->k][i],p->horizontal_y[p->k][i],p->horizontal_z[p->k][i]);
			 }
	  }  
	  //calculate the transfer time
	  for(i = ElementStart; i< ElementStop ; i++)
	  { 	
			   dis1 = sqrt((p->probe_x[p->k][i]-p->horizontal_x[p->k][i])*(p->probe_x[p->k][i]-p->horizontal_x[p->k][i])
							  +(p->probe_y[p->k][i]-p->horizontal_y[p->k][i])*(p->probe_y[p->k][i]-p->horizontal_y[p->k][i])
							  +(p->probe_z[p->k][i]-p->horizontal_z[p->k][i])*(p->probe_z[p->k][i]-p->horizontal_z[p->k][i]));
			   dis2 = sqrt((p->horizontal_x[p->k][i]-p->focus_x[p->k])*(p->horizontal_x[p->k][i]-p->focus_x[p->k])
							 +(p->horizontal_y[p->k][i]-p->focus_y[p->k])*(p->horizontal_y[p->k][i]-p->focus_y[p->k])
							 +(p->horizontal_z[p->k][i]-p->focus_z[p->k])*(p->horizontal_z[p->k][i]-p->focus_z[p->k]));
			   time[i] = dis1/c1+dis2/c2;		   
	  }
	  // get the time delay
	  timemax = time[0];
	  for(i = ElementStart ; i< ElementStop ; i++)
	  {
			if(timemax < time[i])  timemax = time[i] ;					 
	  } 
	  for(i = ElementStart; i< ElementStop ; i++)
	  {
	//		 g_printf("No.%d,time[%d] = %f,¦¤t=%d\n",i+1,i+1,time[i],(gint)((timemax - time[i])*1000000+0.5));
		   p->timedelay[p->k][i] = (gint)((timemax - time[i])*1000000+0.5); 	
	  }
	  p->G_Time[p->k] = timemax;
	  free(time);
}

/*
  Name:  cylinder_2d_roof_od_zero
  Copyright: Dopplor 
  Author: Sheng Shen
  Date: 10-05-11 13:40
  Description:   2 DIMENSION ´øROOF ½ÇµÄ OD ¾Û½¹·¨Ôò ROTATION Z = 0
  Input:  data: structure point to wedge probe .... coefficients
        angle1: refract angle
        angle2: skew angle
        depth : focus depth of sonic beam
*/
void cylinder_2d_roof_od_zero (gpointer data, gdouble angle1, gdouble angle2, gdouble depth)
{
		 DRAW_UI_P p = (DRAW_UI_P) data ;
		 
		 gdouble c1 ;			 // wave speed
		 gdouble c2 ;
		 gdouble k1 ;  
		 gdouble r  ;
		 gdouble h0 =  p->wedge_p->wg_heigh_fir ;				   // first element high
//		 gint Row      =  p->element_sel->sec_axis_ape  ;                  // element y direction numble
//         gint Column   =  p->element_sel->pri_axis_ape;                  // element x direction numble
//         if((Row*Column) > (p->probe_p->ele_num_pri * p->probe_p->ele_num_sec))
//            return;
		 int PriElementStart = p->element_sel->primary_axis_s - 1  ;
		 int PriElementNum	 = p->probe_p->ele_num_pri			  ;
		 int SecElementStart = p->element_sel->seconary_axis_s -1 ;
		 int SecElementNum	 = p->probe_p->ele_num_sec			  ;
		 int PriElementSelect= p->element_sel->pri_axis_ape 	  ;
		 int SecElementSelect= p->element_sel->sec_axis_ape 	  ;
		 int PriElementStop  = PriElementStart +  PriElementSelect;
		 int SecElementStop  = SecElementStart +  SecElementSelect;
		 
		 gdouble Intervaly = p->probe_p->sec_axis_pitch ;		   // y direction interval
		 gdouble Intervalx = p->probe_p->pri_axis_pitch ;		   // x direction interval distance
		 gdouble pri_ele_size = p->probe_p->pri_ele_size ;        
		 gdouble wg_pri_axis_reference	= p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
		 gdouble wg_sec_axis_reference	= p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
		 gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
		 gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
         gdouble length = p->wedge_p->wg_length ;                              // wedge length
		 gdouble CylinderExtDiameter = p->specimen->speci_outside_cylindrical ;// outside cylinder diameter
		 	  
		 gdouble  a1 = fabs(angle1*PI/180);						   // refract angle
		 gdouble  a2 = fabs(angle2*PI/180);						   // deflect angle
	     if(a2>PI/2) a2 = PI-a2 ;
		 
		 gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180	 ; // roofangle   y-z platform
		 gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180 ; // wedgeangle  x-z platform	   
		 gdouble  FocusDepth = depth;							   //  true focus depth
 
		 // refraction calculation 
		 gdouble aSinTemp;
		 gdouble aProjection;
		 gdouble bProjection;
		 gdouble zHightTemp;
		 
		 gdouble tempangle1;
		 gdouble tempangle2;
		 gdouble tempangle3;

		 gdouble tempFocusxxx;
		 gdouble tempFocusyyy;
		 gdouble tempFocuszzz;
		 gdouble angle_rotate;
		 
		 gdouble xTemp, yTemp, zTemp ;
		 gdouble x0,y0,z0;			  // element center coordinate
		 //  element offset in each direction
		 gdouble x;
		 gdouble y;
		 gdouble z;
		 gdouble d;
		 gdouble s_x;
		 gdouble s_y;
		 gdouble s_zy;
		 gdouble s_zx;	   
		 // variable for search method
		 gdouble SearchLength , SearchAngle;
		 gdouble TempAngle;
		 gdouble TempResult;
		 gdouble SkewAngleTemp;
		 gdouble SearchPoint ;
		 gdouble TempLength  ;
		 gdouble tana,tanb,sina,sinb ;
		 
         gdouble r_depth;
         gdouble a;
		 gdouble b;
		 
		 gdouble xxx;
		 gdouble yyy;
		 gdouble zzz;
		 
		 gint i, j; 
		 int count;
		 // variable for time calculation
		 gdouble dis1;
		 gdouble dis2;
		 gdouble timemax ;
 
		gdouble *time = malloc(PriElementNum*SecElementNum*sizeof(gdouble));
	    if(p->probe_p->D1_D2 == 0) {SecElementNum = 1;  SecElementStart = 0; SecElementStop = 1;}
		 
		if(PriElementStop > PriElementNum )  return ;
		if(SecElementStop > SecElementNum )  return ;	

		r = CylinderExtDiameter/2.0 ;
		// kill the impossible condition
		if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
	 
		if(p->probe_p->transmi_trans_longi==0)
        {   
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
            c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
        }                                           
        else                                 
        {
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
            c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
        }
		 // refract coefficient
		 k1 = c1/c2 ;

		 // element location offset calculate
		 // ÔÚROOF½Ç²»µÈÓÚ0Ê±,ÔÚ´¹Ö±ÓÚWEDGE ½ÇÉÏ±ß·½ÏòÉÏÃ¿×ßÒ»¶Î¾àÀë
         // ¶ÔÓ¦µÄ X Y Z Èý¸ö·½ÏòÉÏ¶¼»áÓÐÒ»¸öÎ»ÖÃ±ä»¯SX SY SZ
		 if((wedgeangle != 0) && (roofangle != 0))
		 {
			  x = 1;
			  y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
			  z = y*tan(roofangle) ;
			  d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
			  s_x  = -Intervaly/d	 ;
			  s_y  = -Intervaly*y/d   ;
			  s_zy	= -Intervaly*(z-tan(wedgeangle))/d	 ;			
		 }
		 else
		 {	 
			  s_y = -Intervaly*cos(roofangle);
			  s_x = 0 ;
			  s_zy = -Intervaly*sin(roofangle);
		 }	   

	     //calc offset generated by element selection
		 z0 = SecElementStart*s_zy - PriElementStart*Intervalx*sin(wedgeangle);
		 x0 = Intervalx*cos(wedgeangle)*PriElementStart + SecElementStart*s_x ;
		 y0 = s_y*SecElementStart   ;

		 // center probe element	(x0,y0,z0)			  
		 z0 = -(z0 +h0 + Intervalx*(PriElementSelect - 1)*sin(wedgeangle)/2 - s_zy*(SecElementSelect -1)/2) -sqrt(CylinderExtDiameter*CylinderExtDiameter - length*length)/2;
		 x0 = x0 -length/2 + wg_pri_elem_offset_fir + Intervalx*(PriElementSelect - 1)*cos(wedgeangle)/2 + (SecElementSelect-1)*s_x/2 ;
         if(roofangle<0)
		     wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;
		 y0 = y0 - wg_sec_axis_reference - wg_sec_elem_offset_fir + s_y*(SecElementSelect-1)/2 ;
         //ÒÔÏÂºÍ1Î¬CylinderÇé¿öÀàËÆ.
         //Ö»ÊÇ½«3Î¬µÄ×ø±êÍ¶Ó°µ½X-ZÃæ
         //¿Õ¼ä½Ç¶ÈºÍÍ¶Ó°½ÇÆ«×ª½ÇÖ®¼äµÄ¹ØÏµ
         // tan(Projection) = tan(SpaceAngle)*cos(SkewAngle);
		 // get focus point coordinate 
		 aSinTemp = asin(k1*sin(a1));
		 aProjection = atan(tan(aSinTemp)*cos(a2));
		 zHightTemp = sqrt(z0*z0 + x0*x0);
		 
		 tempangle1 = asin(r*sin(aProjection)/zHightTemp);
		 tempangle2 = aProjection - tempangle1;   //tempangle2  keep for the below calculation
         // refract point
		 xxx = r * sin(tempangle2);
		 zzz = r * cos(tempangle2);
		 
         bProjection = atan(tan(a1)*cos(a2));
         tempangle3 = asin(sin(bProjection)*r/(r-FocusDepth));  // tempangle3 is sure to be large than 90 degree
		 tempangle1 = tempangle3 - bProjection               ;
		 // µ±ÕÛÉä½ÇºÍÆ«×ª½ÇÉè¶¨,¼È¿ÉÇóµÃ×î´ó¾Û½¹Éî¶È.
		 // R*SIN(PROJECTION)
         //if(FocusDepth>r*sin(bProjection))  FocusDepth =  r*sin(bProjection);
		 //g_print("MaxDepth:%f\n", r*sin(bProjection))        ;  // when a1 and a2 is setted, there will exist a max focus depth		 
		 tempFocusxxx = (r-FocusDepth) * sin(tempangle1+tempangle2) ;
		 tempFocuszzz = (r-FocusDepth) * cos(tempangle1+tempangle2) ;
         tempFocusyyy = zHightTemp*sin(tempangle2)+sin(tempangle1)*(r-FocusDepth);         
		 tempFocusyyy = tempFocusyyy*tan(a2) ;
		 //Ö®Ç°  gdouble  a1 = fabs(angle1*PI/180); 						   // refract angle
		 // 		   gdouble	  a2 = fabs(angle2*PI/180); 						   // deflect angle
		 // 		   if(a2>PI/2)	a2 = PI-a2 ;
		 //µ±a1 a2	  ¶¼´óÓÚ0Ê±,Ïà¶ÔÓÚÌ½Í·ÖÐÐÄµãµÄ×ø±êÏµµÄÈëÉäµã×ø±ê
		 // TEMPFOCUSXXX TEMPFOCUSYYY TEMPFOCUSZZZ
		 //ÇóµÃÁÙÊ±×ø±êºó,ÔÙ¸ù¾Ýa1 a2µÄÊµ¼ÊÇé¿ö,½«×ø±êµÄÕý¸ºÖµÉè¶¨
         if(angle1>=0)
         {
             if(angle2>=0)
             {
                 if(angle2>90)
                 {
                      tempFocusxxx=-tempFocusxxx;
                 }
             }
			 else
			 {
			     if(a2>PI/2)
			     {
			          tempFocusxxx=-tempFocusxxx;
			     }
				 tempFocusyyy = -tempFocusyyy;
			 }
         }
		 else
		 {
		     if(angle2>=0)
             {
                 if(angle2>90)
                 {
                      tempFocusyyy = -tempFocusyyy;
                 }
				 else
				 {
				      tempFocusyyy=-tempFocusyyy;
					  tempFocusxxx = -tempFocusxxx;
				 }
             }
			 else
			 {
			     if(a2<PI/2)
			     {
			          tempFocusxxx=-tempFocusxxx;
			     }		 
			 }
		 }
		 //×ø±êÐý×ª,½«½¹µã×ø±êÓÉÖÐÐÄÌ½Í·×ø±êÐý×ªµ½Êµ¼Ê×ø±ê
		 p->focus_y[p->k]   = y0 - tempFocusyyy    ;
		 angle_rotate = -asin(x0/zHightTemp) ;
		 p->focus_x[p->k] = tempFocusxxx*cos(angle_rotate) - tempFocuszzz*sin(angle_rotate);
		 p->focus_z[p->k] = -(tempFocusxxx*sin(angle_rotate) + tempFocuszzz*cos(angle_rotate));
		 //µÚÒ»¸öÌ½Í·µÄ×ø±ê
		 p->probe_x[p->k][0] =   -length/2 + wg_pri_elem_offset_fir ;
		 p->probe_y[p->k][0] =   -wg_sec_axis_reference - wg_sec_elem_offset_fir;
		 p->probe_z[p->k][0] =   -h0	- sqrt(CylinderExtDiameter*CylinderExtDiameter- length*length)/2;	  
		 tempangle2 = asin(p->focus_x[p->k]/(r-FocusDepth)) ;
		 r_depth    = r - FocusDepth ;
		 
		 for(i = PriElementStart; i< PriElementStop; i++)
		 {
			  for(j = SecElementStart; j< SecElementStop; j++)
			  {
					//get elements' coordinates
					zTemp = p->probe_z[p->k][0] + j*s_zy - i*Intervalx*sin(wedgeangle);
					xTemp = p->probe_x[p->k][0] + Intervalx*cos(wedgeangle)*i + j*s_x ;
					yTemp = p->probe_y[p->k][0] + s_y*j;
					p->probe_x[p->k][i*SecElementNum+j] = xTemp  ;
					p->probe_y[p->k][i*SecElementNum+j] = yTemp  ;
					p->probe_z[p->k][i*SecElementNum+j] = zTemp  ;
					if((xTemp*xTemp+zTemp*zTemp)<r*r)
					{
					   	p->horizontal_x[p->k][i*SecElementNum+j] = xTemp  ;
					    p->horizontal_y[p->k][i*SecElementNum+j] = yTemp ;
					    p->horizontal_z[p->k][i*SecElementNum+j] = zTemp ;
					    continue ;
					}
                    count = 0;
					zHightTemp   = sqrt(xTemp*xTemp + zTemp*zTemp);
					angle_rotate = -asin(xTemp/zHightTemp)        ;
					tempangle3   = tempangle2 + angle_rotate      ;
                    if(tempangle3 == 0)
                    { // µ±Í¶Ó°½ÇÎª0Ê±,ÔÚY·½Ïò×÷ËÑË÷.ÀàËÆÓÚÒ»Î¬ËÑË÷
					    xxx = 0;
						zzz = r ;			
					    if(yTemp == p->focus_y[p->k])
					       yyy = yTemp ;
					    else 
					    {
					         zTemp = zHightTemp - r;
							 TempLength = fabs(yTemp-p->focus_y[p->k]);
							 SearchLength = TempLength/2 ;
							 SearchPoint = 0 ;
							 TempResult = 0 ;
                             do
                             {
                                  SearchPoint += SearchLength ;      
                                   //printf("search point :%f \n",SearchPoint);
                                  tana = SearchPoint/zTemp;
                                  sina = sqrt(tana*tana/(1+tana*tana));
                                  sinb = sina/k1;				   
                                  if(sinb>=1)  
                                  {
                                       SearchLength = -fabs(SearchLength)/2 ;                   
                                  }
                                  else
                                  {
                                       tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
                                       TempResult=SearchPoint+tanb*FocusDepth ;
                                       if(TempResult>TempLength)   SearchLength = -fabs(SearchLength)/2 ;
                                       if(TempResult<TempLength)   SearchLength =  fabs(SearchLength)/2 ;                 
                                  }                   
                                  count++;         
                             }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;   

                             yyy = yTemp + SearchPoint*(p->focus_y[p->k]-yTemp)/fabs(p->focus_y[p->k] - yTemp); 
							 
					    }
                        
					    p->horizontal_x[p->k][i*SecElementNum+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)  ;
					    p->horizontal_y[p->k][i*SecElementNum+j] = yyy ;
					    p->horizontal_z[p->k][i*SecElementNum+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate));
						continue ;
                    }
					tempangle1   = fabs(tempangle3);
					SearchLength = tempangle1/2                   ;
					SearchAngle  = 0                              ;
					TempResult   = 0                              ;
					
					yyy = fabs(p->focus_y[p->k] - yTemp) ;
					//TempResult = TempLength + SearchGate ;
					do
					{// ËÑË÷X-ZÍ¶Ó°½Ç
						  SearchAngle += SearchLength ; 	 
						  //printf("search point :%f \n",SearchPoint);
						  aProjection = atan(zHightTemp*sin(SearchAngle)/(zHightTemp*cos(SearchAngle)-r));
						  SkewAngleTemp = atan(yyy/(zHightTemp*sin(SearchAngle)+(r-FocusDepth)*sin(tempangle1-SearchAngle)));
                          a = atan(tan(aProjection)/cos(SkewAngleTemp));
                          if(fabs(sin(a)/k1)>=1)
                          {
                                 SearchLength = -fabs(SearchLength)/2 ;
                          }
                          else
                          {						  
                             b = asin(sin(a)/k1)                          ;
						     bProjection = atan(tan(b)*cos(SkewAngleTemp));
                             TempResult  = r*sin(bProjection)/sin(bProjection+tempangle1-SearchAngle)  ;
						     if(TempResult>r_depth)   SearchLength = -fabs(SearchLength)/2 ;
                             if(TempResult<r_depth)   SearchLength =  fabs(SearchLength)/2 ;
                          }
						  count++;
					}while( (fabs(TempResult-r_depth) > SearchGate) && ( count<=20 )) ;	   
					// translate into common coordiniate
                    if(tempangle3<=0)
					       xxx = -r*sin(SearchAngle) ;
					else   
						   xxx = r*sin(SearchAngle);
					
					if(yTemp>p->focus_y[p->k])
					    yyy = yTemp - sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp) ;
					else 
					    yyy = yTemp + sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp);
                    zzz = r*cos(SearchAngle);
					p->horizontal_x[p->k][i*SecElementNum+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)  ;
					p->horizontal_y[p->k][i*SecElementNum+j] = yyy ;
					p->horizontal_z[p->k][i*SecElementNum+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate)) ;				   
			  }
		 }
		//calculate the transfer time
		for(i = PriElementStart; i< PriElementStop; i++)
		{
			for(j = SecElementStart; j< SecElementStop; j++)
			{
				 dis1 = sqrt((p->probe_x[p->k][i*SecElementNum+j]-p->horizontal_x[p->k][i*SecElementNum+j])*(p->probe_x[p->k][i*SecElementNum+j]-p->horizontal_x[p->k][i*SecElementNum+j])
								+(p->probe_y[p->k][i*SecElementNum+j]-p->horizontal_y[p->k][i*SecElementNum+j])*(p->probe_y[p->k][i*SecElementNum+j]-p->horizontal_y[p->k][i*SecElementNum+j])
							   +(p->probe_z[p->k][i*SecElementNum+j]-p->horizontal_z[p->k][i*SecElementNum+j])*(p->probe_z[p->k][i*SecElementNum+j]-p->horizontal_z[p->k][i*SecElementNum+j]));
				 dis2 = sqrt((p->horizontal_x[p->k][i*SecElementNum+j]-p->focus_x[p->k])*(p->horizontal_x[p->k][i*SecElementNum+j]-p->focus_x[p->k])
							   +(p->horizontal_y[p->k][i*SecElementNum+j]-p->focus_y[p->k])*(p->horizontal_y[p->k][i*SecElementNum+j]-p->focus_y[p->k])
							   +(p->horizontal_z[p->k][i*SecElementNum+j]-p->focus_z[p->k])*(p->horizontal_z[p->k][i*SecElementNum+j]-p->focus_z[p->k]));
				 time[i*SecElementNum+j] = dis1/c1+dis2/c2;		   
			}
		}
		// get the time delay
		timemax = time[PriElementStart*SecElementNum + SecElementStart]; 
		
		for(i=PriElementStart; i< PriElementStop ; i++)
		{
			for(j = SecElementStart; j< SecElementStop; j++)
			{
				  if(timemax < time[i*SecElementNum + j ])	timemax = time[i*SecElementNum + j ] ;
			}
		}
		
		g_print("***********\n") ;
		g_print("	 x1 x2 x3\n")  ;
		g_print("y1  0	3  6  \n") ;
		g_print("y2  1	4  7  \n") ;
		g_print("y3  2	5  8  \n") ;
		g_print("***********\n");	   
		
		for(i=PriElementStart; i< PriElementStop ; i++)
		{
			for(j = SecElementStart; j< SecElementStop; j++)
			{
				 g_printf("No.[%d][%d],time = %f,¦¤t=%d\n",i+1,j+1,time[i*SecElementNum + j ],(gint)((timemax - time[i*SecElementNum + j ])*1000000+0.5));
				 p->timedelay[p->k][i*SecElementNum + j] = (gint)((timemax - time[i*SecElementNum + j ])*1000000+0.5)								   ;
			}
		}
		p->G_Time[p->k] = timemax;
		free(time);


}




/*
  Name:  cylinder_2d_roof_id
  Copyright: Dopplor 
  Author: Sheng Shen
  Date: 17-03-11 13:40
  Description:   2 DIMENSION ´øROOF ½ÇµÄ ID ¾Û½¹·¨Ôò 
  Input:  data: structure point to wedge probe .... coefficients
        angle1: refract angle
        angle2: skew angle
        depth : focus depth of sonic beam
*/
void cylinder_2d_roof_id(gpointer data, gdouble angle1, gdouble angle2 , gdouble depth)
{
      
	   DRAW_UI_P p = (DRAW_UI_P) data ;
	   
	   gdouble c1 ; 		   // wave speed
	   gdouble c2 ;
	   gdouble k1 ;  
	   gdouble r  ;
	   gdouble h0 =  p->wedge_p->wg_heigh_fir ; 				 // first element high
	   //gint Row      =  p->element_sel->sec_axis_ape  ;                  // element y direction numble
       //gint Column   = p->element_sel->pri_axis_ape;                  // element x direction numble
       //if((Row*Column) > (p->probe_p->ele_num_pri * p->probe_p->ele_num_sec))
       //     return;
	   int PriElementStart = p->element_sel->primary_axis_s -1	;
	   int PriElementNum   = p->probe_p->ele_num_pri			;
	   int SecElementStart = p->element_sel->seconary_axis_s -1 ;
	   int SecElementNum   = p->probe_p->ele_num_sec			;
	   int PriElementSelect= p->element_sel->pri_axis_ape		;
	   int SecElementSelect= p->element_sel->sec_axis_ape		;
	   int PriElementStop  = PriElementStart +	PriElementSelect;
	   int SecElementStop  = SecElementStart +	SecElementSelect;
	   
	   gdouble Intervaly = p->probe_p->sec_axis_pitch ; 		 // y direction interval
	   gdouble Intervalx = p->probe_p->pri_axis_pitch ; 		 // x direction interval distance
	   gdouble pri_ele_size = p->probe_p->pri_ele_size ;		
	   gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	   gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	   gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
	   gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	   gdouble length = p->wedge_p->wg_length ; 							 // wedge length
	   gdouble CylinderIntDiameter = p->specimen->speci_inside_cylindrical ;// outside cylinder diameter
	   
	  
	   gdouble	a1 = fabs(angle1*PI/180); 							 // refract angle
	   gdouble	a2 = fabs(angle2*PI/180); 							 // deflect angle
	   if(a2>PI/2)  a2 = PI-a2 ;
	   gdouble	roofangle = p->wedge_p->wg_roof_angle*PI/180   ; // roofangle	y-z platform
	   gdouble	wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ; // wedgeangle	x-z platform	 
	   gdouble	FocusDepth = depth; 							 //  true focus depth
	  
	   // refraction calculation 
	   gdouble aSinTemp;
	   gdouble aProjection;
	   gdouble bProjection;
	   gdouble zHightTemp;
	   
	   gdouble tempangle1;
	   gdouble tempangle2;
	   gdouble tempangle3;
	  
	   gdouble tempFocusxxx;
	   gdouble tempFocusyyy;
	   gdouble tempFocuszzz;
	   gdouble angle_rotate;
	   
	   gdouble xTemp, yTemp, zTemp ;
	   gdouble x0,y0,z0;			                               // element center coordinate
	   //  element offset in each direction
	   gdouble x;
	   gdouble y;
	   gdouble z;
	   gdouble d;
	   gdouble s_x;
	   gdouble s_y;
	   gdouble s_zy;
	   gdouble s_zx;	 
	   // variable for search method
	   gdouble SearchLength , SearchAngle;
	   gdouble TempAngle;
	   gdouble TempResult;
	   gdouble SkewAngleTemp;
	   gdouble SearchPoint ;
	   gdouble TempLength  ;
	   gdouble tana,tanb,sina,sinb ;
	   gdouble r_depth;
	   gdouble a;
	   gdouble b;
	   
	   gdouble xxx;
	   gdouble yyy;
	   gdouble zzz;
	   
	   gint i, j; 
	   int count;
	   // variable for time calculation
	   gdouble dis1;
	   gdouble dis2;
	   gdouble timemax ;
	   
	   gdouble *time = malloc(PriElementNum*SecElementNum*sizeof(gdouble));
	   if(p->probe_p->D1_D2 == 0) {SecElementNum = 1;  SecElementStart = 0; SecElementStop = 1;}
		
	   if(PriElementStop > PriElementNum )	return ;
	   if(SecElementStop > SecElementNum )	return ;   

	   r = CylinderIntDiameter/2.0 ;
	   // kill the impossible condition
	   if(wedgeangle == PI/2 || roofangle == PI/2)	return ;
	  
	   if(p->probe_p->transmi_trans_longi==0)
        {   
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
            c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
        }                                           
        else                                 
        {
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
            c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
        }
	   // refract coefficient
	   k1 = c1/c2 ;
	   // element location offset calculate
	   // ÔÚROOF½Ç²»µÈÓÚ0Ê±,ÔÚ´¹Ö±ÓÚWEDGE ½ÇÉÏ±ß·½ÏòÉÏÃ¿×ßÒ»¶Î¾àÀë
       // ¶ÔÓ¦µÄ X Y Z Èý¸ö·½ÏòÉÏ¶¼»áÓÐÒ»¸öÎ»ÖÃ±ä»¯SX SY SZ
	   if((wedgeangle != 0) && (roofangle != 0))
	   {
			x = 1;
			y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
			z = y*tan(roofangle) ;
			d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
			s_x  = -Intervaly/d     ;
			s_y  = -Intervaly*y/d	;
			s_zy  = -Intervaly*(z-tan(wedgeangle))/d   ;		  
	   }
	   else
	   {   
			s_y = -Intervaly*cos(roofangle);
			s_x = 0 ;
			s_zy = -Intervaly*sin(roofangle);
	   }	 

	   //calc offset generated by element selection
	   z0 = SecElementStart*s_zy - PriElementStart*Intervalx*sin(wedgeangle);
	   x0 = Intervalx*cos(wedgeangle)*PriElementStart + SecElementStart*s_x ;
	   y0 = s_y*SecElementStart   ;
	   // center probe element	  (x0,y0,z0)			
	   z0 = -(z0 + h0 + Intervalx*(PriElementSelect - 1)*sin(wedgeangle)/2 - s_zy*(SecElementSelect-1)/2) + sqrt(CylinderIntDiameter*CylinderIntDiameter - length*length)/2;
	   x0 = x0 - length/2 + wg_pri_elem_offset_fir + Intervalx*(PriElementSelect - 1)*cos(wedgeangle)/2 + (SecElementSelect-1)*s_x/2 ;
       if(roofangle<0)
		 wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;
	   y0 = y0 - wg_sec_axis_reference - wg_sec_elem_offset_fir + s_y*(SecElementSelect-1)/2 ;
	  
	   // get focus point coordinate
       //ÒÔÏÂºÍ1Î¬CylinderÇé¿öÀàËÆ.
       //Ö»ÊÇ½«3Î¬µÄ×ø±êÍ¶Ó°µ½X-ZÃæ
       //¿Õ¼ä½Ç¶ÈºÍÍ¶Ó°½ÇÆ«×ª½ÇÖ®¼äµÄ¹ØÏµ
       // tan(Projection) = tan(SpaceAngle)*cos(SkewAngle);
	   aSinTemp = asin(k1*sin(a1));
	   aProjection = atan(tan(aSinTemp)*cos(a2));
	   zHightTemp = sqrt(z0*z0 + x0*x0);
	   
	   tempangle1 = asin(r*sin(aProjection)/zHightTemp);
	   tempangle2 = tempangle1 - aProjection;	//tempangle2  keep for the below calculation
	   // refract point
	   xxx = r * sin(tempangle2);
	   zzz = r * cos(tempangle2);
	   
	   bProjection = atan(tan(a1)*cos(a2));
	   tempangle3 = asin(sin(bProjection)*r/(r+FocusDepth)); 
	   tempangle1 = bProjection - tempangle3			   ;  
	   
	   tempFocusxxx = (r+FocusDepth) * sin(tempangle1+tempangle2)              ;
	   tempFocuszzz = -(r+FocusDepth) * cos(tempangle1+tempangle2)             ;
	   tempFocusyyy = zHightTemp*sin(tempangle2)+sin(tempangle1)*(r+FocusDepth);
	   tempFocusyyy = tempFocusyyy*tan(a2)                                     ;
	   //Ö®Ç°  gdouble	a1 = fabs(angle1*PI/180); 							 // refract angle
	   //            gdouble	a2 = fabs(angle2*PI/180); 							 // deflect angle
	   //            if(a2>PI/2)  a2 = PI-a2 ;
	   //µ±a1 a2	¶¼´óÓÚ0Ê±,Ïà¶ÔÓÚÌ½Í·ÖÐÐÄµãµÄ×ø±êÏµµÄÈëÉäµã×ø±ê
	   // TEMPFOCUSXXX TEMPFOCUSYYY TEMPFOCUSZZZ
	   //ÇóµÃÁÙÊ±×ø±êºó,ÔÙ¸ù¾Ýa1 a2µÄÊµ¼ÊÇé¿ö,½«×ø±êµÄÕý¸ºÖµÉè¶¨
	   if(angle1>=0)
	   {
		   if(angle2>=0)
		   {
			   if(angle2>90)
			   {
					tempFocusxxx=-tempFocusxxx;
			   }
		   }
		   else
		   {
			   if(a2>PI/2)
			   {
					tempFocusxxx=-tempFocusxxx;
			   }
			   tempFocusyyy = -tempFocusyyy;
		   }
	   }
	   else
	   {
		   if(angle2>=0)
		   {
			   if(angle2>90)
			   {
					tempFocusyyy = -tempFocusyyy;
			   }
			   else
			   {
					tempFocusyyy=-tempFocusyyy;
					tempFocusxxx = -tempFocusxxx;
			   }
		   }
		   else
		   {
			   if(a2<PI/2)
			   {
					tempFocusxxx=-tempFocusxxx;
			   }	   
		   }
	   }

	   p->focus_y[p->k]	= y0 - tempFocusyyy                                        ;
	   angle_rotate = asin(x0/zHightTemp)                                      ;
	   p->focus_x[p->k] = tempFocusxxx*cos(angle_rotate) - tempFocuszzz*sin(angle_rotate);
	   p->focus_z[p->k] = -(tempFocusxxx*sin(angle_rotate) + tempFocuszzz*cos(angle_rotate));
	   
	   p->probe_x[p->k][0] =	 -length/2 + wg_pri_elem_offset_fir ;
	   p->probe_y[p->k][0] =	 -wg_sec_axis_reference - wg_sec_elem_offset_fir;
	   p->probe_z[p->k][0] =	 -h0  + sqrt(CylinderIntDiameter*CylinderIntDiameter- length*length)/2;
	   tempangle2 = asin(p->focus_x[p->k]/(r+FocusDepth)) ;
	   r_depth	  = r + FocusDepth ;
	   
	   for(i = PriElementStart; i< PriElementStop; i++)
	   {
			for(j = SecElementStart; j< SecElementStop; j++)
			{
				  //get elements' coordinates
				  zTemp = p->probe_z[p->k][0] + j*s_zy - i*Intervalx*sin(wedgeangle);
				  xTemp = p->probe_x[p->k][0] + Intervalx*cos(wedgeangle)*i + j*s_x ;
				  yTemp = p->probe_y[p->k][0] + s_y*j;
				  p->probe_x[p->k][i*SecElementNum+j] = xTemp  ;
				  p->probe_y[p->k][i*SecElementNum+j] = yTemp  ;
				  p->probe_z[p->k][i*SecElementNum+j] = zTemp  ;
				  if((xTemp*xTemp+zTemp*zTemp)>r*r)
				  {
					   	p->horizontal_x[p->k][i*SecElementNum+j] = xTemp ;
					    p->horizontal_y[p->k][i*SecElementNum+j] = yTemp ;
					    p->horizontal_z[p->k][i*SecElementNum+j] = zTemp ;
					    continue ;
				  }
                  count = 0;
				  zHightTemp   = sqrt(xTemp*xTemp + zTemp*zTemp);
				  angle_rotate = asin(xTemp/zHightTemp)		    ;
				  tempangle3   = tempangle2 - angle_rotate		;	  
				  
				  if(tempangle3 == 0)
				  {// µ±Í¶Ó°½ÇÎª0Ê±,ÔÚY·½Ïò×÷ËÑË÷.ÀàËÆÓÚÒ»Î¬ËÑË÷
					  xxx = 0;
					  zzz = -r ; 		  
					  if(yTemp == p->focus_y[p->k])
						 yyy = yTemp ;
					  else 
					  {    
						   zTemp = r - zHightTemp;
						   TempLength= fabs(yTemp-p->focus_y[p->k]);
						   SearchLength = TempLength/2 ;
						   SearchPoint  = 0 ;
						   TempResult = 0 ;
						   do
						   {
								SearchPoint += SearchLength ;	   
								tana = SearchPoint/zTemp;
								sina = sqrt(tana*tana/(1+tana*tana));
								sinb = sina/k1; 				 
								if(sinb>=1)  
								{
									 SearchLength = -fabs(SearchLength)/2 ; 				  
								}
								else
								{
									 tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
									 TempResult=SearchPoint+tanb*FocusDepth ;
									 if(TempResult>TempLength)	 SearchLength = -fabs(SearchLength)/2 ;
									 if(TempResult<TempLength)	 SearchLength =  fabs(SearchLength)/2 ; 				
								}					
								count++;		 
						   }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;	
						   yyy = yTemp + SearchPoint*(p->focus_y[p->k]-yTemp)/fabs(p->focus_y[p->k] - yTemp); 
					  }
					  p->horizontal_x[p->k][i*SecElementNum+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)  ;
					  p->horizontal_y[p->k][i*SecElementNum+j] = yyy ;
					  p->horizontal_z[p->k][i*SecElementNum+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate));
					  continue ;
				  }

				  tempangle1   = fabs(tempangle3)               ;
				  SearchLength = tempangle1/2					;
				  SearchAngle  = 0								;
				  TempResult   = 0								;
				  yyy = fabs(p->focus_y[p->k] - yTemp) ;
				  do
				  {// ËÑË÷X-ZÍ¶Ó°½Ç
						SearchAngle += SearchLength ;	   
						//printf("search point :%f \n",SearchPoint);
						aProjection = atan(zHightTemp*sin(SearchAngle)/(r - zHightTemp*cos(SearchAngle)));
						SkewAngleTemp = atan(yyy/(zHightTemp*sin(SearchAngle)+(r+FocusDepth)*sin(tempangle1-SearchAngle)));
						a = atan(tan(aProjection)/cos(SkewAngleTemp));
						if(fabs(sin(a)/k1)>=1)
						{
							   SearchLength = -fabs(SearchLength)/2 ;
						}
						else
						{						
						   b = asin(sin(a)/k1)							;
						   bProjection = atan(tan(b)*cos(SkewAngleTemp));
						   TempResult  = r*sin(bProjection)/sin(bProjection-tempangle1+SearchAngle);
						   if(TempResult>r_depth)	SearchLength =  fabs(SearchLength)/2 ;
						   if(TempResult<r_depth)	SearchLength =	-fabs(SearchLength)/2 ;
						}
						count++;
				  }while( (fabs(r_depth-TempResult) > SearchGate) && ( count<=20 )) ;	 
				  // translate into common coordiniate
                  xxx = (tempangle3<=0)?-r*sin(SearchAngle):r*sin(SearchAngle);				  
				  if(yTemp>p->focus_y[p->k])
					  yyy = yTemp - sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp) ;
				  else 
					  yyy = yTemp + sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp);
				  zzz = -r*cos(SearchAngle);
				  p->horizontal_x[p->k][i*SecElementNum+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)  ;
				  p->horizontal_y[p->k][i*SecElementNum+j] = yyy ;
				  p->horizontal_z[p->k][i*SecElementNum+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate) ) ;				 
			}
	   }
	  //calculate the transfer time
	  for(i = PriElementStart; i< PriElementStop; i++)
	  {
		  for(j = SecElementStart; j< SecElementStop; j++)
		  {
			   dis1 = sqrt((p->probe_x[p->k][i*SecElementNum+j]-p->horizontal_x[p->k][i*SecElementNum+j])*(p->probe_x[p->k][i*SecElementNum+j]-p->horizontal_x[p->k][i*SecElementNum+j])
							  +(p->probe_y[p->k][i*SecElementNum+j]-p->horizontal_y[p->k][i*SecElementNum+j])*(p->probe_y[p->k][i*SecElementNum+j]-p->horizontal_y[p->k][i*SecElementNum+j])
							 +(p->probe_z[p->k][i*SecElementNum+j]-p->horizontal_z[p->k][i*SecElementNum+j])*(p->probe_z[p->k][i*SecElementNum+j]-p->horizontal_z[p->k][i*SecElementNum+j]));
			   dis2 = sqrt((p->horizontal_x[p->k][i*SecElementNum+j]-p->focus_x[p->k])*(p->horizontal_x[p->k][i*SecElementNum+j]-p->focus_x[p->k])
							 +(p->horizontal_y[p->k][i*SecElementNum+j]-p->focus_y[p->k])*(p->horizontal_y[p->k][i*SecElementNum+j]-p->focus_y[p->k])
							 +(p->horizontal_z[p->k][i*SecElementNum+j]-p->focus_z[p->k])*(p->horizontal_z[p->k][i*SecElementNum+j]-p->focus_z[p->k]));
			   time[i*SecElementNum+j] = dis1/c1+dis2/c2;		 
		  }
	  }
	  // get the time delay
	  timemax = time[PriElementStart*SecElementNum + SecElementStart]; 
	  
	  for(i=PriElementStart; i< PriElementStop ; i++)
	  {
		  for(j = SecElementStart; j< SecElementStop; j++)
		  {
				if(timemax < time[i*SecElementNum + j ])  timemax = time[i*SecElementNum + j ] ;
		  }
	  }
	  
	  g_print("***********\n") ;
	  g_print("    x1 x2 x3\n")  ;
	  g_print("y1  0  3  6	\n") ;
	  g_print("y2  1  4  7	\n") ;
	  g_print("y3  2  5  8	\n") ;
	  g_print("***********\n"); 	 
	  
	  for(i=PriElementStart; i< PriElementStop ; i++)
	  {
		  for(j = SecElementStart; j< SecElementStop; j++)
		  {
			   g_printf("No.[%d][%d],time = %f,¦¤t=%d\n",i+1,j+1,time[i*SecElementNum + j ],(gint)((timemax - time[i*SecElementNum + j ])*1000000+0.5));
			   p->timedelay[p->k][i*SecElementNum + j] = (gint)((timemax - time[i*SecElementNum + j ])*1000000+0.5) 								 ;
		  }
	  }
	  p->G_Time[p->k] = timemax;
	  free(time);

}

void cylinder_2d_roof_od_pr(gpointer data, gdouble angle1, gdouble angle2, gdouble depth)
{
	 DRAW_UI_P p = (DRAW_UI_P) data ;
	 
	 gdouble c1 ;			 // wave speed
	 gdouble c2 ;
	 gdouble k1 ;  
	 gdouble r	;
	 gdouble h0 =  p->wedge_p->wg_heigh_fir ;				   // first element high
	 gint Row      =  p->element_sel->sec_axis_ape  ;                  // element y direction numble
     gint Column   = p->element_sel->pri_axis_ape;                  // element x direction numble
     if((Row*Column) > (p->probe_p->ele_num_pri * p->probe_p->ele_num_sec))
            return;
	 
	 gdouble Intervaly = p->probe_p->sec_axis_pitch ;		   // y direction interval
	 gdouble Intervalx = p->probe_p->pri_axis_pitch ;		   // x direction interval distance
	 gdouble pri_ele_size = p->probe_p->pri_ele_size ;		  
	 gdouble wg_pri_axis_reference	= p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	 gdouble wg_sec_axis_reference	= p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	 gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
	 gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	 gdouble length = p->wedge_p->wg_length ;							   // wedge length
	 gdouble CylinderExtDiameter = p->specimen->speci_outside_cylindrical ;// outside cylinder diameter
	 gdouble separation = p->wedge_r->wg_separation ;
	
	gdouble  a1 = fabs(angle1*PI/180);						  // refract angle
	gdouble  a2 = fabs(angle2*PI/180);						  // deflect angle
	if(a2>PI/2) a2 = PI-a2 ;

	 gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180	 ; // roofangle   y-z platform
	 gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ; // wedgeangle  x-z platform	   
	 gdouble  FocusDepth = depth;							   //  true focus depth
	
	 // refraction calculation 
	 gdouble aSinTemp;
	 gdouble aProjection;
	 gdouble bProjection;
	 gdouble zHightTemp;
	 
	 gdouble tempangle1;
	 gdouble tempangle2;
	 gdouble tempangle3;
	
	 gdouble tempFocusxxx;
	 gdouble tempFocusyyy;
	 gdouble tempFocuszzz;
	 gdouble angle_rotate;
	 
	 gdouble xTemp, yTemp, zTemp ;
	 gdouble x0,y0,z0;			  // element center coordinate
	 //  element offset in each direction
	 gdouble x;
	 gdouble y;
	 gdouble z;
	 gdouble d;
	 gdouble s_x;
	 gdouble s_y;
	 gdouble s_zy;
	 gdouble s_zx;	   
	 // variable for search method
	 gdouble SearchLength , SearchAngle;
	 gdouble TempAngle;
	 gdouble TempResult;
	 gdouble SkewAngleTemp;
	 gdouble SearchPoint ;
	 gdouble TempLength  ;
	 gdouble tana,tanb,sina,sinb ;
	 
	 gdouble r_depth;
	 gdouble a;
	 gdouble b;
	 
	 gdouble xxx;
	 gdouble yyy;
	 gdouble zzz;
	 
	 gint i, j; 
	 int count;
	 // variable for time calculation
	 gdouble dis1;
	 gdouble dis2;
	 gdouble timemax ;
	 gdouble *time = malloc(2*Row*Column*sizeof(gdouble));
	 r = CylinderExtDiameter/2.0 ;
	 // kill the impossible condition
	 if(Column<=0||Row<=0) return ;
	 if(p->probe_p->D1_D2 == 0)  Row = 1 ;
	 if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
	
	 if(p->probe_p->transmi_trans_longi==0)
    {   
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
        c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
    }                                           
    else                                 
    {
        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
        c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
    }
	 // refract coefficient
	 k1 = c1/c2 ;
	
	 // element location offset calculate
	 // ÔÚROOF½Ç²»µÈÓÚ0Ê±,ÔÚ´¹Ö±ÓÚWEDGE ½ÇÉÏ±ß·½ÏòÉÏÃ¿×ßÒ»¶Î¾àÀë
	 // ¶ÔÓ¦µÄ X Y Z Èý¸ö·½ÏòÉÏ¶¼»áÓÐÒ»¸öÎ»ÖÃ±ä»¯SX SY SZ
	 if((wedgeangle != 0) && (roofangle != 0))
	 {
		  x = 1;
		  y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
		  z = y*tan(roofangle) ;
		  d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
		  s_x  = -Intervaly/d	 ;
		  s_y  = -Intervaly*y/d   ;
		  s_zy	= -Intervaly*(z-tan(wedgeangle))/d	 ;			
	 }
	 else
	 {	 
		  s_y = -Intervaly*cos(roofangle);
		  s_x = 0 ;
		  s_zy = -Intervaly*sin(roofangle);
	 }	   
	 // center probe element	(x0,y0,z0)			  
	 z0 = -(h0 + Intervalx*(Column - 1)*sin(wedgeangle)/2 - s_zy*(Row-1)/2) -sqrt(CylinderExtDiameter*CylinderExtDiameter - length*length)/2;
	 x0 = -length/2 + wg_pri_elem_offset_fir + Intervalx*(Column - 1)*cos(wedgeangle)/2 + (Row-1)*s_x/2 ;
	 if(roofangle<0)
		 wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;
	 y0 = -wg_sec_axis_reference - wg_sec_elem_offset_fir + -separation/2;
	 //ÒÔÏÂºÍ1Î¬CylinderÇé¿öÀàËÆ.
	  //Ö»ÊÇ½«3Î¬µÄ×ø±êÍ¶Ó°µ½X-ZÃæ
	  //¿Õ¼ä½Ç¶ÈºÍÍ¶Ó°½ÇÆ«×ª½ÇÖ®¼äµÄ¹ØÏµ
	  // tan(Projection) = tan(SpaceAngle)*cos(SkewAngle);
	  // get focus point coordinate 
	 aSinTemp = asin(k1*sin(a1));
	 aProjection = atan(tan(aSinTemp)*cos(a2));
	 zHightTemp = sqrt(z0*z0 + x0*x0);
	 
	 tempangle1 = asin(r*sin(aProjection)/zHightTemp);
	 tempangle2 = aProjection - tempangle1;   //tempangle2	keep for the below calculation
	 // refract point
	 xxx = r * sin(tempangle2);
	 zzz = r * cos(tempangle2);
	 
	 bProjection = atan(tan(a1)*cos(a2));
	 tempangle3 = asin(sin(bProjection)*r/(r-FocusDepth));	// tempangle3 is sure to be large than 90 degree
	 tempangle1 = tempangle3 - bProjection				 ;
	 // µ±ÕÛÉä½ÇºÍÆ«×ª½ÇÉè¶¨,¼È¿ÉÇóµÃ×î´ó¾Û½¹Éî¶È.
	 // R*SIN(PROJECTION)
	 //if(FocusDepth>r*sin(bProjection))  FocusDepth =	r*sin(bProjection);
	 //g_print("MaxDepth:%f\n", r*sin(bProjection)) 	   ;  // when a1 and a2 is setted, there will exist a max focus depth		 
	 tempFocusxxx = (r-FocusDepth) * sin(tempangle1+tempangle2) ;
	 tempFocuszzz = (r-FocusDepth) * cos(tempangle1+tempangle2) ;
	 tempFocusyyy = zHightTemp*sin(tempangle2)+sin(tempangle1)*(r-FocusDepth);		   
	 tempFocusyyy = tempFocusyyy*tan(a2) ;
	 //Ö®Ç°  gdouble  a1 = fabs(angle1*PI/180); 						   // refract angle
	 // 		   gdouble	  a2 = fabs(angle2*PI/180); 						   // deflect angle
	 // 		   if(a2>PI/2)	a2 = PI-a2 ;
	 //µ±a1 a2	  ¶¼´óÓÚ0Ê±,Ïà¶ÔÓÚÌ½Í·ÖÐÐÄµãµÄ×ø±êÏµµÄÈëÉäµã×ø±ê
	 // TEMPFOCUSXXX TEMPFOCUSYYY TEMPFOCUSZZZ
	 //ÇóµÃÁÙÊ±×ø±êºó,ÔÙ¸ù¾Ýa1 a2µÄÊµ¼ÊÇé¿ö,½«×ø±êµÄÕý¸ºÖµÉè¶¨
	 if(angle1>=0)
	 {
		 if(angle2>=0)
		 {
			 if(angle2>90)
			 {
				  tempFocusxxx=-tempFocusxxx;
			 }
		 }
		 else
		 {
			 if(a2>PI/2)
			 {
				  tempFocusxxx=-tempFocusxxx;
			 }
			 tempFocusyyy = -tempFocusyyy;
		 }
	 }
	 else
	 {
		 if(angle2>=0)
		 {
			 if(angle2>90)
			 {
				  tempFocusyyy = -tempFocusyyy;
			 }
			 else
			 {
				  tempFocusyyy=-tempFocusyyy;
				  tempFocusxxx = -tempFocusxxx;
			 }
		 }
		 else
		 {
			 if(a2<PI/2)
			 {
				  tempFocusxxx=-tempFocusxxx;
			 }		 
		 }
	 }
	 //×ø±êÐý×ª,½«½¹µã×ø±êÓÉÖÐÐÄÌ½Í·×ø±êÐý×ªµ½Êµ¼Ê×ø±ê
	 p->focus_y[p->k]   = y0 - tempFocusyyy	 ;
	 angle_rotate = -asin(x0/zHightTemp) ;
	 p->focus_x[p->k] = tempFocusxxx*cos(angle_rotate) - tempFocuszzz*sin(angle_rotate);
	 p->focus_z[p->k] = -(tempFocusxxx*sin(angle_rotate) + tempFocuszzz*cos(angle_rotate));

     p->focus_xr[p->k] = p->focus_x[p->k] ;
	 p->focus_yr[p->k] = p->focus_y[p->k] ;
	 p->focus_zr[p->k] = p->focus_z[p->k] ;

	 p->probe_x[p->k][0] =   -length/2 + wg_pri_elem_offset_fir ;
     p->probe_y[p->k][0] =   -wg_sec_axis_reference - wg_sec_elem_offset_fir;
     p->probe_z[p->k][0] =   -h0	- sqrt(CylinderExtDiameter*CylinderExtDiameter- length*length)/2;	  
	 tempangle2 = asin(p->focus_x[p->k]/(r-FocusDepth)) ;
	 r_depth	= r - FocusDepth ;
	 
	 for(i = 0; i< Column; i++)
	 {
		  for(j = 0; j< Row; j++)
		  {
				//get elements' coordinates
				zTemp = p->probe_z[p->k][0] + j*s_zy - i*Intervalx*sin(wedgeangle);
				xTemp = p->probe_x[p->k][0] + Intervalx*cos(wedgeangle)*i + j*s_x ;
				yTemp = p->probe_y[p->k][0] + s_y*j;
				p->probe_x[p->k][i*Row+j] = xTemp  ;
				p->probe_y[p->k][i*Row+j] = yTemp  ;
				p->probe_z[p->k][i*Row+j] = zTemp  ;
				if((xTemp*xTemp+zTemp*zTemp)<r*r)
				{
					p->horizontal_x[p->k][i*Row+j] = xTemp  ;
					p->horizontal_y[p->k][i*Row+j] = yTemp ;
					p->horizontal_z[p->k][i*Row+j] = zTemp ;
					continue ;
				}
				count = 0;
				zHightTemp	 = sqrt(xTemp*xTemp + zTemp*zTemp);
				angle_rotate = -asin(xTemp/zHightTemp)		  ;
				tempangle3	 = tempangle2 + angle_rotate	  ;
				if(tempangle3 == 0)
				{ // µ±Í¶Ó°½ÇÎª0Ê±,ÔÚY·½Ïò×÷ËÑË÷.ÀàËÆÓÚÒ»Î¬ËÑË÷
					xxx = 0;
					zzz = r ;			
					if(yTemp == p->focus_y[p->k])
					   yyy = yTemp ;
					else 
					{
						 zTemp = zHightTemp - r;
						 TempLength = fabs(yTemp-p->focus_y[p->k]);
						 SearchLength = TempLength/2 ;
						 SearchPoint = 0 ;
						 TempResult = 0 ;
						 do
						 {
							  SearchPoint += SearchLength ; 	 
							   //printf("search point :%f \n",SearchPoint);
							  tana = SearchPoint/zTemp;
							  sina = sqrt(tana*tana/(1+tana*tana));
							  sinb = sina/k1;				   
							  if(sinb>=1)  
							  {
								   SearchLength = -fabs(SearchLength)/2 ;					
							  }
							  else
							  {
								   tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
								   TempResult=SearchPoint+tanb*FocusDepth ;
								   if(TempResult>TempLength)   SearchLength = -fabs(SearchLength)/2 ;
								   if(TempResult<TempLength)   SearchLength =  fabs(SearchLength)/2 ;				  
							  } 				  
							  count++;		   
						 }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;   
	
						 yyy = yTemp + SearchPoint*(p->focus_y[p->k]-yTemp)/fabs(p->focus_y[p->k] - yTemp); 
						 
					}
					
					p->horizontal_x[p->k][i*Row+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)	;
					p->horizontal_y[p->k][i*Row+j] = yyy ;
					p->horizontal_z[p->k][i*Row+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate));
					continue ;
				}
				tempangle1	 = fabs(tempangle3);
				SearchLength = tempangle1/2 				  ;
				SearchAngle  = 0							  ;
				TempResult	 = 0							  ;
				
				yyy = fabs(p->focus_y[p->k] - yTemp) ;
				//TempResult = TempLength + SearchGate ;
				do
				{// ËÑË÷X-ZÍ¶Ó°½Ç
					  SearchAngle += SearchLength ; 	 
					  //printf("search point :%f \n",SearchPoint);
					  aProjection = atan(zHightTemp*sin(SearchAngle)/(zHightTemp*cos(SearchAngle)-r));
					  SkewAngleTemp = atan(yyy/(zHightTemp*sin(SearchAngle)+(r-FocusDepth)*sin(tempangle1-SearchAngle)));
					  a = atan(tan(aProjection)/cos(SkewAngleTemp));
					  if(fabs(sin(a)/k1)>=1)
					  {
							 SearchLength = -fabs(SearchLength)/2 ;
					  }
					  else
					  { 					  
						 b = asin(sin(a)/k1)						  ;
						 bProjection = atan(tan(b)*cos(SkewAngleTemp));
						 TempResult  = r*sin(bProjection)/sin(bProjection+tempangle1-SearchAngle)  ;
						 if(TempResult>r_depth)   SearchLength = -fabs(SearchLength)/2 ;
						 if(TempResult<r_depth)   SearchLength =  fabs(SearchLength)/2 ;
					  }
					  count++;
				}while( (fabs(TempResult-r_depth) > SearchGate) && ( count<=20 )) ;    
				// translate into common coordiniate
				if(tempangle3<=0)
					   xxx = -r*sin(SearchAngle) ;
				else   
					   xxx = r*sin(SearchAngle);
				
				if(yTemp>p->focus_y[p->k])
					yyy = yTemp - sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp) ;
				else 
					yyy = yTemp + sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp);
				zzz = r*cos(SearchAngle);
				p->horizontal_x[p->k][i*Row+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)	;
				p->horizontal_y[p->k][i*Row+j] = yyy ;
				p->horizontal_z[p->k][i*Row+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate)) ; 			   
		  }
	 }
	//calculate the transfer time
	for(i=0;i<Column;i++)
	{
		for(j =0;j<Row; j++)
		{
			 dis1 = sqrt((p->probe_x[p->k][i*Row+j]-p->horizontal_x[p->k][i*Row+j])*(p->probe_x[p->k][i*Row+j]-p->horizontal_x[p->k][i*Row+j])
							+(p->probe_y[p->k][i*Row+j]-p->horizontal_y[p->k][i*Row+j])*(p->probe_y[p->k][i*Row+j]-p->horizontal_y[p->k][i*Row+j])
						   +(p->probe_z[p->k][i*Row+j]-p->horizontal_z[p->k][i*Row+j])*(p->probe_z[p->k][i*Row+j]-p->horizontal_z[p->k][i*Row+j]));
			 dis2 = sqrt((p->horizontal_x[p->k][i*Row+j]-p->focus_x[p->k])*(p->horizontal_x[p->k][i*Row+j]-p->focus_x[p->k])
						   +(p->horizontal_y[p->k][i*Row+j]-p->focus_y[p->k])*(p->horizontal_y[p->k][i*Row+j]-p->focus_y[p->k])
						   +(p->horizontal_z[p->k][i*Row+j]-p->focus_z[p->k])*(p->horizontal_z[p->k][i*Row+j]-p->focus_z[p->k]));
			 time[i*Row+j] = dis1/c1+dis2/c2;		   
		}
	}
	// get the time delay
	timemax = time[0];
	for(i=0;i<Column*Row;i++)
	{
		  if(timemax < time[i])  timemax = time[i] ;				   
	}
	
	g_print("***********\n")   ;
	g_print("	 x1 x2 x3\n")  ;
	g_print("y1  0	3  6  \n") ;
	g_print("y2  1	4  7  \n") ;
	g_print("y3  2	5  8  \n") ;
	g_print("***********\n")   ;	   
	g_print("pitch\n")         ;
	for(i = 0 ;i<Column*Row ; i++)
	{
		 g_printf("No.%d,time[%d] = %f,¦¤t=%d\n",i+1,i+1,time[i],(gint)((timemax - time[i])*1000000+0.5));
		 p->timedelay[p->k][i] = (gint)((timemax - time[i])*1000000+0.5);
	}

	h0 =  p->wedge_r->wg_heigh_fir ;				  // first element high
	Row      =  p->element_sel->sec_axis_ape  ;                  // element y direction numble
    Column   = p->element_sel->pri_axis_ape;                  // element x direction numble
    if((Row*Column) > (p->probe_p->ele_num_pri * p->probe_p->ele_num_sec))
              return;
	Intervaly = p->probe_p->sec_axis_pitch ;		  // y direction interval
	Intervalx = p->probe_p->pri_axis_pitch ;		  // x direction interval distance
	pri_ele_size = p->probe_p->pri_ele_size ;
	wg_pri_axis_reference  = p->wedge_r->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	wg_sec_axis_reference  = p->wedge_r->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
	wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	roofangle = p->wedge_r->wg_roof_angle*PI/180   ; // roofangle	y-z platform
	wedgeangle= p->wedge_r->wg_wedge_angle*PI/180  ; // wedgeangle	x-z platform	 
	
	if((wedgeangle != 0) && (roofangle != 0))
	{
		 x = 1;
		 y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
		 z = y*tan(roofangle) ;
		 d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
		 s_x  = -Intervaly*x/d	  ;
		 s_y  = Intervaly*y/d	  ;
		 s_zy  = -Intervaly*(z-x*tan(wedgeangle))/d   ; 		 
	}
	else
	{	
		 s_y = -Intervaly*cos(roofangle);
		 s_x = 0 ;
		 s_zy = -Intervaly*sin(roofangle);
	}  

	// center probe element    (x0,y0,z0)			 

	p->probe_xr[p->k][0] =   -length/2 + wg_pri_elem_offset_fir ;
	p->probe_yr[p->k][0] =   p->probe_y[p->k][0]  - separation;
	p->probe_zr[p->k][0] =   -h0	- sqrt(CylinderExtDiameter*CylinderExtDiameter- length*length)/2;	 
	//receiver time delay calculation 
	s_y = -s_y ;
	 for(i = 0; i< Column; i++)
	 {
		  for(j = 0; j< Row; j++)
		  {
				//get elements' coordinates
				zTemp = p->probe_zr[p->k][0] + j*s_zy - i*Intervalx*sin(wedgeangle);
				xTemp = p->probe_xr[p->k][0] + Intervalx*cos(wedgeangle)*i + j*s_x ;
				yTemp = p->probe_yr[p->k][0] + s_y*j;
				p->probe_xr[p->k][i*Row+j] = xTemp  ;
				p->probe_yr[p->k][i*Row+j] = yTemp  ;
				p->probe_zr[p->k][i*Row+j] = zTemp  ;
				if((xTemp*xTemp+zTemp*zTemp)<r*r)
				{
					p->horizontal_xr[p->k][i*Row+j] = xTemp  ;
					p->horizontal_yr[p->k][i*Row+j] = yTemp ;
					p->horizontal_zr[p->k][i*Row+j] = zTemp ;
					continue ;
				}
				count = 0;
				zHightTemp	 = sqrt(xTemp*xTemp + zTemp*zTemp);
				angle_rotate = -asin(xTemp/zHightTemp)		  ;
				tempangle3	 = tempangle2 + angle_rotate	  ;
				if(tempangle3 == 0)
				{ // µ±Í¶Ó°½ÇÎª0Ê±,ÔÚY·½Ïò×÷ËÑË÷.ÀàËÆÓÚÒ»Î¬ËÑË÷
					xxx = 0;
					zzz = r ;			
					if(yTemp == p->focus_yr[p->k])
					   yyy = yTemp ;
					else 
					{
						 zTemp = zHightTemp - r;
						 TempLength = fabs(yTemp-p->focus_y[p->k]);
						 SearchLength = TempLength/2 ;
						 SearchPoint = 0 ;
						 TempResult = 0 ;
						 do
						 {
							  SearchPoint += SearchLength ; 	 
							   //printf("search point :%f \n",SearchPoint);
							  tana = SearchPoint/zTemp;
							  sina = sqrt(tana*tana/(1+tana*tana));
							  sinb = sina/k1;				   
							  if(sinb>=1)  
							  {
								   SearchLength = -fabs(SearchLength)/2 ;					
							  }
							  else
							  {
								   tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
								   TempResult=SearchPoint+tanb*FocusDepth ;
								   if(TempResult>TempLength)   SearchLength = -fabs(SearchLength)/2 ;
								   if(TempResult<TempLength)   SearchLength =  fabs(SearchLength)/2 ;				  
							  } 				  
							  count++;		   
						 }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;   
	
						 yyy = yTemp + SearchPoint*(p->focus_yr[p->k]-yTemp)/fabs(p->focus_yr[p->k] - yTemp); 
						 
					}
					
					p->horizontal_xr[p->k][i*Row+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)	;
					p->horizontal_yr[p->k][i*Row+j] = yyy ;
					p->horizontal_zr[p->k][i*Row+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate));
					continue ;
				}
				tempangle1	 = fabs(tempangle3);
				SearchLength = tempangle1/2 				  ;
				SearchAngle  = 0							  ;
				TempResult	 = 0							  ;
				
				yyy = fabs(p->focus_yr[p->k] - yTemp) ;
				//TempResult = TempLength + SearchGate ;
				do
				{// ËÑË÷X-ZÍ¶Ó°½Ç
					  SearchAngle += SearchLength ; 	 
					  //printf("search point :%f \n",SearchPoint);
					  aProjection = atan(zHightTemp*sin(SearchAngle)/(zHightTemp*cos(SearchAngle)-r));
					  SkewAngleTemp = atan(yyy/(zHightTemp*sin(SearchAngle)+(r-FocusDepth)*sin(tempangle1-SearchAngle)));
					  a = atan(tan(aProjection)/cos(SkewAngleTemp));
					  if(fabs(sin(a)/k1)>=1)
					  {
							 SearchLength = -fabs(SearchLength)/2 ;
					  }
					  else
					  { 					  
						 b = asin(sin(a)/k1)						  ;
						 bProjection = atan(tan(b)*cos(SkewAngleTemp));
						 TempResult  = r*sin(bProjection)/sin(bProjection+tempangle1-SearchAngle)  ;
						 if(TempResult>r_depth)   SearchLength = -fabs(SearchLength)/2 ;
						 if(TempResult<r_depth)   SearchLength =  fabs(SearchLength)/2 ;
					  }
					  count++;
				}while( (fabs(TempResult-r_depth) > SearchGate) && ( count<=20 )) ;    
				// translate into common coordiniate
				if(tempangle3<=0)
					   xxx = -r*sin(SearchAngle) ;
				else   
					   xxx = r*sin(SearchAngle);
				
				if(yTemp>p->focus_yr[p->k])
					yyy = yTemp - sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp) ;
				else 
					yyy = yTemp + sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp);
				zzz = r*cos(SearchAngle);
				p->horizontal_xr[p->k][i*Row+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)	;
				p->horizontal_yr[p->k][i*Row+j] = yyy ;
				p->horizontal_zr[p->k][i*Row+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate)) ; 			   
		  }
	 }
	//calculate the transfer time
	for(i=0;i<Column;i++)
	{
		for(j =0;j<Row; j++)
		{
			 dis1 = sqrt((p->probe_xr[p->k][i*Row+j]-p->horizontal_xr[p->k][i*Row+j])*(p->probe_xr[p->k][i*Row+j]-p->horizontal_xr[p->k][i*Row+j])
							+(p->probe_yr[p->k][i*Row+j]-p->horizontal_yr[p->k][i*Row+j])*(p->probe_yr[p->k][i*Row+j]-p->horizontal_yr[p->k][i*Row+j])
						   +(p->probe_zr[p->k][i*Row+j]-p->horizontal_zr[p->k][i*Row+j])*(p->probe_zr[p->k][i*Row+j]-p->horizontal_zr[p->k][i*Row+j]));
			 dis2 = sqrt((p->horizontal_xr[p->k][i*Row+j]-p->focus_xr[p->k])*(p->horizontal_xr[p->k][i*Row+j]-p->focus_xr[p->k])
						   +(p->horizontal_yr[p->k][i*Row+j]-p->focus_yr[p->k])*(p->horizontal_yr[p->k][i*Row+j]-p->focus_yr[p->k])
						   +(p->horizontal_zr[p->k][i*Row+j]-p->focus_zr[p->k])*(p->horizontal_zr[p->k][i*Row+j]-p->focus_zr[p->k]));
			 time[i*Row+j] = dis1/c1+dis2/c2;		   
		}
	}

	// get the time delay
	timemax = time[0];
	for(i=0;i<Column*Row;i++)
	{
		  if(timemax < time[i])  timemax = time[i] ;				   
	}
	
	g_print("receiver\n") ;
 
	for(i =0 ;i<Column*Row ; i++)
	{
		 g_printf("No.%d,time[%d] = %f,¦¤t=%d\n",i+1,i+1,time[i],(gint)((timemax - time[i])*1000000+0.5));
		 p->timedelay[p->k][i] = (gint)((timemax - time[i])*1000000+0.5);
	}
	p->G_Time[p->k] = timemax;
	free(time);


}
void cylinder_2d_roof_id_pr(gpointer data, gdouble angle1, gdouble angle2, gdouble depth)
{
   	   DRAW_UI_P p = (DRAW_UI_P) data ;
	   
	   gdouble c1 ; 		   // wave speed
	   gdouble c2 ;
	   gdouble k1 ;  
	   gdouble r  ;
	   gdouble h0 =  p->wedge_p->wg_heigh_fir ; 				 // first element high
	   gint Row      =  p->element_sel->sec_axis_ape  ;                  // element y direction numble
       gint Column   = p->element_sel->pri_axis_ape;                  // element x direction numble
       if((Row*Column) > (p->probe_p->ele_num_pri * p->probe_p->ele_num_sec))
                  return;

      	   
	   gdouble Intervaly = p->probe_p->sec_axis_pitch ; 		 // y direction interval
	   gdouble Intervalx = p->probe_p->pri_axis_pitch ; 		 // x direction interval distance
	   gdouble pri_ele_size = p->probe_p->pri_ele_size ;		
	   gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	   gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	   gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
	   gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	   gdouble length = p->wedge_p->wg_length ; 							 // wedge length
	   gdouble CylinderIntDiameter = p->specimen->speci_inside_cylindrical ;// outside cylinder diameter
	   gdouble separation  = p->wedge_r->wg_separation ;
	  
	  gdouble  a1 = fabs(angle1*PI/180);						// refract angle
	  gdouble  a2 = fabs(angle2*PI/180);						// deflect angle
	  if(a2>PI/2) a2 = PI-a2 ;

	   gdouble	roofangle = p->wedge_p->wg_roof_angle*PI/180   ; // roofangle	y-z platform
	   gdouble	wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ; // wedgeangle	x-z platform	 
	   gdouble	FocusDepth = depth; 							 //  true focus depth
	  
	   // refraction calculation 
	   gdouble aSinTemp;
	   gdouble aProjection;
	   gdouble bProjection;
	   gdouble zHightTemp;
	   
	   gdouble tempangle1;
	   gdouble tempangle2;
	   gdouble tempangle3;
	  
	   gdouble tempFocusxxx;
	   gdouble tempFocusyyy;
	   gdouble tempFocuszzz;
	   gdouble angle_rotate;
	   
	   gdouble xTemp, yTemp, zTemp ;
	   gdouble x0,y0,z0;			                               // element center coordinate
	   //  element offset in each direction
	   gdouble x;
	   gdouble y;
	   gdouble z;
	   gdouble d;
	   gdouble s_x;
	   gdouble s_y;
	   gdouble s_zy;
	   gdouble s_zx;	 
	   // variable for search method
	   gdouble SearchLength , SearchAngle;
	   gdouble TempAngle;
	   gdouble TempResult;
	   gdouble SkewAngleTemp;
	   gdouble SearchPoint ;
	   gdouble TempLength  ;
	   gdouble tana,tanb,sina,sinb ;
	   gdouble r_depth;
	   gdouble a;
	   gdouble b;
	   
	   gdouble xxx;
	   gdouble yyy;
	   gdouble zzz;
	   
	   gint i, j; 
	   int count;
	   // variable for time calculation
	   gdouble dis1;
	   gdouble dis2;
	   gdouble timemax ;
	   gdouble *time = malloc(2*Row*Column*sizeof(gdouble));
	   r = CylinderIntDiameter/2.0 ;
	   // kill the impossible condition
	   if(Column<=0||Row<=0) return ;
	   if(p->probe_p->D1_D2 == 0)  Row = 1 ;
	   if(wedgeangle == PI/2 || roofangle == PI/2)	return ;
	  
	   if(p->probe_p->transmi_trans_longi==0)
        {   
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
            c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
        }                                           
        else                                 
        {
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
            c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
        }
	   // refract coefficient
	   k1 = c1/c2 ;
	   // element location offset calculate
	   // ÔÚROOF½Ç²»µÈÓÚ0Ê±,ÔÚ´¹Ö±ÓÚWEDGE ½ÇÉÏ±ß·½ÏòÉÏÃ¿×ßÒ»¶Î¾àÀë
       // ¶ÔÓ¦µÄ X Y Z Èý¸ö·½ÏòÉÏ¶¼»áÓÐÒ»¸öÎ»ÖÃ±ä»¯SX SY SZ
	   if((wedgeangle != 0) && (roofangle != 0))
	   {
			x = 1;
			y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
			z = y*tan(roofangle) ;
			d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
			s_x  = -Intervaly/d     ;
			s_y  = -Intervaly*y/d	;
			s_zy  = -Intervaly*(z-tan(wedgeangle))/d   ;		  
	   }
	   else
	   {   
			s_y = -Intervaly*cos(roofangle);
			s_x = 0 ;
			s_zy = -Intervaly*sin(roofangle);
	   }	 
	   // center probe element	  (x0,y0,z0)			
	   z0 = -(h0 + Intervalx*(Column - 1)*sin(wedgeangle)/2 - s_zy*(Row-1)/2) + sqrt(CylinderIntDiameter*CylinderIntDiameter - length*length)/2;
	   x0 = -length/2 + wg_pri_elem_offset_fir + Intervalx*(Column - 1)*cos(wedgeangle)/2 + (Row-1)*s_x/2 ;
	   y0 = -wg_sec_axis_reference - wg_sec_elem_offset_fir -separation/2 ;
	  
	   // get focus point coordinate
       //ÒÔÏÂºÍ1Î¬CylinderÇé¿öÀàËÆ.
       //Ö»ÊÇ½«3Î¬µÄ×ø±êÍ¶Ó°µ½X-ZÃæ
       //¿Õ¼ä½Ç¶ÈºÍÍ¶Ó°½ÇÆ«×ª½ÇÖ®¼äµÄ¹ØÏµ
       // tan(Projection) = tan(SpaceAngle)*cos(SkewAngle);
		   aSinTemp = asin(k1*sin(a1));
	   aProjection = atan(tan(aSinTemp)*cos(a2));
	   zHightTemp = sqrt(z0*z0 + x0*x0);
	   
	   tempangle1 = asin(r*sin(aProjection)/zHightTemp);
	   tempangle2 = tempangle1 - aProjection;	//tempangle2  keep for the below calculation
	   // refract point
	   xxx = r * sin(tempangle2);
	   zzz = r * cos(tempangle2);
	   
	   bProjection = atan(tan(a1)*cos(a2));
	   tempangle3 = asin(sin(bProjection)*r/(r+FocusDepth)); 
	   tempangle1 = bProjection - tempangle3			   ;  
	   
	   tempFocusxxx = (r+FocusDepth) * sin(tempangle1+tempangle2)              ;
	   tempFocuszzz = -(r+FocusDepth) * cos(tempangle1+tempangle2)             ;
	   tempFocusyyy = zHightTemp*sin(tempangle2)+sin(tempangle1)*(r+FocusDepth);
	   tempFocusyyy = tempFocusyyy*tan(a2)                                     ;
	   //Ö®Ç°  gdouble	a1 = fabs(angle1*PI/180); 							 // refract angle
	   //            gdouble	a2 = fabs(angle2*PI/180); 					 // deflect angle
	   //            if(a2>PI/2)  a2 = PI-a2 ;
	   //µ±a1 a2	¶¼´óÓÚ0Ê±,Ïà¶ÔÓÚÌ½Í·ÖÐÐÄµãµÄ×ø±êÏµµÄÈëÉäµã×ø±ê
	   // TEMPFOCUSXXX TEMPFOCUSYYY TEMPFOCUSZZZ
	   //ÇóµÃÁÙÊ±×ø±êºó,ÔÙ¸ù¾Ýa1 a2µÄÊµ¼ÊÇé¿ö,½«×ø±êµÄÕý¸ºÖµÉè¶¨
	   if(angle1>=0)
	   {
		   if(angle2>=0)
		   {
			   if(angle2>90)
			   {
					tempFocusxxx=-tempFocusxxx;
			   }
		   }
		   else
		   {
			   if(a2>PI/2)
			   {
					tempFocusxxx=-tempFocusxxx;
			   }
			   tempFocusyyy = -tempFocusyyy;
		   }
	   }
	   else
	   {
		   if(angle2>=0)
		   {
			   if(angle2>90)
			   {
					tempFocusyyy = -tempFocusyyy;
			   }
			   else
			   {
					tempFocusyyy=-tempFocusyyy;
					tempFocusxxx = -tempFocusxxx;
			   }
		   }
		   else
		   {
			   if(a2<PI/2)
			   {
					tempFocusxxx=-tempFocusxxx;
			   }	   
		   }
	   }

	   p->focus_y[p->k]	= y0 - tempFocusyyy                                        ;
	   angle_rotate = asin(x0/zHightTemp)                                      ;
	   p->focus_x[p->k] = tempFocusxxx*cos(angle_rotate) - tempFocuszzz*sin(angle_rotate);
	   p->focus_z[p->k] = -(tempFocusxxx*sin(angle_rotate) + tempFocuszzz*cos(angle_rotate));
	   p->focus_xr[p->k] = p->focus_x[p->k] ;
	   p->focus_yr[p->k] = p->focus_y[p->k] ;
	   p->focus_zr[p->k] = p->focus_z[p->k] ;
	   
	   p->probe_x[p->k][0] =	 -length/2 + wg_pri_elem_offset_fir ;
	   p->probe_y[p->k][0] =	 -wg_sec_axis_reference - wg_sec_elem_offset_fir;
	   p->probe_z[p->k][0] =	 -h0  + sqrt(CylinderIntDiameter*CylinderIntDiameter- length*length)/2;
	   tempangle2 = asin(p->focus_x[p->k]/(r+FocusDepth)) ;
	   r_depth	  = r + FocusDepth ;
	   for(i = 0; i< Column; i++)
	   {
			for(j = 0; j< Row; j++)
			{
				  //get elements' coordinates
				  zTemp = p->probe_z[p->k][0] + j*s_zy - i*Intervalx*sin(wedgeangle);
				  xTemp = p->probe_x[p->k][0] + Intervalx*cos(wedgeangle)*i + j*s_x ;
				  yTemp = p->probe_y[p->k][0] + s_y*j;
				  p->probe_x[p->k][i*Row+j] = xTemp  ;
				  p->probe_y[p->k][i*Row+j] = yTemp  ;
				  p->probe_z[p->k][i*Row+j] = zTemp  ;
				  if((xTemp*xTemp+zTemp*zTemp)>r*r)
				  {
					   	p->horizontal_x[p->k][i*Row+j] = xTemp ;
					    p->horizontal_y[p->k][i*Row+j] = yTemp ;
					    p->horizontal_z[p->k][i*Row+j] = zTemp ;
					    continue ;
				  }
                  count = 0;
				  zHightTemp   = sqrt(xTemp*xTemp + zTemp*zTemp);
				  angle_rotate = asin(xTemp/zHightTemp)		    ;
				  tempangle3   = tempangle2 - angle_rotate		;	  
				  
				  if(tempangle3 == 0)
				  {// µ±Í¶Ó°½ÇÎª0Ê±,ÔÚY·½Ïò×÷ËÑË÷.ÀàËÆÓÚÒ»Î¬ËÑË÷
					  xxx = 0;
					  zzz = -r ; 		  
					  if(yTemp == p->focus_y[p->k])
						 yyy = yTemp ;
					  else 
					  {    
						   zTemp = r - zHightTemp;
						   TempLength= fabs(yTemp-p->focus_y[p->k]);
						   SearchLength = TempLength/2 ;
						   SearchPoint  = 0 ;
						   TempResult = 0 ;
						   do
						   {
								SearchPoint += SearchLength ;	   
								tana = SearchPoint/zTemp;
								sina = sqrt(tana*tana/(1+tana*tana));
								sinb = sina/k1; 				 
								if(sinb>=1)  
								{
									 SearchLength = -fabs(SearchLength)/2 ; 				  
								}
								else
								{
									 tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
									 TempResult=SearchPoint+tanb*FocusDepth ;
									 if(TempResult>TempLength)	 SearchLength = -fabs(SearchLength)/2 ;
									 if(TempResult<TempLength)	 SearchLength =  fabs(SearchLength)/2 ; 				
								}					
								count++;		 
						   }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;	
						   yyy = yTemp + SearchPoint*(p->focus_y[p->k]-yTemp)/fabs(p->focus_y[p->k] - yTemp); 
					  }
					  p->horizontal_x[p->k][i*Row+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)  ;
					  p->horizontal_y[p->k][i*Row+j] = yyy ;
					  p->horizontal_z[p->k][i*Row+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate));
					  continue ;
				  }

				  tempangle1   = fabs(tempangle3)               ;
				  SearchLength = tempangle1/2					;
				  SearchAngle  = 0								;
				  TempResult   = 0								;
				  yyy = fabs(p->focus_y[p->k] - yTemp) ;
				  do
				  {// ËÑË÷X-ZÍ¶Ó°½Ç
						SearchAngle += SearchLength ;	   
						//printf("search point :%f \n",SearchPoint);
						aProjection = atan(zHightTemp*sin(SearchAngle)/(r - zHightTemp*cos(SearchAngle)));
						SkewAngleTemp = atan(yyy/(zHightTemp*sin(SearchAngle)+(r+FocusDepth)*sin(tempangle1-SearchAngle)));
						a = atan(tan(aProjection)/cos(SkewAngleTemp));
						if(fabs(sin(a)/k1)>=1)
						{
							   SearchLength = -fabs(SearchLength)/2 ;
						}
						else
						{						
						   b = asin(sin(a)/k1)							;
						   bProjection = atan(tan(b)*cos(SkewAngleTemp));
						   TempResult  = r*sin(bProjection)/sin(bProjection-tempangle1+SearchAngle);
						   if(TempResult>r_depth)	SearchLength =  fabs(SearchLength)/2 ;
						   if(TempResult<r_depth)	SearchLength =	-fabs(SearchLength)/2 ;
						}
						count++;
				  }while( (fabs(r_depth-TempResult) > SearchGate) && ( count<=20 )) ;	 
				  // translate into common coordiniate
                  xxx = (tempangle3<=0)?-r*sin(SearchAngle):r*sin(SearchAngle);				  
				  if(yTemp>p->focus_y[p->k])
					  yyy = yTemp - sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp) ;
				  else 
					  yyy = yTemp + sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp);
				  zzz = -r*cos(SearchAngle);
				  p->horizontal_x[p->k][i*Row+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)  ;
				  p->horizontal_y[p->k][i*Row+j] = yyy ;
				  p->horizontal_z[p->k][i*Row+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate) ) ;				 
			}
	   }
	  //calculate the transfer time
	  for(i=0;i<Column;i++)
	  {
		  for(j =0;j<Row; j++)
		  {
			   dis1 = sqrt((p->probe_x[p->k][i*Row+j]-p->horizontal_x[p->k][i*Row+j])*(p->probe_x[p->k][i*Row+j]-p->horizontal_x[p->k][i*Row+j])
							  +(p->probe_y[p->k][i*Row+j]-p->horizontal_y[p->k][i*Row+j])*(p->probe_y[p->k][i*Row+j]-p->horizontal_y[p->k][i*Row+j])
							 +(p->probe_z[p->k][i*Row+j]-p->horizontal_z[p->k][i*Row+j])*(p->probe_z[p->k][i*Row+j]-p->horizontal_z[p->k][i*Row+j]));
			   dis2 = sqrt((p->horizontal_x[i*Row+j]-p->focus_x)*(p->horizontal_x[i*Row+j]-p->focus_x)
							 +(p->horizontal_y[i*Row+j]-p->focus_y)*(p->horizontal_y[i*Row+j]-p->focus_y)
							 +(p->horizontal_z[i*Row+j]-p->focus_z)*(p->horizontal_z[i*Row+j]-p->focus_z));
			   time[i*Row+j] = dis1/c1+dis2/c2; 		 
		  }
	  }
	  // get the time delay
	  timemax = time[0];
	  for(i=0;i<Column*Row;i++)
	  {
			if(timemax < time[i])  timemax = time[i] ;					 
	  }
	  g_print("***********\n") ;
	  g_print("    x1 x2 x3\n")  ;
	  g_print("y1  1  4  7	\n") ;
	  g_print("y2  2  5  8	\n") ;
	  g_print("y3  3  6  9	\n") ;
	  g_print("***********\n"); 	 
	  g_print("Pitch\n");
	  for(i = 0 ;i<Column*Row ; i++)
	  {
		  g_printf("No.%d,time[%d] = %f,¦¤t=%d\n",i+1,i+1,time[i],(gint)((timemax - time[i])*1000000+0.5));
		  p->timedelay[p->k][i] = (gint)((timemax - time[i])*1000000+0.5);
	  }


	h0 =  p->wedge_r->wg_heigh_fir ;				  // first element high
	Row      =  p->element_sel->sec_axis_ape  ;                  // element y direction numble
    Column   =  p->element_sel->pri_axis_ape;                  // element x direction numble
    if((Row*Column) > (p->probe_p->ele_num_pri * p->probe_p->ele_num_sec))
              return;
              
	Intervaly = p->probe_p->sec_axis_pitch ;		  // y direction interval
	Intervalx = p->probe_p->pri_axis_pitch ;		  // x direction interval distance
	pri_ele_size = p->probe_p->pri_ele_size ;
	wg_pri_axis_reference  = p->wedge_r->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	wg_sec_axis_reference  = p->wedge_r->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
	wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	roofangle = p->wedge_r->wg_roof_angle*PI/180   ; // roofangle	y-z platform
	wedgeangle= p->wedge_r->wg_wedge_angle*PI/180  ; // wedgeangle	x-z platform	 
	
	if((wedgeangle != 0) && (roofangle != 0))
	{
		 x = 1;
		 y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
		 z = y*tan(roofangle) ;
		 d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
		 s_x  = -Intervaly*x/d	  ;
		 s_y  = Intervaly*y/d	  ;
		 s_zy  = -Intervaly*(z-x*tan(wedgeangle))/d   ; 		 
	}
	else
	{	
		 s_y = -Intervaly*cos(roofangle);
		 s_x = 0 ;
		 s_zy = -Intervaly*sin(roofangle);
	}  

	// center probe element    (x0,y0,z0)			 
	
	p->probe_xr[p->k][0] =   -length/2 + wg_pri_elem_offset_fir ;
	p->probe_yr[p->k][0] =   p->probe_y[p->k][0] - separation;
	p->probe_zr[p->k][0] =   -h0  + sqrt(CylinderIntDiameter*CylinderIntDiameter- length*length)/2;

      s_y = -s_y ;
	  for(i = 0; i< Column; i++)
	  {
		   for(j = 0; j< Row; j++)
		   {
				 //get elements' coordinates
				 zTemp = p->probe_zr[p->k][0] + j*s_zy - i*Intervalx*sin(wedgeangle);
				 xTemp = p->probe_xr[p->k][0] + Intervalx*cos(wedgeangle)*i + j*s_x ;
				 yTemp = p->probe_yr[p->k][0] + s_y*j;
				 p->probe_xr[p->k][i*Row+j] = xTemp  ;
				 p->probe_yr[p->k][i*Row+j] = yTemp  ;
				 p->probe_zr[p->k][i*Row+j] = zTemp  ;
				 if((xTemp*xTemp+zTemp*zTemp)>r*r)
				 {
					   p->horizontal_xr[p->k][i*Row+j] = xTemp ;
					   p->horizontal_yr[p->k][i*Row+j] = yTemp ;
					   p->horizontal_zr[p->k][i*Row+j] = zTemp ;
					   continue ;
				 }
				 count = 0;
				 zHightTemp   = sqrt(xTemp*xTemp + zTemp*zTemp);
				 angle_rotate = asin(xTemp/zHightTemp)		   ;
				 tempangle3   = tempangle2 - angle_rotate	   ;	 
				 
				 if(tempangle3 == 0)
				 {// µ±Í¶Ó°½ÇÎª0Ê±,ÔÚY·½Ïò×÷ËÑË÷.ÀàËÆÓÚÒ»Î¬ËÑË÷
					 xxx = 0;
					 zzz = -r ; 		 
					 if(yTemp == p->focus_yr[p->k])
						yyy = yTemp ;
					 else 
					 {	  
						  zTemp = r - zHightTemp;
						  TempLength= fabs(yTemp-p->focus_yr[p->k]);
						  SearchLength = TempLength/2 ;
						  SearchPoint  = 0 ;
						  TempResult = 0 ;
						  do
						  {
							   SearchPoint += SearchLength ;	  
							   tana = SearchPoint/zTemp;
							   sina = sqrt(tana*tana/(1+tana*tana));
							   sinb = sina/k1;					
							   if(sinb>=1)	
							   {
									SearchLength = -fabs(SearchLength)/2 ;					 
							   }
							   else
							   {
									tanb = sqrt(sinb*sinb/(1-sinb*sinb)) ;
									TempResult=SearchPoint+tanb*FocusDepth ;
									if(TempResult>TempLength)	SearchLength = -fabs(SearchLength)/2 ;
									if(TempResult<TempLength)	SearchLength =	fabs(SearchLength)/2 ;				   
							   }				   
							   count++; 		
						  }while( (fabs(TempResult-TempLength) > SearchGate) && ( count<=20 )) ;   
						  yyy = yTemp + SearchPoint*(p->focus_yr[p->k]-yTemp)/fabs(p->focus_yr[p->k] - yTemp); 
					 }
					 p->horizontal_xr[p->k][i*Row+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)  ;
					 p->horizontal_yr[p->k][i*Row+j] = yyy ;
					 p->horizontal_zr[p->k][i*Row+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate));
					 continue ;
				 }
	  
				 tempangle1   = fabs(tempangle3)			   ;
				 SearchLength = tempangle1/2				   ;
				 SearchAngle  = 0							   ;
				 TempResult   = 0							   ;
				 yyy = fabs(p->focus_yr[p->k] - yTemp) ;
				 do
				 {// ËÑË÷X-ZÍ¶Ó°½Ç
					   SearchAngle += SearchLength ;	  
					   //printf("search point :%f \n",SearchPoint);
					   aProjection = atan(zHightTemp*sin(SearchAngle)/(r - zHightTemp*cos(SearchAngle)));
					   SkewAngleTemp = atan(yyy/(zHightTemp*sin(SearchAngle)+(r+FocusDepth)*sin(tempangle1-SearchAngle)));
					   a = atan(tan(aProjection)/cos(SkewAngleTemp));
					   if(fabs(sin(a)/k1)>=1)
					   {
							  SearchLength = -fabs(SearchLength)/2 ;
					   }
					   else
					   {					   
						  b = asin(sin(a)/k1)						   ;
						  bProjection = atan(tan(b)*cos(SkewAngleTemp));
						  TempResult  = r*sin(bProjection)/sin(bProjection-tempangle1+SearchAngle);
						  if(TempResult>r_depth)   SearchLength =  fabs(SearchLength)/2 ;
						  if(TempResult<r_depth)   SearchLength =  -fabs(SearchLength)/2 ;
					   }
					   count++;
				 }while( (fabs(r_depth-TempResult) > SearchGate) && ( count<=20 )) ;	
				 // translate into common coordiniate
				 xxx = (tempangle3<=0)?-r*sin(SearchAngle):r*sin(SearchAngle);				 
				 if(yTemp>p->focus_yr[p->k])
					 yyy = yTemp - sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp) ;
				 else 
					 yyy = yTemp + sin(SearchAngle)*zHightTemp*tan(SkewAngleTemp);
				 zzz = -r*cos(SearchAngle);
				 p->horizontal_xr[p->k][i*Row+j] = xxx*cos(angle_rotate)-zzz*sin(angle_rotate)  ;
				 p->horizontal_yr[p->k][i*Row+j] = yyy ;
				 p->horizontal_zr[p->k][i*Row+j] = -(xxx*sin(angle_rotate)+zzz*cos(angle_rotate) ) ;				
		   }
	  }

	  //calculate the transfer time
	  for(i=0;i<Column;i++)
	  {
		  for(j =0;j<Row; j++)
		  {
			   dis1 = sqrt((p->probe_xr[p->k][i*Row+j]-p->horizontal_xr[p->k][i*Row+j])*(p->probe_xr[p->k][i*Row+j]-p->horizontal_xr[p->k][i*Row+j])
							  +(p->probe_yr[p->k][i*Row+j]-p->horizontal_yr[p->k][i*Row+j])*(p->probe_yr[p->k][i*Row+j]-p->horizontal_yr[p->k][i*Row+j])
							 +(p->probe_zr[p->k][i*Row+j]-p->horizontal_zr[p->k][i*Row+j])*(p->probe_zr[p->k][i*Row+j]-p->horizontal_zr[p->k][i*Row+j]));
			   dis2 = sqrt((p->horizontal_xr[p->k][i*Row+j]-p->focus_xr[p->k])*(p->horizontal_xr[p->k][i*Row+j]-p->focus_xr[p->k])
							 +(p->horizontal_yr[p->k][i*Row+j]-p->focus_yr[p->k])*(p->horizontal_yr[p->k][i*Row+j]-p->focus_yr[p->k])
							 +(p->horizontal_zr[p->k][i*Row+j]-p->focus_zr[p->k])*(p->horizontal_zr[p->k][i*Row+j]-p->focus_zr[p->k]));
			   time[i*Row+j] = dis1/c1+dis2/c2; 		 
		  }
	  }
	  
	  // get the time delay
	  timemax = time[0];
	  for(i=0;i<Column*Row;i++)
	  {
			if(timemax < time[i])  timemax = time[i] ;					 
	  }
	  
	  g_print("receiver\n") ;
	  
	  for(i =0 ;i<Column*Row ; i++)
	  {
		   g_printf("No.%d,time[%d] = %f,¦¤t=%d\n",i+1,i+1,time[i],(gint)((timemax - time[i])*1000000+0.5));
		   p->timedelay[p->k][i] = (gint)((timemax - time[i])*1000000+0.5);
	  }
	  p->G_Time[p->k] = timemax;
	  free(time);

}


//*********************************************
//          ¾Û½¹·¨ÔòÊý¾ÝÇåÁã 
//*********************************************
void clear_focal_law(gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P) data ;
    gint i,j;
    gint Row      =  p->element_sel->sec_axis_ape  ;                  // element y direction numble
    gint Column   = p->element_sel->pri_axis_ape;                     // element x direction numble
    if((Row*Column) > (p->probe_p->ele_num_pri * p->probe_p->ele_num_sec))
              return;
    
    for(i=0;i < p->k+1;i++)
    {
        //ÏÈÇå³ý½¹µã
        p->focus_x[i] = 0;
        p->focus_y[i] = 0;
        p->focus_z[i] = 0;
        
        p->focus_xr[i] = 0;
        p->focus_yr[i] = 0;
        p->focus_zr[i] = 0;
        
        for(j =0 ;j<(Column*Row) ; j++)
        {
            p->probe_x[i][j] = 0;
            p->probe_y[i][j] = 0;
            p->probe_z[i][j] = 0;
            
            p->probe_xr[i][j] = 0;
            p->probe_yr[i][j] = 0;
            p->probe_zr[i][j] = 0;
            
            p->horizontal_x[i][j] = 0;
            p->horizontal_y[i][j] = 0;
            p->horizontal_z[i][j] = 0;
            
            p->horizontal_xr[i][j] = 0;
            p->horizontal_yr[i][j] = 0;
            p->horizontal_zr[i][j] = 0;
        }    
    }
}

/*
  Name: ProjectionToDepth_1d_roof
  Copyright: Doppler
  Author:    Shen Sheng
  Date: 22-04-11 09:19
  Description:  translate the projection parameter into true depth for focuslaw calculation 
  input : data : void pointer to DRAW_UI structure
  return  FALSE : if fail
          TRUE    : if success
  the result will be store in FocusDepth pointer memory
*/

int ProjectionToDepth_1d_roof (gpointer data, double RefractAngle, double Projection, double* FocusDepth)
{
   	   DRAW_UI_P p = (DRAW_UI_P) data ;
	   // get the center probe coordinate
       gdouble x0,y0,z0 ;
	   gdouble wedgeangle = p->wedge_p->wg_wedge_angle*G_PI/180.0;
       gdouble roofangle  = fabs(p->wedge_p->wg_roof_angle *G_PI/180.0);
	   gdouble Intervalx  = p->probe_p->pri_axis_pitch;
	   gdouble h0         = p->wedge_p->wg_heigh_fir  ;
	   gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir ;
	   gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir ;
	   gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	   gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/

	   double desirex, desirey, desirez  ;
	   double 	tanw  , tanr   , vx1    , vy1    ,vz1    ;
	   double para1, para2, vx2 ;
	   double min_angle1 , min_angle2 ;
	   double refract_x , refract_y ;
	   double tempR, TempLength ;
	   double len1, len2, len3 ;
	   
       int ElementStart = p->element_sel->primary_axis_s - 1 ;
       int ElementColumn= p->probe_p->ele_num_pri            ;
	   int SelectColumn = p->element_sel->pri_axis_ape       ;
	   int ElementStop  =   SelectColumn+ ElementStart       ;
	   if(ElementStop > ElementColumn) return FALSE          ;

	   gdouble a1 , a2                                       ;
       gdouble c1, c2 ; // velocity in the wedge and specimen
	   if(p->probe_p->transmi_trans_longi==0)
       {   
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
            c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
       }                                           
       else                                 
       {
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
            c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
       }

	   a1  =  RefractAngle*G_PI/180.0                 ;
       a2  =  asin(sin(a1)*c1/c2)                     ;  

	   //  middle probe offset to the wedge coordinate
	   z0 = Intervalx*ElementStart*sin(wedgeangle);
	   x0 = Intervalx*ElementStart*cos(wedgeangle);
	   
   	   z0 = -(z0 + h0 + Intervalx*(SelectColumn - 1)*sin(wedgeangle)/2);
	   x0 = x0 + wg_pri_axis_reference + wg_pri_elem_offset_fir + Intervalx*(SelectColumn-1)*cos(wedgeangle)/2;
       if(roofangle<0)
		 {wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;}
	   y0 = -wg_sec_axis_reference - wg_sec_elem_offset_fir;
       // Projection Èç¹ûºÍRefractAngle ²»ÔÚÍ¬Ò»·½Ïò
	   
	   if(roofangle == 0)
	   {
	             //roofangle == 0 Ê±,¼òµ¥Èý½Ç¹ØÏµ¿ÉÇó³öProjection / true depth Ö®¼äµÄ¹ØÏµ
                 if( RefractAngle * (Projection - x0 - fabs(tan(a2)*z0) ) <= 0  || a1 == 0  )  
                           return FALSE;
				 *FocusDepth = Projection - x0 + tan(a2)*z0          ;
                 *FocusDepth = *FocusDepth / tan(a1)                 ;
                 if(*FocusDepth<=0) return FALSE                     ;
                 return TRUE                                         ;
	   }
	   else
	   {        //µ±roofangle ²»µÈÓÚ0
                if(wedgeangle==0)
		        {
			            desirex = x0                            ;
				   		desirey = y0 - fabs(z0) * tan(roofangle);
				   		desirez = 0                             ;
		    	}
				else
				{
			    		tanw = -tan(wedgeangle);
			            tanr = tan(roofangle)  ;
			            vx1  = tanw*tanr       ;
			            vy1  = -(1+tanw*tanw)  ;
			            vz1  = -tanr           ;
				        // (x-para1)/vx2 = y-para2   
			     		//¹ýÌ½Í·ÓëÐ¨¿éÃæ´¹Ö±ÃæÓëZ=0ÃæµÄ½»Ïß·½³Ì
			    		para1 = x0             ;
			    		para2 = y0 + z0*vz1/vy1;
			    		vx2 = -vy1/vx1         ;
			    		//ÖÐÐÄÌ½Í·Óë½»ÏßµÄ´¹Ö±µã
			    		desirex = (vx2*x0+y0+para1/vx2 - para2)/(vx2+1/vx2);
			    		desirey = para2 + (desirex - para1)/vx2            ;
			    		desirez = 0                                        ;
				}                                  
		    	// Çó×îÐ¡ÈëÉä½Ç
				min_angle1 = atan(sqrt((desirex-x0)*(desirex-x0)+(desirey-y0)*(desirey-y0))/fabs(z0));
		    	min_angle2 = sin(min_angle1) * c2 / c1                                               ;
		    	if(min_angle2>=1)
		    	{
		               // Èç¹û×îÐ¡ÈëÉä½Ç·¢ÉúÈ«·´Éä
					   return FALSE ;
		    	}
				else 
				{
				      if(asin(min_angle2)>=fabs(a1))
				      {
					          //Èç¹û ×îÐ¡ÕÛÉä½Ç´óÓÚ¸ø¶¨ÕÛÉä½Ç,È¡´¹Ö±µã×÷ÎªÖÐÐÄÌ½Í·ÈëÉäµã 
					          refract_x = desirex;
						      refract_y = desirey;
						      a1 = min_angle2 ;
				      }
			          else
			          {
				              // ¼ÆËãÕý³£Çé¿öÏÂ½¹µãµÄ×ø±ê
				              //refract point ÕÛÉäµã×ø±ê 
				              min_angle2 = asin(sin(a1)*c1/c2);
				              tempR = z0*tan(min_angle2);
						      TempLength = sqrt(tempR*tempR - (desirex-x0)*(desirex-x0)-(desirey-y0)*(desirey-y0));
						      if(a1 >= 0)
						      {
					                 refract_x = desirex-TempLength*vx2/sqrt(1+vx2*vx2);
							         refract_y = desirey-TempLength/sqrt(1+vx2*vx2)    ;
				              }
				              else
				              {
					                 refract_x = desirex+TempLength*vx2/sqrt(1+vx2*vx2);
							         refract_y = desirey+TempLength/sqrt(1+vx2*vx2);
				              }
			          }		  
					  // ÇóÕÛÉäÉäÏß×ø±êÖ±Ïß·½³Ì
					  len1 = refract_x - x0;
					  len2 = refract_y - y0;
					  len3 = sqrt(len1*len1+len2*len2)/tan(a1);
                      //   (x - refract_x)   (y - refract_y)       z
                      //   ------------- =  -------------     =   ---
					  //           len1           len2            len3
                      //     Projection  is  in X direction , and the desire i depth in Z direction
                      if( len1 == 0 || a1*(Projection-refract_x) <=0 )   return FALSE   ;
                      *FocusDepth = fabs((Projection - refract_x)*len3/len1)            ;
					  return TRUE  ;
			    }
	   	}
}

/*
  Name: PlaneToDepth_1d_roof 
  Copyright: Doppler             
  Author:    Shen Sheng
  Date: 22-04-11 09:19
  Description:  translate the focus Plane parameter into true depth in calculation 
  input : data : void pointer to DRAW_UI structure
  return  FALSE : if fail
          TRUE  : if success
  the result will be store in FocusDepth pointer memory
*/
int PlaneToDepth_1d_roof (gpointer data, double RefractAngle, double* FocusDepth)
{
   	   DRAW_UI_P p = (DRAW_UI_P) data   ;
	   // get the center probe coordinate
       gdouble x0, y0, z0 ;
	   gdouble wedgeangle = p->wedge_p->wg_wedge_angle*G_PI/180.0;
       gdouble roofangle  = p->wedge_p->wg_roof_angle*G_PI/180.0 ;
	   gdouble Intervalx  = p->probe_p->pri_axis_pitch;
	   gdouble h0         = p->wedge_p->wg_heigh_fir  ;
	   gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir ;
	   gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir ;
	   gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	   gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	   //  ssssssssssssssssssssssssssss
	   gdouble xPt1  = p->focal_point->offset_start ;
	   gdouble zPt1  = p->focal_point->depth_start  ;

       gdouble xPt2  = p->focal_point->offset_end  ;
	   gdouble zPt2  = p->focal_point->depth_end   ;
       gdouble k1, k2 ;  // beam line and focus plane line gradient
       gdouble b1, b2 ;  // append coefficient ot beam line and focus plane line

	   double desirex, desirey, desirez  ;
	   double 	tanw  , tanr   , vx1    , vy1    ,vz1        ;
	   double para1, para2, vx2 ;
	   double min_angle1 , min_angle2 ;
	   double refract_x , refract_y ;
	   
	   double tempR, TempLength ;
	   double len1, len2, len3 ;
		   
       int ElementStart = p->element_sel->primary_axis_s - 1 ;
       int ElementColumn= p->probe_p->ele_num_pri            ;
	   int SelectColumn = p->element_sel->pri_axis_ape       ;
	   int ElementStop  =   SelectColumn+ ElementStart       ;
	   gdouble  a1 , a2  ;
	   gdouble xxx , zzz ; 
	  
       gdouble c1, c2 ; // velocity in the wedge and specimen
	   if(p->probe_p->transmi_trans_longi==0)
       {   
            c1  = p->wedge_p->wg_lon_vel            ;    /* Ð¨¿é×Ý²¨ÉùËÙ */ 
            c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
       }                                           
       else                                 
       {
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
            c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
       }

	   a1  =  RefractAngle*G_PI/180.0                 ;
       a2  =  asin(sin(a1)*c1/c2)                     ;  

	   //  middle probe offset to the wedge coordinate
	   z0 = Intervalx*ElementStart*sin(wedgeangle);
	   x0 = Intervalx*ElementStart*cos(wedgeangle);
	   
       z0 = -(z0 + h0 + Intervalx*(SelectColumn - 1)*sin(wedgeangle)/2);
       x0 = x0 + wg_pri_axis_reference + wg_pri_elem_offset_fir + Intervalx*(SelectColumn-1)*cos(wedgeangle)/2;
       if(roofangle<0)
        	 {wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;}
       y0 = -wg_sec_axis_reference - wg_sec_elem_offset_fir;

	   if(roofangle == 0)
	   {
             if(xPt2 != xPt1)
             {
                     k2  = (zPt2 - zPt1)/(xPt2 - xPt1)               ;
                     if(a1!=0) 
                     {                  
            			 k1  = 1/tan(a1)                             ;
            			 if( k1 == k2 )    return FALSE              ;
                         b1 = -k1*(x0 + tan(a2) * fabs(z0))          ;
            			 b2 = -k2 * xPt1 + zPt1                      ;
            			 xxx = (b1-b2) / ( k2 - k1)                  ;
            			 zzz = k1 * (xxx - (x0 + tan(a2) * fabs(z0)));
            			 if(zzz <= 0)  return FALSE                  ;
            			 *FocusDepth = zzz                           ;
                     }
                     else
                     {
                         zzz = k2*x0 +b2            ;
                         if(zzz<=0)   return FALSE  ;
                         *FocusDepth = zzz          ;  
                     }
             }
             else
             {
                     if( a1 == 0 )   return FALSE                 ;
                     k1 = 1/tan(a1)                               ;
                     zzz = k1 * (xPt1 - (x0 + tan(a2) * fabs(z0)));
                     if(zzz<=0)      return FALSE                 ;
                     *FocusDepth = zzz                            ;
             }
			 return TRUE  ;
	   }
	   else
	   {        //µ±roofangle ²»µÈÓÚ0
			    if(wedgeangle==0)
		        {
			            desirex = x0 ;
				   		desirey = y0 - fabs(z0) * tan(roofangle);
				   		desirez = 0  ;
		    	}
				else
				{
			    		tanw = -tan(wedgeangle);
			            tanr = tan(roofangle)  ;
			            vx1  = tanw*tanr       ;
			            vy1  = -(1+tanw*tanw)  ;
			            vz1  = -tanr           ;
				        // (x-para1)/vx2 = y-para2   
			     		//¹ýÌ½Í·ÓëÐ¨¿éÃæ´¹Ö±ÃæÓëZ=0ÃæµÄ½»Ïß·½³Ì
			    		para1 = x0             ;
			    		para2 = y0 + z0*vz1/vy1;
			    		vx2 = -vy1/vx1         ;
			    		//ÖÐÐÄÌ½Í·Óë½»ÏßµÄ´¹Ö±µã
			    		desirex = (vx2*x0+y0+para1/vx2 - para2)/(vx2+1/vx2);
			    		desirey = para2 + (desirex - para1)/vx2            ;
			    		desirez = 0                                        ;
				}                                  
		    	// Çó×îÐ¡ÈëÉä½Ç
				min_angle1 = atan(sqrt((desirex-x0)*(desirex-x0)+(desirey-y0)*(desirey-y0))/fabs(z0));
		    	min_angle2 = sin(min_angle1)*c2/c1;
		    	if(min_angle2>=1)
		    	{
		            // Èç¹û×îÐ¡ÈëÉä½Ç·¢ÉúÈ«·´ÉäÈ¡½¹µãÎªÖÐÐÄÌ½Í·×ø±
					return FALSE ;
		    	}
				else 
				{
				      if(asin(min_angle2)>=fabs(a1))
				      {
				          //Èç¹û ×îÐ¡ÕÛÉä½Ç´óÓÚ¸ø¶¨ÕÛÉä½Ç,È¡´¹Ö±µã×÷ÎªÖÐÐÄÌ½Í·ÈëÉäµã 
				          refract_x = desirex;
					      refract_y = desirey;
					      a1 = min_angle2 ;
				      }
			          else
			          {
			              // ¼ÆËãÕý³£Çé¿öÏÂ½¹µãµÄ×ø±ê
			              //refract point ÕÛÉäµã×ø±ê 
			              min_angle2 = asin(sin(a1)*c1/c2);
			              tempR = z0*tan(min_angle2);
					      TempLength = sqrt(tempR*tempR - (desirex-x0)*(desirex-x0)-(desirey-y0)*(desirey-y0));
					      if(a1 >= 0)
					      {
				                 refract_x = desirex - TempLength * vx2/sqrt(1+vx2*vx2);
						         refract_y = desirey - TempLength / sqrt(1+vx2*vx2)    ;
			              }
			              else
			              {
				                 refract_x = desirex + TempLength*vx2 / sqrt(1+vx2*vx2);
						         refract_y = desirey + TempLength / sqrt(1+vx2*vx2)    ;
			              }
			          }		  
					  // ÇóÕÛÉäÉäÏß×ø±êÖ±Ïß·½³Ì
			          len1 = refract_x - x0;
					  len2 = refract_y - y0;
					  len3 = sqrt(len1*len1+len2*len2)/tan(a1);
                      //       (x - refract_x)       (y - refract_y)         z
                      //        ------------- =     -------------      =    ---
					  //               len1               len2              len3
                      //     Projection  is  in X direction , and the desire i depth in Z direction
                      //     a1 = atan(len1/len3);  
                      //     ½«ÕÛÉä½ÇÍ¶Ó°µ½ Y=0 ÉÏ.ÔòºÍROOF½ÇµÈÓÚ0Ê±Çé¿öÒ»Ñù
					  if(xPt2 == xPt1)
					  {
                              k2  = (zPt2 - zPt1)/(xPt2 - xPt1) 	;
        					  k1  = len1/len3 						;
        					  k1  = 1/k1                            ;
        					  if( k1 == k2 )
        							return FALSE                    ;
        					  b1 = -k1*refract_x        			;
        					  b2 = -k2 * xPt1 + zPt1				;
        					  xxx = (b1-b2) / ( k2 - k1)			;
        					  zzz = k1 * (xxx - refract_x)          ;
        					  if( zzz<=0 )  return FALSE            ;
        					  *FocusDepth = zzz 					;
                      }
                      else
                      {
                              k1  = len1/len3 						;
        					  k1  = 1/k1                            ;
			                  zzz = k1 * (xPt1 - refract_x)         ;
        					  if( zzz<=0 )  return FALSE            ;
                      }
                      

			    }
	   	}
        return TRUE                           ;
}
/*
  Name: AngleSteerToRefract_1d_roof 
  Copyright: Doppler             
  Author:    Shen Sheng
  Date: 22-04-11 09:19
  Description:  translate the focus steer parameter into true depth in calculation 
  input : data : void pointer to DRAW_UI structure
  return  FALSE : if fail
          TRUE  : if success
  the result will be store in FocusDepth pointer memory
*/

int AngleSteerToRefract_1d_roof( gpointer data , gdouble beam_steer_angle, gdouble* RefractAngle)
{
   	   DRAW_UI_P p = (DRAW_UI_P) data ;
	   // get the center probe coordinate
       gdouble x0,y0,z0 ;
	   gdouble wedgeangle = p->wedge_p->wg_wedge_angle*G_PI/180.0;
       gdouble roofangle  = p->wedge_p->wg_roof_angle*G_PI/180.0 ;
	   gdouble Intervalx  = p->probe_p->pri_axis_pitch;
	   gdouble h0         = p->wedge_p->wg_heigh_fir  ;
	   gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir ;
	   gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir ;

	   double desirex, desirey, desirez               ;
	   double desirex1, desirey1,desirez1             ;
	   double tanw  , tanr   , vx1    , vy1    ,vz1   ;
	   double para1, para2 ,vx2                       ;
	   double tempAngle                               ;
	   double  x1 , y1 , z1                           ;
	   double temp, TempLength                        ;
	   double len1, len2, len3                        ;

	   int ElementStart = p->element_sel->primary_axis_s - 1 ;
       int ElementColumn= p->probe_p->ele_num_pri            ;
	   int SelectColumn = p->element_sel->pri_axis_ape       ;
	   int ElementStop  =   SelectColumn+ ElementStart       ;
	   gdouble a1 , a2  ;

	   a1 = beam_steer_angle * G_PI / 180.0                 ;
	   a2 = a1 + wedgeangle                                  ;
       
       gdouble c1, c2 ; // velocity in the wedge and specimen
	   if(p->probe_p->transmi_trans_longi==0)
       {   
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
            c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
       }                                           
       else                                 
       {
            c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
            c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
       }
	   
       if(roofangle == 0)
       {
		    if(sin(a2)*c2/c1 >= 1)  return FALSE ;
		    *RefractAngle = asin(sin(a2)*c2/c1) * 180 / G_PI   ;
       }
	   else
	   {        //µ±roofangle ²»µÈÓÚ0
			    //  middle probe offset to the wedge coordinate
	 		    z0 = Intervalx*ElementStart*sin(wedgeangle);
			    x0 = Intervalx*ElementStart*cos(wedgeangle);
			   
				z0 = -(z0 + h0 + Intervalx*(SelectColumn - 1)*sin(wedgeangle)/2);
				x0 = x0 + wg_pri_elem_offset_fir + Intervalx*(SelectColumn-1)*cos(wedgeangle)/2;
				if(roofangle<0)
					{wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;}
				y0 = - wg_sec_elem_offset_fir;


				if(wedgeangle==0)
		        {
			            desirex = x0                             ;
				   		desirey = y0 - fabs(z0) * tan(roofangle) ;
				   		desirez = 0                              ;
		    	}
				else
				{
			    		tanw = -tan(wedgeangle)                  ;
			            tanr = tan(roofangle)                    ;
			            vx1  = tanw                              ;
			            vy1  = tanr                              ;
			            vz1  =  -1                               ;

				        //´¹Ö±Ì½Í·Ö±Ïß. ¹ýÖÐÐÄÌ½Í· µ½Z0 ÃæµÄ½»µã 
						//		 (x - x0)	         (y -  y0)		    z  - z0
						//		  ------------- =  ------------- =	     ---
						//		     vx1		        vy1 	         vz1
                        //  z = 0
                        desirex = x0 - z0 * vx1 / vz1   ;
						desirey = y0 - z0 * vy1 / vz1   ;
						desirez = 0 ;			 
						tanw = -tan(wedgeangle);
						tanr = tan(roofangle)  ;
						vx1  = tanw*tanr       ;
						vy1  = -(1+tanw*tanw)  ;
						vz1  = -tanr           ;
						// (x-para1)/vx2 = y-para2   
						//¹ýÌ½Í·ÓëÐ¨¿éÃæ´¹Ö±ÃæÓëZ=0ÃæµÄ½»Ïß·½³Ì
						para1 = x0             ;
						para2 = y0 + z0*vz1/vy1;
						vx2 = -vy1/vx1         ;
						//ÖÐÐÄÌ½Í·Óë½»ÏßµÄ´¹Ö±µã
						desirex1 = (vx2*x0+y0+para1/vx2 - para2)/(vx2+1/vx2);
						desirey1 = para2 + (desirex1 - para1)/vx2 ;
						desirez1 = 0 ;
						
				}       
				TempLength = sqrt((desirex - x0)*(desirex - x0) + (desirey - y0)*(desirey - y0) + (desirez - z0)*(desirez - z0));
                temp  = sqrt((desirex1 - x0)*(desirex1 - x0) + (desirey1 - y0)*(desirey1 - y0) + (desirez1 - z0)*(desirez1 - z0));
				tempAngle = -acos(temp/TempLength)  ;
				g_print(" %f \n", tempAngle);
				temp = TempLength * tan(a1) ;
				x1   = x0 - temp * cos(wedgeangle)  ;
				y1   = y0                           ;
				z1   = z0 + temp * sin(wedgeangle)  ;
				if(z1 >= 0) return FALSE   ;
                a2   = sqrt((desirex - x1)*(desirex - x1) + (desirey - y1)*(desirey - y1))/sqrt((desirex - x1)*(desirex - x1) + (desirey - y1)*(desirey - y1) + (desirez - z1)*(desirez - z1)) ;
                
                if(a2*c2/c1>=1)  return FALSE ;
                if(a1 >= tempAngle)     
				      *RefractAngle  = asin(a2*c2/c1) * 180 / G_PI  ;
                else  
					  *RefractAngle  = -asin(a2*c2/c1)* 180 / G_PI  ;
					  
		        g_print(" transfer angle = %f\n" , *RefractAngle)   ;
	   	}
	   	return TRUE ;
}

/*
  Name: AngleSteerToRefract_1d_roof 
  Copyright: Doppler             
  Author:    Shen Sheng
  Date: 22-04-11 09:19
  Description:  translate the focus steer parameter into true depth in calculation 
  input : data : void pointer to DRAW_UI structure
  return  FALSE : if fail
          TRUE  : if success
  the result will be store in FocusDepth pointer memory
*/

int BeamSkewToRefract_1d_roof( gpointer data , gdouble beam_skew_angle, gdouble* RefractAngle)
{
		   DRAW_UI_P p = (DRAW_UI_P) data ;
		   //get the center probe coordinate
		   gdouble x0 , y0, z0;
		   gdouble wedgeangle = p->wedge_p->wg_wedge_angle*G_PI/180.0;
		   gdouble roofangle  = p->wedge_p->wg_roof_angle*G_PI/180.0 ;
		   gdouble Intervalx  = p->probe_p->pri_axis_pitch;
		   gdouble h0		  = p->wedge_p->wg_heigh_fir  ;
		   gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir ;
		   gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir ;
	
		   double desirex, desirey, desirez 			 ;
		   double	tanw  , tanr   , vx1	, vy1	 ,vz1;
		   double  x1 , y1 , z1 						 ;
		   double temp, TempLength						 ;
		   double len1, len2, len3						 ;
	       double para1 ,para2                           ;
		   int ElementStart = p->element_sel->primary_axis_s - 1 ;
		   int ElementColumn= p->probe_p->ele_num_pri			 ;
		   int SelectColumn = p->element_sel->pri_axis_ape		 ;
		   int ElementStop	=	SelectColumn+ ElementStart		 ;
		   gdouble a1 , a2 , vx2	                             ;
	
		   a1 = beam_skew_angle * G_PI/180.0					 ;

		   gdouble c1, c2 ; // velocity in the wedge and specimen
		   if(p->probe_p->transmi_trans_longi==0)
		   {   
				c1	= p->wedge_p->wg_lon_vel ;				 /* Ð¨¿é×Ý²¨ÉùËÙ */ 
				c2	= p->specimen->speci_transverse_wave;	 /* Ñù±¾ºá²¨ÉùËÙ */  
		   }										   
		   else 								
		   {
				c1	= p->wedge_p->wg_lon_vel ;				 /* Ð¨¿é×Ý²¨ÉùËÙ */    
				c2	= p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
		   }
		   
		   if(roofangle == 0)
		   {
				  return FALSE   ;
		   }
		   else
		   {	   //µ±roofangle ²»µÈÓÚ0
				   //  middle probe offset to the wedge coordinate
					z0 = Intervalx*ElementStart*sin(wedgeangle)   ;
					x0 = Intervalx*ElementStart*cos(wedgeangle)   ;
				   
					z0 = -(z0 + h0 + Intervalx*(SelectColumn - 1)*sin(wedgeangle)/2)               ;
					x0 = x0 + wg_pri_elem_offset_fir + Intervalx*(SelectColumn-1)*cos(wedgeangle)/2;
					if(roofangle < 0)
						 { wg_sec_elem_offset_fir =  -wg_sec_elem_offset_fir; }
					y0 = -wg_sec_elem_offset_fir; 
					
    	    		tanw = -tan(wedgeangle);
    	            tanr = tan(roofangle)  ;
    	            vx1  = tanw*tanr       ;
    	            vy1  = -(1+tanw*tanw)  ;
    	            vz1  = -tanr           ;
    		        // (x-para1)/vx2 = y-para2   
    	     		// ¹ýÌ½Í·ÓëÐ¨¿éÃæ´¹Ö±ÃæÓëZ=0ÃæµÄ½»Ïß·½³Ì
    	    		para1 = x0             ;
    	    		para2 = y0 + z0*vz1/vy1;
    	    		if(vx1 != 0)    vx2 = -vy1/vx1  ;
					else return FALSE ;
				    desirex = (vx2*x0+y0+para1/vx2 - para2)/(vx2+1/vx2);
	    		    desirey = para2 + (desirex - para1)/vx2 ;
	    		    desirez = 0 ;
                    //      skew line
                    //      -tan(a1)(x-x0) = y-y0   
                    //      get the junction of SkewLine and  (x-para1)/vx2 = y-para2					
                    if(vx1 != 0)
                    {  // µ±ROOF ½Ç´æÔÚÊ±,VX1²»¿ÉÄÜµÈÓÚ0
                            tanr = -tan(a1)         ;
                            tanw = 1/vx2            ;
                            
                            x1 = (para2 + tanr*x0 - y0 - tanw*para1) / (tanr-tanw) ;
                            y1 = tanr*(x1-x0) + y0  ;
                    }
                    else 
                    {
                            x1 = x0 + (y0 - para2)/tan(a1)  ;
                            y1 = para2                      ;
                    }
					a2   = sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1))/sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) +  z0*z0) ;
				    if(a2*c2/c1>=1) return FALSE;
					if(x1<desirex)  a2 = -a2  ;
                    *RefractAngle  = asin(a2*c2/c1)*180 / G_PI ;
			}
		    g_print("TransferAngle = %f\n",*RefractAngle);
			return TRUE ;
}


/*
  Name: ProjectionToDepth_2d_roof
  Copyright: Doppler
  Author:    Shen Sheng
  Date: 22-04-11 09:19
  Description:  translate the projection parameter into true depth for focuslaw calculation 
  input : data : void pointer to DRAW_UI structure
            angle1 : refract angle 
            angle2 : skew angle 
            Projection : projection distance
  return  FALSE : if fail
          TRUE    : if success
  the result will be store in FocusDepth pointer memory
*/

int ProjectionToDepth_2d_roof (gpointer data, gdouble angle1, gdouble angle2, double Projection, double* FocusDepth)
{
	     DRAW_UI_P p = (DRAW_UI_P) data ;
	     
	     gdouble c1 ;            // wave speed
	     gdouble c2 ;
	     gdouble k1 ;  
	     gdouble h0 =  p->wedge_p->wg_heigh_fir ;                  // first element high

	     int PriElementStart = p->element_sel->primary_axis_s -1  ;
	     int PriElementNum   = p->probe_p->ele_num_pri            ;
	     int SecElementStart = p->element_sel->seconary_axis_s -1 ;
		 int SecElementNum   = p->probe_p->ele_num_sec            ;
		 int PriElementSelect= p->element_sel->pri_axis_ape       ;
		 int SecElementSelect= p->element_sel->sec_axis_ape       ;
	     int PriElementStop  = PriElementStart +  PriElementSelect;
		 int SecElementStop  = SecElementStart +  SecElementSelect;

	     gdouble Intervaly = p->probe_p->sec_axis_pitch ;          // y direction interval
	     gdouble Intervalx = p->probe_p->pri_axis_pitch ;          // x direction interval distance
	     gdouble pri_ele_size = p->probe_p->pri_ele_size ;
	     gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	     gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	     gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
	     gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
         if(angle1 == 0 || angle1 == 90 || fabs(angle2) == 90)  return FALSE  ;
		 gdouble  a1 = angle1*PI/180;                              // refract angle
	     gdouble  a2 = angle2*PI/180;                              // deflect angle
	     double   a1Projection               ;
		 double   a2Projection               ;

	     gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180   ; // roofangle   y-z platform
	     gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ; // wedgeangle  x-z platform     
	     
	     gdouble x0,y0,z0;                                         // element center coordinate
	     //  element offset in each direction
	     gdouble x;
	     gdouble y;
	     gdouble z;
	     gdouble d;
	     gdouble s_x;
	     gdouble s_y;
	     gdouble s_zy;
	     gdouble s_zx;     
	     
		 if(PriElementStop > PriElementNum )  return FALSE;
		 if(SecElementStop > SecElementNum )  return FALSE;

	     // kill the impossible condition
		 if(p->probe_p->D1_D2 == 0) {SecElementNum = 1;  SecElementStart = 0; SecElementStop = 1;}
	     if(wedgeangle == PI/2 || roofangle == PI/2)  return FALSE;
	 
	     if(p->probe_p->transmi_trans_longi==0)
	     {   
	        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
	        c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
	     }                                           
	     else                                 
	     {
	        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
	        c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
	     }
	     // refract coefficient    
		 a1Projection = atan(tan(a1)*cos(a2));
		 a2Projection = asin(sin(a1)*c1/c2) ;
		 a2Projection = atan(tan(a2Projection)*cos(a2));


	     // element location offset calculate
	     // ÔÚROOF½Ç²»µÈÓÚ0Ê±,ÔÚ´¹Ö±ÓÚWEDGE ½ÇÉÏ±ß·½ÏòÉÏÃ¿×ßÒ»¶Î¾àÀë
	     // ¶ÔÓ¦µÄ X Y Z Èý¸ö·½ÏòÉÏ¶¼»áÓÐÒ»¸öÎ»ÖÃ±ä»¯SX SY SZ
	     if((wedgeangle != 0) && (roofangle != 0))
	     {
	          x = 1;
	          y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
	          z = y*tan(roofangle) ;
	          d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
	          s_x  = -Intervaly/d    ;
	          s_y  = -Intervaly*y/d   ;
	          s_zy  = -Intervaly*(z-tan(wedgeangle))/d   ;          
	     }
	     else
	     {   
	          s_y = -Intervaly*cos(roofangle);
	          s_x = 0 ;
	          s_zy = -Intervaly*sin(roofangle);
	     }     
		 //calc offset generated by element selection

		 z0 = SecElementStart*s_zy - PriElementStart*Intervalx*sin(wedgeangle);
		 x0 = Intervalx*cos(wedgeangle)*PriElementStart + SecElementStart*s_x ;
		 y0 = s_y*SecElementStart   ;

	     // center probe element    (x0,y0,z0)            
	     z0 = -(z0 + h0 + Intervalx*(PriElementSelect - 1)*sin(wedgeangle)/2 - s_zy*(SecElementSelect - 1)/2);
	     x0 = x0 + wg_pri_axis_reference + wg_pri_elem_offset_fir + Intervalx*(PriElementSelect - 1)*cos(wedgeangle)/2 + (SecElementSelect - 1)*s_x/2 ;
	     if(roofangle<0)
			 wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;
		 y0 = y0 -wg_sec_axis_reference - wg_sec_elem_offset_fir + s_y*(SecElementSelect - 1)/2 ;   
 
         *FocusDepth = (Projection - x0 + tan(a2Projection)*z0)/tan(a1Projection) ;
		 if(*FocusDepth<0) return FALSE ; 

          return TRUE ;
}

/*
  Name: PlaneToDepth_2d_roof 
  Copyright: Doppler             
  Author:    Shen Sheng
  Date: 22-04-11 09:19
  Description:  translate the focus Plane parameter into true depth in calculation 
  input : data : void pointer to DRAW_UI structure
            angle1 : refract angle
            angle2 : skew angle
  return  FALSE : if fail
          TRUE  : if success
  the result will be store in FocusDepth pointer memory
*/
int PlaneToDepth_2d_roof (gpointer data, gdouble angle1, gdouble angle2, double* FocusDepth)
{
	     DRAW_UI_P p = (DRAW_UI_P) data ;
	     
	     gdouble c1 ;            // wave speed
	     gdouble c2 ;
	     gdouble h0 =  p->wedge_p->wg_heigh_fir ;                  // first element high

	     int PriElementStart = p->element_sel->primary_axis_s -1  ;
	     int PriElementNum   = p->probe_p->ele_num_pri            ;
	     int SecElementStart = p->element_sel->seconary_axis_s -1 ;
		 int SecElementNum   = p->probe_p->ele_num_sec            ;
		 int PriElementSelect= p->element_sel->pri_axis_ape       ;
		 int SecElementSelect= p->element_sel->sec_axis_ape       ;
	     int PriElementStop  = PriElementStart +  PriElementSelect;
		 int SecElementStop  = SecElementStart +  SecElementSelect;

	     gdouble Intervaly = p->probe_p->sec_axis_pitch ;          // y direction interval
	     gdouble Intervalx = p->probe_p->pri_axis_pitch ;          // x direction interval distance
	     gdouble pri_ele_size = p->probe_p->pri_ele_size ;
	     gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*Ö÷ÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	     gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*´ÎÖáÐ¨¿é²Î¿¼Î»ÖÃ*/
	     gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*µÚÒ»Ö÷ÖáÕóÔªÆ«ÒÆ*/
	     gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*µÚÒ»´ÎÖáÕóÔªÆ«ÒÆ*/
	     gdouble  a1 = angle1*PI/180;                              // refract angle
	     gdouble  a2 = angle2*PI/180;                              // deflect angle
	     double   a1Projection               ;
		 double   a2Projection               ;

		 //  ssssssssssssssssssssssssssss
		 gdouble xPt1  = p->focal_point->offset_start ;
		 gdouble zPt1  = p->focal_point->depth_start  ;
		 
		 gdouble xPt2  = p->focal_point->offset_end  ;
		 gdouble zPt2  = p->focal_point->depth_end	 ;
		 gdouble k1, k2 ;  // beam line and focus plane line gradient
		 gdouble b1, b2 ;  // append coefficient ot beam line and focus plane line

	     gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180   ; // roofangle   y-z platform
	     gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ; // wedgeangle  x-z platform     
	     
	     gdouble xTemp, yTemp, zTemp ;
	     gdouble x0,y0,z0;                                         // element center coordinate
	     gdouble xP, yP, zP;                                       // focus point coordinate
	     //  element offset in each direction
	     gdouble x;
	     gdouble y;
	     gdouble z;
	     gdouble d;
	     gdouble s_x;
	     gdouble s_y;
	     gdouble s_zy;
	     gdouble s_zx;     
	
		 if(PriElementStop > PriElementNum )  return ;
		 if(SecElementStop > SecElementNum )  return ;	 
     
	     // kill the impossible condition
		 if(p->probe_p->D1_D2 == 0) {SecElementNum = 1;  SecElementStart = 0; SecElementStop = 1;}
	     if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
	 
	     if(p->probe_p->transmi_trans_longi==0)
	     {   
	        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */ 
	        c2  = p->specimen->speci_transverse_wave;    /* Ñù±¾ºá²¨ÉùËÙ */  
	     }                                           
	     else                                 
	     {
	        c1  = p->wedge_p->wg_lon_vel ;               /* Ð¨¿é×Ý²¨ÉùËÙ */    
	        c2  = p->specimen->speci_longitudinal_wave;  /* Ñù±¾×Ý²¨ÉùËÙ */
	     }
		 a1Projection = atan(tan(a1)*cos(a2));
		 a2Projection = asin(sin(a1)*c1/c2) ;
		 a2Projection = atan(tan(a2Projection)*cos(a2));

	     // element location offset calculate
	     // ÔÚROOF½Ç²»µÈÓÚ0Ê±,ÔÚ´¹Ö±ÓÚWEDGE ½ÇÉÏ±ß·½ÏòÉÏÃ¿×ßÒ»¶Î¾àÀë
	     // ¶ÔÓ¦µÄ X Y Z Èý¸ö·½ÏòÉÏ¶¼»áÓÐÒ»¸öÎ»ÖÃ±ä»¯SX SY SZ
	     if((wedgeangle != 0) && (roofangle != 0))
	     {
	          x = 1;
	          y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
	          z = y*tan(roofangle) ;
	          d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
	          s_x  = -Intervaly/d    ;
	          s_y  = -Intervaly*y/d   ;
	          s_zy  = -Intervaly*(z-tan(wedgeangle))/d   ;          
	     }
	     else
	     {   
	          s_y = -Intervaly*cos(roofangle);
	          s_x = 0 ;
	          s_zy = -Intervaly*sin(roofangle);
	     }     
		 //calc offset generated by element selection

		 z0 = SecElementStart*s_zy - PriElementStart*Intervalx*sin(wedgeangle);
		 x0 = Intervalx*cos(wedgeangle)*PriElementStart + SecElementStart*s_x ;
		 y0 = s_y*SecElementStart	;
		 
		 // center probe element	(x0,y0,z0)			  
		 z0 = -(z0 + h0 + Intervalx*(PriElementSelect - 1)*sin(wedgeangle)/2 - s_zy*(SecElementSelect - 1)/2);
		 x0 = x0 + wg_pri_axis_reference + wg_pri_elem_offset_fir + Intervalx*(PriElementSelect - 1)*cos(wedgeangle)/2 + (SecElementSelect - 1)*s_x/2 ;
		 if(roofangle<0)
			 wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir;
		 y0 = y0 -wg_sec_axis_reference - wg_sec_elem_offset_fir + s_y*(SecElementSelect - 1)/2 ;	

       
		if(xPt2 != xPt1)
		{
				k2	= (zPt2 - zPt1)/(xPt2 - xPt1)	  ;
				k1	= 1/tan(a1Projection)  		      ;
				if( k1 == k2 )
					  return FALSE					  ;
				b1 = -k1*(x0 + fabs(z0)*tan(a2Projection))  ;
				b2 = -k2 * xPt1 + zPt1				  ;
				x = (b1-b2) / ( k2 - k1)			  ;
				z = k1 * (x - x0 - fabs(z0)*tan(a2Projection)) ;
				if( z<=0 )  return FALSE			  ;
				*FocusDepth = z					      ;
		}
		else
		{
                k1 = 1/tan(a1Projection)              ;
				*FocusDepth = k1 * (xPt1 - x0 - tan(a2Projection)*fabs(z0));
				if(*FocusDepth<0) return FALSE	      ; 
		}
		return TRUE 						          ;

}


