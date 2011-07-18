/************************************************* 
               OpenGL 
 ************************************************* */

#include "drawui.h"
#include "trackball.h"
#include <math.h>
#define PI G_PI
#define material_w_h 130
static float view_quat[4] = { 0.0, 0.0, 0.0, 1.0 };

/* 函数声明 */
void realize (GtkWidget *widget,gpointer   data);
gboolean configure_event (GtkWidget *widget,GdkEventConfigure *event, gpointer data);
gboolean expose_event (GtkWidget *widget,GdkEventExpose *event, gpointer data);
gboolean key_press_event (GtkWidget *widget,GdkEventKey *event,gpointer data);
gboolean scroll_event (GtkWidget *widget,GdkEventScroll *event,gpointer data);
gboolean button_press_event (GtkWidget *widget,GdkEventButton *event,gpointer data);
gboolean motion_notify_event (GtkWidget *widget,GdkEventMotion *event,gpointer data);
gboolean PointInWedgeBottonRect(gpointer data);


void DrawAxis(gpointer data);/* 画坐标轴函数 */ 
void Drawcylindrical(gpointer data) ;
// for 2d situation 
void DrawFlat2D         (gpointer data);
void DrawFocusResult (gpointer data);
void DrawElement_2D_Flat       (gpointer data);
void DrawWedge2D     (gpointer data);
void DrawWedge2D_Cylinder_OD    (gpointer data);
void DrawWedge2D_Cylinder_ID(gpointer data);
void DrawElement2DCylinderOD     (gpointer data);
void DrawElement2DCylinderID (gpointer data);
// pitch and catch
void DrawWedgePitchReceive(gpointer data);
void DrawElement_2D_FlatPitchReceive(gpointer data);  
void DrawWedge2D_Inverse     (gpointer data);
void DrawElement_2D_Flat2D_Inverse      (gpointer data);
void DrawCylinderWedgePitchReceiveOD(gpointer data);
void DrawCylinderWedgePitchReceiveID(gpointer data);
void DrawCylinderWedgeInverseOD(gpointer data);
void DrawCylinderWedgeInverseID(gpointer data);
void DrawElementCylinderPitchReceiveOD(gpointer data);
void DrawElementCylinderReceiverOD     (gpointer data);
void DrawElementCylinderPitchReceiveID(gpointer data);
void DrawElementCylinderReceiverID     (gpointer data);
void DrawWedge2DReceiver(gpointer data);
void DrawWedge2DReceiverInverse(gpointer data);
void DrawElement2DReceiver(gpointer data);
void DrawCylinderWedgeReceiverOD(gpointer data);
void DrawCylinderWedgeReceiverInverseOD(gpointer data);
void DrawCylinderWedgeReceiverID(gpointer data);
void DrawCylinderWedgeReceiverInverseID(gpointer data);
void DrawWedge2D_Cylinder_OD_Zero    (gpointer data);
void DrawWedge2D_Cylinder_OD_Inverse_Zero    (gpointer data);
void DrawWedge2D_Cylinder_ID_Zero    (gpointer data);
void DrawWedge2D_Cylinder_ID_Inverse_Zero    (gpointer data);
void DrawElement2DCylinderOD_Zero  (gpointer data) ;
void DrawElement2DCylinderID_Zero  (gpointer data);


void realize (GtkWidget *widget,gpointer   data)
{
  DRAW_UI_P p = (DRAW_UI_P)(data);
  GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);
  /*** OpenGL BEGIN ***/
  if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
    return;
  glEnable(GL_BLEND);   //   打开混合 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor( 0.99, 0.99, 0.99, 1 );
  glColor3f( 1.0f, 0.0f, 0.0f ); 
  gdk_gl_drawable_gl_end (gldrawable);
  /*** OpenGL END ***/
}

gboolean configure_event (GtkWidget *widget,GdkEventConfigure *event, gpointer data)
{
  DRAW_UI_P p = (DRAW_UI_P)(data);
  GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);
  GLfloat w = widget->allocation.width;//
  GLfloat h = widget->allocation.height;//
  /*** OpenGL BEGIN ***/
  if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
    return FALSE;
    
  GLfloat nRange = 200.0f;
    // Prevent a divide by zero
    if(h == 0)
        h = 1;
    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);
    // Reset projection matrix stack
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*1000, nRange*1000);
    else 
        glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*1000, nRange*1000);
    // Reset Model view matrix stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

  gdk_gl_drawable_gl_end (gldrawable);
  /*** OpenGL END ***/

  return TRUE;
}

gboolean expose_event (GtkWidget *widget,GdkEventExpose *event, gpointer data)
{
      DRAW_UI_P p = (DRAW_UI_P)(data);
      GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
      GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);
      gdouble wg_roof_angle =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
      float m[4][4];
      
      /*** OpenGL BEGIN ***/
      if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
        return FALSE;
        glClear (GL_COLOR_BUFFER_BIT);
        
        glLoadIdentity();
        glScalef(xScale ,yScale ,zScale);
        glTranslatef(xTranslate,yTranslate,0.0f);                    
              
    #if 0
        /* 键盘旋转 */      
        glRotatef(spinx, 1.0f, 0.0f, 0.0f);
        glRotatef(spiny, 0.0f, 1.0f, 0.0f);
        glRotatef(spinz, 0.0f, 0.0f, 1.0f);
    #endif           
        
    
    glPushMatrix (); 
    switch(p->view)//选择视图
    {
       case 0://左视图 
            glRotatef(90, 0.0f, 1.0f, 0.0f); 
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            break; 
       case 1://主视图 
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            break;
       case 2://俯视图
            //default  do nothing
            break; 
       default ://3D视图单独处理 ：见expose_event_3d 
            break; 
    }
      
    if(!p->probe_p->Pitch_Catch)
    {
        switch(p->probe_p->D1_D2)
        {                         
            case 0:     /* 1-D聚焦算法 */
                switch(p->specimen->flat_cylindrical)
                {
                   case 0:         /*如果选中 Flat*/         
                   	     DrawFlat2D(p);
                         if(wg_roof_angle>=0)
						   DrawWedge2D(p);
						 else 
						   DrawWedge2D_Inverse(p);
                         DrawElement_2D_Flat(p);  
                      break;
                   case 1:        /* 如果选中 Cylindrical */     
					   Drawcylindrical(p);
					   if(!strcmp(p->specimen->Inspection_od_id,"OD"))
					   {  
						   if( p->location->rotation_z == 90.0)
						   {
							   if(p->wedge_p->wg_roof_angle>=0)
									 DrawWedge2D_Cylinder_OD(p) ;
							   else 
									 DrawCylinderWedgeInverseOD(p);
							   DrawElement2DCylinderOD(p);
							  
						   }
						   else if(p->location->rotation_z == 0)
						   {
							   if (p->wedge_p->wg_roof_angle>=0)   
							   DrawWedge2D_Cylinder_OD_Zero(p) ;
							   else
							   DrawWedge2D_Cylinder_OD_Inverse_Zero(p) ;
							   DrawElement2DCylinderOD_Zero(p);
						   }
					   }
					   else
					   {
						   if(p->location->rotation_z == 90.0)
						   {
							   if(p->wedge_p->wg_roof_angle>=0)
									DrawWedge2D_Cylinder_ID(p);
							   else 
									DrawCylinderWedgeInverseID(p);
							   DrawElement2DCylinderID(p);	 
						   }
						   else if(p->location->rotation_z == 0)
						   {
							   if (p->wedge_p->wg_roof_angle>=0)   
							   DrawWedge2D_Cylinder_ID_Zero(p) ;
							   else
							   DrawWedge2D_Cylinder_ID_Inverse_Zero(p) ;
							   DrawElement2DCylinderID_Zero(p);
						   } 
					   }

                   break;     
                }                 
             break;    
           case 1:     /* 2-D聚焦算法 */
            if(p->specimen->flat_cylindrical == 0 )
            {  
                   DrawFlat2D(p);
				   if(p->wedge_p->wg_roof_angle>=0)
                        DrawWedge2D(p);
				   else
				   	    DrawWedge2D_Inverse(p);
                   DrawElement_2D_Flat(p);
            }
            else
            {
				Drawcylindrical(p);
				if(!strcmp(p->specimen->Inspection_od_id,"OD"))
				{  
					if( p->location->rotation_z == 90.0)
					{
						if(p->wedge_p->wg_roof_angle>=0)
							  DrawWedge2D_Cylinder_OD(p) ;
						else 
							  DrawCylinderWedgeInverseOD(p);
						DrawElement2DCylinderOD(p);
					   
					}
					else if(p->location->rotation_z == 0)
					{
						if (p->wedge_p->wg_roof_angle>=0)	
						DrawWedge2D_Cylinder_OD_Zero(p) ;
						else
						DrawWedge2D_Cylinder_OD_Inverse_Zero(p) ;
						DrawElement2DCylinderOD_Zero(p);
					}
				}
				else
				{
					if(p->location->rotation_z == 90.0)
					{
						if(p->wedge_p->wg_roof_angle>=0)
							 DrawWedge2D_Cylinder_ID(p);
						else 
							 DrawCylinderWedgeInverseID(p);
						DrawElement2DCylinderID(p);   
					}
					else if(p->location->rotation_z == 0)
					{
						if (p->wedge_p->wg_roof_angle>=0)	
						DrawWedge2D_Cylinder_ID_Zero(p) ;
						else
						DrawWedge2D_Cylinder_ID_Inverse_Zero(p) ;
						DrawElement2DCylinderID_Zero(p);
					} 
				}


            }
            break;
        }
    }
    else
    {
       if(p->probe_p->D1_D2 ==0)
       {
            if(p->specimen->flat_cylindrical == 0 )
            {            	  
                  DrawFlat2D(p);
                  DrawWedgePitchReceive(p);
                  DrawElement_2D_FlatPitchReceive(p);
            }
			else
			{
				   Drawcylindrical(p);
                   if(!strcmp(p->specimen->Inspection_od_id,"OD"))
                   {	   
                         DrawCylinderWedgePitchReceiveOD(p) ;
				         DrawElementCylinderPitchReceiveOD(p);
                   }
                   else
                   {
                         DrawCylinderWedgePitchReceiveID(p);
						 DrawElementCylinderPitchReceiveID(p);		
                   }    
			}
       }
	   else
	   {
	        if(p->specimen->flat_cylindrical == 0 )
            {
            	  DrawFlat2D(p);
                  DrawWedgePitchReceive(p);
                  DrawElement_2D_FlatPitchReceive(p);
            }
			else
			{
			       Drawcylindrical(p);
                   if(!strcmp(p->specimen->Inspection_od_id,"OD"))
                   {	   
                         DrawCylinderWedgePitchReceiveOD(p) ;
				         DrawElementCylinderPitchReceiveOD(p);
                   }
                   else
                   {
                         DrawCylinderWedgePitchReceiveID(p);
						 DrawElementCylinderPitchReceiveID(p);		
                   }
			}
	   }
    }
    
    if( p->is_draw_focus)
         DrawFocusResult(p);       
    DrawAxis(p);
    glColor3f( 1.0f, 0.0f, 0.0f );
    gdk_gl_draw_tetrahedron (FALSE);
    glPopMatrix ();  
   
    if (gdk_gl_drawable_is_double_buffered (gldrawable))
        gdk_gl_drawable_swap_buffers (gldrawable);
    else
       glFlush ();
    gdk_gl_drawable_gl_end (gldrawable);
  /*** OpenGL END ***/
  return TRUE;
}
//
gboolean expose_event_3d (GtkWidget *widget,GdkEventExpose *event, gpointer data)
{
  DRAW_UI_P p = (DRAW_UI_P)(data);
  GdkGLContext *glcontext = gtk_widget_get_gl_context (widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);
  gdouble wg_roof_angle =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
  float m[4][4];
  
  /*** OpenGL BEGIN ***/
  if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
    return FALSE;
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
        
    glTranslatef(xTranslate,yTranslate,0.0f);
    glScalef(xScale ,yScale ,zScale); 
         
    /* 轨迹球旋转 */
    build_rotmatrix (m, view_quat);
    glMultMatrixf (&m[0][0]);
    
glPushMatrix (); 

    glRotatef(140, 1.0f, 0.0f, 0.0f); 
    glRotatef(340, 0.0f, 0.0f, 1.0f); 
    if(!p->probe_p->Pitch_Catch)
    {
        switch(p->probe_p->D1_D2)
        {                         
            case 0:     /* 1-D聚焦算法 */
                switch(p->specimen->flat_cylindrical)
                {
                   case 0:         /*如果选中 Flat*/         
                   	     DrawFlat2D(p);
                         if(wg_roof_angle>=0)
						   DrawWedge2D(p);
						 else 
						   DrawWedge2D_Inverse(p);
                         DrawElement_2D_Flat(p);  
                      break;
                   case 1:        /* 如果选中 Cylindrical */     
						   Drawcylindrical(p);
						   if(!strcmp(p->specimen->Inspection_od_id,"OD"))
						   {  
							   if( p->location->rotation_z == 90.0)
							   {
								   if(p->wedge_p->wg_roof_angle>=0)
										 DrawWedge2D_Cylinder_OD(p) ;
								   else 
										 DrawCylinderWedgeInverseOD(p);
								   DrawElement2DCylinderOD(p);
								  
							   }
							   else if(p->location->rotation_z == 0)
							   {
							       if (p->wedge_p->wg_roof_angle>=0)   
								   DrawWedge2D_Cylinder_OD_Zero(p) ;
								   else
								   DrawWedge2D_Cylinder_OD_Inverse_Zero(p) ;
								   DrawElement2DCylinderOD_Zero(p);
							   }
						   }
						   else
						   {
							   if(p->location->rotation_z == 90.0)
							   {
								   if(p->wedge_p->wg_roof_angle>=0)
										DrawWedge2D_Cylinder_ID(p);
								   else 
										DrawCylinderWedgeInverseID(p);
								   DrawElement2DCylinderID(p);	 
							   }
							   else if(p->location->rotation_z == 0)
							   {
								   if (p->wedge_p->wg_roof_angle>=0)   
								   DrawWedge2D_Cylinder_ID_Zero(p) ;
								   else
								   DrawWedge2D_Cylinder_ID_Inverse_Zero(p) ;
								   DrawElement2DCylinderID_Zero(p);
							   } 
						   }
                   break;     
                }                 
             break;    
           case 1:     /* 2-D聚焦算法 */
            if(p->specimen->flat_cylindrical == 0 )
            {  
                   DrawFlat2D(p);
				   if(p->wedge_p->wg_roof_angle>=0)
                        DrawWedge2D(p);
				   else
				   	    DrawWedge2D_Inverse(p);
                   DrawElement_2D_Flat(p);
            }
            else
            {
						   Drawcylindrical(p);
						   if(!strcmp(p->specimen->Inspection_od_id,"OD"))
						   {  
							   if( p->location->rotation_z == 90.0)
							   {
								   if(p->wedge_p->wg_roof_angle>=0)
										 DrawWedge2D_Cylinder_OD(p) ;
								   else 
										 DrawCylinderWedgeInverseOD(p);
								   DrawElement2DCylinderOD(p);
								  
							   }
							   else if(p->location->rotation_z == 0)
							   {
							       if (p->wedge_p->wg_roof_angle>=0)   
								   DrawWedge2D_Cylinder_OD_Zero(p) ;
								   else
								   DrawWedge2D_Cylinder_OD_Inverse_Zero(p) ;
								   DrawElement2DCylinderOD_Zero(p);
							   }
						   }
						   else
						   {
							   if(p->location->rotation_z == 90.0)
							   {
								   if(p->wedge_p->wg_roof_angle>=0)
										DrawWedge2D_Cylinder_ID(p);
								   else 
										DrawCylinderWedgeInverseID(p);
								   DrawElement2DCylinderID(p);	 
							   }
							   else if(p->location->rotation_z == 0)
							   {
								   if (p->wedge_p->wg_roof_angle>=0)   
								   DrawWedge2D_Cylinder_ID_Zero(p) ;
								   else
								   DrawWedge2D_Cylinder_ID_Inverse_Zero(p) ;
								   DrawElement2DCylinderID_Zero(p);
							   } 
						   }
            }
            break;
        }
    }
    else
    {
       if(p->probe_p->D1_D2 ==0)
       {
            if(p->specimen->flat_cylindrical == 0 )
            {            	  
                  DrawFlat2D(p);
                  DrawWedgePitchReceive(p);
                  DrawElement_2D_FlatPitchReceive(p);
            }
			else
			{
				   Drawcylindrical(p);
                   if(!strcmp(p->specimen->Inspection_od_id,"OD"))
                   {	   
                         DrawCylinderWedgePitchReceiveOD(p) ;
				         DrawElementCylinderPitchReceiveOD(p);
                   }
                   else
                   {
                         DrawCylinderWedgePitchReceiveID(p);
						 DrawElementCylinderPitchReceiveID(p);		
                   }    
			}
       }
	   else
	   {
	        if(p->specimen->flat_cylindrical == 0 )
            {
            	  DrawFlat2D(p);
                  DrawWedgePitchReceive(p);
                  DrawElement_2D_FlatPitchReceive(p);
            }
			else
			{
			       Drawcylindrical(p);
                   if(!strcmp(p->specimen->Inspection_od_id,"OD"))
                   {	   
                         DrawCylinderWedgePitchReceiveOD(p) ;
				         DrawElementCylinderPitchReceiveOD(p);
                   }
                   else
                   {
                         DrawCylinderWedgePitchReceiveID(p);
						 DrawElementCylinderPitchReceiveID(p);		
                   }
			}
	   }
    }
    
    if( p->is_draw_focus)
         DrawFocusResult(p);       
    DrawAxis(p);
    glColor3f( 1.0f, 0.0f, 0.0f );
    gdk_gl_draw_tetrahedron (FALSE);
    glPopMatrix ();  
   
    if (gdk_gl_drawable_is_double_buffered (gldrawable))
        gdk_gl_drawable_swap_buffers (gldrawable);
    else
       glFlush ();
    gdk_gl_drawable_gl_end (gldrawable);
  /*** OpenGL END ***/
  return TRUE;
}

/* 键盘响应事件 */
gboolean key_press_event (GtkWidget *widget,GdkEventKey *event,gpointer data)
{  
  switch(event->keyval) {
    case GDK_Up:
         //g_print("Up\n"); 
         break;
    case GDK_Left:
         //g_print("Left\n");
         break;
    case GDK_Right:
         //g_print("Right\n");
         break;
    case GDK_Down:
         //g_print("Down\n");
         break;
    case GDK_Escape:
        // gtk_main_quit();
         break;
    case GDK_F1:
        // spinx += 5.0f;
	    // if (spinx > 360.0f) spinx -= 360.0f;
         break;
    case GDK_F2:
        // spinx -= 5.0f;
	    // if (spinx > 360.0f) spinx -= 360.0f;
         break;
    case GDK_F3:
        // spiny += 5.0f;
	    // if (spiny > 360.0f) spiny -= 360.0f;
         break;
    case GDK_F4:
       //  spiny -= 5.0f;
	   //  if (spiny > 360.0f) spiny -= 360.0f;
         break;
    case GDK_F5:
       //  spinz += 5.0f;
	   //  if (spinz > 360.0f) spinz -= 360.0f;
         break;
    case GDK_F6:
       //  spinz -= 5.0f;
	   //  if (spinz > 360.0f) spinz -= 360.0f;
         break;  
      }    
      
    /* Invalidate the whole window.
    gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);*/ 
    /* Update synchronously. 
    gdk_window_process_updates (widget->window, FALSE);*/
    return FALSE;
}

/* 鼠标滚轮响应事件 */
gboolean scroll_event (GtkWidget *widget,GdkEventScroll *event,gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    
    if(event->direction ==  GDK_SCROLL_UP)
    {
         xScale +=0.2f;
         yScale +=0.2f;
         zScale +=0.2f;  
              
    }
    else if(event->direction ==  GDK_SCROLL_DOWN)
    {
         xScale -=0.2f;
         yScale -=0.2f;
         zScale -=0.2f; 
         if(xScale <=0.0f)  xScale =0.1f;
         if(yScale <=0.0f)  yScale =0.1f;
         if(zScale <=0.0f)  zScale =0.1f;
        
    }
     
    /* Invalidate the whole window. */
    gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);
    /* Update synchronously. */
    gdk_window_process_updates (widget->window, FALSE);
    return FALSE;
}

/*鼠标响应事件*/
gboolean button_press_event (GtkWidget *widget,GdkEventButton *event,gpointer data)
{
  DRAW_UI_P p = (DRAW_UI_P)(data);
  switch(event->button)
  {
     case 1 :
          //g_printf("left mouse button\n");
          /* 记录鼠标左键按下位置 */
          pre_point_x=event->x;
          pre_point_y=event->y;
          break; 
     case 2 :
          //g_printf("middle mouse button \n");
          /* 按鼠标中间恢复到初始状态 */
          xScale =yScale=zScale=1.0f;
          xTranslate=yTranslate=0.0f;
          spinx=spiny=spinz=0.0f;
          break;
     case 3 :
          //g_printf("right mouse button\n");
          /* 记录鼠标右键按下位置 */
          xBegin=event->x;
          yBegin=event->y;
          break;              
  }
      /* Invalidate the whole window. */
      gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);
      /* Update synchronously. */
      gdk_window_process_updates (widget->window, FALSE);
      return FALSE;
}

/* 鼠标拖拽事件 */
gboolean motion_notify_event(GtkWidget *widget,GdkEventMotion *event,gpointer data)
{
      DRAW_UI_P p = (DRAW_UI_P)(data);
      gdouble w = widget->allocation.width;
      gdouble h = widget->allocation.height;
      float x = event->x;
      float y = event->y;
      float d_quat[4];
      
      /****************************************
       **********鼠标左键拖动--Rotation********/
      if(p->view == 3)
      {
          if (event->state & GDK_BUTTON1_MASK )
          {
              trackball (d_quat ,(2.0 * pre_point_x - w)/w ,(h - 2.0 * pre_point_y)/h ,(2.0 * x - w)/w ,(h - 2.0 * y)/h);
              add_quats (d_quat, view_quat, view_quat);
            
              pre_point_x = x;
              pre_point_y = y;    
          }   
      }
     /******************************************
       ******鼠标右键拖动************************/
     if (event->state & GDK_BUTTON3_MASK)
     {
          gdouble xlast,ylast;
          
          xlast=event->x;
          ylast=event->y;
          
          xTranslate +=  (xlast - xBegin) ;
          yTranslate += -(ylast - yBegin) ;
          /*将当前点赋给前一个点*/
          xBegin=xlast;
          yBegin=ylast;
     }
      /* Invalidate the whole window. */
      gdk_window_invalidate_rect (widget->window, &widget->allocation, FALSE);
      /* Update synchronously. */
      gdk_window_process_updates (widget->window, FALSE);
      return TRUE;  
}

/* 画坐标轴x、y、z */ 
void DrawAxis(gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    
    glPushMatrix ();
    switch(p->specimen->flat_cylindrical)
    {
       case 0:
            glTranslatef(-(material_w_h+60),0.0f,0.0f);
            break; 
       case 1:
            glTranslatef(-(p->specimen->speci_outside_cylindrical+60),0.0f,0.0f);
            break;                                 
    }
    
    glScalef(0.5 ,0.5 ,0.5);
    
    {
        glColor3f( 0.0f, 0.0f, 1.0f );//指定线的颜色,蓝色
        glBegin( GL_LINES );
        {
            // x-axis
            glVertex3f( 0.0f, 0.0f, 0.0f);
            glVertex3f( 50.0f, 0.0f, 0.0f);
            // x-axis arrow
            glVertex3f( 50.0f, 0.0f, 0.0f);
            glVertex3f( 43.0f, 3.0f, 0.0f);
            glVertex3f( 50.0f, 0.0f, 0.0f);
            glVertex3f( 43.0f,-3.0f, 0.0f);
            
            glVertex3f( 60.0f, 3.0f, 0.0f);
            glVertex3f( 70.0f, -3.0f, 0.0f);
            glVertex3f( 60.0f, -3.0f, 0.0f);
            glVertex3f( 70.0f, 3.0f, 0.0f);
        }
        glEnd();
        glColor3f( 0.0f, 1.0f, 0.0f );//指定线的颜色,绿色

        glBegin( GL_LINES );
        {
            // y-axis
            glVertex3f( 0.0f,  0.0f, 0.0f);
            glVertex3f( 0.0f,  -50.0f, 0.0f);
            
            glVertex3f( 0.0f,  -50.0f, 0.0f);
            glVertex3f( 3.0f,  -43.0f, 0.0f);
            glVertex3f( 0.0f,  -50.0f, 0.0f);
            glVertex3f( -3.0f,  -43.0f, 0.0f);
            
            glVertex3f(  0.0f,  -60.0f, 0.0f);
            glVertex3f( -3.0f,  -65.0f, 0.0f);
            glVertex3f( -3.0f,  -50.0f, 0.0f);
            glVertex3f(  3.0f,  -65.0f, 0.0f);
        }
        glEnd();
        glColor3f( 1.0f, 0.0f, 0.0f );//指定线的颜色,红色

        glBegin( GL_LINES );
        {
            // z-axis
            glVertex3f( 0.0f, 0.0f, 0.0f );
            glVertex3f( 0.0f, 0.0f, 50.0f );
            
            glVertex3f( 0.0f,  0.0f, 50.0f );
            glVertex3f( 0.0f,  3.0f, 43.0f );
            glVertex3f( 0.0f,  0.0f, 50.0f );
            glVertex3f( 0.0f, -3.0f, 43.0f);
            
            glVertex3f( 0.0f, -3.0f, 60.0f );
            glVertex3f( 0.0f, +3.0f, 60.0f );
            glVertex3f( 0.0f, -2.0f, 65.0f );
            glVertex3f( 0.0f, +2.0f, 65.0f);
            glVertex3f( 0.0f, -3.0f, 70.0f );
            glVertex3f( 0.0f, +3.0f, 70.0f );
            glVertex3f( 0.0f, +3.0f, 60.0f );
            glVertex3f( 0.0f, -3.0f, 70.0f);
        }
        glEnd();
    }
    
    glPopMatrix ();
}

void           
DrawFlat2D(gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);     
     
     glPushMatrix (); 
    /*绘制工件*/
    glColor4f(0.75f, 0.75f, 0.75f, 0.3); // Full Brightness.  50% Alpha               
    glBegin(GL_QUADS);
        //front
        glVertex3f(-material_w_h,  material_w_h, 50);
        glVertex3f(-material_w_h, -material_w_h, 50);
        glVertex3f( material_w_h, -material_w_h, 50);
        glVertex3f( material_w_h,  material_w_h, 50);

        //bottom
        glVertex3f(-material_w_h, -material_w_h,  50);
        glVertex3f( material_w_h, -material_w_h,  50);
        glVertex3f( material_w_h, -material_w_h,   0);
        glVertex3f(-material_w_h, -material_w_h,   0);

        //back
        glVertex3f( material_w_h,  material_w_h,   0);
        glVertex3f( material_w_h, -material_w_h,   0);
        glVertex3f(-material_w_h, -material_w_h,   0);
        glVertex3f(-material_w_h,  material_w_h,   0);
    
        //top
        glVertex3f(-material_w_h, material_w_h,  50);
        glVertex3f( material_w_h, material_w_h,  50);
        glVertex3f( material_w_h, material_w_h,   0);
        glVertex3f(-material_w_h, material_w_h,   0);

        //left
        glVertex3f(-material_w_h,  material_w_h,  50);
        glVertex3f(-material_w_h, -material_w_h,  50);
        glVertex3f(-material_w_h, -material_w_h,   0);
        glVertex3f(-material_w_h,  material_w_h,   0);

        //right
        glVertex3f(material_w_h,  material_w_h,  50);
        glVertex3f(material_w_h, -material_w_h,  50);
        glVertex3f(material_w_h, -material_w_h,   0);
        glVertex3f(material_w_h,  material_w_h,   0);
   glEnd();
   
   /*绘制工件边框效果*/
    glColor3f(0.0f, 0.0f, 0.0f);             
    glBegin(GL_LINE_LOOP);
        //front
        glVertex3f(-material_w_h,  material_w_h, 50);
        glVertex3f(-material_w_h, -material_w_h, 50);
        glVertex3f( material_w_h, -material_w_h, 50);
        glVertex3f( material_w_h,  material_w_h, 50);
    glEnd();
    glBegin(GL_LINE_LOOP);
        //bottom
        glVertex3f(-material_w_h, -material_w_h,  50);
        glVertex3f( material_w_h, -material_w_h,  50);
        glVertex3f( material_w_h, -material_w_h,   0);
        glVertex3f(-material_w_h, -material_w_h,   0);
    glEnd();
    glBegin(GL_LINE_LOOP);
        //back
        glVertex3f( material_w_h,  material_w_h,   0);
        glVertex3f( material_w_h, -material_w_h,   0);
        glVertex3f(-material_w_h, -material_w_h,   0);
        glVertex3f(-material_w_h,  material_w_h,   0);
    glEnd();
    glBegin(GL_LINE_LOOP);
        //top
        glVertex3f(-material_w_h, material_w_h,  50);
        glVertex3f( material_w_h, material_w_h,  50);
        glVertex3f( material_w_h, material_w_h,   0);
        glVertex3f(-material_w_h, material_w_h,   0);
    glEnd();
    glBegin(GL_LINE_LOOP);
        //left
        glVertex3f(-material_w_h,  material_w_h,  50);
        glVertex3f(-material_w_h, -material_w_h,  50);
        glVertex3f(-material_w_h, -material_w_h,   0);
        glVertex3f(-material_w_h,  material_w_h,   0);
    glEnd();
    glBegin(GL_LINE_LOOP);
        //right
        glVertex3f(material_w_h,  material_w_h,  50);
        glVertex3f(material_w_h, -material_w_h,  50);
        glVertex3f(material_w_h, -material_w_h,   0);
        glVertex3f(material_w_h,  material_w_h,   0);
   glEnd();
   glPopMatrix ();     
                 
}

/*画圆弧工件*/
void Drawcylindrical(gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    
    gdouble inside_r,outside_r,length,w;
    
    inside_r = p->specimen->speci_inside_cylindrical/2; /*圆柱内径*/
    outside_r= p->specimen->speci_outside_cylindrical/2;/*圆柱外径*/
    length   = p->specimen->speci_length_cylindrical;   /*圆柱长度*/
    
    glPushMatrix (); 
    glColor4f(0.75f, 0.75f, 0.75f, 0.3); // Full Brightness.  50% Alpha
    glRotatef(p->location->rotation_z, 0.0f, 0.0f, 1.0f);
    /*绘制工件*/
    glBegin(GL_QUAD_STRIP);
    for(w=0;w<=2*PI;w+=0.01)
       {
            glVertex3f(length/2, inside_r*cos(w),inside_r*sin(w));
            glVertex3f(-length/2,inside_r*cos(w),inside_r*sin(w));
       }
    glEnd();
    //
    glBegin(GL_QUAD_STRIP);
    for(w=0;w<=2*PI;w+=0.01)
       {
        if(w==2*PI)w=0.02;
        glVertex3f(length/2, outside_r*cos(w),outside_r*sin(w));
        glVertex3f(-length/2,outside_r*cos(w),outside_r*sin(w));
       }
    glEnd();
    //
    glBegin(GL_QUAD_STRIP);
    for(w=0;w<=2*PI;w+=0.01)
       {
        glVertex3f(length/2,inside_r*cos(w),inside_r*sin(w));
        glVertex3f(length/2,outside_r*cos(w),outside_r*sin(w));
       }
    glEnd();
    //
    glBegin(GL_QUAD_STRIP);
    for(w=0;w<=2*PI;w+=0.01)
       {
        if(w==2*PI)w=0.02;
        glVertex3f(-length/2,inside_r*cos(w),inside_r*sin(w));
        glVertex3f(-length/2,outside_r*cos(w),outside_r*sin(w));
       }
    glEnd();
    
    /*绘制边框效果*/  
    glColor3f(0.0f, 0.0f, 0.0f);           
    glBegin(GL_LINE_LOOP);
    for(w=0;w<=2*PI;w+=0.01)
       {
        glVertex3f(length/2,inside_r*cos(w),inside_r*sin(w));
       }
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    for(w=0;w<=2*PI;w+=0.01)
       {
        glVertex3f(length/2,outside_r*cos(w),outside_r*sin(w));
       }
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    for(w=0;w<=2*PI;w+=0.01)
       {
        glVertex3f(-length/2,inside_r*cos(w),inside_r*sin(w));
       }
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    for(w=0;w<=2*PI;w+=0.01)
       {
        glVertex3f(-length/2,outside_r*cos(w),outside_r*sin(w));
       }
    glEnd();
    glPopMatrix (); 
}

void DrawWedge2D(gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
    gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;
    
    wedgeangle=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
    wg_heigh_fir=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width =p->wedge_p->wg_width;     /*楔块宽度*/
    length=p->wedge_p->wg_length;    /*楔块长度*/
    height=p->wedge_p->wg_height;/*楔块高度*/
       
    if(wedgeangle==PI/2||roofangle==PI/2)  return ;
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
 
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    
    glPushMatrix ();
    glTranslatef(wg_pri_axis_reference,-wg_sec_axis_reference,0.0f);       
   /*绘制楔块*/ 
   glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha               
       // button z = 0
       glBegin(GL_QUADS);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       // front y = 0 
       glBegin(GL_POLYGON);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
              glVertex3f(length,0,-height);
           }
           else   
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
           glVertex3f(length,0,0);
       glEnd();
       //    x = 0
       glBegin(GL_POLYGON);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
               glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
               glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
          //  xie  jiao
       glBegin(GL_POLYGON);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                glVertex3f(0,-width,-h_small -width*tan(roofangle));
           }
       glEnd();
         // TOP
       glBegin(GL_POLYGON);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  

          // X = Length
       glBegin(GL_POLYGON);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
           // y = width
       glBegin(GL_POLYGON);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
           if(h_ybig>height)
           {
              glVertex3f(0,-width,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();            
       
   glColor4f(0.0f, 0.00f, 0.0f, 1);    
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
              glVertex3f(length,0,-height);
           }
           else   
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
           glVertex3f(length,0,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
              glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);   
                glVertex3f(0,-width,-h_small - width*tan(roofangle));
           }
       glEnd(); 
       glBegin(GL_LINE_LOOP);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  
       
       glBegin(GL_LINE_LOOP);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
       
       glBegin(GL_LINE_LOOP);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
           if(h_ybig>height)
           {
              glVertex3f(0,-width,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
      
   glPopMatrix (); 
}



void DrawWedge2D_Inverse     (gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
    gdouble wg_separation ;
	gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;
	 
    wedgeangle=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =fabs(p->wedge_p->wg_roof_angle*PI/180);  /* 顶角 */
    wg_heigh_fir=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
	wg_separation = p->wedge_r->wg_separation ;
	
    width =p->wedge_p->wg_width;     /*楔块宽度*/
    length=p->wedge_p->wg_length;    /*楔块长度*/
    height=p->wedge_p->wg_height;/*楔块高度*/
       
    if(wedgeangle==PI/2||roofangle==PI/2)  return ;
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
 
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    
    glPushMatrix ();
	//双晶和ROOF角小于0时 楔块的偏移量不一样.
	glTranslatef(wg_pri_axis_reference, -wg_sec_axis_reference+width, 0.0);
        
   /*绘制楔块*/ 
   glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha               
       // button z = 0
       glBegin(GL_QUADS);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       // front y = - width 
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,0);
           glVertex3f(0,-width,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
              glVertex3f(length,-width,-height);
           }
           else   
              glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
           glVertex3f(length,-width,0);
       glEnd();
       //    x = 0
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,0);
           glVertex3f(0,-width,-h_small);
           if(h_ybig>height)
           {     
               glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
               glVertex3f(0, 0,-height);
           }
           else   
              glVertex3f(0,0,-h_small-width*tan(roofangle));
           glVertex3f(0,0,0);
       glEnd();
          //  xie  jiao
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
           else   
           {
              glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
           }
           if(h_ybig>height)   
              glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
                glVertex3f(0,0,-h_small -width*tan(roofangle));
           }
       glEnd();
         // TOP
       glBegin(GL_POLYGON);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, 0, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,-width,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);      
                 }
                 else   
                    glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,0,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
           }
       glEnd();  

          // X = Length
       glBegin(GL_POLYGON);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           if(h_xbig>height)
           {
              glVertex3f(length,-width,-height);
              glVertex3f(length, 0    ,-height);
           }
           else 
           {
              glVertex3f(length, -width, -h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,0 ,-height);                             
              }                    
              else
                    glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
           // y = 0
       glBegin(GL_POLYGON);
           glVertex3f(length,0,0);
           glVertex3f(0, 0,0);
           if(h_ybig>=height)
           {
              glVertex3f(0,0,-height);
              glVertex3f(length, 0,-height);
           }
           else 
           {
              glVertex3f(0, 0,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
                    glVertex3f(length,0,-height);                             
              }                    
              else
                    glVertex3f(length,0,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();            
       
   glColor4f(0.0f, 0.00f, 0.0f, 1);    
   // button z = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,0,0);
	   glVertex3f(length,0,0);
	   glVertex3f(length,-width,0);
	   glVertex3f(0,-width,0);
   glEnd();
   // front y = - width 
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,0);
	   glVertex3f(0,-width,-h_small);
	   if(h_xbig>height)
	   {	 
		  glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
		  glVertex3f(length,-width,-height);
	   }
	   else   
		  glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
	   glVertex3f(length,-width,0);
   glEnd();
   //	 x = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,0);
	   glVertex3f(0,-width,-h_small);
	   if(h_ybig>height)
	   {	 
		   glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
		   glVertex3f(0, 0,-height);
	   }
	   else   
		  glVertex3f(0,0,-h_small-width*tan(roofangle));
	   glVertex3f(0,0,0);
   glEnd();
	  //  xie  jiao
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,-h_small);			
	   if(h_xbig>height)   
		  glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
	   else   
	   {
		  glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
		  if((h_xbig+h_ybig-h_small)>=height)
			 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
		  else
			 glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
	   }
	   if(h_ybig>height)   
		  glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
	   else 
	   {  
			if((h_xbig+h_ybig-h_small)>=height)
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
			glVertex3f(0,0,-h_small -width*tan(roofangle));
	   }
   glEnd();
	 // TOP
   glBegin(GL_LINE_LOOP);
	   if((h_xbig+h_ybig-h_small)>=height)
	   {
			 glVertex3f(length, 0, -height );
			 if(h_xbig>height)
			 {	
				glVertex3f(length,-width,-height);				   
				glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);	  
			 }
			 else	
				glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
   
			 if(h_ybig>height)
			 {	   
				glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				glVertex3f(0,0,-height);
			 }
			 else	
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
	   }
   glEnd();  
   
	  // X = Length
   glBegin(GL_LINE_LOOP);
	   glVertex3f(length,0,0);
	   glVertex3f(length,-width,0);
	   if(h_xbig>height)
	   {
		  glVertex3f(length,-width,-height);
		  glVertex3f(length, 0	  ,-height);
	   }
	   else 
	   {
		  glVertex3f(length, -width, -h_small-length*tan(wedgeangle));		
		  if((h_xbig+h_ybig-h_small)>=height)
		  {
				glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
				glVertex3f(length,0 ,-height);							   
		  } 				   
		  else
				glVertex3f(length, 0,-(h_xbig+h_ybig-h_small)); 	 
	   }
   glEnd();
	   // y = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(length,0,0);
	   glVertex3f(0, 0,0);
	   if(h_ybig>=height)
	   {
		  glVertex3f(0,0,-height);
		  glVertex3f(length, 0,-height);
	   }
	   else 
	   {
		  glVertex3f(0, 0,-h_small-width*tan(roofangle));
		  if((h_xbig+h_ybig-h_small)>=height)
		  {
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
				glVertex3f(length,0,-height);							  
		  } 				   
		  else
				glVertex3f(length,0,-(h_xbig+h_ybig-h_small));		
	   }
   glEnd();  

      
   glPopMatrix (); 

     
}


void DrawWedge2D_Cylinder_OD    (gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
    gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;
    gdouble CylindricalExtDiameter;
	gdouble CylindricalIntDiameter;
	gint i; gdouble angle; gdouble r;
	gdouble zHeight;
	gdouble ySpace ;
    wedgeangle=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
    wg_heigh_fir=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width =p->wedge_p->wg_width;     /*楔块宽度*/
    length=p->wedge_p->wg_length;    /*楔块长度*/
    height=p->wedge_p->wg_height;/*楔块高度*/
	CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
	CylindricalIntDiameter = p->specimen->speci_inside_cylindrical  ;
    r = CylindricalExtDiameter/2 ;
    if(wedgeangle==PI/2||roofangle==PI/2)  return ;
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    angle = asin(length/CylindricalExtDiameter);
	zHeight = -sqrt(CylindricalExtDiameter*CylindricalExtDiameter - length*length)/2 ;
    ySpace = -wg_sec_axis_reference;
    glPushMatrix ();
	  
    // button z = 0
    glColor4f(0.0,0.0,0.0,1.0);
	for(i = 0; i< 20; i++)
    {
		   glBegin(GL_LINES);
			   glVertex3f(r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			   glVertex3f(r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
   
			   glVertex3f(-r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			   glVertex3f(-r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
		   glEnd();
    }
     /*绘制楔块*/ 
	glColor4f(0.2f, 0.5f, 0.7f, 0.3);	
	// y = 0
	if(h_xbig>height)
	{
		 glBegin(GL_TRIANGLES);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace,zHeight-height);
			glVertex3f(-length/2,ySpace,zHeight);
			glVertex3f(-length/2,ySpace,zHeight-h_small);
		 glEnd();	
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			}
			glEnd();
			glBegin(GL_TRIANGLES);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace,zHeight-height);
			glVertex3f(length/2,ySpace,zHeight-height);
			glVertex3f(length/2,ySpace,zHeight);
			glEnd();
			
	 }
	 else
	 {
	        glBegin(GL_TRIANGLES);
			glVertex3f(length/2,ySpace,zHeight-h_small-length*tan(wedgeangle));
			glVertex3f(-length/2,ySpace,zHeight);
			glVertex3f(-length/2,ySpace,zHeight-h_small);
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace,zHeight-h_small-length*tan(wedgeangle));
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace,zHeight-h_small-length*tan(wedgeangle));
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			}
            glEnd();
	  } 
	  // y = width
      if(h_ybig>height)
      {
          	glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
            glEnd();
			glBegin(GL_TRIANGLES);
			   glVertex3f(-length/2,ySpace-width,zHeight);
			   glVertex3f(-length/2,ySpace-width,zHeight-height);
			   glVertex3f(length/2,ySpace-width,zHeight-height);
			glEnd();
      }
	  else if((h_xbig+h_ybig-h_small)>=height)
	  {
	        glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
            glEnd();
			
		    glBegin(GL_TRIANGLES);
			   glVertex3f(-length/2,ySpace-width,zHeight);
			   glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,ySpace-width,zHeight-height);
			   glVertex3f(length/2,ySpace-width,zHeight-height);
			   
        	   glVertex3f(-length/2,ySpace-width,zHeight);
			   glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,ySpace-width,zHeight-height);
			   glVertex3f(-length/2,ySpace-width,zHeight-h_small-width*tan(roofangle));
			glEnd();
			
	  }
	  else
	  {
	      	glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight+h_small-h_xbig-h_ybig);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight+h_small-h_xbig-h_ybig);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
            glEnd();
			glBegin(GL_TRIANGLES);
        	   glVertex3f(-length/2,ySpace-width,zHeight);
			   glVertex3f(length/2,ySpace-width,zHeight+h_small-h_xbig-h_ybig);
			   glVertex3f(-length/2,ySpace-width,zHeight-h_small-width*tan(roofangle));
			glEnd();
	  }

	   
     glTranslatef(-length/2,ySpace,zHeight);       
       //    x = 0
       glBegin(GL_POLYGON);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
               glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
               glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
          //  xie  jiao
       glBegin(GL_POLYGON);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                glVertex3f(0,-width,-h_small -width*tan(roofangle));
           }
       glEnd();
         // TOP
       glBegin(GL_POLYGON);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  

          // X = Length
       glBegin(GL_POLYGON);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
         
       
   glColor4f(0.0f, 0.00f, 0.0f, 1);    


       glBegin(GL_LINE_STRIP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
              glVertex3f(length,0,-height);
           }
           else   
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
           glVertex3f(length,0,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
              glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);   
                glVertex3f(0,-width,-h_small - width*tan(roofangle));
           }
       glEnd(); 
       glBegin(GL_LINE_LOOP);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  
       
       glBegin(GL_LINE_LOOP);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
       
       glBegin(GL_LINE_STRIP);
           
           glVertex3f(0,-width,0);
           if(h_ybig>height)
           {
              glVertex3f(0,-width,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
		   glVertex3f(length,-width,0);
       glEnd();
      
   glPopMatrix ();       
}



void DrawWedge2D_Cylinder_OD_Zero    (gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
	gdouble CylindricalExtDiameter ,CylindricalIntDiameter ;
    gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;
    gdouble zHeight    ;
    wedgeangle=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
    wg_heigh_fir=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width =p->wedge_p->wg_width;     /*楔块宽度*/
    length=p->wedge_p->wg_length;    /*楔块长度*/
    height=p->wedge_p->wg_height;/*楔块高度*/
    CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
	CylindricalIntDiameter = p->specimen->speci_inside_cylindrical  ;
    if(wedgeangle==PI/2||roofangle==PI/2)  return ;
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
 
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    zHeight = -sqrt(CylindricalExtDiameter*CylindricalExtDiameter - width*width)/2 ;
    glPushMatrix ();
    glTranslatef(wg_pri_axis_reference,width/2,zHeight);       
   /*绘制楔块*/ 
   glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha               
       // button z = 0
       glBegin(GL_QUADS);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       // front y = 0 
       glBegin(GL_POLYGON);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
              glVertex3f(length,0,-height);
           }
           else   
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
           glVertex3f(length,0,0);
       glEnd();
       //    x = 0
       glBegin(GL_POLYGON);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
               glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
               glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
          //  xie  jiao
       glBegin(GL_POLYGON);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                glVertex3f(0,-width,-h_small -width*tan(roofangle));
           }
       glEnd();
         // TOP
       glBegin(GL_POLYGON);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  

          // X = Length
       glBegin(GL_POLYGON);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
           // y = width
       glBegin(GL_POLYGON);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
           if(h_ybig>height)
           {
              glVertex3f(0,-width,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();            
       
       glColor4f(0.0f, 0.00f, 0.0f, 1);    
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
              glVertex3f(length,0,-height);
           }
           else   
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
           glVertex3f(length,0,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
              glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);   
                glVertex3f(0,-width,-h_small - width*tan(roofangle));
           }
       glEnd(); 
       glBegin(GL_LINE_LOOP);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  
       
       glBegin(GL_LINE_LOOP);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
       
       glBegin(GL_LINE_LOOP);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
           if(h_ybig>height)
           {
              glVertex3f(0,-width,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
      
   glPopMatrix ();  
}


void DrawWedge2D_Cylinder_OD_Inverse_Zero    (gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
    gdouble wg_separation ;
	gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;
	gdouble CylindricalExtDiameter ;
	gdouble zHeight ;
    wedgeangle=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =fabs(p->wedge_p->wg_roof_angle*PI/180);  /* 顶角 */
    wg_heigh_fir=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
	wg_separation = p->wedge_r->wg_separation ;
	
    width =p->wedge_p->wg_width;     /*楔块宽度*/
    length=p->wedge_p->wg_length;    /*楔块长度*/
    height=p->wedge_p->wg_height;/*楔块高度*/
    CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
	zHeight = -sqrt(CylindricalExtDiameter*CylindricalExtDiameter - width*width)/2 ; 
	
    if(wedgeangle==PI/2||roofangle==PI/2)  return ;
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
 
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    
    glPushMatrix ();
	//双晶和ROOF角小于0时 楔块的偏移量不一样.
	glTranslatef(wg_pri_axis_reference, width/2, zHeight);
        
   /*绘制楔块*/ 
   glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha               
       // button z = 0
       glBegin(GL_QUADS);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       // front y = - width 
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,0);
           glVertex3f(0,-width,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
              glVertex3f(length,-width,-height);
           }
           else   
              glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
           glVertex3f(length,-width,0);
       glEnd();
       //    x = 0
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,0);
           glVertex3f(0,-width,-h_small);
           if(h_ybig>height)
           {     
               glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
               glVertex3f(0, 0,-height);
           }
           else   
              glVertex3f(0,0,-h_small-width*tan(roofangle));
           glVertex3f(0,0,0);
       glEnd();
          //  xie  jiao
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
           else   
           {
              glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
           }
           if(h_ybig>height)   
              glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
                glVertex3f(0,0,-h_small -width*tan(roofangle));
           }
       glEnd();
         // TOP
       glBegin(GL_POLYGON);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, 0, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,-width,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);      
                 }
                 else   
                    glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,0,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
           }
       glEnd();  

          // X = Length
       glBegin(GL_POLYGON);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           if(h_xbig>height)
           {
              glVertex3f(length,-width,-height);
              glVertex3f(length, 0    ,-height);
           }
           else 
           {
              glVertex3f(length, -width, -h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,0 ,-height);                             
              }                    
              else
                    glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
           // y = 0
       glBegin(GL_POLYGON);
           glVertex3f(length,0,0);
           glVertex3f(0, 0,0);
           if(h_ybig>=height)
           {
              glVertex3f(0,0,-height);
              glVertex3f(length, 0,-height);
           }
           else 
           {
              glVertex3f(0, 0,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
                    glVertex3f(length,0,-height);                             
              }                    
              else
                    glVertex3f(length,0,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();            
       
   glColor4f(0.0f, 0.00f, 0.0f, 1);    
   // button z = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,0,0);
	   glVertex3f(length,0,0);
	   glVertex3f(length,-width,0);
	   glVertex3f(0,-width,0);
   glEnd();
   // front y = - width 
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,0);
	   glVertex3f(0,-width,-h_small);
	   if(h_xbig>height)
	   {	 
		  glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
		  glVertex3f(length,-width,-height);
	   }
	   else   
		  glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
	   glVertex3f(length,-width,0);
   glEnd();
   //	 x = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,0);
	   glVertex3f(0,-width,-h_small);
	   if(h_ybig>height)
	   {	 
		   glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
		   glVertex3f(0, 0,-height);
	   }
	   else   
		  glVertex3f(0,0,-h_small-width*tan(roofangle));
	   glVertex3f(0,0,0);
   glEnd();
	  //  xie  jiao
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,-h_small);			
	   if(h_xbig>height)   
		  glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
	   else   
	   {
		  glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
		  if((h_xbig+h_ybig-h_small)>=height)
			 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
		  else
			 glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
	   }
	   if(h_ybig>height)   
		  glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
	   else 
	   {  
			if((h_xbig+h_ybig-h_small)>=height)
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
			glVertex3f(0,0,-h_small -width*tan(roofangle));
	   }
   glEnd();
	 // TOP
   glBegin(GL_LINE_LOOP);
	   if((h_xbig+h_ybig-h_small)>=height)
	   {
			 glVertex3f(length, 0, -height );
			 if(h_xbig>height)
			 {	
				glVertex3f(length,-width,-height);				   
				glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);	  
			 }
			 else	
				glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
   
			 if(h_ybig>height)
			 {	   
				glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				glVertex3f(0,0,-height);
			 }
			 else	
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
	   }
   glEnd();  
   
	  // X = Length
   glBegin(GL_LINE_LOOP);
	   glVertex3f(length,0,0);
	   glVertex3f(length,-width,0);
	   if(h_xbig>height)
	   {
		  glVertex3f(length,-width,-height);
		  glVertex3f(length, 0	  ,-height);
	   }
	   else 
	   {
		  glVertex3f(length, -width, -h_small-length*tan(wedgeangle));		
		  if((h_xbig+h_ybig-h_small)>=height)
		  {
				glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
				glVertex3f(length,0 ,-height);							   
		  } 				   
		  else
				glVertex3f(length, 0,-(h_xbig+h_ybig-h_small)); 	 
	   }
   glEnd();
	   // y = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(length,0,0);
	   glVertex3f(0, 0,0);
	   if(h_ybig>=height)
	   {
		  glVertex3f(0,0,-height);
		  glVertex3f(length, 0,-height);
	   }
	   else 
	   {
		  glVertex3f(0, 0,-h_small-width*tan(roofangle));
		  if((h_xbig+h_ybig-h_small)>=height)
		  {
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
				glVertex3f(length,0,-height);							  
		  } 				   
		  else
				glVertex3f(length,0,-(h_xbig+h_ybig-h_small));		
	   }
   glEnd();  

      
   glPopMatrix (); 

     
}


void DrawWedge2D_Cylinder_ID_Zero    (gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
	gdouble CylindricalExtDiameter ,CylindricalIntDiameter ;
    gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;
    gdouble zHeight    ;
    wedgeangle=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
    wg_heigh_fir=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width =p->wedge_p->wg_width;     /*楔块宽度*/
    length=p->wedge_p->wg_length;    /*楔块长度*/
    height=p->wedge_p->wg_height;/*楔块高度*/
	CylindricalIntDiameter = p->specimen->speci_inside_cylindrical  ;
    if(wedgeangle==PI/2||roofangle==PI/2)  return ;
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
 
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    zHeight = sqrt(CylindricalIntDiameter*CylindricalIntDiameter - width*width)/2 ;
    glPushMatrix ();
    glTranslatef(wg_pri_axis_reference,width/2,zHeight);       
   /*绘制楔块*/ 
   glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha               
       // button z = 0
       glBegin(GL_QUADS);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       // front y = 0 
       glBegin(GL_POLYGON);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
              glVertex3f(length,0,-height);
           }
           else   
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
           glVertex3f(length,0,0);
       glEnd();
       //    x = 0
       glBegin(GL_POLYGON);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
               glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
               glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
          //  xie  jiao
       glBegin(GL_POLYGON);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                glVertex3f(0,-width,-h_small -width*tan(roofangle));
           }
       glEnd();
         // TOP
       glBegin(GL_POLYGON);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  

          // X = Length
       glBegin(GL_POLYGON);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
           // y = width
       glBegin(GL_POLYGON);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
           if(h_ybig>height)
           {
              glVertex3f(0,-width,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();            
       
       glColor4f(0.0f, 0.00f, 0.0f, 1);    
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
              glVertex3f(length,0,-height);
           }
           else   
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
           glVertex3f(length,0,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
              glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);   
                glVertex3f(0,-width,-h_small - width*tan(roofangle));
           }
       glEnd(); 
       glBegin(GL_LINE_LOOP);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  
       
       glBegin(GL_LINE_LOOP);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
       
       glBegin(GL_LINE_LOOP);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
           if(h_ybig>height)
           {
              glVertex3f(0,-width,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
      
   glPopMatrix ();  
}


void DrawWedge2D_Cylinder_ID_Inverse_Zero    (gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
    gdouble wg_separation ;
	gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;
	gdouble CylindricalIntDiameter ;
	gdouble zHeight ;
    wedgeangle=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =fabs(p->wedge_p->wg_roof_angle*PI/180);  /* 顶角 */
    wg_heigh_fir=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
	wg_separation = p->wedge_r->wg_separation ;
	
    width =p->wedge_p->wg_width;     /*楔块宽度*/
    length=p->wedge_p->wg_length;    /*楔块长度*/
    height=p->wedge_p->wg_height;/*楔块高度*/
    CylindricalIntDiameter = p->specimen->speci_inside_cylindrical  ;
	zHeight = sqrt(CylindricalIntDiameter*CylindricalIntDiameter - width*width)/2 ; 
	
    if(wedgeangle==PI/2||roofangle==PI/2)  return ;
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
 
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    
    glPushMatrix ();
	//双晶和ROOF角小于0时 楔块的偏移量不一样.
	glTranslatef(wg_pri_axis_reference, width/2, zHeight);
        
   /*绘制楔块*/ 
   glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha               
       // button z = 0
       glBegin(GL_QUADS);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       // front y = - width 
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,0);
           glVertex3f(0,-width,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
              glVertex3f(length,-width,-height);
           }
           else   
              glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
           glVertex3f(length,-width,0);
       glEnd();
       //    x = 0
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,0);
           glVertex3f(0,-width,-h_small);
           if(h_ybig>height)
           {     
               glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
               glVertex3f(0, 0,-height);
           }
           else   
              glVertex3f(0,0,-h_small-width*tan(roofangle));
           glVertex3f(0,0,0);
       glEnd();
          //  xie  jiao
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
           else   
           {
              glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
           }
           if(h_ybig>height)   
              glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
                glVertex3f(0,0,-h_small -width*tan(roofangle));
           }
       glEnd();
         // TOP
       glBegin(GL_POLYGON);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, 0, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,-width,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);      
                 }
                 else   
                    glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,0,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
           }
       glEnd();  

          // X = Length
       glBegin(GL_POLYGON);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           if(h_xbig>height)
           {
              glVertex3f(length,-width,-height);
              glVertex3f(length, 0    ,-height);
           }
           else 
           {
              glVertex3f(length, -width, -h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,0 ,-height);                             
              }                    
              else
                    glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
           // y = 0
       glBegin(GL_POLYGON);
           glVertex3f(length,0,0);
           glVertex3f(0, 0,0);
           if(h_ybig>=height)
           {
              glVertex3f(0,0,-height);
              glVertex3f(length, 0,-height);
           }
           else 
           {
              glVertex3f(0, 0,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
                    glVertex3f(length,0,-height);                             
              }                    
              else
                    glVertex3f(length,0,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();            
       
   glColor4f(0.0f, 0.00f, 0.0f, 1);    
   // button z = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,0,0);
	   glVertex3f(length,0,0);
	   glVertex3f(length,-width,0);
	   glVertex3f(0,-width,0);
   glEnd();
   // front y = - width 
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,0);
	   glVertex3f(0,-width,-h_small);
	   if(h_xbig>height)
	   {	 
		  glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
		  glVertex3f(length,-width,-height);
	   }
	   else   
		  glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
	   glVertex3f(length,-width,0);
   glEnd();
   //	 x = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,0);
	   glVertex3f(0,-width,-h_small);
	   if(h_ybig>height)
	   {	 
		   glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
		   glVertex3f(0, 0,-height);
	   }
	   else   
		  glVertex3f(0,0,-h_small-width*tan(roofangle));
	   glVertex3f(0,0,0);
   glEnd();
	  //  xie  jiao
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,-h_small);			
	   if(h_xbig>height)   
		  glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
	   else   
	   {
		  glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
		  if((h_xbig+h_ybig-h_small)>=height)
			 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
		  else
			 glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
	   }
	   if(h_ybig>height)   
		  glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
	   else 
	   {  
			if((h_xbig+h_ybig-h_small)>=height)
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
			glVertex3f(0,0,-h_small -width*tan(roofangle));
	   }
   glEnd();
	 // TOP
   glBegin(GL_LINE_LOOP);
	   if((h_xbig+h_ybig-h_small)>=height)
	   {
			 glVertex3f(length, 0, -height );
			 if(h_xbig>height)
			 {	
				glVertex3f(length,-width,-height);				   
				glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);	  
			 }
			 else	
				glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
   
			 if(h_ybig>height)
			 {	   
				glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				glVertex3f(0,0,-height);
			 }
			 else	
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
	   }
   glEnd();  
   
	  // X = Length
   glBegin(GL_LINE_LOOP);
	   glVertex3f(length,0,0);
	   glVertex3f(length,-width,0);
	   if(h_xbig>height)
	   {
		  glVertex3f(length,-width,-height);
		  glVertex3f(length, 0	  ,-height);
	   }
	   else 
	   {
		  glVertex3f(length, -width, -h_small-length*tan(wedgeangle));		
		  if((h_xbig+h_ybig-h_small)>=height)
		  {
				glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
				glVertex3f(length,0 ,-height);							   
		  } 				   
		  else
				glVertex3f(length, 0,-(h_xbig+h_ybig-h_small)); 	 
	   }
   glEnd();
	   // y = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(length,0,0);
	   glVertex3f(0, 0,0);
	   if(h_ybig>=height)
	   {
		  glVertex3f(0,0,-height);
		  glVertex3f(length, 0,-height);
	   }
	   else 
	   {
		  glVertex3f(0, 0,-h_small-width*tan(roofangle));
		  if((h_xbig+h_ybig-h_small)>=height)
		  {
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
				glVertex3f(length,0,-height);							  
		  } 				   
		  else
				glVertex3f(length,0,-(h_xbig+h_ybig-h_small));		
	   }
   glEnd();  

      
   glPopMatrix (); 

     
}

void DrawCylinderWedgeInverseOD(gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
    gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;
    gdouble CylindricalExtDiameter;
	gdouble CylindricalIntDiameter;
	gint i; gdouble angle; gdouble r;
	gdouble zHeight;
	gdouble wg_separation;
	gdouble yOffset;
    wedgeangle=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =fabs(p->wedge_p->wg_roof_angle*PI/180);  /* 顶角 */
    wg_heigh_fir=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
	wg_separation          = p->wedge_r->wg_separation ;
    width =p->wedge_p->wg_width;     /*楔块宽度*/
    length=p->wedge_p->wg_length;    /*楔块长度*/
    height=p->wedge_p->wg_height;/*楔块高度*/
	CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
	CylindricalIntDiameter = p->specimen->speci_inside_cylindrical  ;
    r = CylindricalExtDiameter/2 ;
    if(wedgeangle==PI/2||roofangle==PI/2)  return ;
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    angle = asin(length/CylindricalExtDiameter);
	zHeight = -sqrt(CylindricalExtDiameter*CylindricalExtDiameter - length*length)/2 ;
    // special for 

    yOffset = -wg_sec_axis_reference+width ;
	glPushMatrix ();
	
    glColor4f(0.0,0.0,0.0,1.0);
	for(i = 0; i< 20; i++)
    {
		   glBegin(GL_LINES);
			   glVertex3f(r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			   glVertex3f(r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
   
			   glVertex3f(-r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			   glVertex3f(-r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
		   glEnd();
    }
     /*绘制楔块*/ 
	glColor4f(0.2f, 0.5f, 0.7f, 0.3);	
	// y = -width
	if(h_xbig>height)
	{
		 glBegin(GL_TRIANGLES);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			glVertex3f(-length/2,yOffset-width,zHeight);
			glVertex3f(-length/2,yOffset-width,zHeight-h_small);
		 glEnd();	
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
			}
			glEnd();
			glBegin(GL_TRIANGLES);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			glVertex3f(length/2,yOffset-width,zHeight-height);
			glVertex3f(length/2,yOffset-width,zHeight);
			glEnd();
			
	 }
	 else
	 {
	        glBegin(GL_TRIANGLES);
			glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
			glVertex3f(-length/2,yOffset-width,zHeight);
			glVertex3f(-length/2,yOffset-width,zHeight-h_small);
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
			}
            glEnd();
	  } 
	  // y = width
      if(h_ybig>height)
      {
          	glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,yOffset,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,yOffset,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			}
            glEnd();
			glBegin(GL_TRIANGLES);
			   glVertex3f(-length/2,yOffset,zHeight);
			   glVertex3f(-length/2,yOffset,zHeight-height);
			   glVertex3f(length/2,yOffset,zHeight-height);
			glEnd();
      }
	  else if((h_xbig+h_ybig-h_small)>=height)
	  {
	        glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,yOffset,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,yOffset,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			}
            glEnd();
			
		    glBegin(GL_TRIANGLES);
			   glVertex3f(-length/2,yOffset,zHeight);
			   glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,yOffset,zHeight-height);
			   glVertex3f(length/2,yOffset,zHeight-height);
			   
        	   glVertex3f(-length/2,yOffset,zHeight);
			   glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,yOffset,zHeight-height);
			   glVertex3f(-length/2,yOffset,zHeight-h_small-width*tan(roofangle));
			glEnd();
			
	  }
	  else
	  {
	      	glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			}
            glEnd();
			glBegin(GL_TRIANGLES);
        	   glVertex3f(-length/2,yOffset,zHeight);
			   glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
			   glVertex3f(-length/2,yOffset,zHeight-h_small-width*tan(roofangle));
			glEnd();
	  }

	// 双晶和ROOF角小于0时的楔块平移不一样

    glTranslatef(-length/2, -wg_sec_axis_reference + width,zHeight);
	 //glTranslatef(wg_pri_axis_reference,-wg_sec_axis_reference-wg_separation,0.0f);		
	/*绘制楔块*/ 
	glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha			   
		// button z = 0
		// front y = - width 
		//	  x = 0
		glBegin(GL_POLYGON);
			glVertex3f(0,-width,0);
			glVertex3f(0,-width,-h_small);
			if(h_ybig>height)
			{	  
				glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				glVertex3f(0, 0,-height);
			}
			else   
			   glVertex3f(0,0,-h_small-width*tan(roofangle));
			glVertex3f(0,0,0);
		glEnd();
		   //  xie	jiao
		glBegin(GL_POLYGON);
			glVertex3f(0,-width,-h_small);			 
			if(h_xbig>height)	
			   glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
			else   
			{
			   glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
			   if((h_xbig+h_ybig-h_small)>=height)
				  glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
			   else
				  glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
			}
			if(h_ybig>height)	
			   glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
			else 
			{  
				 if((h_xbig+h_ybig-h_small)>=height)
					 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
				 glVertex3f(0,0,-h_small -width*tan(roofangle));
			}
		glEnd();
		  // TOP
		glBegin(GL_POLYGON);
			if((h_xbig+h_ybig-h_small)>=height)
			{
				  glVertex3f(length, 0, -height );
				  if(h_xbig>height)
				  {  
					 glVertex3f(length,-width,-height); 				
					 glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);	   
				  }
				  else	 
					 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
	
				  if(h_ybig>height)
				  { 	
					 glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
					 glVertex3f(0,0,-height);
				  }
				  else	 
					 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
			}
		glEnd();  
	
		   // X = Length
		glBegin(GL_POLYGON);
			glVertex3f(length,0,0);
			glVertex3f(length,-width,0);
			if(h_xbig>height)
			{
			   glVertex3f(length,-width,-height);
			   glVertex3f(length, 0    ,-height);
			}
			else 
			{
			   glVertex3f(length, -width, -h_small-length*tan(wedgeangle)); 	 
			   if((h_xbig+h_ybig-h_small)>=height)
			   {
					 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
					 glVertex3f(length,0 ,-height); 							
			   }					
			   else
					 glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));	  
			}
		glEnd();
			// y = 0		
		
	glColor4f(0.0f, 0.00f, 0.0f, 1);	
	// button z = 0
	// front y = - width 
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,-width,0);
		glVertex3f(0,-width,-h_small);
		if(h_xbig>height)
		{	  
		   glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
		   glVertex3f(length,-width,-height);
		}
		else   
		   glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
		glVertex3f(length,-width,0);
	glEnd();
	//	  x = 0
	glBegin(GL_LINE_LOOP);
		glVertex3f(0,-width,0);
		glVertex3f(0,-width,-h_small);
		if(h_ybig>height)
		{	  
			glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
			glVertex3f(0, 0,-height);
		}
		else   
		   glVertex3f(0,0,-h_small-width*tan(roofangle));
		glVertex3f(0,0,0);
	glEnd();
	   //  xie	jiao
	glBegin(GL_LINE_LOOP);
		glVertex3f(0,-width,-h_small);			 
		if(h_xbig>height)	
		   glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
		else   
		{
		   glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
		   if((h_xbig+h_ybig-h_small)>=height)
			  glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
		   else
			  glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
		}
		if(h_ybig>height)	
		   glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
		else 
		{  
			 if((h_xbig+h_ybig-h_small)>=height)
				 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
			 glVertex3f(0,0,-h_small -width*tan(roofangle));
		}
	glEnd();
	  // TOP
	glBegin(GL_LINE_LOOP);
		if((h_xbig+h_ybig-h_small)>=height)
		{
			  glVertex3f(length, 0, -height );
			  if(h_xbig>height)
			  {  
				 glVertex3f(length,-width,-height); 				
				 glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);	   
			  }
			  else	 
				 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
	
			  if(h_ybig>height)
			  { 	
				 glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				 glVertex3f(0,0,-height);
			  }
			  else	 
				 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
		}
	glEnd();  
	
	   // X = Length
	glBegin(GL_LINE_LOOP);
		glVertex3f(length,0,0);
		glVertex3f(length,-width,0);
		if(h_xbig>height)
		{
		   glVertex3f(length,-width,-height);
		   glVertex3f(length, 0    ,-height);
		}
		else 
		{
		   glVertex3f(length, -width, -h_small-length*tan(wedgeangle)); 	 
		   if((h_xbig+h_ybig-h_small)>=height)
		   {
				 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
				 glVertex3f(length,0 ,-height); 							
		   }					
		   else
				 glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));	  
		}
	glEnd();
		// y = 0
	glBegin(GL_LINE_STRIP);
		
		glVertex3f(0, 0,0);
		if(h_ybig>=height)
		{
		   glVertex3f(0,0,-height);
		   glVertex3f(length, 0,-height);
		}
		else 
		{
		   glVertex3f(0, 0,-h_small-width*tan(roofangle));
		   if((h_xbig+h_ybig-h_small)>=height)
		   {
				 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
				 glVertex3f(length,0,-height);							   
		   }					
		   else
				 glVertex3f(length,0,-(h_xbig+h_ybig-h_small)); 	 
		}
		glVertex3f(length,0,0);
	glEnd();  
	
	   
	glPopMatrix (); 
	
	  

}

void DrawWedge2D_Cylinder_ID(gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
    gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;
    gdouble CylindricalExtDiameter;
	gdouble CylindricalIntDiameter;
	gint i; gdouble r;gdouble angle; gdouble zHeight;
    wedgeangle=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
    wg_heigh_fir=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width =p->wedge_p->wg_width;     /*楔块宽度*/
    length=p->wedge_p->wg_length;    /*楔块长度*/
    height=p->wedge_p->wg_height;/*楔块高度*/
	CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
	CylindricalIntDiameter = p->specimen->speci_inside_cylindrical  ;
    r = CylindricalIntDiameter/2 ;	
    angle = asin(length/CylindricalIntDiameter);
	zHeight = sqrt(CylindricalIntDiameter*CylindricalIntDiameter - length*length)/2 ;
	if(wedgeangle==PI/2||roofangle==PI/2)  return ;
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
    
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    
    glPushMatrix ();
	glColor4f(0.0,0.0,0.0,1.0);
	glBegin(GL_LINES);
       for(i=0; i<20; i++)
       {
			   glVertex3f(r*sin(i*angle/20),-wg_sec_axis_reference,r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),-wg_sec_axis_reference,r*cos((i+1)*angle/20));
			   glVertex3f(r*sin(i*angle/20),-wg_sec_axis_reference-width,r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),-wg_sec_axis_reference-width,r*cos((i+1)*angle/20));
   
			   glVertex3f(-r*sin(i*angle/20),-wg_sec_axis_reference,r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),-wg_sec_axis_reference,r*cos((i+1)*angle/20));
			   glVertex3f(-r*sin(i*angle/20),-wg_sec_axis_reference-width,r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),-wg_sec_axis_reference-width,r*cos((i+1)*angle/20));
       } 
	glEnd();

	glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha         
	// y = 0
	if(h_xbig>height)
	{
		 glBegin(GL_TRIANGLES);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,-wg_sec_axis_reference,zHeight-height);
			glVertex3f(-length/2,-wg_sec_axis_reference,zHeight);
			glVertex3f(-length/2,-wg_sec_axis_reference,zHeight-h_small);
		 glEnd();	
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,-wg_sec_axis_reference,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),-wg_sec_axis_reference,r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),-wg_sec_axis_reference,r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,-wg_sec_axis_reference,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),-wg_sec_axis_reference,r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),-wg_sec_axis_reference,r*cos((i+1)*angle/20));
			}
			glEnd();
			glBegin(GL_TRIANGLES);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,-wg_sec_axis_reference,zHeight-height);
			glVertex3f(length/2,-wg_sec_axis_reference,zHeight-height);
			glVertex3f(length/2,-wg_sec_axis_reference,zHeight);
			glEnd();
			
	 }
	 else
	 {
	        glBegin(GL_TRIANGLES);
			glVertex3f(length/2,-wg_sec_axis_reference,zHeight-h_small-length*tan(wedgeangle));
			glVertex3f(-length/2,-wg_sec_axis_reference,zHeight);
			glVertex3f(-length/2,-wg_sec_axis_reference,zHeight-h_small);
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,-wg_sec_axis_reference,zHeight-h_small-length*tan(wedgeangle));
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),-wg_sec_axis_reference,r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),-wg_sec_axis_reference,r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,-wg_sec_axis_reference,zHeight-h_small-length*tan(wedgeangle));
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),-wg_sec_axis_reference,r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),-wg_sec_axis_reference,r*cos((i+1)*angle/20));
			}
            glEnd();
	  } 
	  // y = width
      if(h_ybig>height)
      {
          	glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,-wg_sec_axis_reference-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),-wg_sec_axis_reference-width,r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),-wg_sec_axis_reference-width,r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,-wg_sec_axis_reference-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),-wg_sec_axis_reference-width,r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),-wg_sec_axis_reference-width,r*cos((i+1)*angle/20));
			}
            glEnd();
			glBegin(GL_TRIANGLES);
			   glVertex3f(-length/2,-wg_sec_axis_reference-width,zHeight);
			   glVertex3f(-length/2,-wg_sec_axis_reference-width,zHeight-height);
			   glVertex3f(length/2,-wg_sec_axis_reference-width,zHeight-height);
			glEnd();
      }
	  else if((h_xbig+h_ybig-h_small)>=height)
	  {
	        glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,-wg_sec_axis_reference-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),-wg_sec_axis_reference-width,r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),-wg_sec_axis_reference-width,r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,-wg_sec_axis_reference-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),-wg_sec_axis_reference-width,r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),-wg_sec_axis_reference-width,r*cos((i+1)*angle/20));
			}
            glEnd();
			
		    glBegin(GL_TRIANGLES);
			   glVertex3f(-length/2,-wg_sec_axis_reference-width,zHeight);
			   glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,-wg_sec_axis_reference-width,zHeight-height);
			   glVertex3f(length/2,-wg_sec_axis_reference-width,zHeight-height);
			   
        	   glVertex3f(-length/2,-wg_sec_axis_reference-width,zHeight);
			   glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,-wg_sec_axis_reference-width,zHeight-height);
			   glVertex3f(-length/2,-wg_sec_axis_reference-width,zHeight-h_small-width*tan(roofangle));
			glEnd();
			
	  }
	  else
	  {
	      	glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,-wg_sec_axis_reference-width,zHeight+h_small-h_xbig-h_ybig);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),-wg_sec_axis_reference-width,r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),-wg_sec_axis_reference-width,r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,-wg_sec_axis_reference-width,zHeight+h_small-h_xbig-h_ybig);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),-wg_sec_axis_reference-width,r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),-wg_sec_axis_reference-width,r*cos((i+1)*angle/20));
			}
            glEnd();
			glBegin(GL_TRIANGLES);
        	   glVertex3f(-length/2,-wg_sec_axis_reference-width,zHeight);
			   glVertex3f(length/2,-wg_sec_axis_reference-width,zHeight+h_small-h_xbig-h_ybig);
			   glVertex3f(-length/2,-wg_sec_axis_reference-width,zHeight-h_small-width*tan(roofangle));
			glEnd();
	  }

    glTranslatef(-length/2,-wg_sec_axis_reference,sqrt(CylindricalIntDiameter*CylindricalIntDiameter - length*length)/2);       
    /*绘制楔块*/
    //    x = 0
       glBegin(GL_POLYGON);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
               glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
               glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
          //  xie  jiao
       glBegin(GL_POLYGON);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                glVertex3f(0,-width,-h_small -width*tan(roofangle));
           }
       glEnd();
       // TOP
       glBegin(GL_POLYGON);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  
       // X = Length
       glBegin(GL_POLYGON);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();        
   glColor4f(0.0f, 0.00f, 0.0f, 1);    

       glBegin(GL_LINE_STRIP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
              glVertex3f(length,0,-height);
           }
           else   
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
           glVertex3f(length,0,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
              glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);   
                glVertex3f(0,-width,-h_small - width*tan(roofangle));
           }
       glEnd(); 
       glBegin(GL_LINE_LOOP);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  
       
       glBegin(GL_LINE_LOOP);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
       
       glBegin(GL_LINE_STRIP);
     
		   glVertex3f(0,-width,0);
           if(h_ybig>height)
           {
              glVertex3f(0,-width,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
		   glVertex3f(length,-width,0);
       glEnd();
      
   glPopMatrix ();   
}

void DrawCylinderWedgeInverseID(gpointer data)
{   
	DRAW_UI_P p = (DRAW_UI_P)(data);
		 
	 gdouble wedgeangle,roofangle,wg_heigh_fir;
	 gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
	 gdouble wg_pri_axis_reference,wg_sec_axis_reference;
	 gdouble width,length,height;
	 gdouble h_small ,h_xbig, h_ybig ;
	 gdouble xTemp,yTemp;
	 gdouble CylindricalExtDiameter;
	 gdouble CylindricalIntDiameter;
	 gint i; gdouble angle; gdouble r;
	 gdouble zHeight;
	 gdouble wg_separation;
	 gdouble yOffset;
	 wedgeangle=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
	 roofangle =fabs(p->wedge_p->wg_roof_angle*PI/180);  /* 顶角 */
	 wg_heigh_fir=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
	 wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
	 wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
	 wg_pri_axis_reference	= p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
	 wg_sec_axis_reference	= p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
	 wg_separation			= p->wedge_r->wg_separation ;
	 width =p->wedge_p->wg_width;	  /*楔块宽度*/
	 length=p->wedge_p->wg_length;	  /*楔块长度*/
	 height=p->wedge_p->wg_height;/*楔块高度*/
	 CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
	 CylindricalIntDiameter = p->specimen->speci_inside_cylindrical  ;
	 r = CylindricalIntDiameter/2 ;
	 if(wedgeangle==PI/2||roofangle==PI/2)	return ;
	 h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
	 h_xbig= h_small + length*tan(wedgeangle) ;
	 h_ybig= h_small + width*tan(roofangle)   ;
	 angle = asin(length/CylindricalIntDiameter);
	 zHeight = sqrt(CylindricalIntDiameter*CylindricalIntDiameter - length*length)/2 ;

	 yOffset =    -wg_sec_axis_reference+width ;
	 glPushMatrix ();
	 
	 glColor4f(0.0,0.0,0.0,1.0);
	 for(i = 0; i< 20; i++)
	 {
			glBegin(GL_LINES);
				glVertex3f(r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
				glVertex3f(r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
	
				glVertex3f(-r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
				glVertex3f(-r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
			glEnd();
	 }
	  /*绘制楔块*/ 
	 glColor4f(0.2f, 0.5f, 0.7f, 0.3);	 
	 // y = -width
	 if(h_xbig>height)
	 {
		  glBegin(GL_TRIANGLES);
			 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			 glVertex3f(-length/2,yOffset-width,zHeight);
			 glVertex3f(-length/2,yOffset-width,zHeight-h_small);
		  glEnd();	 
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
			 }
			 glEnd();
			
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(-r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
			 }
			 glEnd();
			 glBegin(GL_TRIANGLES);
			 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			 glVertex3f(length/2,yOffset-width,zHeight-height);
			 glVertex3f(length/2,yOffset-width,zHeight);
			 glEnd();
			 
	  }
	  else
	  {
			 glBegin(GL_TRIANGLES);
			 glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
			 glVertex3f(-length/2,yOffset-width,zHeight);
			 glVertex3f(-length/2,yOffset-width,zHeight-h_small);
			 glEnd();
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
			 }
			 glEnd();
			
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(-r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
			 }
			 glEnd();
	   } 
	   // y = width
	   if(h_ybig>height)
	   {
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
			 }
			 glEnd();
			
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(-r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
			 }
			 glEnd();
			 glBegin(GL_TRIANGLES);
				glVertex3f(-length/2,yOffset,zHeight);
				glVertex3f(-length/2,yOffset,zHeight-height);
				glVertex3f(length/2,yOffset,zHeight-height);
			 glEnd();
	   }
	   else if((h_xbig+h_ybig-h_small)>=height)
	   {
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
			 }
			 glEnd();
			
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(-r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
			 }
			 glEnd();
			 
			 glBegin(GL_TRIANGLES);
				glVertex3f(-length/2,yOffset,zHeight);
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,yOffset,zHeight-height);
				glVertex3f(length/2,yOffset,zHeight-height);
				
				glVertex3f(-length/2,yOffset,zHeight);
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,yOffset,zHeight-height);
				glVertex3f(-length/2,yOffset,zHeight-h_small-width*tan(roofangle));
			 glEnd();
			 
	   }
	   else
	   {
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
			 }
			 glEnd();
			
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(-r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
			 }
			 glEnd();
			 glBegin(GL_TRIANGLES);
				glVertex3f(-length/2,yOffset,zHeight);
				glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
				glVertex3f(-length/2,yOffset,zHeight-h_small-width*tan(roofangle));
			 glEnd();
	   }

	glTranslatef(-length/2, -wg_sec_axis_reference + width,zHeight);
	 //glTranslatef(wg_pri_axis_reference,-wg_sec_axis_reference-wg_separation,0.0f);		
	/*绘制楔块*/ 
	glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha			   
		// button z = 0
		// front y = - width 
		//	  x = 0
		glBegin(GL_POLYGON);
			glVertex3f(0,-width,0);
			glVertex3f(0,-width,-h_small);
			if(h_ybig>height)
			{	  
				glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				glVertex3f(0, 0,-height);
			}
			else   
			   glVertex3f(0,0,-h_small-width*tan(roofangle));
			glVertex3f(0,0,0);
		glEnd();
		   //  xie	jiao
		glBegin(GL_POLYGON);
			glVertex3f(0,-width,-h_small);			 
			if(h_xbig>height)	
			   glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
			else   
			{
			   glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
			   if((h_xbig+h_ybig-h_small)>=height)
				  glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
			   else
				  glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
			}
			if(h_ybig>height)	
			   glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
			else 
			{  
				 if((h_xbig+h_ybig-h_small)>=height)
					 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
				 glVertex3f(0,0,-h_small -width*tan(roofangle));
			}
		glEnd();
		  // TOP
		glBegin(GL_POLYGON);
			if((h_xbig+h_ybig-h_small)>=height)
			{
				  glVertex3f(length, 0, -height );
				  if(h_xbig>height)
				  {  
					 glVertex3f(length,-width,-height); 				
					 glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);	   
				  }
				  else	 
					 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
	
				  if(h_ybig>height)
				  { 	
					 glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
					 glVertex3f(0,0,-height);
				  }
				  else	 
					 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
			}
		glEnd();  
	
		   // X = Length
		glBegin(GL_POLYGON);
			glVertex3f(length,0,0);
			glVertex3f(length,-width,0);
			if(h_xbig>height)
			{
			   glVertex3f(length,-width,-height);
			   glVertex3f(length, 0    ,-height);
			}
			else 
			{
			   glVertex3f(length, -width, -h_small-length*tan(wedgeangle)); 	 
			   if((h_xbig+h_ybig-h_small)>=height)
			   {
					 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
					 glVertex3f(length,0 ,-height); 							
			   }					
			   else
					 glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));	  
			}
		glEnd();
			// y = 0
	glColor4f(0.0f, 0.00f, 0.0f, 1);	
	// button z = 0

	// front y = - width 
	glBegin(GL_LINE_STRIP);
		glVertex3f(0,-width,0);
		glVertex3f(0,-width,-h_small);
		if(h_xbig>height)
		{	  
		   glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
		   glVertex3f(length,-width,-height);
		}
		else   
		   glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
		glVertex3f(length,-width,0);
	glEnd();
	//	  x = 0
	glBegin(GL_LINE_LOOP);
		glVertex3f(0,-width,0);
		glVertex3f(0,-width,-h_small);
		if(h_ybig>height)
		{	  
			glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
			glVertex3f(0, 0,-height);
		}
		else   
		   glVertex3f(0,0,-h_small-width*tan(roofangle));
		glVertex3f(0,0,0);
	glEnd();
	   //  xie	jiao
	glBegin(GL_LINE_LOOP);
		glVertex3f(0,-width,-h_small);			 
		if(h_xbig>height)	
		   glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
		else   
		{
		   glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
		   if((h_xbig+h_ybig-h_small)>=height)
			  glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
		   else
			  glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
		}
		if(h_ybig>height)	
		   glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
		else 
		{  
			 if((h_xbig+h_ybig-h_small)>=height)
				 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
			 glVertex3f(0,0,-h_small -width*tan(roofangle));
		}
	glEnd();
	  // TOP
	glBegin(GL_LINE_LOOP);
		if((h_xbig+h_ybig-h_small)>=height)
		{
			  glVertex3f(length, 0, -height );
			  if(h_xbig>height)
			  {  
				 glVertex3f(length,-width,-height); 				
				 glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);	   
			  }
			  else	 
				 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
	
			  if(h_ybig>height)
			  { 	
				 glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				 glVertex3f(0,0,-height);
			  }
			  else	 
				 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
		}
	glEnd();  
	
	   // X = Length
	glBegin(GL_LINE_LOOP);
		glVertex3f(length,0,0);
		glVertex3f(length,-width,0);
		if(h_xbig>height)
		{
		   glVertex3f(length,-width,-height);
		   glVertex3f(length, 0    ,-height);
		}
		else 
		{
		   glVertex3f(length, -width, -h_small-length*tan(wedgeangle)); 	 
		   if((h_xbig+h_ybig-h_small)>=height)
		   {
				 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
				 glVertex3f(length,0 ,-height); 							
		   }					
		   else
				 glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));	  
		}
	glEnd();
		// y = 0
	glBegin(GL_LINE_STRIP);
		glVertex3f(0, 0,0);
		if(h_ybig>=height)
		{
		   glVertex3f(0,0,-height);
		   glVertex3f(length, 0,-height);
		}
		else 
		{
		   glVertex3f(0, 0,-h_small-width*tan(roofangle));
		   if((h_xbig+h_ybig-h_small)>=height)
		   {
				 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
				 glVertex3f(length,0,-height);							   
		   }					
		   else
				 glVertex3f(length,0,-(h_xbig+h_ybig-h_small)); 	 
		}
	    glVertex3f(length,0,0);
	glEnd();  

	glPopMatrix (); 
	
	  

}

void DrawElement_2D_Flat(gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
       
     gdouble TempElementXS;
     gdouble TempElementYS;
     gdouble TempElementZXS;
     gdouble TempElementZYS;
     gdouble TempElementHX ;
     gdouble TempElementHY ;
     gdouble TempElementXLen;
     gdouble TempElementYWidth;
     
     gdouble x;
     gdouble y;
     gdouble z;
     gdouble d;
     gdouble e_x;
     gdouble e_y;
     gdouble e_zx;
     gdouble e_zy;
     gdouble s_x;
     gdouble s_y;
     gdouble s_zy;
     gdouble s_zx;
     
     gdouble xStart ;
     gdouble yStart ;
     gdouble zStart ;
     gdouble xOrg;
     gdouble yOrg;
     gdouble zOrg;
     gdouble zOrgTemp;
     int i;
     int j;    
             
     gdouble h0  = p->wedge_p->wg_heigh_fir ;                        // first element high
     gint Row  =    p->probe_p->ele_num_sec ;                        // element x direction numble
     gint Column    = p->probe_p->ele_num_pri;                       // element y direction numble
     gdouble Intervaly = p->probe_p->sec_axis_pitch ;                // y direction interval
     gdouble Intervalx = p->probe_p->pri_axis_pitch ;                // x direction interval distance
     gdouble ElementWidth = p->probe_p->sec_ele_size ;               // ydirection element length
     gdouble ElementLength  = p->probe_p->pri_ele_size ;             // x direction element width

     gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
     gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
     gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
     gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
     
     gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180   ;      // roofangle   y-z platform
     gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ;      // wedgeangle  x-z platform
          
     if(Column<=0||Row<=0) return ;
	 if(p->probe_p->D1_D2 == 0)  Row = 1 ;
     if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
     
     //  calculate the offset in each direction of one element
     if((wedgeangle != 0) && (roofangle != 0))
     {
          x = 1;
          y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
          z = y*tan(roofangle) ;
          d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
          e_x  = -ElementWidth*x/d;
          s_x  = -Intervaly*x/d    ;
          e_y  = -ElementWidth*y/d  ;
          s_y  = -Intervaly*y/d     ;
          e_zy  = -ElementWidth*(z-x*tan(wedgeangle))/d;
          s_zy  = -Intervaly*(z-x*tan(wedgeangle))/d   ;          
     }
     else
     {   
          e_y = -ElementWidth*cos(roofangle) ;
          s_y = -Intervaly*cos(roofangle);
          e_x = 0 ;
          s_x = 0 ;
          e_zy = -ElementWidth*sin(roofangle) ;
          s_zy = -Intervaly*sin(roofangle);
     }
     
     TempElementXLen = ElementLength*cos(wedgeangle) ;
     TempElementYWidth=-ElementWidth*cos(roofangle)   ;
     TempElementHX =   ElementLength*sin(wedgeangle) ;
     TempElementHY =   -ElementWidth*sin( roofangle  );
     TempElementXS =   Intervalx*cos(wedgeangle)     ;
     TempElementYS =   -Intervaly*cos(roofangle)      ;
     TempElementZXS=   Intervalx*sin(wedgeangle)     ;
     TempElementZYS=   -Intervaly*sin(roofangle)      ;
     if(roofangle<0) wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir ;
	 
     xOrg =   wg_pri_axis_reference + wg_pri_elem_offset_fir - TempElementXLen/2 - e_x/2 ;
	 yOrg =   -wg_sec_axis_reference - wg_sec_elem_offset_fir - e_y/2;
     zOrg =   -h0 +TempElementHX/2 - e_zy/2 ;        	 

     glPushMatrix ();
     for(i = 0; i<Column; i++)
     {
           xStart = xOrg + i*TempElementXS;
           zOrgTemp  = zOrg - i*TempElementZXS ;           
           for(j=0; j<Row; j++)
           {
                    yStart = yOrg + j*s_y;                   
                    zStart = zOrgTemp + j*s_zy;
                    glColor4f(0.9,0.9,0.9,0.8);
                    glBegin(GL_QUADS);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);
                    glEnd();
                    glColor4f(0.0,0.0,0.0,1.0);
                    glBegin(GL_LINE_LOOP);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);     
                    glEnd();
                    xStart = xStart + s_x ;
           }
     }
     glPopMatrix();
}

void DrawElement2DCylinderOD     (gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
       
     gdouble TempElementXS;
     gdouble TempElementYS;
     gdouble TempElementZXS;
     gdouble TempElementZYS;
     gdouble TempElementHX ;
     gdouble TempElementHY ;
     gdouble TempElementXLen;
     gdouble TempElementYWidth;
     
     gdouble x;
     gdouble y;
     gdouble z;
     gdouble d;
     gdouble e_x;
     gdouble e_y;
     gdouble e_zx;
     gdouble e_zy;
     gdouble s_x;
     gdouble s_y;
     gdouble s_zy;
     gdouble s_zx;
     
     gdouble xStart ;
     gdouble yStart ;
     gdouble zStart ;
     gdouble xOrg;
     gdouble yOrg;
     gdouble zOrg;
     gdouble zOrgTemp;
     int i;
     int j;    
             
     gdouble h0  = p->wedge_p->wg_heigh_fir ;                        // first element high
     gint Row  =    p->probe_p->ele_num_sec ;                        // element x direction numble
     gint Column    = p->probe_p->ele_num_pri;                       // element y direction numble
     gdouble Intervaly = p->probe_p->sec_axis_pitch ;                // y direction interval
     gdouble Intervalx = p->probe_p->pri_axis_pitch ;                // x direction interval distance
     gdouble ElementWidth = p->probe_p->sec_ele_size ;               // ydirection element length
     gdouble ElementLength  = p->probe_p->pri_ele_size ;             // x direction element width

     gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
     gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
     gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
     gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
     gdouble CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
	 gdouble length = p->wedge_p->wg_length ;
	 
     gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180   ;      // roofangle   y-z platform
     gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ;      // wedgeangle  x-z platform
          
     if(Column<=0||Row<=0) return ;
	 if(p->probe_p->D1_D2 == 0)  Row = 1 ;
     if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
     
     //  calculate the offset in each direction of one element
     if((wedgeangle != 0) && (roofangle != 0))
     {
          x = 1;
          y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
          z = y*tan(roofangle) ;
          d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
          e_x  = -ElementWidth*x/d;
          s_x  = -Intervaly*x/d    ;
          e_y  = -ElementWidth*y/d  ;
          s_y  = -Intervaly*y/d     ;
          e_zy  = -ElementWidth*(z-x*tan(wedgeangle))/d;
          s_zy  = -Intervaly*(z-x*tan(wedgeangle))/d   ;          
     }
     else
     {   
          e_y = -ElementWidth*cos(roofangle) ;
          s_y = -Intervaly*cos(roofangle);
          e_x = 0 ;
          s_x = 0 ;
          e_zy = -ElementWidth*sin(roofangle) ;
          s_zy = -Intervaly*sin(roofangle);
     }
     
      TempElementXLen = ElementLength*cos(wedgeangle) ;
      TempElementYWidth=-ElementWidth*cos(roofangle)   ;
      TempElementHX =   ElementLength*sin(wedgeangle) ;
      TempElementHY =   -ElementWidth*sin( roofangle  );
      TempElementXS =   Intervalx*cos(wedgeangle)     ;
      TempElementYS =   -Intervaly*cos(roofangle)      ;
      TempElementZXS=   Intervalx*sin(wedgeangle)     ;
      TempElementZYS=   -Intervaly*sin(roofangle)      ;
     if(roofangle<0)   wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir ;
     xOrg =   -p->wedge_p->wg_length/2+ wg_pri_elem_offset_fir - TempElementXLen/2 - e_x/2 ;
     yOrg =   -wg_sec_axis_reference - wg_sec_elem_offset_fir - e_y/2;
     zOrg =   -h0 +TempElementHX/2 - e_zy/2 -sqrt(CylindricalExtDiameter*CylindricalExtDiameter - length*length)/2  ;        
     
     glPushMatrix ();
     
     for(i = 0; i<Column; i++)
     {
           xStart = xOrg + i*TempElementXS;
           zOrgTemp  = zOrg - i*TempElementZXS ;           
           for(j=0; j<Row; j++)
           {
                    yStart = yOrg + j*s_y;                   
                    zStart = zOrgTemp + j*s_zy;
                    glColor4f(0.9,0.9,0.9,0.8);
                    glBegin(GL_QUADS);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);
                    glEnd();
                    glColor4f(0.0,0.0,0.0,1.0);
                    glBegin(GL_LINE_LOOP);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);     
                    glEnd();
                    xStart = xStart + s_x ;
           }
     }
     glPopMatrix();    
}

void DrawElement2DCylinderOD_Zero  (gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
       
     gdouble TempElementXS;
     gdouble TempElementYS;
     gdouble TempElementZXS;
     gdouble TempElementZYS;
     gdouble TempElementHX ;
     gdouble TempElementHY ;
     gdouble TempElementXLen;
     gdouble TempElementYWidth;
     
     gdouble x;
     gdouble y;
     gdouble z;
     gdouble d;
     gdouble e_x;
     gdouble e_y;
     gdouble e_zx;
     gdouble e_zy;
     gdouble s_x;
     gdouble s_y;
     gdouble s_zy;
     gdouble s_zx;
     
     gdouble xStart ;
     gdouble yStart ;
     gdouble zStart ;
     gdouble xOrg;
     gdouble yOrg;
     gdouble zOrg;
     gdouble zOrgTemp;
     int i;
     int j;    
             
     gdouble h0  = p->wedge_p->wg_heigh_fir ;                        // first element high
     gint Row  =    p->probe_p->ele_num_sec ;                        // element x direction numble
     gint Column    = p->probe_p->ele_num_pri;                       // element y direction numble
     gdouble Intervaly = p->probe_p->sec_axis_pitch ;                // y direction interval
     gdouble Intervalx = p->probe_p->pri_axis_pitch ;                // x direction interval distance
     gdouble ElementWidth = p->probe_p->sec_ele_size ;               // ydirection element length
     gdouble ElementLength  = p->probe_p->pri_ele_size ;             // x direction element width

     gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
     gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
     gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
     gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
     gdouble CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
	 gdouble width = p->wedge_p->wg_width;
	 
     gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180   ;      // roofangle   y-z platform
     gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ;      // wedgeangle  x-z platform
          
     if(Column<=0||Row<=0) return ;
	 if(p->probe_p->D1_D2 == 0)  Row = 1 ;
     if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
     
     //  calculate the offset in each direction of one element
     if((wedgeangle != 0) && (roofangle != 0))
     {
          x = 1;
          y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
          z = y*tan(roofangle) ;
          d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
          e_x  = -ElementWidth*x/d;
          s_x  = -Intervaly*x/d    ;
          e_y  = -ElementWidth*y/d  ;
          s_y  = -Intervaly*y/d     ;
          e_zy  = -ElementWidth*(z-x*tan(wedgeangle))/d;
          s_zy  = -Intervaly*(z-x*tan(wedgeangle))/d   ;          
     }
     else
     {   
          e_y = -ElementWidth*cos(roofangle) ;
          s_y = -Intervaly*cos(roofangle);
          e_x = 0 ;
          s_x = 0 ;
          e_zy = -ElementWidth*sin(roofangle) ;
          s_zy = -Intervaly*sin(roofangle);
     }
     
	 TempElementXLen = ElementLength*cos(wedgeangle)  ;
	 TempElementYWidth=-ElementWidth*cos(roofangle)   ;
	 TempElementHX =   ElementLength*sin(wedgeangle)  ;
	 TempElementHY =   -ElementWidth*sin(roofangle)   ;
	 TempElementXS =   Intervalx*cos(wedgeangle)      ;
	 TempElementYS =   -Intervaly*cos(roofangle)      ;
	 TempElementZXS=   Intervalx*sin(wedgeangle)      ;
	 TempElementZYS=   -Intervaly*sin(roofangle)      ;
	 
     if(roofangle<0)   wg_sec_elem_offset_fir = width - wg_sec_elem_offset_fir ;
	 
     xOrg =  wg_pri_axis_reference + wg_pri_elem_offset_fir - TempElementXLen/2 - e_x/2 ;
     yOrg =  width/2 - wg_sec_elem_offset_fir - e_y/2;
     zOrg =  -h0 +TempElementHX/2 - e_zy/2 -sqrt(CylindricalExtDiameter*CylindricalExtDiameter - width*width)/2  ;        
     
     glPushMatrix ();
     
     for(i = 0; i<Column; i++)
     {
           xStart = xOrg + i*TempElementXS;
           zOrgTemp  = zOrg - i*TempElementZXS ;           
           for(j=0; j<Row; j++)
           {
                    yStart = yOrg + j*s_y;                   
                    zStart = zOrgTemp + j*s_zy;
                    glColor4f(0.9,0.9,0.9,0.8);
                    glBegin(GL_QUADS);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);
                    glEnd();
                    glColor4f(0.0,0.0,0.0,1.0);
                    glBegin(GL_LINE_LOOP);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);     
                    glEnd();
                    xStart = xStart + s_x ;
           }
     }
     glPopMatrix();    
}


void DrawElement2DCylinderID_Zero  (gpointer data)
{
	DRAW_UI_P p = (DRAW_UI_P) data ;
	  
	gdouble TempElementXS;
	gdouble TempElementYS;
	gdouble TempElementZXS;
	gdouble TempElementZYS;
	gdouble TempElementHX ;
	gdouble TempElementHY ;
	gdouble TempElementXLen;
	gdouble TempElementYWidth;
	
	gdouble x;
	gdouble y;
	gdouble z;
	gdouble d;
	gdouble e_x;
	gdouble e_y;
	gdouble e_zx;
	gdouble e_zy;
	gdouble s_x;
	gdouble s_y;
	gdouble s_zy;
	gdouble s_zx;
	
	gdouble xStart ;
	gdouble yStart ;
	gdouble zStart ;
	gdouble xOrg;
	gdouble yOrg;
	gdouble zOrg;
	gdouble zOrgTemp;
	int i;
	int j;	  
			
	gdouble h0	= p->wedge_p->wg_heigh_fir ;						// first element high
	gint Row  =    p->probe_p->ele_num_sec ;						// element x direction numble
	gint Column    = p->probe_p->ele_num_pri;						// element y direction numble
	gdouble Intervaly = p->probe_p->sec_axis_pitch ;				// y direction interval
	gdouble Intervalx = p->probe_p->pri_axis_pitch ;				// x direction interval distance
	gdouble ElementWidth = p->probe_p->sec_ele_size ;				// ydirection element length
	gdouble ElementLength  = p->probe_p->pri_ele_size ; 			// x direction element width
	
	gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
	gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
	gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
	gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
	gdouble CylindricalIntDiameter = p->specimen->speci_inside_cylindrical ;
	gdouble width = p->wedge_p->wg_width;
	
	gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180	;	   // roofangle   y-z platform
	gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180	;	   // wedgeangle  x-z platform
		 
	if(Column<=0||Row<=0) return ;
	if(p->probe_p->D1_D2 == 0)	Row = 1 ;
	if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
	
	//	calculate the offset in each direction of one element
	if((wedgeangle != 0) && (roofangle != 0))
	{
		 x = 1;
		 y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
		 z = y*tan(roofangle) ;
		 d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
		 e_x  = -ElementWidth*x/d;
		 s_x  = -Intervaly*x/d	  ;
		 e_y  = -ElementWidth*y/d  ;
		 s_y  = -Intervaly*y/d	   ;
		 e_zy  = -ElementWidth*(z-x*tan(wedgeangle))/d;
		 s_zy  = -Intervaly*(z-x*tan(wedgeangle))/d   ; 		 
	}
	else
	{	
		 e_y = -ElementWidth*cos(roofangle) ;
		 s_y = -Intervaly*cos(roofangle);
		 e_x = 0 ;
		 s_x = 0 ;
		 e_zy = -ElementWidth*sin(roofangle) ;
		 s_zy = -Intervaly*sin(roofangle);
	}
	
	 TempElementXLen = ElementLength*cos(wedgeangle) ;
	 TempElementYWidth=-ElementWidth*cos(roofangle)   ;
	 TempElementHX =   ElementLength*sin(wedgeangle) ;
	 TempElementHY =   -ElementWidth*sin( roofangle  );
	 TempElementXS =   Intervalx*cos(wedgeangle)	 ;
	 TempElementYS =   -Intervaly*cos(roofangle)	  ;
	 TempElementZXS=   Intervalx*sin(wedgeangle)	 ;
	 TempElementZYS=   -Intervaly*sin(roofangle)	  ;
	if(roofangle<0)   wg_sec_elem_offset_fir = width - wg_sec_elem_offset_fir ;
	xOrg =	 wg_pri_axis_reference + wg_pri_elem_offset_fir - TempElementXLen/2 - e_x/2 ;
	yOrg =	 width/2 - wg_sec_elem_offset_fir - e_y/2;
	zOrg =	 -h0 +TempElementHX/2 - e_zy/2 +sqrt(CylindricalIntDiameter*CylindricalIntDiameter - width*width)/2  ;		
	
	glPushMatrix ();
	
	for(i = 0; i<Column; i++)
	{
		  xStart = xOrg + i*TempElementXS;
		  zOrgTemp	= zOrg - i*TempElementZXS ; 		  
		  for(j=0; j<Row; j++)
		  {
				   yStart = yOrg + j*s_y;					
				   zStart = zOrgTemp + j*s_zy;
				   glColor4f(0.9,0.9,0.9,0.8);
				   glBegin(GL_QUADS);
					   glVertex3f(xStart,yStart,zStart);
					   glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
					   glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
					   glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);
				   glEnd();
				   glColor4f(0.0,0.0,0.0,1.0);
				   glBegin(GL_LINE_LOOP);
					   glVertex3f(xStart,yStart,zStart);
					   glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
					   glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
					   glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);	   
				   glEnd();
				   xStart = xStart + s_x ;
		  }
	}
	glPopMatrix();	  

     

}


void DrawElementCylinderReceiverOD     (gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
       
     gdouble TempElementXS;
     gdouble TempElementYS;
     gdouble TempElementZXS;
     gdouble TempElementZYS;
     gdouble TempElementHX ;
     gdouble TempElementHY ;
     gdouble TempElementXLen;
     gdouble TempElementYWidth;
     
     gdouble x;
     gdouble y;
     gdouble z;
     gdouble d;
     gdouble e_x;
     gdouble e_y;
     gdouble e_zx;
     gdouble e_zy;
     gdouble s_x;
     gdouble s_y;
     gdouble s_zy;
     gdouble s_zx;
     
     gdouble xStart ;
     gdouble yStart ;
     gdouble zStart ;
     gdouble xOrg;
     gdouble yOrg;
     gdouble zOrg;
     gdouble zOrgTemp;
     int i;
     int j;    
             
     gdouble h0  = p->wedge_r->wg_heigh_fir ;                        // first element high
     gint Row  =    p->probe_p->ele_num_sec ;                        // element x direction numble
     gint Column    = p->probe_p->ele_num_pri;                       // element y direction numble
     gdouble Intervaly = p->probe_p->sec_axis_pitch ;                // y direction interval
     gdouble Intervalx = p->probe_p->pri_axis_pitch ;                // x direction interval distance
     gdouble ElementWidth = p->probe_p->sec_ele_size ;               // ydirection element length
     gdouble ElementLength  = p->probe_p->pri_ele_size ;             // x direction element width

     gdouble wg_pri_axis_reference  = p->wedge_r->wg_pri_axis_reference; /*主轴楔块参考位置*/
     gdouble wg_sec_axis_reference  = p->wedge_r->wg_sec_axis_reference; /*次轴楔块参考位置*/
     gdouble wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
     gdouble wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
     gdouble CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
	 gdouble length = p->wedge_r->wg_length ;
     gdouble separation = p->wedge_r->wg_separation; 
     gdouble  roofangle = p->wedge_r->wg_roof_angle*PI/180   ;      // roofangle   y-z platform
     gdouble  wedgeangle= p->wedge_r->wg_wedge_angle*PI/180  ;      // wedgeangle  x-z platform

     gdouble wg_pri_axis_reference1  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
     gdouble wg_sec_axis_reference1  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
     gdouble wg_pri_elem_offset_fir1 = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
     gdouble wg_sec_elem_offset_fir1 = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
     gdouble roofangle1 = p->wedge_p->wg_roof_angle ;

          
     if(Column<=0||Row<=0) return ;
	 if(p->probe_p->D1_D2 == 0)  Row = 1 ;
     if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
     
     //  calculate the offset in each direction of one element
     if((wedgeangle != 0) && (roofangle != 0))
     {
          x = 1;
          y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
          z = y*tan(roofangle) ;
          d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
          e_x  = -ElementWidth*x/d;
          s_x  = -Intervaly*x/d    ;
          e_y  = -ElementWidth*y/d  ;
          s_y  = -Intervaly*y/d     ;
          e_zy  = -ElementWidth*(z-x*tan(wedgeangle))/d;
          s_zy  = -Intervaly*(z-x*tan(wedgeangle))/d   ;          
     }
     else
     {   
          e_y = -ElementWidth*cos(roofangle) ;
          s_y = Intervaly*cos(roofangle);
          e_x = 0 ;
          s_x = 0 ;
          e_zy = -ElementWidth*sin(roofangle) ;
          s_zy = -Intervaly*sin(roofangle);
     }

     
      TempElementXLen = ElementLength*cos(wedgeangle) ;
      TempElementYWidth=-ElementWidth*cos(roofangle)   ;
      TempElementHX =   ElementLength*sin(wedgeangle) ;
      TempElementHY =   -ElementWidth*sin( roofangle  );
      TempElementXS =   Intervalx*cos(wedgeangle)     ;
      TempElementYS =   -Intervaly*cos(roofangle)      ;
      TempElementZXS=   Intervalx*sin(wedgeangle)     ;
      TempElementZYS=   -Intervaly*sin(roofangle)      ;

	 if(roofangle1>=0 )
	      yOrg = -wg_sec_axis_reference1 -wg_sec_elem_offset_fir1 -separation -e_y/2        ;
     if(roofangle1<0 ) 
	 	  yOrg = -wg_sec_axis_reference1 + wg_sec_elem_offset_fir1 -separation -e_y/2; 

     xOrg =   -p->wedge_p->wg_length/2+ wg_pri_elem_offset_fir - TempElementXLen/2 - e_x/2 ;
     //yOrg =   -wg_sec_axis_reference - wg_sec_elem_offset_fir - e_y/2-p->wedge_r->wg_separation;
     zOrg =   -h0 +TempElementHX/2 - e_zy/2 -sqrt(CylindricalExtDiameter*CylindricalExtDiameter - length*length)/2  ;        
     
     glPushMatrix ();
     
     for(i = 0; i<Column; i++)
     {
           xStart = xOrg + i*TempElementXS;
           zOrgTemp  = zOrg - i*TempElementZXS ;           
           for(j=0; j<Row; j++)
           {
                    yStart = yOrg + j*s_y;                   
                    zStart = zOrgTemp + j*s_zy;
                    glColor4f(0.9,0.9,0.9,0.8);
                    glBegin(GL_QUADS);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);
                    glEnd();
                    glColor4f(0.0,0.0,0.0,1.0);
                    glBegin(GL_LINE_LOOP);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);     
                    glEnd();
                    xStart = xStart + s_x ;
           }
     }
     glPopMatrix();    
}


void DrawElementCylinderReceiverID     (gpointer data)
{
		 DRAW_UI_P p = (DRAW_UI_P) data ;
		   
		 gdouble TempElementXS;
		 gdouble TempElementYS;
		 gdouble TempElementZXS;
		 gdouble TempElementZYS;
		 gdouble TempElementHX ;
		 gdouble TempElementHY ;
		 gdouble TempElementXLen;
		 gdouble TempElementYWidth;
		 
		 gdouble x;
		 gdouble y;
		 gdouble z;
		 gdouble d;
		 gdouble e_x;
		 gdouble e_y;
		 gdouble e_zx;
		 gdouble e_zy;
		 gdouble s_x;
		 gdouble s_y;
		 gdouble s_zy;
		 gdouble s_zx;
		 
		 gdouble xStart ;
		 gdouble yStart ;
		 gdouble zStart ;
		 gdouble xOrg;
		 gdouble yOrg;
		 gdouble zOrg;
		 gdouble zOrgTemp;
		 int i;
		 int j;    
				 
		 gdouble h0  = p->wedge_r->wg_heigh_fir ;						 // first element high
		 gint Row  =	p->probe_p->ele_num_sec ;						 // element x direction numble
		 gint Column	= p->probe_p->ele_num_pri;						 // element y direction numble
		 gdouble Intervaly = p->probe_p->sec_axis_pitch ;				 // y direction interval
		 gdouble Intervalx = p->probe_p->pri_axis_pitch ;				 // x direction interval distance
		 gdouble ElementWidth = p->probe_p->sec_ele_size ;				 // ydirection element length
		 gdouble ElementLength	= p->probe_p->pri_ele_size ;			 // x direction element width
	
		 gdouble wg_pri_axis_reference	= p->wedge_r->wg_pri_axis_reference; /*主轴楔块参考位置*/
		 gdouble wg_sec_axis_reference	= p->wedge_r->wg_sec_axis_reference; /*次轴楔块参考位置*/
		 gdouble wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
		 gdouble wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
		 gdouble CylindricalIntDiameter = p->specimen->speci_inside_cylindrical ;
		 gdouble length = p->wedge_r->wg_length ;
		 gdouble separation = p->wedge_r->wg_separation; 
		 gdouble  roofangle = p->wedge_r->wg_roof_angle*PI/180	 ;		// roofangle   y-z platform
		 gdouble  wedgeangle= p->wedge_r->wg_wedge_angle*PI/180  ;		// wedgeangle  x-z platform
	
		 gdouble wg_pri_axis_reference1  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
		 gdouble wg_sec_axis_reference1  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
		 gdouble wg_pri_elem_offset_fir1 = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
		 gdouble wg_sec_elem_offset_fir1 = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
		 gdouble roofangle1 = p->wedge_p->wg_roof_angle ;
	
			  
		 if(Column<=0||Row<=0) return ;
		 if(p->probe_p->D1_D2 == 0)  Row = 1 ;
		 if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
		 
		 //  calculate the offset in each direction of one element
		 if((wedgeangle != 0) && (roofangle != 0))
		 {
			  x = 1;
			  y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
			  z = y*tan(roofangle) ;
			  d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
			  e_x  = -ElementWidth*x/d;
			  s_x  = -Intervaly*x/d    ;
			  e_y  = -ElementWidth*y/d	;
			  s_y  = -Intervaly*y/d 	;
			  e_zy	= -ElementWidth*(z-x*tan(wedgeangle))/d;
			  s_zy	= -Intervaly*(z-x*tan(wedgeangle))/d   ;		  
		 }
		 else
		 {	 
			  e_y = -ElementWidth*cos(roofangle) ;
			  s_y = Intervaly*cos(roofangle);
			  e_x = 0 ;
			  s_x = 0 ;
			  e_zy = -ElementWidth*sin(roofangle) ;
			  s_zy = -Intervaly*sin(roofangle);
		 }
	
		 
		  TempElementXLen = ElementLength*cos(wedgeangle) ;
		  TempElementYWidth=-ElementWidth*cos(roofangle)   ;
		  TempElementHX =	ElementLength*sin(wedgeangle) ;
		  TempElementHY =	-ElementWidth*sin( roofangle  );
		  TempElementXS =	Intervalx*cos(wedgeangle)	  ;
		  TempElementYS =	-Intervaly*cos(roofangle)	   ;
		  TempElementZXS=	Intervalx*sin(wedgeangle)	  ;
		  TempElementZYS=	-Intervaly*sin(roofangle)	   ;
	
		 if(roofangle1>=0 )
			  yOrg = -wg_sec_axis_reference1 -wg_sec_elem_offset_fir1 -separation -e_y/2		;
		 if(roofangle1<0 ) 
			  yOrg = -wg_sec_axis_reference1 + wg_sec_elem_offset_fir1 -separation -e_y/2; 
	
		 xOrg =   -p->wedge_p->wg_length/2+ wg_pri_elem_offset_fir - TempElementXLen/2 - e_x/2 ;
		 //yOrg =	-wg_sec_axis_reference - wg_sec_elem_offset_fir - e_y/2-p->wedge_r->wg_separation;
		 zOrg =   -h0 +TempElementHX/2 - e_zy/2 + sqrt(CylindricalIntDiameter*CylindricalIntDiameter - length*length)/2	;		 
		 
		 glPushMatrix ();
		 
		 for(i = 0; i<Column; i++)
		 {
			   xStart = xOrg + i*TempElementXS;
			   zOrgTemp  = zOrg - i*TempElementZXS ;		   
			   for(j=0; j<Row; j++)
			   {
						yStart = yOrg + j*s_y;					 
						zStart = zOrgTemp + j*s_zy;
						glColor4f(0.9,0.9,0.9,0.8);
						glBegin(GL_QUADS);
							glVertex3f(xStart,yStart,zStart);
							glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
							glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
							glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);
						glEnd();
						glColor4f(0.0,0.0,0.0,1.0);
						glBegin(GL_LINE_LOOP);
							glVertex3f(xStart,yStart,zStart);
							glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
							glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
							glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX); 	
						glEnd();
						xStart = xStart + s_x ;
			   }
		 }
		 glPopMatrix();    
}

void DrawElement2DCylinderID (gpointer data)
{
	DRAW_UI_P p = (DRAW_UI_P) data ;
	  
	gdouble TempElementXS;
	gdouble TempElementYS;
	gdouble TempElementZXS;
	gdouble TempElementZYS;
	gdouble TempElementHX ;
	gdouble TempElementHY ;
	gdouble TempElementXLen;
	gdouble TempElementYWidth;
	
	gdouble x;
	gdouble y;
	gdouble z;
	gdouble d;
	gdouble e_x;
	gdouble e_y;
	gdouble e_zx;
	gdouble e_zy;
	gdouble s_x;
	gdouble s_y;
	gdouble s_zy;
	gdouble s_zx;
	
	gdouble xStart ;
	gdouble yStart ;
	gdouble zStart ;
	gdouble xOrg;
	gdouble yOrg;
	gdouble zOrg;
	gdouble zOrgTemp;
	int i;
	int j;	  
			
	gdouble h0	= p->wedge_p->wg_heigh_fir ;						// first element high
	gint Row  =    p->probe_p->ele_num_sec ;						// element x direction numble
	gint Column    = p->probe_p->ele_num_pri;						// element y direction numble
	gdouble Intervaly = p->probe_p->sec_axis_pitch ;				// y direction interval
	gdouble Intervalx = p->probe_p->pri_axis_pitch ;				// x direction interval distance
	gdouble ElementWidth = p->probe_p->sec_ele_size ;				// ydirection element length
	gdouble ElementLength  = p->probe_p->pri_ele_size ; 			// x direction element width
	
	gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
	gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
	gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
	gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
	gdouble CylindricalIntDiameter = p->specimen->speci_inside_cylindrical ;
	gdouble length = p->wedge_p->wg_length ;
	
	gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180	;	   // roofangle   y-z platform
	gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180	;	   // wedgeangle  x-z platform
		 
	if(Column<=0||Row<=0) return ;
	if(p->probe_p->D1_D2 == 0)	Row = 1 ;
	if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
	
	//	calculate the offset in each direction of one element
	if((wedgeangle != 0) && (roofangle != 0))
	{
		 x = 1;
		 y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
		 z = y*tan(roofangle) ;
		 d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
		 e_x  = -ElementWidth*x/d;
		 s_x  = -Intervaly*x/d	  ;
		 e_y  = -ElementWidth*y/d  ;
		 s_y  = -Intervaly*y/d	   ;
		 e_zy  = -ElementWidth*(z-x*tan(wedgeangle))/d;
		 s_zy  = -Intervaly*(z-x*tan(wedgeangle))/d   ; 		 
	}
	else
	{	
		 e_y = -ElementWidth*cos(roofangle) ;
		 s_y = -Intervaly*cos(roofangle);
		 e_x = 0 ;
		 s_x = 0 ;
		 e_zy = -ElementWidth*sin(roofangle) ;
		 s_zy = -Intervaly*sin(roofangle);
	}
	
	 TempElementXLen = ElementLength*cos(wedgeangle) ;
	 TempElementYWidth=-ElementWidth*cos(roofangle)   ;
	 TempElementHX =   ElementLength*sin(wedgeangle) ;
	 TempElementHY =   -ElementWidth*sin( roofangle  );
	 TempElementXS =   Intervalx*cos(wedgeangle)	 ;
	 TempElementYS =   -Intervaly*cos(roofangle)	  ;
	 TempElementZXS=   Intervalx*sin(wedgeangle)	 ;
	 TempElementZYS=   -Intervaly*sin(roofangle)	  ;
	if(roofangle<0)   wg_sec_elem_offset_fir = -wg_sec_elem_offset_fir ;
	xOrg =	 -p->wedge_p->wg_length/2+ wg_pri_elem_offset_fir - TempElementXLen/2 - e_x/2 ;
	yOrg =	 -wg_sec_axis_reference - wg_sec_elem_offset_fir - e_y/2;
	zOrg =	 -h0 +TempElementHX/2 - e_zy/2 +sqrt(CylindricalIntDiameter*CylindricalIntDiameter - length*length)/2  ;		
	
	glPushMatrix ();
	
	for(i = 0; i<Column; i++)
	{
		  xStart = xOrg + i*TempElementXS;
		  zOrgTemp	= zOrg - i*TempElementZXS ; 		  
		  for(j=0; j<Row; j++)
		  {
				   yStart = yOrg + j*s_y;					
				   zStart = zOrgTemp + j*s_zy;
				   glColor4f(0.9,0.9,0.9,0.8);
				   glBegin(GL_QUADS);
					   glVertex3f(xStart,yStart,zStart);
					   glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
					   glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
					   glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);
				   glEnd();
				   glColor4f(0.0,0.0,0.0,1.0);
				   glBegin(GL_LINE_LOOP);
					   glVertex3f(xStart,yStart,zStart);
					   glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
					   glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
					   glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);	   
				   glEnd();
				   xStart = xStart + s_x ;
		  }
	}
	glPopMatrix();	  

     
}

void DrawElement_2D_Flat2D_Inverse(gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
       
     gdouble TempElementXS;
     gdouble TempElementYS;
     gdouble TempElementZXS;
     gdouble TempElementZYS;
     gdouble TempElementHX ;
     gdouble TempElementHY ;
     gdouble TempElementXLen;
     gdouble TempElementYWidth;
     
     gdouble x;
     gdouble y;
     gdouble z;
     gdouble d;
     gdouble e_x;
     gdouble e_y;
     gdouble e_zx;
     gdouble e_zy;
     gdouble s_x;
     gdouble s_y;
     gdouble s_zy;
     gdouble s_zx;
     
     gdouble xStart ;
     gdouble yStart ;
     gdouble zStart ;
     gdouble xOrg;
     gdouble yOrg;
     gdouble zOrg;
     gdouble zOrgTemp;
     int i;
     int j;    
             
     gdouble h0  = p->wedge_p->wg_heigh_fir ;                        // first element high
     gint Row  =    p->probe_p->ele_num_sec ;                        // element x direction numble
     gint Column    = p->probe_p->ele_num_pri;                       // element y direction numble
     gdouble Intervaly = p->probe_p->sec_axis_pitch ;                // y direction interval
     gdouble Intervalx = p->probe_p->pri_axis_pitch ;                // x direction interval distance
     gdouble ElementWidth = p->probe_p->sec_ele_size ;               // ydirection element length
     gdouble ElementLength  = p->probe_p->pri_ele_size ;             // x direction element width

     gdouble wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
     gdouble wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
     gdouble wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
     gdouble wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
     gdouble wg_separation = p->wedge_r->wg_separation ;
	 gdouble width = p->wedge_p->wg_width ;
	 
     gdouble  roofangle = p->wedge_p->wg_roof_angle*PI/180   ;      // roofangle   y-z platform
     gdouble  wedgeangle= p->wedge_p->wg_wedge_angle*PI/180  ;      // wedgeangle  x-z platform
          
     if(Column<=0||Row<=0) return ;
	  if(p->probe_p->D1_D2 == 0)  Row = 1 ;
     if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
     
     //  calculate the offset in each direction of one element
     if((wedgeangle != 0) && (roofangle != 0))
     {
          x = 1;
          y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
          z = y*tan(roofangle) ;
          d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
          e_x  = -ElementWidth*x/d;
          s_x  = -Intervaly*x/d    ;
          e_y  = ElementWidth*y/d  ;
          s_y  = Intervaly*y/d     ;
          e_zy  = -ElementWidth*(z-x*tan(wedgeangle))/d;
          s_zy  = -Intervaly*(z-x*tan(wedgeangle))/d   ;          
     }
     else
     {   
          e_y = ElementWidth*cos(roofangle) ;
          s_y = Intervaly*cos(roofangle);
          e_x = 0 ;
          s_x = 0 ;
          e_zy = -ElementWidth*sin(roofangle) ;
          s_zy = -Intervaly*sin(roofangle);
     }
     
      TempElementXLen = ElementLength*cos(wedgeangle) ;
      TempElementYWidth=ElementWidth*cos(roofangle)   ;
      TempElementHX =   ElementLength*sin(wedgeangle) ;
      TempElementHY =   -ElementWidth*sin( roofangle  );
      TempElementXS =   Intervalx*cos(wedgeangle)     ;
      TempElementYS =   Intervaly*cos(roofangle)      ;
      TempElementZXS=   Intervalx*sin(wedgeangle)     ;
      TempElementZYS=   -Intervaly*sin(roofangle)      ;

     xOrg =   wg_pri_axis_reference + wg_pri_elem_offset_fir - TempElementXLen/2 - e_x/2 ;
     yOrg =   -wg_sec_axis_reference - wg_sec_elem_offset_fir - wg_separation  - e_y/2;
     zOrg =   -h0 +TempElementHX/2 - e_zy/2 ;        
     
     glPushMatrix ();
     
     for(i = 0; i<Column; i++)
     {
           xStart = xOrg + i*TempElementXS;
           zOrgTemp  = zOrg - i*TempElementZXS ;           
           for(j=0; j<Row; j++)
           {
                    yStart = yOrg + j*s_y;                   
                    zStart = zOrgTemp + j*s_zy;
                    glColor4f(0.9,0.9,0.9,0.8);
                    glBegin(GL_QUADS);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);
                    glEnd();
                    glColor3f(0.0,0.0,0.0);
                    glBegin(GL_LINE_LOOP);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);     
                    glEnd();
                    xStart = xStart + s_x ;
           }
     }
     glPopMatrix();
}

void DrawWedgePitchReceive(gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
     if(p->wedge_p->wg_roof_angle>=0)
	        DrawWedge2D(p);
	 else 
	 	    DrawWedge2D_Inverse(p);
	 if(p->wedge_r->wg_roof_angle>0)
	 	    DrawWedge2DReceiver(p);
	 else   
	 	    DrawWedge2DReceiverInverse(p);
}


void DrawWedge2DReceiver(gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
    gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;

	gdouble wedgeangle1,roofangle1,wg_heigh_fir1;
    gdouble wg_pri_elem_offset_fir1,wg_sec_elem_offset_fir1;
    gdouble wg_pri_axis_reference1,wg_sec_axis_reference1;
    gdouble width1,length1,height1;
    gdouble separation;
	gdouble ySpace;
	
	wedgeangle=p->wedge_r->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =p->wedge_r->wg_roof_angle*PI/180;  /* 顶角 */
    wg_heigh_fir=p->wedge_r->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_r->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_r->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width =p->wedge_r->wg_width;     /*楔块宽度*/
    length=p->wedge_r->wg_length;    /*楔块长度*/
    height=p->wedge_r->wg_height;/*楔块高度*/
    separation = p->wedge_r->wg_separation ;
	wedgeangle1=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle1 =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
    wg_heigh_fir1=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir1 = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir1 = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference1  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference1  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width1 =p->wedge_p->wg_width;     /*楔块宽度*/
    length1=p->wedge_p->wg_length;    /*楔块长度*/
    height1=p->wedge_p->wg_height;/*楔块高度*/

	
    if(roofangle1>=0)
	        ySpace = -wg_sec_axis_reference1 - 	wg_sec_elem_offset_fir1 - separation + wg_sec_elem_offset_fir ;
    else    
		    ySpace = -wg_sec_axis_reference1  + wg_sec_elem_offset_fir1 -separation +wg_sec_elem_offset_fir;
	
    if(wedgeangle==PI/2||roofangle==PI/2)  return ;
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
 
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    
    glPushMatrix ();
    glTranslatef(wg_pri_axis_reference,ySpace,0.0f);       
   /*绘制楔块*/ 
   glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha               
       // button z = 0
       glBegin(GL_QUADS);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       // front y = 0 
       glBegin(GL_POLYGON);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
              glVertex3f(length,0,-height);
           }
           else   
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
           glVertex3f(length,0,0);
       glEnd();
       //    x = 0
       glBegin(GL_POLYGON);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
               glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
               glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
          //  xie  jiao
       glBegin(GL_POLYGON);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                glVertex3f(0,-width,-h_small -width*tan(roofangle));
           }
       glEnd();
         // TOP
       glBegin(GL_POLYGON);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  

          // X = Length
       glBegin(GL_POLYGON);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
           // y = width
       glBegin(GL_POLYGON);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
           if(h_ybig>height)
           {
              glVertex3f(0,-width,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();            
       
   glColor4f(0.0f, 0.00f, 0.0f, 1);    
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
              glVertex3f(length,0,-height);
           }
           else   
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
           glVertex3f(length,0,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
              glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);   
                glVertex3f(0,-width,-h_small - width*tan(roofangle));
           }
       glEnd(); 
       glBegin(GL_LINE_LOOP);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  
       
       glBegin(GL_LINE_LOOP);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
       
       glBegin(GL_LINE_LOOP);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
           if(h_ybig>height)
           {
              glVertex3f(0,-width,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
      
   glPopMatrix (); 
}

void DrawWedge2DReceiverInverse(gpointer  data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
    gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;

	gdouble wedgeangle1,roofangle1,wg_heigh_fir1;
    gdouble wg_pri_elem_offset_fir1,wg_sec_elem_offset_fir1;
    gdouble wg_pri_axis_reference1,wg_sec_axis_reference1;
    gdouble width1,length1,height1;
    gdouble separation;
	gdouble ySpace;
	
	wedgeangle=p->wedge_r->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =fabs(p->wedge_r->wg_roof_angle*PI/180);  /* 顶角 */
    wg_heigh_fir=p->wedge_r->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_r->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_r->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width =p->wedge_r->wg_width;     /*楔块宽度*/
    length=p->wedge_r->wg_length;    /*楔块长度*/
    height=p->wedge_r->wg_height;/*楔块高度*/
    separation = p->wedge_r->wg_separation ;
	wedgeangle1=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle1 =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
    wg_heigh_fir1=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir1 = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir1 = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference1  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference1  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width1 =p->wedge_p->wg_width;     /*楔块宽度*/
    length1=p->wedge_p->wg_length;    /*楔块长度*/
    height1=p->wedge_p->wg_height;/*楔块高度*/

	
    if(roofangle1>=0)
	        ySpace = -wg_sec_axis_reference1 - 	wg_sec_elem_offset_fir1 - separation - wg_sec_elem_offset_fir + width ;
    else    
		    ySpace = -wg_sec_axis_reference1  + wg_sec_elem_offset_fir1 -separation - wg_sec_elem_offset_fir + width;

	if(wedgeangle==PI/2||roofangle==PI/2)  return ;
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
 
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    
    glPushMatrix ();
	//双晶和ROOF角小于0时 楔块的偏移量不一样.
	glTranslatef(wg_pri_axis_reference, ySpace, 0.0);
        
    /*绘制楔块*/ 
    glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha               
       // button z = 0
       glBegin(GL_QUADS);
           glVertex3f(0,0,0);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           glVertex3f(0,-width,0);
       glEnd();
       // front y = - width 
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,0);
           glVertex3f(0,-width,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
              glVertex3f(length,-width,-height);
           }
           else   
              glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
           glVertex3f(length,-width,0);
       glEnd();
       //    x = 0
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,0);
           glVertex3f(0,-width,-h_small);
           if(h_ybig>height)
           {     
               glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
               glVertex3f(0, 0,-height);
           }
           else   
              glVertex3f(0,0,-h_small-width*tan(roofangle));
           glVertex3f(0,0,0);
       glEnd();
          //  xie  jiao
       glBegin(GL_POLYGON);
           glVertex3f(0,-width,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
           else   
           {
              glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
           }
           if(h_ybig>height)   
              glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
                glVertex3f(0,0,-h_small -width*tan(roofangle));
           }
       glEnd();
         // TOP
       glBegin(GL_POLYGON);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, 0, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,-width,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);      
                 }
                 else   
                    glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,0,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
           }
       glEnd();  

          // X = Length
       glBegin(GL_POLYGON);
           glVertex3f(length,0,0);
           glVertex3f(length,-width,0);
           if(h_xbig>height)
           {
              glVertex3f(length,-width,-height);
              glVertex3f(length, 0    ,-height);
           }
           else 
           {
              glVertex3f(length, -width, -h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,0 ,-height);                             
              }                    
              else
                    glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
           // y = 0
       glBegin(GL_POLYGON);
           glVertex3f(length,0,0);
           glVertex3f(0, 0,0);
           if(h_ybig>=height)
           {
              glVertex3f(0,0,-height);
              glVertex3f(length, 0,-height);
           }
           else 
           {
              glVertex3f(0, 0,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
                    glVertex3f(length,0,-height);                             
              }                    
              else
                    glVertex3f(length,0,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();            
       
   glColor4f(0.0f, 0.00f, 0.0f, 1);    
   // button z = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,0,0);
	   glVertex3f(length,0,0);
	   glVertex3f(length,-width,0);
	   glVertex3f(0,-width,0);
   glEnd();
   // front y = - width 
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,0);
	   glVertex3f(0,-width,-h_small);
	   if(h_xbig>height)
	   {	 
		  glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
		  glVertex3f(length,-width,-height);
	   }
	   else   
		  glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
	   glVertex3f(length,-width,0);
   glEnd();
   //	 x = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,0);
	   glVertex3f(0,-width,-h_small);
	   if(h_ybig>height)
	   {	 
		   glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
		   glVertex3f(0, 0,-height);
	   }
	   else   
		  glVertex3f(0,0,-h_small-width*tan(roofangle));
	   glVertex3f(0,0,0);
   glEnd();
	  //  xie  jiao
   glBegin(GL_LINE_LOOP);
	   glVertex3f(0,-width,-h_small);			
	   if(h_xbig>height)   
		  glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
	   else   
	   {
		  glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
		  if((h_xbig+h_ybig-h_small)>=height)
			 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
		  else
			 glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
	   }
	   if(h_ybig>height)   
		  glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
	   else 
	   {  
			if((h_xbig+h_ybig-h_small)>=height)
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
			glVertex3f(0,0,-h_small -width*tan(roofangle));
	   }
   glEnd();
	 // TOP
   glBegin(GL_LINE_LOOP);
	   if((h_xbig+h_ybig-h_small)>=height)
	   {
			 glVertex3f(length, 0, -height );
			 if(h_xbig>height)
			 {	
				glVertex3f(length,-width,-height);				   
				glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);	  
			 }
			 else	
				glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
   
			 if(h_ybig>height)
			 {	   
				glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				glVertex3f(0,0,-height);
			 }
			 else	
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
	   }
   glEnd();  
   
	  // X = Length
   glBegin(GL_LINE_LOOP);
	   glVertex3f(length,0,0);
	   glVertex3f(length,-width,0);
	   if(h_xbig>height)
	   {
		  glVertex3f(length,-width,-height);
		  glVertex3f(length, 0	  ,-height);
	   }
	   else 
	   {
		  glVertex3f(length, -width, -h_small-length*tan(wedgeangle));		
		  if((h_xbig+h_ybig-h_small)>=height)
		  {
				glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
				glVertex3f(length,0 ,-height);							   
		  } 				   
		  else
				glVertex3f(length, 0,-(h_xbig+h_ybig-h_small)); 	 
	   }
   glEnd();
	   // y = 0
   glBegin(GL_LINE_LOOP);
	   glVertex3f(length,0,0);
	   glVertex3f(0, 0,0);
	   if(h_ybig>=height)
	   {
		  glVertex3f(0,0,-height);
		  glVertex3f(length, 0,-height);
	   }
	   else 
	   {
		  glVertex3f(0, 0,-h_small-width*tan(roofangle));
		  if((h_xbig+h_ybig-h_small)>=height)
		  {
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
				glVertex3f(length,0,-height);							  
		  } 				   
		  else
				glVertex3f(length,0,-(h_xbig+h_ybig-h_small));		
	   }
   glEnd();  

      
   glPopMatrix (); 
}

void DrawElement_2D_FlatPitchReceive(gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
     DrawElement_2D_Flat(p);  
     DrawElement2DReceiver(p) ;
}
void DrawElement2DReceiver(gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;  
     gdouble TempElementXS;
     gdouble TempElementYS;
     gdouble TempElementZXS;
     gdouble TempElementZYS;
     gdouble TempElementHX ;
     gdouble TempElementHY ;
     gdouble TempElementXLen;
     gdouble TempElementYWidth;
     
     gdouble x;
     gdouble y;
     gdouble z;
     gdouble d;
     gdouble e_x;
     gdouble e_y;
     gdouble e_zx;
     gdouble e_zy;
     gdouble s_x;
     gdouble s_y;
     gdouble s_zy;
     gdouble s_zx;
     
     gdouble xStart ;
     gdouble yStart ;
     gdouble zStart ;
     gdouble xOrg;
     gdouble yOrg;
     gdouble zOrg;
     gdouble zOrgTemp;
     int i;
     int j;    
             
     gdouble h0  = p->wedge_r->wg_heigh_fir ;                        // first element high
     gint Row  =    p->probe_p->ele_num_sec ;                        // element x direction numble
     gint Column    = p->probe_p->ele_num_pri;                       // element y direction numble
     gdouble Intervaly = p->probe_p->sec_axis_pitch ;                // y direction interval
     gdouble Intervalx = p->probe_p->pri_axis_pitch ;                // x direction interval distance
     gdouble ElementWidth = p->probe_p->sec_ele_size ;               // ydirection element length
     gdouble ElementLength  = p->probe_p->pri_ele_size ;             // x direction element width

     gdouble wg_pri_axis_reference  = p->wedge_r->wg_pri_axis_reference; /*主轴楔块参考位置*/
     gdouble wg_sec_axis_reference  = p->wedge_r->wg_sec_axis_reference; /*次轴楔块参考位置*/
     gdouble wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
     gdouble wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
     gdouble width = p->wedge_r->wg_width;
     gdouble  roofangle = p->wedge_r->wg_roof_angle*PI/180   ;      // roofangle   y-z platform
     gdouble  wedgeangle= p->wedge_r->wg_wedge_angle*PI/180  ;      // wedgeangle  x-z platform
     gdouble  separation = p->wedge_r->wg_separation;

	 gdouble wg_pri_axis_reference1  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
     gdouble wg_sec_axis_reference1  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
     gdouble wg_pri_elem_offset_fir1 = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
     gdouble wg_sec_elem_offset_fir1 = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
     gdouble width1 = p->wedge_r->wg_width ;
     gdouble  roofangle1 = p->wedge_p->wg_roof_angle*PI/180   ;         // roofangle   y-z platform
     gdouble  wedgeangle1= p->wedge_p->wg_wedge_angle*PI/180  ;         // wedgeangle  x-z platform
          
     if(Column<=0||Row<=0) return ;
	 if(p->probe_p->D1_D2 == 0)  Row = 1 ;
     if(wedgeangle == PI/2 || roofangle == PI/2)  return ;
     
     //  calculate the offset in each direction of one element
     if((wedgeangle != 0) && (roofangle != 0))
     {
          x = 1;
          y = cos(roofangle)/(sin(roofangle)*sin(wedgeangle)*cos(wedgeangle)) ;
          z = y*tan(roofangle) ;
          d = sqrt((y*y)/(cos(roofangle)*cos(roofangle)) - 1/(cos(wedgeangle)*cos(wedgeangle))); 
          e_x  = -ElementWidth*x/d;
          s_x  = -Intervaly*x/d    ;
          e_y  = -ElementWidth*y/d  ;
          s_y  = -Intervaly*y/d     ;
          e_zy  = -ElementWidth*(z-x*tan(wedgeangle))/d;
          s_zy  = -Intervaly*(z-x*tan(wedgeangle))/d   ;          
     }
     else
     {   
          e_y = -ElementWidth*cos(roofangle) ;
          s_y = Intervaly*cos(roofangle);
          e_x = 0 ;
          s_x = 0 ;
          e_zy = -ElementWidth*sin(roofangle) ;
          s_zy = -Intervaly*sin(roofangle);
     }
     
     TempElementXLen = ElementLength*cos(wedgeangle) ;
     TempElementYWidth=-ElementWidth*cos(roofangle)   ;
     TempElementHX =   ElementLength*sin(wedgeangle) ;
     TempElementHY =   -ElementWidth*sin( roofangle  );
     TempElementXS =   Intervalx*cos(wedgeangle)     ;
     TempElementYS =   -Intervaly*cos(roofangle)      ;
     TempElementZXS=   Intervalx*sin(wedgeangle)     ;
     TempElementZYS=   -Intervaly*sin(roofangle)      ;
	 
	 if(roofangle1>=0 )
	      yOrg = -wg_sec_axis_reference1 -wg_sec_elem_offset_fir1 -separation -e_y/2        ;
     if(roofangle1<0 ) 
	 	  yOrg = -wg_sec_axis_reference1 + wg_sec_elem_offset_fir1 -separation -e_y/2; 
     xOrg =   wg_pri_axis_reference + wg_pri_elem_offset_fir - TempElementXLen/2 - e_x/2 ;
	 //yOrg =   -wg_sec_axis_reference - wg_sec_elem_offset_fir - e_y/2;
     zOrg =   -h0 +TempElementHX/2 - e_zy/2 ;        	 
     
     glPushMatrix ();
     for(i = 0; i<Column; i++)
     {
           xStart = xOrg + i*TempElementXS;
           zOrgTemp  = zOrg - i*TempElementZXS ;           
           for(j=0; j<Row; j++)
           {
                    yStart = yOrg + j*s_y;                   
                    zStart = zOrgTemp + j*s_zy;
                    glColor4f(0.9,0.9,0.9,0.8);
                    glBegin(GL_QUADS);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);
                    glEnd();
                    glColor4f(0.0,0.0,0.0,1.0);
                    glBegin(GL_LINE_LOOP);
                        glVertex3f(xStart,yStart,zStart);
                        glVertex3f(xStart+e_x,yStart+e_y,zStart+e_zy);
                        glVertex3f(xStart+e_x+TempElementXLen,yStart+e_y,zStart+e_zy-TempElementHX);
                        glVertex3f(xStart+TempElementXLen,yStart,zStart-TempElementHX);     
                    glEnd();
                    xStart = xStart + s_x ;
           }
     }
     glPopMatrix();

}


void DrawCylinderWedgePitchReceiveOD(gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
     if(p->wedge_p->wg_roof_angle>=0)
	        DrawWedge2D_Cylinder_OD(p)     ;
	 else 
	 	    DrawCylinderWedgeInverseOD(p)  ;
	 if(p->wedge_r->wg_roof_angle>0)
	 	    DrawCylinderWedgeReceiverOD(p);
	 else  
	 	    DrawCylinderWedgeReceiverInverseOD(p);
}

void DrawCylinderWedgeReceiverOD(gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
    gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;
    gdouble CylindricalExtDiameter;
	gdouble CylindricalIntDiameter;
	gint i; gdouble angle; gdouble r;
	gdouble zHeight;

		
	gdouble wedgeangle1,roofangle1,wg_heigh_fir1;
    gdouble wg_pri_elem_offset_fir1,wg_sec_elem_offset_fir1;
    gdouble wg_pri_axis_reference1,wg_sec_axis_reference1;
    gdouble width1,length1,height1;
    gdouble separation;
	gdouble ySpace;
	
	CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
	CylindricalIntDiameter = p->specimen->speci_inside_cylindrical  ;
    r = CylindricalExtDiameter/2 ;
    if(wedgeangle==PI/2||roofangle==PI/2)  return ;

	
	wedgeangle=p->wedge_r->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =p->wedge_r->wg_roof_angle*PI/180;  /* 顶角 */
    wg_heigh_fir=p->wedge_r->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_r->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_r->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width =p->wedge_r->wg_width;     /*楔块宽度*/
    length=p->wedge_r->wg_length;    /*楔块长度*/
    height=p->wedge_r->wg_height;/*楔块高度*/
    separation = p->wedge_r->wg_separation ;
	wedgeangle1=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle1 =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
    wg_heigh_fir1=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir1 = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir1 = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference1  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference1  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width1 =p->wedge_p->wg_width;     /*楔块宽度*/
    length1=p->wedge_p->wg_length;    /*楔块长度*/
    height1=p->wedge_p->wg_height;/*楔块高度*/

	
    if(roofangle1>=0)
	        ySpace = -wg_sec_axis_reference1 - 	wg_sec_elem_offset_fir1 - separation + wg_sec_elem_offset_fir ;
    else    
		    ySpace = -wg_sec_axis_reference1  + wg_sec_elem_offset_fir1 - separation +wg_sec_elem_offset_fir;

	
    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    angle = asin(length/CylindricalExtDiameter);
	zHeight = -sqrt(CylindricalExtDiameter*CylindricalExtDiameter - length*length)/2 ;
    glPushMatrix ();
	         
    // button z = 0
    glColor4f(0.0,0.0,0.0,1.0);
	for(i = 0; i< 20; i++)
    {
		   glBegin(GL_LINES);
			   glVertex3f(r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			   glVertex3f(r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
   
			   glVertex3f(-r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			   glVertex3f(-r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
		   glEnd();
    }
     /*绘制楔块*/ 
	glColor4f(0.2f, 0.5f, 0.7f, 0.3);	
	// y = 0
	if(h_xbig>height)
	{
		 glBegin(GL_TRIANGLES);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace,zHeight-height);
			glVertex3f(-length/2,ySpace,zHeight);
			glVertex3f(-length/2,ySpace,zHeight-h_small);
		 glEnd();	
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			}
			glEnd();
			glBegin(GL_TRIANGLES);
			glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace,zHeight-height);
			glVertex3f(length/2,ySpace,zHeight-height);
			glVertex3f(length/2,ySpace,zHeight);
			glEnd();
			
	 }
	 else
	 {
	        glBegin(GL_TRIANGLES);
			glVertex3f(length/2,ySpace,zHeight-h_small-length*tan(wedgeangle));
			glVertex3f(-length/2,ySpace,zHeight);
			glVertex3f(-length/2,ySpace,zHeight-h_small);
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace,zHeight-h_small-length*tan(wedgeangle));
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace,zHeight-h_small-length*tan(wedgeangle));
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),ySpace,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace,-r*cos((i+1)*angle/20));
			}
            glEnd();
	  } 
	  // y = width
      if(h_ybig>height)
      {
          	glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
            glEnd();
			glBegin(GL_TRIANGLES);
			   glVertex3f(-length/2,ySpace-width,zHeight);
			   glVertex3f(-length/2,ySpace-width,zHeight-height);
			   glVertex3f(length/2,ySpace-width,zHeight-height);
			glEnd();
      }
	  else if((h_xbig+h_ybig-h_small)>=height)
	  {
	        glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight-height);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
            glEnd();
			
		    glBegin(GL_TRIANGLES);
			   glVertex3f(-length/2,ySpace-width,zHeight);
			   glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,ySpace-width,zHeight-height);
			   glVertex3f(length/2,ySpace-width,zHeight-height);
			   
        	   glVertex3f(-length/2,ySpace-width,zHeight);
			   glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,ySpace-width,zHeight-height);
			   glVertex3f(-length/2,ySpace-width,zHeight-h_small-width*tan(roofangle));
			glEnd();
			
	  }
	  else
	  {
	      	glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight+h_small-h_xbig-h_ybig);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
			glEnd();
		   
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(length/2,ySpace-width,zHeight+h_small-h_xbig-h_ybig);
			for(i = 0; i<20; i++)
			{
			   glVertex3f(-r*sin(i*angle/20),ySpace-width,-r*cos(i*angle/20));
			   glVertex3f(-r*sin((i+1)*angle/20),ySpace-width,-r*cos((i+1)*angle/20));
			}
            glEnd();
			glBegin(GL_TRIANGLES);
        	   glVertex3f(-length/2,ySpace-width,zHeight);
			   glVertex3f(length/2,ySpace-width,zHeight+h_small-h_xbig-h_ybig);
			   glVertex3f(-length/2,ySpace-width,zHeight-h_small-width*tan(roofangle));
			glEnd();
	  }

	   
     glTranslatef(-length/2,ySpace,zHeight);       
       //    x = 0
       glBegin(GL_POLYGON);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
               glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
               glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
          //  xie  jiao
       glBegin(GL_POLYGON);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                glVertex3f(0,-width,-h_small -width*tan(roofangle));
           }
       glEnd();
         // TOP
       glBegin(GL_POLYGON);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  

          // X = Length
       glBegin(GL_POLYGON);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
         
       
   glColor4f(0.0f, 0.00f, 0.0f, 1);    


       glBegin(GL_LINE_STRIP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_xbig>height)
           {     
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
              glVertex3f(length,0,-height);
           }
           else   
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
           glVertex3f(length,0,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,0);
           glVertex3f(0,0,-h_small);
           if(h_ybig>height)
           {     
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
              glVertex3f(0,-width,-height);
           }
           else   
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
           glVertex3f(0,-width,0);
       glEnd();
       glBegin(GL_LINE_LOOP);
           glVertex3f(0,0,-h_small);           
           if(h_xbig>height)   
              glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
           else   
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));
              if((h_xbig+h_ybig-h_small)>=height)
                 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
              else
                 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
           }
           
           if(h_ybig>height)   
              glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
           else 
           {  
                if((h_xbig+h_ybig-h_small)>=height)
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);   
                glVertex3f(0,-width,-h_small - width*tan(roofangle));
           }
       glEnd(); 
       glBegin(GL_LINE_LOOP);
           if((h_xbig+h_ybig-h_small)>=height)
           {
                 glVertex3f(length, -width, -height );
                 if(h_xbig>height)
                 {  
                    glVertex3f(length,0,-height);                 
                    glVertex3f((height-h_small)/tan(wedgeangle),0,-height);      
                 }
                 else   
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);

                 if(h_ybig>height)
                 {     
                    glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
                    glVertex3f(0,-width,-height);
                 }
                 else   
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
           }
       glEnd();  
       
       glBegin(GL_LINE_LOOP);
           glVertex3f(length,-width,0);
           glVertex3f(length,0,0);
           if(h_xbig>height)
           {
              glVertex3f(length,0,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(length,0,-h_small-length*tan(wedgeangle));      
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
       glEnd();
       
       glBegin(GL_LINE_STRIP);
           
           glVertex3f(0,-width,0);
           if(h_ybig>height)
           {
              glVertex3f(0,-width,-height);
              glVertex3f(length,-width,-height);
           }
           else 
           {
              glVertex3f(0,-width,-h_small-width*tan(roofangle));
              if((h_xbig+h_ybig-h_small)>=height)
              {
                    glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
                    glVertex3f(length,-width,-height);                             
              }                    
              else
                    glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));      
           }
		   glVertex3f(length,-width,0);
       glEnd();
      
   glPopMatrix ();    
}

void DrawCylinderWedgeReceiverInverseOD(gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle,wg_heigh_fir;
    gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
    gdouble wg_pri_axis_reference,wg_sec_axis_reference;
    gdouble width,length,height;
    gdouble h_small ,h_xbig, h_ybig ;
    gdouble xTemp,yTemp;
    gdouble CylindricalExtDiameter;
	gdouble CylindricalIntDiameter;
	gint i; gdouble angle; gdouble r;
	gdouble zHeight;

		
	gdouble wedgeangle1,roofangle1,wg_heigh_fir1;
    gdouble wg_pri_elem_offset_fir1,wg_sec_elem_offset_fir1;
    gdouble wg_pri_axis_reference1,wg_sec_axis_reference1;
    gdouble width1,length1,height1;
    gdouble separation;
	gdouble yOffset;
	
	CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
	CylindricalIntDiameter = p->specimen->speci_inside_cylindrical  ;
    r = CylindricalExtDiameter/2 ;
    if(wedgeangle==PI/2||roofangle==PI/2)  return ;
	
	wedgeangle=p->wedge_r->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle =fabs(p->wedge_r->wg_roof_angle*PI/180);  /* 顶角 */
    wg_heigh_fir=p->wedge_r->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference  = p->wedge_r->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_r->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width =p->wedge_r->wg_width;     /*楔块宽度*/
    length=p->wedge_r->wg_length;    /*楔块长度*/
    height=p->wedge_r->wg_height;/*楔块高度*/
    separation = p->wedge_r->wg_separation ;
	wedgeangle1=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
    roofangle1 =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
    wg_heigh_fir1=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
    wg_pri_elem_offset_fir1 = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
    wg_sec_elem_offset_fir1 = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
    wg_pri_axis_reference1  = p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
    wg_sec_axis_reference1  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
    width1 =p->wedge_p->wg_width;     /*楔块宽度*/
    length1=p->wedge_p->wg_length;    /*楔块长度*/
    height1=p->wedge_p->wg_height;/*楔块高度*/

	
    if(roofangle1>=0)
	        yOffset = -wg_sec_axis_reference1 - 	wg_sec_elem_offset_fir1 - separation - wg_sec_elem_offset_fir + width ;
    else    
		    yOffset = -wg_sec_axis_reference1  + wg_sec_elem_offset_fir1 -separation - wg_sec_elem_offset_fir + width;

    h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
    h_xbig= h_small + length*tan(wedgeangle) ;
    h_ybig= h_small + width*tan(roofangle)   ;
    angle = asin(length/CylindricalExtDiameter);
	zHeight = -sqrt(CylindricalExtDiameter*CylindricalExtDiameter - length*length)/2 ;
    glPushMatrix ();
	glColor4f(0.0,0.0,0.0,1.0);
	 for(i = 0; i< 20; i++)
	 {
			glBegin(GL_LINES);
				glVertex3f(r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
				glVertex3f(r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
	
				glVertex3f(-r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
				glVertex3f(-r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
			glEnd();
	 }
	  /*绘制楔块*/ 
	 glColor4f(0.2f, 0.5f, 0.7f, 0.3);	 
	 // y = -width
	 if(h_xbig>height)
	 {
		  glBegin(GL_TRIANGLES);
			 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			 glVertex3f(-length/2,yOffset-width,zHeight);
			 glVertex3f(-length/2,yOffset-width,zHeight-h_small);
		  glEnd();	 
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
			 }
			 glEnd();
			
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(-r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
			 }
			 glEnd();
			 glBegin(GL_TRIANGLES);
			 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
			 glVertex3f(length/2,yOffset-width,zHeight-height);
			 glVertex3f(length/2,yOffset-width,zHeight);
			 glEnd();
			 
	  }
	  else
	  {
			 glBegin(GL_TRIANGLES);
			 glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
			 glVertex3f(-length/2,yOffset-width,zHeight);
			 glVertex3f(-length/2,yOffset-width,zHeight-h_small);
			 glEnd();
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
			 }
			 glEnd();
			
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(-r*sin(i*angle/20),yOffset-width,-r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,-r*cos((i+1)*angle/20));
			 }
			 glEnd();
	   } 
	   // y = width
	   if(h_ybig>height)
	   {
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			 }
			 glEnd();
			
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(-r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			 }
			 glEnd();
			 glBegin(GL_TRIANGLES);
				glVertex3f(-length/2,yOffset,zHeight);
				glVertex3f(-length/2,yOffset,zHeight-height);
				glVertex3f(length/2,yOffset,zHeight-height);
			 glEnd();
	   }
	   else if((h_xbig+h_ybig-h_small)>=height)
	   {
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			 }
			 glEnd();
			
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight-height);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(-r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			 }
			 glEnd();
			 
			 glBegin(GL_TRIANGLES);
				glVertex3f(-length/2,yOffset,zHeight);
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,yOffset,zHeight-height);
				glVertex3f(length/2,yOffset,zHeight-height);
				
				glVertex3f(-length/2,yOffset,zHeight);
				glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,yOffset,zHeight-height);
				glVertex3f(-length/2,yOffset,zHeight-h_small-width*tan(roofangle));
			 glEnd();
			 
	   }
	   else
	   {
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
				glVertex3f(r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			 }
			 glEnd();
			
			 glBegin(GL_TRIANGLE_FAN);
			 glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
			 for(i = 0; i<20; i++)
			 {
				glVertex3f(-r*sin(i*angle/20),yOffset,-r*cos(i*angle/20));
				glVertex3f(-r*sin((i+1)*angle/20),yOffset,-r*cos((i+1)*angle/20));
			 }
			 glEnd();
			 glBegin(GL_TRIANGLES);
				glVertex3f(-length/2,yOffset,zHeight);
				glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
				glVertex3f(-length/2,yOffset,zHeight-h_small-width*tan(roofangle));
			 glEnd();
	   }
	
	 // 双晶和ROOF角小于0时的楔块平移不一样
	
	 glTranslatef(-length/2, yOffset, zHeight);
	  //glTranslatef(wg_pri_axis_reference,-wg_sec_axis_reference-wg_separation,0.0f);		 
	 /*绘制楔块*/ 
	 glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.	50% Alpha				
		 // button z = 0
		 // front y = - width 
		 //    x = 0
		 glBegin(GL_POLYGON);
			 glVertex3f(0,-width,0);
			 glVertex3f(0,-width,-h_small);
			 if(h_ybig>height)
			 {	   
				 glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				 glVertex3f(0, 0,-height);
			 }
			 else	
				glVertex3f(0,0,-h_small-width*tan(roofangle));
			 glVertex3f(0,0,0);
		 glEnd();
			//	xie  jiao
		 glBegin(GL_POLYGON);
			 glVertex3f(0,-width,-h_small); 		  
			 if(h_xbig>height)	 
				glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
			 else	
			 {
				glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
				if((h_xbig+h_ybig-h_small)>=height)
				   glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
				else
				   glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
			 }
			 if(h_ybig>height)	 
				glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
			 else 
			 {	
				  if((h_xbig+h_ybig-h_small)>=height)
					  glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
				  glVertex3f(0,0,-h_small -width*tan(roofangle));
			 }
		 glEnd();
		   // TOP
		 glBegin(GL_POLYGON);
			 if((h_xbig+h_ybig-h_small)>=height)
			 {
				   glVertex3f(length, 0, -height );
				   if(h_xbig>height)
				   {  
					  glVertex3f(length,-width,-height);				 
					  glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);		
				   }
				   else   
					  glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
	 
				   if(h_ybig>height)
				   {	 
					  glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
					  glVertex3f(0,0,-height);
				   }
				   else   
					  glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
			 }
		 glEnd();  
	 
			// X = Length
		 glBegin(GL_POLYGON);
			 glVertex3f(length,0,0);
			 glVertex3f(length,-width,0);
			 if(h_xbig>height)
			 {
				glVertex3f(length,-width,-height);
				glVertex3f(length, 0	,-height);
			 }
			 else 
			 {
				glVertex3f(length, -width, -h_small-length*tan(wedgeangle));	  
				if((h_xbig+h_ybig-h_small)>=height)
				{
					  glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
					  glVertex3f(length,0 ,-height);							 
				}					 
				else
					  glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));	   
			 }
		 glEnd();
			 // y = 0		 
		 
	 glColor4f(0.0f, 0.00f, 0.0f, 1);	 
	 // button z = 0
	 // front y = - width 
	 glBegin(GL_LINE_STRIP);
		 glVertex3f(0,-width,0);
		 glVertex3f(0,-width,-h_small);
		 if(h_xbig>height)
		 {	   
			glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
			glVertex3f(length,-width,-height);
		 }
		 else	
			glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
		 glVertex3f(length,-width,0);
	 glEnd();
	 //    x = 0
	 glBegin(GL_LINE_LOOP);
		 glVertex3f(0,-width,0);
		 glVertex3f(0,-width,-h_small);
		 if(h_ybig>height)
		 {	   
			 glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
			 glVertex3f(0, 0,-height);
		 }
		 else	
			glVertex3f(0,0,-h_small-width*tan(roofangle));
		 glVertex3f(0,0,0);
	 glEnd();
		//	xie  jiao
	 glBegin(GL_LINE_LOOP);
		 glVertex3f(0,-width,-h_small); 		  
		 if(h_xbig>height)	 
			glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
		 else	
		 {
			glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
			if((h_xbig+h_ybig-h_small)>=height)
			   glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
			else
			   glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
		 }
		 if(h_ybig>height)	 
			glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
		 else 
		 {	
			  if((h_xbig+h_ybig-h_small)>=height)
				  glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
			  glVertex3f(0,0,-h_small -width*tan(roofangle));
		 }
	 glEnd();
	   // TOP
	 glBegin(GL_LINE_LOOP);
		 if((h_xbig+h_ybig-h_small)>=height)
		 {
			   glVertex3f(length, 0, -height );
			   if(h_xbig>height)
			   {  
				  glVertex3f(length,-width,-height);				 
				  glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);		
			   }
			   else   
				  glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
	 
			   if(h_ybig>height)
			   {	 
				  glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				  glVertex3f(0,0,-height);
			   }
			   else   
				  glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
		 }
	 glEnd();  
	 
		// X = Length
	 glBegin(GL_LINE_LOOP);
		 glVertex3f(length,0,0);
		 glVertex3f(length,-width,0);
		 if(h_xbig>height)
		 {
			glVertex3f(length,-width,-height);
			glVertex3f(length, 0	,-height);
		 }
		 else 
		 {
			glVertex3f(length, -width, -h_small-length*tan(wedgeangle));	  
			if((h_xbig+h_ybig-h_small)>=height)
			{
				  glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
				  glVertex3f(length,0 ,-height);							 
			}					 
			else
				  glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));	   
		 }
	 glEnd();
		 // y = 0
	 glBegin(GL_LINE_STRIP);
		 
		 glVertex3f(0, 0,0);
		 if(h_ybig>=height)
		 {
			glVertex3f(0,0,-height);
			glVertex3f(length, 0,-height);
		 }
		 else 
		 {
			glVertex3f(0, 0,-h_small-width*tan(roofangle));
			if((h_xbig+h_ybig-h_small)>=height)
			{
				  glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
				  glVertex3f(length,0,-height); 							
			}					 
			else
				  glVertex3f(length,0,-(h_xbig+h_ybig-h_small));	  
		 }
		 glVertex3f(length,0,0);
	 glEnd();  
	 
		
	 glPopMatrix (); 
}



void DrawCylinderWedgePitchReceiveID(gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
     if(p->wedge_p->wg_roof_angle>=0)
	          DrawWedge2D_Cylinder_ID(p) ;
	 else 
	 	      DrawCylinderWedgeInverseID(p) ;
	 if(p->wedge_r->wg_roof_angle>0)
	 	      DrawCylinderWedgeReceiverID(p);
	 else 
	 	      DrawCylinderWedgeReceiverInverseID(p);
	
}


void DrawCylinderWedgeReceiverID(gpointer data)
{
		DRAW_UI_P p = (DRAW_UI_P)(data);
			
		gdouble wedgeangle,roofangle,wg_heigh_fir;
		gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
		gdouble wg_pri_axis_reference,wg_sec_axis_reference;

	    gdouble wedgeangle1,roofangle1;
		gdouble wg_pri_elem_offset_fir1,wg_sec_elem_offset_fir1;
		gdouble wg_pri_axis_reference1,wg_sec_axis_reference1;

		gdouble width,length,height;
		gdouble h_small ,h_xbig, h_ybig ;
		gdouble xTemp,yTemp;
		gdouble CylindricalExtDiameter;
		gdouble CylindricalIntDiameter;
		gint i; gdouble r;gdouble angle; gdouble zHeight;
		gdouble ySpace;
		gdouble separation ;
        separation = p->wedge_r->wg_separation;
		roofangle1 =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
		wg_sec_elem_offset_fir1 = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
		wg_sec_axis_reference1  = p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
		
		wedgeangle=p->wedge_r->wg_wedge_angle*PI/180 ; /* 楔块角 */
		roofangle =p->wedge_r->wg_roof_angle*PI/180;  /* 顶角 */
		wg_heigh_fir=p->wedge_r->wg_heigh_fir;	/*第一阵元高度*/
		wg_pri_elem_offset_fir = p->wedge_r->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
		wg_sec_elem_offset_fir = p->wedge_r->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
		wg_pri_axis_reference  = p->wedge_r->wg_pri_axis_reference; /*主轴楔块参考位置*/
		wg_sec_axis_reference  = p->wedge_r->wg_sec_axis_reference; /*次轴楔块参考位置*/
		width =p->wedge_r->wg_width;	 /*楔块宽度*/
		length=p->wedge_r->wg_length;	 /*楔块长度*/
		height=p->wedge_r->wg_height;/*楔块高度*/
		CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
		CylindricalIntDiameter = p->specimen->speci_inside_cylindrical	;
		r = CylindricalIntDiameter/2 ;	
		angle = asin(length/CylindricalIntDiameter);
		zHeight = sqrt(CylindricalIntDiameter*CylindricalIntDiameter - length*length)/2 ;
		if(wedgeangle==PI/2||roofangle==PI/2)  return ;
		h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
		
		h_xbig= h_small + length*tan(wedgeangle) ;
		h_ybig= h_small + width*tan(roofangle)	 ;

			
        if(roofangle1>=0)
	        ySpace = -wg_sec_axis_reference1 - 	wg_sec_elem_offset_fir1 - separation + wg_sec_elem_offset_fir ;
        else    
		    ySpace = -wg_sec_axis_reference1  + wg_sec_elem_offset_fir1 - separation +wg_sec_elem_offset_fir;
		
		glPushMatrix ();
		glColor4f(0.0,0.0,0.0,1.0);
		glBegin(GL_LINES);
		   for(i=0; i<20; i++)
		   {
				   glVertex3f(r*sin(i*angle/20),ySpace,r*cos(i*angle/20));
				   glVertex3f(r*sin((i+1)*angle/20),ySpace,r*cos((i+1)*angle/20));
				   glVertex3f(r*sin(i*angle/20),ySpace-width,r*cos(i*angle/20));
				   glVertex3f(r*sin((i+1)*angle/20),ySpace-width,r*cos((i+1)*angle/20));
	   
				   glVertex3f(-r*sin(i*angle/20),ySpace,r*cos(i*angle/20));
				   glVertex3f(-r*sin((i+1)*angle/20),ySpace ,r*cos((i+1)*angle/20));
				   glVertex3f(-r*sin(i*angle/20),ySpace -width,r*cos(i*angle/20));
				   glVertex3f(-r*sin((i+1)*angle/20),ySpace -width,r*cos((i+1)*angle/20));
		   } 
		glEnd();
	
		glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha		 
		// y = 0
		if(h_xbig>height)
		{
			 glBegin(GL_TRIANGLES);
				glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace ,zHeight-height);
				glVertex3f(-length/2,ySpace ,zHeight);
				glVertex3f(-length/2,ySpace ,zHeight-h_small);
			 glEnd();	
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace ,zHeight-height);
				for(i = 0; i<20; i++)
				{
				   glVertex3f(r*sin(i*angle/20),ySpace ,r*cos(i*angle/20));
				   glVertex3f(r*sin((i+1)*angle/20),ySpace ,r*cos((i+1)*angle/20));
				}
				glEnd();
			   
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace ,zHeight-height);
				for(i = 0; i<20; i++)
				{
				   glVertex3f(-r*sin(i*angle/20),ySpace ,r*cos(i*angle/20));
				   glVertex3f(-r*sin((i+1)*angle/20),ySpace ,r*cos((i+1)*angle/20));
				}
				glEnd();
				glBegin(GL_TRIANGLES);
				glVertex3f((height-h_small)/tan(wedgeangle)-length/2,ySpace ,zHeight-height);
				glVertex3f(length/2,ySpace ,zHeight-height);
				glVertex3f(length/2,ySpace ,zHeight);
				glEnd();
				
		 }
		 else
		 {
				glBegin(GL_TRIANGLES);
				glVertex3f(length/2,ySpace ,zHeight-h_small-length*tan(wedgeangle));
				glVertex3f(-length/2,ySpace ,zHeight);
				glVertex3f(-length/2,ySpace ,zHeight-h_small);
				glEnd();
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(length/2,ySpace ,zHeight-h_small-length*tan(wedgeangle));
				for(i = 0; i<20; i++)
				{
				   glVertex3f(r*sin(i*angle/20),ySpace ,r*cos(i*angle/20));
				   glVertex3f(r*sin((i+1)*angle/20),ySpace ,r*cos((i+1)*angle/20));
				}
				glEnd();
			   
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(length/2,ySpace ,zHeight-h_small-length*tan(wedgeangle));
				for(i = 0; i<20; i++)
				{
				   glVertex3f(-r*sin(i*angle/20),ySpace ,r*cos(i*angle/20));
				   glVertex3f(-r*sin((i+1)*angle/20),ySpace ,r*cos((i+1)*angle/20));
				}
				glEnd();
		  } 
		  // y = width
		  if(h_ybig>height)
		  {
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(length/2,ySpace -width,zHeight-height);
				for(i = 0; i<20; i++)
				{
				   glVertex3f(r*sin(i*angle/20),ySpace -width,r*cos(i*angle/20));
				   glVertex3f(r*sin((i+1)*angle/20),ySpace -width,r*cos((i+1)*angle/20));
				}
				glEnd();
			   
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(length/2,ySpace -width,zHeight-height);
				for(i = 0; i<20; i++)
				{
				   glVertex3f(-r*sin(i*angle/20),ySpace -width,r*cos(i*angle/20));
				   glVertex3f(-r*sin((i+1)*angle/20),ySpace -width,r*cos((i+1)*angle/20));
				}
				glEnd();
				glBegin(GL_TRIANGLES);
				   glVertex3f(-length/2,ySpace -width,zHeight);
				   glVertex3f(-length/2,ySpace -width,zHeight-height);
				   glVertex3f(length/2,ySpace -width,zHeight-height);
				glEnd();
		  }
		  else if((h_xbig+h_ybig-h_small)>=height)
		  {
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(length/2,ySpace -width,zHeight-height);
				for(i = 0; i<20; i++)
				{
				   glVertex3f(r*sin(i*angle/20),ySpace -width,r*cos(i*angle/20));
				   glVertex3f(r*sin((i+1)*angle/20),ySpace -width,r*cos((i+1)*angle/20));
				}
				glEnd();
			   
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(length/2,ySpace -width,zHeight-height);
				for(i = 0; i<20; i++)
				{
				   glVertex3f(-r*sin(i*angle/20),ySpace -width,r*cos(i*angle/20));
				   glVertex3f(-r*sin((i+1)*angle/20),ySpace -width,r*cos((i+1)*angle/20));
				}
				glEnd();
				
				glBegin(GL_TRIANGLES);
				   glVertex3f(-length/2,ySpace -width,zHeight);
				   glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,ySpace -width,zHeight-height);
				   glVertex3f(length/2,ySpace -width,zHeight-height);
				   
				   glVertex3f(-length/2,ySpace -width,zHeight);
				   glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,ySpace -width,zHeight-height);
				   glVertex3f(-length/2,ySpace -width,zHeight-h_small-width*tan(roofangle));
				glEnd();
				
		  }
		  else
		  {
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(length/2,ySpace -width,zHeight+h_small-h_xbig-h_ybig);
				for(i = 0; i<20; i++)
				{
				   glVertex3f(r*sin(i*angle/20),ySpace -width,r*cos(i*angle/20));
				   glVertex3f(r*sin((i+1)*angle/20),ySpace -width,r*cos((i+1)*angle/20));
				}
				glEnd();
			   
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(length/2,ySpace -width,zHeight+h_small-h_xbig-h_ybig);
				for(i = 0; i<20; i++)
				{
				   glVertex3f(-r*sin(i*angle/20),ySpace -width,r*cos(i*angle/20));
				   glVertex3f(-r*sin((i+1)*angle/20),ySpace -width,r*cos((i+1)*angle/20));
				}
				glEnd();
				glBegin(GL_TRIANGLES);
				   glVertex3f(-length/2,ySpace -width,zHeight);
				   glVertex3f(length/2,ySpace -width,zHeight+h_small-h_xbig-h_ybig);
				   glVertex3f(-length/2,ySpace -width,zHeight-h_small-width*tan(roofangle));
				glEnd();
		  }
	
		glTranslatef(-length/2,ySpace ,sqrt(CylindricalIntDiameter*CylindricalIntDiameter - length*length)/2);		
		/*绘制楔块*/
		//	  x = 0
		   glBegin(GL_POLYGON);
			   glVertex3f(0,0,0);
			   glVertex3f(0,0,-h_small);
			   if(h_ybig>height)
			   {	 
				   glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
				   glVertex3f(0,-width,-height);
			   }
			   else   
				  glVertex3f(0,-width,-h_small-width*tan(roofangle));
			   glVertex3f(0,-width,0);
		   glEnd();
			  //  xie  jiao
		   glBegin(GL_POLYGON);
			   glVertex3f(0,0,-h_small);		   
			   if(h_xbig>height)   
				  glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
			   else   
			   {
				  glVertex3f(length,0,-h_small-length*tan(wedgeangle));
				  if((h_xbig+h_ybig-h_small)>=height)
					 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
				  else
					 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
			   }
			   
			   if(h_ybig>height)   
				  glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
			   else 
			   {  
					if((h_xbig+h_ybig-h_small)>=height)
						glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
					glVertex3f(0,-width,-h_small -width*tan(roofangle));
			   }
		   glEnd();
		   // TOP
		   glBegin(GL_POLYGON);
			   if((h_xbig+h_ybig-h_small)>=height)
			   {
					 glVertex3f(length, -width, -height );
					 if(h_xbig>height)
					 {	
						glVertex3f(length,0,-height);				  
						glVertex3f((height-h_small)/tan(wedgeangle),0,-height); 	 
					 }
					 else	
						glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
	
					 if(h_ybig>height)
					 {	   
						glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
						glVertex3f(0,-width,-height);
					 }
					 else	
						glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
			   }
		   glEnd();  
		   // X = Length
		   glBegin(GL_POLYGON);
			   glVertex3f(length,-width,0);
			   glVertex3f(length,0,0);
			   if(h_xbig>height)
			   {
				  glVertex3f(length,0,-height);
				  glVertex3f(length,-width,-height);
			   }
			   else 
			   {
				  glVertex3f(length,0,-h_small-length*tan(wedgeangle)); 	 
				  if((h_xbig+h_ybig-h_small)>=height)
				  {
						glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
						glVertex3f(length,-width,-height);							   
				  } 				   
				  else
						glVertex3f(length,-width,-(h_xbig+h_ybig-h_small)); 	 
			   }
		   glEnd(); 	   
	   glColor4f(0.0f, 0.00f, 0.0f, 1);    
	
		   glBegin(GL_LINE_STRIP);
			   glVertex3f(0,0,0);
			   glVertex3f(0,0,-h_small);
			   if(h_xbig>height)
			   {	 
				  glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
				  glVertex3f(length,0,-height);
			   }
			   else   
				  glVertex3f(length,0,-h_small-length*tan(wedgeangle));
			   glVertex3f(length,0,0);
		   glEnd();
		   glBegin(GL_LINE_LOOP);
			   glVertex3f(0,0,0);
			   glVertex3f(0,0,-h_small);
			   if(h_ybig>height)
			   {	 
				  glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
				  glVertex3f(0,-width,-height);
			   }
			   else   
				  glVertex3f(0,-width,-h_small-width*tan(roofangle));
			   glVertex3f(0,-width,0);
		   glEnd();
		   glBegin(GL_LINE_LOOP);
			   glVertex3f(0,0,-h_small);		   
			   if(h_xbig>height)   
				  glVertex3f((height-h_small)/tan(wedgeangle),0,-height);
			   else   
			   {
				  glVertex3f(length,0,-h_small-length*tan(wedgeangle));
				  if((h_xbig+h_ybig-h_small)>=height)
					 glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
				  else
					 glVertex3f(length,-width,-(h_xbig+h_ybig-h_small));
			   }
			   
			   if(h_ybig>height)   
				  glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
			   else 
			   {  
					if((h_xbig+h_ybig-h_small)>=height)
						glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);	
					glVertex3f(0,-width,-h_small - width*tan(roofangle));
			   }
		   glEnd(); 
		   glBegin(GL_LINE_LOOP);
			   if((h_xbig+h_ybig-h_small)>=height)
			   {
					 glVertex3f(length, -width, -height );
					 if(h_xbig>height)
					 {	
						glVertex3f(length,0,-height);				  
						glVertex3f((height-h_small)/tan(wedgeangle),0,-height); 	 
					 }
					 else	
						glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
	
					 if(h_ybig>height)
					 {	   
						glVertex3f(0,-(height-h_small)/tan(roofangle),-height);
						glVertex3f(0,-width,-height);
					 }
					 else	
						glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
			   }
		   glEnd();  
		   
		   glBegin(GL_LINE_LOOP);
			   glVertex3f(length,-width,0);
			   glVertex3f(length,0,0);
			   if(h_xbig>height)
			   {
				  glVertex3f(length,0,-height);
				  glVertex3f(length,-width,-height);
			   }
			   else 
			   {
				  glVertex3f(length,0,-h_small-length*tan(wedgeangle)); 	 
				  if((h_xbig+h_ybig-h_small)>=height)
				  {
						glVertex3f(length,-(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
						glVertex3f(length,-width,-height);							   
				  } 				   
				  else
						glVertex3f(length,-width,-(h_xbig+h_ybig-h_small)); 	 
			   }
		   glEnd();
		   
		   glBegin(GL_LINE_STRIP);
		 
			   glVertex3f(0,-width,0);
			   if(h_ybig>height)
			   {
				  glVertex3f(0,-width,-height);
				  glVertex3f(length,-width,-height);
			   }
			   else 
			   {
				  glVertex3f(0,-width,-h_small-width*tan(roofangle));
				  if((h_xbig+h_ybig-h_small)>=height)
				  {
						glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),-width,-height);
						glVertex3f(length,-width,-height);							   
				  } 				   
				  else
						glVertex3f(length,-width,-(h_xbig+h_ybig-h_small)); 	 
			   }
			   glVertex3f(length,-width,0);
		   glEnd();
		  
	   glPopMatrix ();	 
}


void DrawCylinderWedgeReceiverInverseID(gpointer data) 
{	
		DRAW_UI_P p = (DRAW_UI_P)(data);
			 
		 gdouble wedgeangle,roofangle,wg_heigh_fir;
		 gdouble wg_pri_elem_offset_fir,wg_sec_elem_offset_fir;
		 gdouble wg_pri_axis_reference,wg_sec_axis_reference;
		 gdouble roofangle1;
		 gdouble wg_sec_elem_offset_fir1;
		 gdouble wg_sec_axis_reference1;
		 gdouble width,length,height;
		 gdouble h_small ,h_xbig, h_ybig ;
		 gdouble xTemp,yTemp;
		 gdouble CylindricalExtDiameter;
		 gdouble CylindricalIntDiameter;
		 gint i; gdouble angle; gdouble r;
		 gdouble zHeight;
		 gdouble separation;
		 gdouble yOffset;
		 roofangle1 = p->wedge_p->wg_roof_angle ;
		 wg_sec_elem_offset_fir1 = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
		 wg_sec_axis_reference1	= p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
		 wedgeangle=p->wedge_p->wg_wedge_angle*PI/180 ; /* 楔块角 */
		 roofangle =fabs(p->wedge_p->wg_roof_angle*PI/180);  /* 顶角 */
		 wg_heigh_fir=p->wedge_p->wg_heigh_fir;  /*第一阵元高度*/
		 wg_pri_elem_offset_fir = p->wedge_p->wg_pri_elem_offset_fir;/*第一主轴阵元偏移*/
		 wg_sec_elem_offset_fir = p->wedge_p->wg_sec_elem_offset_fir;/*第一次轴阵元偏移*/
		 wg_pri_axis_reference	= p->wedge_p->wg_pri_axis_reference; /*主轴楔块参考位置*/
		 wg_sec_axis_reference	= p->wedge_p->wg_sec_axis_reference; /*次轴楔块参考位置*/
		 separation			= p->wedge_r->wg_separation ;
		 width =p->wedge_p->wg_width;	  /*楔块宽度*/
		 length=p->wedge_p->wg_length;	  /*楔块长度*/
		 height=p->wedge_p->wg_height;/*楔块高度*/
		 CylindricalExtDiameter = p->specimen->speci_outside_cylindrical ;
		 CylindricalIntDiameter = p->specimen->speci_inside_cylindrical  ;
		 r = CylindricalIntDiameter/2 ;
		 if(wedgeangle==PI/2||roofangle==PI/2)	return ;
		 h_small = wg_heigh_fir - wg_pri_elem_offset_fir*tan(wedgeangle) - wg_sec_elem_offset_fir*tan(roofangle);
		 h_xbig= h_small + length*tan(wedgeangle) ;
		 h_ybig= h_small + width*tan(roofangle)   ;
		 angle = asin(length/CylindricalIntDiameter);
		 zHeight = sqrt(CylindricalIntDiameter*CylindricalIntDiameter - length*length)/2 ;


		 if(roofangle1>=0)
	        yOffset = -wg_sec_axis_reference1 - 	wg_sec_elem_offset_fir1 - separation - wg_sec_elem_offset_fir + width ;
         else     
		    yOffset = -wg_sec_axis_reference1  + wg_sec_elem_offset_fir1 -separation - wg_sec_elem_offset_fir + width;
	
		 glPushMatrix ();
		 
		 glColor4f(0.0,0.0,0.0,1.0);
		 for(i = 0; i< 20; i++)
		 {
				glBegin(GL_LINES);
					glVertex3f(r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
					glVertex3f(r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
					glVertex3f(r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
					glVertex3f(r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
		
					glVertex3f(-r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
					glVertex3f(-r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
					glVertex3f(-r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
					glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
				glEnd();
		 }
		  /*绘制楔块*/ 
		 glColor4f(0.2f, 0.5f, 0.7f, 0.3);	 
		 // y = -width
		 if(h_xbig>height)
		 {
			  glBegin(GL_TRIANGLES);
				 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
				 glVertex3f(-length/2,yOffset-width,zHeight);
				 glVertex3f(-length/2,yOffset-width,zHeight-h_small);
			  glEnd();	 
				 glBegin(GL_TRIANGLE_FAN);
				 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
				 for(i = 0; i<20; i++)
				 {
					glVertex3f(r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
					glVertex3f(r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
				 }
				 glEnd();
				
				 glBegin(GL_TRIANGLE_FAN);
				 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
				 for(i = 0; i<20; i++)
				 {
					glVertex3f(-r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
					glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
				 }
				 glEnd();
				 glBegin(GL_TRIANGLES);
				 glVertex3f((height-h_small)/tan(wedgeangle)-length/2,yOffset-width,zHeight-height);
				 glVertex3f(length/2,yOffset-width,zHeight-height);
				 glVertex3f(length/2,yOffset-width,zHeight);
				 glEnd();
				 
		  }
		  else
		  {
				 glBegin(GL_TRIANGLES);
				 glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
				 glVertex3f(-length/2,yOffset-width,zHeight);
				 glVertex3f(-length/2,yOffset-width,zHeight-h_small);
				 glEnd();
				 glBegin(GL_TRIANGLE_FAN);
				 glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
				 for(i = 0; i<20; i++)
				 {
					glVertex3f(r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
					glVertex3f(r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
				 }
				 glEnd();
				
				 glBegin(GL_TRIANGLE_FAN);
				 glVertex3f(length/2,yOffset-width,zHeight-h_small-length*tan(wedgeangle));
				 for(i = 0; i<20; i++)
				 {
					glVertex3f(-r*sin(i*angle/20),yOffset-width,r*cos(i*angle/20));
					glVertex3f(-r*sin((i+1)*angle/20),yOffset-width,r*cos((i+1)*angle/20));
				 }
				 glEnd();
		   } 
		   // y = width
		   if(h_ybig>height)
		   {
				 glBegin(GL_TRIANGLE_FAN);
				 glVertex3f(length/2,yOffset,zHeight-height);
				 for(i = 0; i<20; i++)
				 {
					glVertex3f(r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
					glVertex3f(r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
				 }
				 glEnd();
				
				 glBegin(GL_TRIANGLE_FAN);
				 glVertex3f(length/2,yOffset,zHeight-height);
				 for(i = 0; i<20; i++)
				 {
					glVertex3f(-r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
					glVertex3f(-r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
				 }
				 glEnd();
				 glBegin(GL_TRIANGLES);
					glVertex3f(-length/2,yOffset,zHeight);
					glVertex3f(-length/2,yOffset,zHeight-height);
					glVertex3f(length/2,yOffset,zHeight-height);
				 glEnd();
		   }
		   else if((h_xbig+h_ybig-h_small)>=height)
		   {
				 glBegin(GL_TRIANGLE_FAN);
				 glVertex3f(length/2,yOffset,zHeight-height);
				 for(i = 0; i<20; i++)
				 {
					glVertex3f(r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
					glVertex3f(r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
				 }
				 glEnd();
				
				 glBegin(GL_TRIANGLE_FAN);
				 glVertex3f(length/2,yOffset,zHeight-height);
				 for(i = 0; i<20; i++)
				 {
					glVertex3f(-r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
					glVertex3f(-r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
				 }
				 glEnd();
				 
				 glBegin(GL_TRIANGLES);
					glVertex3f(-length/2,yOffset,zHeight);
					glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,yOffset,zHeight-height);
					glVertex3f(length/2,yOffset,zHeight-height);
					
					glVertex3f(-length/2,yOffset,zHeight);
					glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle)-length/2,yOffset,zHeight-height);
					glVertex3f(-length/2,yOffset,zHeight-h_small-width*tan(roofangle));
				 glEnd();
				 
		   }
		   else
		   {
				 glBegin(GL_TRIANGLE_FAN);
				 glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
				 for(i = 0; i<20; i++)
				 {
					glVertex3f(r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
					glVertex3f(r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
				 }
				 glEnd();
				
				 glBegin(GL_TRIANGLE_FAN);
				 glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
				 for(i = 0; i<20; i++)
				 {
					glVertex3f(-r*sin(i*angle/20),yOffset,r*cos(i*angle/20));
					glVertex3f(-r*sin((i+1)*angle/20),yOffset,r*cos((i+1)*angle/20));
				 }
				 glEnd();
				 glBegin(GL_TRIANGLES);
					glVertex3f(-length/2,yOffset,zHeight);
					glVertex3f(length/2,yOffset,zHeight+h_small-h_xbig-h_ybig);
					glVertex3f(-length/2,yOffset,zHeight-h_small-width*tan(roofangle));
				 glEnd();
		   }
	
		glTranslatef(-length/2,  yOffset, zHeight);
		 //glTranslatef(wg_pri_axis_reference,-wg_sec_axis_reference-wg_separation,0.0f);		
		/*绘制楔块*/ 
		glColor4f(0.2f, 0.5f, 0.7f, 0.3); // Full Brightness.  50% Alpha			   
			// button z = 0
			// front y = - width 
			//	  x = 0
			glBegin(GL_POLYGON);
				glVertex3f(0,-width,0);
				glVertex3f(0,-width,-h_small);
				if(h_ybig>height)
				{	  
					glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
					glVertex3f(0, 0,-height);
				}
				else   
				   glVertex3f(0,0,-h_small-width*tan(roofangle));
				glVertex3f(0,0,0);
			glEnd();
			   //  xie	jiao
			glBegin(GL_POLYGON);
				glVertex3f(0,-width,-h_small);			 
				if(h_xbig>height)	
				   glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
				else   
				{
				   glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
				   if((h_xbig+h_ybig-h_small)>=height)
					  glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
				   else
					  glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
				}
				if(h_ybig>height)	
				   glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				else 
				{  
					 if((h_xbig+h_ybig-h_small)>=height)
						 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
					 glVertex3f(0,0,-h_small -width*tan(roofangle));
				}
			glEnd();
			  // TOP
			glBegin(GL_POLYGON);
				if((h_xbig+h_ybig-h_small)>=height)
				{
					  glVertex3f(length, 0, -height );
					  if(h_xbig>height)
					  {  
						 glVertex3f(length,-width,-height); 				
						 glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);	   
					  }
					  else	 
						 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
		
					  if(h_ybig>height)
					  { 	
						 glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
						 glVertex3f(0,0,-height);
					  }
					  else	 
						 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
				}
			glEnd();  
		
			   // X = Length
			glBegin(GL_POLYGON);
				glVertex3f(length,0,0);
				glVertex3f(length,-width,0);
				if(h_xbig>height)
				{
				   glVertex3f(length,-width,-height);
				   glVertex3f(length, 0    ,-height);
				}
				else 
				{
				   glVertex3f(length, -width, -h_small-length*tan(wedgeangle)); 	 
				   if((h_xbig+h_ybig-h_small)>=height)
				   {
						 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
						 glVertex3f(length,0 ,-height); 							
				   }					
				   else
						 glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));	  
				}
			glEnd();
				// y = 0
		glColor4f(0.0f, 0.00f, 0.0f, 1);	
		// button z = 0
	
		// front y = - width 
		glBegin(GL_LINE_STRIP);
			glVertex3f(0,-width,0);
			glVertex3f(0,-width,-h_small);
			if(h_xbig>height)
			{	  
			   glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
			   glVertex3f(length,-width,-height);
			}
			else   
			   glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
			glVertex3f(length,-width,0);
		glEnd();
		//	  x = 0
		glBegin(GL_LINE_LOOP);
			glVertex3f(0,-width,0);
			glVertex3f(0,-width,-h_small);
			if(h_ybig>height)
			{	  
				glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
				glVertex3f(0, 0,-height);
			}
			else   
			   glVertex3f(0,0,-h_small-width*tan(roofangle));
			glVertex3f(0,0,0);
		glEnd();
		   //  xie	jiao
		glBegin(GL_LINE_LOOP);
			glVertex3f(0,-width,-h_small);			 
			if(h_xbig>height)	
			   glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);
			else   
			{
			   glVertex3f(length,-width,-h_small-length*tan(wedgeangle));
			   if((h_xbig+h_ybig-h_small)>=height)
				  glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height) ;
			   else
				  glVertex3f(length,0,-(h_xbig+h_ybig-h_small));
			}
			if(h_ybig>height)	
			   glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
			else 
			{  
				 if((h_xbig+h_ybig-h_small)>=height)
					 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle), 0 ,-height);
				 glVertex3f(0,0,-h_small -width*tan(roofangle));
			}
		glEnd();
		  // TOP
		glBegin(GL_LINE_LOOP);
			if((h_xbig+h_ybig-h_small)>=height)
			{
				  glVertex3f(length, 0, -height );
				  if(h_xbig>height)
				  {  
					 glVertex3f(length,-width,-height); 				
					 glVertex3f((height-h_small)/tan(wedgeangle),-width,-height);	   
				  }
				  else	 
					 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
		
				  if(h_ybig>height)
				  { 	
					 glVertex3f(0,-width+(height-h_small)/tan(roofangle),-height);
					 glVertex3f(0,0,-height);
				  }
				  else	 
					 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
			}
		glEnd();  
		
		   // X = Length
		glBegin(GL_LINE_LOOP);
			glVertex3f(length,0,0);
			glVertex3f(length,-width,0);
			if(h_xbig>height)
			{
			   glVertex3f(length,-width,-height);
			   glVertex3f(length, 0    ,-height);
			}
			else 
			{
			   glVertex3f(length, -width, -h_small-length*tan(wedgeangle)); 	 
			   if((h_xbig+h_ybig-h_small)>=height)
			   {
					 glVertex3f(length,-width+(height-h_small-length*tan(wedgeangle))/tan(roofangle),-height);
					 glVertex3f(length,0 ,-height); 							
			   }					
			   else
					 glVertex3f(length, 0,-(h_xbig+h_ybig-h_small));	  
			}
		glEnd();
			// y = 0
		glBegin(GL_LINE_STRIP);
			glVertex3f(0, 0,0);
			if(h_ybig>=height)
			{
			   glVertex3f(0,0,-height);
			   glVertex3f(length, 0,-height);
			}
			else 
			{
			   glVertex3f(0, 0,-h_small-width*tan(roofangle));
			   if((h_xbig+h_ybig-h_small)>=height)
			   {
					 glVertex3f((height-h_small-width*tan(roofangle))/tan(wedgeangle),0,-height);
					 glVertex3f(length,0,-height);							   
			   }					
			   else
					 glVertex3f(length,0,-(h_xbig+h_ybig-h_small)); 	 
			}
			glVertex3f(length,0,0);
		glEnd();  
	
		glPopMatrix (); 
}

void DrawElementCylinderPitchReceiveID(gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
     DrawElement2DCylinderID(p);  
     DrawElementCylinderReceiverID(p);
}
 


void DrawElementCylinderPitchReceiveOD(gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
     DrawElement2DCylinderOD(p);  
     DrawElementCylinderReceiverOD(p);
}


void DrawFocusResult(gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P) data ;
//     gint Row     = p->probe_p->ele_num_sec ;                         // element x direction numble
//     gint Column  = p->probe_p->ele_num_pri ;                         // element y direction numble
//     if(p->probe_p->D1_D2 == 0) Row= 1;

	 int PriElementStart = p->element_sel->primary_axis_s -1  ;
     int PriElementNum   = p->probe_p->ele_num_pri            ;
     int SecElementStart = p->element_sel->seconary_axis_s -1 ;
	 int SecElementNum   = p->probe_p->ele_num_sec            ;
	 int PriElementSelect= p->element_sel->pri_axis_ape       ;
	 int SecElementSelect= p->element_sel->sec_axis_ape       ;
     int PriElementStop  = PriElementStart +  PriElementSelect;
	 int SecElementStop  = SecElementStart +  SecElementSelect;
     int PriElementResolution = p->element_sel->primary_axis_r;
	 if(p->beam_angle->beam_type == 1)
	 {
		   PriElementStart = p->element_sel->primary_axis_s - 1 + PriElementResolution * p->final_num ;
		   PriElementStop	 = PriElementStart +  PriElementSelect;
	 }

	 if(p->probe_p->D1_D2 == 0) {SecElementNum = 1;  SecElementStart = 0; SecElementStop = 1;}
     if(!p->DrawResult) return ;/* DrawResult==0时，返回;  DrawResult==1时，绘制聚焦法则结果 */

	 if(p->probe_p->D1_D2 == 0 && p->specimen->flat_cylindrical==1 && p->probe_p->Pitch_Catch == 1)
	 {
            p->DrawResult = 0;
            return ;
     }
	 
     int i, j;
     int tmp;
	 int elementN ;
	 gboolean ColorSelection;
	 gint kkk = ((p->beam_angle->beam_skew_angle_stop) - (p->beam_angle->beam_skew_angle_start))/(p->beam_angle->beam_skew_angle_resolution) + 1 ;
	 ColorSelection = PointInWedgeBottonRect(p);
     gint init = p->element_sel->primary_axis_s - 1;
	 tmp = p->element_sel->pri_axis_ape * p->element_sel->sec_axis_ape ;
     switch(p->probe_p->D1_D2)
     {
         case 0:            
              elementN = p->probe_p->ele_num_pri ;
              break;
         case 1:
              elementN = p->probe_p->ele_num_pri * p->probe_p->ele_num_sec ;
              break;                       
     }
     if( (tmp + init ) > elementN )
         return;

     glPushMatrix();
     
     
        glBegin(GL_LINES);
		    if(!ColorSelection)
				glColor3f(1.0,0.0,0.0);
			else
				glColor3f(0.0,0.0,1.0);

		     for(i=PriElementStart; i< PriElementStop ; i++)
		     {
		         for(j = SecElementStart; j< SecElementStop; j++)
		         {
                           glVertex3f(p->probe_x[p->final_num][i*SecElementNum+j],p->probe_y[p->final_num][i*SecElementNum+j],p->probe_z[p->final_num][i*SecElementNum+j]);
                           glVertex3f(p->horizontal_x[p->final_num][i*SecElementNum+j],p->horizontal_y[p->final_num][i*SecElementNum+j],p->horizontal_z[p->final_num][i*SecElementNum+j]);
                           glVertex3f(p->horizontal_x[p->final_num][i*SecElementNum+j],p->horizontal_y[p->final_num][i*SecElementNum+j],p->horizontal_z[p->final_num][i*SecElementNum+j]);
                           glVertex3f(p->focus_x[p->final_num],p->focus_y[p->final_num],p->focus_z[p->final_num]);    
		         }
		     }			

			if(p->probe_p->Pitch_Catch)
			{
				for(i=PriElementStart; i< PriElementStop ; i++)
				{
					for(j = SecElementStart; j< SecElementStop; j++)
					{
							  glVertex3f(p->probe_xr[p->final_num][i*SecElementNum+j],p->probe_yr[p->final_num][i*SecElementNum+j],p->probe_zr[p->final_num][i*SecElementNum+j]);
							  glVertex3f(p->horizontal_xr[p->final_num][i*SecElementNum+j],p->horizontal_yr[p->final_num][i*SecElementNum+j],p->horizontal_zr[p->final_num][i*SecElementNum+j]);
							  glVertex3f(p->horizontal_xr[p->final_num][i*SecElementNum+j],p->horizontal_yr[p->final_num][i*SecElementNum+j],p->horizontal_zr[p->final_num][i*SecElementNum+j]);
							  glVertex3f(p->focus_xr[p->final_num],p->focus_yr[p->final_num],p->focus_zr[p->final_num]);	 
					}
				}  


			}
			//画焦点
			if(p->probe_p->D1_D2 == 0)
			{  // 1D
	            for(i=0; i< p->k; i++)
	            {   
	                glColor3f(0.0,0.0,0.0);  
					glVertex3f(p->focus_x[i],p->focus_y[i],p->focus_z[i]);
					if(p->k == 0) 
					   glVertex3f(p->focus_x[i],p->focus_y[i],p->focus_z[i]);
					else
					   glVertex3f(p->focus_x[i+1],p->focus_y[i+1],p->focus_z[i+1]);
	            }
			}
			else
			{  // 2D
			    for(i=0; i< p->k ; i++)
	            {   
	                glColor3f(0.0,0.0,0.0); 
                    if(kkk==1 || (i+1)%kkk)
					{ 
    					glVertex3f(p->focus_x[i],p->focus_y[i],p->focus_z[i]);
    					if(p->k == 0) 
    					   glVertex3f(p->focus_x[i],p->focus_y[i],p->focus_z[i]);
    					else
    					   glVertex3f(p->focus_x[i+1],p->focus_y[i+1],p->focus_z[i+1]);
                     }
	            }
			}
            if(p->probe_p->Pitch_Catch)
			{
                for(i=0; i< p->k; i++)
                {   
                    glColor3f(0.0,0.0,0.0);  
    				glVertex3f(p->focus_xr[i],p->focus_yr[i],p->focus_zr[i]);
    				if(p->k == 0) 
    				   glVertex3f(p->focus_xr[i],p->focus_yr[i],p->focus_zr[i]);
    				else
    				   glVertex3f(p->focus_xr[i+1],p->focus_yr[i+1],p->focus_zr[i+1]);
                }  
            }
         glEnd();
		 
     glPopMatrix();
	 
}


gboolean PointInWedgeBottonRect(gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
        
    gdouble wedgeangle,roofangle;
    gdouble wg_sec_axis_reference;
    gdouble wg_pri_axis_reference;
    gdouble width,length,height;
        
    gdouble xStart;
    gdouble yStart;
    gdouble xEnd  ;
    gdouble yEnd  ;
    int i,j       ;
	int tmp;
	int elementN ;
    
    int PriElementStart = p->element_sel->primary_axis_s -1  ;
    int PriElementNum   = p->probe_p->ele_num_pri            ;
    int SecElementStart = p->element_sel->seconary_axis_s -1 ;
    int SecElementNum   = p->probe_p->ele_num_sec            ;
    int PriElementSelect= p->element_sel->pri_axis_ape       ;
    int SecElementSelect= p->element_sel->sec_axis_ape       ;
    int PriElementStop  = PriElementStart +  PriElementSelect;
    int SecElementStop  = SecElementStart +  SecElementSelect;
    int PriElementResolution = p->element_sel->primary_axis_r;
    
    roofangle =p->wedge_p->wg_roof_angle*PI/180;  /* 顶角 */
    wg_pri_axis_reference  = p->wedge_p->wg_pri_axis_reference ; /*主轴楔块参考位置*/
    wg_sec_axis_reference  = p->wedge_p->wg_sec_axis_reference ; /*次轴楔块参考位置*/
    
    width =p->wedge_p->wg_width ;     /*楔块宽度*/
    length=p->wedge_p->wg_length;     /*楔块长度*/
    height=p->wedge_p->wg_height;     /*楔块高度*/


	
	if(p->specimen->flat_cylindrical == 0)
	{
		 xStart = wg_pri_axis_reference ;
	     xEnd   = xStart + length ;
	}
	else
	{
	   	 xStart = -length/2 ;
	     xEnd   =  length/2 ;
	}
	
	if(roofangle >= 0)
	{
		 yStart = -wg_sec_axis_reference - width ;
		 yEnd   = -wg_sec_axis_reference         ;
	}
	else
	{
	     yStart = -wg_sec_axis_reference;
	     yEnd   = -wg_sec_axis_reference+width   ;
	}

	 if(p->beam_angle->beam_type == 1)
	 {
		   PriElementStart = p->element_sel->primary_axis_s - 1 + PriElementResolution * p->final_num ;
		   PriElementStop	 = PriElementStart +  PriElementSelect;
	 }

     for(i=PriElementStart; i< PriElementStop ; i++)
     {
         for(j = SecElementStart; j< SecElementStop; j++)
         {
             if (   p->horizontal_x[p->final_num][i] <= xStart || p->horizontal_x[p->final_num][i] >=xEnd ||
    		 	    p->horizontal_y[p->final_num][i] <= yStart || p->horizontal_y[p->final_num][i] >= yEnd  )
    		     return -1 ;   
         }
     }	

	return 0;
}


