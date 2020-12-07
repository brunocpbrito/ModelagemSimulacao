#include <string.h>
#include <omnetpp.h>
#include <math.h>


using namespace omnetpp;

class Disciplina : public cSimpleModule {
  private:
    bool on = false;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void updateDisplay();
    virtual int choose(int choices);
    virtual int randomPortIndex();

  public:
    void switchState() {
        on = !on;
    };
};

Define_Module(Disciplina);

int Disciplina::choose(int choices) {
    //a fun��o srand seta um seed aleat�rio e depois a fun��o rand
    //gera um n�mero aleat�rio. em seguida, o m�dulo gera um valor
    //inteiro de 0 at� choices-1
    std::srand(time(NULL));
    int rnum = std::rand();
    return rnum % choices;
}

int Disciplina::randomPortIndex() {
    return choose(gateSize("saida"));
}

void Disciplina::updateDisplay() {
    const char* txt2 = "off";
    const char* color = "red";
    const char* status = "status/red";
    if (on) {
        txt2 = "on";
        //color = "black";
        status = "status/green";
    }
    cDisplayString& ds = getDisplayString();
    ds.setTagArg("i2", 0, status);
    //ds.setTagArg("i", 1, color);
    //� preciso chamar o "refreshDisplay" para atualizar a exibi��o.
    //caso n�o chame esta fun��o, as altera��es n�o ser�o exibidas.
    refreshDisplay();
    bubble(txt2);
}

void Disciplina::initialize() {
    if (strcmp("inicio", getName())==0 ) {
        cMessage *msg = new cMessage("switchMsg");
        send(msg, "saida", 0);
    }
}

void Disciplina::handleMessage(cMessage *msg) {
    switchState();
    updateDisplay();
    //send(msg, "saida");
    send(msg, "saida", randomPortIndex());
}
