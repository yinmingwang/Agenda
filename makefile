Agenda: agenda.cpp AgendaUI.o AgendaService.o Storage.o Meeting.o Date.o User.o
	g++ -Wall agenda.cpp AgendaUI.o AgendaService.o Storage.o Meeting.o Date.o User.o  -std=c++11 -o Agenda -std=c++11
AgendaUI.o: AgendaUI.h AgendaUI.cpp
	g++ -c AgendaUI.cpp -std=c++11
AgendaService.o: AgendaService.h AgendaService.cpp
	g++ -c AgendaService.cpp -std=c++11
Storage.o: Storage.cpp Storage.h
	g++ -c Storage.cpp -std=c++11
Meeting.o: Meeting.cpp Meeting.h
	g++ -c Meeting.cpp
Date.o: Date.cpp Date.h
	g++ -c Date.cpp
User.o: User.cpp User.h
	g++ -c User.cpp
clean:
	rm *.o agenda.data

