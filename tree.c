/************************************************* 
                    树形视图 
 ************************************************* */
 
#include "drawui.h"

/*树形结构信号回调函数声明*/
void item_signal_0(GtkWidget *treeitem, gpointer data);
void item_signal_1(GtkWidget *treeitem, gpointer data);
void item_signal_2(GtkWidget *treeitem, gpointer data);
void item_signal_3(GtkWidget *treeitem, gpointer data);
void item_signal_4(GtkWidget *treeitem, gpointer data);
void item_signal_5(GtkWidget *treeitem, gpointer data);
void item_signal_6(GtkWidget *treeitem, gpointer data);
void item_signal_7(GtkWidget *treeitem, gpointer data);
void item_signal_8(GtkWidget *treeitem, gpointer data);
void item_signal_9(GtkWidget *treeitem, gpointer data);
void item_signal_10(GtkWidget *treeitem, gpointer data);
void item_signal_11(GtkWidget *treeitem, gpointer data);

GtkWidget *create_tree_left (DRAW_UI_P p);/*创建左上树形数据窗口*/ 
GtkWidget *create_tree_right(DRAW_UI_P p);/*创建右上树形数据窗口*/
extern void draw_menu(DRAW_UI_P p);
extern void focal_law(GtkWidget *widget, gpointer data);/*聚焦算法实现*/

/*创建左上树形数据窗口*/
GtkWidget *create_tree_left(DRAW_UI_P p)
{
    GtkWidget *tree;
    GtkWidget *tree_item;
    GtkWidget *subtree;
    GtkWidget *subtree1;
    GtkWidget *subtree_item;
    GtkWidget *scrolled_window;   
    
    /*设置滚动窗口*/
   scrolled_window=gtk_scrolled_window_new(NULL,NULL);
   gtk_container_set_border_width(GTK_CONTAINER(scrolled_window),10);
   gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
   gtk_widget_set_size_request(GTK_WIDGET(scrolled_window),210,190);
   
   tree=GTK_WIDGET(gtk_tree_new());
   gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),tree);
   tree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Hardware selection"));
   gtk_tree_append(tree,tree_item);
   /*为树项创建子树*/
   subtree=GTK_WIDGET(gtk_tree_new());
   gtk_tree_item_set_subtree(tree_item,subtree);
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Hardware selection"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_0),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_0),(gpointer) (p));
   gtk_tree_item_expand(tree_item);//将树项展开 
   gtk_tree_append(subtree,subtree_item);
   gtk_widget_show(subtree_item);
   
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Probe"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_1),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_1),(gpointer) (p));
   gtk_tree_append(subtree,subtree_item);
   gtk_widget_show(subtree_item);
   
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Wedge"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_2),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_2),(gpointer) (p));
   gtk_tree_append(subtree,subtree_item);
   gtk_widget_show(subtree_item);

   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Scanner"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_3),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_3),(gpointer) (p));
   gtk_tree_append(subtree,subtree_item);
   gtk_widget_show(subtree_item);
   
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Beam selection"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_4),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_4),(gpointer) (p));
   gtk_tree_append(subtree,subtree_item);
   gtk_widget_show(subtree_item);
   //
   subtree1=GTK_WIDGET(gtk_tree_new());
   gtk_tree_item_set_subtree(subtree_item,subtree1);
   gtk_tree_item_expand(subtree_item);//将树项展开 
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Beam angle selection"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_4),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_4),(gpointer) (p));  
   gtk_tree_append(subtree1,subtree_item);
   gtk_widget_show(subtree_item);
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Focal point selection"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_5),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_5),(gpointer) (p));
   gtk_tree_append(subtree1,subtree_item);
   gtk_widget_show(subtree_item);
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Element selection"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_6),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_6),(gpointer) (p));
   gtk_tree_append(subtree1,subtree_item);
   gtk_widget_show(subtree_item);
   
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Beam simulation"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_7),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_7),(gpointer) (p));
   gtk_tree_append(subtree,subtree_item);
   gtk_widget_show(subtree_item);
   //
   subtree1=GTK_WIDGET(gtk_tree_new());
   gtk_tree_item_set_subtree(subtree_item,subtree1);
   gtk_tree_item_expand(subtree_item);//将树项展开
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Paramenter"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_7),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_7),(gpointer) (p));
   gtk_tree_append(subtree1,subtree_item);
   gtk_widget_show(subtree_item);
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Exent"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_8),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_8),(gpointer) (p));
   gtk_tree_append(subtree1,subtree_item);
   gtk_widget_show(subtree_item);
   
   gtk_widget_show_all(scrolled_window);
   
   return scrolled_window;      
}

/*创建右上树形数据窗口*/
GtkWidget *create_tree_right(DRAW_UI_P p)
{
    GtkWidget *tree;
    GtkWidget *tree_item;
    GtkWidget *subtree;
    GtkWidget *subtree_item;
    GtkWidget *scrolled_window;  
    GtkWidget *vbox; 
    
    /*设置滚动窗口*/
   scrolled_window=gtk_scrolled_window_new(NULL,NULL);
   gtk_container_set_border_width(GTK_CONTAINER(scrolled_window),10);
   gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
   gtk_widget_set_size_request(GTK_WIDGET(scrolled_window),190,190);
   vbox=gtk_vbox_new(FALSE,0);
   gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window),vbox);
   //
   tree=GTK_WIDGET(gtk_tree_new());
   gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(tree),FALSE,FALSE,5);
   tree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Specimen Settings"));
   gtk_tree_append(tree,tree_item);
   /*为树项创建子树*/
   subtree=GTK_WIDGET(gtk_tree_new());
   gtk_tree_item_set_subtree(tree_item,subtree);
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Definition"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_9),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_9),(gpointer) (p));
   gtk_tree_item_expand(tree_item);//将树项展开 
   gtk_tree_append(subtree,subtree_item);
   gtk_widget_show(subtree_item);
   
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Location"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_10),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_10),(gpointer) (p));
   gtk_tree_append(subtree,subtree_item);
   gtk_widget_show(subtree_item);
   
   subtree_item=GTK_WIDGET(gtk_tree_item_new_with_label("Projected Sequence"));
   g_signal_connect(G_OBJECT(subtree_item),"select",GTK_SIGNAL_FUNC(item_signal_11),(gpointer) (p));
   g_signal_connect(G_OBJECT(subtree_item),"toggle",GTK_SIGNAL_FUNC(item_signal_11),(gpointer) (p));
   gtk_tree_append(subtree,subtree_item);
   gtk_widget_show(subtree_item); 
   
//   p->btn_run=gtk_button_new_with_label(g_locale_to_utf8("开始[Run]",-1,NULL,NULL,NULL));
//   gtk_box_pack_end(GTK_BOX(vbox),GTK_WIDGET(p->btn_run),FALSE,FALSE,0);
//   g_signal_connect(G_OBJECT(p->btn_run),"clicked",G_CALLBACK(focal_law),(gpointer) (p));  
   
   gtk_widget_show_all(scrolled_window);
   return scrolled_window;       
}

void item_signal_0(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->pos="Hardware selection";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}

void item_signal_1(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->pos="Probe";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}

void item_signal_2(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->pos="Wedge";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}

void item_signal_3(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->pos="Scanner";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}

void item_signal_4(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->pos="Beam angle selection";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}

void item_signal_5(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);   
     p->pos="Focal point selection";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}

void item_signal_6(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->pos="Element selection";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}

void item_signal_7(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->pos="Paramenter";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}

void item_signal_8(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->pos="Exent";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}

void item_signal_9(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->pos="Definition";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}

void item_signal_10(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->pos="Location";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}

void item_signal_11(GtkWidget *treeitem, gpointer data)
{
     DRAW_UI_P p = (DRAW_UI_P)(data);
     p->pos="Projected Sequence";
     //g_printf("%s is clicked \n",p->pos);
     draw_menu(p);
}
