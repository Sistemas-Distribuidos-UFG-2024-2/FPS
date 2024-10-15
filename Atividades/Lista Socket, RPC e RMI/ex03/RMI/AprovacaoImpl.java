import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;

public class AprovacaoImpl extends UnicastRemoteObject implements Aprovacao {

    public AprovacaoImpl() throws RemoteException {
        super();
    }

    @Override
    public String calcularAprovacao(double n1, double n2, double n3) throws RemoteException {
        double media = (n1 + n2) / 2;

        if (media >= 7.0) {
            return "Aprovado";
        } else if (media > 3.0) {
            double mediaFinal = (media + n3) / 2;
            if (mediaFinal >= 5.0) {
                return "Aprovado";
            } else {
                return "Reprovado";
            }
        } else {
            return "Reprovado";
        }
    }
}