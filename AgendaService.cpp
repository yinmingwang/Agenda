#include"AgendaService.h"
#include"Storage.h"
#include<string>
#include<iostream>
using namespace std;

// con and de
AgendaService::AgendaService() {
    storage_ = Storage::getInstance();
}

AgendaService::~AgendaService() {
    delete storage_;
    //storage_->sync();
}

// User manip
bool AgendaService::userRegister(string userName, string password,string email, string phone) {
    list<User> l = storage_->queryUser( [userName](const User& u) { if (userName == u.getName()) return true; return false; } );

    if ( l.size() != 0 ) {
        return false;
    } else {
        User u(userName, password, email, phone);
        storage_->createUser(u);
        return true;
    }

}
//
bool AgendaService::userLogIn(string userName, string password) {
    list<User> l = storage_->queryUser( [userName](const User& u) { if (userName == u.getName()) return true; return false; } );
    if ( l.size() == 0 ) {
        return false;
    } else {
        if ( l.front().getPassword() != password ) {
            return false;
        } else {
            return true;
        }
    }
}
//
bool AgendaService::deleteUser(string userName, string password) {
    if ( storage_->deleteUser( [userName](const User& u) { if (userName == u.getName()) return true; return false; } ) ) {
            storage_->deleteMeeting( [userName](const Meeting& m) { if (userName == m.getSponsor() || userName == m.getParticipator()) return true; return false; } );
            return true;
    } else {
        return false;
    }
}
//
list<User> AgendaService::listAllUsers() {
    list<User> l = storage_->queryUser( [](const User& u) { return true; } );
    return l;
}

//
bool AgendaService::createMeeting(string userName, string title, string participator, string startDate, string endDate) {
/*
    // two people
    if ( userName == participator ) {
        //cout << "same" << endl;
        return false;
    }
*/
    // time
    // same???
    if ( Date::stringToDate(startDate) >= Date::stringToDate(endDate) ) {
        // cout << "time" << endl;
        return false;
    }
    if ( !Date::isValid(Date::stringToDate(startDate)) || !Date::isValid(Date::stringToDate(endDate)) ) {
        return false;
    }
/*
    // title same
    list<Meeting> l = storage_->queryMeeting( [title](const Meeting& m) { if ( title == m.getTitle() ) return true; return false; } );
    if ( l.size() != 0 ) {
        //cout << "sametitle" << endl;
        return false;
    }
*/
    // two user
    list<User> l1 = storage_->queryUser( [userName, participator](const User& u) { if (userName == u.getName() || participator == u.getName() ) return true; return false; } );
        //cout << "size" << l1.size() << endl;
    if ( l1.size() != 2 ) {
        return false;
    }
    
    
    list<Meeting> l2 = storage_->queryMeeting( [userName, participator](const Meeting& m) { if ( userName == m.getSponsor() || userName == m.getParticipator() || participator == m.getSponsor() || participator == m.getParticipator() ) return true; return false; } );
    // time
    list<Meeting>::iterator ita = l2.begin();
    for ( ; ita != l2.end(); ita++ ) {
        
        if ( (Date::stringToDate(startDate) >= ita->getStartDate() && Date::stringToDate(startDate) < ita->getEndDate()) || (Date::stringToDate(endDate) > ita->getStartDate() && Date::stringToDate(endDate) <= ita->getEndDate()) || (Date::stringToDate(startDate) <= ita->getStartDate() && Date::stringToDate(endDate) >= ita->getEndDate()) ) {
            return false;
        }
       
    }
    // title
    ita = l2.begin();
    for ( ; ita != l2.end(); ita++ ) {
        if ( ita->getTitle() == title ) {
            return false;
        }
    }
    
    // create meeting
    Meeting m(userName, participator, Date::stringToDate(startDate), Date::stringToDate(endDate), title);
    storage_->createMeeting(m);
    return true;
}
//
list<Meeting> AgendaService::meetingQuery(string userName, string title) {
    list<Meeting> l = storage_->queryMeeting( [userName, title](const Meeting& m) { if ( (userName == m.getSponsor() || userName == m.getParticipator()) && title == m.getTitle() ) return true; return false;} );
    return l;
}
//
list<Meeting> AgendaService::meetingQuery(string userName, string startDate, string endDate) {
    list<Meeting> l = listAllMeetings(userName);
    list<Meeting> l1;
    list<Meeting>::iterator ita = l.begin();
    if ( !Date::isValid(Date::stringToDate(startDate)) || !Date::isValid(Date::stringToDate(endDate)) || Date::stringToDate(startDate) > Date::stringToDate(endDate)) {
        return l1;
    }
    for ( ; ita != l.end(); ita++ ) {
        if ( (Date::stringToDate(startDate) >= ita->getStartDate() && Date::stringToDate(startDate) <= ita->getEndDate()) || (Date::stringToDate(endDate) >= ita->getStartDate() && Date::stringToDate(endDate) <= ita->getEndDate()) || (Date::stringToDate(startDate) <= ita->getStartDate() && Date::stringToDate(endDate) >= ita->getEndDate()) ) {
           l1.push_back(*ita);
        }
    }
    return l1;
}
//
list<Meeting> AgendaService::listAllMeetings(string userName) {
    list<Meeting> l = storage_->queryMeeting( [userName](const Meeting& m) { if ( userName == m.getSponsor() || userName == m.getParticipator() ) return true; return false; } );
    return l;
}
//
list<Meeting> AgendaService::listAllSponsorMeetings(string userName) {
    list<Meeting> l = storage_->queryMeeting( [userName](const Meeting& m) { if ( userName == m.getSponsor() ) return true; return false; } );
    return l;
}
//
list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
    list<Meeting> l = storage_->queryMeeting( [userName](const Meeting& m) { if ( userName == m.getParticipator() ) return true; return false;} );
    return l;
}
//
bool AgendaService::deleteMeeting(string userName, string title) {
        if ( storage_->deleteMeeting( [userName, title](const Meeting& m) { if (userName == m.getSponsor() && title == m.getTitle() ) return true; return false; } ) ) {
            return true;
        } else {
            return false;
        }
}
//
bool AgendaService::deleteAllMeetings(string userName) {
        if ( storage_->deleteMeeting( [userName](const Meeting& m) { if (userName == m.getSponsor() ) return true; return false; } ) ) {
            return true;
        } else {
            return false;
        }
}

//
void AgendaService::startAgenda() {
    storage_ = Storage::getInstance();
}

void AgendaService::quitAgenda() {
    storage_->sync();
    exit(0);
}

