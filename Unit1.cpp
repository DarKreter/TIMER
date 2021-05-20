//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream.h>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TForm1 *Form1;
short tryb;
//---------------------------------------------------------------------------
__fastcall TForm1::~TForm1()
{
        if(byl_zapis)
        {
                zapisanie_danych(Turuch, true);
        }
        else
        {
                zapisanie_danych(Turuch, false);
        }
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        byl_zapis = false;
        dayhourminutesecond1 -> Checked = true;
        tryb = 0;

        CreateDirectory("C:/Games", NULL);
        CreateDirectory("C:/Games/TIMER", NULL);
        fstream plik;
        plik.open("C:/Games/TIMER/dane.txt",ios::out | ios::app);
        plik.close();


}
//---------------------------------------------------------------------------
void zapisanie_danych(czas time, bool byl_zapis)
{
        fstream plik;   vector<string> dane;    string linia;
        plik.open("C:/Games/TIMER/dane.txt",ios::in);
        while(getline(plik,linia))
        {
                dane.push_back(linia);
        }
        plik.close();

        fstream file;
        file.open("C:/Games/TIMER/dane.txt",ios::out);
        for(ull i = 0;i < dane.size() - ( byl_zapis == false ? 0 : 2) ;i++)
        {
                file << dane[i]<<endl;
        }
        SYSTEMTIME x;
        GetLocalTime(&x);
        file    << (x.wDay < 10 ? "0":"") <<x.wDay
                <<(x.wMonth < 10 ? "0":"") <<x.wMonth <<x.wYear <<endl;
        file << (time.sekund < 10 ? "0":"") <<time.sekund << (time.minut < 10 ? "0":"")<< time.minut
        << (time.godzin < 10 ? "0":"") <<  time.godzin
        <<(time.dni < 10 ? "0":"") << time.dni;
        file.close();


}
//---------------------------------------------------------------------------
inline short dni_miesiac(short x)
{
        short suma = 0;
        switch(x)
        {
                case 12:
                        suma+=31;
                case 11:
                        suma+=30;
                case 10:
                        suma+=31;
                case 9:
                        suma+=30;
                case 8:
                        suma+=31;
                case 7:
                        suma+=31;
                case 6:
                        suma+=30;
                case 5:
                        suma+=31;
                case 4:
                        suma+=30;
                case 3:
                        suma+=31;
                case 2:
                        suma+=29;
                case 1:
                        suma+=31;
        }
        return suma;
}

//---------------------------------------------------------------------------
czas::czas ()
{
        dni = 0; godzin = 0; minut = 0; sekund = 0;
        static short x= 0;
        fstream plik;
        string linia;

        SYSTEMTIME st;
        GetLocalTime(&st);

        plik.open("C:/Games/TIMER/dane.txt");
        switch(x)
        {
          case 0:{      //uruchomienie  DZIALA

                dni = 0;
                godzin = 0;
                minut = 0;
                sekund = 0;
                break;
        }
        case 1:{        //tydzien

                short licznik = 0;
                while(getline(plik,linia))
                {
                        AnsiString x = linia.substr(0,2).c_str() , y = linia.substr(2,2).c_str(), z = linia.substr(4,linia.length() -  4).c_str();
                        ull wynik = StrToInt(x)
                                + dni_miesiac(StrToInt( y ) )
                                + 365 * StrToInt(z);
                        ull wynik_dzis =   st.wDay + dni_miesiac(st.wMonth) + st.wYear * 365;
                        if(licznik % 2 == 0     && wynik_dzis - wynik < 7)
                        {
                                getline(plik,linia);
                                licznik ++;

                                AnsiString kupa =    linia.substr(0,2).c_str();
                                sekund += StrToInt(kupa);

                                kupa =    linia.substr(2,2).c_str();
                                minut += StrToInt(kupa);

                                kupa =    linia.substr(4,2).c_str();
                                godzin += StrToInt(kupa);

                                kupa =    linia.substr(6, linia.length() - 6).c_str();
                                dni += StrToInt(kupa);
                        }
                        licznik ++;
                }
                break;
        }
        case 2:{        //miesiac
                 short licznik = 0;
                while(getline(plik,linia))
                {
                        AnsiString x = linia.substr(0,2).c_str() , y = linia.substr(2,2).c_str(), z = linia.substr(4,linia.length() -  4).c_str();
                        ull wynik = StrToInt(x)
                                + dni_miesiac(StrToInt( y ) )
                                + 365 * StrToInt(z);
                        ull wynik_dzis =   st.wDay + dni_miesiac(st.wMonth) + st.wYear * 365;
                        if(licznik % 2 == 0     && wynik_dzis - wynik < 31)
                        {
                                getline(plik,linia);
                                licznik ++;

                                AnsiString kupa =    linia.substr(0,2).c_str();
                                sekund += StrToInt(kupa);

                                kupa =    linia.substr(2,2).c_str();
                                minut += StrToInt(kupa);

                                kupa =    linia.substr(4,2).c_str();
                                godzin += StrToInt(kupa);

                                kupa =    linia.substr(6, linia.length() - 6).c_str();
                                dni += StrToInt(kupa);
                        }
                        licznik ++;
                }
                break;
        }
        case 3:{        //instalacja  DZIALA
                short licznik = 0;
                while(getline(plik,linia))
                {
                        if(licznik % 2 == 1)
                        {
                                AnsiString kupa =    linia.substr(0,2).c_str();
                                sekund += StrToInt(kupa);

                                kupa =    linia.substr(2,2).c_str();
                                minut += StrToInt(kupa);

                                kupa =    linia.substr(4,2).c_str();
                                godzin += StrToInt(kupa);

                                kupa =    linia.substr(6, linia.length() - 6).c_str();
                                dni += StrToInt(kupa);
                        }
                        licznik ++;
                }
                break;
        }
        }
        plik.close();

        if(sekund >= 60)
        {
                minut += (sekund / 60);
                sekund -= (sekund/60) * 60;
        }
        if(minut >= 60)
        {
                godzin += (minut / 60);
                minut -= (minut/60) * 60;
        }
        if(godzin >= 24)
        {
                dni += (godzin / 24);
                godzin -= (godzin/24) * 24;
        }

        x++;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        Turuch.minela_sekunda();
        Ttyg.minela_sekunda();
        Tmies.minela_sekunda();
        Tinst.minela_sekunda();


        Turuch.do_napisu(Label2);
        Ttyg.do_napisu(Label7);
        Tmies.do_napisu(Label8);
        Tinst.do_napisu(Label9);



}
//---------------------------------------------------------------------------
void czas::do_napisu(TLabel * napis)
{
        string co_wpisac;
        fstream plik;
        switch(tryb)
        {
        case 0:{
                plik.open("C:/Games/TIMER/roboczy.txt",ios::out);
                plik    <<(dni <10 ? "0":"")<< dni<<" dni, "
                        <<(godzin <10 ? "0":"")<<godzin<<" godzin, "
                        <<(minut <10 ? "0":"")<<minut<<" minut, "
                        <<(sekund <10 ? "0":"")<<sekund<<" sekund";
                        napis -> Font -> Size = 14;
                plik.close();
                break;
        }
        case 1:{
                plik.open("C:/Games/TIMER/roboczy.txt",ios::out);
                plik    <<(godzin+dni*24 <10 ? "0":"")<<godzin+dni*24<<" godzin, "
                        <<(minut <10 ? "0":"")<<minut<<" minut, "
                        <<(sekund <10 ? "0":"")<<sekund<<" sekund";
                        napis -> Font -> Size = 18;
                plik.close();
                break;
        }
        case 2:{
                ull przejsciowy = minut + godzin*60 + dni *24*60;
                plik.open("C:/Games/TIMER/roboczy.txt",ios::out);
                plik    <<(przejsciowy <10 ? "0":"")<<przejsciowy<<" minut, "
                        <<(sekund <10 ? "0":"")<<sekund<<" sekund";
                        napis -> Font -> Size = 20;
                plik.close();
                break;
        }
        case 3:{
                ull przejsciowy = sekund + minut*60 + godzin*60*60 + dni *24*60*60;
                plik.open("C:/Games/TIMER/roboczy.txt",ios::out);
                plik    <<(przejsciowy <10 ? "0":"")<<przejsciowy<<" sekund";
                        napis -> Font -> Size = 24;
                plik.close();
                break;
        }
        }

        //----------------------------------------------
        plik.open("C:/Games/TIMER/roboczy.txt",ios::in);
        getline(plik,co_wpisac);
        plik.close();
        napis -> Caption = co_wpisac.c_str();
}
//---------------------------------------------------------------------------
void czas::minela_sekunda()
{
        if(sekund == 59)
        {
                if(minut == 59)
                {
                        if(godzin == 23)
                        {
                                dni ++;
                                godzin = 0;
                                minut = 0;
                                sekund = 0;
                        }
                        else
                        {
                                godzin ++;
                                minut = 0;
                                sekund = 0;
                        }
                }
                else
                {
                        minut++;
                        sekund = 0;
                }
        }
        else
        {
                sekund++;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrayIcon1Click(TObject *Sender)
{
        Show();
        Application->BringToFront();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TrayIcon1Destroy(TObject *Sender)
{
       TrayIcon1Click(TrayIcon1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Otwrz1Click(TObject *Sender)
{
        Show();
        Application -> BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zakocz2Click(TObject *Sender)
{

        if(Application->MessageBoxA("Zamkniêcie programu mo¿e spowodowaæ utratê danych!\nCzy napewno chcesz kontynuowaæ?","Potwierdzenie",MB_YESNO  | MB_ICONQUESTION)
         == IDYES)
         {
                Application -> Terminate();
         }
        //Zapytanie o potwierdzenie z haslem

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Zakocz1Click(TObject *Sender)
{
        Show();
        Application -> BringToFront();

        Form2 -> ShowModal();
        //Okienko z informacja
}
//---------------------------------------------------------------------------


void __fastcall TForm1::dayhourminutesecond1Click(TObject *Sender)
{
       if(dayhourminutesecond1 -> Checked == false)
       {
            dayhourminutesecond1 -> Checked = true;

            HourMinuteSecond1 -> Checked = false;
            MinuteSecond1 -> Checked = false;
            Seconds1 -> Checked = false;

            tryb = 0;
       }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::HourMinuteSecond1Click(TObject *Sender)
{
        if(HourMinuteSecond1 -> Checked == false)
        {
                HourMinuteSecond1 -> Checked = true;

                dayhourminutesecond1 -> Checked = false;
                MinuteSecond1 -> Checked = false;
                Seconds1 -> Checked = false;

                tryb = 1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MinuteSecond1Click(TObject *Sender)
{
        if(MinuteSecond1 -> Checked == false)
       {
                MinuteSecond1 -> Checked = true;

                HourMinuteSecond1 -> Checked = false;
                dayhourminutesecond1 -> Checked = false;
                Seconds1 -> Checked = false;

                tryb = 2;
       }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Seconds1Click(TObject *Sender)
{
        if(Seconds1 -> Checked == false)
       {
                Seconds1 -> Checked = true;

                HourMinuteSecond1 -> Checked = false;
                dayhourminutesecond1 -> Checked = false;
                MinuteSecond1 -> Checked = false;

                tryb = 3;
       }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
        if(byl_zapis)
        {
                zapisanie_danych(Turuch, true);
        }
        else
        {
                byl_zapis = true;
                zapisanie_danych(Turuch, false);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
               Action=caNone;
              Form1 -> Visible = false;

}
//---------------------------------------------------------------------------

