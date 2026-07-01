
/**
 * Escreva uma descrição da classe PlanoPremiumTop aqui.
 * 
 * @author (seu nome) 
 * @version (um número da versão ou uma data)
 */

import java.io.Serializable;
import java.util.*;
import java.util.List;

public class PlanoPremiumTop implements PlanoSubscricao {
    @Override
    public int calcularPontosReproducao(int pontosAtuais) {
        // 100 pontos para a adesão (pode ser aplicado uma vez) e 2.5% dos pontos já acumulados para cada nova reprodução.
        // Aqui implementei só a parte de 2.5% por reprodução:
        return (int) Math.round(pontosAtuais * 0.025);
    }
    @Override
    public String getNomePlano() {
        return "PremiumTop";
    }
}
