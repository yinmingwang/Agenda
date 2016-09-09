#include"Meeting.h"
#include<iostream>
using namespace std;

Meeting::Meeting() :sponsor_(""), participator_(""), title_("") {
    Date d1(1000, 1, 1, 0, 0);
    Date d2(9999, 12, 31, 23, 59);
    startDate_ = d1;
    endDate_ = d2;
}

Meeting::Meeting(string sponsor, string participator,
          Date startTime, Date endTime, string title)
        :sponsor_(sponsor), participator_(participator),
         startDate_(startTime), endDate_(endTime),
         title_(title) {}
//
string Meeting::getSponsor() const {
    return sponsor_;
}

void Meeting::setSponsor(string sponsor) {
    sponsor_ = sponsor;
}
//
string Meeting::getParticipator() const {
    return participator_;
}

void Meeting::setParticipator(string participator) {
    participator_ = participator;
}
//
Date Meeting::getStartDate() const {
    return startDate_;
}

void Meeting::setStartDate(Date startDate) {
        startDate_ = startDate;
}
//
Date Meeting::getEndDate() const {
    return endDate_;
}

void Meeting::setEndDate(Date endDate) {
        endDate_ = endDate;
}
//
string Meeting::getTitle() const {
    return title_;
}

void Meeting::setTitle(string title) {
    title_ = title;
}

