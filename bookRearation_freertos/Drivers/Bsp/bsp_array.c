/********************************************
 * �ļ�����arrayLib.c
 * �ļ���������̬����⺯�����й��ܺ����Ķ���
 * �༭�ˣ�
 * �༭���ڣ�2021-06-01
*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsp_array.h"
#include "main.h" 
/* 
 * ������: initArray
 * ��������: ��ʼ����̬����
 * ����: ����Ԫ�صĿռ��С
 * ����ֵ: �ɹ��򷵻س�ʼ����Ķ�̬����ָ��
 * 		   ʧ�ܷ���NULL 
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
 * ������: appendArrayTail
 * ��������: β��׷������Ԫ��
 * ����: 1.��Ҫ׷�ӵ�����ָ�� 2.��Ҫ׷�ӵ�Ԫ��ָ��
 * ����ֵ: �ɹ�׷�ӷ���0 ʧ�ܷ���-1
*/
int appendArrayTail(Array_t *ar, const void *data)
{
	void *temp;
#if 0
	/* �����ԭ����һ�����ݵĿռ� */
	temp = realloc(ar->addr, (ar->n+1)*ar->size);
	if (temp == NULL)
	{
		return -1;
	}
#else
	/* �����ԭ����һ�����ݵĿռ� */
	temp = malloc((ar->n+1) * ar->size);
	if (temp == NULL)
	{
		return -1;
	}
	/* ��ԭ�������ƶ����¿ռ� */
	memmove(temp, ar->addr, ar->n * ar->size);
	/* �ͷ�ԭ�����ݿռ� */
	free(ar->addr);
#endif
	/* �������ݸ��Ƶ��¿ռ��β�� */
	memmove((uint16_t*)temp+(uint16_t)(ar->n*ar->size), data, ar->size);
	/* ���ݸ�����1 */
	ar->n += 1;
	/* �������ݵ�ַָ�� */
	ar->addr = temp;

	return 0;
}

/*
 * ������: appendArrayTop
 * ��������: ͷ��׷������Ԫ��
 * ����: 1.��Ҫ׷�ӵ�����ָ�� 2.��Ҫ׷�ӵ�Ԫ��ָ��
 * ����ֵ: �ɹ�׷�ӷ���0 ʧ�ܷ���-1
*/
int appendArrayTop(Array_t *ar, const void *data)
{
	void *temp;
#if 0
	/* �����ԭ����һ�����ݵĿռ� */
	temp = realloc(ar->addr, (ar->n+1)*ar->size);
	if (temp == NULL)
	{
		return -1;
	}
#else
	/* �����ԭ����һ�����ݵĿռ� */
	temp = malloc((ar->n+1) * ar->size);
	if (temp == NULL)
	{
		return -1;
	}
	/* ��ԭ�������ƶ����¿ռ� */
	memmove((uint16_t*)temp+ar->size, ar->addr, ar->n * ar->size);
	/* �ͷ�ԭ�����ݿռ� */
	free(ar->addr);
#endif
	/* �������ݸ��Ƶ��¿ռ��ͷ�� */
	memmove(temp, data, ar->size);
	/* ���ݸ�����1 */
	ar->n += 1;
	/* �������ݵ�ַָ�� */
	ar->addr = temp;

	return 0;
}

/*
 * ������: insertArrayByIndex
 * ��������: ָ�������±��������Ԫ��
 * 			 <���������±�ĺϷ���>
 * ����: 1.��Ҫ�������ݵ�����ָ�� 2.��Ҫ���������ָ��
 * 		 2.�����±�ֵ
 * ����ֵ: �ɹ����뷵��0 ʧ�ܷ���-1
*/
int insertArrayByIndex(Array_t *ar, const void *data, int idx)
{
	/* ����±�Ϸ��� */
	if (idx < 0 || idx > ar->n)
	{
		printf("Error! index is illegal!\n");
		return -1;
	}

	void *temp;
#if 0
	/* �����ԭ����һ�����ݵĿռ� */
	temp = realloc(ar->addr, (ar->n+1)*ar->size);
	if (temp == NULL)
	{
		return -1;
	}
	/* ��ԭ���ռ�idx�Լ�����������ƶ����¿ռ��idx֮�� */
	memmove(temp+(idx+1)*ar->size, temp+idx*ar->size, \
								(ar->n-idx)*ar->size);
	/* �������ݲ��뵽�¿ռ��idx�� */
	memmove(temp+idx*ar->size, data, ar->size);
#else
	/* �����ԭ����һ�����ݵĿռ� */
	temp = malloc((ar->n+1)*ar->size);
	if (temp == NULL)
	{
		return -1;
	}
	/* ��ԭ���ռ�idx��ǰ�������ƶ����¿ռ�ǰ�� */
	memmove(temp, ar->addr, idx*ar->size);
	/* �������ݲ��뵽�¿ռ��idx�� */
	memmove((uint16_t*)temp+idx*ar->size, data, ar->size);
	/* ��ԭ���ռ�idx�Լ�����������ƶ����¿ռ��idx֮�� */
	memmove((uint16_t*)temp+(idx+1)*ar->size, ar->addr+(idx*ar->size), \
								(ar->n-idx)*ar->size);
#endif
	/* ����Ԫ�ظ�����1 */
	ar->n += 1;
	/* �������ݵ�ַ */
	ar->addr = temp;

	return 0;
}

/*
 * ������: travelArray
 * ��������: ������̬����Ԫ��
 * ����: 1.��Ҫ����������ָ�� 2.�ص�����
 * ����ֵ: ��
*/
void travelArray(Array_t *ar, void (*func)(void *data))
{
	int i;
	for (i = 0; i < ar->n; i++)
	{
		/* ar->addr + i*ar->size: ÿ�����ݵ���ʼ��ַ */
		func((uint16_t*)ar->addr + i*ar->size);
	}
}

/*
 * ������: searchArrayByIndex
 * ��������: �����±��������Ԫ��<�����±�ĺϷ���>
 * ����: 1.��Ҫ���ҵ�����ָ�� 2.���ҵ��±�
 * ����ֵ: ���ݴ��ڷ������ݵ�ַ �������򷵻�NULL
*/
void *searchArrayByIndex(Array_t *ar, const int idx)
{
	/* �±�Ϸ��Լ�� */
	if (idx < 0 || idx >= ar->n)
	{
		fprintf(stderr,"Error! index is illegal!\n");
		return NULL;
	}
	return (uint16_t*)ar->addr + idx*ar->size;
}

/*
 * ������: searchArrayOneByCond
 * ��������: ������������Ԫ��,����ж�����ҵ�һ��
 * ����: 1.��Ҫ���ҵ�����ָ�� 2.�Ƚϻص�����ָ�� 3.����ָ��
 * ����ֵ: ���ݴ��ڷ������ݵ�ַ �������򷵻�NULL
*/
void *searchArrayOneByCond(Array_t *ar, compare_t *func, \
										const void *key)
{
	int i;
	for (i = 0; i < ar->n; i++)
	{
 		/* �ȽϺ�������ƥ��func����1 */
		if (func((uint16_t*)ar->addr+i*ar->size, key) == 1)
		{
			return (uint16_t*)ar->addr + i*ar->size;
		}
	}
	return NULL;
}
/*
 * ������: searchArrayByCond
 * ��������: ������������Ԫ��
 * ����: 1.��Ҫ���ҵ�����ָ�� 2.�Ƚϻص�����ָ�� 3.����ָ��
 * ����ֵ: ���ݴ��ڷ����������� �������򷵻�NULL
*/
Array_t *searchArrayByCond(Array_t *ar, compare_t *func, \
										const void *key)
{
	int i, ret;
	Array_t *result;

	/* �������ڱ����������� */
	result = initArray(ar->size);
	if (result == NULL)
	{
		return NULL;
	}
	/* �������� */
	for (i = 0; i < ar->n; i++)
	{
 		/* �ȽϺ�������ƥ��func����1 */
		if (func((uint16_t*)ar->addr+i*ar->size, key) == 1)
		{
			/* ��ƥ�������β��׷�ӵ������� */
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
 * ������: deleteArrayByIndex
 * ��������: �����±�ɾ������Ԫ��
 * ����: 1.����ָ�� 2.�±�
 * ����ֵ: �ɹ�ɾ������0 ʧ�ܷ���-1
*/
int deleteArrayByIndex(Array_t *ar, const int idx)
{
	/* ����±�Ϸ��� */
	if (idx < 0 || idx >= ar->n)
	{
		fprintf(stderr, "Error! index is illegal!\n");
		return -1;
	}
	/* ͨ�����ݰ��˴ﵽɾ��Ŀ�� */
	void *temp;
	temp = malloc((ar->n-1)*ar->size);
	if (temp == NULL)
	{
		return -1;
	}
	/* ��idx֮ǰ�������Ƶ��¿ռ� */
	memmove(temp, ar->addr, idx*ar->size);
	/* ��idx֮��������Ƶ��¿ռ� */
	memmove((uint16_t*)temp+idx*ar->size, (uint16_t*)ar->addr+(idx+1)*ar->size, \
					              (ar->n-idx-1)*ar->size);
	/* �ͷ�ԭ�����ݿռ� */
	free(ar->addr);
	/* ����Ԫ�ظ��� */
	ar->n -= 1;
	/* ��������Ԫ�ص�ַ */
	ar->addr = temp;

	return 0;
}

/*
 * ������: deleteArrayOneByCond
 * ��������: ��������ɾ������Ԫ��,������ƥ����ֻɾ����һ��
 * ����: 1.����ָ�� 2.�Ƚϻص�����ָ�� 3.����
 * ����ֵ: �ɹ�ɾ������0 ʧ�ܷ���-1
*/
int deleteArrayOneByCond(Array_t *ar, compare_t *func, \
									 const void *key)
{
	int i;
	for (i = 0; i < ar->n; i++)
	{
		/* �ȽϺ�������ƥ�䷵��1 */
		if (func((uint16_t*)ar->addr+i*ar->size, key) == 1)
		{
			return deleteArrayByIndex(ar,i);
		}
	}
	return -1;
}

/*
 * ������: deleteArrayByCond
 * ��������: ��������ɾ������ƥ�������Ԫ��
 * ����: 1.����ָ�� 2.�Ƚϻص�����ָ�� 3.����
 * ����ֵ: ���سɹ�ɾ����Ԫ�ظ���
*/
int deleteArrayByCond(Array_t *ar, compare_t *func, \
								   const void *key)
{
	int i;
	int count = 0;
	for (i = 0; i < ar->n; i++)
	{
		/* �ȽϺ�������ƥ�䷵��1 */
		if (func((uint16_t*)ar->addr+i*ar->size, key) == 1)
		{
			if (deleteArrayByIndex(ar,i) == 0)
			{
				count++;
				i--; /* �ֲ����±�ɾ��Ԫ�غ���±�仯 */
			}
		}
	}
	return count;
}
/*
 * ������: sortArray
 * ��������: ������Ԫ�ؽ�������
 * 			<���ڰ�ʲô˳�����������û��Ļص�����������ʵ��>
 * ����: 1.����ָ�� 2.�Ƚϻص�����ָ��
 * ����ֵ: ����ɹ�����0 ʧ�ܷ���-1
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
		    /* �ȽϺ�������ƥ�䷵��1 */
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
 * ������: saveArrayToFile
 * ��������: ������Ԫ�����ݱ��浽�ļ���
 * ����: 1.����ָ�� 2.��Ҫ������ļ�
 * ����ֵ: ����ɹ�����0 ʧ�ܷ���-1
*/
int saveArrayToFile(Array_t *ar, const char *file)
{
	FILE *fout;
	int ret;

	/* ���ļ��� */
	fout = fopen(file, "w");
	if (fout == NULL)
	{
		perror(file);
		return -1;
	}
	/* д������Ԫ�ظ��� */
	ret = fwrite(&ar->n, sizeof(ar->n), 1, fout);
	if (ret != 1)
	{
		/* д��ʧ��:�ر��ļ���,�ر��ļ� */
		fclose(fout);
		remove(file);
		return -1;
	}
	/* д������Ԫ�ؿռ��С */
	ret = fwrite(&ar->size, sizeof(ar->size), 1, fout);
	if (ret != 1)
	{
		/* д��ʧ��:�ر��ļ���,�ر��ļ� */
		fclose(fout);
		remove(file);
		return -1;
	}
	/* д������ */
	ret = 0;
	while (ret != ar->n) /* ��֤д�� */
	{
		ret += fwrite((uint16_t*)ar->addr+ret*ar->size, \
					ar->size, ar->n-ret, fout);
		/* �������д�ļ����� */
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
 * ������: loadArrayFromFile
 * ��������: ���ļ��м�����������
 * ����: ��Ҫ���ص��ļ�
 * ����ֵ: �ɹ����ط�������ָ�� ʧ�ܷ���NULL
*/
Array_t *loadArrayFromFile(const char *file)
{
	int ret;
	FILE *fin;
	Array_t *ar;

	/* ���ļ� */
	fin = fopen(file, "r");
	if (fin == NULL)
	{
		return NULL;
	}
	/* �ɹ����ļ� */

	ar = initArray(0);
	if (ar == NULL)
	{
		fclose(fin);
		return NULL;
	}
	/* �ɹ���ʼ������ */
	
	/* ��ȡ����Ԫ�ظ��� */
	ret = fread(&ar->n, sizeof(ar->n), 1, fin);
	if (ret != 1)
	{
		fclose(fin);
		destoryArray(ar);
		return NULL;
	}
	/* ��ȡ����Ԫ�ؿռ��С */
	ret = fread(&ar->size, sizeof(ar->size), 1, fin);
	if (ret != 1)
	{
		fclose(fin);
		destoryArray(ar);
		return NULL;
	}
	/* ��ȡ����Ԫ������ */
	ar->addr = malloc(ar->n * ar->size);
	if (ar->addr == NULL)
	{
		fclose(fin);
		destoryArray(ar);
		return NULL;
	}
	ret = 0;
	while (ret != ar->n) /* ��֤���� */
	{
		ret += fread((uint16_t*)ar->addr + ret*ar->size, \
						ar->size, ar->n-ret, fin);
		if (ferror(fin))
		{
			if (ret > 0) /* �Ѿ���ȡ����һ���� */
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
		/* �п����ļ���¼�ĸ�����ʵ�ʵĲ�һ�� */
		else if (feof(fin)) 
		{
			break;
		}
	}
	/* �ļ����ݶ�ʧ,û��֮ǰ�洢����ô�� */
	if (ar->n != ret)
	{
		void *temp;
		ar->n = ret;
		temp = realloc(ar->addr, ar->n*ar->size);
	}

	fclose(fin);   // �رմ򿪵��ļ�
	return ar;
}

/*
 * ������: destoryArray
 * ��������: ���ٶ�̬�������Ա�
 * ����: ����ָ��
 * ����ֵ: ��
*/
void destoryArray(Array_t *ar)
{
	/* �ͷ�����Ԫ�ؿռ� */
	free(ar->addr);
	/* �ͷ����鱾��ռ� */
	free(ar);
	/* �����ٴ�ʹ���ͷŵĿռ� */
	ar = NULL;
}

/*
 * ������: isEmptyArray
 * ��������: �ж��Ƿ��ǿ�����
 * ����: ����ָ��
 * ����ֵ: Ϊ�շ���1 ��Ϊ�շ���0
*/
int isEmptyArray(Array_t *ar)
{
	/* Ԫ�ظ���Ϊ��ͬʱԪ�ص�ַΪNULL */
	return ar->n==0 && ar->addr==NULL;
}

/*
 * ������: arrayLenth
 * ��������: ������ĳ���(Ԫ�ظ���)
 * ����: ����ָ��
 * ����ֵ: ���������Ԫ�ظ���
*/
int arrayLenth(Array_t *ar)
{
	return ar->n;
}


