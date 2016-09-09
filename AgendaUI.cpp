#include"AgendaUI.h"
#include<iostream>
#include<iomanip>
#include<list>
using namespace std;

AgendaUI::AgendaUI() {
    userName_ = "";
    userPassword_ = "";
}

void AgendaUI::OperationLoop() {
    startAgenda();
    while ( 1 ) {
        if ( !executeOperation(getOperation()) ) {
            cout << "[error] command not found" << endl;
        }
    }
}

void AgendaUI::startAgenda() {
    cout << "----------------------------------------------------------Agenda-------------------------------------------" << endl
         << "Action :" << endl
         << "l  - log in Agenda by username and password" << endl
         << "r  - register an Agenda account" << endl
         << "q  - quit Agenda" << endl
         << "----------------------------------------------------------Agenda-------------------------------------------" << endl
         << endl;
}

string AgendaUI::getOperation() {
    if ( userName_ == "" ) {
        cout << "Agenda : ~$ ";
    } else {
        cout << "Agenda@" << userName_ << " : # ";
    }
    string s;
    cin >> s;
    return s;
}    
    
bool AgendaUI::executeOperation(string op) {
    if ( userName_ == "" ) {
        if ( op == "l" ) {
            userLogIn();
            return true;
        } else if ( op == "r" ) {
            userRegister();
            return true;
        } else if ( op == "q" ) {
            quitAgenda();
            return true;
        } else {
            return false;
        }
    } else {
         if (op == "o") {
            userLogOut();
            return true;
        } else if (op == "dc") {
            deleteUser();
            return true;
        } else if (op == "lu") {
            listAllUsers();
            return true;
        } else if (op == "cm") {
            createMeeting();
            return true;
        } else if (op == "la") {
            listAllMeetings();
            return true;
        } else if (op == "las") {
            listAllSponsorMeetings();
            return true;
        } else if (op == "lap") {
            listAllParticipateMeetings();
            return true;
        } else if (op == "qm") {
            queryMeetingByTitle();
            return true;
        } else if (op == "qt") {
            queryMeetingByTimeInterval();
            return true;
        } else if (op == "dm") {
            deleteMeetingByTitle();
            return true;
        } else if (op == "da") {
            deleteAllMeetings();
            return true;
        } else {
            return false;
        }
    }
}

void AgendaUI::printDirection() {
        cout << "----------------------------------------------------------Agenda-------------------------------------------" << endl << endl
             << "Action :" << endl
             << "o  - log out Agenda" << endl
             << "dc  - delete Agenda account" << endl
             << "lu  - list all Agenda users" << endl
             << "cm  - create a meeting" << endl
             << "la  - list all meetings" << endl
             << "las  - list all sponsor meetings" << endl
             << "lap  - list all participator meetings" << endl
             << "qm  - query meeting by title" << endl
             << "qt  - query meeting by time interval" << endl
             << "dm  - delete meeting by title" << endl
             << "da  - delete all meetings" << endl
             << "----------------------------------------------------------Agenda-------------------------------------------" << endl
             << endl << endl;
}

void AgendaUI::userLogIn() {
    cout << "[log in] [user name] [password]" << endl
         << "[log in] ";
    string n, p;
    cin >> n >> p;
    if ( agendaService_.userLogIn(n, p) ) {
        userName_ = n;
        userPassword_ = p;
        cout << "[log in] succeed!" << endl << endl;
        printDirection();
    } else {
        cout << "[error] log in fail!" << endl << endl;
        startAgenda();
    }
}

void AgendaUI::userRegister() {
    cout << "[register] [user name] [password] [email] [phone]" << endl
         << "[register] ";
    string u, pw, e, p;
    cin >> u >> pw >> e >> p;
    if ( agendaService_.userRegister(u, pw, e, p) ) {
        cout << "register succeed!" << endl << endl;
    } else {
        cout << "[error] register fail!" << endl << endl;
    }
    startAgenda();
}

void AgendaUI::quitAgenda() {
    agendaService_.quitAgenda();
}
//
void AgendaUI::userLogOut() {
    userName_ = "";
    userPassword_ = "";
    startAgenda();
}
//
void AgendaUI::deleteUser() {
    agendaService_.deleteUser(userName_, userPassword_);
    cout << "[delete agenda account] succeed!" << endl << endl;
    userName_ = "";
    userPassword_ = "";
    startAgenda();
}

void AgendaUI::listAllUsers() {
    cout << "[list all users]" << endl << endl
         << setw(20) << left << "name"
         << setw(20) << left << "email"
         << setw(20) << left << "phone" << endl;
    list<User> l = agendaService_.listAllUsers();
    list<User>::iterator it = l.begin();
    for ( ; it != l.end(); it++ ) {
        cout << setw(20) << left << it->getName()
             << setw(20) << left << it->getEmail()
             << setw(20) << left << it->getPhone() << endl;
    }
    cout << endl;
    printDirection();
}

void AgendaUI::createMeeting() {
    cout << "[create meeting] [title] [participator] [start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]" << endl;
    cout << "[create meeting] ";
    string a, b, c, d;
    cin >> a >> b >> c >> d;
    bool e = agendaService_.createMeeting(userName_, a, b, c, d);
    if ( e ) {
        cout << "[create meeting] succeed!" << endl;
    }
    else {
        cout << "[error] create meeting fail!" << endl;
    }
    printDirection();
}

void AgendaUI::listAllMeetings() {
    cout << "[list all meetings]" << endl << endl;
    list<Meeting> m;
    m = agendaService_.listAllMeetings(userName_);
    printMeetings(m);
    printDirection();
}

void AgendaUI::listAllSponsorMeetings() {
    cout << "[list all sponsor meetings]" << endl << endl;
    list<Meeting> m;
    m = agendaService_.listAllSponsorMeetings(userName_);
    printMeetings(m);
    printDirection();
}

void AgendaUI::listAllParticipateMeetings(void) {
    cout << "[list all participate meetings]" << endl << endl;
    list<Meeting> m;
    m = agendaService_.listAllParticipateMeetings(userName_);
    printMeetings(m);
    printDirection();
}

void AgendaUI::queryMeetingByTitle() {
    cout << "[query meeting] [title]:" << endl;
    cout << "[query meeting] ";
    string s;
    cin >> s;
    cout << endl;
    list<Meeting> m;
    list<Meeting>::iterator it;
    m = agendaService_.meetingQuery(userName_, s);
    it = m.begin();
    if ( m.size() == 0 ) {
        cout << "meeting not found!" << endl;
    } else {
        cout << setw(20) <<  left <<  "sponsor";
        cout << setw(20) <<  left <<  "participator";
        cout << setw(20) <<  left <<  "start time";
        cout << setw(20) <<  left <<  "end time" << endl;
        
        cout << setw(20) <<  left <<  it->getSponsor();
        cout << setw(20) <<  left <<  it->getParticipator();
        cout << setw(20) <<  left <<  Date::dateToString(it->getStartDate());
        cout << setw(20) <<  left <<  Date::dateToString(it->getEndDate());
        cout << endl << endl;
    }
    printDirection();
}

void AgendaUI::queryMeetingByTimeInterval() {
    cout << "[query meetings] [start time<yyyy-mm-dd/hh:mm>] [end time<yyyy-mm-dd/hh:mm>]" << endl;
    cout << "[query meetings] ";
    string a, b;
    cin >> a >> b;
    cout << endl;
    list<Meeting> m = agendaService_.meetingQuery(userName_, a, b);
    list<Meeting>::iterator it;
    if (m.size() == 0) {
        cout << "meeting not found!" << endl;
    } else {
        cout << "[query meetings]" << endl;
        printMeetings(m);
    }
    printDirection();
}

void AgendaUI::deleteMeetingByTitle(void) {
    cout << "[delete meeting] [title]:" << endl;
    cout << "[delete meeting] ";
    string a;
    cin >> a;
    cout << endl << endl;
    if ( agendaService_.deleteMeeting(userName_, a)) {
        cout << "[delete meeting by title] succeed!" << endl;
    } else {
        cout << "[error] delete meeting fail!" << endl;
    }
    printDirection();
}

void AgendaUI::deleteAllMeetings(void) {
    if ( agendaService_.deleteAllMeetings(userName_) ) {
        cout << "[delete all meetings] succeed!" << endl;
    } else {
        cout << "[error] no meeting to be deleted!" << endl;
    }
    printDirection();
}

void AgendaUI::printMeetings(list<Meeting> meetings) {
    list<Meeting>::iterator it = meetings.begin();
    if ( meetings.size() == 0 ) {
            cout << "no meeting to be printed!";
    } else {
        cout << setw(20) <<  left <<  "title";
        cout << setw(20) <<  left <<  "sponsor";
        cout << setw(20) <<  left <<  "participator";
        cout << setw(20) <<  left <<  "start time";
        cout << setw(20) <<  left <<  "end time" << endl;
        for ( ; it != meetings.end(); it++) {
            cout << setw(20) <<  left <<  it->getTitle();
            cout << setw(20) <<  left <<  it->getSponsor();
            cout << setw(20) <<  left <<  it->getParticipator();
            cout << setw(20) <<  left <<  Date::dateToString(it->getStartDate());
            cout << setw(20) <<  left <<  Date::dateToString(it->getEndDate());
            cout << endl;
        }
    }
    cout << endl;
}

