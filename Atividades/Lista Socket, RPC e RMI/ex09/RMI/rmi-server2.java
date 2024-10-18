import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class BaralhoImpl extends UnicastRemoteObject implements Baralho {

    protected BaralhoImpl() throws RemoteException {
        super();
    }

    @Override
    public String obterNomeCarta(int valor, int naipe) throws RemoteException {
        String[] valores = {"Ás", "Dois", "Três", "Quatro", "Cinco", "Seis", "Sete", "Oito", "Nove", "Dez", "Valete", "Dama", "Rei"};
        String[] naipes = {"Ouros", "Paus", "Copas", "Espadas"};

        return valores[valor - 1] + " de " + naipes[naipe - 1];
    }
}
