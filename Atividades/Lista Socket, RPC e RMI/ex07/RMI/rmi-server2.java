import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class AposentadoriaImpl extends UnicastRemoteObject implements Aposentadoria {

    protected AposentadoriaImpl() throws RemoteException {
        super();
    }

    @Override
    public boolean verificarAposentadoria(int idade, int tempoServico) throws RemoteException {
        return idade >= 65 || (idade >= 60 && tempoServico >= 25) || tempoServico >= 30;
    }
}