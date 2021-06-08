/***********************************************
 * �ļ�����arrayLib.h
 * �ļ���������̬����⺯��ͷ�ļ�,�����˶�̬����
 * 			 ���й��ܵĺ����������Լ����Ͷ����
 * �༭�ˣ�
 * �༭���ڣ�2021-06-01
************************************************/

#ifndef  _BSP_ARRAY_H_
#define  _BSP_ARRAY_H_

#include "main.h"

/* ��̬����ṹ���װ */
typedef struct {
	int  n;     // ��̬�����Ԫ�ظ���
	int  size;	// ��̬�����Ԫ�ؿռ��С
	uint16_t *addr; // ��̬�����������ʼ��ַ
} Array_t;

/* �ȽϺ������Ͷ��� */
typedef int compare_t(const void *data1, const void *data2);

/******************************
 * ����Ϊ���ж�̬����⺯������
*******************************/

/* 
 * ������: initArray
 * ��������: ��ʼ����̬����
 * ����: ����Ԫ�صĿռ��С
 * ����ֵ: �ɹ��򷵻س�ʼ����Ķ�̬����ָ��
 * 		   ʧ�ܷ���NULL 
*/
Array_t *initArray(int size);

/*
 * ������: appendArrayTail
 * ��������: β��׷������Ԫ��
 * ����: 1.��Ҫ׷�ӵ�����ָ�� 2.��Ҫ׷�ӵ�Ԫ��ָ��
 * ����ֵ: �ɹ�׷�ӷ���0 ʧ�ܷ���-1
*/
int appendArrayTail(Array_t *ar, const void *data);

/*
 * ������: appendArrayTop
 * ��������: ͷ��׷������Ԫ��
 * ����: 1.��Ҫ׷�ӵ�����ָ�� 2.��Ҫ׷�ӵ�Ԫ��ָ��
 * ����ֵ: �ɹ�׷�ӷ���0 ʧ�ܷ���-1
*/
int appendArrayTop(Array_t *ar, const void *data);

/*
 * ������: insertArrayByIndex
 * ��������: ָ�������±��������Ԫ��
 * 			 <���������±�ĺϷ���>
 * ����: 1.��Ҫ�������ݵ�����ָ�� 2.��Ҫ���������ָ��
 * 		 2.�����±�ֵ
 * ����ֵ: �ɹ����뷵��0 ʧ�ܷ���-1
*/
int insertArrayByIndex(Array_t *ar, const void *data, int idx);

/*
 * ������: travelArray
 * ��������: ������̬����Ԫ��
 * ����: 1.��Ҫ����������ָ�� 2.�ص�����
 * ����ֵ: ��
*/
void travelArray(Array_t *ar, void (*func)(void *data));

/*
 * ������: searchArrayByIndex
 * ��������: �����±��������Ԫ��<�����±�ĺϷ���>
 * ����: 1.��Ҫ���ҵ�����ָ�� 2.���ҵ��±�
 * ����ֵ: ���ݴ��ڷ������ݵ�ַ �������򷵻�NULL
*/
void *searchArrayByIndex(Array_t *ar, const int idx);

/*
 * ������: searchArrayOneByCond
 * ��������: ������������Ԫ��,����ж�����ҵ�һ��
 * ����: 1.��Ҫ���ҵ�����ָ�� 2.�Ƚϻص�����ָ�� 3.����ָ��
 * ����ֵ: ���ݴ��ڷ������ݵ�ַ �������򷵻�NULL
*/
void *searchArrayOneByCond(Array_t *ar, compare_t *func, \
										const void *key);
/*
 * ������: searchArrayByCond
 * ��������: ������������Ԫ��
 * ����: 1.��Ҫ���ҵ�����ָ�� 2.�Ƚϻص�����ָ�� 3.����ָ��
 * ����ֵ: ���ݴ��ڷ����������� �������򷵻�NULL
*/
Array_t *searchArrayByCond(Array_t *ar, compare_t *func, \
										const void *key);
/*
 * ������: deleteArrayByIndex
 * ��������: �����±�ɾ������Ԫ��
 * ����: 1.����ָ�� 2.�±�
 * ����ֵ: �ɹ�ɾ������0 ʧ�ܷ���-1
*/
int deleteArrayByIndex(Array_t *ar, const int idx);

/*
 * ������: deleteArrayOneByCond
 * ��������: ��������ɾ������Ԫ��,������ƥ����ֻɾ����һ��
 * ����: 1.����ָ�� 2.�Ƚϻص�����ָ�� 3.����
 * ����ֵ: �ɹ�ɾ������0 ʧ�ܷ���-1
*/
int deleteArrayOneByCond(Array_t *ar, compare_t *func, \
									 const void *key);
/*
 * ������: deleteArrayByCond
 * ��������: ��������ɾ������ƥ�������Ԫ��
 * ����: 1.����ָ�� 2.�Ƚϻص�����ָ�� 3.����
 * ����ֵ: ���سɹ�ɾ����Ԫ�ظ���
*/
int deleteArrayByCond(Array_t *ar, compare_t *func, \
								   const void *key);
/*
 * ������: sortArray
 * ��������: ������Ԫ�ؽ�������
 * 			<���ڰ�ʲô˳�����������û��Ļص�����������ʵ��>
 * ����: 1.����ָ�� 2.�Ƚϻص�����ָ��
 * ����ֵ: ����ɹ�����0 ʧ�ܷ���-1
*/
int sortArray(Array_t *ar, compare_t *func);

/*
 * ������: saveArrayToFile
 * ��������: ������Ԫ�����ݱ��浽�ļ���
 * ����: 1.����ָ�� 2.��Ҫ������ļ�
 * ����ֵ: ����ɹ�����0 ʧ�ܷ���-1
*/
int saveArrayToFile(Array_t *ar, const char *file);

/*
 * ������: loadArrayFromFile
 * ��������: ���ļ��м�����������
 * ����: ��Ҫ���ص��ļ�
 * ����ֵ: �ɹ����ط�������ָ�� ʧ�ܷ���NULL
*/
Array_t *loadArrayFromFile(const char *file);

/*
 * ������: destoryArray
 * ��������: ���ٶ�̬�������Ա�
 * ����: ����ָ��
 * ����ֵ: ��
*/
void destoryArray(Array_t *ar);

/*
 * ������: isEmptyArray
 * ��������: �ж��Ƿ��ǿ�����
 * ����: ����ָ��
 * ����ֵ: Ϊ�շ���1 ��Ϊ�շ���0
*/
int isEmptyArray(Array_t *ar);

/*
 * ������: arrayLenth
 * ��������: ������ĳ���(Ԫ�ظ���)
 * ����: ����ָ��
 * ����ֵ: ���������Ԫ�ظ���
*/
int arrayLenth(Array_t *ar);

#endif  /* _ARRAY_LIB_H_ */



