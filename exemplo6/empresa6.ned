package exemplo6;

simple Disciplina
{
    parameters:
        @display("i=old/folder;i2=status/red, red");
    gates:
        input entrada[];
        output saida[1];
}


network Perfil
{
    @display("bgb=381,245");
    types:
        channel D extends ned.DelayChannel
        {
            delay = 60s;
        }
    submodules:
        inicio: Disciplina {
            @display("i=,yellow1;p=284,45");
        }
        especificas[3]: Disciplina {
            @display("i=,darkblue;p=254,190");
        }
        comum[6]: Disciplina {
            @display("i=,red;p=52,88");
        }
    connections:
        inicio.saida++ --> D --> comum[0].entrada++;
        comum[0].saida++ --> D --> comum[1].entrada++;
        comum[0].saida++ --> D --> comum[2].entrada++;

        comum[1].saida++ --> D --> comum[3].entrada++;
        comum[3].saida++ --> D --> comum[4].entrada++;
        comum[2].saida++ --> D --> comum[4].entrada++;
        comum[4].saida++ --> D --> comum[5].entrada++;

        comum[2].saida++ --> D --> especificas[0].entrada++;
        especificas[0].saida++ --> D --> especificas[1].entrada++;
        especificas[1].saida++ --> D --> especificas[2].entrada++;

        especificas[2].saida++ --> D --> comum[5].entrada++;
        comum[5].saida++ --> D --> inicio.entrada++;

        //for i=0..sizeof(m)-2, for j=i+1..sizeof(m)-1 {
        //	m[i].port++ <--> D <--> m[j].port++;
        //}
}
