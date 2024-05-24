#include "choose_dialog.h"
#include "main_window.h"
#include <QApplication>
#include<Client.h>
#include<Server.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // test_num=argc;
    /*
    FLAG:
    ChooseDlg dlg;
    dlg.resize(600,600);
    if(dlg.exec()!=QDialog::Accepted)
        return 0;
    MainWnd wnd(dlg._selected);
    // wnd.show();
    */

    //create Client_Team_1.exe
    // FLAG:
    // MainWnd wnd(argv[1],argv[2],argv[3],3);

    //create Server_Team_1.exe
    FLAG:
    MainWnd wnd(argv[1],2);

    int e=a.exec();
    if(e==RESTART)//
    {
        goto FLAG;
    }
    return a.exec();

}
