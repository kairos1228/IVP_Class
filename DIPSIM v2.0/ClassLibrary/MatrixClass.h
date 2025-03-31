// 
// MatrixClass.h
// 
// Last Modified : 2000/06/30
//
// By jw9557@dali.korea.ac.kr
//
#ifndef __MATRIX_CLASS
#define __MATRIX_CLASS

class AFX_EXT_CLASS CMatrix
{
// attribute
private:

	int m_iWidth;

	int m_iHeight;

	double* m_p1DObject;

	double** m_p2DObject;

// methods
public:

	CMatrix();
	CMatrix( int iWidth, int iHeight );
	CMatrix( CMatrix& Object );
	~CMatrix();

	int GetWidth();

	int GetHeight();

	void SetWidth( int iWidth );

	void SetHeight( int iHeight );

	void Alloc( int nWidth, int nHeight );

	void Free();

	// Matrix�� 1D pointer�� �����Ѵ�.
	const double* Get1DPtr() const;
	double* Get1DPtr();

	// ������ ��ġ�� �����͸� ����.
	void SetAt( int X, int Y, double dfData );

	// �����͸� ��´�.
	double GetAt( int X, int Y );

	// [] operator overloading
	double* operator[]( int iIndex ); 
	CMatrix& operator=( CMatrix& Object );

};

#endif // __MATRIX_CLASS