import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class BancoImpl extends UnicastRemoteObject implements Banco {

    protected BancoImpl() throws RemoteException {
        super();
    }

    @Override
    public float calcularCredito(float saldoMedio) throws RemoteException {
        if (saldoMedio >= 0 && saldoMedio <= 200) {
            return 0;
        } else if (saldoMedio >= 201 && saldoMedio <= 400) {
            return saldoMedio * 0.20f;
        } else if (saldoMedio >= 401 && saldoMedio <= 600) {
            return saldoMedio * 0.30f;
        } else {
            return saldoMedio * 0.40f;
        }
    }
}
