
/**
 * Escreva uma descrição da classe PlanoPremiumBase aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public class PlanoPremiumBase implements PlanoSubscricao {
    @Override
    public int calcularPontosReproducao(int pontosAtuais) {
        return 10;
    }
    @Override
    public String getNomePlano() {
        return "PremiumBase";
    }
}
