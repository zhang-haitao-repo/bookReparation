/***********************************************
 * 文件名：arrayLib.h
 * 文件描述：动态数组库函数头文件,包含了动态数组
 * 			 所有功能的函数的声明以及类型定义等
 * 编辑人：
 * 编辑日期：2021-06-01
************************************************/

#ifndef  _BSP_ARRAY_H_
#define  _BSP_ARRAY_H_

#include "main.h"

/* 动态数组结构体封装 */
typedef struct {
	int  n;     // 动态数组的元素个数
	int  size;	// 动态数组的元素空间大小
	uint16_t *addr; // 动态数组的数据起始地址
} Array_t;

/* 比较函数类型定义 */
typedef int compare_t(const void *data1, const void *data2);

/******************************
 * 以下为所有动态数组库函数声明
*******************************/

/* 
 * 函数名: initArray
 * 函数功能: 初始化动态数组
 * 参数: 数组元素的空间大小
 * 返回值: 成功则返回初始化后的动态数组指针
 * 		   失败返回NULL 
*/
Array_t *initArray(int size);

/*
 * 函数名: appendArrayTail
 * 函数功能: 尾部追加数组元素
 * 参数: 1.需要追加的数组指针 2.需要追加的元素指针
 * 返回值: 成功追加返回0 失败返回-1
*/
int appendArrayTail(Array_t *ar, const void *data);

/*
 * 函数名: appendArrayTop
 * 函数功能: 头部追加数组元素
 * 参数: 1.需要追加的数组指针 2.需要追加的元素指针
 * 返回值: 成功追加返回0 失败返回-1
*/
int appendArrayTop(Array_t *ar, const void *data);

/*
 * 函数名: insertArrayByIndex
 * 函数功能: 指定数组下标插入数组元素
 * 			 <函数会检查下标的合法性>
 * 参数: 1.需要插入数据的数组指针 2.需要插入的数据指针
 * 		 2.数组下标值
 * 返回值: 成功插入返回0 失败返回-1
*/
int insertArrayByIndex(Array_t *ar, const void *data, int idx);

/*
 * 函数名: travelArray
 * 函数功能: 遍历动态数组元素
 * 参数: 1.需要遍历的数组指针 2.回调函数
 * 返回值: 无
*/
void travelArray(Array_t *ar, void (*func)(void *data));

/*
 * 函数名: searchArrayByIndex
 * 函数功能: 根据下标查找数组元素<会检查下标的合法性>
 * 参数: 1.需要查找的数组指针 2.查找的下标
 * 返回值: 数据存在返回数据地址 不存在则返回NULL
*/
void *searchArrayByIndex(Array_t *ar, const int idx);

/*
 * 函数名: searchArrayOneByCond
 * 函数功能: 根据条件查找元素,如果有多个则找第一个
 * 参数: 1.需要查找的数组指针 2.比较回调函数指针 3.条件指针
 * 返回值: 数据存在返回数据地址 不存在则返回NULL
*/
void *searchArrayOneByCond(Array_t *ar, compare_t *func, \
										const void *key);
/*
 * 函数名: searchArrayByCond
 * 函数功能: 根据条件查找元素
 * 参数: 1.需要查找的数组指针 2.比较回调函数指针 3.条件指针
 * 返回值: 数据存在返回数据数组 不存在则返回NULL
*/
Array_t *searchArrayByCond(Array_t *ar, compare_t *func, \
										const void *key);
/*
 * 函数名: deleteArrayByIndex
 * 函数功能: 根据下标删除数组元素
 * 参数: 1.数组指针 2.下标
 * 返回值: 成功删除返回0 失败返回-1
*/
int deleteArrayByIndex(Array_t *ar, const int idx);

/*
 * 函数名: deleteArrayOneByCond
 * 函数功能: 根据条件删除数组元素,如果多个匹配则只删除第一个
 * 参数: 1.数组指针 2.比较回调函数指针 3.条件
 * 返回值: 成功删除返回0 失败返回-1
*/
int deleteArrayOneByCond(Array_t *ar, compare_t *func, \
									 const void *key);
/*
 * 函数名: deleteArrayByCond
 * 函数功能: 根据条件删除所有匹配的数组元素
 * 参数: 1.数组指针 2.比较回调函数指针 3.条件
 * 返回值: 返回成功删除的元素个数
*/
int deleteArrayByCond(Array_t *ar, compare_t *func, \
								   const void *key);
/*
 * 函数名: sortArray
 * 函数功能: 对数组元素进行排序
 * 			<至于按什么顺序排列则由用户的回调函数具体来实现>
 * 参数: 1.数组指针 2.比较回调函数指针
 * 返回值: 排序成功返回0 失败返回-1
*/
int sortArray(Array_t *ar, compare_t *func);

/*
 * 函数名: saveArrayToFile
 * 函数功能: 把数组元素数据保存到文件中
 * 参数: 1.数组指针 2.需要保存的文件
 * 返回值: 保存成功返回0 失败返回-1
*/
int saveArrayToFile(Array_t *ar, const char *file);

/*
 * 函数名: loadArrayFromFile
 * 函数功能: 从文件中加载数组数据
 * 参数: 需要加载的文件
 * 返回值: 成功加载返回数组指针 失败返回NULL
*/
Array_t *loadArrayFromFile(const char *file);

/*
 * 函数名: destoryArray
 * 函数功能: 销毁动态数组线性表
 * 参数: 数组指针
 * 返回值: 无
*/
void destoryArray(Array_t *ar);

/*
 * 函数名: isEmptyArray
 * 函数功能: 判断是否是空数组
 * 参数: 数组指针
 * 返回值: 为空返回1 不为空返回0
*/
int isEmptyArray(Array_t *ar);

/*
 * 函数名: arrayLenth
 * 函数功能: 求数组的长度(元素个数)
 * 参数: 数组指针
 * 返回值: 返回数组的元素个数
*/
int arrayLenth(Array_t *ar);

#endif  /* _ARRAY_LIB_H_ */



