// 
// ImageClass.H
// 
// Last Modified : 2000/06/30
//
// By jw9557@dali.korea.ac.kr
//
#ifndef __IMAGE_CLASS
#define __IMAGE_CLASS

#include <string.h>
#include <stdlib.h>
#include "BasicType.h"

class CImageByte;
class CImageFloat;
class CImageComplex;
class CImageRGB;

enum { IT_BYTE, IT_FLOAT, IT_COMPLEX, IT_RGB, IT_SEQ, IT_VECTOR, IT_UNKNOWN = 100 };

////////////////////////////////////////////////////////////////////////////
//
// Class : CImageObject
//
// Des : ��� ���� Ŭ������ ������ �ְ� �ϴ� �ֻ��� Ŭ����                      
//
////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CImageObject 
{
// attribute
private:

	// ����ũ��
	int m_iWidth;
	
	// ����ũ��
	int m_iHeight; 

protected:

	// Image�� Ÿ������
	int m_iType;	

// methods
public:

	// Constructor
	CImageObject();

	// Destructor
	~CImageObject();

	// Image�� ������ ��´�.
	int GetType();

	// Image�� ������ �����Ѵ�.
	void SetType( int iType );

	// Image�� ���� ũ�⸦ ��´�.
	int GetWidth(); 
	
	// Image�� ���� ũ�⸦ ��´�.
	int GetHeight(); 

	// Image�� ���� ũ�⸦ �����Ѵ�.
	void SetWidth( int nWidth );
	
	// Image�� ���� ũ�⸦ �����Ѵ�.
	void SetHeight( int nHeight ); 
};


template <class T> 
class AFX_EXT_CLASS CImageTemplate : public CImageObject 
{
// attribute
protected:

	// 1DImage Pointer�� �ε��� ������ ������ Pointer
	// 2D ������ Array�� ������ �ش�.
	T** m_p2DImage;		

	// ���� Image ������ �� �ִ� 1D Array
	T* m_p1DImage;

// methods
public:

	// Constructor
	CImageTemplate();

	// Destructor
	~CImageTemplate();

	// 1DImage�� �����͸� �ٷ� ���´�.
	T* Get1DImage();
	const T* Get1DImage() const;

	// 2DImage�� �����͸� �ٷ� ���´�.
	T** Get2DImage();
	const T** Get2DImage() const;

	// �޸��� �Ҵ�
	BOOL Alloc( int iWidth, int iHeight );

	// �Ҵ�� �޸��� ����
	BOOL Free();

	// �� �ȼ��� ������ ���´�.
	void GetPixel( T &pixel, int nX, int nY );

	// �� �ȼ��� ������ ���´�.
	T GetPixel( int nX, int nY );

	// �ȼ��� ������ �����Ѵ�.
	void SetPixel( T pixel, int nX, int nY );

	// �޸𸮰� �Ҵ�Ǿ����� �˾ƺ���.
	BOOL IsAlloc();

	// [] operator overloading
	T* operator[]( int iIndex ); 
};

//
// CImageTemplate Member Functions
//

template <class T> 
CImageTemplate<T>::CImageTemplate()
{
	m_p1DImage = NULL;
	m_p2DImage = NULL;
}

// Destructor
template <class T> 
CImageTemplate<T>::~CImageTemplate()
{
	if ( Free() == FALSE )
	{
		AfxMessageBox( "Free(): Memory Free Error" );
	}
}

// �޸��� �Ҵ�
template <class T> 
BOOL CImageTemplate<T>::Alloc( int iWidth, int iHeight )
{
	SetWidth( iWidth );
	SetHeight( iHeight );

	m_p1DImage = (T*)GlobalAlloc( GMEM_FIXED | GMEM_ZEROINIT, iWidth * iHeight * sizeof( T ) );

	if ( m_p1DImage == NULL ) return FALSE;
	
	m_p2DImage = new T*[ iHeight ];

	if ( m_p2DImage == NULL ) return FALSE;

	for( int iC = 0; iC < iHeight; iC++ ) m_p2DImage[iC] = (T*)( m_p1DImage + iWidth * iC );

	return TRUE;
}

// �Ҵ�� �޸��� ����
template <class T> 
BOOL CImageTemplate<T>::Free()
{
	if ( m_p1DImage == NULL ) return FALSE;
	
	delete []m_p2DImage;
	GlobalFree( (HGLOBAL)m_p1DImage );

	m_p1DImage = NULL;
	m_p2DImage = NULL;

	return TRUE;
}

// 1DImage�� �����͸� �ٷ� ���´�.
template <class T> 
T* CImageTemplate<T>::Get1DImage()
{
	return (T*)m_p1DImage;
}

template <class T> 
const T* CImageTemplate<T>::Get1DImage() const
{
	return (const T*)m_p1DImage;
}

// 2DImage�� �����͸� �ٷ� ���´�.
template <class T> 
T** CImageTemplate<T>::Get2DImage()
{
	return (T**)m_p2DImage;
}

template <class T> 
const T** CImageTemplate<T>::Get2DImage() const
{
	return (const T**)m_p2DImage;
}

// �޸𸮰� �Ҵ�Ǿ����� �˾ƺ���.
template <class T> 
BOOL CImageTemplate<T>::IsAlloc()
{
	return (m_p1DImage != NULL) ? TRUE : FALSE;
}

// �� �ȼ��� ������ ���´�.
template <class T> 
void CImageTemplate<T>::GetPixel( T &pixel, int iX, int iY )
{
	pixel = m_p2DImage[iX][iY];
}

// �� �ȼ��� ������ ���´�.
template <class T> 
T CImageTemplate<T>::GetPixel( int iX, int iY )
{
	return m_p2DImage[iX][iY];
}

// �ȼ��� ������ �����Ѵ�.
template <class T> 
void CImageTemplate<T>::SetPixel( T pixel, int iX, int iY )
{
	m_p2DImage[iX][iY] = pixel;
}

template <class T>
T* CImageTemplate<T>::operator[]( int iIndex ) 
{
	ASSERT( iIndex >= 0 && iIndex < GetHeight() );
	return m_p2DImage[iIndex];
}

class AFX_EXT_CLASS CImageByte : public CImageTemplate<BYTE> 
{
// methods
public:

	// Constructor	
	CImageByte();
	CImageByte( int iWidth, int iHeight );
	CImageByte( CImageByte& Object );
	CImageByte( CImageFloat& Object );
	CImageByte( CImageComplex& Object );
	CImageByte( CImageRGB& Object );

	~CImageByte();

	// Operator overloading
	CImageByte& operator=( CImageByte& Object );
	CImageByte& operator=( CImageFloat& Object );
	CImageByte& operator=( CImageComplex& Object );
	CImageByte& operator=( CImageRGB& Object );
};

class AFX_EXT_CLASS CImageFloat : public CImageTemplate<FLOAT> 
{
// methods
public:

	// Constructor	
	CImageFloat();
	CImageFloat( int iWidth, int iHeight );
	CImageFloat( CImageByte& Object );
	CImageFloat( CImageFloat& Object );
	CImageFloat( CImageComplex& Object );
	CImageFloat( CImageRGB& Object );

	~CImageFloat();

	// Operator overloading
	CImageFloat& operator=( CImageByte& Object );
	CImageFloat& operator=( CImageFloat& Object );
	CImageFloat& operator=( CImageComplex& Object );
	CImageFloat& operator=( CImageRGB& Object );
};

class AFX_EXT_CLASS CImageComplex : public CImageTemplate<COMPLEX> 
{
// methods
public:

	// Constructor
	CImageComplex();
	CImageComplex( int iWidth, int iHeight );
	CImageComplex( CImageByte& Object );
	CImageComplex( CImageFloat& Object );
	CImageComplex( CImageComplex& Object );
	CImageComplex( CImageRGB& Object );

	~CImageComplex();

	// Operator overloading
	CImageComplex& operator=( CImageByte& Object );
	CImageComplex& operator=( CImageFloat& Object );
	CImageComplex& operator=( CImageComplex& Object );
	CImageComplex& operator=( CImageRGB& Object );

	// �ȼ��� Imaginary �����͸� ��´�.
	void GetPixelIm( float &fIm, int iX, int iY );

	// �ȼ��� Imaginary �����͸� ��´�.
	float GetPixelIm( int iX, int iY );

	// �ȼ��� Real �����͸� ��´�.
	void GetPixelRe( float &fRe, int iX, int iY );

	// �ȼ��� Real �����͸� ��´�.
	float GetPixelRe( int iX, int iY );

	// �ȼ��� Imaginary ������ �����.
	void SetPixelIm( float fIm, int iX, int iY ); 

	// �ȼ��� Real ������ �����.
	void SetPixelRe( float fRe, int iX, int iY );
};

class AFX_EXT_CLASS CImageRGB : public CImageTemplate<RGB> 
{
// methods
public:

	// Constructor	
	CImageRGB();
	CImageRGB( int iWidth, int iHeight );
	CImageRGB( CImageByte& Object );
	CImageRGB( CImageFloat& Object );
	CImageRGB( CImageComplex& Object );
	CImageRGB( CImageRGB& Object );

	~CImageRGB();

	// Operator overloading
	CImageRGB& operator=( CImageByte& Object );
	CImageRGB& operator=( CImageFloat& Object );
	CImageRGB& operator=( CImageComplex& Object );
	CImageRGB& operator=( CImageRGB& Object );

	// �ȼ��� R �����͸� ��´�.
	void GetPixelR( BYTE &byR, int iX, int iY );
	BYTE GetPixelR( int iX, int iY );

	// �ȼ��� G �����͸� ��´�.
	void GetPixelG( BYTE &byG, int iX, int iY );
	BYTE GetPixelG( int iX, int iY );
	
	// �ȼ��� B �����͸� ��´�.
	void GetPixelB( BYTE &byB, int iX, int iY );
	BYTE GetPixelB( int iX, int iY );

	// �ȼ��� RGB �����͸� ��´�.
	void GetPixelRGB( RGB &rgb, int iX, int iY );
	RGB GetPixelRGB( int iX, int iY );

	// �ȼ��� R,G,B���� ����.
	void SetPixelR( BYTE byR, int iX, int iY ); 
	void SetPixelG( BYTE byG, int iX, int iY ); 
	void SetPixelB( BYTE byB, int iX, int iY ); 

	// �ȼ��� RGB ������ �����.
	void SetPixelRGB( RGB rgb, int iX, int iY );
	void SetPixelRGB( BYTE byR, BYTE byG, BYTE byB, int iX, int iY );

	// YUV�� RGB�� ��ȯ
	YUV RGBtoYUV( RGB rgb );
	RGB YUVtoRGB( YUV yuv );

	// HSI�� RGB�� ��ȯ
	HSI RGBtoHSI( RGB rgb );
	RGB HSItoRGB( HSI hsi );
};


#endif // __IMAGE_CLASS