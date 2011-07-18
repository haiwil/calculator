/************************************************* 
               何凡
               2011.01.10
 ************************************************* */

#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include "drawui.h"


/*OpenGL Global Variable*/
GLdouble spinx,spiny,spinz, xScale,yScale,zScale, xTranslate,yTranslate,zTranslate;
GLdouble pre_point_x,pre_point_y,xBegin,yBegin;

int main(int argc,char* argv[])
{
    GtkWidget *window;
    GtkWidget *vbox;
    GdkGLConfig *glconfig;
    gint i,j;
    DRAW_UI_P  p_ui;
    /*---全局变量数据声明并初始化---*/   
#if 1   
    PROBE probe_p ={0,0,0,0,  0.0,5.00,32,4,1.00,10.00,1.00,10.00,  0.0,5.00,32,4,1.00,10.00,1.00,10.00, "Default"};
    WEDGE wedge_p={36.0,0.0,2330,1157,1049,12.00,9.00,15.50,-116.50,-15.50,66.50,31.00,40.00,50, "Default"};
    WEDGE wedge_r={36.0,0.0,2330,1157,1049,12.00,9.00,15.50,-116.50,-15.50,66.50,31.00,40.00,50, "Default"};
    SCANNER scanner={ 0.0,0.0,0.0, 0.0,0.0,0.0 };
    BEAM_ANGLE beam_angle={0.0,0.0,1.0,  0.0,0.0,1.0,  40.0,70.0,10.0,  0.0,0.0,1.0 ,0,0};
    SPECIMEN specimen={"Default","Steel" ,5920,3230,  250.00,50.00,250.00,   400.00,500.00,300.00, 0 ,"OD"};
    FOCAL_POINT  focal_point={ 1 ,100.0,100.0,100.0  ,20,10,0,20};
    ELEMENT_SEL  element_sel={1,1,1, 1,1,1,   32,1,1, 0 };
    LOCATION location={0.00,0.00,0.00, 0.0,0.0,90.0, 0.00,0.00,0.00,  0,1,2 };
    PROJECT  project={ 1 ,TRUE};
    DB_PROBE db_probe[] = 
    {
        {0,	"2.25L32E45-22",  	0,	2.25,  32,	1.406,  1.406,  1,  22,   22},                                                                                                                                                                                                                                                                        
        {1,	"5L32E32-10",	   	0,	5,     32,  1,      1,      1,  10,   10},                                                                                                                                                                                                                                                                            
        {2,	"5L64E64-10",	   	0,	5,     64,  1,      1,      1,  10,   10},                                                                                                                                                                                                                                                                            
        {3,	"10L32E10-7",	   	0,	10,    32,	0.313,  0.313,  1,  7,    7},                                                                                                                                                                                                                                                                              
        {4,	"2L16-A1",	       	0,	2.25,  16,	0.75,   0.75,   1,  12,   12},                                                                                                                                                                                                                                                                               
        {5,	"5L16-A1",	       	0,	5,     16,	0.6,    0.6,    1,  10,   10},                                                                                                                                                                                                                                                                                    
        {6,	"10L32-A1",	        0,	10,    32,	0.31,   0.31,   1,  7,    7},                                                                                                                                                                                                                                                                                   
        {7,	"2L64-A2",	       	0,	2.25,  64,	0.75,   0.75,   1,  12,   12},                                                                                                                                                                                                                                                                                
        {8,	"5L64-A2" ,    	    0,	5,     64,	0.6,    0.6,    1,  10,   10},                                                                                                                                                                                                                                                                                    
        {9,	"5L16-C2",	       	0,	5,     16,	0.6,    0.6,    1,  10,   10},                                                                                                                                                                                                                                                                                    
        {10,"5L64-I1",	       	0,	5,     64,	0.6,    0.6,    1,  10,   10},                                                                                                                                                                                                                                                                                   
        {11,"10L16E4-4",	    0,	10,    16,	0.25,   0.25,   1,  4,    4},                                                                                                                                                                                                                                                                                   
        {12,"5L10-A0",	       	0,	5,     10,	0.6,    0.6,    1,  6,    6},                                                                                                                                                                                                                                                                                       
        {13,"10L16E7.2-7.2",  	0,	10,    16,	0.41,   0.41,   1,  7.2,  7.2},                                                                                                                                                                                                                                                                             
        {14,"5L12E7.2-7.2",	    0,	5,     12,	0.6,    0.6,    1,  7.2,  7.2},                                                                                                                                                                                                                                                                               
        {15,"7.5L60E60-10",	    0,	7.5,   60,	1,      1,      1,  10,   10},                                                                                                                                                                                                                                                                             
        {16,"5L28E14-6",	    0,	5,     28,	0.5,    0.5,    1,  6,    6},                                                                                                                                                                                                                                                                                     
        {17,"5L12E6-6",	        0,	5,     12,	0.5,    0.5,    1,  6,    6},                                                                                                                                                                                                                                                                                     
        {18,"2.25L32E32-15",	0,	2.25,  32,	1,      1,      1,  15,   15},                                                                                                                                                                                                                                                                           
        {19,"5L16E20-15",	   	0,	5,     16,	1.25,   1.25,   1,  15,   15},                                                                                                                                                                                                                                                                             
        {20,"7.5L12E7.2-7.2",	0,	7.5,   12,	0.6,    0.6,    1,  7.2,  7.2},                                                                                                                                                                                                                                                                           
        {21,"10L28E7-7",     	0,	10,    28,	0.25,   0.25,   1,  7,    7},                                                                                                                                                                                                                                                                                   
        {22,"5L24E10-7",	    0,	5,     24,	0.42,   0.42,   1,  7,    7},                                                                                                                                                                                                                                                                                     
        {23,"10L16-A00",	    0,	10,    16,	0.31,   0.31,   1,  5,    5},                                                                                                                                                                                                                                                                                   
        {24,"10L10-A0",	        0,	10,    10,	0.6,    0.6,    1,  6,    6},                                                                                                                                                                                                                                                                                   
        {25,"10L64-A2",	        0,	10,    64,	0.6,    0.6,    1,  7,    7},                                                                                                                                                                                                                                                                                   
        {26,"3.5L16-A3",	    0,	3.5,   16,	1.6,    1.6,    1,  16,   16},                                                                                                                                                                                                                                                                               
        {27,"5L16-A3",	       	0,	5,     16,	1.2,    1.2,    1,  12,   12},                                                                                                                                                                                                                                                                                   
        {28,"1.5L16-A4",	    0,	1.5,   16,	2.8,    2.8,    1,  26,   26},                                                                                                                                                                                                                                                                               
        {29,"2.25L16-A4",	   	0,	2.25,  16,	2,      2,      1,  20,   20},                                                                                                                                                                                                                                                                             
        {30,"2.25L32-A5",	   	0,	2.25,  32,	0.75,   0.75,   1,  24,   24},                                                                                                                                                                                                                                                                            
        {31,"5L32-A5",	       	0,	5,     32,	0.6,    0.6,    1,  20,   20},                                                                                                                                                                                                                                                                                    
        {32,"10L64-I1",	        0,	10,    64,	0.5,    0.5,    1,  10,   10},                                                                                                                                                                                                                                                                                
        {33,"5L128-I2",	        0,	5,     128,	0.6,    0.6,    1,  10,   10},                                                                                                                                                                                                                                                                                  
        {34,"10L128-I2",      	0,	10,    128,	0.5,    0.5,    1,  7,    7},                                                                                                                                                                                                                                                                                   
        {35,"2L128-I3",	        0,	2.25,  128,	0.75,   0.75,   1,  12,   12},                                                                                                                                                                                                                                                                              
        {36,"5L128-I3",	        0,	5,     128,	0.75,   0.75,   1,  10,   10}
    };
    DB_WEDGE  db_wedge[] = 
    {
        {	0 ,  "ABWXE012a (5L12E7.2-7.2; 10L16E7.2-7.2)",  34  ,  0,   1157,  3.84,  1.24,  10  },
        {	1 ,  "ABWXE013a (2.25L32E45-22)              ",  31  ,  0,   1157,  24  ,  7   ,  22  },
        {	2 ,  "ABWXE014a (2.25L32E45-22)              ",  16  ,  0,   1157,  35  ,  7   ,  22  },
        {	3 ,  "ABWXE015a (5L64E64-10)                 ",  31  ,  0,   1157,  17.5,  6   ,  17.5},
        {	4 ,  "ABWXE016a (5L64E64-10)                 ",  16  ,  0,   1157,  25  ,  7   ,  17.5},
        {	5 ,  "ABWXE017a (7.5L60E60-10)               ",  31  ,  0,   1157,  17  ,  8   ,  17.5},
        {	6 ,  "ABWXE018a (7.5L60E60-10)               ",  16  ,  0,   1157,  25  ,  8   ,  17.5},
        {	7 ,  "ABWXE019a (5L32E32-10)                 ",  36  ,  0,   1157,  12  ,  9   ,  15.5},
        {	8 ,  "ABWXE020a (SA2-N45S)                   ",  31  ,  0,   1157,  7   ,  3.6 ,  15  },
        {	9 ,  "ABWXE021a (10L32E10-7)                 ",  31  ,  0,   1157,  7   ,  11  ,  15.5},
        {	10,  "ABWXE022a (10L16E4-4)                  ",  31  ,  0,   1157,  4   ,  4   ,  10  },
        {	11,  "ABWXE023a (SA1-N60S)                   ",  39  ,  0,   1157,  5   ,  3.1 ,  15  },
        {	12,  "ABWXE024a (SA1-N45L)                   ",  16  ,  0,   1157,  19  ,  3.7 ,  15  },
        {	13,  "ABWXE025a (SA1-N60L- short)            ",  20  ,  0,   1157,  19  ,  3.7 ,  15  },
        {	14,  "ABWXE029a (SA1-N45S)                   ",  31  ,  0,   1157,  7   ,  3   ,  15  },
        {	15,  "ABWXE030a (2.25L32E32-15)              ",  31.8,  0,   1157,  15  ,  5   ,  18  },
        {	16,  "ABWXE031a (2.25L32E32-15)              ",  27.5,  0,   1157,  10  ,  5   ,  18  },
        {	17,  "ABWXE035a (2.25L32E45-22)              ",  36  ,  0,   1157,  9   ,  7   ,  22  },
        {	18,  "ABWXE038a (SA2-N60L)                   ",  20  ,  0,   1157,  15  ,  3.7 ,  15  },
        {	19,  "ABWXE039a (5L16E20-15)                 ",  38  ,  0,   1157,  8   ,  6.4 ,  22  },
        {	20,  "ABWXE048a (SA1-N60L)                   ",  20  ,  0,   1157,  14.5,  3.7 ,  15  },
        {	21,  "ABWXE052a (SA2-N45L)                   ",  16  ,  0,   1157,  19  ,  3.8 ,  15  },
        {	22,  "ABWXE053a (SA2-N60S)                   ",  39  ,  0,   1157,  5   ,  3   ,  15  },
        {	23,  "ABWXE054a (SA2-0L)                     ",  0   ,  0,   1157,  20  ,  10.9,  15  },
        {	24,  "ABWXE061a (SA1-0L)                     ",  0   ,  0,   1157,  20  ,  6   ,  15  },
        {	25,  "ABWXE082a (5L32E32-10)                 ",  19  ,  0,   1157,  6   ,  7.5 ,  15.5},
        {	26,  "ABWXE083a (10L28E7-7)                  ",  31  ,  0,   1157,  4   ,  2   ,  10  },
        {	27,  "ABWXE084a (5L24E10-7)                  ",  31  ,  0,   1157,  5.5 ,  4.2 ,  15.5},
        {	28,  "SA00-0L                                ",  0   ,  0,   1157,  5   ,  5.7 ,  6   },
        {	29,  "SA0-0L                                 ",  0   ,  0,   1157,  10  ,  8.5 ,  6.2 },
        {	30,  "SA00-N45S                              ",  31  ,  0,   1157,  2.6 ,  6.7 ,  6   },
        {	31,  "SA00-N60S                              ",  39  ,  0,   1157,  2.2 ,  7.3 ,  7   },
        {	32,  "SA0-N45L                               ",  16  ,  0,   1157,  11.9,  11.5,  5.7 },
        {	33,  "SA0-N45S                               ",  31  ,  0,   1157,  7.3 ,  10.7,  5.7 },
        {	34,  "SA0-N60S                               ",  39  ,  0,   1157,  6.3 ,  10.6,  5.7 },
        {	35,  "SA1-0L                                 ",  0   ,  0,   1157,  20  ,  8.9 ,  15  },
        {	36,  "SA1-N45L                               ",  16  ,  0,   1157,  19  ,  3.8 ,  15  },
        {	37,  "SA1-N45L-IHC                           ",  16  ,  0,   1157,  19  ,  3.8 ,  20  },
        {	38,  "SA1-N45S                               ",  31  ,  0,   1157,  8   ,  3.4 ,  15  },
        {	39,  "SA1-N45S-IHC                           ",  31  ,  0,   1157,  8   ,  3.4 ,  20  },
        {	40,  "SA2-N55S DUAL 2L64                     ",  36  ,  0,   1157,  5.4 ,  4   ,  15  },
        {	41,  "SA1-N60S-IHC                           ",  39  ,  0,   1157,  5   ,  3   ,  20  },
        {	42,  "SA1-N60S                               ",  39  ,  0,   1157,  5   ,  3   ,  15  },
        {	43,  "SA1-N60L-IHC                           ",  20  ,  0,   1157,  14.5,  3.7 ,  20  },
        {	44,  "SA1-N60L                               ",  20  ,  0,   1157,  14.5,  3.7 ,  15  },
        {	45,  "SA2-0L                                 ",  0   ,  0,   1157,  20  ,  8.9 ,  15  },
        {	46,  "SA2-N45S-IHC                           ",  31  ,  0,   1157,  7   ,  3.3 ,  20  },
        {	47,  "SA2-N45S                               ",  31  ,  0,   1157,  7   ,  3.3 ,  15  },
        {	48,  "SA2-N45L-IHC                           ",  16  ,  0,   1157,  19  ,  3.8 ,  20  },
        {	49,  "SA2-N45L                               ",  16  ,  0,   1157,  19  ,  3.8 ,  15  },
        {	50,  "SA2-N55S DUAL 5L64                     ",  36  ,  0,   1157,  11  ,  11.7,  15  },
        {	51,  "SA2-N55S-IHC DUAL 2L64                 ",  36  ,  0,   1157,  5.4 ,  4   ,  20  },
        {	52,  "SA2-N55S-IHC DUAL 5L64                 ",  36  ,  0,   1157,  11  ,  11.7,  20  },
        {	53,  "SA2-N60S-IHC                           ",  39  ,  0,   1157,  5.7 ,  3.9 ,  20  },
        {	54,  "SA2-N60S                               ",  39  ,  0,   1157,  5   ,  3   ,  15  },
        {	55,  "SA2-N60L-IHC                           ",  20  ,  0,   1157,  15  ,  3.7 ,  20  },
        {	56,  "SA2-N60L-IHC DUAL 2L64                 ",  20  ,  0,   1157,  27.8,  3.8 ,  20  },
        {	57,  "SA2-N60L-IHC DUAL 5L64                 ",  20  ,  0,   1157,  34.1,  13.6,  20  },
        {	58,  "Sl3-0L-IHC 2L128                       ",  0   ,  0,   1157,  20  ,  9.2 ,  18.5},
        {	59,  "Sl2-N45S-IHC 5L128                     ",  31  ,  0,   1157,  4.7 ,  4.7 ,  22.5},
        {	60,  "Sl2-N45S-IHC 10L128                    ",  31  ,  0,   1157,  8   ,  10.2,  22.5},
        {	61,  "Sl2-N45L-IHC 5L128                     ",  16  ,  0,   1157,  26.5,  4.7 ,  22.5},
        {	62,  "Sl2-N45L-IHC 10L128                    ",  16  ,  0,   1157,  28.2,  10.9,  22.5},
        {	63,  "Sl2-0L-IHC 10L128                      ",  0   ,  0,   1157,  20  ,  15.7,  18.5},
        {	64,  "Sl2-0L-IHC 5L128                       ",  0   ,  0,   1157,  20  ,  9.3 ,  18.5},
        {	65,  "Sl1-N45L-IHC 5L64                      ",  16  ,  0,   1157,  14.8,  7.3 ,  22.5},
        {	66,  "Sl1-N45L-IHC 10L64                     ",  16  ,  0,   1157,  15.7,  10.4,  22.5},
        {	67,  "SA3-0L-IHC 3L16                        ",  0   ,  0,   1157,  20  ,  6.9 ,  25  },
        {	68,  "SA3-0L-IHC 5L16                        ",  0   ,  0,   1157,  20  ,  7.3 ,  25  },
        {	69,  "SA3-N45S-IHC 3L16                      ",  31  ,  0,   1157,  16.8,  8.5 ,  20  },
        {	70,  "SA3-N45L-IHC 3L16                      ",  16  ,  0,   1157,  39.1,  6.6 ,  25  },
        {	71,  "SA3-N45S-IHC 5L16                      ",  31  ,  0,   1157,  17  ,  8.9 ,  20  },
        {	72,  "SA3-N45L-IHC 5L16                      ",  16  ,  0,   1157,  39.2,  7   ,  25  },
        {	73,  "SA3-N60S-IHC 3L16                      ",  39  ,  0,   1157,  7.6 ,  5.7 ,  25  },
        {	74,  "SA3-N60S-IHC 5L16                      ",  39  ,  0,   1157,  7.6 ,  6   ,  25  },
        {	75,  "SA3-N60L-IHC 3L16                      ",  20  ,  0,   1157,  28.3,  6.5 ,  25  },
        {	76,  "SA3-N60L-IHC 5L16                      ",  20  ,  0,   1157,  28.4,  6.9 ,  25  },
        {	77,  "SA4-0L-IHC 1L16                        ",  0   ,  0,   1157,  20  ,  8.7 ,  27.5},
        {	78,  "SA4-0L-IHC 2L16                        ",  0   ,  0,   1157,  20  ,  8.5 ,  27.5},
        {	79,  "SA4-N45S-IHC 1L16                      ",  31  ,  0,   1157,  19.9,  7.5 ,  27.5},
        {	80,  "SA4-N45S-IHC 2L16                      ",  31  ,  0,   1157,  19.8,  7.3 ,  27.5},
        {	81,  "SA4-N45L-IHC 1L16                      ",  16  ,  0,   1157,  68.6,  8.4 ,  27.5},
        {	82,  "SA4-N45L-IHC 2L16                      ",  16  ,  0,   1157,  68.5,  8.2 ,  27.5},
        {	83,  "SA4-N60S-IHC 1L16                      ",  39  ,  0,   1157,  8.7 ,  6.3 ,  27.5},
        {	84,  "SA4-N60S-IHC 2L16                      ",  39  ,  0,   1157,  8   ,  6.1 ,  27.5},
        {	85,  "SA4-N60L-IHC 1L16                      ",  20  ,  0,   1157,  49.8,  8.2 ,  27.5},
        {	86,  "SA4-N60L-IHC 2L16                      ",  20  ,  0,   1157,  49.7,  8   ,  27.5},
        {	87,  "SA5-0L-IHC                             ",  0   ,  0,   1157,  20  ,  7   ,  23.3},
        {	88,  "SA5-N45S-IHC                           ",  31  ,  0,   1157,  17.9,  2.5 ,  27.8},
        {	89,  "SA5-N60S-IHC                           ",  39  ,  0,   1157,  6.6 ,  2.3 ,  27.8},
        {	90,  "SA5-N60L-IHC                           ",  20  ,  0,   1157,  32  ,  2.8 ,  25  },
        {	91,  "Sl1-0L-IHC 10L64                       ",  0   ,  0,   1157,  20  ,  15.2,  20  },
        {	92,  "Sl1-0L-IHC 5L64                        ",  0   ,  0,   1157,  20  ,  12  ,  20  },
        {	93,  "Sl1-N45S-IHC 10L64                     ",  31  ,  0,   1157,  7.6 ,  9.7 ,  22.5},
        {	94,  "Sl1-N45S-IHC 5L64                      ",  31  ,  0,   1157,  6   ,  7   ,  22.5},
        {	95,  "SA1-L45L-IHC                           ",  0   ,  16,  1157,  37.6,  16.9,  16.3},
        {	96,  "SA1-L45L                               ",  0   ,  16,  1157,  37.6,  16.9,  16.3},
        {	97,  "SA1-L45S                               ",  0   ,  31,  1157,  18  ,  16.9,  14.6},
        {	98,  "SA1-L45S-IHC                           ",  0   ,  31,  1157,  18  ,  16.9,  14.6},
    };
    MATERIAL     material[] = 
    {
        {0,  "Aluminium",    "Solid",  6320, 3130, 2700},
        {1,  "Brass",        "Solid",  4400, 2200, 8400},
        {2,  "Copper",       "Solid",  4700, 2260, 8900},
        {3,  "Glass(crown)", "Solid",  5660, 3420, 2500},
        {4,  "Glass(flint)", "Solid",  4260, 2560, 3600},
        {5,  "Glycerine",    "Liquid", 1920, 1,    1260},
        {6,  "Gold",         "Solid",  3240, 1200, 19300},
        {7,  "kerosine",     "Liquid", 1324, 1   , 810},
        {8,  "Lead",         "Solid",  2160, 700 , 11400},
        {9,  "Nickel",       "Solid",  5630, 2960, 8800},
        {10, "Oil mineral",  "Liquid", 1440, 1,    825},
        {11, "Oil SAE 20",   "Liquid", 1740, 1,    870},
        {12, "Oil silicon",  "Liquid", 960,  1,    818},
        {13, "Platinum",     "Solid",  3960, 1670, 21400},
        {14, "Plexiglass",   "Solid",  2730, 1430, 1180}, 
        {15, "Quartz glass", "Solid",  5570, 3520, 2600},
        {16, "Rexolite",     "Solid",  2330, 1157, 1049},
        {17, "Silver",       "Solid",  3600, 1590, 10500},
        {18, "Steel(carbon)","Solid",  5920, 3230, 7850},
        {19, "Steel(stainless)","Solid",5770, 3150, 7850},
        {20, "Tin",             "Solid",3320, 1670, 7300},
        {21, "Tungsten",        "Solid",5460, 2620, 19100},
        {22, "Water(20 C)",    "Liquid",1483, 1   ,1000},
        {23,  "Zinc",           "Solid", 4170, 2410,7100}       
    };
         
#else
    PROBE probe_p ={0,0,0,0,  0.0,5.00,32,4,1.00,10.00,1.00,10.00,  0.0,5.00,32,4,1.00,10.00,1.00,10.00};
    WEDGE wedge_p={36.0,0.0,2330,1157,1049,12.00,9.00,15.50,-116.50,-15.50,66.50,31.00,40.00,50};
    WEDGE wedge_r={36.0,0.0,2330,1157,1049,12.00,9.00,15.50,-116.50,-15.50,66.50,31.00,40.00,50};
    SCANNER scanner={ 0.0,0.0,0.0, 0.0,0.0,0.0 };
    BEAM_ANGLE beam_angle={0.0,0.0,1.0,  0.0,0.0,1.0,  40.0,70.0,10.0,  0.0,0.0,1.0 ,0,0};
    SPECIMEN specimen={5920,3230,  250.00,50.00,250.00,   400.00,500.00,300.00, 0 ,"OD"};
    FOCAL_POINT  focal_point={ 1 ,20.0,20.0,20.0  ,20,10,0,20};
    ELEMENT_SEL  element_sel={1,1,1, 1,1,1,   32,1,1, 0 };
    LOCATION location={0.00,0.00,0.00, 0.0,0.0,90.0, 0.00,0.00,0.00,  0,1,2 };
    PROJECT  project={ 1 ,TRUE};
#endif
    spinx=spiny=spinz=0.0f;
    xScale=yScale=zScale=1.0f;
    xTranslate=yTranslate=zTranslate=0.0f;
    xBegin=yBegin=0.0f;
               
    gtk_init(&argc,&argv);
    gtk_gl_init (&argc, &argv);

    p_ui=(DRAW_UI_P)g_malloc0(sizeof(DRAW_UI));
    glconfig = gdk_gl_config_new_by_mode (GDK_GL_MODE_RGB |GDK_GL_MODE_DEPTH |GDK_GL_MODE_DOUBLE);
    
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),g_locale_to_utf8( "计算器[Calculator]",-1,NULL,NULL,NULL));
    gtk_window_set_icon_from_file (GTK_WINDOW(window),"./image/doppler.ico",NULL) ;
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    /* 获取屏幕大小 */
    GdkScreen* screen; 
    gint width, height; 
    screen = gdk_screen_get_default(); 
    width = gdk_screen_get_width(screen); 
    height = gdk_screen_get_height(screen); 
    gtk_widget_set_size_request(window, width, height);
    gtk_widget_set_size_request(GTK_WIDGET(window),0.8*width,0.8*height);
    
    /* Get automatically redrawn if any of their children changed allocation. */
    gtk_container_set_reallocate_redraws (GTK_CONTAINER (window), TRUE);
    
    /* 
    g_printf("*****功能快捷键*****\n");
    g_printf("鼠标左键：旋转 \n鼠标右键：移动 \n");
    g_printf("鼠标中键：恢复初始状态 \n鼠标滚轮：缩放 \n");
    g_printf("Run/F9 :聚焦法则\n");
    g_printf("*****功能快捷键*****\n");*/
    
    p_ui->window=window;
    p_ui->glconfig=glconfig;
    p_ui->probe_p=&probe_p;/*探头*/
    p_ui->wedge_p=&wedge_p;/*楔块*/
    p_ui->wedge_r=&wedge_r;/*楔块*/
    p_ui->beam_angle=&beam_angle;/*声束角*/
    p_ui->specimen=&specimen;/*样本参数*/
    p_ui->focal_point=&focal_point;/*聚焦点选择*/
    p_ui->location=&location;
    p_ui->project=&project;
    p_ui->scanner=&scanner;
    p_ui->element_sel=&element_sel;
    for(i = 0;i < db_num_probe; i++)
        p_ui->db_probe[i] = &db_probe[i];
    for(j = 0;j < db_num_wedge; j++)
        p_ui->db_wedge[j] = &db_wedge[j];
    for(j = 0;j < material_num; j++)
        p_ui->material[j] = &material[j];    
        
    p_ui->DrawResult = 0 ;
    p_ui->CurrentNum = 0 ;
    p_ui->show_hide  = 0 ;
    p_ui->db_count   = 0 ;
    p_ui->footprint  = 0 ;
    p_ui->is_draw_focus = 1;
    p_ui->view = 3;
    
    vbox=gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);   
    gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(do_appwindow(p_ui)),FALSE,FALSE,0);//添加快捷菜单
    gtk_box_pack_start(GTK_BOX(vbox),GTK_WIDGET(init_ui(p_ui)),TRUE,TRUE,0);
    gtk_box_pack_end(GTK_BOX(vbox),GTK_WIDGET(CreateStasteBar(p_ui)),FALSE,FALSE,0);//添加状态栏 
    
    gtk_widget_show(vbox);
    gtk_widget_show(window);
    
#if 1
    gtk_window_maximize(GTK_WINDOW(window)) ;
#else
	gtk_window_fullscreen (GTK_WINDOW(window));
#endif

    gtk_main();
    return 0;
}

