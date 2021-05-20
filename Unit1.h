//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
#define ull unsigned long long
//---------------------------------------------------------------------------
#include "Unit2.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "trayicon.h"
#include <Menus.hpp>
#include <time.h>
#include <vector.h>
#include <ImgList.hpp>

//---------------------------------------------------------------------------

class czas
{
        protected:
        ull sekund, minut, godzin, dni;
        short kto;

        public:
        void do_napisu(TLabel * napis);

        void minela_sekunda();

        czas::czas();

        friend void zapisanie_danych(czas, bool);
};

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TTimer *Timer1;
        TLabel *Label2;
        TTrayIcon *TrayIcon1;
        TPopupMenu *PopupMenu1;
        TMenuItem *Otwrz1;
        TMenuItem *Zakocz1;
        TMenuItem *Zakocz2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TMenuItem *Tryb1;
        TMenuItem *dayhourminutesecond1;
        TMenuItem *HourMinuteSecond1;
        TMenuItem *MinuteSecond1;
        TMenuItem *Seconds1;
        TTimer *Timer2;
        TImageList *ImageList1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall TrayIcon1Click(TObject *Sender);
        void __fastcall TrayIcon1Destroy(TObject *Sender);
        void __fastcall Otwrz1Click(TObject *Sender);
        void __fastcall Zakocz2Click(TObject *Sender);
        void __fastcall Zakocz1Click(TObject *Sender);
        void __fastcall dayhourminutesecond1Click(TObject *Sender);
        void __fastcall HourMinuteSecond1Click(TObject *Sender);
        void __fastcall MinuteSecond1Click(TObject *Sender);
        void __fastcall Seconds1Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
        ull time;
        czas Turuch;
        czas Ttyg, Tmies, Tinst;
        bool byl_zapis;
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        __fastcall ~TForm1();
};

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
