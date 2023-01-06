#pragma once
#ifndef VECTOR2D
#define VECTOR2D
#include "MyMath2D.h"

struct sMatrix4X4;

class cVector2D
{
	float mX;
	float mY;
public:
	cVector2D();
	cVector2D(const cVector2D&);
	cVector2D(float, float);
	~cVector2D();

	void SetXY(float, float);
	float GetX() const;
	float GetY() const;
	float GetSize() const;
	cVector2D Round() const;
	cVector2D Nomaliztion() const;
	friend bool operator==(const cVector2D&, const cVector2D&); //������ ���
	friend bool operator!=(const cVector2D&, const cVector2D&);
	friend cVector2D operator+(const cVector2D&, const cVector2D&); //���� ��
	friend cVector2D operator-(const cVector2D&, const cVector2D&); //���� ��
	friend cVector2D operator*(const cVector2D&, float);//���� ��Į���
	friend cVector2D operator*(const cVector2D&, const sMatrix4X4&);
	friend float operator*(const cVector2D&, const cVector2D&);//���� ��Į���
	friend float DotOperator(const cVector2D&, const cVector2D&); //���� ����
	friend bool operator< (const cVector2D&, const cVector2D&);
	friend cVector2D ProJ(const cVector2D&, const cVector2D&); //���� ��������
	friend cVector2D ProJa(const cVector2D&, const cVector2D&); //���� ��������
	friend std::ostream &operator<<(std::ostream&, const cVector2D&);// ���� ���  test�ϱ�����

	static float GetLength(const cVector2D&, const cVector2D&);
};






#endif // !VECTOR2D
