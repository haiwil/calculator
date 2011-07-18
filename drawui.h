/************************************************* 
            定义主界面相关数据结构 
 ************************************************* */
 
#ifndef	__DRAW_UI_H_
#define	__DRAW_UI_H_
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <string.h>
#include <stdio.h>
#include "datastruct.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <gdk/gdkkeysyms.h>

#ifdef G_OS_WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

#define elements_num 512
#define TRUE_DEPTH	24
#define db_num_probe 37
#define db_num_wedge 99
#define material_num 24

extern gdouble spinx,spiny,spinz, xScale,yScale,zScale, xTranslate,yTranslate,zTranslate;
extern gdouble pre_point_x,pre_point_y,xBegin,yBegin;
/*画界面结构体*/
typedef struct Draw_interface
{
    GtkWidget *window;
    GtkWidget *hpaned;
    GtkWidget *vpaned;
    GtkWidget *hpaned_sub;
    GtkWidget *btn_run;
    GtkAdjustment* adj;
    /*聚焦参数*/
    PROBE_P        probe_p;
    WEDGE_P        wedge_p;
    WEDGE_P        wedge_r;
    BEAM_ANGLE_P   beam_angle;
    SPECIMEN_P     specimen;
    FOCAL_POINT_P  focal_point;
    LOCATION_P     location;
    PROJECT_P      project;
    SCANNER_P      scanner;
    ELEMENT_SEL_P  element_sel;
    DB_PROBE_P     db_probe[db_num_probe];
    DB_WEDGE_P     db_wedge[db_num_wedge];
    MATERIAL_P     material[material_num];
    /*beam配置文件 参数*/
    FILE *fp;
    FILE *stream;
    FILE *focal_law_data;
    LAW     law[elements_num];
    ELEMENT element[elements_num][100][32];
    GtkWidget *filechooser;
    GtkWidget *dialog;
    /*阵元延时信息*/
    GtkWidget *ScrooledWindow;
    GtkWidget *hbox_delay;
    GtkWidget *combo;
    GtkWidget *clist[2];
    gdouble CurrentNum;
    gboolean show_hide;
    // 
    GtkWidget *status_bar;
    gint context_id;
    /*延时变量 */
    gdouble timedelay[elements_num][elements_num];
    gdouble G_Time[elements_num];
    gchar pp[elements_num] ;
    /* database */
    GtkWidget *entry_db_probe;
    GtkWidget *entry_db_wedge;
    GtkWidget *window_db;
    GtkWidget *treeview;
    GtkListStore *store;
    gint db_count;
    
    GtkWidget *entry_material[5];
    /* 绘图opengl */
    gboolean is_draw_focus;//是否绘制焦点 
    gint view;//选择视图所用的 计数器 
    GtkWidget *drawing_area[4];
    GdkGLConfig *glconfig;
    gint k;//聚焦计算时点的序号 
    gint tmp_k;//循环时需要 
    gint del_k;//循环时需要 
    gint final_num;//最终画点的序号 
    gboolean DrawResult;
    GLdouble focus_x[elements_num];/*聚焦点坐标 */
    GLdouble focus_y[elements_num];/*聚焦点坐标*/
    GLdouble focus_z[elements_num];/*聚焦点坐标*/
    GLdouble probe_x[elements_num][elements_num];/*阵元坐标*/
    GLdouble probe_y[elements_num][elements_num];/*阵元坐标*/
    GLdouble probe_z[elements_num][elements_num];/*阵元坐标*/
    GLdouble horizontal_x[elements_num][elements_num];/*入射点坐标 */
    GLdouble horizontal_y[elements_num][elements_num];/*入射点坐标 */
    GLdouble horizontal_z[elements_num][elements_num];/*入射点坐标 */
    //接收探头
    GLdouble focus_xr[elements_num];/*聚焦点坐标 */
	GLdouble focus_yr[elements_num];/*聚焦点坐标 */
	GLdouble focus_zr[elements_num];/*聚焦点坐标 */
	GLdouble probe_xr[elements_num][elements_num];/*阵元坐标*/
    GLdouble probe_yr[elements_num][elements_num];/*阵元坐标*/
    GLdouble probe_zr[elements_num][elements_num];/*阵元坐标*/
    GLdouble horizontal_xr[elements_num][elements_num];/*入射点坐标 */
    GLdouble horizontal_yr[elements_num][elements_num];/*入射点坐标 */
    GLdouble horizontal_zr[elements_num][elements_num];/*入射点坐标 */
    /*左下窗口变量*/
    GtkWidget *left_down_window;
    GtkWidget *vbox_ldw;
    gchar *pos;//
    /*Hard Selection*/
    GtkWidget *hbox_h_ldw[7];
    GtkWidget *vbox_h_ldw1[7];
    GtkWidget *vbox_h_ldw2[7];
    GtkWidget *label_ldw[7];
    GtkWidget *text[7];
    gchar *parament[7];
    gchar *label[7];
    /*probe*/
    GtkWidget *frame_ps;
    GtkWidget *linear_wg[3];//1D or 2D
    GtkWidget *entry[20];
    GtkWidget *label_p;
    GtkWidget *check_btn_p[5];
    GtkWidget *SequenceComm[2];  // add by WolfLord for 2D sequence widget
    GtkWidget *D2ShowHBox[5];
    GtkWidget *database_btn[3];
    /**/
    GtkWidget *frame;
    GtkWidget *hbox_wg;
    GtkWidget *vbox_wg;
    /*wedge*/
    GtkWidget *label_wg;
    GtkWidget *label_wg_l;
    GtkWidget *flat_wg;
    GtkWidget *entry_wg[28];
    GtkWidget *btn_wg;
    GtkWidget *database_btn_wg[3];
    gint footprint;
    /*scanner*/
    GtkWidget *frame_g;
    GtkWidget *frame_pof;
    GtkWidget *frame_por;
    GtkWidget *label_g;
    GtkWidget *label_g_l;
    GtkWidget *grp_num;
    GtkWidget *entry_sc[6];
    /*Beam angle selection*/
    GtkWidget *label_beam;
    GtkWidget *label_beam1;
    GtkWidget *label_beam2;
    GtkWidget *label_beam3;
    GtkWidget *combox_beam[2];
    GtkWidget *entry_beam[12];
    GtkWidget *btn_beam;
    /*Focal point selection*/
    GtkWidget *label_focal;
    GtkWidget *label_focal1;
    GtkWidget *label_focal2;
    GtkWidget *label_focal3;
    GtkWidget *combox_focal;
    GtkWidget *frame_focal;
    GtkWidget *check_focal;
    GtkWidget *entry_foc[9];
    /*element selection*/
    gboolean  selection;
    GtkWidget *frame_elem;
    GtkWidget *label_elem1;
    GtkWidget *label_elem2;
    GtkWidget *label_elem3;
    GtkWidget *label_elem4;
    GtkWidget *entry_elem[18];
    GtkWidget *entry_beam1;
    GtkWidget *entry_beam2;
    GtkWidget *entry_beam3;
    /*paramenter*/
    GtkWidget *frame_pra1;
    GtkWidget *frame_pra2;
    GtkWidget *frame_pra3;
    GtkWidget *label_pra1;
    GtkWidget *label_pra2;
    GtkWidget *entry_pra;
    GtkWidget *entry_pra1;
    GtkWidget *btn_pra1;
    GtkWidget *btn_pra2;
    GtkWidget *check_btn_pra1;
    GtkWidget *check_btn_pra2;
    GtkWidget *check_btn_pra3;
    GtkWidget *check_btn_pra4;
    /*extent*/
    GtkWidget *label_extent1;
    GtkWidget *label_extent2;
    GtkWidget *label_extent3;
    GtkWidget *label_extent4;
    GtkWidget *chk_btn_extent;
    GtkWidget *entry_extent1;
    GtkWidget *entry_extent2;
    GtkWidget *entry_extent3;
    GtkWidget *entry_extent4;
    GtkWidget *frame_extent1;
    GtkWidget *frame_extent2;
    GtkWidget *radio_btn_extent1;
    GtkWidget *radio_btn_extent2;
    GtkWidget *radio_btn_extent3;
    GtkWidget *radio_btn_extent4;
    GtkWidget *radio_btn_extent5;
    GtkWidget *btn_extent;
    GtkWidget *combox_extent;
    /*definition*/
    GtkWidget *label_def[14];
    GtkWidget *entry_def[10];
    GtkWidget *combox_def;
    GtkWidget *hbox_wg_f[3];
    GtkWidget *hbox_wg_c[3];
    /*location*/
    GtkWidget *frame_loca[3];
    GtkWidget *label_loca[2];
    GtkWidget *entry_loca[9];
    GtkWidget *combo_loca[3];
    /*projected sequence*/
    GtkWidget *label_pro[2];
    GtkWidget *combo_pro[3];
    GtkWidget *entry_pro;
    GtkWidget *radio_pro[3];             
}DRAW_UI, *DRAW_UI_P;

 /*Hard Selection*/
static gchar *Hd_select_parament[7]=
{
    "256","256","4096","yes","16384","65535","200"
};
static gchar *Hd_select_label[7]=
{
    "Maximum number of active pulsers:  ",
    "Maximum number of active receivers:",
    "Maximum number of focal laws:      ",
    "DDF available:                     ",
    "DDF,maximum number of points:      ",
    "Maximum element delay:             ",
    "Default pulser voltage:            "   
};


/*------函数声明------*/
GtkWidget *init_ui(DRAW_UI_P p);//初始化主界面
GtkWidget *create_draw_area0(DRAW_UI_P p);/*创建绘图区域*/
GtkWidget *create_draw_area1(DRAW_UI_P p);/*创建绘图区域*/
GtkWidget *create_draw_area2(DRAW_UI_P p);/*创建绘图区域*/
GtkWidget *create_draw_area3(DRAW_UI_P p);/*创建绘图区域*/
GtkWidget *init_left_down_window(DRAW_UI_P p);/*初始化左下窗口*/
GtkWidget *do_appwindow(DRAW_UI_P p);/*快捷菜单栏创建函数*/
GtkWidget *ShowElementDelay(DRAW_UI_P p);/*阵元延时显示函数*/
GtkWidget *ShowElementDelay_time(DRAW_UI_P p);/*阵元延时显示函数*/
GtkWidget *InsertElementDelay(DRAW_UI_P p);/*实时更新阵元延时函数*/
void CurrentFocallaw(GtkWidget *widget, gpointer data);/* 阵元信息回调函数 */
GtkWidget *InsertCurrentFocallaw(DRAW_UI_P p);
GtkWidget *CreateStasteBar(DRAW_UI_P p);/*创建状态栏*/
void WarnningDialog (DRAW_UI_P p);/* 警告对话框 */
void activate_action (GtkAction *action,gpointer data);
void show_action (GtkAction *action,gpointer data);
void hide_action (GtkAction *action,gpointer data);
void about(GtkWidget *widget, gpointer data);
void update_widget_bg(GtkWidget *widget, const gchar *img_file);/*设置背景图片*/
void register_stock_icons (void);
/*viewport*/
void view_left(GtkWidget *widget, gpointer data);//左视图 
void view_front(GtkWidget *widget, gpointer data);//Z主视图 
void view_top(GtkWidget *widget, gpointer data);//俯视图 
void view_3D(GtkWidget *widget, gpointer data);//三位视图 
/*database*/
void probe_import(GtkWidget *widget, gpointer data);
void probe_export(GtkWidget *widget, gpointer data);
void probe_delete(GtkWidget *widget, gpointer data);
void wedge_import(GtkWidget *widget, gpointer data);
void wedge_export(GtkWidget *widget, gpointer data);
void wedge_delete(GtkWidget *widget, gpointer data);

GtkTreeModel *create_model (gpointer data);
void add_columns_probe (GtkTreeView *treeview, gpointer data );
void add_columns_wedge (GtkTreeView *treeview, gpointer data );
GtkWidget *do_list_store (gpointer data);
void selection_changed(GtkTreeSelection *selection, gpointer data);
//
void db_probe_import(GtkWidget *widget, gpointer data);
void db_probe_export(GtkWidget *widget, gpointer data);
void db_probe_delete(GtkWidget *widget, gpointer data);
void db_probe_cancel(GtkWidget *widget, gpointer data);
//
void db_wedge_import(GtkWidget *widget, gpointer data);
void db_wedge_export(GtkWidget *widget, gpointer data);
void db_wedge_delete(GtkWidget *widget, gpointer data);
void db_wedge_cancel(GtkWidget *widget, gpointer data);
/*------外部函数声明------*/
extern GtkWidget *create_tree_left (DRAW_UI_P p);/*创建左上树形数据窗口*/ 
extern GtkWidget *create_tree_right(DRAW_UI_P p);/*创建右上树形数据窗口*/

/*------OpenGL外部函数声明------*/
extern void realize (GtkWidget *widget,gpointer   data);
extern gboolean configure_event (GtkWidget *widget,GdkEventConfigure *event, gpointer data);
extern gboolean expose_event (GtkWidget *widget,GdkEventExpose *event, gpointer data);
extern gboolean expose_event_3d (GtkWidget *widget,GdkEventExpose *event, gpointer data);
extern gboolean key_press_event (GtkWidget *widget,GdkEventKey *event,gpointer data);
extern gboolean scroll_event (GtkWidget *widget,GdkEventScroll *event,gpointer data);
extern gboolean button_press_event (GtkWidget *widget,GdkEventButton *event,gpointer data);
extern gboolean motion_notify_event(GtkWidget *widget,GdkEventMotion *event,gpointer data);

void force_updata(gpointer data);//gtk控件值发生改变时，强制刷新opengl 

extern void focal_law(GtkWidget *widget, gpointer data);
/* 聚焦法则保存为.law文件 */
extern void save(GtkWidget *widget,gpointer data);/*聚焦法则计算结果保存为一个文件*/
extern void open(GtkWidget *widget,gpointer data);/*读取一个聚焦法则文件(.law)*/

/*beam配置文件保存*/
extern void save_beam_setup(GtkWidget *widget,gpointer data);
extern void save_as_beam_setup(GtkWidget *widget,gpointer data);
extern void load_beam_setup(GtkWidget *widget,gpointer data);
/*.law文件保存*/
extern void save_law(GtkWidget *widget,gpointer data);
extern void save_as_law(GtkWidget *widget,gpointer data);

#endif
