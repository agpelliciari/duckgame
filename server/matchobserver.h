#ifndef LIB_MatchObserver_H
#define LIB_MatchObserver_H

// definimos la clase pero no hace falta incluir la dependencia.
class Event;


// Por ahora esta clase abstracta/interface
// Tiene de proposito remover dependencias, no hay porque tener una dependencia directa
// del matchstate en el player container.
class MatchObserver {
public:
    // Por ahora un match observer solo encapsula un recibidor de eventos.
    virtual void receiveEvent(const Event&& event) = 0;
    virtual ~MatchObserver(){}
};

#endif
