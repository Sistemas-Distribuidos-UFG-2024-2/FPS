import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class PesoIdealImpl extends UnicastRemoteObject implements PesoIdeal {
    protected PesoIdealImpl() throws RemoteException {
        super();
    }

    public float calcularPesoIdeal(float altura, char sexo) throws RemoteException {
        if (sexo == 'M') {
            return (72.7f * altura) - 58;
        } else {
            return (62.1f * altura) - 44.7f;
        }
    }

    public static void main(String[] args) {
        try {
            Naming.rebind("rmi://localhost/PesoIdealService", new PesoIdealImpl());
            System.out.println("Servidor RMI iniciado...");
        } catch (Exception e) {
            System.err.println("Erro no servidor: " + e);
        }
    }
}