
// MMFCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MMFC.h"
#include "MMFCDlg.h"
#include "afxdialogex.h"
#include <nmmintrin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define MAX_COUNT 6

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{

public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMMFCDlg 对话框



CMMFCDlg::CMMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture, m_picture);///非常重要 DDX_Control 将控件与变量绑定，这样就可以通过变量来控制控件等
}

BEGIN_MESSAGE_MAP(CMMFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON1, &CMMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMMFCDlg::OnBnClickedButton2)
	//ON_BN_CLICKED(IDCANCEL, &CMMFCDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CMMFCDlg::OnBnClickedButton3)
	
	//ON_BN_SETFOCUS(IDC_R1, &CMMFCDlg::OnBnSetfocusR1)
END_MESSAGE_MAP()


// CMMFCDlg 消息处理程序
CBitmap bmps[MAX_COUNT];
CBitmap bitmap;
CBitmap mmp[MAX_COUNT];
int m = 0, n = 1;
BOOL CMMFCDlg::OnInitDialog()
{


	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		bitmap.LoadBitmap(IDB_BITMAP1);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	//bmps[0].LoadBitmap(IDB_BITMAP1);
	// TODO: 在此添加额外的初始化代码
	for (int i = 0; i < MAX_COUNT; i++)
	{
		bmps[i].LoadBitmap(IDB_BITMAP1 + i);
	}

	for (int i = 0; i < MAX_COUNT; i++)
	{
		mmp[i].LoadBitmap(IDB_BITMAP1 + i);
	}
	//GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	//GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	//GetDlgItem(IDC_BUTTON3)->EnableWindow(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMMFCDlg::OnPaint()
{


	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		
		
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialog::OnPaint();

	}
	Ondraw();


}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMMFCDlg::getCBitmapFade(int m, int n)
{


	BITMAP b;                //声明位图文件b
	bmps[m].GetBitmap(&b);   //获取第一张图片
	int size = b.bmHeight*b.bmWidthBytes;  //获取位图字节数

	BYTE *lp1 = new BYTE[size];
	bmps[m].GetBitmapBits(size, lp1);   //获取第一张图片的像素列

	BITMAP b2;               //声明位图文件b2
	bmps[n].GetBitmap(&b2);  //获取第二张图片，由于图片大小相等，所以不用重复计算字节数

	BYTE *lp2 = new BYTE[size];
	bmps[n].GetBitmapBits(size, lp2);  //获取第二张图片的像素列

	//GetBitmapBits（）函数将指定位图的位拷贝到缓冲区里。
	BYTE *lp3 = new BYTE[size];    //用来显示中间图像


	int *rgb = new int[8];
	BYTE *pic1 = new BYTE[8];
	BYTE *pic2 = new BYTE[8];
	BYTE *pic3 = new BYTE[8];
	BYTE *pic4 = new BYTE[8];
	BYTE *pic5 = new BYTE[8];
	BYTE *pic6 = new BYTE[8];
	BYTE *pic7 = new BYTE[8];
	BYTE *pic8 = new BYTE[8];
	for (int fade = 127; fade >= 0; fade--) //
	{
		for (int y = 0; y < b.bmHeight; y++)
		{
			#pragma omp parallel forprivatc(4,x) //4线程并行计算
			for (int x = 0; x < b.bmWidth; x = x + 8)  //4个两像素同时计算
			{ 
				rgb[0] = y*b.bmWidthBytes + x * 4;
				rgb[1] = y*b.bmWidthBytes + (x + 1) * 4;
				rgb[2] = y*b.bmWidthBytes + (x + 2) * 4;
				rgb[3] = y*b.bmWidthBytes + (x + 3) * 4;
				rgb[4] = y*b.bmWidthBytes + (x + 4) * 4;
				rgb[5] = y*b.bmWidthBytes + (x + 5) * 4;
				rgb[6] = y*b.bmWidthBytes + (x + 6) * 4;
				rgb[7] = y*b.bmWidthBytes + (x + 7) * 4;
				//A的两个像素8字节
				pic1[0] = lp1[rgb[0]];
				pic1[1] = lp1[rgb[0] + 1];
				pic1[2] = lp1[rgb[0] + 2];
				pic1[3] = lp1[rgb[0] + 3];
				pic1[4] = lp1[rgb[1]];
				pic1[5] = lp1[rgb[1] + 1];
				pic1[6] = lp1[rgb[1] + 2];
				pic1[7] = lp1[rgb[1] + 3];
				//B的两个像素8字节
				pic2[0] = lp2[rgb[0]];
				pic2[1] = lp2[rgb[0] + 1];
				pic2[2] = lp2[rgb[0] + 2];
				pic2[3] = lp2[rgb[0] + 3];
				pic2[4] = lp2[rgb[1]];
				pic2[5] = lp2[rgb[1] + 1];
				pic2[6] = lp2[rgb[1] + 2];
				pic2[7] = lp2[rgb[1] + 3];
				//A的两个像素8字节
				pic3[0] = lp1[rgb[2]];
				pic3[1] = lp1[rgb[2] + 1];
				pic3[2] = lp1[rgb[2] + 2];
				pic3[3] = lp1[rgb[2] + 3];
				pic3[4] = lp1[rgb[3]];
				pic3[5] = lp1[rgb[3] + 1];
				pic3[6] = lp1[rgb[3] + 2];
				pic3[7] = lp1[rgb[3] + 3];
				//B的两个像素8字节
				pic4[0] = lp2[rgb[2]];
				pic4[1] = lp2[rgb[2] + 1];
				pic4[2] = lp2[rgb[2] + 2];
				pic4[3] = lp2[rgb[2] + 3];
				pic4[4] = lp2[rgb[3]];
				pic4[5] = lp2[rgb[3] + 1];
				pic4[6] = lp2[rgb[3] + 2];
				pic4[7] = lp2[rgb[3] + 3];
				//A的两个像素8字节
				pic5[0] = lp1[rgb[4]];
				pic5[1] = lp1[rgb[4] + 1];
				pic5[2] = lp1[rgb[4] + 2];
				pic5[3] = lp1[rgb[4] + 3];
				pic5[4] = lp1[rgb[5]];
				pic5[5] = lp1[rgb[5] + 1];
				pic5[6] = lp1[rgb[5] + 2];
				pic5[7] = lp1[rgb[5] + 3];
				//B的两个像素8字节
				pic6[0] = lp2[rgb[4]];
				pic6[1] = lp2[rgb[4] + 1];
				pic6[2] = lp2[rgb[4] + 2];
				pic6[3] = lp2[rgb[4] + 3];
				pic6[4] = lp2[rgb[5]];
				pic6[5] = lp2[rgb[5] + 1];
				pic6[6] = lp2[rgb[5] + 2];
				pic6[7] = lp2[rgb[5] + 3];
				//A的两个像素8字节
				pic7[0] = lp1[rgb[6]];
				pic7[1] = lp1[rgb[6] + 1];
				pic7[2] = lp1[rgb[6] + 2];
				pic7[3] = lp1[rgb[6] + 3];
				pic7[4] = lp1[rgb[7]];
				pic7[5] = lp1[rgb[7] + 1];
				pic7[6] = lp1[rgb[7] + 2];
				pic7[7] = lp1[rgb[7] + 3];
				//B的两个像素8字节
				pic8[0] = lp2[rgb[6]];
				pic8[1] = lp2[rgb[6] + 1];
				pic8[2] = lp2[rgb[6] + 2];
				pic8[3] = lp2[rgb[6] + 3];
				pic8[4] = lp2[rgb[7]];
				pic8[5] = lp2[rgb[7] + 1];
				pic8[6] = lp2[rgb[7] + 2];
				pic8[7] = lp2[rgb[7] + 3];
				__m128i xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6,xmm7,xmm9;
				__m128i xmm8 = _mm_setzero_si128();
				//初始化寄存器

				xmm0 = _mm_set_epi16(fade, fade, fade, fade, fade, fade, fade, fade);//8个fade因子装入寄存器

				xmm1 = _mm_loadu_si128((__m128i*)pic1);//A的两个像素分量装入寄存器
				xmm1 = _mm_unpacklo_epi8(xmm1, xmm8);//8个一位解紧缩至16位
				xmm2 = _mm_loadu_si128((__m128i*)pic2);//B的两个像素分量装入寄存器
				xmm2 = _mm_unpacklo_epi8(xmm2, xmm8);//8个一位解紧缩至16位
				xmm1 = _mm_sub_epi16(xmm1, xmm2);   //A-B
				xmm1 = _mm_mullo_epi16(xmm1, xmm0);//8个16位乘法
				xmm1 = _mm_srai_epi16(xmm1, 7);//右移7位，相当于除127
				xmm1 = _mm_add_epi16(xmm1, xmm2);//加法
				xmm1 = _mm_packus_epi16(xmm1,xmm8);//16个一位紧缩为8位
				lp3[rgb[0]] = _mm_extract_epi8(xmm1, 0);//依次提取每个整型，放入待显示像素数组
				lp3[rgb[0] + 1] = _mm_extract_epi8(xmm1, 1);
				lp3[rgb[0] + 2] = _mm_extract_epi8(xmm1, 2);
				lp3[rgb[0] + 3] = _mm_extract_epi8(xmm1, 3);
				lp3[rgb[1]] = _mm_extract_epi8(xmm1, 4);
				lp3[rgb[1] + 1] = _mm_extract_epi8(xmm1, 5);
				lp3[rgb[1] + 2] = _mm_extract_epi8(xmm1, 6);
				lp3[rgb[1] + 3] = _mm_extract_epi8(xmm1, 7);

				xmm3 = _mm_loadu_si128((__m128i*)pic3);
				xmm3 = _mm_unpacklo_epi8(xmm3, xmm8);
				xmm4 = _mm_loadu_si128((__m128i*)pic4);
				xmm4 = _mm_unpacklo_epi8(xmm4, xmm8);
				xmm3 = _mm_sub_epi16(xmm3, xmm4);
				xmm3 = _mm_mullo_epi16(xmm3, xmm0);
				xmm3 = _mm_srai_epi16(xmm3, 7);
				xmm3 = _mm_add_epi16(xmm3, xmm4);
				xmm3 = _mm_packus_epi16(xmm3, xmm8);
				lp3[rgb[2]] = _mm_extract_epi8(xmm3, 0);
				lp3[rgb[2] + 1] = _mm_extract_epi8(xmm3, 1);
				lp3[rgb[2] + 2] = _mm_extract_epi8(xmm3, 2);
				lp3[rgb[2] + 3] = _mm_extract_epi8(xmm3, 3);
				lp3[rgb[3]] = _mm_extract_epi8(xmm3, 4);
				lp3[rgb[3] + 1] = _mm_extract_epi8(xmm3, 5);
				lp3[rgb[3] + 2] = _mm_extract_epi8(xmm3, 6);
				lp3[rgb[3] + 3] = _mm_extract_epi8(xmm3, 7);

				xmm5 = _mm_loadu_si128((__m128i*)pic5);
				xmm5 = _mm_unpacklo_epi8(xmm5, xmm8);
				xmm6 = _mm_loadu_si128((__m128i*)pic6);
				xmm6 = _mm_unpacklo_epi8(xmm6, xmm8);
				xmm5 = _mm_sub_epi16(xmm5, xmm6);
				xmm5 = _mm_mullo_epi16(xmm5, xmm0);
				xmm5 = _mm_srai_epi16(xmm5, 7);
				xmm5 = _mm_add_epi16(xmm5, xmm6);
				xmm5 = _mm_packus_epi16(xmm5, xmm8);  //packs的区别
				lp3[rgb[4]] = _mm_extract_epi8(xmm5, 0);
				lp3[rgb[4] + 1] = _mm_extract_epi8(xmm5, 1);
				lp3[rgb[4] + 2] = _mm_extract_epi8(xmm5, 2);
				lp3[rgb[4] + 3] = _mm_extract_epi8(xmm5, 3);
				lp3[rgb[5]] = _mm_extract_epi8(xmm5, 4);
				lp3[rgb[5] + 1] = _mm_extract_epi8(xmm5, 5);
				lp3[rgb[5] + 2] = _mm_extract_epi8(xmm5, 6);
				lp3[rgb[5] + 3] = _mm_extract_epi8(xmm5, 7);

				xmm7 = _mm_loadu_si128((__m128i*)pic7);
				xmm7 = _mm_unpacklo_epi8(xmm7, xmm8);
				xmm9 = _mm_loadu_si128((__m128i*)pic8);
				xmm9 = _mm_unpacklo_epi8(xmm9, xmm8);
				xmm7 = _mm_sub_epi16(xmm7, xmm9);
				xmm7 = _mm_mullo_epi16(xmm7, xmm0);
				xmm7 = _mm_srai_epi16(xmm7, 7);
				xmm7 = _mm_add_epi16(xmm7, xmm9);
				xmm7 = _mm_packus_epi16(xmm7, xmm8);  //packs的区别
				lp3[rgb[6]] = _mm_extract_epi8(xmm7, 0);
				lp3[rgb[6] + 1] = _mm_extract_epi8(xmm7, 1);
				lp3[rgb[6] + 2] = _mm_extract_epi8(xmm7, 2);
				lp3[rgb[6] + 3] = _mm_extract_epi8(xmm7, 3);
				lp3[rgb[7]] = _mm_extract_epi8(xmm7, 4);
				lp3[rgb[7] + 1] = _mm_extract_epi8(xmm7, 5);
				lp3[rgb[7] + 2] = _mm_extract_epi8(xmm7, 6);
				lp3[rgb[7] + 3] = _mm_extract_epi8(xmm7, 7);
				//余下3个两像素的计算类似
			}
		}
		bitmap.SetBitmapBits(size, lp3);
		Ondraw();

	}
	delete lp1;
	delete lp2;
	delete lp3;
}

void CMMFCDlg::Ondraw(void)
{

	CDC * dc = m_picture.GetDC();  //就是获取当前窗口的类对象指针，以便进行下一步的编程
	CDC mDC;
	mDC.CreateCompatibleDC(dc);  //该函数创建一个与指定设备兼容的内存设备上下文环境（DC）

	CRect rc;
	m_picture.GetClientRect(&rc);  //该函数获取窗口客户区的大小
	HBITMAP hOldbmp = (HBITMAP)mDC.SelectObject(bitmap); //该函数选择一对象到指定的设备上下文环境中

	dc->BitBlt(0, 0, rc.Width(), rc.Height(), &mDC, 0, 0, SRCCOPY);//该函数对指定的源设备环境区域中的像素进行位块(bit_block)转换
	mDC.SelectObject(hOldbmp);
	mDC.DeleteDC();

}

 int s = 0;

void CMMFCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int mp = GetCheckedRadioButton(IDC_R1, IDC_R2);
	CStatic *p = (CStatic *)GetDlgItem(IDC_P);
	if (mp == IDC_R1) {
		if (s > 0)
		{
			p->SetBitmap(mmp[--s]);
			m = s; n = s +1;
		}
		if (s == 0) { 
		s = 6;
		m = 5; n = 4;
		}
	}
	else if(mp == IDC_R2){
		if (m == 0 && n == 1) {
			getCBitmapFade(0, 5);
			m = 5; n = 4;			
		}
		else {
			if (m > n) {
				getCBitmapFade(m, n);
				s = n;
				m--; n--;
				if (m == 0 && n == -1) { m = 0; n = 1; }
			}
			else {
				m--; n--;
				getCBitmapFade(n, m);
				s = m;
			}
			
		}
	}
	else AfxMessageBox(_T("请选择模式！"));
}


void CMMFCDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int mp = GetCheckedRadioButton(IDC_R1, IDC_R2);
	CStatic *p = (CStatic *)GetDlgItem(IDC_P);

	if (mp == IDC_R1) {	
			p->SetBitmap(mmp[s++]);
			m = s-1; n = s ;
			if (s == MAX_COUNT) s = 0;
	}
	else if(mp == IDC_R2)
	{
		
		if (m == 5 && n == 6) {
			getCBitmapFade(5, 0);
			m = 0; n = 1;
		}
		else {
			getCBitmapFade(m, n);
			m++; n++;
			s = n;
		}
	}
	else AfxMessageBox(_T("请选择模式！"));
}



void CMMFCDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int mp=GetCheckedRadioButton(IDC_R1,IDC_R2);
	CStatic *p = (CStatic *)GetDlgItem(IDC_P);
	if (mp == IDC_R1)
	{
		
		//AfxMessageBox(_T("普通模式"));
		
		if (s == MAX_COUNT) {
			s = 0;
			for (; s < MAX_COUNT; s++)
			{
				//mmp[s].LoadBitmap(IDB_BITMAP7 + s);
				p->SetBitmap(mmp[s]);
				Sleep(1000);
			}
			if (s == MAX_COUNT) { AfxMessageBox(_T("播放完毕！")); s = 0; }
		}
		else {
			for (; s < MAX_COUNT; s++)
			{
				//mmp[s].LoadBitmap(IDB_BITMAP7 + s);
				p->SetBitmap(mmp[s]);
				Sleep(1000);
				
			}
			if (s == MAX_COUNT) { AfxMessageBox(_T("播放完毕！")); s = 0; }
		}
		
	}
	else if (mp == IDC_R2)
	{
		if(m==5&&n==6){
			getCBitmapFade(5, 0); Sleep(1000);
			m = 0; n = 1;
			for (; m < 5, n<6; m++, n++)  //AfxMessageBox(_T("淡入淡出"));
			{
				getCBitmapFade(m, n);
				Sleep(1000);
			}
			if (n == 6 && m == 5) { AfxMessageBox(_T("播放完毕！")); }
		}
		else {
			m = 0; n = 1;
			for (; m < 5, n<6; m++, n++)  //AfxMessageBox(_T("淡入淡出"));
			{
				getCBitmapFade(m, n);
				Sleep(1000);
			}
			if (n == 6 && m == 5) { AfxMessageBox(_T("播放完毕！")); }

		}
	}
	else AfxMessageBox(_T("请选择模式！"));
}






