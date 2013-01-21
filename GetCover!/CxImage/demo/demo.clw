; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDemoDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "demo.h"
LastPage=0

ClassCount=24
Class1=CDemoApp
Class2=CDemoDoc
Class3=CDemoView
Class4=CMainFrame

ResourceCount=28
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_DEMOTYPE
Class5=CAboutDlg
Class6=CChildFrame
Resource4=IDD_THRESHOLD (Neutral)
Resource5=IDD_REPAIR (Neutral)
Resource6=IDD_DWNURL (Neutral)
Class7=DlgRotate
Resource7=IDD_OPTIONS (Neutral)
Class8=DlgCapture
Resource8=IDD_COLORIZE (Neutral)
Resource9=IDR_MAINFRAME (Neutral)
Class9=DlgResample
Resource10=IDD_OPACITY (Neutral)
Resource11=IDD_FFT (Neutral)
Class10=DlgDecBpp
Class11=DlgIncBpp
Resource12=IDD_COMBINE (Neutral)
Class12=DlgOptions
Resource13=IDD_DECBPP (Neutral)
Class13=DlgDither
Resource14=IDD_ABOUTBOX (Neutral)
Class14=DlgThreshold
Resource15=IDM_CXIMAGE1
Class15=DlgColorize
Resource16=IDR_DEMOTYPE (Neutral)
Resource17=IDD_CAPTURE (Neutral)
Class16=DlgOpacity
Resource18=IDD_DITHER (Neutral)
Class17=DlgURL
Resource19=IDD_RESAMPLE (Neutral)
Class18=DlgGamma
Resource20=IDD_INCBPP (Neutral)
Class19=DlgHisto
Resource21=IDR_TOOLBAR1
Class20=DlgPalette
Resource22=IDD_HISTO (Neutral)
Class21=DlgCombine
Resource23=IDM_CXIMAGE1 (Neutral)
Resource24=IDR_TOOLBAR1 (Neutral)
Resource25=IDD_ROTATE (Neutral)
Class22=DlgFFT
Resource26=IDD_PALETTE (Neutral)
Class23=DlgRepair
Resource27=IDD_GAMMA (Neutral)
Class24=DlgText
Resource28=IDD_TEXT (Neutral)

[CLS:CDemoApp]
Type=0
HeaderFile=demo.h
ImplementationFile=demo.cpp
Filter=W
LastObject=CDemoApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CDemoDoc]
Type=0
HeaderFile=demoDoc.h
ImplementationFile=demoDoc.cpp
Filter=N
LastObject=ID_WINDOW_DUPLICATE
BaseClass=CDocument
VirtualFilter=DC

[CLS:CDemoView]
Type=0
HeaderFile=demoView.h
ImplementationFile=demoView.cpp
Filter=C
LastObject=ID_CXIMAGE_CONTOUR
BaseClass=CScrollView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=W
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=CChildFrame
BaseClass=CMDIChildWnd
VirtualFilter=mfWC

[CLS:CAboutDlg]
Type=0
HeaderFile=demo.cpp
ImplementationFile=demo.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
CommandCount=8
Command8=ID_APP_ABOUT

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_DEMOTYPE]
Type=1
Class=CDemoView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
CommandCount=21
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[CLS:DlgRotate]
Type=0
HeaderFile=DlgRotate.h
ImplementationFile=DlgRotate.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=DlgRotate

[CLS:DlgCapture]
Type=0
HeaderFile=dlgcapture.h
ImplementationFile=dlgcapture.cpp
BaseClass=CDialog
LastObject=DlgCapture
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX (Neutral)]
Type=1
Class=CAboutDlg
ControlCount=18
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342242817
Control4=IDC_STATIC,static,1342308481
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352

[MNU:IDR_DEMOTYPE (Neutral)]
Type=1
Class=CDemoView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_SELECTSOURCE
Command7=ID_FILE_ACQUIRE
Command8=ID_FILE_CAPTURE
Command9=ID_FILE_PRINT
Command10=ID_FILE_PRINT_PREVIEW
Command11=ID_FILE_PRINT_SETUP
Command12=ID_FILE_MRU_FILE1
Command13=ID_APP_EXIT
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_REDO
Command16=ID_EDIT_CUT
Command17=ID_EDIT_COPY
Command18=ID_EDIT_PASTE
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_VIEW_HISTOGRAM
Command22=ID_VIEW_PALETTE
Command23=ID_VIEW_TOOLS_MOVE
Command24=ID_VIEW_TOOLS_SELECT
Command25=ID_VIEW_TOOLS_ZOOM
Command26=ID_VIEW_TOOLS_TEXT
Command27=ID_VIEW_MENUSTYLE_NORMAL
Command28=ID_VIEW_MENUSTYLE_XP
Command29=ID_STRETCH_MODE
Command30=ID_VIEW_FULLSCREEN
Command31=ID_VIEW_ZOOMIN
Command32=ID_VIEW_ZOOMOUT
Command33=ID_VIEW_NORMALVIEWING11
Command34=ID_IMAGE_FROM_BITMAP
Command35=ID_CXIMAGE_LOADJPEGRESOURCE
Command36=ID_CXIMAGE_LOADICONRESOURCE
Command37=ID_CXIMAGE_LOADPNGRESOURCE
Command38=ID_CXIMAGE_LOADGIFRESOURCE
Command39=ID_CXIMAGE_LOADTIFRESOURCE
Command40=ID_TRANSFORM_ELLIPSE
Command41=ID_CXIMAGE_DEMOSAVEMULTIPAGETIFF
Command42=ID_CXIMAGE_DEMOSAVEANIMATEDGIF
Command43=ID_CXIMAGE_DOWNLOADFROMURL
Command44=ID_CXIMAGE_MIRROR
Command45=ID_CXIMAGE_FLIP
Command46=ID_CXIMAGE_NEGATIVE
Command47=ID_CXIMAGE_ROTATEL
Command48=ID_CXIMAGE_ROTATER
Command49=ID_CXIMAGE_ROTATE
Command50=ID_CXIMAGE_RESAMPLE
Command51=ID_CXIMAGE_CROP
Command52=ID_CXIMAGE_SETTRANSPARENCY
Command53=ID_CXIMAGE_REMOVETRANSPARENCY
Command54=ID_CXIMAGE_OPACITY
Command55=ID_CXIMAGE_REMOVEALPHACHANNEL
Command56=ID_CXIMAGE_ALPHACHANNEL_SPLIT
Command57=ID_CXIMAGE_ALPHASTRIP
Command58=ID_CXIMAGE_INVETALPHA
Command59=ID_CXIMAGE_ALPHAPALETTETOGGLE
Command60=ID_CXIMAGE_ALPHACREATE
Command61=ID_CXIMAGE_GRAYSCALE
Command62=ID_CXIMAGE_DITHER
Command63=ID_CXIMAGE_DECREASEBPP
Command64=ID_CXIMAGE_INCREASEBPP
Command65=ID_CXIMAGE_HISTOGRAM_STRETCH
Command66=ID_CXIMAGE_HISTOGRAM_EQUALIZE
Command67=ID_CXIMAGE_HISTOGRAM_NORMALIZE
Command68=ID_CXIMAGE_HISTOGRAM_LOG
Command69=ID_CXIMAGE_HISTOGRAM_ROOT
Command70=ID_CXIMAGE_OPTIONS
Command71=ID_CXIMAGE_THRESHOLD
Command72=ID_CXIMAGE_COLORIZE
Command73=ID_CXIMAGE_GAMMA
Command74=ID_CXIMAGE_LIGHTEN
Command75=ID_CXIMAGE_DARKEN
Command76=ID_CXIMAGE_CONTRAST
Command77=ID_CXIMAGE_LESSCONTRAST
Command78=ID_CXIMAGE_ADDNOISE
Command79=ID_CXIMAGE_MEDIAN
Command80=ID_CXIMAGE_ERODE
Command81=ID_CXIMAGE_DILATE
Command82=ID_CXIMAGE_CONTOUR
Command83=ID_CXIMAGE_JITTER
Command84=ID_CXIMAGE_BLUR
Command85=ID_CXIMAGE_SOFTEN
Command86=ID_CXIMAGE_GAUSSIAN3X3
Command87=ID_CXIMAGE_GAUSSIAN5X5
Command88=ID_CXIMAGE_SHARPEN
Command89=ID_CXIMAGE_EDGE
Command90=ID_CXIMAGE_EMBOSS
Command91=ID_CXIMAGE_PSEUDOCOLORS
Command92=ID_CXIMAGE_SPLITRGB
Command93=ID_CXIMAGE_SPLITHSL
Command94=ID_CXIMAGE_SPLITYUV
Command95=ID_CXIMAGE_SPLITYIQ
Command96=ID_CXIMAGE_SPLITXYZ
Command97=ID_CXIMAGE_SPLITCMYK
Command98=ID_CXIMAGE_COMBINE
Command99=ID_CXIMAGE_FFT
Command100=ID_CXIMAGE_REPAIR
Command101=ID_WINDOW_NEW
Command102=ID_WINDOW_CASCADE
Command103=ID_WINDOW_TILE_HORZ
Command104=ID_WINDOW_ARRANGE
Command105=ID_WINDOW_CLOSEALL
Command106=ID_WINDOW_DUPLICATE
Command107=ID_APP_ABOUT
CommandCount=107

[TB:IDR_MAINFRAME (Neutral)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_FILE_ACQUIRE
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_REDO
Command11=ID_VIEW_ZOOMIN
Command12=ID_VIEW_NORMALVIEWING11
Command13=ID_VIEW_ZOOMOUT
Command14=ID_VIEW_TOOLS_MOVE
Command15=ID_VIEW_TOOLS_SELECT
Command16=ID_VIEW_TOOLS_ZOOM
Command17=ID_VIEW_TOOLS_TEXT
Command18=ID_VIEW_HISTOGRAM
Command19=ID_VIEW_PALETTE
Command20=ID_CXIMAGE_OPTIONS
Command21=ID_APP_ABOUT
CommandCount=21

[MNU:IDR_MAINFRAME (Neutral)]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SELECTSOURCE
Command4=ID_FILE_ACQUIRE
Command5=ID_FILE_CAPTURE
Command6=ID_FILE_PRINT_SETUP
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_EDIT_PASTE
Command10=ID_VIEW_TOOLBAR
Command11=ID_VIEW_STATUS_BAR
Command12=ID_VIEW_HISTOGRAM
Command13=ID_VIEW_MENUSTYLE_NORMAL
Command14=ID_VIEW_MENUSTYLE_XP
Command15=ID_VIEW_FULLSCREEN
Command16=ID_IMAGE_FROM_BITMAP
Command17=ID_CXIMAGE_LOADJPEGRESOURCE
Command18=ID_CXIMAGE_LOADICONRESOURCE
Command19=ID_CXIMAGE_LOADPNGRESOURCE
Command20=ID_CXIMAGE_LOADGIFRESOURCE
Command21=ID_CXIMAGE_LOADTIFRESOURCE
Command22=ID_CXIMAGE_DEMOSAVEMULTIPAGETIFF
Command23=ID_CXIMAGE_DEMOSAVEANIMATEDGIF
Command24=ID_CXIMAGE_DOWNLOADFROMURL
Command25=ID_APP_ABOUT
CommandCount=25

[ACL:IDR_MAINFRAME (Neutral)]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_VIEW_ZOOMIN
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_VIEW_NORMALVIEWING11
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_ZOOMOUT
Command16=ID_EDIT_CUT
Command17=ID_EDIT_REDO
Command18=ID_EDIT_UNDO
CommandCount=18

[DLG:IDD_ROTATE (Neutral)]
Type=1
Class=DlgRotate
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_CAPTURE (Neutral)]
Type=1
Class=DlgCapture
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728835

[MNU:IDM_CXIMAGE1]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_REDO
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_CXIMAGE_MIRROR
Command6=ID_CXIMAGE_FLIP
Command7=ID_CXIMAGE_NEGATIVE
Command8=ID_CXIMAGE_THRESHOLD
Command9=ID_CXIMAGE_COLORIZE
Command10=ID_CXIMAGE_GAMMA
Command11=ID_CXIMAGE_LIGHTEN
Command12=ID_CXIMAGE_DARKEN
Command13=ID_CXIMAGE_CONTRAST
Command14=ID_CXIMAGE_ADDNOISE
Command15=ID_CXIMAGE_MEDIAN
Command16=ID_CXIMAGE_ERODE
Command17=ID_CXIMAGE_DILATE
Command18=ID_CXIMAGE_BLUR
Command19=ID_CXIMAGE_SOFTEN
Command20=ID_CXIMAGE_SHARPEN
Command21=ID_CXIMAGE_EDGE
Command22=ID_CXIMAGE_EMBOSS
Command23=ID_CXIMAGE_ROTATEL
Command24=ID_CXIMAGE_ROTATER
Command25=ID_CXIMAGE_ROTATE
Command26=ID_CXIMAGE_RESAMPLE
Command27=ID_CXIMAGE_CROP
Command28=ID_CXIMAGE_SETTRANSPARENCY
Command29=ID_CXIMAGE_REMOVETRANSPARENCY
Command30=ID_CXIMAGE_OPACITY
Command31=ID_CXIMAGE_REMOVEALPHACHANNEL
Command32=ID_CXIMAGE_ALPHASTRIP
Command33=ID_CXIMAGE_INVETALPHA
Command34=ID_CXIMAGE_ALPHAPALETTETOGGLE
Command35=ID_CXIMAGE_GRAYSCALE
Command36=ID_CXIMAGE_DITHER
Command37=ID_CXIMAGE_DECREASEBPP
Command38=ID_CXIMAGE_INCREASEBPP
Command39=ID_CXIMAGE_SPLITRGB
Command40=ID_CXIMAGE_SPLITYUV
Command41=ID_CXIMAGE_SPLITHSL
Command42=ID_CXIMAGE_PSEUDOCOLORS
Command43=ID_CXIMAGE_COMBINE
Command44=ID_CXIMAGE_OPTIONS
CommandCount=44

[DLG:IDD_RESAMPLE (Neutral)]
Type=1
Class=DlgResample
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_RADIO1,button,1342308361
Control6=IDC_RADIO2,button,1342177289
Control7=IDC_RADIO3,button,1342177289

[CLS:DlgResample]
Type=0
HeaderFile=DlgResample.h
ImplementationFile=DlgResample.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_CXIMAGE_FILTERS_LESSCONTRAST
VirtualFilter=dWC

[CLS:DlgDecBpp]
Type=0
HeaderFile=DlgDecBpp.h
ImplementationFile=DlgDecBpp.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK1
VirtualFilter=dWC

[CLS:DlgIncBpp]
Type=0
HeaderFile=DlgIncBpp.h
ImplementationFile=DlgIncBpp.cpp
BaseClass=CDialog
Filter=D
LastObject=65535
VirtualFilter=dWC

[CLS:DlgOptions]
Type=0
HeaderFile=DlgOptions.h
ImplementationFile=DlgOptions.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDEXIF

[CLS:DlgDither]
Type=0
HeaderFile=DlgDither.h
ImplementationFile=DlgDither.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_RADIO1

[DLG:IDD_THRESHOLD (Neutral)]
Type=1
Class=DlgThreshold
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:DlgThreshold]
Type=0
HeaderFile=DlgThreshold.h
ImplementationFile=DlgThreshold.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=DlgThreshold

[DLG:IDD_DECBPP (Neutral)]
Type=1
Class=DlgDecBpp
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342308361
Control4=IDC_STATIC,button,1342177287
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_RADIO3,button,1342177289
Control7=IDC_STATIC,button,1342177287
Control8=IDC_RADIO4,button,1342308361
Control9=IDC_RADIO5,button,1342177289
Control10=IDC_CHECK1,button,1342242819

[DLG:IDD_INCBPP (Neutral)]
Type=1
Class=DlgIncBpp
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342308361
Control4=65535,button,1342177287
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_RADIO3,button,1342177289

[DLG:IDD_OPTIONS (Neutral)]
Type=1
Class=DlgOptions
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT3,edit,1350631552
Control9=IDC_STATIC,button,1342177287
Control10=IDC_RADIO1,button,1342308361
Control11=IDC_RADIO2,button,1342177289
Control12=IDC_RADIO3,button,1476395017
Control13=IDC_RADIO4,button,1342177289
Control14=IDC_RADIO5,button,1342177289
Control15=IDC_RADIO6,button,1342177289
Control16=IDC_RADIO7,button,1476395017
Control17=IDEXIF,button,1342242816

[DLG:IDD_DITHER (Neutral)]
Type=1
Class=DlgDither
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342308361
Control4=IDC_RADIO2,button,1342177289

[DLG:IDD_COLORIZE (Neutral)]
Type=1
Class=DlgColorize
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT3,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT4,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT5,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_RADIO3,button,1342308361
Control14=IDC_RADIO4,button,1342177289

[CLS:DlgColorize]
Type=0
HeaderFile=DlgColorize.h
ImplementationFile=DlgColorize.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=DlgColorize

[TB:IDR_TOOLBAR1]
Type=1
Class=?
Command1=ID_VIEW_NORMALVIEWING11
Command2=ID_CXIMAGE_OPTIONS
Command3=ID_APP_EXIT
Command4=ID_VIEW_ZOOMIN
Command5=ID_VIEW_ZOOMOUT
Command6=ID_CXIMAGE_ROTATE
Command7=ID_CXIMAGE_FLIP
Command8=ID_CXIMAGE_MIRROR
Command9=ID_CXIMAGE_RESAMPLE
Command10=ID_CXIMAGE_CROP
Command11=ID_CXIMAGE_GRAYSCALE
Command12=ID_CXIMAGE_NEGATIVE
Command13=ID_CXIMAGE_DECREASEBPP
Command14=ID_CXIMAGE_INCREASEBPP
Command15=ID_CXIMAGE_SPLITCHANNELS
Command16=ID_BUTTON32842
Command17=ID_CXIMAGE_SETTRANSPARENCY
Command18=ID_CXIMAGE_REMOVETRANSPARENCY
Command19=ID_VIEW_PALETTE
CommandCount=19

[DLG:IDD_OPACITY (Neutral)]
Type=1
Class=DlgOpacity
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:DlgOpacity]
Type=0
HeaderFile=DlgOpacity.h
ImplementationFile=DlgOpacity.cpp
BaseClass=CDialog
Filter=D
LastObject=IDCANCEL
VirtualFilter=dWC

[CLS:DlgURL]
Type=0
HeaderFile=DlgURL.h
ImplementationFile=DlgURL.cpp
BaseClass=CDialog
Filter=D
LastObject=DlgURL
VirtualFilter=dWC

[DLG:IDD_DWNURL (Neutral)]
Type=1
Class=DlgURL
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATUS,static,1342308352
Control6=IDC_URL,edit,1350631552

[DLG:IDD_GAMMA (Neutral)]
Type=1
Class=DlgGamma
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:DlgGamma]
Type=0
HeaderFile=DlgGamma.h
ImplementationFile=DlgGamma.cpp
BaseClass=CDialog
Filter=D
LastObject=DlgGamma
VirtualFilter=dWC

[DLG:IDD_HISTO (Neutral)]
Type=1
Class=DlgHisto
ControlCount=1
Control1=IDC_LOG,button,1342242819

[CLS:DlgHisto]
Type=0
HeaderFile=DlgHisto.h
ImplementationFile=DlgHisto.cpp
BaseClass=CDialogBar
Filter=C
LastObject=DlgHisto
VirtualFilter=dWC

[DLG:IDD_PALETTE (Neutral)]
Type=1
Class=DlgPalette
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177298
Control4=IDC_LOAD,button,1342242816
Control5=IDC_SAVE,button,1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_RADIO1,button,1342308361
Control8=IDC_RADIO2,button,1342177289
Control9=IDC_RADIO3,button,1342177289
Control10=IDC_CHECK2,button,1342242819
Control11=IDC_BAR,static,1342312448

[CLS:DlgPalette]
Type=0
HeaderFile=DlgPalette.h
ImplementationFile=DlgPalette.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_COMBINE (Neutral)]
Type=1
Class=DlgCombine
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO1,combobox,1344339971
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_COMBO2,combobox,1344339971
Control8=IDC_COMBO3,combobox,1344339971
Control9=IDC_STATIC,static,1342308352
Control10=IDC_COMBO4,combobox,1344339971
Control11=IDC_COMBO5,combobox,1344339971
Control12=IDC_COMBO6,combobox,1344339971
Control13=IDC_COMBO7,combobox,1344339971
Control14=IDC_COMBO8,combobox,1344339971
Control15=IDC_COMBO9,combobox,1344339971
Control16=IDC_STATIC,static,1342308352

[CLS:DlgCombine]
Type=0
HeaderFile=DlgCombine.h
ImplementationFile=DlgCombine.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=DlgCombine

[TB:IDR_TOOLBAR1 (Neutral)]
Type=1
Class=?
Command1=ID_VIEW_NORMALVIEWING11
Command2=ID_CXIMAGE_OPTIONS
Command3=ID_APP_EXIT
Command4=ID_VIEW_ZOOMIN
Command5=ID_VIEW_ZOOMOUT
Command6=ID_CXIMAGE_ROTATE
Command7=ID_CXIMAGE_FLIP
Command8=ID_CXIMAGE_MIRROR
Command9=ID_CXIMAGE_RESAMPLE
Command10=ID_CXIMAGE_CROP
Command11=ID_CXIMAGE_GRAYSCALE
Command12=ID_CXIMAGE_NEGATIVE
Command13=ID_CXIMAGE_DECREASEBPP
Command14=ID_CXIMAGE_INCREASEBPP
Command15=ID_CXIMAGE_SPLITCHANNELS
Command16=ID_BUTTON32842
Command17=ID_CXIMAGE_SETTRANSPARENCY
Command18=ID_CXIMAGE_REMOVETRANSPARENCY
Command19=ID_VIEW_PALETTE
CommandCount=19

[MNU:IDM_CXIMAGE1 (Neutral)]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_REDO
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_CXIMAGE_MIRROR
Command6=ID_CXIMAGE_FLIP
Command7=ID_CXIMAGE_NEGATIVE
Command8=ID_CXIMAGE_THRESHOLD
Command9=ID_CXIMAGE_COLORIZE
Command10=ID_CXIMAGE_GAMMA
Command11=ID_CXIMAGE_LIGHTEN
Command12=ID_CXIMAGE_DARKEN
Command13=ID_CXIMAGE_CONTRAST
Command14=ID_CXIMAGE_LESSCONTRAST
Command15=ID_CXIMAGE_ADDNOISE
Command16=ID_CXIMAGE_MEDIAN
Command17=ID_CXIMAGE_ERODE
Command18=ID_CXIMAGE_DILATE
Command19=ID_CXIMAGE_CONTOUR
Command20=ID_CXIMAGE_JITTER
Command21=ID_CXIMAGE_BLUR
Command22=ID_CXIMAGE_SOFTEN
Command23=ID_CXIMAGE_GAUSSIAN3X3
Command24=ID_CXIMAGE_GAUSSIAN5X5
Command25=ID_CXIMAGE_SHARPEN
Command26=ID_CXIMAGE_EDGE
Command27=ID_CXIMAGE_EMBOSS
Command28=ID_CXIMAGE_PSEUDOCOLORS
Command29=ID_CXIMAGE_SPLITRGB
Command30=ID_CXIMAGE_SPLITHSL
Command31=ID_CXIMAGE_SPLITYUV
Command32=ID_CXIMAGE_SPLITYIQ
Command33=ID_CXIMAGE_SPLITXYZ
Command34=ID_CXIMAGE_SPLITCMYK
Command35=ID_CXIMAGE_COMBINE
Command36=ID_CXIMAGE_FFT
Command37=ID_CXIMAGE_REPAIR
Command38=ID_CXIMAGE_ROTATEL
Command39=ID_CXIMAGE_ROTATER
Command40=ID_CXIMAGE_ROTATE
Command41=ID_CXIMAGE_RESAMPLE
Command42=ID_CXIMAGE_CROP
Command43=ID_CXIMAGE_SETTRANSPARENCY
Command44=ID_CXIMAGE_REMOVETRANSPARENCY
Command45=ID_CXIMAGE_OPACITY
Command46=ID_CXIMAGE_REMOVEALPHACHANNEL
Command47=ID_CXIMAGE_ALPHACHANNEL_SPLIT
Command48=ID_CXIMAGE_ALPHASTRIP
Command49=ID_CXIMAGE_INVETALPHA
Command50=ID_CXIMAGE_ALPHAPALETTETOGGLE
Command51=ID_CXIMAGE_ALPHACREATE
Command52=ID_CXIMAGE_GRAYSCALE
Command53=ID_CXIMAGE_DITHER
Command54=ID_CXIMAGE_DECREASEBPP
Command55=ID_CXIMAGE_INCREASEBPP
Command56=ID_CXIMAGE_HISTOGRAM_STRETCH
Command57=ID_CXIMAGE_HISTOGRAM_EQUALIZE
Command58=ID_CXIMAGE_HISTOGRAM_NORMALIZE
Command59=ID_CXIMAGE_HISTOGRAM_LOG
Command60=ID_CXIMAGE_HISTOGRAM_ROOT
Command61=ID_CXIMAGE_OPTIONS
CommandCount=61

[DLG:IDD_FFT (Neutral)]
Type=1
Class=DlgFFT
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_REAL,combobox,1344339971
Control4=IDC_IMAG,combobox,1344339971
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_CHECK1,button,1342242819
Control8=IDC_CHECK3,button,1342242819
Control9=IDC_CHECK4,button,1342242819

[CLS:DlgFFT]
Type=0
HeaderFile=DlgFFT.h
ImplementationFile=DlgFFT.cpp
BaseClass=CDialog
Filter=D
LastObject=DlgFFT
VirtualFilter=dWC

[DLG:IDD_REPAIR (Neutral)]
Type=1
Class=DlgRepair
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_COMBO9,combobox,1344339971

[CLS:DlgRepair]
Type=0
HeaderFile=DlgRepair.h
ImplementationFile=DlgRepair.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=DlgRepair

[DLG:IDD_TEXT (Neutral)]
Type=1
Class=DlgText
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=ID_FONT,button,1342242816

[CLS:DlgText]
Type=0
HeaderFile=DlgText.h
ImplementationFile=DlgText.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=DlgText

