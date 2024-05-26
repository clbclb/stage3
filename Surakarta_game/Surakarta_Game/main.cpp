#include "choose_dialog.h"
#include "main_window.h"
#include <QApplication>
#include<Client.h>
#include<Server.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // test_num=argc;
    if(argc==1){
        FLAG:
        ChooseDlg dlg;
        dlg.resize(600,600);
        if(dlg.exec()!=QDialog::Accepted)
            return 0;
        MainWnd wnd("127.0.0.1","10086","BLACK",dlg._selected);
        int e=a.exec();
        if(e==RESTART)//
        {
            goto FLAG;
        }
        return a.exec();
    }
    // wnd.show();


    //create Client_Team_1.exe
    if(argc==4){
        FLAG1:
        MainWnd wnd(argv[1],argv[2],argv[3],3);
        int e=a.exec();
        if(e==RESTART)//
        {
            goto FLAG1;
        }
        return a.exec();
    }

    //create Server_Team_1.exe
    if(argc==2){
        FLAG2:
        MainWnd wnd("127.0.0.1",argv[1],"BLACK",2);

        int e=a.exec();
        if(e==RESTART)//
        {
            goto FLAG2;
        }
        return a.exec();
    }
    return a.exec();
}
