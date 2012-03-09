#ifndef __OBJECT_DEF
#define __OBJECT_DEF
#define _YM_480
////////////////////////////////////////////////////////////鸟速度小于多少会爆掉
#define BIRD_PLOSION_SPEED 1
#define MAX_OBJECTS 200
//////////////////////////////////////////////////////////////////////物体属性定义
#define WOOD_DENSITY 1.2f				//木头
#define WOOD_FRICTION 15.0f
#define WOOD_RESTITION 0.1f //0.1f

#define ICE_DENSITY 2.0f				//冰
#define ICE_FRICTION 5.0f
#define ICE_RESTITION 0.1f   //0.1

#define STONE_DENSITY 3.0f				//石头
#define STONE_FRICTION 15.0f	
#define STONE_RESTITION 0.1f

#define BIRD_DENSITY 1.0f					//鸟
#define BIRD_FRICTION 13.0f	
#define BIRD_RESTITION 0.1f  
	
#define PIG_DENSITY 1.0f						//猪属性
#define PIG_FRICTION 10.0f	
#define PIG_RESTITION 0.1f	//0.1

#define FLOOR_DENSITY 0.f					//地面属性
#define FLOOR_FRICTION 15.0f	
#define FLOOR_RESTITION 0.1f   //0.5
//////////////////////////////////////////////////////////////////////物体生命值定义
#define PIG_CROWN_PH  1
#define PIG_BEARD_PH  1
#define PIG_CAP_PH  1
#define PIG_L_PH  1  
#define PIG_M_PH  1  
#define PIG_S_PH  1  
//
#define WOOD_B_TIP_PH 1
#define WOOD_L_TIP_PH 1
#define WOOD_M_TIP_PH 1
#define WOOD_S_TIP_PH 1
#define WOOD_M_SQU_PH 1
#define WOOD_S_SQU_PH 1
#define WOOD_S_RECT_PH 1
//
#define ICE_B_TIP_PH 1
#define ICE_L_TIP_PH 1
#define ICE_M_TIP_PH 1
#define ICE_S_TIP_PH 1
#define ICE_M_SQU_PH 1
#define ICE_S_SQU_PH 1
#define ICE_S_RECT_PH 1
//
#define STONE_B_TIP_PH 1
#define STONE_L_TIP_PH 1
#define STONE_M_TIP_PH 1
#define STONE_S_TIP_PH 1
#define STONE_M_SQU_PH 1
#define STONE_S_SQU_PH 1
#define STONE_S_RECT_PH 1
//
///////////////////////////////////////////////////////////////////////物体长宽定义

#ifdef _YM_480
#define FLOOR_LEVEL_X  34  //地面高度
#define MAX_ROLE_LEN  60   //绳子最大长度

	#define  B_TIP_WIDTH 80.0f 
	#define  B_TIP_HEIGHT 8.0f   //超大
	#define  L_TIP_WIDTH 64.0f 
	#define  L_TIP_HEIGHT 8.0f   //长条
	#define  M_TIP_WIDTH 32.0f 
	#define  M_TIP_HEIGHT 8.0f   //中条
	#define  S_TIP_WIDTH 16.0f 
	#define  S_TIP_HEIGHT 8.0f   //短条
	#define  L_SQU_WIDTH 32.0f                         //????????????????????????
	#define  M_SQU_WIDTH 16.0f 
	#define  S_SQU_WIDTH 8.0f  //正方形	
	#define  S_RECT_WIDTH 32.0f 
	#define  S_RECT_HEIGHT 16.0f  //短矩形

  #define S_REDBIRD_WIDTH 38 
  #define S_REDBIRD_HEIGHT 38  //红鸟

	#define	L_CIR_RADIUS 16.5f  
	#define	S_CIR_RADIUS 8.5f 
	//
	#define Z_TRI_X1  16.5f
	#define Z_TRI_Y1  0.0f
	#define Z_TRI_X2  -16.5f
	#define Z_TRI_Y2  16.5f
	#define Z_TRI_X3  -16.5f
	#define Z_TRI_Y3  -16.5f

	#define C_TRI_X1  16.5f
	#define C_TRI_Y1  16.5f
	#define C_TRI_X2  -16.5f
	#define C_TRI_Y2  16.5f
	#define C_TRI_X3  -16.5f
	#define C_TRI_Y3  -16.5f
//
	#define BIRD_TRI_X1  12.0f
	#define BIRD_TRI_Y1  0.0f
	#define BIRD_TRI_X2  -12.0f
	#define BIRD_TRI_Y2  12.0f
	#define BIRD_TRI_X3  -12.0f
	#define BIRD_TRI_Y3  -12.0f
	//
	#define PIG_CROWN_RADIUS 22.0f
	#define PIG_BEARD_RADIUS 16.0f
	#define PIG_CAP_RADIUS 15.0f
	#define PIG_L_RADIUS 15.0f
	#define PIG_M_RADIUS 12.0f
	#define PIG_S_RADIUS 7.0f
	//
  #define BIRD_RED_RADIUS 10.0f
  #define BIRD_BOMB_RADIUS 15.0f
  #define BIRD_EGG_RADIUS 20.0f
  #define BIRD_THREE_RADIUS 6.0f

	//
  #define SLING_DOT1_X  80
  #define SLING_DOT1_Y  8
  #define SLING_DOT2_X  80
  #define SLING_DOT2_Y  28
#endif

enum _FIXTURE_TYPE
{
	FIXTURE_FLOOR=0, //地面
	FIXTURE_WOOD, //木头
	FIXTURE_PIG,  //猪
	FIXTURE_BIRD, //鸟
	FIXTURE_ICE,//冰
	FIXTURE_STONE //石头
};
enum _SHAPE_TYPE
{	
	SHAPE_L_TIP=0,	//长条
	SHAPE_M_TIP,	//中条
	SHAPE_S_TIP,	//短条
	SHAPE_L_SQU,    //大正方形中空
	SHAPE_M_SQU,	//中正方形
	SHAPE_S_SQU,	//小正方形
	SHAPE_S_RECT, //短矩形    
	SHAPE_Z_TRIANGLE, //正三角形
	SHAPE_C_TRIANGLE, //侧三角形
	// 程序中判断以此为上为矩形
	SHAPE_L_CIR, //大圆
	SHAPE_S_CIR, //小圆
	//
	SHAPE_CROWN_PIG,
	SHAPE_BEARD_PIG,
	SHAPE_CAP_PIG,
	SHAPE_L_PIG,    
	SHAPE_M_PIG,
	SHAPE_S_PIG,//6种猪
	//
	SHAPE_FLOOR_POLY,  //地面
	SHAPE_B_TIP,
	//
	SHAPE_WHEEL,  //车轮
	SHAPE_TNT,   //炸弹
	//
	SHAPE_RED_BIRD,   //鸟
	SHAPE_SPEED_BIRD,
	SHAPE_THREE_BIRD,
	SHAPE_BOMB_BIRD,
	SHAPE_EGG_BIRD,
	SHAPE_YA_BIRD
	//
};

enum _SHAPE_LIST
{
	SHAPE_RECT=0, //矩形
	SHAPE_CIRCLE, //圆形
	SHAPE_POLY	//多边形
};

#endif