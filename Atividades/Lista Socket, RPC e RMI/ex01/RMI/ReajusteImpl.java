import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class ReajusteImpl extends UnicastRemoteObject implements Reajuste {
    protected ReajusteImpl() throws RemoteException {
        super();
    }

    @Override
    public float calcularReajuste(String nome, String cargo, float salario) throws RemoteException {
        if (cargo.equalsIgnoreCase("operador")) {
            return salario * 1.20f; // Reajuste de 20%
        } else if (cargo.equalsIgnoreCase("programador")) {
            return salario * 1.18f; // Reajuste de 18%
        }
        return salario; // Sem reajuste
    }
}
