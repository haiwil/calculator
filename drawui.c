/************************************************* 
              主界面
 ************************************************* */
 
#include "drawui.h"

/***************************************************
            初始化主界面 
 ***************************************************/  
GtkWidget *init_ui(DRAW_UI_P p)
{
    GtkWidget *widget;
    GtkWidget *vbox_sub;
    GtkWidget *page;
    GtkWidget *label[5];
    
    widget=gtk_vbox_new(FALSE,0);
    gtk_widget_show(widget);
//    gtk_widget_set_size_request(GTK_WIDGET(p->left_down_window),400,250);
    /***************************************************
            PA Calculator页面的内容 
     ***************************************************/    
    p->vpaned=gtk_vpaned_new();//二级垂直分栏 
    p->hpaned_sub=gtk_hpaned_new();//三级水平分栏    
    /*二级 左边垂直分栏里添加构件*/ 
    gtk_paned_add1(GTK_PANED(p->vpaned),p->hpaned_sub);//
    gtk_paned_add2(GTK_PANED(p->vpaned),init_left_down_window(p));
    /*在三级水平分栏窗口的两部分添加构件*/
	gtk_paned_add1(GTK_PANED(p->hpaned_sub),create_tree_left (p));
    gtk_paned_add2(GTK_PANED(p->hpaned_sub),create_tree_right(p));
    
    /*****************************************************
             page---分页控制 
     *****************************************************/
    page=gtk_notebook_new();
    label[0]=gtk_label_new("Focal Laws Calculator");
    label[1]=gtk_label_new("Display Info");
    label[2]=gtk_label_new("Elements Info");
    gtk_notebook_append_page(GTK_NOTEBOOK(page),p->vpaned,label[0]); /* 第一页 */
//    gtk_notebook_append_page(GTK_NOTEBOOK(page),do_appwindow(p),label[1]);/* 第二页 */
//    gtk_notebook_append_page(GTK_NOTEBOOK(page),do_appwindow(p),label[2]);/* 第三页 */
    gtk_widget_show_all(page);
    
    /*****************************************************
            分栏窗口 
     *****************************************************/
    p->hpaned=gtk_hpaned_new();//一级水平分栏  
    gtk_widget_show(p->hpaned);    
    gtk_box_pack_start(GTK_BOX(widget),GTK_WIDGET(p->hpaned),TRUE,TRUE,0);
    //
    vbox_sub=gtk_vbox_new(FALSE,0);
    gtk_widget_show(vbox_sub);
    gtk_box_pack_start(GTK_BOX(vbox_sub),GTK_WIDGET( create_draw_area0(p) ),TRUE,TRUE,0);  // 绘图区域添加在此处  
    gtk_box_pack_start(GTK_BOX(vbox_sub),GTK_WIDGET( create_draw_area1(p) ),TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox_sub),GTK_WIDGET( create_draw_area2(p) ),TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox_sub),GTK_WIDGET( create_draw_area3(p) ),TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox_sub),GTK_WIDGET( ShowElementDelay(p) ),FALSE,FALSE,0);//阵元延时信息显示添加在此处 
    // 
	/*在一级水平分栏窗口的两部分添加构件*/
	gtk_paned_add1(GTK_PANED(p->hpaned),page);/* 页面控件添加在此处 */
    gtk_paned_add2(GTK_PANED(p->hpaned),vbox_sub);        

    
    
    

    return widget;
}

/*****************************************************
            初始化左下窗口
*****************************************************/
GtkWidget * init_left_down_window(DRAW_UI_P p)
{
    gint i;
    for(i=0;i<7;i++)
    {
      p->parament[i]=Hd_select_parament[i];
      p->label[i]=Hd_select_label[i];                
    }
    p->left_down_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_container_set_border_width(GTK_CONTAINER(p->left_down_window),0);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(p->left_down_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(GTK_WIDGET(p->left_down_window),400,250);
	p->vbox_ldw=gtk_fixed_new(); 
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->left_down_window),p->vbox_ldw);
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
    gtk_widget_show_all(p->left_down_window);
    return  p->left_down_window ;
}

/*****************************************************
            创建绘图区域 -----0 , 1 , 2 , 3
*****************************************************/
GtkWidget *create_draw_area0(DRAW_UI_P p)
{
    p->drawing_area[0]=gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(p->drawing_area[0]), 700, 500);
    
    gtk_widget_set_gl_capability (p->drawing_area[0],p->glconfig,NULL,TRUE,GDK_GL_RGBA_TYPE);
    gtk_widget_add_events (p->drawing_area[0],GDK_BUTTON_PRESS_MASK | GDK_SCROLL_MASK  |GDK_BUTTON1_MOTION_MASK
                         |GDK_BUTTON3_MOTION_MASK );
    
    g_signal_connect_after (G_OBJECT (p->drawing_area[0]), "realize",G_CALLBACK (realize), (gpointer) p);
    g_signal_connect (G_OBJECT (p->drawing_area[0]), "configure_event",G_CALLBACK (configure_event), (gpointer) p);
    g_signal_connect(G_OBJECT(p->drawing_area[0]), "expose_event", G_CALLBACK(expose_event), (gpointer) p );
    g_signal_connect (G_OBJECT (p->drawing_area[0]), "scroll_event",G_CALLBACK (scroll_event), (gpointer) p);
    g_signal_connect (G_OBJECT (p->drawing_area[0]), "button_press_event",G_CALLBACK (button_press_event), (gpointer) p); 
    g_signal_connect (G_OBJECT (p->drawing_area[0]), "motion_notify_event",G_CALLBACK (motion_notify_event), (gpointer) p);
    /* key_press_event handler for top-level window */
    g_signal_connect_swapped (G_OBJECT (p->window), "key_press_event",G_CALLBACK (key_press_event), p->drawing_area[0]);//
	
//    gtk_widget_show_all(p->drawing_area[0]);
    
    return  p->drawing_area[0];       
}
//
GtkWidget *create_draw_area1(DRAW_UI_P p)
{
    p->drawing_area[1]=gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(p->drawing_area[1]), 700, 500);
    
    gtk_widget_set_gl_capability (p->drawing_area[1],p->glconfig,NULL,TRUE,GDK_GL_RGBA_TYPE);
    gtk_widget_add_events (p->drawing_area[1],GDK_BUTTON_PRESS_MASK | GDK_SCROLL_MASK  |GDK_BUTTON1_MOTION_MASK
                         |GDK_BUTTON3_MOTION_MASK );
    
    g_signal_connect_after (G_OBJECT (p->drawing_area[1]), "realize",G_CALLBACK (realize), (gpointer) p);
    g_signal_connect (G_OBJECT (p->drawing_area[1]), "configure_event",G_CALLBACK (configure_event), (gpointer) p);
    g_signal_connect(G_OBJECT(p->drawing_area[1]), "expose_event", G_CALLBACK(expose_event), (gpointer) p );
    g_signal_connect (G_OBJECT (p->drawing_area[1]), "scroll_event",G_CALLBACK (scroll_event), (gpointer) p);
    g_signal_connect (G_OBJECT (p->drawing_area[1]), "button_press_event",G_CALLBACK (button_press_event), (gpointer) p); 
    g_signal_connect (G_OBJECT (p->drawing_area[1]), "motion_notify_event",G_CALLBACK (motion_notify_event), (gpointer) p);
    /* key_press_event handler for top-level window */
    g_signal_connect_swapped (G_OBJECT (p->window), "key_press_event",G_CALLBACK (key_press_event), p->drawing_area[1]);//
			    
//    gtk_widget_show_all(p->drawing_area[1]);
    
    return  p->drawing_area[1];       
}
//
GtkWidget *create_draw_area2(DRAW_UI_P p)
{
    p->drawing_area[2]=gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(p->drawing_area[2]), 700, 500);
    
    gtk_widget_set_gl_capability (p->drawing_area[2],p->glconfig,NULL,TRUE,GDK_GL_RGBA_TYPE);
    gtk_widget_add_events (p->drawing_area[2],GDK_BUTTON_PRESS_MASK | GDK_SCROLL_MASK  |GDK_BUTTON1_MOTION_MASK
                         |GDK_BUTTON3_MOTION_MASK );
    
    g_signal_connect_after (G_OBJECT (p->drawing_area[2]), "realize",G_CALLBACK (realize), (gpointer) p);
    g_signal_connect (G_OBJECT (p->drawing_area[2]), "configure_event",G_CALLBACK (configure_event), (gpointer) p);
    g_signal_connect(G_OBJECT(p->drawing_area[2]), "expose_event", G_CALLBACK(expose_event), (gpointer) p );
    g_signal_connect (G_OBJECT (p->drawing_area[2]), "scroll_event",G_CALLBACK (scroll_event), (gpointer) p);
    g_signal_connect (G_OBJECT (p->drawing_area[2]), "button_press_event",G_CALLBACK (button_press_event), (gpointer) p); 
    g_signal_connect (G_OBJECT (p->drawing_area[2]), "motion_notify_event",G_CALLBACK (motion_notify_event), (gpointer) p);
    /* key_press_event handler for top-level window */
    g_signal_connect_swapped (G_OBJECT (p->window), "key_press_event",G_CALLBACK (key_press_event), p->drawing_area[2]);//
			    
//    gtk_widget_show_all(p->drawing_area[2]);
    
    return  p->drawing_area[2];       
}
//
GtkWidget *create_draw_area3(DRAW_UI_P p)
{
    p->drawing_area[3]=gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(p->drawing_area[3]), 700, 500);
    
    gtk_widget_set_gl_capability (p->drawing_area[3],p->glconfig,NULL,TRUE,GDK_GL_RGBA_TYPE);
    gtk_widget_add_events (p->drawing_area[3],GDK_BUTTON_PRESS_MASK | GDK_SCROLL_MASK  |GDK_BUTTON1_MOTION_MASK
                         |GDK_BUTTON3_MOTION_MASK );
    
    g_signal_connect_after (G_OBJECT (p->drawing_area[3]), "realize",G_CALLBACK (realize), (gpointer) p);
    g_signal_connect (G_OBJECT (p->drawing_area[3]), "configure_event",G_CALLBACK (configure_event), (gpointer) p);
    g_signal_connect(G_OBJECT(p->drawing_area[3]), "expose_event", G_CALLBACK(expose_event_3d), (gpointer) p );
    g_signal_connect (G_OBJECT (p->drawing_area[3]), "scroll_event",G_CALLBACK (scroll_event), (gpointer) p);
    g_signal_connect (G_OBJECT (p->drawing_area[3]), "button_press_event",G_CALLBACK (button_press_event), (gpointer) p); 
    g_signal_connect (G_OBJECT (p->drawing_area[3]), "motion_notify_event",G_CALLBACK (motion_notify_event), (gpointer) p);
    /* key_press_event handler for top-level window */
    g_signal_connect_swapped (G_OBJECT (p->window), "key_press_event",G_CALLBACK (key_press_event), p->drawing_area[3]);//
			    
    gtk_widget_show_all(p->drawing_area[3]);
    
    return  p->drawing_area[3];       
}


/*****************************************************
            快捷菜单创建部分 
*****************************************************/
/* menu bar*/
static GtkActionEntry entries[] = {
  { "FileMenu", NULL, "_File" },               /* name, stock id, label */
  { "PreferencesMenu", NULL, "_Preferences" }, /* name, stock id, label */
  { "ElementInfo", NULL, "_ElementInfo" }, /* name, stock id, label */ 
  { "Viewport", NULL, "Viewport" }, /* name, stock id, label */ 
  { "HelpMenu", NULL, "_Help" },               /* name, stock id, label */
//File  
  { "Load Beam Data File", GTK_STOCK_OK,                      /* name, stock id */
    "_Load Beam Data File", "<control>L",                      /* label, accelerator */
    "Load Beam Data File",                       /* tooltip */ 
    G_CALLBACK (load_beam_setup) },      
  { "Save Beam Data File", NULL,                    /* name, stock id */
    "_Save Beam Data File","<control>S",                      /* label, accelerator */     
    "Save Beam Data File",                       /* tooltip */
    G_CALLBACK (save_beam_setup) },
  { "SaveAs", GTK_STOCK_SAVE,                                           /* name, stock id */
    "_Save Beam Data File As...", "<control>A",                       /* label, accelerator */     
    "Save As Beam Data File",                                         /* tooltip */
    G_CALLBACK (save_as_beam_setup) },

  { "Save", GTK_STOCK_SAVE,                    /* name, stock id */
    "Save",NULL,                      /* label, accelerator */     
    "Save Beam Data File",                       /* tooltip */
    G_CALLBACK (save_as_beam_setup) }, 
  { "Load", GTK_STOCK_OK,                      /* name, stock id */
    "Load", NULL,                      /* label, accelerator */
    "Load Beam Data File",                       /* tooltip */ 
    G_CALLBACK (load_beam_setup) }, 
//quit
  { "Quit", GTK_STOCK_QUIT,                    /* name, stock id */
    "_Quit", "<alt>F4",                     /* label, accelerator */     
    "Quit",                                    /* tooltip */
    G_CALLBACK (gtk_main_quit) },
//Help
  { "About", NULL,                             /* name, stock id */
    "_About", "<control>A",                    /* label, accelerator */     
    "About",                                   /* tooltip */  
    G_CALLBACK (about) },
//FocalLaw
  { "Run", "demo_run",                   /* name, stock id */
     "Run", "F9",                               /* label, accelerator */     
    "Focal Law Begin",                                    /* tooltip */
    G_CALLBACK (focal_law) },
//element info
  { "Show", "demo_show",                   /* name, stock id */
     "Show", "<alt>S",                               /* label, accelerator */     
    "Show Element Info",                                    /* tooltip */
    G_CALLBACK (show_action) },  
  { "Hide", GTK_STOCK_CLOSE,                   /* name, stock id */
     "Hide", "<alt>D",                               /* label, accelerator */     
    "Hide Element Info",                                    /* tooltip */
    G_CALLBACK (hide_action) },
//online
  { "Connection", GTK_STOCK_CONNECT,                   /* name, stock id */
     "Link", NULL,                               /* label, accelerator */     
    "Connect With Omiscan",                                    /* tooltip */
    G_CALLBACK (activate_action) },       
//save .law文件 
  { "Save .law File", NULL,                    /* name, stock id */
    "Save .law File", NULL,                      /* label, accelerator */     
    "Save .law File",                       /* tooltip */
    G_CALLBACK (save_law) },
  { "Save .law File As",    NULL,                                           /* name, stock id */
    "Save .law File As...", NULL,                       /* label, accelerator */     
    "Save As .law File",                                         /* tooltip */
    G_CALLBACK (save_as_law) },  
//view
  { "Top", "demo_top",                    /* name, stock id */
    "Top", "F5",                      /* label, accelerator */     
    "top view ",                       /* tooltip--俯视图 */
    G_CALLBACK (view_top) },
  { "Left","demo_left",                                           /* name, stock id */
    "Left", "F6",                       /* label, accelerator */     
    "left view",                                         /* tooltip--左视图 */
    G_CALLBACK (view_left) },
  { "Front","demo_front",                                           /* name, stock id */
    "Front", "F7",                       /* label, accelerator */     
    "front view",                                         /* tooltip--主视图 */
    G_CALLBACK (view_front) },
  { "3D", "demo_3d",                                           /* name, stock id */
    "3D", "F8",                       /* label, accelerator */     
    "3D view",                                         /* tooltip--三维视图 */
    G_CALLBACK (view_3D) },             
};
static guint n_entries = G_N_ELEMENTS (entries);

static const gchar *ui_info = 
"<ui>"
"  <menubar name='MenuBar'>"

"    <menu action='FileMenu'>"
"      <menuitem action='Load Beam Data File'/>"
"      <separator/>"
"      <menuitem action='Save Beam Data File'/>"
"      <menuitem action='SaveAs'/>"
"      <separator/>"
"      <menuitem action='Save .law File'/>"
"      <menuitem action='Save .law File As'/>"
"      <separator/>"
"      <menuitem action='Quit'/>"
"    </menu>"

"    <menu action='ElementInfo'>"
"      <menuitem action='Run'/>"
"      <separator/>"
"      <menuitem action='Show'/>"
"      <menuitem action='Hide'/>"
"    </menu>"

"    <menu action='Viewport'>"
"      <menuitem action='3D'/>"
"      <separator/>"
"      <menuitem action='Top'/>"
"      <menuitem action='Left'/>"
"      <menuitem action='Front'/>"
"    </menu>"

"    <menu action='HelpMenu'>"
"      <menuitem action='About'/>"
"    </menu>"

"  </menubar>"

"  <toolbar  name='ToolBar'>"
"    <toolitem action='Load'/>"
"    <toolitem action='Save'/>"
"    <separator action='Sep1'/>"
"    <toolitem action='Run'/>"
"    <separator action='Sep2'/>"
"    <toolitem action='Show'/>"
"    <toolitem action='Hide'/>"
"    <separator action='Sep3'/>"
"    <toolitem action='Connection'/>"
"    <separator action='Sep4'/>"
"    <toolitem action='Top'/>"
"    <toolitem action='Left'/>"
"    <toolitem action='Front'/>"
"    <toolitem action='3D'/>"
"  </toolbar>"
"</ui>";

/* This function registers our custom toolbar icons, so they can be themed.
 *
 * It's totally optional to do this, you could just manually insert icons
 * and have them not be themeable, especially if you never expect people
 * to theme your app.
 */
#define NUM_PIXBUF 6
void register_stock_icons (void)
{
  static gboolean registered = FALSE;
  
  if (!registered)
    {
      gint i;
      GdkPixbuf *pixbuf[NUM_PIXBUF];
      GtkIconFactory *factory[NUM_PIXBUF];

      static GtkStockItem items[] = 
      {
        { "demo_3d",    "3D",   0, 0, NULL },
        { "demo_top",   "TOP",  0, 0, NULL },
        { "demo_left",  "LEFT", 0, 0, NULL },
        { "demo_front", "FRONT",0, 0, NULL },
        { "demo_run",   "RUN",  0, 0, NULL },
        { "demo_show",  "SHOW", 0, 0, NULL }
      };
      
      registered = TRUE;

      /* Register our stock items */
      gtk_stock_add (items, G_N_ELEMENTS (items));

      for(i=0;i<NUM_PIXBUF;i++)
      {
         /* Add our custom icon factory to the list of defaults */
         factory[i] = gtk_icon_factory_new ();
         gtk_icon_factory_add_default (factory[i]);   
         //
         pixbuf[i] = NULL;                   
      }
          
      pixbuf[0] = gdk_pixbuf_new_from_file ("./image/3D.png",    NULL);
      pixbuf[1] = gdk_pixbuf_new_from_file ("./image/top.png",   NULL);
      pixbuf[2] = gdk_pixbuf_new_from_file ("./image/left.png",  NULL);
      pixbuf[3] = gdk_pixbuf_new_from_file ("./image/front.png", NULL);
      pixbuf[4] = gdk_pixbuf_new_from_file ("./image/run.png",   NULL);
      pixbuf[5] = gdk_pixbuf_new_from_file ("./image/show.png",  NULL);

      /* Register icon to accompany stock item */
      GtkIconSet *icon_set[NUM_PIXBUF];
      GdkPixbuf  *transparent[NUM_PIXBUF];
      for(i=0;i<NUM_PIXBUF;i++)
      {
           if (pixbuf[i] != NULL)
            {
              /* The gtk-logo-rgb icon has a white background, make it transparent */
              transparent[i] = gdk_pixbuf_add_alpha (pixbuf[i], TRUE, 0xff, 0xff, 0xff);
              icon_set[i]    = gtk_icon_set_new_from_pixbuf (transparent[i]);
              switch(i)
              {
                  case 0 :
                       gtk_icon_factory_add (factory[i], "demo_3d",    icon_set[i]);
                       break;  
                  case 1 :
                       gtk_icon_factory_add (factory[i], "demo_top",   icon_set[i]);
                       break;      
                  case 2 :
                       gtk_icon_factory_add (factory[i], "demo_left",  icon_set[i]);
                       break;  
                  case 3 :
                       gtk_icon_factory_add (factory[i], "demo_front", icon_set[i]);
                       break;  
                  case 4 :
                       gtk_icon_factory_add (factory[i], "demo_run",   icon_set[i]);
                       break; 
                  case 5 :
                       gtk_icon_factory_add (factory[i], "demo_show",  icon_set[i]);
                       break;                     
              }
              
              gtk_icon_set_unref (icon_set[i]);
              g_object_unref (pixbuf[i]);
              g_object_unref (transparent[i]);
            }
          else
            g_warning ("failed to load GTK logo for toolbar");
          
          /* Drop our reference to the factory, GTK will hold a reference. */
          g_object_unref (factory[i]);
      }          
    }
}
//
void activate_action (GtkAction *action,gpointer data)
{
  DRAW_UI_P p = (DRAW_UI_P)(data);
  /*
  const gchar *name = gtk_action_get_name (action);
  const gchar *typename = G_OBJECT_TYPE_NAME (action);

  GtkWidget *dialog;
  
  dialog = gtk_message_dialog_new (GTK_WINDOW (p->window),
                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_INFO,
                                   GTK_BUTTONS_CLOSE,
                                   "You activated action: \"%s\" of type \"%s\"",
                                    name, typename);

  g_signal_connect (dialog,
                    "response",
                    G_CALLBACK (gtk_widget_destroy),
                    NULL);
  
  gtk_widget_show (dialog);*/
}
//**************************************************
//  Name:  about
//  Copyright: Dopplor 
//  Author: He Fan
//  Date: 20-04-26 15:30
//**************************************************
void about(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   GtkWidget *dialog, *label, *vbox;
   /* Create the widgets */
   dialog = gtk_dialog_new_with_buttons ("About Doppler's calculator",
                                         GTK_WINDOW (p->window),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_CANCEL,
                                         GTK_RESPONSE_NONE,
                                         NULL);
   gtk_widget_set_size_request(GTK_WIDGET (dialog), 400, 370);
   gtk_window_set_modal (GTK_WINDOW(dialog), TRUE);//激活该窗口禁止主窗口 
   /* Ensure that the dialog box is destroyed when the user responds. */
   g_signal_connect_swapped (dialog,
                             "response",
                             G_CALLBACK (gtk_widget_destroy),
                             dialog);
   vbox = GTK_WIDGET(GTK_DIALOG(dialog)->vbox);                                      
   label = gtk_label_new ("Doppler's CopyRight");                          
   gtk_container_add (GTK_CONTAINER (vbox), label);
   
   gtk_widget_show_all (dialog);
  
}

/*快捷菜单栏创建函数*/
GtkWidget *do_appwindow(DRAW_UI_P p)
{
      GtkWidget *window=p->window;
      GtkWidget *table;
      GtkWidget *bar;
//      GtkWidget *hbox;
      GtkWidget *handle[5];/*浮动工具栏*/
      GtkActionGroup *action_group;
      GtkUIManager *merge;
      GError *error = NULL;      
      
      register_stock_icons ();
      table = gtk_table_new (1, 4, FALSE);
      /* Create the menubar and toolbar*/      
      action_group = gtk_action_group_new ("AppWindowActions");
      gtk_action_group_add_actions (action_group, entries, n_entries, (gpointer) (p));

      merge = gtk_ui_manager_new ();
      g_object_set_data_full (G_OBJECT (table), "ui-manager", merge, g_object_unref);
      gtk_ui_manager_insert_action_group (merge, action_group, 0);
      gtk_window_add_accel_group (GTK_WINDOW (window), gtk_ui_manager_get_accel_group (merge));
      
      if (!gtk_ui_manager_add_ui_from_string (merge, ui_info, -1, &error))
    	{
    	  g_message ("building menus failed: %s", error->message);
    	  g_error_free (error);
    	}

      bar = gtk_ui_manager_get_widget (merge, "/MenuBar");
     
      gtk_table_attach (GTK_TABLE (table),bar, 
                        /* X direction */          /* Y direction */
                        0, 1,                      0, 1,
                        GTK_EXPAND | GTK_FILL,     0,
                        0,                         0);

//      hbox=gtk_hbox_new(FALSE,0);
//      handle[0]=gtk_handle_box_new();
//      gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(handle[0]),FALSE,FALSE,5);
      
      bar = gtk_ui_manager_get_widget (merge, "/ToolBar");
      gtk_toolbar_set_tooltips (GTK_TOOLBAR (bar), TRUE);
//      gtk_container_add(GTK_CONTAINER(handle[0]),bar);
      //
//      handle[1]=gtk_handle_box_new();
//      gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(handle[1]),FALSE,FALSE,5);
      //
//      gtk_widget_show (handle[0]);
      gtk_table_attach (GTK_TABLE (table),bar, 
                        /* X direction */       /* Y direction */
                        0, 1,                   1, 2,
                        GTK_EXPAND | GTK_FILL,  0,
                        0,                      0);
                        
      gtk_widget_show (table);
      return table;   
}

/*阵元延时显示函数*/
GtkWidget *ShowElementDelay(DRAW_UI_P p)
{      
    
    p->ScrooledWindow=gtk_scrolled_window_new(NULL,NULL);
    gtk_container_set_border_width(GTK_CONTAINER(p->ScrooledWindow),0);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(p->ScrooledWindow),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(GTK_WIDGET(p->ScrooledWindow),700,200);
    //
    p->hbox_delay = ShowElementDelay_time(p);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(p->ScrooledWindow),p->hbox_delay);  
    //
	return  p->ScrooledWindow ;
}

GtkWidget *ShowElementDelay_time(DRAW_UI_P p)
{
    GtkWidget *ScrooledWindow[2];
    GtkWidget *hbox;
    GtkWidget *frame[3];
    GtkWidget *vbox;
    static gchar *titles[]={"Index","Delay(ns)"};       
    
    //
	hbox=gtk_hbox_new(FALSE,0);
	
    //Current focal law
    frame[0]=gtk_frame_new("Current focal law");
    gtk_widget_set_size_request(GTK_WIDGET(frame[0]),200,100);
    gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(frame[0]),FALSE,FALSE,5);
    
    vbox=gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(frame[0]),vbox);
    
    p->combo = gtk_combo_box_entry_new_text();
    gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo), p->CurrentNum);
    g_signal_connect(G_OBJECT(p->combo),"changed" ,G_CALLBACK(CurrentFocallaw),(gpointer) p );
    gtk_widget_set_sensitive (p->combo, p->DrawResult);
    gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(p->combo),FALSE,FALSE,5);
    
    //Pulser elements
    frame[1]=gtk_frame_new("Pulser elements");
    gtk_widget_set_size_request(GTK_WIDGET(frame[1]),250,200);
    gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(frame[1]),FALSE,FALSE,5);
    
    ScrooledWindow[0]=gtk_scrolled_window_new(NULL,NULL);
    gtk_container_set_border_width(GTK_CONTAINER(ScrooledWindow[0]),0);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(ScrooledWindow[0]),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(frame[1]),ScrooledWindow[0]);
    
    vbox=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(ScrooledWindow[0]),vbox);
      
	p->clist[0]=gtk_clist_new_with_titles(2,titles);
	gtk_clist_set_shadow_type(GTK_CLIST(p->clist[0]),GTK_SHADOW_OUT);//设置边框阴影
    gtk_clist_set_column_width(GTK_CLIST(p->clist[0]),0,100);//设置列宽 
    gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(p->clist[0]),FALSE,FALSE,5);
    
    //Recever elements
    frame[2]=gtk_frame_new("Recever elements");
    gtk_widget_set_size_request(GTK_WIDGET(frame[2]),250,200);
    gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(frame[2]),FALSE,FALSE,5);
    
    ScrooledWindow[1]=gtk_scrolled_window_new(NULL,NULL);
    gtk_container_set_border_width(GTK_CONTAINER(ScrooledWindow[1]),0);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(ScrooledWindow[1]),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(frame[2]),ScrooledWindow[1]);
    
    vbox=gtk_vbox_new(FALSE,0);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(ScrooledWindow[1]),vbox);
      
	p->clist[1]=gtk_clist_new_with_titles(2,titles);
	gtk_clist_set_shadow_type(GTK_CLIST(p->clist[1]),GTK_SHADOW_OUT);//设置边框阴影
    gtk_clist_set_column_width(GTK_CLIST(p->clist[1]),0,100);//设置列宽 
    gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(p->clist[1]),FALSE,FALSE,5);
    

	return  hbox ; 
}

GtkWidget *InsertCurrentFocallaw(DRAW_UI_P p)
{
   gint i,j;
   gdouble a2,a3,a_,a_tmp;
   gdouble screwStart, screwStep , screwEnd, screwTmp ;
   gint temp1 ,temp2 , temp3 ;

   int PriElementStart = p->element_sel->primary_axis_s   ;
   int PriElementResolution = p->element_sel->primary_axis_r;

   double DepthStart = p->focal_point->focal_focus_point_start  ;
   double Resolution = p->focal_point->focal_focus_point_resolution;
   
   gchar ch[20] = "Azmuthal  R:";
   gchar ch_inedx[10];
   
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
                a_tmp=a2; 
                a3 = (p->beam_angle->beam_refrac_angle_stop); 
                a_ = (p->beam_angle->beam_refrac_angle_resolution);
				screwStart = (p->beam_angle->beam_skew_angle_start);
                screwTmp   =screwStart;
                screwEnd = (p->beam_angle->beam_skew_angle_stop); 
                screwStep = (p->beam_angle->beam_skew_angle_resolution);
            }
           break;                            
   }
    
   gtk_widget_set_sensitive (p->combo, p->DrawResult);

   switch(p->probe_p->D1_D2)
   {
        case 0://1D
             switch(p->beam_angle->beam_type)
               {
                  case 0://Azimuthal
                        switch(p->beam_angle->beam_angle_sel)
                        {
                           case 0://Refracted
                                strcpy(ch,"Azmuthal  R:");
                                for(i=0;i < p->del_k+1;i++)
                                {
                                   a_tmp = a2 + a_*i;//当前折射角 
                                   sprintf(p->pp, "%.0f",a_tmp);
                                   strncat(ch,p->pp,3);
                                   gtk_combo_box_remove_text(GTK_COMBO_BOX(p->combo),i);
                                   gtk_combo_box_insert_text(GTK_COMBO_BOX(p->combo),i,ch); 
                                   strcpy(ch,"Azmuthal  R:");
                                }
                                gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo), 0);
                                break;
                           case 1://Primary steering
                                strcpy(ch,"Azmuthal  PS:");
                                for(i=0;i < p->del_k+1;i++)
                                {
                                   a_tmp = a2 + a_*i;//当前折射角 
                                   sprintf(p->pp, "%.0f",a_tmp);
                                   strncat(ch,p->pp,3);
                                   gtk_combo_box_remove_text(GTK_COMBO_BOX(p->combo),i);
                                   gtk_combo_box_insert_text(GTK_COMBO_BOX(p->combo),i,ch); 
                                   strcpy(ch,"Azmuthal  PS:");
                                }
                                gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo), 0);
                                break;
                           case 2://Beam skew
                                strcpy(ch,"Azmuthal  S:");
                                for(i=0;i < p->del_k+1;i++)
                                {
                                   a_tmp = a2 + a_*i;//当前折射角 
                                   sprintf(p->pp, "%.0f",a_tmp);
                                   strncat(ch,p->pp,3);
                                   gtk_combo_box_remove_text(GTK_COMBO_BOX(p->combo),i);
                                   gtk_combo_box_insert_text(GTK_COMBO_BOX(p->combo),i,ch); 
                                   strcpy(ch,"Azmuthal  S:");
                                }
                                gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo), 0);
                                break;  
                        }
                        break;  
                  case 1://Linear                        
                        strcpy(ch,"Linear L");
                        for(i=0;i < p->del_k+1;i++)
                        {
                           
                           sprintf(ch_inedx, "%d",i+1);
                           strncat(ch,ch_inedx,1);
                           strncat(ch,":",1);
                           //a_tmp = a2 + a_*i;//当前折射角 
                           temp1 = PriElementStart + PriElementResolution * i  ;
						   sprintf(p->pp, "%d", temp1);
                           strncat(ch,p->pp,3);
                           gtk_combo_box_remove_text(GTK_COMBO_BOX(p->combo),i);
                           gtk_combo_box_insert_text(GTK_COMBO_BOX(p->combo),i,ch); 
                           strcpy(ch,"Linear L");
                        }
                        gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo), 0);
                        break;
                  case 2://Depth
                        strcpy(ch,"Depth D:");
                        for(i=0;i < p->del_k+1;i++)
                        {
                           a_tmp = DepthStart + Resolution * i;//当前折射角 
                           sprintf(p->pp, "%.0f",a_tmp);
                           strncat(ch,p->pp,3);
                           gtk_combo_box_remove_text(GTK_COMBO_BOX(p->combo),i);
                           gtk_combo_box_insert_text(GTK_COMBO_BOX(p->combo),i,ch); 
                           strcpy(ch,"Depth D:");
                        }
                        gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo), 0);
                        break;  
                  case 3://Static 
                        for(i=0;i < p->del_k+1;i++)
                        {
                          gtk_combo_box_remove_text(GTK_COMBO_BOX(p->combo),0); 
                        } 
                        gtk_combo_box_insert_text(GTK_COMBO_BOX(p->combo),0,"Law1");
                        gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo), 0);
                        break;
             }
             break;  
        case 1://2D
             switch(p->beam_angle->beam_type)
               {
                  case 0://Azimuthal
                        switch(p->beam_angle->beam_angle_sel)
                        {
                           case 0:

                                break;
                           case 1:
                                
                                break;
                           case 2:
                                
                                break; 
                           case 3:
                                if(screwEnd < screwStart) break ;
                                temp3 =1+ (gint)((screwEnd - screwStart) / screwStep) ;
	                            for ( i = 0; i <= p->del_k; i ++ ) 
	                            {
									  temp1 = i / temp3 ;
									  temp2 = i % temp3 ;
									  strcpy(ch,"Azim. PS:");
									  sprintf(ch_inedx, "%d",i+1);
									  strncat(ch,ch_inedx,1);
	            	                  a2 = a_tmp + a_ * temp1;
									  screwTmp = screwStart + screwStep * temp2 ;
									  sprintf(p->pp, "R:%.0f, S:%.0f",a2,screwTmp);
	            	                  strncat(ch,p->pp,15);
	            	                  gtk_combo_box_remove_text(GTK_COMBO_BOX(p->combo),i);
	                                  gtk_combo_box_insert_text(GTK_COMBO_BOX(p->combo),i,ch); 
	                            }
                                gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo), 0);
                                break;      
                        }
                        break;  
                  case 1://Linear
						strcpy(ch,"Linear L");
						for(i=0;i < p->del_k+1;i++)
						{
						 
						 sprintf(ch_inedx, "%d",i+1);
						 strncat(ch,ch_inedx,1);
						 strncat(ch,":",1);
						 //a_tmp = a2 + a_*i;//当前折射角 
						 temp1 = PriElementStart + PriElementResolution * i  ;
						 sprintf(p->pp, "%d", temp1);
						 strncat(ch,p->pp,3);
						 gtk_combo_box_remove_text(GTK_COMBO_BOX(p->combo),i);
						 gtk_combo_box_insert_text(GTK_COMBO_BOX(p->combo),i,ch); 
						 strcpy(ch,"Linear L");
						}
						gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo), 0);
						break;
                  case 2://Depth
                        strcpy(ch,"Depth D:");
                        for(i=0;i < p->del_k+1;i++)
                        {
                           a_tmp = DepthStart + Resolution * i;//当前折射角 
                           sprintf(p->pp, "%.0f",a_tmp);
                           strncat(ch,p->pp,3);
                           gtk_combo_box_remove_text(GTK_COMBO_BOX(p->combo),i);
                           gtk_combo_box_insert_text(GTK_COMBO_BOX(p->combo),i,ch); 
                           strcpy(ch,"Depth D:");
                        }
                        gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo), 0);
                        break;  
                  case 3://Static 
                        for(i=0;i < p->del_k+1;i++)
                        {
                          gtk_combo_box_remove_text(GTK_COMBO_BOX(p->combo),0); 
                        } 
                        gtk_combo_box_insert_text(GTK_COMBO_BOX(p->combo),0,"Law1");
                        gtk_combo_box_set_active(GTK_COMBO_BOX(p->combo), 0);
                        break;
             }
             break;                  
   }
               
   
}

GtkWidget *InsertElementDelay(DRAW_UI_P p)
{
	int PriElementStart = p->element_sel->primary_axis_s -1  ;
	int PriElementNum	= p->probe_p->ele_num_pri			 ;
	int SecElementStart = p->element_sel->seconary_axis_s -1 ;
	int SecElementNum	= p->probe_p->ele_num_sec			 ;
	int PriElementSelect= p->element_sel->pri_axis_ape		 ;
	int SecElementSelect= p->element_sel->sec_axis_ape		 ;
	
	int PriElementStop	= PriElementStart +  PriElementSelect;
	int SecElementStop	= SecElementStart +  SecElementSelect;
	
	int PriElementResolution = p->element_sel->primary_axis_r;
	
    if(p->beam_angle->beam_type == 1)
	{
	      PriElementStart = p->element_sel->primary_axis_s - 1 + PriElementResolution * p->final_num ;
		  PriElementStop	= PriElementStart +  PriElementSelect;
    }
	
    if(p->probe_p->D1_D2 == 0) {SecElementNum = 1;  SecElementStart = 0; SecElementStop = 1;}
    if(PriElementStop > PriElementNum )  return NULL;
	if(SecElementStop > SecElementNum && p->probe_p->D1_D2 ) return NULL;	 

	int i, j; 
	static gchar *texts[]={"",""};

	gchar Index[elements_num];

	gtk_clist_clear(GTK_CLIST(p->clist[0]));
	gtk_clist_clear(GTK_CLIST(p->clist[1]));
	gtk_clist_freeze(GTK_CLIST(p->clist[0]));
	gtk_clist_freeze(GTK_CLIST(p->clist[1]));
	gint tmp;
	gint elementN ;
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
  
    if( (init+tmp) > elementN )
         return 0;
   
    //Pulser elements
	for(i=0; i < elementN; i++)
	{       
		   gtk_clist_append(GTK_CLIST(p->clist[0]),texts);
		   sprintf(Index, "%d",i+1);  // 将整数转换成字符串       
		   gtk_clist_set_text(GTK_CLIST(p->clist[0]),i,0,Index );      
	}

	for(i=PriElementStart; i< PriElementStop ; i++)
	{
		 for(j = SecElementStart; j< SecElementStop; j++)
		 {
		      sprintf(p->pp, "%.0f",p->timedelay[p->final_num][i*SecElementNum+j]);
	          gtk_clist_set_text(GTK_CLIST(p->clist[0]),i*SecElementNum+j,1,p->pp ); 
		 }
	}
	
   //Recever elements 
   for(i=0; i < elementN; i++)
	{       
	   gtk_clist_append(GTK_CLIST(p->clist[1]),texts);
	   sprintf(Index, "%d",i+1);  // 将整数转换成字符串       
	   gtk_clist_set_text(GTK_CLIST(p->clist[1]),i,0,Index );      
	}
   for(i=PriElementStart; i< PriElementStop ; i++)
   {
		for(j = SecElementStart; j< SecElementStop; j++)
		{
			 sprintf(p->pp, "%.0f",p->timedelay[p->final_num][i*SecElementNum+j]);
			 gtk_clist_set_text(GTK_CLIST(p->clist[1]),i*SecElementNum+j,1,p->pp ); 
		}
   }

    
   gtk_clist_thaw(GTK_CLIST(p->clist[0]));
   gtk_clist_thaw(GTK_CLIST(p->clist[1]));

}

void CurrentFocallaw(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    gint i;
    p->CurrentNum = gtk_combo_box_get_active(GTK_COMBO_BOX(p->combo));
    
    for(i=0;i<p->k+1;i++)
    {
       if(i == p->CurrentNum )
       {
          p->final_num = i ;  
       } 
    }
    if( p->is_draw_focus)
        InsertElementDelay(p);
    force_updata(p);
}

void show_action (GtkAction *action,gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data); 
    gtk_widget_show_all(p->ScrooledWindow); 
    force_updata(p);
    p->show_hide = 1 ;
}
void hide_action (GtkAction *action,gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   gtk_widget_hide_all(p->ScrooledWindow);
   force_updata(p);
   p->show_hide = 0 ;
}


/*创建状态栏*/
GtkWidget *CreateStasteBar(DRAW_UI_P p)
{
    p->status_bar = gtk_statusbar_new();
    p->context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(p->status_bar),"Doppler's Calculator");
    gtk_statusbar_push(GTK_STATUSBAR(p->status_bar),p->context_id,"Doppler's Calculator");
    
    gtk_widget_show (p->status_bar);
    return  p->status_bar ;
}

void WarnningDialog (DRAW_UI_P p)
{
  GtkWidget *dialog;
  
  dialog = gtk_message_dialog_new (GTK_WINDOW (p->window),
                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_INFO,
                                   GTK_BUTTONS_CLOSE,
                                   "For laws no beam convergence is possible at the given setup",
                                    NULL, NULL);

  g_signal_connect (dialog,
                    "response",
                    G_CALLBACK (gtk_widget_destroy),
                    NULL);
  
  gtk_widget_show (dialog); 
}

//**********************************************************
//            设置背景图片 
//**********************************************************
void update_widget_bg(GtkWidget *widget, const gchar *img_file)
{       
GtkStyle *style;     
GdkPixbuf *pixbuf;       
GdkPixmap *pixmap;     
gint width, height;    

pixbuf = gdk_pixbuf_new_from_file(img_file, NULL);    
width = gdk_pixbuf_get_width(pixbuf);   
height = gdk_pixbuf_get_height(pixbuf);    
pixmap = gdk_pixmap_new(NULL, width, height, 24);   
gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, NULL, 0);
style = gtk_style_copy(GTK_WIDGET (widget)->style);    

if (style->bg_pixmap[GTK_STATE_NORMAL])        
    g_object_unref(style->bg_pixmap[GTK_STATE_NORMAL]);    

style->bg_pixmap[GTK_STATE_NORMAL] = g_object_ref(pixmap);    
style->bg_pixmap[GTK_STATE_ACTIVE] = g_object_ref(pixmap);
style->bg_pixmap[GTK_STATE_PRELIGHT] = g_object_ref(pixmap);
style->bg_pixmap[GTK_STATE_SELECTED] = g_object_ref(pixmap);
style->bg_pixmap[GTK_STATE_INSENSITIVE] = g_object_ref(pixmap);
gtk_widget_set_style(GTK_WIDGET (widget), style);
g_object_unref(style);
}


//**************************************************
//  Name:  database-------probe
//  Copyright: Dopplor 
//  Author: He Fan
//  Date: 20-04-21 10:30
//**************************************************
void probe_import(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   GtkWidget *vbox;
   GtkWidget *hbox;
   GtkWidget *label;
   GtkWidget *button[2];
   
   
   p->window_db = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(p->window_db),"UT Database");
   gtk_widget_set_size_request(GTK_WIDGET(p->window_db),700,400);
   gtk_window_set_position(GTK_WINDOW(p->window_db),GTK_WIN_POS_CENTER);
   gtk_window_set_transient_for(GTK_WINDOW(p->window_db), GTK_WINDOW(p->window));//与主窗口关联 
   gtk_window_set_resizable(GTK_WINDOW(p->window_db), FALSE);//禁止最大化
   gtk_window_set_modal (GTK_WINDOW(p->window_db), TRUE);//激活该窗口禁止主窗口 
   
   
   vbox = gtk_vbox_new (FALSE, 0);
   gtk_container_add (GTK_CONTAINER (p->window_db), vbox);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   label = gtk_label_new("Configration name");
   p->entry_db_probe = gtk_entry_new(); 
   gtk_entry_set_text(GTK_ENTRY(p->entry_db_probe),"Default");
   gtk_widget_set_sensitive (p->entry_db_probe, FALSE);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(label),FALSE,FALSE,2);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(p->entry_db_probe),FALSE,FALSE,5);
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(do_list_store(p)),TRUE,TRUE,5);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   button[0] = gtk_button_new_with_label("Import");
   update_widget_bg(button[0], "./image/bg.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[0]),50,35);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(button[0]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[0]),"clicked",G_CALLBACK(db_probe_import),(gpointer) (p));
   //
   button[1] = gtk_button_new_with_label("Cancel");
//   update_widget_bg(button[1], "./image/import.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[1]),50,35);
   gtk_box_pack_end(GTK_BOX(hbox),GTK_WIDGET(button[1]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[1]),"clicked",G_CALLBACK(db_probe_cancel),(gpointer) (p));
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   
   gtk_widget_show_all(p->window_db); 
}
void probe_export(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   GtkWidget *vbox;
   GtkWidget *hbox;
   GtkWidget *label;
   GtkWidget *button[2];
   
   
   p->window_db = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(p->window_db),"UT Database");
   gtk_widget_set_size_request(GTK_WIDGET(p->window_db),700,400);
   gtk_window_set_position(GTK_WINDOW(p->window_db),GTK_WIN_POS_CENTER);
   gtk_window_set_transient_for(GTK_WINDOW(p->window_db), GTK_WINDOW(p->window));//与主窗口关联 
   gtk_window_set_resizable(GTK_WINDOW(p->window_db), FALSE);//禁止最大化
   gtk_window_set_modal (GTK_WINDOW(p->window_db), TRUE);//激活该窗口禁止主窗口 
   
   
   vbox = gtk_vbox_new (FALSE, 0);
   gtk_container_add (GTK_CONTAINER (p->window_db), vbox);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   label = gtk_label_new("Configration name");
   p->entry_db_probe = gtk_entry_new(); 
   gtk_entry_set_text(GTK_ENTRY(p->entry_db_probe),"Default");
   gtk_widget_set_sensitive (p->entry_db_probe, FALSE);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(label),FALSE,FALSE,2);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(p->entry_db_probe),FALSE,FALSE,5);
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(do_list_store(p)),TRUE,TRUE,5);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   button[0] = gtk_button_new_with_label("Export");
   update_widget_bg(button[0], "./image/bg.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[0]),50,35);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(button[0]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[0]),"clicked",G_CALLBACK(db_probe_export),(gpointer) (p));
   //
   button[1] = gtk_button_new_with_label("Cancel");
//   update_widget_bg(button[1], "./image/import.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[1]),50,35);
   gtk_box_pack_end(GTK_BOX(hbox),GTK_WIDGET(button[1]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[1]),"clicked",G_CALLBACK(db_probe_cancel),(gpointer) (p));
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   
   gtk_widget_show_all(p->window_db); 
}
void probe_delete(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   GtkWidget *vbox;
   GtkWidget *hbox;
   GtkWidget *label;
   GtkWidget *button[2];
   
   
   p->window_db = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(p->window_db),"UT Database");
   gtk_widget_set_size_request(GTK_WIDGET(p->window_db),700,400);
   gtk_window_set_position(GTK_WINDOW(p->window_db),GTK_WIN_POS_CENTER);
   gtk_window_set_transient_for(GTK_WINDOW(p->window_db), GTK_WINDOW(p->window));//与主窗口关联 
   gtk_window_set_resizable(GTK_WINDOW(p->window_db), FALSE);//禁止最大化
   gtk_window_set_modal (GTK_WINDOW(p->window_db), TRUE);//激活该窗口禁止主窗口 
   
   
   vbox = gtk_vbox_new (FALSE, 0);
   gtk_container_add (GTK_CONTAINER (p->window_db), vbox);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   label = gtk_label_new("Configration name");
   p->entry_db_probe = gtk_entry_new(); 
   gtk_entry_set_text(GTK_ENTRY(p->entry_db_probe),"Default");
   gtk_widget_set_sensitive (p->entry_db_probe, FALSE);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(label),FALSE,FALSE,2);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(p->entry_db_probe),FALSE,FALSE,5);
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(do_list_store(p)),TRUE,TRUE,5);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   button[0] = gtk_button_new_with_label("Delete");
   update_widget_bg(button[0], "./image/bg.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[0]),50,35);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(button[0]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[0]),"clicked",G_CALLBACK(db_probe_delete),(gpointer) (p));
   //
   button[1] = gtk_button_new_with_label("Cancel");
//   update_widget_bg(button[1], "./image/import.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[1]),50,35);
   gtk_box_pack_end(GTK_BOX(hbox),GTK_WIDGET(button[1]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[1]),"clicked",G_CALLBACK(db_probe_cancel),(gpointer) (p));
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   
   gtk_widget_show_all(p->window_db); 
}
//**************************************************
//  Name:  database-------wedge
//  Copyright: Dopplor 
//  Author: He Fan
//  Date: 20-04-22 15:30
//**************************************************
void wedge_import(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   GtkWidget *vbox;
   GtkWidget *hbox;
   GtkWidget *label;
   GtkWidget *button[2];
   
   
   p->window_db = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(p->window_db),"UT Database");
   gtk_widget_set_size_request(GTK_WIDGET(p->window_db),700,400);
   gtk_window_set_position(GTK_WINDOW(p->window_db),GTK_WIN_POS_CENTER);
   gtk_window_set_transient_for(GTK_WINDOW(p->window_db), GTK_WINDOW(p->window));//与主窗口关联 
   gtk_window_set_resizable(GTK_WINDOW(p->window_db), FALSE);//禁止最大化
   gtk_window_set_modal (GTK_WINDOW(p->window_db), TRUE);//激活该窗口禁止主窗口 
   
   
   vbox = gtk_vbox_new (FALSE, 0);
   gtk_container_add (GTK_CONTAINER (p->window_db), vbox);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   label = gtk_label_new("Configration name");
   p->entry_db_wedge = gtk_entry_new(); 
   gtk_entry_set_text(GTK_ENTRY(p->entry_db_wedge),"Default");
   gtk_widget_set_size_request(GTK_WIDGET(p->entry_db_wedge),250,25);
   gtk_widget_set_sensitive (p->entry_db_wedge, FALSE);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(label),FALSE,FALSE,2);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(p->entry_db_wedge),FALSE,FALSE,5);
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(do_list_store(p)),TRUE,TRUE,5);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   button[0] = gtk_button_new_with_label("Import");
   update_widget_bg(button[0], "./image/bg.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[0]),50,35);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(button[0]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[0]),"clicked",G_CALLBACK(db_wedge_import),(gpointer) (p));
   //
   button[1] = gtk_button_new_with_label("Cancel");
//   update_widget_bg(button[1], "./image/import.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[1]),50,35);
   gtk_box_pack_end(GTK_BOX(hbox),GTK_WIDGET(button[1]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[1]),"clicked",G_CALLBACK(db_wedge_cancel),(gpointer) (p));
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   
   gtk_widget_show_all(p->window_db); 
}
void wedge_export(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   GtkWidget *vbox;
   GtkWidget *hbox;
   GtkWidget *label;
   GtkWidget *button[2];
   
   
   p->window_db = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(p->window_db),"UT Database");
   gtk_widget_set_size_request(GTK_WIDGET(p->window_db),700,400);
   gtk_window_set_position(GTK_WINDOW(p->window_db),GTK_WIN_POS_CENTER);
   gtk_window_set_transient_for(GTK_WINDOW(p->window_db), GTK_WINDOW(p->window));//与主窗口关联 
   gtk_window_set_resizable(GTK_WINDOW(p->window_db), FALSE);//禁止最大化
   gtk_window_set_modal (GTK_WINDOW(p->window_db), TRUE);//激活该窗口禁止主窗口 
   
   
   vbox = gtk_vbox_new (FALSE, 0);
   gtk_container_add (GTK_CONTAINER (p->window_db), vbox);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   label = gtk_label_new("Configration name");
   p->entry_db_wedge = gtk_entry_new(); 
   gtk_entry_set_text(GTK_ENTRY(p->entry_db_wedge),"Default");
   gtk_widget_set_size_request(GTK_WIDGET(p->entry_db_wedge),250,25);
   gtk_widget_set_sensitive (p->entry_db_wedge, FALSE);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(label),FALSE,FALSE,2);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(p->entry_db_wedge),FALSE,FALSE,5);
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(do_list_store(p)),TRUE,TRUE,5);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   button[0] = gtk_button_new_with_label("Export");
   update_widget_bg(button[0], "./image/bg.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[0]),50,35);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(button[0]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[0]),"clicked",G_CALLBACK(db_wedge_export),(gpointer) (p));
   //
   button[1] = gtk_button_new_with_label("Cancel");
//   update_widget_bg(button[1], "./image/import.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[1]),50,35);
   gtk_box_pack_end(GTK_BOX(hbox),GTK_WIDGET(button[1]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[1]),"clicked",G_CALLBACK(db_wedge_cancel),(gpointer) (p));
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   
   gtk_widget_show_all(p->window_db); 
}
void wedge_delete(GtkWidget *widget, gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   GtkWidget *vbox;
   GtkWidget *hbox;
   GtkWidget *label;
   GtkWidget *button[2];
   
   
   p->window_db = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(p->window_db),"UT Database");
   gtk_widget_set_size_request(GTK_WIDGET(p->window_db),700,400);
   gtk_window_set_position(GTK_WINDOW(p->window_db),GTK_WIN_POS_CENTER);
   gtk_window_set_transient_for(GTK_WINDOW(p->window_db), GTK_WINDOW(p->window));//与主窗口关联 
   gtk_window_set_resizable(GTK_WINDOW(p->window_db), FALSE);//禁止最大化
   gtk_window_set_modal (GTK_WINDOW(p->window_db), TRUE);//激活该窗口禁止主窗口 
   
   
   vbox = gtk_vbox_new (FALSE, 0);
   gtk_container_add (GTK_CONTAINER (p->window_db), vbox);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   label = gtk_label_new("Configration name");
   p->entry_db_wedge = gtk_entry_new(); 
   gtk_entry_set_text(GTK_ENTRY(p->entry_db_wedge),"Default");
   gtk_widget_set_size_request(GTK_WIDGET(p->entry_db_wedge),250,25);
   gtk_widget_set_sensitive (p->entry_db_wedge, FALSE);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(label),FALSE,FALSE,2);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(p->entry_db_wedge),FALSE,FALSE,5);
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(do_list_store(p)),TRUE,TRUE,5);
   //
   hbox = gtk_hbox_new (FALSE, 0);
   button[0] = gtk_button_new_with_label("Delete");
   update_widget_bg(button[0], "./image/bg.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[0]),50,35);
   gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(button[0]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[0]),"clicked",G_CALLBACK(db_wedge_delete),(gpointer) (p));
   //
   button[1] = gtk_button_new_with_label("Cancel");
//   update_widget_bg(button[1], "./image/import.jpg");
   gtk_widget_set_size_request(GTK_WIDGET(button[1]),50,35);
   gtk_box_pack_end(GTK_BOX(hbox),GTK_WIDGET(button[1]),FALSE,FALSE,2);
   g_signal_connect(G_OBJECT(button[1]),"clicked",G_CALLBACK(db_wedge_cancel),(gpointer) (p));
   //
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(hbox),FALSE,FALSE,5);
   
   gtk_widget_show_all(p->window_db); 
}

//********************************************
//  Name:  create_model
//  Copyright: Dopplor 
//  Author: He Fan
//  Date: 20-04-11 10:30
//********************************************
GtkTreeModel *create_model (gpointer data)
{
  DRAW_UI_P p = (DRAW_UI_P)(data);
  
  gint i = 0;
  GtkTreeIter iter;
  
  if(!strcmp(p->pos,"Probe"))
  {
      //create list store 
      p->store = gtk_list_store_new (10,
    			      G_TYPE_INT,   G_TYPE_STRING, G_TYPE_DOUBLE,
                      G_TYPE_DOUBLE,G_TYPE_INT,    G_TYPE_DOUBLE,   
                      G_TYPE_DOUBLE,G_TYPE_INT,    G_TYPE_DOUBLE,
                      G_TYPE_DOUBLE);
    
      // add data to the list store
      for (i = 0; i < G_N_ELEMENTS (p->db_probe); i++)
        {
          gtk_list_store_append (p->store, &iter);
          gtk_list_store_set (p->store, &iter,
    			  0, p->db_probe[i]->db_index,      1, p->db_probe[i]->name,          2, p->db_probe[i]->skewangle,   
                  3, p->db_probe[i]->frequency,     4, p->db_probe[i]->number_pri,    5, p->db_probe[i]->pri_axis_pitch,  
                  6, p->db_probe[i]->pri_ele_size,  7, p->db_probe[i]->number_sec,    8, p->db_probe[i]->sec_axis_pitch,
                  9, p->db_probe[i]->sec_ele_size,  -1);
        } 
  }
  else if(!strcmp(p->pos,"Wedge"))
  {
      //create list store 
      p->store = gtk_list_store_new (8,
    			      G_TYPE_INT,    G_TYPE_STRING, G_TYPE_DOUBLE,
                      G_TYPE_DOUBLE, G_TYPE_DOUBLE, G_TYPE_DOUBLE,
                      G_TYPE_DOUBLE, G_TYPE_DOUBLE );
    
      // add data to the list store
      for (i = 0; i < G_N_ELEMENTS (p->db_wedge); i++)
        {
          gtk_list_store_append (p->store, &iter);
          gtk_list_store_set (p->store, &iter,
    			  0, p->db_wedge[i]->db_index,      1, p->db_wedge[i]->name,       2, p->db_wedge[i]->wedge_angle,   
                  3, p->db_wedge[i]->roof_angle,    4, p->db_wedge[i]->vel_longi,  5, p->db_wedge[i]->height,        
                  6, p->db_wedge[i]->first_offset,  7, p->db_wedge[i]->sec_offset,
                  -1);
        } 
  }
      

  return GTK_TREE_MODEL (p->store);
}
//********************************************
//  Name:  add_columns
//  Copyright: Dopplor 
//  Author: He Fan
//  Date: 20-04-11 10:30
//********************************************
void add_columns_probe (GtkTreeView *treeview, gpointer data )
{
  DRAW_UI_P p = (DRAW_UI_P)(data);
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkTreeModel *model = gtk_tree_view_get_model (treeview);
  

  //0 
  renderer = gtk_cell_renderer_text_new ();		    
  column = gtk_tree_view_column_new_with_attributes ("Index",
                             renderer,
						     "text",
                             0,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 0);
  gtk_tree_view_append_column (treeview, column);
  //1 
  renderer = gtk_cell_renderer_text_new ();		    
  column = gtk_tree_view_column_new_with_attributes ("    Name",
                             renderer,
						     "text",
                             1,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 1);
  gtk_tree_view_append_column (treeview, column);
  //2 
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("Skew angle\n   (deg)",
						     renderer,
						     "text",
						     2,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 2);
  gtk_tree_view_append_column (treeview, column);
  //3 
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("Frequency\n  (MHz)",
						     renderer,
						     "text",
						     3,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 3);
  gtk_tree_view_append_column (treeview, column);
  //4 
  renderer = gtk_cell_renderer_text_new ();		    
  column = gtk_tree_view_column_new_with_attributes ("  Number of\n element on\n  primary\n   axis",
                             renderer,
						     "text",
                             4,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 4);
  gtk_tree_view_append_column (treeview, column);
  //5 
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("  Primary\naxis pitch\n   (mm)",
						     renderer,
						     "text",
						     5,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 5);
  gtk_tree_view_append_column (treeview, column);
  //6 
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("  Primary\nelement size\n   (mm)",
						     renderer,
						     "text",
						     6,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 6);
  gtk_tree_view_append_column (treeview, column);
  //7 
  renderer = gtk_cell_renderer_text_new ();		    
  column = gtk_tree_view_column_new_with_attributes ("  Number of\n element on\n  secondary\n   axis",
                             renderer,
						     "text",
                             7,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 7);
  gtk_tree_view_append_column (treeview, column);
  //8 
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("  Secondary\naxis pitch\n   (mm)",
						     renderer,
						     "text",
						     8,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 8);
  gtk_tree_view_append_column (treeview, column);
  //9 
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("  Secondary\nelement size\n   (mm)",
						     renderer,
						     "text",
						     9,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 9);
  gtk_tree_view_append_column (treeview, column);
}
//
void add_columns_wedge (GtkTreeView *treeview, gpointer data )
{
  DRAW_UI_P p = (DRAW_UI_P)(data);
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkTreeModel *model = gtk_tree_view_get_model (treeview);
  

  //0 
  renderer = gtk_cell_renderer_text_new ();		    
  column = gtk_tree_view_column_new_with_attributes ("Index",
                             renderer,
						     "text",
                             0,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 0);
  gtk_tree_view_append_column (treeview, column);
  //1 
  renderer = gtk_cell_renderer_text_new ();		    
  column = gtk_tree_view_column_new_with_attributes ("    Name",
                             renderer,
						     "text",
                             1,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 1);
  gtk_tree_view_append_column (treeview, column);
  //2 
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("Wedge angle\n  (deg)",
						     renderer,
						     "text",
						     2,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 2);
  gtk_tree_view_append_column (treeview, column);
  //3 
  renderer = gtk_cell_renderer_text_new ();		    
  column = gtk_tree_view_column_new_with_attributes ("Roof angle\n   (deg)",
                             renderer,
						     "text",
                             3,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 3);
  gtk_tree_view_append_column (treeview, column);
  //4 
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("Sound velocity\nlongitudinal\n    (m/s)",
						     renderer,
						     "text",
						     4,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 4);
  gtk_tree_view_append_column (treeview, column);
  //5 
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("Height at the\nmiddle of the\nfirst element\n    (mm)",
						     renderer,
						     "text",
						     5,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 5);
  gtk_tree_view_append_column (treeview, column);
  //6 
  renderer = gtk_cell_renderer_text_new ();		    
  column = gtk_tree_view_column_new_with_attributes ("Primary axis offset\nof the middle of\nthe first element\n      (mm)",
                             renderer,
						     "text",
                             6,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 6);
  gtk_tree_view_append_column (treeview, column);
  //7 
  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes ("Secondary axis offset\nof the middle of\nthe first element\n      (mm)",
						     renderer,
						     "text",
						     7,
						     NULL);
  gtk_tree_view_column_set_sort_column_id (column, 7);
  gtk_tree_view_append_column (treeview, column);
  
}
//********************************************
//  Name:  do_list_store
//  Copyright: Dopplor 
//  Author: He Fan
//  Date: 20-04-11 10:30
//********************************************
GtkWidget *do_list_store (gpointer data)
{
      DRAW_UI_P p = (DRAW_UI_P)(data);
      
      GtkWidget *sw;      
      GtkTreeSelection *selection;      

      sw = gtk_scrolled_window_new (NULL, NULL);
      gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

      // create tree view 
      p->treeview = gtk_tree_view_new_with_model ( create_model(p) );      
      g_object_unref ( create_model(p) );
      gtk_container_add (GTK_CONTAINER (sw), p->treeview);
      // add columns to the tree view 
      if(!strcmp(p->pos,"Probe"))
            add_columns_probe (GTK_TREE_VIEW (p->treeview),(gpointer)p );
      else if(!strcmp(p->pos,"Wedge"))
            add_columns_wedge (GTK_TREE_VIEW (p->treeview),(gpointer)p );

      selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (p->treeview));    
      g_signal_connect (selection,"changed",G_CALLBACK (selection_changed),(gpointer)p );
			
      return sw;
}
//********************************************
//  Name:  selection_changed
//  Copyright: Dopplor 
//  Author: He Fan
//  Date: 20-04-11 10:30
//********************************************
void selection_changed(GtkTreeSelection *selection, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     
     GtkTreeView *treeView;    
     GtkTreeModel *model; 
     GtkTreeIter iter;      
     gchar *active;      
     
     treeView = gtk_tree_selection_get_tree_view(selection);    
     model = gtk_tree_view_get_model(treeView);    
     gtk_tree_selection_get_selected(selection, &model, &iter);    
     //get name
     gtk_tree_model_get(model, &iter,1, &active,-1);
     //get index
     gtk_tree_model_get(model, &iter,0, &p->db_count,-1);    

     if(!strcmp(p->pos,"Probe"))
            gtk_entry_set_text(GTK_ENTRY(p->entry_db_probe),active);
     else if(!strcmp(p->pos,"Wedge"))
            gtk_entry_set_text(GTK_ENTRY(p->entry_db_wedge),active);
}
//********************************************
//  Name:  db_probe
//  Copyright: Dopplor 
//  Author: He Fan
//  Date: 20-04-11 10:30
//********************************************
void db_probe_import(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    //加载probe配置
    strcpy( p->probe_p->name, p->db_probe[p->db_count]->name );     
    p->probe_p->pb_skew_angle  = p->db_probe[p->db_count]->skewangle; 
    p->probe_p->pb_frequency   = p->db_probe[p->db_count]->frequency;
    p->probe_p->ele_num_pri    = p->db_probe[p->db_count]->number_pri; 
    p->probe_p->ele_num_sec    = p->db_probe[p->db_count]->number_sec; 
    p->probe_p->pri_axis_pitch = p->db_probe[p->db_count]->pri_axis_pitch;
    p->probe_p->sec_axis_pitch = p->db_probe[p->db_count]->sec_axis_pitch; 
    p->probe_p->pri_ele_size   = p->db_probe[p->db_count]->pri_ele_size; 
    p->probe_p->sec_ele_size   = p->db_probe[p->db_count]->sec_ele_size;
    
    gtk_entry_set_text(GTK_ENTRY(p->entry[1]),p->probe_p->name);
    gtk_entry_set_text(GTK_ENTRY(p->entry[2]),p->probe_p->name);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[3]),p->probe_p->pb_skew_angle);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[4]),p->probe_p->pb_skew_angle);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[5]),p->probe_p->pb_frequency);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[6]),p->probe_p->pb_frequency);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[7]),p->probe_p->ele_num_pri);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[8]),p->probe_p->ele_num_pri);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[9]),p->probe_p->pri_axis_pitch);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[10]),p->probe_p->pri_axis_pitch);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[11]),p->probe_p->pri_ele_size);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[12]),p->probe_p->pri_ele_size);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[13]),p->probe_p->sec_ele_size);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[14]),p->probe_p->sec_ele_size);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[15]),p->probe_p->ele_num_sec);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[16]),p->probe_p->ele_num_sec);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[17]),p->probe_p->sec_axis_pitch);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry[18]),p->probe_p->sec_axis_pitch);
    
    gtk_widget_destroy (p->window_db);
}
//
void db_probe_export(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    
}
//
void db_probe_delete(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    GtkTreeIter iter;
    gboolean valid;
    gint count;
    
    p->store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(p->treeview)));    
    if(gtk_tree_model_iter_nth_child(GTK_TREE_MODEL(p->store),&iter,NULL,p->db_count+1) )
    {
        gtk_list_store_remove(GTK_LIST_STORE(p->store), &iter);
    }
/*   
    valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(p->store), &iter);
    while(valid)
    {
        gtk_tree_model_get(GTK_TREE_MODEL(p->store),&iter,0,&count,-1);
        if(count == p->db_count) 
        {   
//            gtk_list_store_clear(GTK_LIST_STORE(p->store));
//            gtk_list_store_remove(GTK_LIST_STORE(p->store), &iter);
            break;
        }
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(p->store), &iter);//先判断是否到结尾
      }
*/ 
    
}
//
void db_probe_cancel(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    gtk_widget_destroy (p->window_db);
}
//********************************************
//  Name:  db_wedge
//  Copyright: Dopplor 
//  Author: He Fan
//  Date: 20-04-22 16:00
//********************************************
void db_wedge_import(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    //加载wedge配置
    strcpy( p->wedge_p->name, p->db_wedge[p->db_count]->name );
    p->wedge_p->wg_wedge_angle = p->db_wedge[p->db_count]->wedge_angle;
    p->wedge_p->wg_roof_angle  = p->db_wedge[p->db_count]->roof_angle ;
    p->wedge_p->wg_lon_vel     = p->db_wedge[p->db_count]->vel_longi  ;
    p->wedge_p->wg_heigh_fir   = p->db_wedge[p->db_count]->height     ;
    p->wedge_p->wg_pri_elem_offset_fir =  p->db_wedge[p->db_count]->first_offset ;
    p->wedge_p->wg_sec_elem_offset_fir =  p->db_wedge[p->db_count]->sec_offset   ;                
       
    gtk_entry_set_text(GTK_ENTRY(p->entry_wg[0]),p->wedge_p->name);
    gtk_entry_set_text(GTK_ENTRY(p->entry_wg[1]),p->wedge_p->name);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[2]),p->wedge_p->wg_wedge_angle);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[3]),p->wedge_p->wg_wedge_angle);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[4]),p->wedge_p->wg_roof_angle);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[5]),p->wedge_p->wg_roof_angle);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[6]),p->wedge_p->wg_lon_vel);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[7]),p->wedge_p->wg_lon_vel);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[12]),p->wedge_p->wg_heigh_fir);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[13]),p->wedge_p->wg_heigh_fir);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[14]),p->wedge_p->wg_pri_elem_offset_fir);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[15]),p->wedge_p->wg_pri_elem_offset_fir);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[16]),p->wedge_p->wg_sec_elem_offset_fir);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(p->entry_wg[17]),p->wedge_p->wg_sec_elem_offset_fir);
    
    gtk_widget_destroy (p->window_db);
}
void db_wedge_export(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    
}
void db_wedge_delete(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    
}
void db_wedge_cancel(GtkWidget *widget, gpointer data)
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    gtk_widget_destroy (p->window_db);    
}
//********************************************
//  Name:  三维视图 
//  Copyright: Dopplor 
//  Author: He Fan
//  Date: 20-04-22 16:00
//********************************************
void view_left(GtkWidget *widget, gpointer data)//drawingarea 0
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    gint i;
    for(i=0;i<4;i++)
        gtk_widget_hide_all(p->drawing_area[i]);
    p->view = 0;
    gtk_widget_show_all(p->drawing_area[0]);
}
void view_front(GtkWidget *widget, gpointer data)//drawingarea 1
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    gint i;
    for(i=0;i<4;i++)
        gtk_widget_hide_all(p->drawing_area[i]);  
    p->view = 1;
    gtk_widget_show_all(p->drawing_area[1]);      
} 
void view_top(GtkWidget *widget, gpointer data)//drawingarea 2
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    gint i;
    for(i=0;i<4;i++)
        gtk_widget_hide_all(p->drawing_area[i]);  
    p->view = 2;
    gtk_widget_show_all(p->drawing_area[2]);      
}
void view_3D(GtkWidget *widget, gpointer data)//drawingarea 3
{
    DRAW_UI_P p = (DRAW_UI_P)(data);
    gint i;
    for(i=0;i<4;i++)
        gtk_widget_hide_all(p->drawing_area[i]);  
    p->view = 3;
    gtk_widget_show_all(p->drawing_area[3]);     
} 
//********************************************
//  Name:  force_updata强制刷新opengl 
//  Copyright: Dopplor 
//  Author: He Fan
//  Date: 20-04-22 16:00
//********************************************
void force_updata(gpointer data)
{
   DRAW_UI_P p = (DRAW_UI_P)(data);
   
   gtk_widget_queue_draw (p->drawing_area[0]);
   gtk_widget_queue_draw (p->drawing_area[1]);
   gtk_widget_queue_draw (p->drawing_area[2]);
   gtk_widget_queue_draw (p->drawing_area[3]);   
}
