#include "choose_dialog.h"
#include "main_window.h"
#include <QApplication>
#include<Client.h>
#include<Server.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FLAG:
    ChooseDlg dlg;
    dlg.resize(600,600);
    if(dlg.exec()!=QDialog::Accepted)
        return 0;

    if(dlg._selected<=1){
        MainWnd wnd(dlg._selected);
        int e=a.exec();
        if(e==RESTART)//
        {
            goto FLAG;
        }
        return a.exec();
    }
    else if(dlg._selected==2){
        Server server;
        server.show();
        return a.exec();
    }
    else{
        Client client;
        client.show();
        return a.exec();
    }
    // wnd.show();
    int e=a.exec();
    if(e==RESTART)//
    {
        goto FLAG;
    }
    return a.exec();

}
