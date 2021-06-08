/********************************************
 * 文件名：arrayLib.c
 * 文件描述：动态数组库函数所有功能函数的定义
 * 编辑人：
 * 编辑日期：2021-06-01
*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsp_array.h"
#include "main.h" 
/* 
 * 函数名: initArray
 * 函数功能: 初始化动态数组
 * 参数: 数组元素的空间大小
 * 返回值: 成功则返回初始化后的动态数组指针
 * 		   失败返回NULL 
*/
Array_t *initArray(int size)
{
	Array_t *ar;
	ar = malloc(sizeof(Array_t));
	if (ar == NULL) return NULL;

	ar->size = size;
	ar->n = 0;
	ar->addr = NULL;

	return ar;
}

/*
 * 函数名: appendArrayTail
 * 函数功能: 尾部追加数组元素
 * 参数: 1.需要追加的数组指针 2.需要追加的元素指针
 * 返回值: 成功追加返回0 失败返回-1
*/
int appendArrayTail(Array_t *ar, const void *data)
{
	void *temp;
#if 0
	/* 分配比原来多一个数据的空间 */
	temp = realloc(ar->addr, (ar->n+1)*ar->size);
	if (temp == NULL)
	{
		return -1;
	}
#else
	/* 分配比原来多一个数据的空间 */
	temp = malloc((ar->n+1) * ar->size);
	if (temp == NULL)
	{
		return -1;
	}
	/* 把原来数据移动到新空间 */
	memmove(temp, ar->addr, ar->n * ar->size);
	/* 释放原来数据空间 */
	free(ar->addr);
#endif
	/* 把新数据复制到新空间的尾部 */
	memmove((uint16_t*)temp+(uint16_t)(ar->n*ar->size), data, ar->size);
	/* 数据个数加1 */
	ar->n += 1;
	/* 更新数据地址指针 */
	ar->addr = temp;

	return 0;
}

/*
 * 函数名: appendArrayTop
 * 函数功能: 头部追加数组元素
 * 参数: 1.需要追加的数组指针 2.需要追加的元素指针
 * 返回值: 成功追加返回0 失败返回-1
*/
int appendArrayTop(Array_t *ar, const void *data)
{
	void *temp;
#if 0
	/* 分配比原来多一个数据的空间 */
	temp = realloc(ar->addr, (ar->n+1)*ar->size);
	if (temp == NULL)
	{
		return -1;
	}
#else
	/* 分配比原来多一个数据的空间 */
	temp = malloc((ar->n+1) * ar->size);
	if (temp == NULL)
	{
		return -1;
	}
	/* 把原来数据移动到新空间 */
	memmove((uint16_t*)temp+ar->size, ar->addr, ar->n * ar->size);
	/* 释放原来数据空间 */
	free(ar->addr);
#endif
	/* 把新数据复制到新空间的头部 */
	memmove(temp, data, ar->size);
	/* 数据个数加1 */
	ar->n += 1;
	/* 更新数据地址指针 */
	ar->addr = temp;

	return 0;
}

/*
 * 函数名: insertArrayByIndex
 * 函数功能: 指定数组下标插入数组元素
 * 			 <函数会检查下标的合法性>
 * 参数: 1.需要插入数据的数组指针 2.需要插入的数据指针
 * 		 2.数组下标值
 * 返回值: 成功插入返回0 失败返回-1
*/
int insertArrayByIndex(Array_t *ar, const void *data, int idx)
{
	/* 检查下标合法性 */
	if (idx < 0 || idx > ar->n)
	{
		printf("Error! index is illegal!\n");
		return -1;
	}

	void *temp;
#if 0
	/* 分配比原来多一个数据的空间 */
	temp = realloc(ar->addr, (ar->n+1)*ar->size);
	if (temp == NULL)
	{
		return -1;
	}
	/* 把原来空间idx以及后面的数据移动到新空间的idx之后 */
	memmove(temp+(idx+1)*ar->size, temp+idx*ar->size, \
								(ar->n-idx)*ar->size);
	/* 把新数据插入到新空间的idx处 */
	memmove(temp+idx*ar->size, data, ar->size);
#else
	/* 分配比原来多一个数据的空间 */
	temp = malloc((ar->n+1)*ar->size);
	if (temp == NULL)
	{
		return -1;
	}
	/* 把原来空间idx以前的数据移动到新空间前面 */
	memmove(temp, ar->addr, idx*ar->size);
	/* 把新数据插入到新空间的idx处 */
	memmove((uint16_t*)temp+idx*ar->size, data, ar->size);
	/* 把原来空间idx以及后面的数据移动到新空间的idx之后 */
	memmove((uint16_t*)temp+(idx+1)*ar->size, ar->addr+(idx*ar->size), \
								(ar->n-idx)*ar->size);
#endif
	/* 数据元素个数加1 */
	ar->n += 1;
	/* 更新数据地址 */
	ar->addr = temp;

	return 0;
}

/*
 * 函数名: travelArray
 * 函数功能: 遍历动态数组元素
 * 参数: 1.需要遍历的数组指针 2.回调函数
 * 返回值: 无
*/
void travelArray(Array_t *ar, void (*func)(void *data))
{
	int i;
	for (i = 0; i < ar->n; i++)
	{
		/* ar->addr + i*ar->size: 每个数据的起始地址 */
		func((uint16_t*)ar->addr + i*ar->size);
	}
}

/*
 * 函数名: searchArrayByIndex
 * 函数功能: 根据下标查找数组元素<会检查下标的合法性>
 * 参数: 1.需要查找的数组指针 2.查找的下标
 * 返回值: 数据存在返回数据地址 不存在则返回NULL
*/
void *searchArrayByIndex(Array_t *ar, const int idx)
{
	/* 下标合法性检查 */
	if (idx < 0 || idx >= ar->n)
	{
		fprintf(stderr,"Error! index is illegal!\n");
		return NULL;
	}
	return (uint16_t*)ar->addr + idx*ar->size;
}

/*
 * 函数名: searchArrayOneByCond
 * 函数功能: 根据条件查找元素,如果有多个则找第一个
 * 参数: 1.需要查找的数组指针 2.比较回调函数指针 3.条件指针
 * 返回值: 数据存在返回数据地址 不存在则返回NULL
*/
void *searchArrayOneByCond(Array_t *ar, compare_t *func, \
										const void *key)
{
	int i;
	for (i = 0; i < ar->n; i++)
	{
 		/* 比较函数条件匹配func返回1 */
		if (func((uint16_t*)ar->addr+i*ar->size, key) == 1)
		{
			return (uint16_t*)ar->addr + i*ar->size;
		}
	}
	return NULL;
}
/*
 * 函数名: searchArrayByCond
 * 函数功能: 根据条件查找元素
 * 参数: 1.需要查找的数组指针 2.比较回调函数指针 3.条件指针
 * 返回值: 数据存在返回数据数组 不存在则返回NULL
*/
Array_t *searchArrayByCond(Array_t *ar, compare_t *func, \
										const void *key)
{
	int i, ret;
	Array_t *result;

	/* 创建用于保存结果的数组 */
	result = initArray(ar->size);
	if (result == NULL)
	{
		return NULL;
	}
	/* 遍历查找 */
	for (i = 0; i < ar->n; i++)
	{
 		/* 比较函数条件匹配func返回1 */
		if (func((uint16_t*)ar->addr+i*ar->size, key) == 1)
		{
			/* 把匹配的数据尾部追加到数组里 */
			ret = appendArrayTail(result, (uint16_t*)ar->addr+i*ar->size);
			if (ret != 0)
			{
				destoryArray(result);
				return NULL;
			}
		}
	}
	return result;
}

/*
 * 函数名: deleteArrayByIndex
 * 函数功能: 根据下标删除数组元素
 * 参数: 1.数组指针 2.下标
 * 返回值: 成功删除返回0 失败返回-1
*/
int deleteArrayByIndex(Array_t *ar, const int idx)
{
	/* 检查下标合法性 */
	if (idx < 0 || idx >= ar->n)
	{
		fprintf(stderr, "Error! index is illegal!\n");
		return -1;
	}
	/* 通过数据搬运达到删除目的 */
	void *temp;
	temp = malloc((ar->n-1)*ar->size);
	if (temp == NULL)
	{
		return -1;
	}
	/* 把idx之前的数据移到新空间 */
	memmove(temp, ar->addr, idx*ar->size);
	/* 把idx之后的数据移到新空间 */
	memmove((uint16_t*)temp+idx*ar->size, (uint16_t*)ar->addr+(idx+1)*ar->size, \
					              (ar->n-idx-1)*ar->size);
	/* 释放原来数据空间 */
	free(ar->addr);
	/* 更新元素个数 */
	ar->n -= 1;
	/* 更新数组元素地址 */
	ar->addr = temp;

	return 0;
}

/*
 * 函数名: deleteArrayOneByCond
 * 函数功能: 根据条件删除数组元素,如果多个匹配则只删除第一个
 * 参数: 1.数组指针 2.比较回调函数指针 3.条件
 * 返回值: 成功删除返回0 失败返回-1
*/
int deleteArrayOneByCond(Array_t *ar, compare_t *func, \
									 const void *key)
{
	int i;
	for (i = 0; i < ar->n; i++)
	{
		/* 比较函数条件匹配返回1 */
		if (func((uint16_t*)ar->addr+i*ar->size, key) == 1)
		{
			return deleteArrayByIndex(ar,i);
		}
	}
	return -1;
}

/*
 * 函数名: deleteArrayByCond
 * 函数功能: 根据条件删除所有匹配的数组元素
 * 参数: 1.数组指针 2.比较回调函数指针 3.条件
 * 返回值: 返回成功删除的元素个数
*/
int deleteArrayByCond(Array_t *ar, compare_t *func, \
								   const void *key)
{
	int i;
	int count = 0;
	for (i = 0; i < ar->n; i++)
	{
		/* 比较函数条件匹配返回1 */
		if (func((uint16_t*)ar->addr+i*ar->size, key) == 1)
		{
			if (deleteArrayByIndex(ar,i) == 0)
			{
				count++;
				i--; /* 弥补按下标删除元素后的下标变化 */
			}
		}
	}
	return count;
}
/*
 * 函数名: sortArray
 * 函数功能: 对数组元素进行排序
 * 			<至于按什么顺序排列则由用户的回调函数具体来实现>
 * 参数: 1.数组指针 2.比较回调函数指针
 * 返回值: 排序成功返回0 失败返回-1
*/
int sortArray(Array_t *ar, compare_t *func)
{
	int i, j;
	void *temp;
	temp = malloc(ar->size);
	if (temp == NULL) return -1;
	for (i = 0; i < ar->n; i++)
	{
		for (j = 1; j < ar->n-i; j++)
		{
		    /* 比较函数条件匹配返回1 */
		    if (func((uint16_t*)ar->addr+i*ar->size, \
					(uint16_t*)ar->addr+j*ar->size) == 1)
		    {
		    	memmove((uint16_t*)temp, (uint16_t*)ar->addr+i*ar->size, ar->size);
				memmove((uint16_t*)ar->addr+i*ar->size, \
						(uint16_t*)ar->addr+j*ar->size, ar->size);
				memmove((uint16_t*)ar->addr+j*ar->size, temp, ar->size);
		    }
		}
	}
	free(temp);
	return 0;	
}

/*
 * 函数名: saveArrayToFile
 * 函数功能: 把数组元素数据保存到文件中
 * 参数: 1.数组指针 2.需要保存的文件
 * 返回值: 保存成功返回0 失败返回-1
*/
int saveArrayToFile(Array_t *ar, const char *file)
{
	FILE *fout;
	int ret;

	/* 打开文件流 */
	fout = fopen(file, "w");
	if (fout == NULL)
	{
		perror(file);
		return -1;
	}
	/* 写入数组元素个数 */
	ret = fwrite(&ar->n, sizeof(ar->n), 1, fout);
	if (ret != 1)
	{
		/* 写入失败:关闭文件流,关闭文件 */
		fclose(fout);
		remove(file);
		return -1;
	}
	/* 写入数组元素空间大小 */
	ret = fwrite(&ar->size, sizeof(ar->size), 1, fout);
	if (ret != 1)
	{
		/* 写入失败:关闭文件流,关闭文件 */
		fclose(fout);
		remove(file);
		return -1;
	}
	/* 写入数据 */
	ret = 0;
	while (ret != ar->n) /* 保证写完 */
	{
		ret += fwrite((uint16_t*)ar->addr+ret*ar->size, \
					ar->size, ar->n-ret, fout);
		/* 如果遇到写文件错误 */
		if (ferror(fout))
		{
			fclose(fout);
			remove(file);
			return -1;
		}
	}

	fclose(fout);
	return 0;
}

/*
 * 函数名: loadArrayFromFile
 * 函数功能: 从文件中加载数组数据
 * 参数: 需要加载的文件
 * 返回值: 成功加载返回数组指针 失败返回NULL
*/
Array_t *loadArrayFromFile(const char *file)
{
	int ret;
	FILE *fin;
	Array_t *ar;

	/* 打开文件 */
	fin = fopen(file, "r");
	if (fin == NULL)
	{
		return NULL;
	}
	/* 成功打开文件 */

	ar = initArray(0);
	if (ar == NULL)
	{
		fclose(fin);
		return NULL;
	}
	/* 成功初始化数组 */
	
	/* 读取数组元素个数 */
	ret = fread(&ar->n, sizeof(ar->n), 1, fin);
	if (ret != 1)
	{
		fclose(fin);
		destoryArray(ar);
		return NULL;
	}
	/* 读取数组元素空间大小 */
	ret = fread(&ar->size, sizeof(ar->size), 1, fin);
	if (ret != 1)
	{
		fclose(fin);
		destoryArray(ar);
		return NULL;
	}
	/* 读取数组元素数据 */
	ar->addr = malloc(ar->n * ar->size);
	if (ar->addr == NULL)
	{
		fclose(fin);
		destoryArray(ar);
		return NULL;
	}
	ret = 0;
	while (ret != ar->n) /* 保证读完 */
	{
		ret += fread((uint16_t*)ar->addr + ret*ar->size, \
						ar->size, ar->n-ret, fin);
		if (ferror(fin))
		{
			if (ret > 0) /* 已经读取到了一部分 */
			{
				break;
			}
			else
			{
				fclose(fin);
				destoryArray(ar);
				return NULL;
			}
		}
		/* 有可能文件记录的个数与实际的不一样 */
		else if (feof(fin)) 
		{
			break;
		}
	}
	/* 文件数据丢失,没有之前存储的那么多 */
	if (ar->n != ret)
	{
		void *temp;
		ar->n = ret;
		temp = realloc(ar->addr, ar->n*ar->size);
	}

	fclose(fin);   // 关闭打开的文件
	return ar;
}

/*
 * 函数名: destoryArray
 * 函数功能: 销毁动态数组线性表
 * 参数: 数组指针
 * 返回值: 无
*/
void destoryArray(Array_t *ar)
{
	/* 释放数组元素空间 */
	free(ar->addr);
	/* 释放数组本身空间 */
	free(ar);
	/* 避免再次使用释放的空间 */
	ar = NULL;
}

/*
 * 函数名: isEmptyArray
 * 函数功能: 判断是否是空数组
 * 参数: 数组指针
 * 返回值: 为空返回1 不为空返回0
*/
int isEmptyArray(Array_t *ar)
{
	/* 元素个数为零同时元素地址为NULL */
	return ar->n==0 && ar->addr==NULL;
}

/*
 * 函数名: arrayLenth
 * 函数功能: 求数组的长度(元素个数)
 * 参数: 数组指针
 * 返回值: 返回数组的元素个数
*/
int arrayLenth(Array_t *ar)
{
	return ar->n;
}


