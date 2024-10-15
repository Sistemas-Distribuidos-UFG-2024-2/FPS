import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class MaioridadeImpl extends UnicastRemoteObject implements Maioridade {

    protected MaioridadeImpl() throws RemoteException {
        super();
    }

    @Override
    public String verificarMaioridade(String nome, String sexo, int idade) throws RemoteException {
        if (sexo.equalsIgnoreCase("masculino") && idade >= 18) {
            return nome + " é maior de idade.";
        } else if (sexo.equalsIgnoreCase("feminino") && idade >= 21) {
            return nome + " é maior de idade.";
        } else {
            return nome + " não é maior de idade.";
        }
    }
}
